<?php

$severname = "localhost";
$username = "root";
$password = "";
$dbname = "game_manage";

$conn = mysqli_connect($severname, $username, $password, $dbname);

$email = $_POST['email'];
$password = $_POST['pas'];
$repassword = $_POST['re_pas'];
$name=$_POST['name'];

if (!$conn) {
	die("Connection falied: ".mysqli_connect_error());
}

if (isset($_POST['submit'])) {
	$query = "select * from user where u_email='$email' ";
	$result = mysqli_query($conn,$query);
	$num = mysqli_num_rows($result);
	if ($num == 1) {
		echo '<script language="JavaScript">;alert("该邮箱已被注册\nUsed email");location.href="../singup.html";</script>;';
	}
	else {
		if ($password != $repassword) {
			echo '<script language="JavaScript">;alert("两次密码不一致");location.href="../singup.html";</script>;';
		}
		else {
			$sql = "INSERT INTO user (u_email,password,nick_name) VALUES ('$email','$password','$name')";
			if (mysqli_query($conn,$sql))
			{
				echo '<script language="JavaScript">;alert("注册成功，点击跳转");location.href="../index.html";</script>;';
			}
			else
			{
				echo '<script language="JavaScript">;alert("注册失败，请重试");location.href="../singup.html";</script>;';
			}
		}
	}
}
mysqli_close($conn);
?>