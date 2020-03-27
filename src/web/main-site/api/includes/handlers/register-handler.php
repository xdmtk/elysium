<?php 

    /*
    * Clean functions for inputs from form
    */
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

    /*
    * When user registers and hits submit this function will be called
    * Gets the values in forms and cleans them and then registers them
    * in account class
    */
    if(isset($_POST['registerButton'])){
        echo 'inside register-handler.php';

        if(!empty($_POST['username']) && !empty($_POST['email']) && !empty($_POST['password'])){
            $userName = cleanUsername($_POST['username']);
            $email = cleanEmail($_POST['email']);
            $password = password_hash(cleanPassword($_POST['password']),CRYPT_BLOWFISH, ['cost' => 12]);

            $account = new Account();
            $account->register($userName, $password, $email);
        }
        else{
            echo 'One of the fields you entered is blank. Make sure you fill out every box';
        }
    }
 ?>