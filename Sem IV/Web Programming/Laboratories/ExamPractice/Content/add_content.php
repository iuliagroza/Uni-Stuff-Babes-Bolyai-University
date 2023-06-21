<?php
session_start();
$db = new mysqli("localhost", "username", "password", "database");
if ($_SESSION["role"] != 1) {
    echo "You are not a content creator!";
} else {
    if ($_SERVER["REQUEST_METHOD"] == "POST") {
        if (isset($_POST["add"])) {
            $title = $_POST["title"];
            $description = $_POST["description"];
            $url = $_POST["url"];
            $userID = $_SESSION["id"];
            $db->query("INSERT INTO Content (Title, Description, URL, UserID) VALUES ('$title', '$description', '$url', '$userID')");
        } elseif (isset($_POST["remove"])) {
            $id = $_POST["id"];
            $userID = $_SESSION["id"];
            $db->query("DELETE FROM Content WHERE ID='$id' AND UserID='$userID'");
        }
    }
}
?>
