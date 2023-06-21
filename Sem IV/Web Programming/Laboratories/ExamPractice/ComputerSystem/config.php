<?php
$host = '127.0.0.1:3307';
$db = 'ComputerSystem';
$user = 'root';
$pass = '';

try {
    $pdo = new PDO("mysql:host=$host;dbname=$db", $user, $pass);
} catch (PDOException $e) {
    die("Could not connect to the database: " . $e->getMessage());
}
?>
