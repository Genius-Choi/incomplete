<?php
include("../tasks/condb.php");
include("../tasks/passw.php");
if(!isset($_POST["email"]))
{
  header("location:adminlogin.html");
  exit();
}
//handle the form 
$uemail=$_POST["email"];
$upass=$_POST["password"];

// Create a prepared statement to prevent SQL injection
$stmt = mysqli_prepare($dbcon, "SELECT * FROM admin left join adminsalt on admin.admin_id=adminsalt.aid WHERE email=?");
mysqli_stmt_bind_param($stmt, "s", $uemail);
mysqli_stmt_execute($stmt);
$result = mysqli_stmt_get_result($stmt);

//check if there is a match 
if($result->num_rows>0)
{
  $rows=$result->fetch_assoc();
  $id=$rows["admin_id"];
  $pass=$rows["password"];
  $salt=$rows["salt"];
  $upass=hashPass($upass,$salt);
  //checking 
  if($upass==$pass)
  {
    session_start();
    $_SESSION["aid"]=$id;
    $_SESSION["password"]=$pass;
    $_SESSION["salt"]=$salt;
    $_SESSION["exp_time"]=time()+(10);
   header("location:home.php");
  } else {
    echo "<p style='color:red;text-align:center;font-size:20px;'> incorrect password   </p>";
   require('adminlogin.html');
  }
 
}  else {
    echo "<p style='color:red;text-align:center;font-size:20px;'> incorrect email  </p>";
   require('adminlogin.html');
}
$dbcon->close();

?>


