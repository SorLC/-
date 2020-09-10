<?php
$severname = "localhost";
$username = "root";
$password = "";
$dbname = "game_manage";
$email=$_SESSION['views'];
$g_id=$_SESSION['g_id'];

$conn = mysqli_connect($severname, $username, $password, $dbname);

if (!$conn) {
	die("Connection falied: ".mysqli_connect_error());
}

if (isset($_POST['submit'])){
	$sql="select * from user_gets_game where u_ID='$email' and g_ID='$g_id'";
	$result=mysqli_query($conn,$sql);
	$num=mysqli_num_rows($result);
	if($num==1){
		echo '<script language="JavaScript">;alert("已经收藏过");location.href="../user.php";</script>;';
	}
	else{
		$sql="insert into user_gets_game values('$email','$g_id')";
		if(mysqli_query($conn,$sql))
		{
			//echo '<script language="JavaScript">;alert("收藏成功");location.href="../collect_game";</script>;';
			echo "<script type='text/javascript'>history.go(-1)</script>";
		}
		else{
			echo '<script language="JavaScript">;alert("收藏失败");location.href="../user.php";</script>;';
		}
	}
	//
	
}
?>