<?php
require_once('db.php');

$sql = "SELECT w.id, w.URL, COUNT(d.idwebsite) AS 'Number of Documents'
        FROM Websites w
        LEFT JOIN Documents d
        ON w.id = d.idwebsite
        GROUP BY w.id";

$stmt = $pdo->prepare($sql);
$stmt->execute();
$websites = $stmt->fetchAll(PDO::FETCH_ASSOC);

// Displaying results in a table
echo "<table>";
echo "<tr><th>Website ID</th><th>URL</th><th>Number of Documents</th></tr>";
foreach ($websites as $website) {
    echo "<tr><td>{$website['id']}</td><td>{$website['URL']}</td><td>{$website['Number of Documents']}</td></tr>";
}
echo "</table><br><button onclick=\"window.location.href='update.php'\">Update document keywords</button><br><button onclick=\"window.location.href='index.php'\">Search for keywords</button>";
?>
