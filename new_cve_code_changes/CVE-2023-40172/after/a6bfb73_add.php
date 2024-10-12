
<?php
require("../../tasks/passw.php");
session_start();
if(!isset($_SESSION["aid"]))
{
	header("location:../adminlogin.html");
   exit();
}

if($_SERVER['REQUEST_METHOD'] == 'POST')
{
  $uemail=htmlspecialchars($_POST["email"], ENT_QUOTES, 'UTF-8');
  $upass=$_POST["password"];

     //check token 
     if(isset($_SESSION["c-token"]) && isset($_POST["csrf-token"]))
     {
       $tok=$_POST["csrf-token"];
       if($_SESSION["c-token"]!=$tok)
       {
         exit("action denied!");
       }
     } else {
         exit("action denied!");
     }
    
  //if empty password or username!
  //alt isempty
  if($uemail=="" || $upass=="")
  {
    header("location:add.php");
    exit();
  }
  require("../../tasks/condb.php");
  
  // Create a prepared statement to prevent SQL injection
  $query = "INSERT INTO admin (email, password) VALUES (?, ?)";
  $stmt = mysqli_prepare($dbcon, $query);
  mysqli_stmt_bind_param($stmt, "ss", $uemail, $upass);
  $result = mysqli_stmt_execute($stmt);
  
  if($result)
  {
    echo("<p style='color:green;position:absolute;left:250px;top:70px'> successfully added $uemail</p>");
    $dbcon->close();
  }  else {
  echo("some thing want wrong please try again!");
  $dbcon->close();
  }
}

//gen ctoken
$tok=$_SESSION["c-token"]=generateSalt();

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
        <link rel="stylesheet" href="../home.css">
    </head>
    <!-- body goes here -->
    
    <body>
        <!--header-->
        <header>
            <!-- -navigation links-->
            <nav>
    
                <ul>
                    <li><a href="../home.php">pipa analytics</a></li>
                    <li><a href="../mg.php" >manage user </a></li>
                    <li><a href="#" style="background-color: black;"> add admin </a></li>
                    <li><a href="setting.php">setting</a></li>
                    <li><a href="logout.php">logout</a></li>
                </ul>
    
            </nav>
    
        </header>
        <!-- content-->
        <main>
      <div class="addbox">
    <form class="adform" action="add.php" method="POST">
    <label>email</label><br>
    <input type="email" name="email" required><br>
    <label>password</label><br>
    <input type="password" name="password" required>
    <input type="text" name="csrf-token" value="<?php echo $tok; ?>" hidden>
    <input class="addbutton" type="submit" value="add">
    </form>
    
      </div>
        </main>
        <!--footer content-->
        <footer>
    
    
        </footer>
    </body>
    
    </html>