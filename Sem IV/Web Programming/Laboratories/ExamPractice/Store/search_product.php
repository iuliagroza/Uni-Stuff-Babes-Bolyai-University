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

$products = [];

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $name = $_POST["name"];

    $sql = "SELECT * FROM Products WHERE name LIKE '$name%'";

    $result = $conn->query($sql);

    if ($result->num_rows > 0) {
        while($row = $result->fetch_assoc()) {
            $products[] = $row;
        }
    } else {
        echo "No results";
    }
}

$conn->close();

?>

<!DOCTYPE html>
<html>
<body>

<h2>Search Product</h2>

<form method="post">
  <label for="name">Product Name:</label><br>
  <input type="text" id="name" name="name" required><br>
  <input type="submit" value="Search">
</form>

<h3>Products:</h3>

<?php foreach ($products as $product) { ?>
  <p>
    <strong><?php echo $product['name']; ?></strong><br>
    <?php echo $product['description']; ?><br>
    <a href="order_product.php?productid=<?php echo $product['id']; ?>">Order this product</a>
  </p>
<?php } ?>

<button onclick="window.location.href='add_product.php'">Add Product</button>
<button onclick="window.location.href='finalize_order.php'">Finalize or Cancel Order</button>

</body>
</html>
