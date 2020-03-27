<?php 
	include("../api/includes/classes/Database.php");

	class Account{

		/**
		* @param User parameters from login
		* If all the fields are valid then it creates
		* a database object and uploads the user to 
		* DB.
		*/
		public function register($userName,$password,$email){

			if($this->validateUserName($userName) &&
				$this->validateEmail($email) &&
				$this->validatePassword($password)){
				$dataBase = new Database();
				$dataBase->verifyAndRegister($userName,$password,$email,'Y');
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
				echo 'Username must be between 5 and 25 characters';
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
	            echo'Password should be at least 8 characters in length and should include at least one upper case letter, one number, and one special character';
	            return false;
	        }
	        else{
	            echo 'Strong password';
	            return true;
	        }
		}

		public function sendEmailVerify($email){
			
			 $email = htmlspecialchars(strip_tags($email));
			 $to = "sebastianbabble@gmail.com";
			 $subject = "Please confirm your account with Elysium";
			 $headers = "From: staff@elysium-project.net\r\n";
			 $message = "Yo welcome to elysium";
			 mail($to, $subject,$message,$headers);
		}

		/**
		* @param users email 
		* Function to validate a person email making sure
		* it includes the chars @ and .com
		* @return true if its a valid email  
		*/
		public function validateEmail($email){
			if(!filter_var($email,FILTER_VALIDATE_EMAIL)){
				echo 'Not a valid email address';
				return false;
			}
			return true;
		}
		
	}
 ?>