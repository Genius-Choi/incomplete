<?php
	function start_session() {
		session_start();
		$_SESSION['isopen']=true;
	}
	
	function destroy_session() {
		$_SESSION['isopen']=false;
		session_destroy();
	}
	
	function get_topics($uname) {
		$sql="SELECT * from `topics` where `uname`='$uname'";
		$res=@mysql_query($sql);
		$res=mysql_fetch_array($res);
		$ret=array();
		while(list($name, $id)=each($res)) {
			if($id==1 and !($name<='100')) {
				$topic=strtoupper($name[0]);
				for($i=1; $i<strlen($name); $i++)
					$topic=$topic.$name[$i];
				$ret[]=$topic;
			}
		}
		return $ret;
	}
	
	function get_pic($uname) {
		$res=@mysql_query("SELECT * from users where uname='$uname'");
		$res=mysql_fetch_array($res);
		$pic=0;
		if($res['userpicture'])
			return ("profile_images/$uname.jpg");
		else
			return ("images/user.jpg");
	}
	
	function display_all_replies($post_id, $curr_id, $indent, $first) {
		$sql="SELECT * from `replies` where `root`='$curr_id' and `post_id`='$post_id'";
		$res=mysql_query($sql);
		if(!mysql_num_rows($res)) {
			return;
		}
		echo "<div style='margin-left: 10*$indent'>";
		while($data=mysql_fetch_array($res)) {
			$rep_id=$data['rep_id'];
			if($curr_id==$post_id and !$first) echo "<br><hr><br><br>";
			$first=false;
			$by=$data['by'];
			$pic=get_pic($by);
			$fp=@fopen("replies/$post_id/$rep_id.txt", "r");
			$rep=@fread($fp, filesize("replies/$post_id/$rep_id.txt"));
			for($i=0; $i<$indent; $i++) echo "&nbsp;"; ?> 
            <img src='<?php echo $pic; ?>' width='20' height='20'/>
            <?php
			echo "<a href='profile.php?member=$by'>$by</a> "; echo $rep; echo "<br>";
			for($i=0; $i<$indent; $i++) echo "&nbsp;"; 
			echo "<a href='reply.php?id=$post_id&root=$rep_id'><img src='images/reply.png' width='15' height='15''/> Reply</a><br><br>";
			display_all_replies($post_id, $rep_id, $indent+10, $first);
		}
		echo "</div>";
	}
	function BlockSQLInjection($str) { 
		return str_replace(array("'","\"","'",'"'), array("&#39;","&quot;","&#39;","&quot;"), $str); 
	}
?>