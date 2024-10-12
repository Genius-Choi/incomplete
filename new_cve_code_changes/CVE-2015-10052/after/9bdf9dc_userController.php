<?php

namespace Controller;

class userController implements IController {
	public function __construct() {
	}
	public function index($param, $data, $session) {
		$this->listusers ();
	}
	public function detail($param) {
		$user = \BO\BOUser::find ( $param );
		if ($user && ! $user->isNew ()) {
			
			(new \View\View ( 'user.detail', array (
					'user' => $user 
			) ))->display ();
		} else {
			$this->listusers ();
		}
	}
	public function listusers() {
		$users = \BO\BOUser::findAll ();
		
		$this->innerView = new \View\View ( 'user.list', array (
				'users' => $users 
		) );
		$this->create();
	}
	public function register() {
	}
	public function login($param, $data, $session) {
		$errorMessage = "";
		$backurl = "/";
		if (isset ( $data ['backurl'] ))
			$backurl = $data ['backurl'];
		
		if (isset ( $data ['email'] ) && isset ( $data ['password'] )) {
			$user = \BO\BOUser::login ( $data ['email'], $data ['password'] );
			if ($user->Id > 0) {
				
				$_SESSION ['userId'] = $user->Id;
				$_SESSION ['FullName'] = $user->FullName;
				// Logged In
				\Redirector::redirect($backurl);
				return;
			} else
				$errorMessage = "Incorrect credentials!";
		} else
			$errorMessage = "Please enter credentials!";
			
			// Display Login Page
		$this->innerView =new \View\View ( 'user.login', array (
				'errorMessage' => $errorMessage,
				'backurl' => $backurl 
		) );
		$this->create();
	}
public function create() {
		$this->innerView = (new \View\View ( 'mainpage', array (
				'title' => 'Login',
				'innercontent' => $this->innerView 
		) ))->display ();
	}
	public function __destruct() {
	}
}
