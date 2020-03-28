<?php 
	class Environment{

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
	    private function read_env($val){
	    	$env_handle = fopen(self::ENV_PATH,"r") or die("Unable to open file!");
	    	while(!feof($env_handle)){
	    		$line = explode ("=", fgets($env_handle));
	    		if($line[0] == $val){
	    			fclose($env_handle);
	    			return trim($line[self::VALUE]);
	    		}
	    	}
	    }

	    /*
	    * Public function that calls read_env
	    */
	    public function get($val){
	    	return self::read_env($val);
	    	}
	    }

		
	
