<?php
	
  //Headers
  header('Access-Control-Allow-Origin: *');
  header('Content-Type: application/json');
  header('Access-Control-Allow-Methods: POST');
  header('Access-Control-Allow-Headers: Access-Control-Allow-Headers,Content-Type, Access-Control-Allow-Methods,Authorization,X-Requested-With');

  //Local
  include_once '../api/Database.php';

  //1.Connect to DB
  $database = new Database();
  //2.Set values from form and check for empty para
  //$database->setFormValues($_POST);

  if($database->setFormValues($_POST) && $database->chkPasswordStrength()){
  	  $database->create();

  }
