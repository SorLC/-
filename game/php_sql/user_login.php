<?php 
$_SESSION['views']=NULL;
$severname = "localhost";
$username = "root";
$password = "";
$dbname = "game_manage";

$conn = mysqli_connect($severname, $username, $password, $dbname);

$email = $_POST['email'];
$password = $_POST['psw'];

if (!$conn) {
	die("Connection falied: ".mysqli_connect_error());
}

if (isset($_POST['submit'])) {
	$query = "select * from user where u_email = '$email' ";
	$result = mysqli_query($conn,$query);
	$num = mysqli_num_rows($result);
	if($num == 1) {
		$sql = "select * from user where u_email = '$email' and password = '$password'";
		$result2 = mysqli_query($conn,$sql);
		$num2 = mysqli_fetch_row($result2);
		if ($num2 != 0) {
			$_SESSION['views']=$email;
			echo '<script language="JavaScript">;alert("登录成功，点击跳转");location.href="../home.html";</script>;';			
		}
		else {
			echo '<script language="JavaScript">;alert("登录失败，可能是密码或者账号输入错误，请返回重试");location.href="../index.html";</script>;';
		}
	}
	else{
		echo '<script language="JavaScript">;alert("没有此账户，点击注册");location.href="../singup.html";</script>;';
	}
}
mysqli_close($conn);
?>