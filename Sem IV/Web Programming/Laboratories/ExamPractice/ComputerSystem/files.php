<?php
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

session_start();
require_once 'config.php';

if (!isset($_SESSION['user_id'])) {
    header('Location: login.php');
    exit;
}

$limit = 5;
$page = isset($_GET['page']) ? $_GET['page'] : 1;
$start = ($page - 1) * $limit;

$stmt = $pdo->prepare('SELECT * FROM Files WHERE userid = ? LIMIT ?, ?');
$stmt->bindValue(1, $_SESSION['user_id'], PDO::PARAM_INT);
$stmt->bindValue(2, $start, PDO::PARAM_INT);
$stmt->bindValue(3, $limit, PDO::PARAM_INT);
$stmt->execute();
$files = $stmt->fetchAll();

?>

<table id="files">
    <thead>
        <tr>
            <th>Id</th>
            <th>Filename</th>
            <th>Filepath</th>
            <th>Size</th>
        </tr>
    </thead>
    <tbody>
        <?php foreach ($files as $file): ?>
        <tr>
            <td><?php echo $file['id']; ?></td>
            <td class="filename"><?php echo $file['filename']; ?></td>
            <td><?php echo $file['filepath']; ?></td>
            <td><?php echo $file['size']; ?></td>
        </tr>
        <?php endforeach; ?>
    </tbody>
</table>

<button id="prev">Previous</button>
<button id="next">Next</button>
<p id="result"></p>
<p id="result_occur"><p> 

<script>
let page = <?php echo $page; ?>;
let filenameCounts = JSON.parse(localStorage.getItem('filenameCounts')) || {};

document.querySelector('#prev').addEventListener('click', () => {
    if (page > 1) {
        window.location.href = 'files.php?page=' + (page - 1);
    }
});

document.querySelector('#next').addEventListener('click', () => {
    window.location.href = 'files.php?page=' + (page + 1);
});

const filenames = Array.from(document.querySelectorAll('.filename')).map(td => td.textContent);
filenames.forEach(filename => {
    if (filename in filenameCounts) {
        filenameCounts[filename]++;
    } else {
        filenameCounts[filename] = 1;
    }
});

localStorage.setItem('filenameCounts', JSON.stringify(filenameCounts));

const mostPopularFilename = Object.keys(filenameCounts).reduce((a, b) => filenameCounts[a] > filenameCounts[b] ? a : b);

document.getElementById('result').textContent = 'Most popular filename: ' + mostPopularFilename;

document.getElementById('result_occur').textContent = 'Occurences: ' + filenameCounts[mostPopularFilename];
</script>
