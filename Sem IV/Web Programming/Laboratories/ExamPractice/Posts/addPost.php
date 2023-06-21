<?php
include 'dbconnect.php';

$username = $_POST['username'];
$topic = $_POST['topic'];
$text = $_POST['text'];

// Check if topic exists, if not insert
$checkSql = "SELECT id FROM Topics WHERE topicname = ?";
$stmt = $conn->prepare($checkSql);
$stmt->bind_param("s", $topic);
$stmt->execute();
$stmt->bind_result($topicId);
if($stmt->fetch()) {
  // Topic exists, use the id
} else {
  // Topic does not exist, insert and use the new id
  $insertSql = "INSERT INTO Topics (topicname) VALUES (?)";
  $stmt = $conn->prepare($insertSql);
  $stmt->bind_param("s", $topic);
  $stmt->execute();
  $topicId = $conn->insert_id;
}

// Now insert the post
$postSql = "INSERT INTO Posts (user, topicid, text, date) VALUES (?, ?, ?, NOW())";
$stmt = $conn->prepare($postSql);
$stmt->bind_param("sis", $username, $topicId, $text);
$stmt->execute();

header("Location: index.php");
?>
