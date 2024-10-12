<?php
	require_once('includes/topic_datalist.htm');
	$uname=$_SESSION['uname'];
	$res=@mysql_query("SELECT * from users where uname='$uname'");
	$res=mysql_fetch_array($res);
	$pic=0;
	if($res['userpicture'])
		$pic="profile_images/$uname.jpg";
	else
		$pic="images/user.jpg";
?>
<div class="homelinks" align="center">
    <br>
    <a href="home.php">Home</a> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    <a href="">Notifications</a> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    <a href="profile.php"><img src="<?php echo $pic; ?>" width="20" height="20"/> Profile (<?php echo $uname; ?>)</a> 
    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    <a href="">Messages</a> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    <a href="settings.php">Settings</a> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    <a href="logout.php">Logout</a>
</div>

<div class="search">
	<form action="" method="post">
	<table>
    	<tr>
        	<td><b>Add Topics</b></td> <td> <input type="text" list="topics" name="choose"/> </td> <td> <input type="submit" value="Add" name="add"/> </td>
        </tr>
    </table>
    </form>
    <?php
		if(isset($_POST['add'])) {
			$topic=$_POST['choose'];
			$topic[0]=strtolower($topic[0]);
			@mysql_query("UPDATE topics SET $topic='1' where uname='$uname'");
		}
	?>
</div>
<br> 
<div class="content">
    <label class="trend">
        <fieldset>
            <legend align="left"><h3>Trending Topics</h3></legend>
            <a href="">Technology</a>&nbsp;&nbsp;<a href="">Gadgets</a>&nbsp;&nbsp;<a href="">Programming</a><br><br>
            <a href="">Fashion</a>&nbsp;&nbsp;<a href="">Designing</a>
        </fieldset>
    </label>
</div>