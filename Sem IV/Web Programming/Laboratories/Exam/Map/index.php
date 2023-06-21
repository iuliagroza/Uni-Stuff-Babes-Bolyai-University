<?php
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

include 'functions.php';

if (!isset($_SESSION['route'])) {
    $_SESSION['route'] = array();
}

if (isset($_GET['cityID'])) {
    addCityToRoute($_GET['cityID']);
}

if (isset($_GET['back'])) {
    goBack();
}

if (empty($_SESSION['route'])) {
    $cities = getAllCities();
    echo "Departure:<br><br>";
    foreach ($cities as $city) {
        echo "<a href=\"?cityID={$city['ID']}\">{$city['Name']}</a><br>";
    }
} else {
    $linkedCities = getCitiesLinked(end($_SESSION['route']));
    echo "Intermediate:<br><br>";
    foreach ($linkedCities as $city) {
        echo "{$city['Source']} - <a href=\"?cityID={$city['ID']}\">{$city['Name']}</a> ({$city['Duration']} min; {$city['Distance']} km); Metric: {$city['Metric']}<br>";
    }
    echo "<br><button onclick=\"window.location.href='?finalize'\">Set final destination</button><br>";
    echo "<button onclick=\"window.location.href='?back'\">Back</button><br>";
}

if (isset($_GET['finalize'])) {
    $route = getRoute();
    echo "Your route is:<br>";
    foreach ($route as $city) {
        echo "{$city['Name']}<br>";
    }
}
?>
