<?php

namespace DA;

class DAGuestBookEntry extends DA_Base {
	function find($id) {
		$sql = 'SELECT * FROM GuestBookEntry WHERE Id = :Id';
		$stmt = self::getConnection ()->prepare ( $sql );
		$stmt->bindValue ( ":Id", $id );
		$stmt->execute ();
		
		$people = array ();
		$result = $stmt->fetch ( \PDO::FETCH_ASSOC );
		
		$entry = self::assignValues ( new \BE\BEGuestBookEntry (), $result );
		
		return $entry;
	}
	function findAll() {
		$sql = 'SELECT * FROM GuestBookEntry';
		$stmt = self::getConnection ()->prepare ( $sql );
		$stmt->execute ();
		
		$entries = array ();
		while ( $result = $stmt->fetch ( \PDO::FETCH_ASSOC ) ) {
			
			$entry = self::assignValues ( new \BE\BEGuestBookEntry (), $result );
			$entries [] = $entry;
		}
		return $entries;
	}
	function save(\BE\BEGuestBookEntry $entry) {
		// TODO New and update Queys
		$sql = "";
		if ($entry->Id > 0)
			$sql = "UPDATE GuestBookEntry SET 
					Text = :Text,
					CreatedAt = :CreatedAt,
					UserId = :UserId
					WHERE Id = :Id
					";
		else
			$sql = 'INSERT INTO GuestBookEntry(Text,CreatedAt,UserId) VALUES (:Text,:CreatedAt,:UserId)';
		try {
			$stmt = self::getConnection ()->prepare ( $sql );
			if ($entry->Id > 0)
				$stmt->bindValue ( ":Id", $entry->Id );
			$stmt->bindValue ( ":UserId", $entry->UserId );
			$stmt->bindValue ( ":CreatedAt", $entry->CreatedAt );
			$stmt->bindValue ( ":Text", $entry->Text );
			
			$stmt->execute ();
		} catch ( \Exception $e ) {
			return "<li>An internal Error ocourred!</li>";
		}
		// TODO Error handling
	}
}

