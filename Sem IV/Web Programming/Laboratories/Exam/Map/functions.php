<?php
include 'db_connection.php';
session_start();

function getAllCities() {
    global $conn;
    $query = "SELECT * FROM City";
    $result = $conn->query($query);
    return $result->fetch_all(MYSQLI_ASSOC);
}

function getCitiesLinked($cityID){
    global $conn;
    $query = "SELECT 
                C1.ID as City1ID, 
                C1.Name as City1, 
                C2.ID as City2ID, 
                C2.Name as City2, 
                L.Duration, 
                L.Distance,
                (0.6*L.Duration + 0.4*L.Distance) as Metric
            FROM 
                Link as L
            JOIN
                City as C1 on L.IDCity1 = C1.ID
            JOIN
                City as C2 on L.IDCity2 = C2.ID
            WHERE 
                L.IDCity1 = $cityID OR L.IDCity2 = $cityID
            ORDER BY 
                Metric ASC";

    $result = $conn->query($query);
    $linkedCities = $result->fetch_all(MYSQLI_ASSOC);
    foreach ($linkedCities as &$city) {
        if ($city['City1ID'] == $cityID) {
            $city['ID'] = $city['City2ID'];
            $city['Name'] = $city['City2'];
            $city['Source'] = $city['City1'];
        } else {
            $city['ID'] = $city['City1ID'];
            $city['Name'] = $city['City1'];
            $city['Source'] = $city['City2'];
        }
    }
    return $linkedCities;
}

function addCityToRoute($cityID) {
    $_SESSION['route'][] = $cityID;
}

function getRoute(){
    global $conn;
    $route = array();
    foreach($_SESSION['route'] as $cityID){
        $query = "SELECT * FROM City WHERE ID = $cityID";
        $result = $conn->query($query);
        if ($result->num_rows > 0) {
            array_push($route, $result->fetch_assoc());
        }
    }
    return $route;
}


function goBack() {
    array_pop($_SESSION['route']);
}
?>
