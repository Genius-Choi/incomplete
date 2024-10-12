<?php   
session_start();
if(isset($_SESSION["id"]))
{
	header("location:user/home.php");
  exit();
}

require("tasks/condb.php");
require("tasks/passw.php");
//handle the form 
$uemail=$_POST["email"];
$upass=$_POST["password"];

//prevent sql injection 
$uemail=mysqli_real_escape_string($dbcon,$uemail);

//query on database.
$query="select * from users left join usersalt on users.id=usersalt.uid where email='$uemail'";
$result=mysqli_query($dbcon,$query);
//check if there is a match 
if($result->num_rows>0)
{
  //fetch  some data
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
  $salt=$row["salt"];

  //checking 
  $upass=hashPass($upass,$salt);
  if($upass==$pas)
  {
      //session start 
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
  $_SESSION["salt"]=$salt;
  $_SESSION["exp_time"]=time()+(10);
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
  header("location:user/home.php");
  } else {
    echo "<p style='color:red;text-align:center;font-size:20px;'> Incorrect Attempt! </p>";
    require('login.html');
  }
  
}  else {
    echo "<p style='color:red;text-align:center;font-size:20px;'> Email doesn't exist </p>";
   require('login.html');
}
$dbcon->close();
?>


