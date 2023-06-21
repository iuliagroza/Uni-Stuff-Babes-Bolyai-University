<?php
$db = new mysqli("localhost", "username", "password", "database");
$result = $db->query("SELECT * FROM Content ORDER BY Date DESC LIMIT 4");
$data = [];
while ($row = $result->fetch_assoc()) {
    $data[] = $row;
}
echo json_encode($data);
?>

<script>
$(document).ready(function() {
    var contentIndex = 0;
    var contentList = [];

    function refreshContent() {
        $.ajax({
            url: 'get_content.php',
            success: function(data) {
                contentList = JSON.parse(data);
                contentIndex = 0;
                updateContentDisplay();
            }
        });
    }

    function updateContentDisplay() {
        if (contentList.length > 0) {
            var content = contentList[contentIndex];
            $('#content-title').text(content.Title);
            $('#content-description').text(content.Description);
            $('#content-url').attr('href', content.URL);
            contentIndex = (contentIndex + 1) % contentList.length;
        } else {
            $('#content-title').text("");
            $('#content-description').text("");
            $('#content-url').attr('href', "#");
        }
    }

    setInterval(refreshContent, 5000);  // Refresh every 5 seconds
    setInterval(updateContentDisplay, 2000);  // Change content every 2 seconds
});

</script>
<div id="content-display">
    <h2 id="content-title"></h2>
    <p id="content-description"></p>
    <a id="content-url" href="#">Read more</a>
</div>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
<script src="main.js"></script>

