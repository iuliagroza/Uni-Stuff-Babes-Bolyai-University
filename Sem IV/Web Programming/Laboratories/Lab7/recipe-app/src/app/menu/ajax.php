<?php
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

// Establish database connection
$servername = "127.0.0.1:3307";
$username = "root";
$password = "";
$dbname = "test";

$conn = new mysqli($servername, $username, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// Retrieve recipes of a specific type
if ($_SERVER["REQUEST_METHOD"] === "POST") {
    $recipeType = $_POST['type'];

    if ($recipeType !== "All") {
        $stmt = $conn->prepare("SELECT * FROM Recipe WHERE Type = ?");
        if ($stmt === false) {
            die("Failed to prepare SQL statement: " . $conn->error);
        }
        $stmt->bind_param("s", $recipeType);
    } else {
        $stmt = $conn->prepare("SELECT * FROM Recipe");
        if ($stmt === false) {
            die("Failed to prepare SQL statement: " . $conn->error);
        }
    }

    $stmt->execute();
    $result = $stmt->get_result();

    if ($result->num_rows > 0) {
        while ($row = $result->fetch_assoc()) {
            echo "<h3>" . $row['Name'] . "</h3>";
            echo "<p>Author: " . $row['Author'] . "</p>";
            echo "<p>Recipe: " . $row['Recipe'] . "</p>";
            echo "<button class='delete-recipe' data-id='" . $row['Rid'] . "'>Delete</button>";
            echo "<button class='edit-recipe' data-id='" . $row['Rid'] . "'>Edit</button>";
            echo "<hr>";
        }
    } else {
        echo "No recipes found.";
    }
}

$conn->close();
?>
