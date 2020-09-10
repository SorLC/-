<?php
$severname = "localhost";
$username = "root";
$password = "";
$dbname = "game_manage";
$email=$_SESSION['views'];
$g_id=$_POST['g_id'];

$conn = mysqli_connect($severname, $username, $password, $dbname);

if (!$conn) {
	die("Connection falied: ".mysqli_connect_error());
}

if (isset($_POST['submit'])){
	$sql="delete from user_gets_game where g_ID='$g_id' and u_ID='$email'";
	$result=mysqli_query($conn,$sql);
	if($result){
		//echo '<script language="JavaScript">;alert("成功");location.href="../collect_game";</script>;';
		echo "<script type='text/javascript'>history.go(-1)</script>";
	}
	else{
		echo '<script language="JavaScript">;alert("失败，请重试");location.href="../collect_game";</script>;';
	}
}
//
?>