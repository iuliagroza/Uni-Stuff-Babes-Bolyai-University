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
