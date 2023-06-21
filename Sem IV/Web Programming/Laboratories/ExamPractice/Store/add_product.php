<?php
session_start();

if (!isset($_SESSION["username"])) {
    header('Location: index.php');
}

$servername = "127.0.0.1:3307";
$username = "root";
$password = "";
$dbname = "Store";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $name = $_POST["name"];
    $description = $_POST["description"];

    $sql = "INSERT INTO Products (name, description) VALUES ('$name', '$description')";

    if ($conn->query($sql) === TRUE) {
        echo "New product added successfully";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }
}

$conn->close();

?>

<!DOCTYPE html>
<html>
<body>

<h2>Add Product</h2>

<form method="post">
  <label for="name">Product Name:</label><br>
  <input type="text" id="name" name="name" required><br>
  <label for="description">Description:</label><br>
  <textarea id="description" name="description" required></textarea><br>
  <input type="submit" value="Add Product">
</form>

<button onclick="window.location.href='search_product.php'">Search Product</button>

</body>
</html>
