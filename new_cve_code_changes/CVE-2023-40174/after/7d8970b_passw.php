<?php

//generate salt 
function generateSalt()
{
  $randb=random_bytes(16);
  return bin2hex($randb);
}

//hash password 
function hashPass($plain,$salt)
{
    $password=$plain.$salt;
    return hash("sha256",$password);
}

//check se exp 
function sexpired()
{
  if(isset($_SESSION["exp_time"]) && $_SESSION["exp_time"]<time())
   return true; 
   else 
   return false;
}

?>