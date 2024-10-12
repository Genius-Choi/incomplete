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

?>