<!-- drop in and out of the PHP context -->
<?php  
session_start();
if(!isset($_SESSION["aid"]))
{
	header("location:../adminlogin.html");
   exit();
}
//connect to the database first!!!!
require('../../tasks/condb.php');
if($_SERVER['REQUEST_METHOD'] == 'POST')
{

	// if the form has been submitted!
	$echanged=false;
	$pchanged=false;
	$gotold=false;
	$putold=false;

	//is email changed 
	if(isset($_POST['email']))
	{
	$echanged=true;
	$newemail=htmlspecialchars($_POST['email'], ENT_QUOTES, 'UTF-8');
	} 
	//is pass ^^
	if(isset($_POST['password']))
	{
	$pchanged=true;
	$newpass=htmlspecialchars($_POST['password'], ENT_QUOTES, 'UTF-8');
	} 
	if(isset($_POST['oldpass']))
	{
		$putold=true;
		$oldpass=htmlspecialchars($_POST['oldpass'], ENT_QUOTES, 'UTF-8');

	}
/*************************************************** */
// SQLi prevention through parameterization
$id = $_SESSION["aid"];
$q = "SELECT * FROM admin WHERE admin_id=?";
$stmt = mysqli_prepare($dbcon, $q);
mysqli_stmt_bind_param($stmt, "i", $id);
mysqli_stmt_execute($stmt);
$result = mysqli_stmt_get_result($stmt);
$row = $result->fetch_assoc(); 
$rpass = $row["password"];  //real

if ($pchanged && $oldpass == $rpass) {
    // change the password 
    $q = "UPDATE admin SET password=? WHERE admin_id=?";
    $stmt = mysqli_prepare($dbcon, $q);
    mysqli_stmt_bind_param($stmt, "si", $newpass, $id);
    mysqli_stmt_execute($stmt);
    echo "changed the password <br>";
}  

if ($echanged && $oldpass == $rpass) {
    $q = "UPDATE admin SET email=? WHERE admin_id=?";
    $stmt = mysqli_prepare($dbcon, $q);
    mysqli_stmt_bind_param($stmt, "si", $newemail, $id);
    mysqli_stmt_execute($stmt);
    echo "changed the email <br>";
}
/***************************************************** */
}
?> 

<html lang="en-us">

<head>
	<title> admin homepage </title>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width,intial-scale=1.0">
	<meta name="keywords"
		content="social media,the best social media platform,chat with your friend ,easy social media,pipago">
	<meta name="description" content="light weight secured student's social media!!!">
	<meta name="author" content="black eagle team">
	<link rel="stylesheet" href="setting.css">
</head>
<!-- body goes here -->

<body>
	<!--header-->
	<header>
		<!-- -navigation links-->
		<nav>

			<ul>
				<li><a href="../home.php">pipa analytics</a></li>
				<li><a href="../mg.php">manage user </a></li>
				<li><a href="add.html"> add admin </a></li>
				<li><a href="#"  style="background-color: black;">setting</a></li>
				<li><a href="logout.php">logout</a></li>
			</ul>

		</nav>

	</header>
	<!-- content-->
	<main>
    <div class="adminsetting">
    <div class="adminsetting1">
		<form action="" method="post">
		<label >email</label><br>
    <input type="email" name="email" required><br>
	<label >new password</label><br>
	<input type="password" name="password" required><br>
	<label >old password</label><br>
	<input type="password" name="oldpass" required title="old password required to save changes" ><br>
	<input type="submit" id="submitb" value="save changes">
</form>
	</div>
	</div>
    
	</main>
	<!--footer content-->
	<footer>


	</footer>
</body>

</html>
