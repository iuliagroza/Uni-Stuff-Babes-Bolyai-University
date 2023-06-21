<?php
session_start();
require_once 'config.php';

if (isset($_POST['username']) && isset($_POST['password'])) {
    $stmt = $pdo->prepare('SELECT * FROM Users WHERE username = ? AND password = ?');
    $stmt->execute([$_POST['username'], $_POST['password']]);
    $user = $stmt->fetch();
    
    if ($user) {
        $_SESSION['user_id'] = $user['id'];
        header('Location: files.php');
        exit;
    } else {
        echo "Invalid username or password";
    }
}

?>

<form method="POST">
    <input type="text" name="username" placeholder="Username" required>
    <input type="password" name="password" placeholder="Password" required>
    <input type="submit" value="Login">
</form>
