<?php 
    include("includes/classes/Account.php");
    include("includes/handlers/register-handle.php");
 ?>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title this</title>
</head>
<body>
<form method = "POST" >
    <div>
        <label>Name</label><br>
        <input type = "text" name = "username">
    </div>
    <div>
        <label>Email</label><br>
        <input type = "text" name = "email">
    </div>
    <div>
        <label>Password</label><br>
        <input type = "text" name = "password">
    </div>
    <button type = "submit" name = "registerButton">SIGN UP</button>
</form>
</body>
</html>