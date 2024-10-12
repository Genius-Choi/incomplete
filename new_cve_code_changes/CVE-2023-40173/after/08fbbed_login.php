<?php
include("../tasks/condb.php");
if(!isset($_POST["email"]))
header("location:adminlogin.html");
//handle the form 
$uemail=$_POST["email"];
$upass=$_POST["password"];

// Create a prepared statement to prevent SQL injection
$stmt = mysqli_prepare($dbcon, "SELECT * FROM admin WHERE email=? AND password=?");
mysqli_stmt_bind_param($stmt, "ss", $uemail, $upass);
mysqli_stmt_execute($stmt);
$result = mysqli_stmt_get_result($stmt);

//check if there is a match 
if($result->num_rows>0)
{
  $rows=$result->fetch_assoc();
  $id=$rows["admin_id"];
  session_start();
  $_SESSION["aid"]=$id;
  $_SESSION["password"]=$rows["password"];
 header("location:home.php");
}  else {
    echo "<p style='color:red;text-align:center;font-size:20px;'> incorrect password or email  </p>";
   require('adminlogin.html');
}
$dbcon->close();

?>


