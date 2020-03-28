<?php 
	include("../api/includes/classes/Database.php");

	class Account{

		/**
		* @param user fields for table
		* Checks to make sure all the values are valid
		* then sends email verification to user
		* and lastly inputs the user in DB with a 
		* 'N' value for verification field
		*/
		public function register($userName,$password,$email){

			if($this->validateUserName($userName) &&
				$this->validateEmail($email) &&
				$this->validatePassword($password)){

				$this->sendRegisterLink($email,$userName);
				$dataBase = new Database();
				$dataBase->verifyAndRegister($userName,$password,$email,'N');
			}
		}

		/**
		* @param users name  
		* Function to validate username and make sure its 
		* a certain length
		* @return true if its a valid username 
		*/
		public function validateUserName($userName){
			if(strlen($userName) > 25 || strlen($userName) < 5 ){
				return false;
			}
			return true;
		}

		/**
		* @param users password 
		* Function to validate password and make sure
		* it's strong enough
		* @return true if its a valid password
		*/ 
		public function validatePassword($password){

			//1. Check if password contains at least one values
	        $password = $password;
	        $uppercase = preg_match('/[A-Z]/', $password);
	        $lowercase = preg_match('/[a-z]/', $password);
	        $number = preg_match('/[0-9]/', $password);
	        $specialChars = preg_match('/[^\w]/', $password);
	        
	        //2. If password doesn't meet all requirments then return false 
	        if(!$uppercase || !$lowercase || !$number || !$specialChars || 
	            strlen($password) < 8) {
	            return false;
	        }
	        else{
	            return true;
	        }
		}

		/**
		* @param username and email
		* Calls xdmtk api to send an email to user with a link
		* when this link is clicked it will send the user
		* to verified.php where we update verification field
		*/	
		public function sendRegisterLink($email,$username){
			$callback = "https://sebastian.elysium-project.net/api/verified.php?token=";
			$body = "https://api.xdmtk.org/mailer/index.php?to=";
			$url_request = $body . $email .
						  "&token=". $username .
						  "&callback=" .$callback ; 

		  	$curl = curl_init();
		  	curl_setopt($curl,CURLOPT_URL, $url_request);
		  	curl_exec($curl);
			 
		}

		/**
		* @param users email 
		* Function to validate a person email making sure
		* it includes the chars @ and .com
		* @return true if its a valid email  
		*/
		public function validateEmail($email){
			if(!filter_var($email,FILTER_VALIDATE_EMAIL)){
				return false;
			}
			return true;
		}
		

	
		
	}
 ?>