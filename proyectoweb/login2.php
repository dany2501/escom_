<?php
include_once 'database.php';

session_start();

if(isset($_GET['cerrar_sesion'])){
	session_unset();

	session_destroy();
}

if(isset($_SESSION['rol'])){
	switch($_SESSION['rol']){
		case 1:
		header('location: Administradores.php');
		break;

		case 2:
		header('location: PP.php');
		break;

		case 3:
		header('location: Alumno.php');
		break;

		default:
	}
}

if(isset($_POST['username']) && isset($_POST['password'])){
	$username = $_POST['username'];
	$password = $_POST['password'];

	$db = new Database();
	$query = $db->connect()->prepare('SELECT*FROM usuarios WHERE username = :username AND password = :password');
	$query->execute(['username' => $username, 'password' => $password]);

	$row = $query->fetch(PDO::FETCH_NUM);
	if($row == true){
            // validar rol
		$rol = $row[3];
		$_SESSION['rol'] = $rol;

		switch($_SESSION['rol']){
			case 1:
			header('location: Administradores.php');
			break;
			
			case 2:
			header('location: PP.php');
			break;

			case 3:
			header('location: Alumno.php');
			break;
			
			default:
		}
	}else{
            // no existe el usuario
		echo "El usuario o contraseña son incorrectos";
	}

}


?>
<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<meta name="author" content="Erick Saúl Quezada Almazán y Johan Ali Rojas Hernandez"> 
	<meta name="viewport" content="width=device-width, initial-scale=1.0">
	<meta http-equiv="X-UA-Compatible" content="ie=edge">
	<title>Login</title>
	<style ">
		body {
			margin: 0;
			padding: 0;
			background: url(bg.jpeg) no-repeat center top;
			background-size: cover;
			font-family: sans-serif;
			height: 100vh;
		}

		.login-box {
			width: 320px;
			height: 420px;
			background: #000;
			color: #fff;
			top: 50%;
			left: 50%;
			position: absolute;
			transform: translate(-50%, -50%);
			box-sizing: border-box;
			padding: 70px 30px;
		}

		.login-box .avatar {
			width: 100px;
			height: 100px;
			border-radius: 50%;
			position: absolute;
			top: -50px;
			left: calc(50% - 50px);
		}

		.login-box h1 {
			margin: 0;
			padding: 0 0 20px;
			text-align: center;
			font-size: 22px;
		}

		.login-box label {
			margin: 0;
			padding: 0;
			font-weight: bold;
			display: block;
		}

		.login-box input {
			width: 100%;
			margin-bottom: 20px;
		}

		.login-box input[type="text"], .login-box input[type="password"] {
			border: none;
			border-bottom: 1px solid #fff;
			background: transparent;
			outline: none;
			height: 40px;
			color: #fff;
			font-size: 16px;
		}

		.login-box input[type="submit"] {
			border: none;
			outline: none;
			height: 40px;
			background: #b80f22;
			color: #fff;
			font-size: 18px;
			border-radius: 20px;
		}

		.login-box input[type="submit"]:hover {
			cursor: pointer;
			background: #ffc107;
			color: #000;
		}

		.login-box a {
			text-decoration: none;
			font-size: 12px;
			line-height: 20px;
			color: darkgrey;
		}

		.login-box a:hover {
			color: #fff;
		}
	</style>
</head>
<body>
	<div class="login-box">
		<a href="Proyecto_Principal(maquetado).php">
			<img src="escom.PNG" class="avatar" alt="Avatar Image">  
		</a>
		<h1>Iniciar Sesión</h1>
		<div align="center">
			<span>O <a href="Registro.php">Registro </a></span>
		</div>
		<form action="#" method="POST">
			<label for="username"></label>
			Usuario: <br/><input type="text" name="username"><br/>
			Contraseña: <br/><input type="text" name="password"><br/>
			<input type="submit" value="Iniciar sesión">
		</form>  
	</div>
</body>
</html>