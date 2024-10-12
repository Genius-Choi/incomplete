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
		<script type="text/javascript" src="<?php echo WP_INSERT_URL; ?>/includes/common/js/ui.multiselect.js?version=<?php echo WP_INSERT_VERSION; ?>"></script>
		<script type="text/javascript">
			jQuery(function(){
				jQuery(".multiselect").multiselect({dividerLocation: 0.5});
			});
			
			function submit_popup() {
				var selectedItems = new Array();
				var pagePicker = document.getElementById('country_picker');
				while (pagePicker.selectedIndex != -1) {
					selectedItems.push(pagePicker.options[pagePicker.selectedIndex].value);
					pagePicker.options[pagePicker.selectedIndex].selected = false;
				}
				parent.jQuery('#<?php echo wp_kses((string)$_GET['target'], ''); ?>').val(selectedItems.join(','));
				parent.jQuery.colorbox.close();
			}
		</script>
	</head>
	<body>
		<?php
		$selected = null;
		if(isset($_GET['data'])) {
			$selected = split(',', urldecode((string)$_GET['data']));
		}
		?>
		<select id="country_picker" class="multiselect" multiple="multiple" >
			<?php
			$countries = wp_insert_get_countries();
			foreach($countries as $country) {
				if($selected && in_array($country['value'], $selected)) {
					echo '<option value="'.$country['value'].'" selected="selected">'.$country['text'].'</option>';
				} else {
					echo '<option value="'.$country['value'].'">'.$country['text'].'</option>';
				}
			}
			?>
		</select>
		<input type="image" src="<?php echo WP_INSERT_URL; ?>/includes/common/images/check.png" style="float: right; margin: 2px 20px 0 0;" onclick="submit_popup()" />
	</body>
</html>