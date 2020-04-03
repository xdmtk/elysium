<?php 
	include("includes/classes/Database.php");

	$conn = new Database();
	$icon = '';
	$msg = '';
	$title = '';
    if ($conn->userDoesntExist($_GET['token']))	 {
        $title = 'Whoops!';
        $icon = 'exclamation';
        $msg = "Sorry, this link isn't valid. Check the request and try again";
    }
    else {
        $title = 'Thank you!';
        $icon = 'check';
        $msg = "Thanks for verifying your email with us. Enjoy the Elysium-Project Chat Application!";
        $conn->updateVerification($_GET['token']);
    }

	$thanks = "
	<html lang=\"en\">
<head>
	<meta charset=\"utf-8\" />
	<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge,chrome=1\" />
	<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">
	<title></title>
	<link href='https://fonts.googleapis.com/css?family=Lato:300,400|Montserrat:700' rel='stylesheet' type='text/css'>
	<style>
		@import url(//cdnjs.cloudflare.com/ajax/libs/normalize/3.0.1/normalize.min.css);
		@import url(//maxcdn.bootstrapcdn.com/font-awesome/4.2.0/css/font-awesome.min.css);
	</style>
	<link rel=\"stylesheet\" href=\"https://2-22-4-dot-lead-pages.appspot.com/static/lp918/min/default_thank_you.css\">
	<script src=\"https://2-22-4-dot-lead-pages.appspot.com/static/lp918/min/jquery-1.9.1.min.js\"></script>
	<script src=\"https://2-22-4-dot-lead-pages.appspot.com/static/lp918/min/html5shiv.js\"></script>
</head>
<body>
	<header class=\"site-header\" id=\"header\">
		<h1 class=\"site-header__title\" data-lead-id=\"site-header-title\">$title</h1>
	</header>

	<div class=\"main-content\">
		<i class=\"fa fa-$icon main-content__checkmark\" id=\"checkmark\"></i>
		<p class=\"main-content__body\" data-lead-id=\"main-content-body\">$msg</p>
	</div>

	<footer class=\"site-footer\" id=\"footer\">
	</footer>
</body>
</html>
	";
    echo $thanks;

 ?>