<div class="summoner-title">
  <div class="row">
    <div class="col-md-7">
      <h1> <?php echo $title ?></h1>
    </div>
  </div>
</div>

<?php if(!empty($stats)) { ?>
<div class="summoner-stats">
  <div class="row">
    <?php foreach ($stats as $skill_name => $stat) { ?>
      <div class="col-md-1">
        <div class="stat-value">
          <?php echo $stat ?>
        </div>
        <div class="stat-label">
          <?php echo $skill_name ?>
        </div>
      </div>
    <?php } ?>
    <div class="col-md-2">
      <div class="given-received-block">
        <div class="panel panel-default">
          <div class="panel-body">
          <?php foreach ($review_stats as $review_stat => $review_statcount) { ?>
              <div class="stat-label">
                <?php echo $review_statcount ?>
                <?php echo $review_stat ?>
              </div>
          <?php } ?>
         </div>
        </div>
      </div>
    </div>
  </div>
</div>
<?php } ?>


<?php if(empty($games)) { ?>
<div class="row">
  <div class="col-md-4 col-md-offset-4"><span class="open_sans"></span></div>
</div>
<?php } else { ?>
<div id="sg_<?php echo $id ?>" class="summoner-games">
  <div class="row">
    <div class="col-md-7">
      <div class="panel-group" id="accordion" role="tablist" aria-multiselectable="true">
      <?php foreach ($games as $gameid => $game) { ?>
        <div class="panel panel-default">
          <div class="panel-heading" role="tab" id="<?php echo $gameid ?>-heading">
              <a data-toggle="collapse" data-parent="#accordion" href="#<?php echo $gameid ?>" aria-expanded="true" aria-controls="<?php echo $gameid ?>">
                Game played on <?php echo $game['time'] ?> GMT
              </a>
          </div>
          <div id="<?php echo $gameid ?>" class="panel-collapse collapse in" role="tabpanel" aria-labelledby="<?php echo $gameid ?>-heading">
            <div class="panel-body">
              <table class="table table-condensed">
              <?php for ($i=0; $i < count($game['100']); $i++) { ?>
                  <tr class="review">
                    <td class="summoner-icon">
                      <?php if(isset($game['100'][$i]['championSprite'])) { ?>
                        <span >
                          <img src="<?php echo $game['100'][$i]['championSprite'] ?>" class="lol-match-icon" alt="Responsive image">
                        </span>
                      <?php } ?>
                    </td>
                    <td class="summoner-name">
                      <a href="<?php echo site_url('summoner') . "/" . $game['100'][$i]['summonerId']; ?>" class="btn btn-link summoner-reviews"><?php echo $game['100'][$i]['name'] ?></a>
                    </td>
                    <td><?php if(array_key_exists($_SESSION['user']['id'] . "-" . $game['100'][$i]['summonerId'] . "-" . $gameid, $current)) { ?>
                     <?php } else if($_SESSION['user']['id'] != $game['100'][$i]['summonerId']) { ?>
                      <div id="<?php echo $_SESSION['user']['id'] . "-" . $game['100'][$i]['summonerId'] . "-" . $gameid?>">
                        <button type="button" id="<?php echo $_SESSION['user']['id'] . "-" . $game['100'][$i]['summonerId'] . "-" . $gameid?>" class="btn btn-link review" name="review_summoner">review</button>
                      </div>
                    <?php } ?>
                    </td>
                    <td class="review-comment">
                      <div id="<?php echo $_SESSION['user']['id'] . "-" . $game['100'][$i]['summonerId'] . "-" . $gameid ?>-message">
                      </div>
                    </td>
                  </tr>
                <?php } ?>
              </table>

              <table class="table table-condensed">
                <?php for ($i=0; $i < count($game['200']); $i++) { ?>
                  <tr class="review"> 
                    <td class="summoner-icon">
                      <?php if(isset($game['200'][$i]['championSprite'])) { ?>
                        <span>
                          <img src="<?php echo $game['200'][$i]['championSprite'] ?>" class="lol-match-icon" alt="Responsive image">
                        </span>
                      <?php } ?>
                    </td>
                    <td class="summoner-name">
                      <span>
                        <a href="<?php echo site_url('summoner') . "/" . $game['200'][$i]['summonerId']; ?>" class="btn btn-link summoner-reviews"><?php echo $game['200'][$i]['name'] ?></a>
                      </span>
                    </td>
                    <td>
                    <?php if(array_key_exists($_SESSION['user']['id'] . "-" . $game['200'][$i]['summonerId'] . "-" . $gameid, $current)) { ?>
                     <?php } else if($_SESSION['user']['id'] != $game['200'][$i]['summonerId']) { ?>
                      <div id="<?php echo $_SESSION['user']['id'] . "-" . $game['200'][$i]['summonerId'] . "-" . $gameid?>">
                        <button type="button" id="<?php echo $_SESSION['user']['id'] . "-" . $game['200'][$i]['summonerId'] . "-" . $gameid?>" class="btn btn-link review" name="review_summoner">review</button>
                      </div>
                    <?php } ?> 
                    </td>
                    <td class="review-comment">
                      <div id="<?php echo $_SESSION['user']['id'] . "-" . $game['200'][$i]['summonerId'] . "-" . $gameid ?>-message">
                      </div>
                    </td>
                  </tr>
                <?php } ?>
              </table> 
            </div>
          </div>
        </div>
      <?php } ?>
      </div>
    </div>
  </div>
</div>
<?php } ?>

<div id="sr_<?php echo $id ?>" class="summoner-reviews">

</div>


