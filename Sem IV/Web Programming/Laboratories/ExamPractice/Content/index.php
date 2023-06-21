<?php
session_start();
$db = new mysqli("localhost", "username", "password", "database");
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $user = $_POST["user"];
    $password = $_POST["password"];
    $result = $db->query("SELECT * FROM Users WHERE User='$user' AND Password='$password'");
    if ($result->num_rows > 0) {
        $row = $result->fetch_assoc();
        $_SESSION["id"] = $row["ID"];
        $_SESSION["role"] = $row["Role"];
        header("Location: index.php");
    } else {
        echo "Invalid username or password";
    }
}
?>
