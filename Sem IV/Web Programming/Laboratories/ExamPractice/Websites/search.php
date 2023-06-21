<?php
require_once('db.php');

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $keywords = explode(' ', $_POST['keywords']);
    
    $inQuery = implode(',', array_fill(0, count($keywords), '?'));
    $sql = "SELECT d.id, d.name, d.keyword1, d.keyword2, d.keyword3, d.keyword4, d.keyword5
            FROM Documents d 
            WHERE d.keyword1 IN ($inQuery)
            OR d.keyword2 IN ($inQuery)
            OR d.keyword3 IN ($inQuery)
            OR d.keyword4 IN ($inQuery)
            OR d.keyword5 IN ($inQuery)";

    // Appending the keywords array 5 times to match each IN clause.
    $params = array_merge($keywords, $keywords, $keywords, $keywords, $keywords);

    $stmt = $pdo->prepare($sql);

    // Binding each keyword separately
    foreach ($params as $k => $param) {
        $stmt->bindValue(($k+1), $param);
    }

    $stmt->execute();
    $documents = $stmt->fetchAll(PDO::FETCH_ASSOC);

    // Filtering documents where exactly 3 keywords match
    $results = [];
    foreach ($documents as $document) {
        $matches = array_intersect($keywords, array_values($document));
        if (count($matches) === 3) {
            $results[] = $document;
        }
    }

    echo "<table border='1'>";
    echo "<tr><th>Id</th><th>Name</th><th>Keyword1</th><th>Keyword2</th><th>Keyword3</th><th>Keyword4</th><th>Keyword5</th></tr>";

    foreach ($results as $document) {
        echo "<tr>";
        echo "<td>" . $document['id'] . "</td>";
        echo "<td>" . $document['name'] . "</td>";
        echo "<td>" . $document['keyword1'] . "</td>";
        echo "<td>" . $document['keyword2'] . "</td>";
        echo "<td>" . $document['keyword3'] . "</td>";
        echo "<td>" . $document['keyword4'] . "</td>";
        echo "<td>" . $document['keyword5'] . "</td>";
        echo "</tr>";
    }

    echo "</table><br><button onclick=\"window.location.href='websites.php'\">Back</button>";

}
?>
