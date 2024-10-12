<?php
require("../tasks/condb.php");
require("../tasks/passw.php");
require("../tasks/validate.php");
session_start();
if (!isset($_SESSION["id"])) {
  header("location:../login.html");
  exit();
}

//is expired 
if(sexpired())
{
   header("location:logout.php");
   exit();
}


if (isset($_POST["ch-info"])) {
  $fname = htmlspecialchars($_POST["fname"], ENT_QUOTES, "UTF-8");
  $lname = htmlspecialchars($_POST["lname"], ENT_QUOTES, "UTF-8");
  $email = htmlspecialchars($_POST["email"], ENT_QUOTES, "UTF-8");
  $city = htmlspecialchars($_POST["city"], ENT_QUOTES, "UTF-8");
  $id = $_SESSION["id"];

  //validate
  if (!validateUserInfo($email, $fname, $lname, $city)) {
    echo "Invalid input detected please fill the form correctly";
    require("setting.html");
    $fn = $_SESSION["fname"];
    $ln = $_SESSION["lname"];
    $email = $_SESSION["email"];
    $city = $_SESSION["city"];
    echo "<script> fill('$fn','$ln','$email','$city')</script>";
    $tok = $_SESSION["c-token"] = generateSalt();
    echo "<script>setToken('$tok')</script>";
    exit();
  }

  //check token 
  if (isset($_SESSION["c-token"]) && isset($_POST["csrf-token"])) {
    $tok = $_POST["csrf-token"];
    if ($_SESSION["c-token"] != $tok) {
      exit("action denied!");
    }
  } else {
    exit("action denied!");
  }


  $query = "update users set fname=?,lname=?,email=?,city=? where id=?";
  $st = $dbcon->prepare($query);
  $st->bind_param("sssss", $fname, $lname, $email, $city, $id);
  $st->execute();
  $_SESSION["fname"] = $fname;
  $_SESSION["lname"] = $lname;
  $_SESSION["email"] = $email;
  $_SESSION["city "] = $city;
  echo "your info changed!";
}



if (isset($_POST["ch-pass"])) {
  $strong_pass=validatePass($_POST["newpass"]);
  $cpass = hashPass($_POST["cpass"], $_SESSION["salt"]);
  $newpass = hashPass($_POST["newpass"], $_SESSION["salt"]);
  $oldpass = hashPass($_POST["oldpass"], $_SESSION["salt"]);
  if ($oldpass == $_SESSION["password"] && $newpass == $cpass && $oldpass != $newpass && $strong_pass) {
    //hange 
    $id = $_SESSION["id"];
    $query = "update users set password=? where id=$id";
    $st = $dbcon->prepare($query);
    $st->bind_param("s", $newpass);
    $st->execute();
    $_SESSION["password"] = $newpass;
    echo "password changed successfully!";
  } else {
    echo "something want wrong. please don't forget to insert minimum 8 character!";
  }
}

require("setting.html");
$fn = $_SESSION["fname"];
$ln = $_SESSION["lname"];
$email = $_SESSION["email"];
$city = $_SESSION["city"];
echo "<script> fill('$fn','$ln','$email','$city')</script>";
$tok = $_SESSION["c-token"] = generateSalt();
echo "<script>setToken('$tok')</script>";
$dbcon->close();

?>