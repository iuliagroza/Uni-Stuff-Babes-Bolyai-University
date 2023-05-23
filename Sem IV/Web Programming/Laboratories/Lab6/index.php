<?php
session_start();

// Check if the user is already logged in
if (isset($_SESSION['loggedin']) && $_SESSION['loggedin'] === true) {
    // Redirect to the menu page
    header("Location: menu.php");
    exit;
}

// Check if the login form is submitted
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $username = $_POST['username'];
    $password = $_POST['password'];

    // Validate username and password (You can replace this with your own validation logic)
    if ($username === 'admin' && $password === 'testpwd123') {
        // Authentication successful, set session variables
        $_SESSION['username'] = $username;
        $_SESSION['loggedin'] = true; // Set the loggedin session variable

        // Redirect to homepage or any other page after successful login
        header('Location: menu.php');
        exit;
    } else {
        // Invalid credentials
        $error = "<span class='error'>Invalid username or password.</span>";
    }
}

// Logout logic
if (isset($_GET['logout'])) {
    session_destroy();
    header('Location: index.php');
    exit;
}
?>

<!DOCTYPE html>
<html>
<head>
    <title>Login</title>
    <style>
        .error {
            color: red;
        }
    </style>
</head>
<body>
    <h1>Login</h1>

    <?php if (isset($error)): ?>
        <p><?= $error ?></p>
    <?php endif; ?>

    <form method="post" action="">
        <label for="username">Username:</label><br>
        <input type="text" id="username" name="username"><br>
        <label for="password">Password:</label><br>
        <input type="password" id="password" name="password"><br><br>
        <input type="submit" value="Login">
    </form>
</body>
</html>
