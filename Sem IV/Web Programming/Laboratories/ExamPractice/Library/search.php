<?php
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

session_start();

$servername = "127.0.0.1:3307";
$username = "root";
$password = "";
$dbname = "Library";

$db = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($db->connect_error) {
    die("Connection failed: " . $db->connect_error);
}

// Store names into session for history
if (!isset($_SESSION['history'])) {
    $_SESSION['history'] = array();
}

array_push($_SESSION['history'], $_POST['name1'], $_POST['name2']);

$name1 = $_POST['name1'];
$name2 = $_POST['name2'];

// Initialize counters
$count1_books = $count1_articles = $count2_books = $count2_articles = 0;

// Get the count of articles and books for each author
$query1_books = $db->query("SELECT COUNT(*) FROM Carti WHERE idAutor IN (SELECT id FROM Persoane WHERE nume_prenume='$name1')");
$query1_articles = $db->query("SELECT COUNT(*) FROM Articole WHERE idAutor IN (SELECT id FROM Persoane WHERE nume_prenume='$name1')");
if($name2 != "") {
    $query2_books = $db->query("SELECT COUNT(*) FROM Carti WHERE idAutor IN (SELECT id FROM Persoane WHERE nume_prenume='$name2')");
    $query2_articles = $db->query("SELECT COUNT(*) FROM Articole WHERE idAutor IN (SELECT id FROM Persoane WHERE nume_prenume='$name2')");
}

if($query1_books->num_rows > 0) {
    $count1_books = $query1_books->fetch_array()[0];
}

if($query1_articles->num_rows > 0) {
    $count1_articles = $query1_articles->fetch_array()[0];
}

if(isset($query2_books) && $query2_books->num_rows > 0) {
    $count2_books = $query2_books->fetch_array()[0];
}

if(isset($query2_articles) && $query2_articles->num_rows > 0) {
    $count2_articles = $query2_articles->fetch_array()[0];
}

// Decide which author to show
if(($count1_books + $count1_articles) > ($count2_books + $count2_articles)) {
    $authorToShow = $name1;
} else {
    $authorToShow = $name2;
}

// Display articles and books by the author
$query_books = $db->query("SELECT * FROM Carti WHERE idAutor IN (SELECT id FROM Persoane WHERE nume_prenume='$authorToShow')");
$query_articles = $db->query("SELECT * FROM Articole WHERE idAutor IN (SELECT id FROM Persoane WHERE nume_prenume='$authorToShow')");

// Fetch and display results
echo "Author: " . $authorToShow . "<br>";

echo "Books:<br>";
if($query_books->num_rows > 0) {
    while($row = $query_books->fetch_assoc()) {
        echo "Title: " . $row['titlu'] . ", Publisher: " . $row['editura'] . ", Year: " . $row['an_aparitie'] . "<br>";
    }
} else {
    echo "No books found.<br>";
}

echo "<br>Articles:<br>";
if($query_articles->num_rows > 0) {
    while($row = $query_articles->fetch_assoc()) {
        echo "Title: " . $row['titlu'] . ", Pages: " . $row['nr_pagini'] . ", Type: " . $row['tip'] . "<br>";
    }
} else {
    echo "No articles found.<br>";
}

echo "<br><button onclick=\"window.location.href='index.php'\">Back</button>";

$db->close();
?>
