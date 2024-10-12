<!doctype html>
<html>
<head>
<meta charset="utf-8">
<title>Welcome to Funchayat</title>
<link href="css/main.css" type="text/css" rel="stylesheet"/>
<?php
	require_once("includes/db.inc");
	require_once("functions/availability.php");
	require_once("functions/main.php");
	if(isset($_COOKIE['user'])) {
		start_session();
		$_SESSION['uname']=$_COOKIE['user'];
		echo "<script>location.href='home.php'</script>";
	}
	session_start();
	if(@$_SESSION['isopen'])
		header('Location: home.php');
?>
</head>

<body>
	<?php
		include_once('includes/header.inc');
	?>
	<form class="login" action="" method="post">
 		<fieldset>
 			<table align="center">
 				<legend align="center"><h2>Login</h2></legend>
 				<tr></tr>
 				<tr>
    				<td height="0" align="center"><h4>Username:</h4></td> <td><input type="text" name="uname" required/></td>
    			</tr>
    			<tr>
    				<td height="0" align="center"><h4>Password:</h4></td> <td><input type="password" name="pwd" required/></td>
   			  </tr>
    			<tr>
    				<td colspan="3" height="0" align="center"><input type="checkbox" checked name="rem" value="yes"/><b>Remember me</b></td>
    			</tr>
   				 <tr>
    				<td colspan="3" height="50" align="center"><input type="submit" value="Login" name="login"/></td>
   				 </tr>
   				 <tr>
    				<td colspan="3" height="50" align="center"><a href="forgotpassword.php"><h4>Forgot Password?</h4></a></td>
    			</tr>
 			</table>
 			<?php
 				if(isset($_POST['login'])) {
					$u=BlockSQLInjection($_POST['uname']);
					$p=BlockSQLInjection($_POST['pwd']);
					$sql="SELECT * from users where uname='$u' and pwd='$p'";
					$res=mysql_query($sql);
					if(mysql_num_rows($res)==1) {
						start_session();
						$_SESSION['uname']=$u;
						if($_POST['rem']=="yes") {
							setcookie("user", $u, time()+86400*5, "/");
						}
						sleep(1);
						header('Location: home.php');
					}
					else
						echo '<p align="center">Username or Password do not match.</p>';
				}
 			?>
		</fieldset>
	</form>


	<h2><p align="center">OR</p></h2>


	<form class="signup" action="#register" method="post">
		<fieldset id="register">
			<table align="center">
				<legend align="center"><h2>Create an account</h2></legend>
				<tr></tr>
				<tr>
					<td height="0"><h4>Choose Username:</h4></td> <td><input type="text" name="uname" required/></td><td><input type="submit" value="Check availability" name="check"/></td>
				</tr>
				<tr>
					<td height="0"><h4>Password:</h4></td> <td><input type="password" name="pwd"/> </td>
				</tr>
				<tr>
					<td height="0"><h4>Confirm password:</h4></td> <td><input type="password" name="cpwd"/> </td>
				</tr>
				<tr>
					<td height="0"><h4>Email:</h4></td> <td><input type="email" name="email"/> </td>
				</tr>
				<tr>
					<td height="0"><h4>Date of birth:</h4></td> <td><input width="5400" type="date" name="dob"/> </td>
				</tr>
				<tr>
					<td align="center" colspan="3" height="80"> <input type="checkbox" name="tnc"/><b>I agree to the <a href="privacypolicy.php">TERMS AND CONDITIONS</a>.</b></td>
				</tr>
				<tr>
					<td align="center" colspan="3" height="50"><input type="submit" value="Sign up" name="signup"/> </td>
				</tr>
			</table>
 			
			<?php
 				if(isset($_POST['signup'])) {
				$u=$_POST['uname'];
				$p=$_POST['pwd'];
				$cp=$_POST['cpwd'];
				$e=$_POST['email'];
				$dob=$_POST['dob'];
				if($p != $cp) 
					echo '<p align="center"><b>Passwords do not match</b></p>';
				else if($p=='' || $cp=='' || $e=='' || $dob=='')
					echo'<p align="center"><b>Please fill in all the fields</b></p>';
				else if(!isset($_POST['tnc']))
					echo '<p align="center"><b>Please agree the <a href="privacypolicy.php">Terms and Conditions</a></b></p>';
				else if(!useravail($u))
					echo '<p align="center"><b>Username not available. Choose a different one.</b></p>';
				else {
					$sql="INSERT into users(uname, pwd, email, dob) values('$u', '$p', '$e', '$dob')";
					if(mysql_query($sql)) {
						echo '<p align="center"><b>Sign up successful. You can now login.</b></p>';
						mysql_query("INSERT into topics(uname) values('$u')");
					}
					else
						echo '<p align="center"><b>An error has occurred. Try again.</b></p>';
				}
			}
			else if(isset($_POST['check'])) {
				$u=$_POST['uname'];
				if(useravail($u))
					echo '<p align="center"><b>Available</b></p>';
				else 
					echo '<p align="center"><b>Not available</b></p>';;
			}
			?>
		</fieldset>
	</form>
    <?php
		require_once('includes/footer.inc');
	?>
</body>
</html>