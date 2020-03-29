<?php 
	include("includes/classes/Database.php");

	$conn = new Database();
	$conn->updateVerification($_GET['token']);

 ?>