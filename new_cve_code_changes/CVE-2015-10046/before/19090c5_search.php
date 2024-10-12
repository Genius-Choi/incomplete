<div class="row">
  <div class="col-md-4"></div>
  <div class="col-md-4">
  	<?php echo form_open('search', array('class' => 'form-horizontal', 'id' => 'search_summoner')); ?>
  		<div class="input-group">
		      <?php echo form_input(array('name' => 'search', 'class' => 'form-control', 'placeholder' => 'Search Summoner', 'id' => 'search_textbox')); ?>
        <span class="input-group-btn">
          <button type="submit" class="btn btn-default">Search</button>
        </span>
		  </div>
	<?php echo form_close(); ?>
  </div>
  <div class="col-md-4"></div>
</div>
