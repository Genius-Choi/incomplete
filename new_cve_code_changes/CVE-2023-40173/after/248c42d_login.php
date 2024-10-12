<?php

use LDAP\Result;

include("tasks/condb.php");
//handle the form 
$uemail=$_POST["email"];
$upass=$_POST["password"];

//prevent sql injection 
$uemail=mysqli_real_escape_string($dbcon,$uemail);
$upass=mysqli_real_escape_string($dbcon,$upass);

//query on database.
$query="select * from users where email='$uemail' and password='$upass'";
$result=mysqli_query($dbcon,$query);

//check if there is a match 
if($result->num_rows>0)
{
  
  
  //fetch  id to store to 
  $row=$result->fetch_assoc();
  $id=$row["id"];
  $lname=$row['lname'];
  $fname=$row["fname"];
  $bd=$row["bday"];
  $city=$row["city"];
  $gender=$row["gender"];
  $email=$row["email"];
  $pas=$row["password"];
  $edu=$row["edu"];
  $joined=$row["joined"];
  
  //session start
  session_start();
  $_SESSION['email']=$email;
  $_SESSION["id"]=$id;
  $_SESSION["fname"]=$fname;
  $_SESSION["lname"]=$lname;
  $_SESSION["bday"]=$bd;
  $_SESSION["city"]=$city;
  $_SESSION["gender"]=$gender;
  $_SESSION["password"]=$pas;
  $_SESSION["edu"]=$edu;
  $_SESSION["joined"]=$joined;
  ////////////////////////////

  //update last seen
  ////////////////////////////
  $sessionID =   session_id();
  session_write_close();

  $chandler=curl_init();
  $url=$_SERVER['SERVER_NAME']."/social-media-skeleton/tasks/updatels.php?email=$uemail";
  curl_setopt($chandler,CURLOPT_URL,$url);
  curl_setopt($chandler, CURLOPT_HTTPHEADER, array("Cookie:".'PHPSESSID=' . $sessionID));
  curl_setopt($chandler,CURLOPT_RETURNTRANSFER,false);
  curl_exec($chandler);
  curl_close($chandler);

$dbcon->close();
  header("location:user/home.php");
    exit;
}  else {
  $dbcon->close();
    echo "<p style='color:red;text-align:center;font-size:20px;'> incorrect password or email  </p>";
   require('login.html');
    exit();
}

?>


