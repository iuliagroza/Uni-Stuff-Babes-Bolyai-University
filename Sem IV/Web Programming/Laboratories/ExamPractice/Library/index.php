<!DOCTYPE html>
<html>
<head>
    <title>Article & Book Search</title>
    <script type="text/javascript">
    function validateForm() {
        var name1 = document.forms["searchForm"]["name1"].value;
        var name2 = document.forms["searchForm"]["name2"].value;

        if (name1 == "" && name2 == "") {
            alert("At least one name must be filled out");
            return false;
        }
    }
    </script>
</head>
<body>
    <form name="searchForm" action="search.php" onsubmit="return validateForm()" method="post">
        <input type="text" name="name1" placeholder="First Name">
        <input type="text" name="name2" placeholder="Second Name">
        <input type="submit" value="Submit">
    </form>
    <button onclick="window.location.href='history.php'">View History</button>
</body>
</html>
