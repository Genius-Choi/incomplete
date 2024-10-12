<!-- drop in and out of the PHP context -->
<?php  
session_start();
require("../../tasks/passw.php");
require("../../tasks/validate.php");
if(!isset($_SESSION["aid"]))
{
	header("location:../adminlogin.html");
   exit();
}

 //is expired 
 if(sexpired())
 {
    header("location:logout.php");
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
	if(isset($_POST['email']) && $_POST['email']!="")
	{
	$echanged=true;
	$newemail=htmlspecialchars($_POST['email'], ENT_QUOTES, 'UTF-8');
	$valide=validateEmail($newemail);
	} 
	//is pass ^^
	if(isset($_POST['password']) && $_POST['password']!="")
	{
	$pchanged=true;
	$newpass=$_POST['password'];
	$strongpass=validatePass($newpass);
	$newpass=hashPass($newpass,$_SESSION["salt"]);
	} 
	if(isset($_POST['oldpass']) && $_POST['oldpass']!="")
	{
		$putold=true;
		$oldpass=$_POST['oldpass'];
		$oldpass=hashPass($oldpass,$_SESSION["salt"]);
	}
/*************************************************** */
$id=$_SESSION["aid"];
$rpass = $_SESSION["password"];  //actual pass

if ($pchanged && $oldpass == $rpass && $oldpass!=$newpass && $strongpass) {
    // change the password 
    $q = "UPDATE admin SET password=? WHERE admin_id=?";
    $stmt = mysqli_prepare($dbcon, $q);
    mysqli_stmt_bind_param($stmt, "si", $newpass, $id);
    mysqli_stmt_execute($stmt);
	$_SESSION["password"]=$newpass;
    echo "changed the password <br>";
} 

if (($pchanged && $oldpass != $rpass) || ($echanged && $oldpass != $rpass)) {
    echo "incorrect attempt! <br>";
}  

if(isset($strongpass) && !$strongpass)
{
	echo "weak password!";
} else if (isset($valide) && !$valide) {
  echo "Invalid input detected, please try again!";
}

if ($echanged && $oldpass == $rpass && $valide) {
    $q = "UPDATE admin SET email=? WHERE admin_id=?";
    $stmt = mysqli_prepare($dbcon, $q);
    mysqli_stmt_bind_param($stmt, "si", $newemail, $id);
    mysqli_stmt_execute($stmt);
    echo "changed the email <br>";
}
/***************************************************** */
}
$dbcon->close();
?> 

<html lang="en-us">

<head>
	<title> admin homepage </title>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width,initial-scale=1.0">
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
				<li><a href="add.php"> add admin </a></li>
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
    <input type="email" name="email"  placeholder="unchanged"><br>
	<label >new password</label><br>
	<input type="password" name="password" placeholder="unchanged" pattern=".{8,}" title="minimum of 8 digits"><br>
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
