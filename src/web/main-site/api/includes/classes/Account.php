<?php 
	Class Account{

		public function register(){

		}

		
		private function validateUsername(){

		}
		private function validateFirstName(){

		}
		private function validateLastName(){

		}
		private function validateEmail(){

		}
		private function validatePassword($pw){
			
			$password = $pw;
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
	}
 ?>