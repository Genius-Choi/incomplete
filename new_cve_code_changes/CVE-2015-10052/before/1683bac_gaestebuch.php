<!doctype html>
<html>
<head>
<meta charset="utf-8">

<meta name="viewport" content="width=device-width, initial-scale=1.0" />
<title>Guestbook</title>
<link rel="stylesheet" href="css/foundation.css" />
<script src="js/vendor/modernizr.js"></script>
</head>
<body>
	<!-- Titlebar -->
	<div class="row">
		<div class="large-12 columns">
			<div class="panel">
				<h1><?php echo $title; ?></h1>
			</div>
		</div>
	</div>
	<div class="row">

		<div class="large-8 columns">
			<!-- Main Content -->
			<div class="row">
				<div>
					<?php $innercontent->display()?>
				</div>



			</div>
		</div>
		

	</div>

	<footer class="row">
	
		<script src="js/vendor/jquery.js"></script>
		<script src="js/foundation.min.js"></script>
		<script>
      		$(document).foundation();
    		</script>
	</footer>

</body>
</html>