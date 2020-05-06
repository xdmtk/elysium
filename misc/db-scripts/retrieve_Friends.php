<?php

    const DB_HOST = 'DB_HOST';
    const DB_USER = 'DB_USER';
    const DB_PASS = 'DB_PASS';
    const DB_NAME = 'DB_NAME';
    const DB_TABLE = 'DB_TABLE';
    const VALUE = 1;
    const ENV_PATH = "/var/www/private.env";
    $conn = "";

    /*
    * Gets value of env name and passes to it back
    */
    function read_env($val){
        $env_handle = fopen(ENV_PATH,"r") or die("Unable to open file!");
        while(!feof($env_handle)){
            $line = explode ("=", fgets($env_handle));
            if($line[0] == $val){
                fclose($env_handle);
                return trim($line[VALUE]);
            }
        }
    }

    /*
    * Public function that calls read_env
    */
    function get($val){
        return read_env($val);
    }

    function getFriends($userName){
        global $conn;
        /** @var  $chkUserName  PDOStatement */
        $chkUserName = $conn->prepare("SELECT friendsname FROM friends WHERE username=:username");
        $chkUserName->bindParam(":username", $userName);
        $chkUserName->execute();

        global $argv;
        $row = $chkUserName->fetchAll();
        
        for($i = 0; i<count($r0w); i++)
        {
            $argv = $argv . $row[i]['friendsname'] . ","; 
        }

        return $argv;
            
    }


    function main() {
        global $conn;
        $conn = new PDO('mysql:host=' . get("DB_HOST") . ';dbname=' . get("DB_NAME"), get("DB_USER"), get("DB_PASS") );
        $conn->setAttribute(PDO::ATTR_ERRMODE,PDO::ERRMODE_EXCEPTION);
        global $argv;
        echo getFriends($argv[1]);
    }

main();
