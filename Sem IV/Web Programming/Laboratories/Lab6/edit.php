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

// Fetch the recipe data based on the provided id
if (isset($_GET['id'])) {
    $id = $_GET['id'];
    $sql = "SELECT * FROM Recipe WHERE Rid='$id'";
    $result = $conn->query($sql);

    if ($result->num_rows > 0) {
        $row = $result->fetch_assoc();
        $id = $row['Rid']; // Assign the value of 'Rid' to $id
        $name = $row['Name'];
        $author = $row['Author'];
        $type = $row['Type'];
        $recipe = $row['Recipe'];
    } else {
        // No recipe found with the provided id
        $message = "Recipe not found.";
    }
}

// Update an existing recipe in the database
if ($_SERVER["REQUEST_METHOD"] === "POST") {
    $id = $_POST['id']; // Assign the value of 'id' from the form to $id
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

    // If there are no errors, proceed with updating the recipe
    if (empty($errors)) {
        // Sanitize input to prevent SQL injection attacks
        $name = mysqli_real_escape_string($conn, $name);
        $author = mysqli_real_escape_string($conn, $author);
        $type = mysqli_real_escape_string($conn, $type);
        $recipe = mysqli_real_escape_string($conn, $recipe);

        $sql = "UPDATE Recipe SET Name='$name', Author='$author', Type='$type', Recipe='$recipe' WHERE Rid='$id'";

        if ($conn->query($sql) === TRUE) {
            $message = "Recipe updated successfully.";
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

<!DOCTYPE html>
<html>
<head>
    <title>Update Recipe</title>

    <style>
        .error {
            color: red;
        }
    </style>

    <script>
        function redirect() {
            window.location.href = "menu.php";
        }

        function confirmUpdate() {
            var result = confirm("Are you sure you want to update this recipe?");
            if (result) {
                // User clicked "OK" to confirm
                return true;
            } else {
                // User clicked "Cancel" to cancel the update
                return false;
            }
        }
    </script>
</head>
<body>
    <h1>Update Recipe</h1>

    <?php if (!empty($message)): ?>
        <p><?= $message ?></p>
    <?php endif; ?>

    <form method="post" action="">
    <input type="hidden" name="id" value="<?= isset($id) ? $id : '' ?>">
        <label for="name">Name:</label><br>
        <input type="text" id="name" name="name" value="<?= isset($name) ? htmlspecialchars($name) : '' ?>"><br>
        <label for="author">Author:</label><br>
        <input type="text" id="author" name="author" value="<?= isset($author) ? htmlspecialchars($author) : '' ?>"><br>
        <label for="type">Type:</label><br>
        <input type="text" id="type" name="type" value="<?= isset($type) ? htmlspecialchars($type) : '' ?>"><br>
        <label for="recipe">Recipe:</label><br>
        <textarea id="recipe" name="recipe"><?= isset($recipe) ? htmlspecialchars($recipe) : '' ?></textarea><br>
        <input type="submit" onclick="confirmUpdate()" value="Update">
        <button type="button" onclick="redirect()">Back</button>
    </form>
</body>
</html>
