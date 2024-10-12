<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Review extends MY_Controller
{
	public function __construct()
	{
		parent::__construct();
		$this->load->model('review_model');
		$this->load->library('recent_games');
	}

	public function create()
	{
		$this->require_login();

		$review = $_POST;

		if(!array_key_exists('id', $review) ||
			!array_key_exists('gameid', $review) ||
			!array_key_exists('fromid', $review) ||
			!array_key_exists('toid', $review) ||
			$_SESSION['user']['id'] != $review['fromid'] ||
			!in_array($review['gameid'], $_SESSION['user']['recent_gameids'])
			)
		{
			return FALSE;
		}
		$review['from_name'] = $_SESSION['user']['name'];
		$this->review_model->create($review);
	}

	public function update()
	{
		$review = $_POST;

		if(!array_key_exists('skill', $review) 
			|| !array_key_exists('id', $review) 
			|| !array_key_exists('value', $review)
			|| $review['skill'] > 5
			|| $review['skill'] < 1
			|| $review['value'] > 5
			|| $review['value'] < 1)
		{
			return FALSE;
		}
		$this->review_model->update($review);
	}

	public function comment()
	{
		$comment = $_POST;
		
		if(!array_key_exists('message', $comment)  || !array_key_exists('id', $comment))
		{
			return FALSE;
		}
		$this->review_model->comment($comment);
	}
}