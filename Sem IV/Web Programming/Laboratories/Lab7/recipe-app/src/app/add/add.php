<?php
$servername = "127.0.0.1:3307";
$username = "root";
$password = "";
$dbname = "test";

$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$message = '';

// Insert a new recipe into the database
if ($_SERVER["REQUEST_METHOD"] === "POST") {
    $name = $_POST['name'];
    $author = $_POST['author'];
    $type = $_POST['type'];
    $recipe = $_POST['recipe'];

    // Validate input fields
    $errors = [];
    if (empty($name)) {
        $errors[] = "Name is required.";
    } else if (empty($author)) {
        $errors[] = "Author is required.";
    } else if (empty($type)) {
        $errors[] = "Type is required.";
    } else if (empty($recipe)) {
        $errors[] = "Recipe is required.";
    } else if ($type !== "Desert" && $type !== "Supe" && $type !== "Paste") {
        $errors[] = "Please provide a valid type.";
    }

    // If there are no errors, proceed with inserting the recipe
    if (empty($errors)) {
        // Sanitize input to prevent SQL injection attacks
        $name = mysqli_real_escape_string($conn, $name);
        $author = mysqli_real_escape_string($conn, $author);
        $type = mysqli_real_escape_string($conn, $type);
        $recipe = mysqli_real_escape_string($conn, $recipe);

        $sql = "INSERT INTO Recipe (Name, Author, Type, Recipe) VALUES ('$name', '$author', '$type', '$recipe')";

        if ($conn->query($sql) === TRUE) {
            $message = "Recipe added successfully.";
        } else {
            $message = "Error: " . $sql . "<br>" . $conn->error;
        }
    } else {
        // Display validation error messages
        $message = "<span class='error'>" . implode("<br>", $errors) . "</span>";
    }
}

$conn->close();
?>