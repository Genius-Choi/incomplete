<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Review_model extends CI_Model
{
	public function __construct()
	{
		parent::__construct();
		$this->db1 = $this->load->database('default', TRUE);
	}

	public function create($review)
	{
		$sql = "INSERT INTO reviews (id, fromid, from_name, toid, gameid)
		VALUES ('" . $review['id'] . "','" . $review['fromid'] . "','" . $review['from_name'] . "','" . $review['toid'] . "','" . $review['gameid'] . "')";

		$this->db1->query($sql);
	}

	public function update($review)
	{
		$skill = "skill" . $review['skill'];
		$skill_value = $review['value'];
		$reviewid = $review['id'];
		$sql = "UPDATE reviews 
				SET $skill = '$skill_value'
				WHERE id = '$reviewid'";
		$result = $this->db1->query($sql);
		return TRUE;
	}

	public function comment($comment)
	{
		$message = $comment['message'];
		$reviewid = $comment['id'];
		$sql = "UPDATE reviews
				SET message = '$message'
				WHERE id = '$reviewid'";
		$result = $this->db1->query($sql);
		return TRUE;
	}

	public function recent($gameids)
	{
		if(count($gameids) == 0)
		{
			return NULL;
		}

		$fromid = $_SESSION['user']['id'];

		$sql = "SELECT * FROM reviews r
				WHERE r.fromid = '$fromid' AND
						(r.gameid IN ('" . implode("','", $gameids) . "'))";

		$result = $this->db1->query($sql);
		$result = $result->result_array();
		$reviews = array();

		foreach ($result as $reviewid => $review)
		{
			$reviews[$review['id']] = $review;
		}
		
		return $reviews;
	}

	public function get($toid)
	{
		$sql = "SELECT * FROM reviews 

				WHERE toid = '$toid'
				AND (message IS NOT NULL
				OR skill1 != 0
				OR skill2 != 0
				OR skill3 != 0
				OR skill4 != 0)";
		$result = $this->db1->query($sql);
		return $result->result_array();
	}

	public function statistics($id)
	{
		$this->db1->trans_start();
		$sql = "SELECT AVG(NULLIF(skill1,0)),AVG(NULLIF(skill2,0)),AVG(NULLIF(skill3,0)),AVG(NULLIF(skill4,0)), COUNT(toid) 
				FROM reviews
				WHERE toid = '$id'";
		$result = $this->db1->query($sql);
		$result = $result->row_array(); 
		$skills['Game-Sense'] = round($result['AVG(NULLIF(skill1,0))'], 1) == 0 ? '-' : round($result['AVG(NULLIF(skill1,0))'], 1);
		$skills['Helpful'] = round($result['AVG(NULLIF(skill2,0))'], 1) == 0 ? '-' : round($result['AVG(NULLIF(skill2,0))'], 1);
		$skills['Skillful'] = round($result['AVG(NULLIF(skill3,0))'], 1) == 0 ? '-' : round($result['AVG(NULLIF(skill3,0))'], 1);
		$skills['Delivery'] = round($result['AVG(NULLIF(skill4,0))'], 1) == 0 ? '-' : round($result['AVG(NULLIF(skill4,0))'], 1);
		$skills['Received'] = $result['COUNT(toid)'];

		$sql = "SELECT COUNT(fromid)
				FROM reviews
				WHERE fromid='$id'
				AND (message IS NOT NULL
				OR skill1 != 0
				OR skill2 != 0
				OR skill3 != 0
				OR skill4 != 0)";
		$result = $this->db1->query($sql);
		$this->db1->trans_complete();
		$result = $result->row_array(); 
		$skills['Given'] = $result['COUNT(fromid)'];
		return $skills;
	}
}