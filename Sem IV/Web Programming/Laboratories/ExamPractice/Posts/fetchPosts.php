<?php
include 'dbconnect.php';

$sql = "SELECT Posts.user, Topics.topicname, Posts.text, Posts.date FROM Posts JOIN Topics ON Posts.topicid = Topics.id ORDER BY Posts.date DESC LIMIT 10";
$result = $conn->query($sql);
if ($result->num_rows > 0) {
  while($row = $result->fetch_assoc()) {
    echo "<p><strong>" . $row["user"]. "</strong> posted in <strong>" . $row["topicname"]. "</strong> at " . $row["date"]. "<br>" . $row["text"]. "</p>";
  }
}
?>
