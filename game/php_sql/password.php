<?php
$severname = "localhost";
$username = "root";
$password = "";
$dbname = "game_manage";

$conn = mysqli_connect($severname, $username, $password, $dbname);

$old_pas=$_POST['pas'];
$password = $_POST['new_pas'];
$repassword = $_POST['new_pas2'];
$email=$_SESSION["views"];

if (!$conn) {
	die("Connection falied: ".mysqli_connect_error());
}

if (isset($_POST['submit'])) {

    $query = "select * from user where u_email = '$email' and password='$old_pas' ";
	$result = mysqli_query($conn,$query);
	$num = mysqli_num_rows($result);
	if ($num == 0) {
		echo '<script language="JavaScript">;alert("旧密码错误")；location.href="../alter_pas.html";</script>;';
	}
	else {
		if ($password != $repassword) {
			echo '<script language="JavaScript">;alert("两次密码不一致");location.href="../alter_pas.html";</script>;';
		}
		else {
			$sql = "update user set password='$password' where u_email='$email' ";
			if (mysqli_query($conn,$sql))
			{
				echo '<script language="JavaScript">;alert("修改成功，点击跳转");location.href="../user.php";</script>;';
			}
			else
			{
				echo '<script language="JavaScript">;alert("修改失败，请重试");location.href="../alter_pas.html";</script>;';
			}
		}
	}
}
mysqli_close($conn);
?>