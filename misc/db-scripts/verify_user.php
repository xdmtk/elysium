<?php

    const DB_HOST = 'DB_HOST';
    const DB_USER = 'DB_USER';
    const DB_PASS = 'DB_PASS';
    const DB_NAME = 'DB_NAME';
    const DB_TABLE = 'DB_TABLE';
    const VALUE = 1;
    const ENV_PATH = "/var/www/private.env";

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

    function userExists($userName){

        /** @var  $chkUserName  PDOStatement */
        $chkUserName = $this->conn->prepare("SELECT username FROM " . Environment::get("DB_TABLE") ." WHERE username=:username");
        $chkUserName->bindParam(":username", $userName);
        $chkUserName->execute();

        if($chkUserName->rowCount() > 0){
            $row = $chkUserName->fetchAll();
            if ($row[0]['verified'] == 'Y') {
                global $argv;
                if ($row[0]['password'] == $argv[2]) {
                    return [true => 'success'];
                }
                else {

                    return [false => 'password_incorrect'];
                }
            }
            else {
                return [false => 'unverified'];
            }

        }
        return [false => 'user_not_found'];
    }


    function main() {
        $this->conn = new PDO('mysql:host=' . get("DB_HOST") . ';dbname=' . get("DB_NAME"), get("DB_USER"), get("DB_PASS") );
        $this->conn->setAttribute(PDO::ATTR_ERRMODE,PDO::ERRMODE_EXCEPTION);
        global $argv;
        echo userExists($argv[1]);
    }

main();
