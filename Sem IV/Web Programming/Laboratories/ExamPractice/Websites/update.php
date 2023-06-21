<!DOCTYPE html>
<html>
<body>

<h2>Update Document Form</h2>
<form action="update_process.php" method="post">
  <input type="text" id="doc_id" name="doc_id" placeholder="Enter Document ID">
  <input type="text" id="keyword1" name="keyword1" placeholder="Enter keyword 1">
  <input type="text" id="keyword2" name="keyword2" placeholder="Enter keyword 2">
  <input type="text" id="keyword3" name="keyword3" placeholder="Enter keyword 3">
  <input type="text" id="keyword4" name="keyword4" placeholder="Enter keyword 4">
  <input type="text" id="keyword5" name="keyword5" placeholder="Enter keyword 5">
  <input type="submit" value="Update">
</form>
<br>

<button onclick="window.location.href='websites.php'">See all websites</button>
<button onclick="window.location.href='index.php'">Search for keywords</button>

</body>
</html>
