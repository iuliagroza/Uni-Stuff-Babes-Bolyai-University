<?php
session_start();

// Check if the user is already logged in
if (!isset($_SESSION['loggedin']) || $_SESSION['loggedin'] !== true) {
    // Redirect to the login page
    header("Location: index.php");
    exit;
}

// Logout logic
if (isset($_POST['logout'])) {
    // Destroy the session and redirect to the login page
    session_destroy();
    header("Location: index.php");
    exit;
}
?>

<!DOCTYPE html>
<html>
<head>
    <title>Food Recipes</title>
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
    <script>
        $(document).ready(function() {
            // AJAX request to retrieve recipes of a specific type
            function getRecipesByType(recipeType) {
                $.ajax({
                    url: 'ajax.php',
                    method: 'POST',
                    data: { type: recipeType },
                    success: function(response) {
                        $('#recipeList').html(response);
                    }
                });
            }

            // Event handler for recipe type selection
            $('.recipeType').click(function() {
                var type = $(this).attr('data-type');
                $('.recipeType').removeClass('active');
                $(this).addClass('active');
                getRecipesByType(type);
                $('#filter').text(type);
            });

            $(document).on('click', '.delete-recipe', function() {
                var id = $(this).attr('data-id');

                // Show a confirmation dialog
                var confirmation = confirm("Are you sure you want to delete this recipe?");

                // If the user clicked "OK", perform the deletion
                if (confirmation) {
                    $.ajax({
                        url: 'delete.php',
                        method: 'POST',
                        data: { id: id },
                        success: function(response) {
                            // Refresh the list of recipes
                            getRecipesByType($('#filter').text());
                        }
                    });
                }
            });

            $(document).on('click', '.edit-recipe', function() {
                var id = $(this).attr('data-id');
                // Redirect to the edit page
                window.location.href = 'edit.php?id=' + id;
            });
        });
    </script>
    <style>
        /* Add your CSS styling here */
    </style>
</head>
<body>
    <h1>Food Recipes</h1>

    <div>
        <button><a href="add.php" class="button" style="text-decoration: none; color: #000000;">Add Recipe</a></button>
    </div>
    <br><button><a href="recommendation.php" class="button" style="text-decoration: none; color: #000000;">I'm feeling lucky</a></button>

    <h2>Filter: <span id="filter">All</span></h2>
    
    <div id="recipeTypes">
        <button class="recipeType active" data-type="All">All</button>
        <button class="recipeType" data-type="Supe">Supe</button>
        <button class="recipeType" data-type="Paste">Paste</button>
        <button class="recipeType" data-type="Desert">Desert</button>
    </div>
    
    <div id="recipeList">
        <!-- Recipes will be dynamically loaded here using AJAX -->
    </div>

    <form id="logout-form" method="POST" action="">
        <br><input type="submit" name="logout" value="Logout">
    </form>
</body>
</html>
