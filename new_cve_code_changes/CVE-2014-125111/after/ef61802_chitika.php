<?php
define('WP_USE_THEMES', false);
require('../../../../../../wp-blog-header.php');
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
	<head>
		<link type="text/css" rel="stylesheet" href="http://ajax.googleapis.com/ajax/libs/jqueryui/1.8.7/themes/smoothness/jquery-ui.css" />
		<link rel="stylesheet" type="text/css" href="<?php echo WP_INSERT_URL; ?>/includes/common/css/style.css?version=<?php echo WP_INSERT_VERSION; ?>" />
		<script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/1.8.3/jquery.min.js"></script>
		<script type="text/javascript" src="http://ajax.googleapis.com/ajax/libs/jqueryui/1/jquery-ui.min.js"></script>
		<script type="text/javascript" src="<?php echo WP_INSERT_URL; ?>/includes/common/js/jquery-jvert-tabs-1.1.4.js?version=<?php echo WP_INSERT_VERSION; ?>"></script>
		<script type="text/javascript" src="<?php echo WP_INSERT_URL; ?>/includes/common/js/jquery.miniColors.js?version=<?php echo WP_INSERT_VERSION; ?>"></script>
		<script type="text/javascript">		
			jQuery(document).ready( function(jQuery) {
				jQuery("#chitikaVtabs").jVertTabs({equalHeights: false});
				jQuery('.minicolors').each( function() {
					jQuery(this).minicolors({letterCase: 'uppercase', swatchPosition: 'right', theme: 'bootstrap', position: jQuery(this).attr('data-position') || 'default',});
				});
			});
			function submit_popup() {
				var adCode = '<script type="text/javascript">\n';
				adCode += 'ch_client = "'+jQuery("#chitikaUserName").val()+'";\n';
				adCode += 'ch_width = '+jQuery("#chitikaAdFormat").children("option").filter(":selected").attr("data-width")+';\n';
				adCode += 'ch_height = '+jQuery("#chitikaAdFormat").children("option").filter(":selected").attr("data-height")+';\n';
				adCode += 'ch_type = "'+jQuery("#chitikaAdType").children("option").filter(":selected").val()+'";\n';
				adCode += 'ch_sid = "'+jQuery("#chitikaAdChannel").val()+'";\n';
				adCode += 'ch_color_site_link = "'+jQuery("#chitikaLinkColor").val()+'";\n';
				adCode += 'ch_color_title = "'+jQuery("#chitikaLinkColor").val()+'";\n';
				adCode += 'ch_color_border = "'+jQuery("#chitikaBorderColor").val()+'";\n';
				adCode += 'ch_color_text = "'+jQuery("#chitikaTextColor").val()+'";\n';
				adCode += 'ch_color_bg = "'+jQuery("#chitikaBackgroundColor").val()+'";\n';
				adCode += '</'+'script>\n';
				adCode += '<script src="http://scripts.chitika.net/eminimalls/amm.js" type="text/javascript"></'+'script>';
				parent.jQuery('#<?php echo wp_kses((string)$_GET['target'], ''); ?>').val(adCode);
				parent.jQuery.colorbox.close();
			}
			function validateUsername(sender) {
				if(sender.value != '') {
					jQuery("#submitButton").css("display", "inline");
				} else {
					jQuery("#submitButton").css("display", "none");
				}
			}
		</script>
		<style type="text/css">
		body {
			color: #333333;
			font-family: sans-serif;
			font-size: 12px;
			line-height: 1.4em;
		}
		#chitikaVtabs p {
			margin: 5px 0 7px !important;
		}
		a {
			color: #21759B;
		}
		a:hover {
			color: #D54E21;
		}
		label {
			line-height:	16.8px;
			vertical-align:	middle;
			cursor:	pointer;
		}
		select, input[type="text"] {
			width: 100%;
			-moz-box-sizing: border-box;
			outline: 0 none;
			border-radius: 3px 3px 3px 3px;
			border: 1px solid #AAAAAA;
			border-spacing: 0;
			clear: both;
			margin: 0;
			padding: 3px;
			box-shadow: 1px 1px 2px rgba(0, 0, 0, 0.1);
		}
		</style>
	</head>
	<body bgcolor="">
		<a href="https://chitika.com/publishers/apply.php?refid=smartlogix"><img src="<?php echo WP_INSERT_URL; ?>/includes/common/images/chitika_banner.png" style="width: 100%;" /></a>
		<div id="chitikaVtabs" style="height: 288px; overflow: hidden;">
			<div>
				<ul>
					<li><a href="#chitikaVtabUsername">Username</a></li>
					<li><a href="#chitikaVtabColors">Colors</a></li>
					<li><a href="#chitikaVtabUnitOptions">Unit Options</a></li>					
					<li><a href="#chitikaVtabChannel">Channel</a></li>
				</ul>
			</div>
			<div>
				<div id="#chitikaVtabUsername" style="min-height: 263px;">
					<p>
						<label>Username</label>
						<input id="chitikaUserName" type="text" class="input widefat" onchange="validateUsername(this)" onkeyup="validateUsername(this)" />
						<small>It is essential that you enter the correct the username for your ads. Entering an incorrect username means you will lose any stats recorded to the changed username.</small>
					</p>
					<p>
						<strong>Dont have a Chitika Account? <a href="https://chitika.com/publishers/apply.php?refid=smartlogix">Click Here</a> to open an Account.</strong>
					</p>
				</div>
				<div id="#chitikaVtabColors" style="min-height: 263px;">
					<p>
						<label>Link</label>
						<input id="chitikaLinkColor" type="text" class="input widefat minicolors" value="#0000CC" />
						<small>Use this field to specify the color of links in your ad.</small>
					</p>
					<p>
						<label>Text</label>
						<input id="chitikaTextColor" type="text" class="input widefat minicolors" value="#000000" />
						<small>Use this field to specify the color of the text under your ad link.</small>
					</p>
					<p>
						<label>Background</label>
						<input id="chitikaBackgroundColor" type="text" class="input widefat minicolors" data-position="top" value="#FFFFFF" />
						<small>Use this field to specify the color you prefer for the background of your ad.</small>
					</p>
					<p>
						<label>Border</label>
						<input id="chitikaBorderColor" type="text" class="input widefat minicolors" data-position="top" value="#FFFFFF" />
						<small>Use this field to specify the color of your ad's border.</small>
					</p>
				</div>
				<div id="#chitikaVtabUnitOptions" style="min-height: 263px;">
					<p>
						<label>Format</label>
						<select id="chitikaAdFormat"> 
							<option value="550x250" data-width="550" data-height="250">550 x 250 MEGA-Unit</option>
							<option value="500x250" data-width="500" data-height="250">500 x 250 MEGA-Unit</option>
							<option value="728x90" data-width="728" data-height="90">728 x 90 Leaderboard</option>
							<option value="120x600" data-width="120" data-height="600">120 x 600 Skyscraper</option>
							<option value="160x600" data-width="160" data-height="600">160 x 600 Wide Skyscraper</option>
							<option value="468x250" data-width="468" data-height="250">468 x 250 *New!* MEGA-Unit Jr.</option>
							<option value="468x180" data-width="468" data-height="180">468 x 180 Blog Banner</option>
							<option value="468x120" data-width="468" data-height="120">468 x 120 Blog Banner</option>
							<option value="468x90" data-width="468" data-height="90">468 x 90 Small Blog Banner</option>
							<option value="468x60" data-width="468" data-height="60">468 x 60 Mini Blog Banner</option>
							<option value="550x120" data-width="550" data-height="120">550 x 120 Content Banner</option>
							<option value="550x90" data-width="550" data-height="90">550 x 90 Content Banner</option>
							<option value="450x90" data-width="450" data-height="90">450 x 90 Small Content Banner</option>
							<option value="430x90" data-width="430" data-height="90">430 x 90 Small Content Banner</option>
							<option value="400x90" data-width="400" data-height="90">400 x 90 Small Content Banner</option>
							<option value="300x250" data-width="300" data-height="250">300 x 250 Rectangle</option>
							<option value="300x150" data-width="300" data-height="150">300 x 150 Rectangle, Wide</option>
							<option value="300x125" data-width="300" data-height="125">300 x 125 Mini Rectangle, Wide</option>
							<option value="300x70" data-width="300" data-height="70">300 x 70 Mini Rectangle, Wide</option>
							<option value="250x250" data-width="250" data-height="250">250 x 250 Square</option>
							<option value="200x200" data-width="200" data-height="200">200 x 200 Small Square</option>
							<option value="160x160" data-width="160" data-height="160">160 x 160 Small Square</option>
							<option value="336x280" data-width="336" data-height="280">336 x 280 Rectangle</option>
							<option value="336x160" data-width="336" data-height="160">336 x 160 Rectangle, Wide</option>
							<option value="334x100" data-width="334" data-height="100">334 x 100 Small Rectangle, Wide</option>
						</select>
						<small>Here is where you can select the size of your ad unit.</small>
					</p>
					<p>
						<label>Type</label>
						<select id="chitikaAdType"> 
							<option selected="selected" value="mpu">Text Ad</option>
							<option value="mobile">Mobile Ad</option>
						</select>
						<small>Choose which type of ad unit you would like.<br /><b>Multi Purpose Unit : </b>Our regular search targeted text ads composed of thumbnail images and text.<br /><b>Mobile Unit : </b>These ads will only be visible to users on mobile devices and will 'hover' at the bottom of their screen.</small>
					</p>
				</div>
				<div id="#chitikaVtabChannel" style="min-height: 263px;">
					<p>
						<label>Channel <small>(Optional)</small></label>
						<input id="chitikaAdChannel" type="text" class="input widefat" value="Chitika Default" />
						<small>Create a channel to keep track of individual ad unit or website's stats.</small>
					</p>
				</div>
			</div>
		</div>
		<input id="submitButton" type="image" src="<?php echo WP_INSERT_URL; ?>/includes/common/images/check.png" style="float: right; margin: 2px 20px 0 0; display: none;" onclick="submit_popup()" />
	</body>
</html>