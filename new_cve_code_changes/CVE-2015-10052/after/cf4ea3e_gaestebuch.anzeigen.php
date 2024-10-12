
<ul>
<?php
foreach ( $entries as $entry ) {
	?>
	<div class="">

		<div class="jumbotron">
			<div>
	<?php
	echo "<p>$entry->Text </p>";
	?>					
			</div>
			<div >
			<?php echo "Entry created by <strong>" . $entry->User->FullName . " </strong> on $entry->CreatedAt ";
			?>
			<ul class="list-inline">
			
				<?php if(isset($entry->editLink)) echo "<li><a href='".$entry->editLink."'>Edit</a></li>"; ?>

			</ul>
			</div>

		</div>
			
	<?php
}
?>
	</div>

</ul>
