<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Summoner extends MY_Controller
{
	public function __construct()
	{
		parent::__construct();
		$this->load->model('user_model');
		$this->load->library('lol_api');
		$this->load->model('review_model');
		$this->load->library('recent_games');
	}

	function _remap($id)
	{
		$this->index($id);
	}

	public function index($id)
	{
		
		if($this->is_logged_in() && ($id == 'index' || $id == $this->get_userid()))
		{
			$id = $this->get_userid();
			$data['games'] = $this->recent_games->get($id);
			$gameids = array_keys($data['games']);
			$_SESSION['user']['recent_gameids'] = $gameids;
		}
		else
		{
			$data['games'] = NULL;
		}
		
		$summoner_name = $this->lol_api->getSummoner($id, 'name');
		if(empty($summoner_name))
		{
			$data['title'] = "No summoner found";
			$data['sub_title'] = "Try searching for another summoner";
		}
		else
		{
			if(!array_key_exists($id, $summoner_name))
			{
				$data['title'] = "Summoner Not Found";
			}
			else
			{
				$data['title'] = $summoner_name[$id];
			}
			
			$data['reviews'] = $this->review_model->get($id);
			if($data['games'] != NULL)
			{
				$current_reviews = $this->review_model->recent($gameids);
				$data['current'] = $current_reviews;
			}
			//parse data and display.
			$stats = $this->review_model->statistics($id);

			$data['stats'] = array_slice($stats, 0, 4);
			$data['review_stats'] = array_slice($stats, 4, 2);
			$data['sub_title'] = "Look below for game reviews";
		}
		$this->view_wrapper('summoner', $data);
	}
}