<div class="row">
    <div class="reviews-title">
      <p></p>
    </div>
  </div>
  <div class="row">
    <div class="col-md-7">
    <div class="reviews-content">
      <?php if(empty($reviews)) { ?>
        <p>No reviews</p>
        <?php } else { foreach ($reviews as $review) { ?>
            <div class="review-header">
              <p>
                <a href="<?php echo site_url('summoner')."/".$review['fromid'] ?>"><?php echo $review['from_name'] ?></a>:
                <?php if($review['skill1'] != 0) { ?>
                Game-sense-<?php echo $review['skill1'] ?>
                <?php } if($review['skill2'] != 0) { ?>
                  Helpful-<?php echo $review['skill2'] ?>
                <?php } if($review['skill3'] != 0) { ?>
                  Skillful-<?php echo $review['skill4'] ?>
                <?php } if($review['skill4'] != 0) { ?>
                  Delivery-<?php echo $review['skill4'] ?>
                <?php } ?>
                <?php echo $review['created'] ?>
              </p>
            </div>
            <div class="review-body">
              <?php if($review['message'] != NULL) { ?>
              <p><?php echo $review['message']?></p>
              <?php } ?>
            </div>
        <?php } } ?>
      </div>
    </div>
  </div>