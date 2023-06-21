<?php

$pdo = new PDO('mysql:host=localhost;dbname=test', 'username', 'password');

// Get user's name
$username = $_POST['username'];

// If a new article was posted
if (isset($_POST['article'])) {
    $journalName = $_POST['journal_name'];
    $summary = $_POST['summary'];
    $date = time();

    // Check if journal exists, otherwise add it
    $stmt = $pdo->prepare("SELECT id FROM Journals WHERE name = ?");
    $stmt->execute([$journalName]);
    $journalId = $stmt->fetchColumn();

    if (!$journalId) {
        $stmt = $pdo->prepare("INSERT INTO Journals (name) VALUES (?)");
        $stmt->execute([$journalName]);
        $journalId = $pdo->lastInsertId();
    }

    // Add new article
    $stmt = $pdo->prepare("INSERT INTO Articles (user, journalid, summary, date) VALUES (?, ?, ?, ?)");
    $stmt->execute([$username, $journalId, $summary, $date]);
}

// If a request was made to view user's articles in a specific journal
if (isset($_POST['view_journal'])) {
    $journalName = $_POST['view_journal'];

    $stmt = $pdo->prepare("SELECT Articles.id, Articles.summary, Articles.date FROM Articles 
        JOIN Journals ON Articles.journalid = Journals.id 
        WHERE Articles.user = ? AND Journals.name = ?");
    $stmt->execute([$username, $journalName]);

    $articles = $stmt->fetchAll();
    // Display $articles as needed
}

// End of PHP code
?>

<form method="POST">
    <input type="text" name="username" placeholder="Your name">
    <input type="text" name="journal_name" placeholder="Journal name">
    <textarea name="summary" placeholder="Article summary"></textarea>
    <input type="submit" name="article" value="Post article">
    <input type="submit" name="view_journal" value="View articles in this journal">
</form>
