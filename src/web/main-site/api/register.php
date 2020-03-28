<?php 
    include("includes/classes/Account.php");


    //1.Cleaning the values for the functions.
    function cleanId($inputText){
        return htmlspecialchars(strip_tags($inputText));
    }
    function cleanUsername($inputText){
        return htmlspecialchars(strip_tags($inputText));
    }
    function cleanEmail($inputText){
        return htmlspecialchars(strip_tags($inputText));
    }
    function cleanPassword($inputText){
        return htmlspecialchars(strip_tags($inputText));
    } 
    //2.Handle request and then register user a new account
   if(!empty($_POST['username']) && !empty($_POST['email']) && !empty($_POST['password'])){
            $userName = cleanUsername($_POST['username']);
            $email = cleanEmail($_POST['email']);
            $password = password_hash(cleanPassword($_POST['password']),CRYPT_BLOWFISH, ['cost' => 12]);

            $account = new Account();
            $account->register($userName, $password, $email);
        }
        
   
?>