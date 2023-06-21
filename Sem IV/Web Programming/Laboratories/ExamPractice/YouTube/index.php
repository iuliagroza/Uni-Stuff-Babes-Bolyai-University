<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "database_name";

$conn = new mysqli($servername, $username, $password, $dbname);

if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

if(isset($_POST['username'])) {
    $username = $_POST['username'];
}

if(isset($_POST['channel_id'])) {
    $channel_id = $_POST['channel_id'];
    $person_id = $conn->query("SELECT id FROM Persons WHERE name = '$username'")->fetch_assoc()['id'];
    $channel_subscribers = $conn->query("SELECT subscribers FROM Channels WHERE id = '$channel_id'")->fetch_assoc()['subscribers'];

    if(strpos($channel_subscribers, $person_id) !== false) {
        $channel_subscribers = preg_replace("/($person_id:)(\d{4}-\d{2}-\d{2})/", "$1" . date('Y-m-d'), $channel_subscribers);
    } else {
        $channel_subscribers .= "," . $person_id . ":" . date('Y-m-d');
    }

    $conn->query("UPDATE Channels SET subscribers = '$channel_subscribers' WHERE id = '$channel_id'");
}

?>

<html>
<body>

<h2>My Channels:</h2>
<?php
if(isset($username)) {
    $person_id = $conn->query("SELECT id FROM Persons WHERE name = '$username'")->fetch_assoc()['id'];
    $result = $conn->query("SELECT * FROM Channels WHERE ownerid = '$person_id'");

    while($row = $result->fetch_assoc()) {
        echo "ID: " . $row["id"]. " - Name: " . $row["name"]. " - Description: " . $row["description"]. " - Subscribers: " . $row["subscribers"]. "<br>";
    }
}
?>

<h2>Subscribed Channels:</h2>
<?php
if(isset($username)) {
    $person_id = $conn->query("SELECT id FROM Persons WHERE name = '$username'")->fetch_assoc()['id'];
    $result = $conn->query("SELECT name, description FROM Channels WHERE FIND_IN_SET('$person_id', REPLACE(subscribers, ':', ','))");

    while($row = $result->fetch_assoc()) {
        echo "Name: " . $row["name"]. " - Description: " . $row["description"]. "<br>";
    }
}
?>

<h2>Subscribe to Channel:</h2>
<form method="post" action="<?php echo $_SERVER['PHP_SELF'];?>">
    <label for="channel_id">Channel ID:</label><br>
    <input type="text" id="channel_id" name="channel_id" value=""><br>
    <input type="submit" value="Subscribe">
</form> 

</body>
</html>
