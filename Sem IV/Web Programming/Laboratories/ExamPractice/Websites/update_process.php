<?php
require_once('db.php');

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $doc_id = $_POST['doc_id'];
    $keyword1 = $_POST['keyword1'];
    $keyword2 = $_POST['keyword2'];
    $keyword3 = $_POST['keyword3'];
    $keyword4 = $_POST['keyword4'];
    $keyword5 = $_POST['keyword5'];
    
    $sql = "UPDATE Documents 
            SET keyword1 = :keyword1, keyword2 = :keyword2, keyword3 = :keyword3, keyword4 = :keyword4, keyword5 = :keyword5
            WHERE id = :doc_id";
    
    $stmt = $pdo->prepare($sql);
    $stmt->bindParam(':doc_id', $doc_id, PDO::PARAM_INT);
    $stmt->bindParam(':keyword1', $keyword1, PDO::PARAM_STR);
    $stmt->bindParam(':keyword2', $keyword2, PDO::PARAM_STR);
    $stmt->bindParam(':keyword3', $keyword3, PDO::PARAM_STR);
    $stmt->bindParam(':keyword4', $keyword4, PDO::PARAM_STR);
    $stmt->bindParam(':keyword5', $keyword5, PDO::PARAM_STR);
    $stmt->execute();

    echo "Document keywords updated successfully! <br><button onclick=\"window.location.href='websites.php'\">Back</button>";
}
?>
