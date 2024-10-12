<?php if(empty($games)) { ?>
<span class="open_sans">No matches have been played</span>
<?php } ?>
<?php foreach ($games as $game) { ?>

<div class="lol-match row">
	<div class="col-md-9">
		<table class="table table-condensed">
			<th class="col-md-1"/>
			<th class="col-md-3"></th>
			<th>Player</th>
			<?php foreach ($game['100'] as $player) { ?>
				<tr>
					<td>
						<?php if(isset($player['championSprite'])) { ?>
						<img src="<?php echo $player['championSprite'] ?>" class="img-responsive" alt="Responsive image">
						<?php } ?>
					</td>
					<td >
						<div class="lol-match-player-name">
							<strong><?php echo $player['name'] ?></strong>
						</div>
					</td>
				</tr>
			<?php } ?>
		</table>
		<table class="table table-condensed">
			<th class="col-md-1"/>
			<th class="col-md-3"></th>
			<th>Player</th>
			<?php foreach ($game['200'] as $player) { ?>
				<tr>
					<td>
						<?php if(isset($player['championSprite'])) { ?>
						<img src="<?php echo $player['championSprite'] ?>" class="img-responsive" alt="Responsive image">
						<?php } ?>
					</td>
					<td >
						<div class="lol-match-player-name">
							<strong><?php echo $player['name'] ?></strong>
						</div>
					</td>
				</tr>
			<?php } ?>
		</table>
	</div>
</div>
<?php } ?>