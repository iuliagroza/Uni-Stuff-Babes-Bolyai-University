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

$message = '';

// Delete a recipe from the database
if ($_SERVER["REQUEST_METHOD"] === "POST") {
    $id = $_POST['id'];

    // Sanitize input to prevent SQL injection attacks
    $id = mysqli_real_escape_string($conn, $id);

    $sql = "DELETE FROM Recipe WHERE Rid='$id'";

    if ($conn->query($sql) === TRUE) {
        $message = "Recipe deleted successfully.";
    } else {
        $message = "Error: " . $sql . "<br>" . $conn->error;
    }
}

$conn->close();
?>

<!DOCTYPE html>
<html>
<head>
    <title>Delete Recipe</title>
</head>
<body>
    <h1>Delete Recipe</h1>

    <?php if (!empty($message)): ?>
        <p><?= $message ?></p>
    <?php endif; ?>

    <form method="post" action="">
        <label for="id">Recipe ID:</label><br>
        <input type="text" id="id" name="id"><br>
        <input type="submit" value="Delete">
    </form>
</body>
</html>
