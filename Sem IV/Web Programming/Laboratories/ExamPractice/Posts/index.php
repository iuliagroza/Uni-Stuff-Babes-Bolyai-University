<?php
include 'dbconnect.php';
?>
<!DOCTYPE html>
<html>
<head>
  <title>Forum</title>
  <script src="https://code.jquery.com/jquery-3.5.1.min.js"></script>
</head>
<body>
  <form method="post" action="addPost.php">
    Username: <input type="text" id="username" name="username">
    Topic: <input type="text" id="topic" name="topic">
    Text: <textarea id="text" name="text"></textarea>
    <input type="submit" value="Submit">
  </form>
  <div id="recentPosts"></div>

<script>
$(document).ready(function() {
  setInterval(function() {
    $('#recentPosts').load('fetchPosts.php')
  }, 5000); // every 5 seconds
});
</script>

</body>
</html>
