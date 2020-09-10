<?php

$severname = "localhost";
$username = "root";
$password = "";
$dbname = "game_manage";

$conn = mysqli_connect($severname, $username, $password, $dbname);
$name=$_POST['name'];
$date=$_POST['bday'];
$email=$_SESSION["views"];

if (!$conn) {
	die("Connection falied: ".mysqli_connect_error());
}

if (isset($_POST['submit'])) {
	mysqli_query ($conn, "update user set nick_name='$name',u_date='$date' where u_email='$email' ");
	echo '<script language="JavaScript">;alert("修改成功，点击跳转");location.href="../user.php";</script>;';
}
mysqli_close($conn);
?>