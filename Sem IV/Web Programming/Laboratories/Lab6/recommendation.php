<?php
$servername = "127.0.0.1:3307";
$username = "root";
$password = "";
$dbname = "test";

$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Retrieve a random recipe from the database
$sql = "SELECT * FROM Recipe ORDER BY RAND() LIMIT 1";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    $row = $result->fetch_assoc();
    $name = $row['Name'];
    $author = $row['Author'];
    $type = $row['Type'];
    $recipe = $row['Recipe'];
} else {
    // No recipe found in the database
    $name = "No Recipe Found";
    $author = "";
    $type = "";
    $recipe = "";
}

$conn->close();
?>

<!DOCTYPE html>
<html>
<head>
    <title>Random Recipe</title>
    <script>
        function redirect() {
            window.location.href = "menu.php";
        }
    </script>
</head>
<body>
    <h1>Random Recipe Recommendation</h1>

    <h2>Recommended Recipe:</h2>
    <h3>Name: <?= $name ?></h3>
    <p>Author: <?= $author ?></p>
    <p>Type: <?= $type ?></p>
    <p>Recipe:</p>
    <pre><?= $recipe ?></pre>

    <button onclick="location.reload()">Get Another Random Recipe</button>
    <button type="button" onclick="redirect()">Back</button>
</body>
</html>
