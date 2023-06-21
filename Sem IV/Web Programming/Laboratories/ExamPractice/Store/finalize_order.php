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
    if ($_POST['action'] == 'finalize') {
        foreach ($_SESSION["orders"] as $order) {
            $user = $_SESSION["username"];
            $productid = $order["productid"];
            $quantity = $order["quantity"];

            $sql = "INSERT INTO Orders (user, productid, quantity) VALUES ('$user', $productid, $quantity)";

            if ($conn->query($sql) === TRUE) {
                echo "Order finalized successfully<br>";
            } else {
                echo "Error: " . $sql . "<br>" . $conn->error;
            }
        }
    }

    unset($_SESSION["orders"]);
}

$conn->close();

?>

<!DOCTYPE html>
<html>
<body>

<h2>Finalize or Cancel Order</h2>

<form method="post">
  <button type="submit" name="action" value="finalize">Finalize Order</button>
  <button type="submit" name="action" value="cancel">Cancel Order</button>
</form>

</body>
</html>
