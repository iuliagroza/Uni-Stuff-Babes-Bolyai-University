<?php
$host = 'your_host';
$db   = 'your_db';
$user = 'your_user';
$pass = 'your_pass';

$pdo = new PDO("mysql:host=$host;dbname=$db", $user, $pass);

$professorName = $_POST['professorName'] ?? '';
$courseId = $_POST['courseId'] ?? '';
$studentName = $_POST['studentName'] ?? '';
$grade = $_POST['grade'] ?? '';

if ($professorName && $courseId && $studentName && $grade) {
    $stmt = $pdo->prepare("SELECT * FROM Courses WHERE id = ? AND professorid = 
    (SELECT id FROM Persons WHERE name = ? AND role = 'professor')");
    $stmt->execute([$courseId, $professorName]);
    $course = $stmt->fetch();

    if ($course) {
        $participants = explode(',', $course['participants']);
        $grades = explode(',', $course['grades']);

        $studentId = array_search($studentName, $participants);
        if ($studentId !== false) {
            $grades[$studentId] = $grade;
        } else {
            $participants[] = $studentName;
            $grades[] = $grade;
        }

        $stmt = $pdo->prepare("UPDATE Courses SET participants = ?, grades = ? WHERE id = ?");
        $stmt->execute([implode(',', $participants), implode(',', $grades), $courseId]);
    }
}

if ($professorName && $courseId) {
    $stmt = $pdo->prepare("SELECT participants FROM Courses WHERE id = ? AND professorid = 
    (SELECT id FROM Persons WHERE name = ? AND role = 'professor')");
    $stmt->execute([$courseId, $professorName]);
    $participants = $stmt->fetchColumn();

    echo "Participants: $participants";
}

if ($professorName && $studentName) {
    $stmt = $pdo->prepare("SELECT coursename FROM Courses WHERE FIND_IN_SET((SELECT id FROM Persons WHERE name = ?), participants) 
    AND professorid = (SELECT id FROM Persons WHERE name = ? AND role = 'professor')");
    $stmt->execute([$studentName, $professorName]);
    $courses = $stmt->fetchAll(PDO::FETCH_COLUMN);

    echo "Courses for $studentName: " . implode(', ', $courses);
}
?>
<form method="post">
    Professor name: <input type="text" name="professorName"><br>
    Course ID: <input type="text" name="courseId"><br>
    Student name: <input type="text" name="studentName"><br>
    Grade: <input type="text" name="grade"><br>
    <input type="submit" value="Submit">
</form>
