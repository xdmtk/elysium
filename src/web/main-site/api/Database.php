<?php
class Database{

    //DB Parameters
    private $DB_HOST = 'localhost';
    private $DB_USER = 'root';
    private $DB_PASS = '1234';
    private $DB_NAME = 'Chat';
    private $DB_TABLE = 'clients';
    private $conn;

    //Table Parameters
    private $id = 'null';
    private $username ;
    private $password;
    private $email;

    public function __construct(){
         $this->conn = null;

        //1. Connect to DB and check for valid connection
        try{
            $this->conn = new PDO('mysql:host=' . $this->DB_HOST . ';dbname=' . $this->DB_NAME, $this->DB_USER, $this->DB_PASS );
            $this->conn->setAttribute(PDO::ATTR_ERRMODE,PDO::ERRMODE_EXCEPTION);

        } catch(PDOException $e){
            echo 'Connection Error: ' . $e->getMessage();
        }

        return $this->conn;
    }

    /* Create Post
     * Creates the query and validates if 
     * username or email exists in DB
     */
    public function create(){

        //1. Create Query
        $query = "INSERT INTO " .
              $this->DB_TABLE . "
                SET
                  id=:id,
                  username=:username,
                  password=:password,
                  email=:email";

        $stmt = $this->conn->prepare($query);

        //2. Run query to check if userName exists
        $chkUserName = $this->conn->prepare("SELECT username FROM clients WHERE username=:username");
        $chkUserName->bindParam(":username", $this->username);
        $chkUserName->execute();

        //3. Run query to check if email already exists
        $chkEmail = $this->conn->prepare("SELECT email FROM clients WHERE email=:email");
        $chkEmail->bindParam(":email", $this->email);
        $chkEmail->execute();


        //4. If userName or email exists prompt client
        if($chkUserName->rowCount() > 0){
            echo 'Error: User already exists ';
        }
        if($chkEmail->rowCount() > 0){
            echo 'Error: Email already exists';
        }
        else {
            //5. Clean data
            $this->id = htmlspecialchars(strip_tags($this->id));
            $this->username = htmlspecialchars(strip_tags($this->username));
            $this->password = htmlspecialchars(strip_tags($this->password));
            $this->email = htmlspecialchars(strip_tags($this->email));

            //6. Bind Data
            $stmt->bindValue(":id", null, PDO::PARAM_INT);
            $stmt->bindParam(":username", $this->username);
            $stmt->bindParam(":password", $this->password);
            $stmt->bindParam(":email", $this->email);

            //7. Execute Query
            if($stmt->execute()){
                echo 'Successful post';
            }
            else{
                echo 'There must have been a problem with the post';
            }
        }
    }

    /*
    * Gets values from the form and the checks if there empty
    * If not empty assign values to member variables
    */
    public function setFormValues(array $request){

        //1.If fields aren't empty assign values to member variables
        if(!empty($_POST['username']) && !empty($_POST['email']) && !empty($_POST['password'])){
            $this->username = $_POST['username'];
            $this->email = $_POST['email'];
            $this->password = $_POST['password'];
            return true;
        }
        else{
            echo 'One of the fields you entered is blank. Make sure you fill out every box';
            return false;
        }
    }

    /*
     * Checks for password strength by 
     * verifying password has at least one of each
     * uppercase, lowercase, numeric, special char
     * and password length is greater than 8
     */
    public function chkPasswordStrength(){

        //1. Check if password contains at least one values
        $password = $this->password;
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