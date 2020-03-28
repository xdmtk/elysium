<?php
include("../api/includes/classes/Environment.php");
class Database{

    private $conn;
    /*
    * Connect to database and check 
    * for errors
    */
    public function __construct(){
         $this->conn = null;

        //1. Connect to DB and check for valid connection
        try{
            $this->conn = new PDO('mysql:host=' . Environment::get("DB_HOST") . ';dbname=' . Environment::get("DB_NAME"), Environment::get("DB_USER"), Environment::get("DB_PASS") );
            $this->conn->setAttribute(PDO::ATTR_ERRMODE,PDO::ERRMODE_EXCEPTION);

        } catch(PDOException $e){
            echo 'Connection Error: ' . $e->getMessage();
        }

        return $this->conn;
    }

    /**
    * @param username
    * calls setVerification which essentially 
    * creates query to update the DB table
    * with a value of 'Y' indicating user
    * has been verified
    */
    public function updateVerification($userName){
        echo $userName;
        $this->setVerification($userName);
    }
    private function setVerification($userName){
        $verified = 'Y';
        $query = $this->conn->prepare("UPDATE " . Environment::get("DB_TABLE") . 
                                      " SET verified=:verified WHERE 
                                      username =:username ");
        $query->bindParam(":verified",$verified );
        $query->bindParam(":username", $userName);
        $query->execute();

    }
    /**
    * @param value of userName 
    * Check if user exists in DB and 
    * @return true if user doesn't exist in database
    */
    private function userExists($userName){
        
        $chkUserName = $this->conn->prepare("SELECT username FROM " . Environment::get("DB_TABLE") ." WHERE username=:username");
        $chkUserName->bindParam(":username", $userName);
        $chkUserName->execute();

        if($chkUserName->rowCount() > 0){
            echo 'Error: User already exists';
            return false;
        }
        return true;
    }

    /**
    * @param users email
    * Checks if user already exists in the database
    * and returns true if they are and false
    * if they aren't
    * @return true if email doesn't exist in database
    */
    private function emailExists($email){

        //1.Prepare statement for checking
        $chkEmail = $this->conn->prepare("SELECT email FROM " . Environment::get("DB_TABLE") . " WHERE email=:email");
        $chkEmail->bindParam(":email", $email);
        $chkEmail->execute();

        //2.Check if table has a row with current username 
        if($chkEmail->rowCount() > 0){
            echo 'Error: Email already exists';
            return false;
        }

        return true;
    }

    /**
    *@param Db connection with all table field values
    * takes the values and binds them to the query string
    * @return Db connection with binded query 
    */
    private function bindQuery($stmt,$userName,$password,$email,$verify){
        $stmt->bindValue(":id", null, PDO::PARAM_INT);
        $stmt->bindParam(":username", $userName);
        $stmt->bindParam(":password", $password);
        $stmt->bindParam(":email", $email);
        $stmt->bindParam(":verify", $verify);

        return $stmt;
    }

    /** 
     * Create Post
     * @param Table fields  
     * Creates the query and validates if 
     * username or email exists in DB
     */
    private function create($userName,$password,$email,$verify){
        
        //1. Create Query
        $query = "INSERT INTO " .
              Environment::get("DB_TABLE") . "
                SET
                  id=:id,
                  username=:username,
                  password=:password,
                  email=:email,
                  verify=:verify";

        //2.Prepare query 
        $stmt = $this->conn->prepare($query);

        $verify = htmlspecialchars_decode(strip_tags($verify));

        //6. Bind Data
        $stmt = $this->bindQuery($stmt,$userName,$password,$email,$verify);

        //7. Execute Query
        if($stmt->execute())
            echo 'Successful post';
        else
            echo 'There must have been a problem with the post';
    }
        
    /**
    * @param Table fields
    * If username and email aren't taken then register user to db
    */
    public function verifyAndRegister($userName, $password, $email, $verified){
       if($this->userExists($userName) && $this->emailExists($email))
             $this->create($userName, $password, $email, $verified);
  }    
}

