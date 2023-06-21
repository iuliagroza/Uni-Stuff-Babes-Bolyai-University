<?php
session_start();

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $_SESSION["username"] = $_POST["username"];
    header('Location: add_product.php');
}

?>

<!DOCTYPE html>
<html>
<body>

<h2>Enter Username</h2>

<form method="post">
  <label for="username">Username:</label><br>
  <input type="text" id="username" name="username" required><br>
  <input type="submit" value="Submit">
</form>

</body>
</html>
