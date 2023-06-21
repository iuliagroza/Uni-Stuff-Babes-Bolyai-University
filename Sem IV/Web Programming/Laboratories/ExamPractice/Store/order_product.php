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

$productid = $_GET['productid'];

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $quantity = $_POST["quantity"];
    $_SESSION["orders"][] = ["productid" => $productid, "quantity" => $quantity];
    echo "Product added to the order";
}

$conn->close();

?>

<!DOCTYPE html>
<html>
<body>

<h2>Order Product</h2>

<form method="post">
  <label for="quantity">Quantity:</label><br>
  <input type="number" id="quantity" name="quantity" required><br>
  <input type="submit" value="Add to Order">
</form>

<a href="search_product.php">Search Other Products</a>
<a href="finalize_order.php">Finalize or Cancel Order</a>

</body>
</html>
