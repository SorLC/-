<!DOCTYPE html>
<html lang="en">

<head>	
    <meta charset="UTF-8">
    <meta name="description" content="">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">
    <!-- The above 4 meta tags *must* come first in the head; any other head content must come *after* these tags -->   
    <metahttp-equiv="Content-Type"content="image/gif"> 
	<!-- Title -->
    <title></title>

    <!-- Favicon -->
    <link rel="icon" href="img/core-img/favicon.ico">

    <!-- Stylesheet -->
    <link rel="stylesheet" href="style.css">

</head>

<body>
    <!-- Preloader -->
    <div class="preloader d-flex align-items-center justify-content-center">
        <div class="spinner">
            <div class="bounce1"></div>
            <div class="bounce2"></div>
            <div class="bounce3"></div>
        </div>
    </div>

    <!-- ##### Header Area Start ##### -->
    <header class="header-area">
        <!-- Top Header Area -->
        <div class="top-header-area">
            <div class="container h-100">
                <div class="row h-100 align-items-center">
                    <div class="col-12 d-flex align-items-center justify-content-between">
                        <!-- Logo Area -->
                        <div class="logo">
                            <a href="home.html"><img src="img/core-img/logo.png" alt=""></a>
                        </div>

                        <!-- Search & Login Area -->
                        <div class="search-login-area d-flex align-items-center">
                            <!-- Top Search Area -->
                            <div class="top-search-area">
                                <form action="kind_review.php" method="get">
                                    <input type="search" name="game_name" id="topSearch" placeholder="Search">
                                    <button type="submit" class="btn"><i class="fa fa-search"></i></button>
                                </form>
                            </div>                           
                        </div>
                    </div>
                </div>
            </div>
        </div>

        <!-- Navbar Area -->
        <div class="egames-main-menu" id="sticker">
            <div class="classy-nav-container breakpoint-off">
                <div class="container">
                    <!-- Menu -->
                    <nav class="classy-navbar justify-content-between" id="egamesNav">

                        <!-- Navbar Toggler -->
                        <div class="classy-navbar-toggler">
                            <span class="navbarToggler"><span></span><span></span><span></span></span>
                        </div>

                        <!-- Menu -->
                        <div class="classy-menu">

                            <!-- Close Button -->
                            <div class="classycloseIcon">
                                <div class="cross-wrap"><span class="top"></span><span class="bottom"></span></div>
                            </div>

                            <!-- Nav Start -->
                            <div class="classynav">
                                <ul>
                                    <li><a href="home.html">主页</a></li>
                                    <li><a href="game-review.html">游戏</a>
                                    </li>
                                    <li><a href="#">分类</a>
                                        <ul class="dropdown">
                                            <li><a href="action_game.html">动作</a></li>
                                            <li><a href="adventure_game.html">冒险</a></li>
                                            <li><a href="role_playing_game.html">角色扮演</a></li>
                                            <li><a href="Leisure_game.html">休闲</a></li>
                                            <li><a href="Strategy_game.html">策略</a></li>
                                            <li><a href="physical_game.html">体育</a></li>
                                        </ul>
                                    </li>
                                    <li><a href="user.php">用户</a></li>
                                </ul>
                            </div>
                            <!-- Nav End -->
                        </div>

                        <!-- Top Social Info -->
                        <div class="top-social-info">
                            <a href="#" data-toggle="tooltip" data-placement="top" title="Pinterest"><i class="fa fa-pinterest" aria-hidden="true"></i></a>
                            <a href="#" data-toggle="tooltip" data-placement="top" title="Facebook"><i class="fa fa-facebook" aria-hidden="true"></i></a>
                            <a href="#" data-toggle="tooltip" data-placement="top" title="Twitter"><i class="fa fa-twitter" aria-hidden="true"></i></a>
                            <a href="#" data-toggle="tooltip" data-placement="top" title="Dribbble"><i class="fa fa-dribbble" aria-hidden="true"></i></a>
                            <a href="#" data-toggle="tooltip" data-placement="top" title="Behance"><i class="fa fa-behance" aria-hidden="true"></i></a>
                            <a href="#" data-toggle="tooltip" data-placement="top" title="Linkedin"><i class="fa fa-linkedin" aria-hidden="true"></i></a>
                        </div>
                    </nav>
                </div>
            </div>
        </div>
    </header>
    <!-- ##### Header Area End ##### -->

    <!-- ##### Breadcrumb Area Start ##### -->
    <section class="breadcrumb-area bg-img bg-overlay" style="background-image: url(img/bg-img/23.jpg);">
        <div class="container h-100">
            <div class="row h-100 align-items-center">
                <!-- Breadcrumb Text -->
                <div class="col-12">
                    <div class="breadcrumb-text">
                        <h2>详细信息</h2>
                    </div>
                </div>
            </div>
        </div>
    </section>
    <!-- ##### Breadcrumb Area End ##### -->

    <!-- ##### Post Details Area Start ##### -->
    <section class="post-news-area section-padding-0-100">
        <div class="container">
            <div class="row justify-content-center">
                <!-- Post Details Content Area -->
                <div class="col-12 col-lg-8">
                    <div class="mt-100">
                        <div class="post-details-content mb-100">                         
								<?php
								function comment($email,$date,$detail){
								echo   '<li class="single_comment_area">';                                    
								    echo    '<div class="comment-content d-flex">';                                      
								        echo     '<div class="comment-author">';
								        echo     '<img src="img/bg-img/32.jpg" alt="author">';
								        echo     '</div>';                                        
								        echo     '<div class="comment-meta">';
								        echo     '<a href="#" class="post-author">'.$email.'</a>';
								        echo     '<a href="#" class="post-date">'.$date.'</a>';
								        echo     '<p>'. $detail.'</p>';            
								        echo    '</div>';
								     echo   '</div>';                                   
								echo   '</li>';	
								}
								function gamekind($g_id,$conn)
								{
									$sql="select * from game_belong_kind where g_ID='$g_id'";
									$result=mysqli_query($conn,$sql);
									$array=array();
									$i=0;
									while($row= mysqli_fetch_array($result)){
										$array[$i]["k_ID"]=$row["k_ID"];
										$i++;
									}
									$j=0;
									while($j<$i){
										$k_id=$array[$j]["k_ID"];
										$sql="select * from game_kind where k_ID='$k_id'";
										$result2=mysqli_query($conn,$sql);
										$row=mysqli_fetch_array($result2);
										echo '<a href="#" class="post-comments">'.$row["k_name"].'</a>';
										$j++;
									}
								 }
								 function publisher($g_id,$conn)
								 {
								 	$sql="select * from publish_game where g_ID='$g_id'";
								 	$result=mysqli_query($conn,$sql);
								 	$array=array();
								 	while($row= mysqli_fetch_array($result)){
								 		$array["p_ID"]=$row["p_ID"];
								 	}
								 	$p_id=$array["p_ID"];
								 	$sql="select * from publisher where p_ID='$p_id'";
								 	if($result2=mysqli_query($conn,$sql)){
								 		$row=mysqli_fetch_array($result2);
										$p_name=$row["p_name"];
								 		echo '<a href="publisher.html?p_name='.$p_name.'" class="post-comments">'.$p_name.'</a>';
								 	}	
								 }
								$severname = "localhost";
								$username = "root";
								$password = "";
								$dbname = "game_manage";
								
								$name=$_GET['game_name'];   
															
								$conn = mysqli_connect($severname, $username, $password, $dbname);
								             					
								if (!$conn) {
								die("Connection falied: ".mysqli_connect_error());
								}
								$query = "select * from game where g_name = '$name' ";
								
								$result = mysqli_query($conn,$query);
								$num = mysqli_num_rows($result);	
								$array=array();
								while($row=mysqli_fetch_array($result)){
								$array["g_ID"]=$row["g_ID"];	
								$array["g_name"]=$row["g_name"];
								$array["g_date"]=$row["g_date"];
								$array["g_recom"]=$row["g_recom"];
								$array["g_price"]=$row["g_price"];
								$array["g_intro"]=$row["g_intro"];
								$array["g_cover"]=$row["g_cover"];
								$array["g_download"]=$row["g_download"];
								}
								$_SESSION['g_id']=$array["g_ID"];
								$g_id=$_SESSION['g_id'];
								$cover=$array["g_cover"];
								echo '<div class="blog-thumbnail mb-50">';								
								echo '<img src='."$cover".'>';
								echo '</div>';
								echo '<div class="blog-content">';
								echo '<h1 class="post-title">'.$array["g_name"].'</h1>';
								echo '<div class="post-meta mb-30">';								
								echo '发行日期:'.'&nbsp&nbsp'.'<a href="#" class="post-date">'.$array["g_date"].'</a>';
								echo '推荐率:'.'&nbsp&nbsp'.'<a href="#" class="post-author">'.$array["g_recom"].'</a>';
								echo '价格:'.'&nbsp&nbsp'.'<a href="#" class="post-comments">'.$array["g_price"].'</a>';
								echo '<br>'.'标签：'.'&nbsp&nbsp';
								gamekind($g_id,$conn);
								echo '<br>'.'发行商:'.'&nbsp&nbsp';
								publisher($g_id,$conn);
								echo '</div>';
								echo '<p>'.$array["g_intro"].'</p>';
								echo '<div class="comment-meta">';
                                echo '下载地址:'.'&nbsp&nbsp'.'<p>'.$array["g_download"].'</p>';
								echo '</div>';
					   echo'</div>';
					echo '</div>';
					echo '<div class="contact-form-area mb-100">';						   	 
								           $u_id=$_SESSION['views'];
								           $sql="select * from user_gets_game where u_ID='$u_id' and g_ID='$g_id' ";
										   $result = mysqli_query($conn,$sql);
										   $num = mysqli_num_rows($result);
								    if($num==0){
								echo   '<form action="php_sql/collection.php" method="post">';
								    echo  '<div class="row">';
										echo   '<div class="col-12">';
										echo   '<button class="btn egames-btn w-50" type="submit" name="submit">收藏</button>';
										echo   '</div>';
									echo	'</div>';
								echo '</form>';			
									}
						   			else{
								echo   '<form action="php_sql/un_collect.php" method="post">';
									echo  '<div class="row">';
										echo   '<div class="col-12">';
										echo   '<input type="hidden" value="'.$g_id.'" name="g_id">'; 
										echo   '<button class="btn egames-btn w-50" type="submit" name="submit">取消收藏</button>';
										echo   '</div>';
									echo	'</div>';
								echo '</form>';		
									}
					echo   '</div>';
					echo '<div class="comment_area clearfix mb-70">';
						echo '<h4 class="mb-50">评论</h4>';
						   
						echo '<ol>';						     			
						     $sql="SELECT * 
                                   from comment
                                   where cm_ID in(SELECT cm_ID from game_comment where g_id='$g_id')";
						     $result=mysqli_query($conn,$sql);
						     if(mysqli_query($conn,$sql)){
						     $array=array();
						     $i=0;
						     while($row= mysqli_fetch_array($result)){
						     	$array[$i]["u_email"]=$row["u_email"];
						     	$array[$i]["cm_time"]=$row["cm_time"];
						     	$array[$i]["cm_detail"]=$row["cm_detail"];
						     	comment($array[$i]["u_email"],$array[$i]["cm_time"],$array[$i]["cm_detail"]);
						     	$i++;
						     }	
						     }
						echo '</ol>';
					echo '</div>';	  
								?>                             

                        <div class="post-a-comment-area mb-30 clearfix" id="reply">
                            <h4 class="mb-50">发布评论</h4>

                            <!-- Reply Form -->
                            <div class="contact-form-area">
                                <form action="php_sql/comment.php" method="post">
                                    <div class="row">
                                        <div class="col-12">
                                            <input typy="text" name="message" class="form-control"  cols="30" rows="10" autocomplete="off" placeholder="评论内容"></input>
                                        </div>
                                        <div class="col-12">
                                            <button class="btn egames-btn w-100" type="submit" name="submit">发布评论</button>
                                        </div>
                                    </div>
                                </form>
                            </div>
                        </div>
                    </div>
                </div>

                <!-- Sidebar Widget -->
                <div class="col-12 col-sm-9 col-md-6 col-lg-4">
                    <div class="sidebar-area mt-100">

                        <!-- Single Widget Area -->
                        <div class="single-widget-area add-widget">
                            <a href="#"><img src="img/bg-img/add.png" alt=""></a>
                            <!-- Side Img -->
                            <img src="img/bg-img/side-img.png" class="side-img" alt="">
                        </div>

                        <!-- Single Widget Area -->
                        <div class="single-widget-area video-widget">
                            <!-- Single Video Widget -->
                            <div class="single-video-widget d-flex">
                                <div class="video-thumbnail">
                                    <img src="img/bg-img/14.jpg" alt="">
                                </div>
                                <div class="video-text">
                                    <a href="#" class="video-title">Assemble Your Squad and Join the Battle</a>
                                    <span>Nintendo Wii, PS4, XBox 360</span>
                                </div>
                                <div class="video-rating">8.3/10</div>
                            </div>

                            <!-- Single Video Widget -->
                            <div class="single-video-widget d-flex">
                                <div class="video-thumbnail">
                                    <img src="img/bg-img/15.jpg" alt="">
                                </div>
                                <div class="video-text">
                                    <a href="#" class="video-title">Tips to improve your game</a>
                                    <span>Nintendo Wii, PS4, XBox 360</span>
                                </div>
                                <div class="video-rating">8.3/10</div>
                            </div>

                            <!-- Single Video Widget -->
                            <div class="single-video-widget d-flex">
                                <div class="video-thumbnail">
                                    <img src="img/bg-img/16.jpg" alt="">
                                </div>
                                <div class="video-text">
                                    <a href="#" class="video-title">Game reviews: the best of 2018</a>
                                    <span>Nintendo Wii, PS4, XBox 360</span>
                                </div>
                                <div class="video-rating">8.3/10</div>
                            </div>

                            <!-- Single Video Widget -->
                            <div class="single-video-widget d-flex">
                                <div class="video-thumbnail">
                                    <img src="img/bg-img/17.jpg" alt="">
                                </div>
                                <div class="video-text">
                                    <a href="#" class="video-title">Assemble Your Squad and Join the Battle</a>
                                    <span>Nintendo Wii, PS4, XBox 360</span>
                                </div>
                                <div class="video-rating">8.3/10</div>
                            </div>

                            <!-- Single Video Widget -->
                            <div class="single-video-widget d-flex">
                                <div class="video-thumbnail">
                                    <img src="img/bg-img/18.jpg" alt="">
                                </div>
                                <div class="video-text">
                                    <a href="#" class="video-title">New to gaming? Here are some tips</a>
                                    <span>Nintendo Wii, PS4, XBox 360</span>
                                </div>
                                <div class="video-rating">8.3/10</div>
                            </div>
                        </div>

                        <!-- Single Widget Area -->                       

                    </div>
                </div>
            </div>
        </div>
    </section>
    <!-- ##### Post Details Area End ##### -->

    <!-- ##### Footer Area Start ##### -->
    <footer class="footer-area">
        <!-- Main Footer Area -->
        <div class="main-footer-area section-padding-100-0">
            <div class="container">
                <div class="row">
                    <!-- Single Footer Widget -->
                    <div class="col-12 col-sm-6 col-lg-3">
                        <div class="single-footer-widget mb-70">
                            <div class="widget-title">
                                <a href="index.html"><img src="img/core-img/logo2.png" alt=""></a>
                            </div>
                            <div class="widget-content">
                                <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit. Mauris velit arcu, scelerisque dignissim massa quis, mattis facilisis erat. Aliquam erat volutpat. Sed efficitur diam ut interdum ultricies.</p>
                            </div>
                        </div>
                    </div>

                    <!-- Single Footer Widget -->
                    <div class="col-12 col-sm-6 col-lg-3">
                        <div class="single-footer-widget mb-70">
                            <div class="widget-title">
                                <h4>Game Reviews</h4>
                            </div>
                            <div class="widget-content">
                                <nav>
                                    <ul>
                                        <li><a href="#">Doom</a></li>
                                        <li><a href="#">Grand Theft Auto</a></li>
                                        <li><a href="#">Bloodborne</a></li>
                                        <li><a href="#">God of war</a></li>
                                        <li><a href="#">Persona 5</a></li>
                                    </ul>
                                </nav>
                            </div>
                        </div>
                    </div>

                    <!-- Single Footer Widget -->
                    <div class="col-12 col-sm-6 col-lg-3">
                        <div class="single-footer-widget mb-70">
                            <div class="widget-title">
                                <h4>Usefull Links</h4>
                            </div>
                            <div class="widget-content">
                                <nav>
                                    <ul>
                                        <li><a href="#">Testimanials</a></li>
                                        <li><a href="#">Reviews</a></li>
                                        <li><a href="#">New Games</a></li>
                                        <li><a href="#">Forum</a></li>
                                        <li><a href="#">Contact</a></li>
                                    </ul>
                                </nav>
                            </div>
                        </div>
                    </div>

                    <!-- Single Footer Widget -->
                    <div class="col-12 col-sm-6 col-lg-3">
                        <div class="single-footer-widget mb-70">
                            <div class="widget-title">
                                <h4>What’s new</h4>
                            </div>
                            <div class="widget-content">
                                <nav>
                                    <ul>
                                        <li><a href="#">Doom</a></li>
                                        <li><a href="#">Grand Theft Auto</a></li>
                                        <li><a href="#">Bloodborne</a></li>
                                        <li><a href="#">God of war</a></li>
                                        <li><a href="#">Persona 5</a></li>
                                    </ul>
                                </nav>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>

        <!-- Copywrite Area -->
        <div class="copywrite-content">
            <div class="container h-100">
                <div class="row h-100 align-items-center">
                    <div class="col-12 col-sm-5">
                        <!-- Copywrite Text -->
                        <p class="copywrite-text"><a href="#">
Copyright &copy; 2018.Company name All rights reserved.<a target="_blank" href="http://sc.chinaz.com/moban/">&#x7F51;&#x9875;&#x6A21;&#x677F;</a>

</p>
                    </div>
                    <div class="col-12 col-sm-7">
                        <!-- Footer Nav -->
                        <div class="footer-nav">
                            <ul>
                                <li><a href="index.html">Home</a></li>
                                <li><a href="game-review.html">Games</a></li>
                                <li><a href="post.html">Articles</a></li>
                                <li><a href="single-game-review.html">Reviews</a></li>
                                <li><a href="contact.html">Contact</a></li>
                            </ul>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </footer>
    <!-- ##### Footer Area End ##### -->

    <!-- ##### All Javascript Script ##### -->
    <!-- jQuery-2.2.4 js -->
    <script src="js/jquery/jquery-2.2.4.min.js"></script>
    <!-- Popper js -->
    <script src="js/bootstrap/popper.min.js"></script>
    <!-- Bootstrap js -->
    <script src="js/bootstrap/bootstrap.min.js"></script>
    <!-- All Plugins js -->
    <script src="js/plugins/plugins.js"></script>
    <!-- Active js -->
    <script src="js/active.js"></script>
</body>

</html>