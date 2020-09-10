<?php
$severname = "localhost";
$username = "root";
$password = "";
$dbname = "game_manage";
$g_id=$_SESSION['g_id'];
$email=$_SESSION['views'];
$detail=$_POST['message'];
$time=date("Y-m-d");
$conn = mysqli_connect($severname, $username, $password, $dbname);

if (!$conn) {
	die("Connection falied: ".mysqli_connect_error());
}

if (isset($_POST['submit'])){
	$sql="select count(*) from comment";
	$result1=mysqli_query($conn,$sql);
	$row= mysqli_fetch_array($result1);
    $cm_id=$row['count(*)'];
	$cm_id=$cm_id+1;
	$sql="insert into comment values ('$cm_id','$detail','$time','$email')";
	$result=mysqli_query($conn,$sql);
	$sql="insert into user_comment values ('$email','$cm_id')";
	$result2=mysqli_query($conn,$sql);
	$sql="insert into game_comment values ('$g_id','$cm_id')";
	$result3=mysqli_query($conn,$sql);
	if($result && $result2 && $result3){
		//echo '<script language="JavaScript">;alert("发布成功");location.href="../user.php";</script>;';
		echo "<script type='text/javascript'>history.go(-1)</script>";
	}
	else{
		echo '<script language="JavaScript">;alert("失败，请重试");location.href="../user.php"</script>;';
	}
}
//
//
?>
