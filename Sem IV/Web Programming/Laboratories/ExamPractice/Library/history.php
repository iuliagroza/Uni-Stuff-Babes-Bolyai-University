<?php
session_start();
if(isset($_SESSION['history'])) {
    foreach($_SESSION['history'] as $name) {
        echo $name . "<br>";
    }
}
?>
