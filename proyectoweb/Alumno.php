<?php

?>

<!DOCTYPE html>
<html lang="es">
<head>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/css/bootstrap.min.css" integrity="sha384-Gn5384xqQ1aoWXA+058RXPxPg6fy4IWvTNh0E263XmFcJlSAwiGgFAW/dAiS6JXm" crossorigin="anonymous">
	<link href="https://fonts.googleapis.com/css?family=Open+Sans|Poppins:300,400,600,800" rel="stylesheet">
	<link rel="stylesheet" href="css/estilos.css">
	<link rel="stylesheet" href="css/font/fontello-57f46aa6/css/icon.css">
	<style>
		body {
	background: #f2f2f2;
	font-family: 'Open sans', 'Poppins', sans-serif;
}

header {
	margin-top: 30px;
}

header .nav {
	min-height: 80px;
	overflow: hidden;
	background: #fff;
}

/* ---- Logo ---*/
header .logo h2,
header .logo span,
header .logo p {
	font-size: 16px;
	display: inline-block;
	margin: 0px;	
}

header .logo h2 {
	font-weight: 800;
	text-transform: uppercase;
}

header .logo .icono {
	color: #bfbfbf;
}

header .logo p {
	color: #777777;
}

/* --- Menu ---*/
header .menu {
	padding: 0;
}

header .menu a{
	display: block;
	text-decoration: none;
	color: #FFF;
	padding: 0 30px;
}

header .menu a div span {
	font-weight: 600;
}

header .menu .c-1 {background: #3da5e2;}
header .menu .c-2 {background: #005385;}
header .menu .c-3 {background: #003855;}
header .menu .c-4 {background: #00090e;}

header .menu .c-1:hover {background: #1ba0ef;}
header .menu .c-2:hover {background: #00426a;}
header .menu .c-3:hover {background: #002d44;}
header .menu .c-4:hover {background: #2e4053;}

/* --- Slider ---*/
.slider {
	margin-bottom: 40px;
}

.slider .col {
	padding: 0;
}

/* --- Acerca de --- */
.acerca-de {
	padding: 30px;
	margin-bottom: 40px;
}

.acerca-de .horario .titulo{
	color: #005385;
	font-family: 'Poppins','Open sans', sans-serif;
	font-weight: 300;
	font-size: 40px;
	margin-bottom: 30px;
	text-align: center;
}
.acerca-de .tareas .titulo{
	color: #005385;
	font-family: 'Poppins','Open sans', sans-serif;
	font-weight: 300;
	font-size: 40px;
	margin-bottom: 30px;
	text-align: center;
}
.acerca-de .progreso .titulo {
	color: #005385;
	font-family: 'Poppins','Open sans', sans-serif;
	font-weight: 300;
	font-size: 40px;
	margin-bottom: 30px;
	text-align: center;
}

.acerca-de .progreso .label{
	font-size: 18px;
	font-weight: 600;
	color: #005385;
	margin-bottom: 10px;
}

.acerca-de .progreso .progress {
	background: #005385;
	border-radius: 0;
	margin-bottom: 15px;
}

.acerca-de .info .progress-bar {
	height: 25px;
	background: #3da5e2;
	line-height: 25px;
	text-align: left;
	padding-left: 20px;
}

/* --- Contacto ---*/
.contacto {
	padding: 40px;
	border-top: 1px solid #cbcbcb;
	margin-bottom: 40px;
}

.contacto .titulo {
	color: #003855;
	font-family: 'Poppins','Open sans', sans-serif;
	font-weight: 300;
	font-size: 40px;
	text-align: center;
}

.contacto .form-group {
	margin-bottom: 0;
}

.formulario input[type='text'],
.formulario input[type='email'],
.formulario textarea {
	padding: 15px;
	border: none;
	width: 100%;
	font-family: 'Poppins','Open sans', sans-serif;
	margin-bottom: 30px;
}

.formulario textarea {
	height: 150px;
	min-height: 150px;
	max-height: 250px;
}

.formulario .boton {
	background: #3da5e2;
	border: none;
	padding: 7px 30px;
	color: #fff;
	font-family: 'Poppins','Open sans', sans-serif;
	cursor: pointer;
	width: auto;
	border-radius: 3px;
}

.formulario .boton:hover {
	background: #1ba0ef;
}

/* --- Redes Sociales ---*/
.redes-sociales {
	padding: 40px;
	margin-bottom:  40px;
}

.redes-sociales .icono {
	width: 100px;
	height: 100px;
	font-size: 40px;
	line-height: 100px;
	text-align: center;
	color: #fff;
	background: #cbcbcb;
	display: inline-block;
	margin: 0px 20px;
	text-decoration: none;
	border-radius: 100px;
	transition: all .3s ease;
}

.redes-sociales .twitter{background: #1da1f2;}

.redes-sociales .facebook{background: #3b5988;}

.redes-sociales .youtube{background: #FF0000;}

.redes-sociales .instagram{
	background: #030903;
	color: #ffffff;
	}

/* --- Mediaqueries ---*/

/*Dispositivo xl*/
@media screen and (max-width: 1199px) {}

/*Dispositivo lg*/
@media screen and (max-width: 991px) {
	.logo {
		height: 76px;
	}

	.menu {
		min-height: 76px;
	}

	.menu a {
		width: 100%;
	}

	.menu a div {
		width: 100%;
	}
	.modal .modal-dialog {
		width: 90%;
	}

	.modal .modal-dialog .modal-content img {
		width: 100%;
	}
}

/*Dispositivo md*/
@media screen and (max-width: 767px) {
	.logo {
		height: 64px;
	}

	.menu {
		min-height: 64px;
	}

	.menu a {
		width: 100%;
	}

	.menu a div {
		width: 100%;
	}
	.modal .modal-dialog {
		width: 90%;
	}

	.modal .modal-dialog .modal-content img {
		width: 100%;
	}
}

/*Dispositivo sm*/
@media screen and (max-width: 575px) {
	header {
		margin-top: 0;
		text-align: center;
	}

	header .logo h2,
	header .logo p {
		font-size: 12px;
	}

	.logo {
		height: 50px;
	}

	.menu {
		min-height: 50px;
	}

	.menu a {
		width: 100%;
	}

	.menu a div {
		width: 100%;
	}

	.modal .modal-dialog {
		width: 90%;
	}

	.modal .modal-dialog .modal-content img {
		width: 100%;
	}

	.redes-sociales .icono {
		width: 50px;
		height: 50px;
		line-height: 50px;
		font-size: 20px;
}




	</style>
	<title>Menu Principal</title>
</head>
<body>

	<header>
		<div class="container">
			<!--Barra logo + menu-->
			<div class="row nav rounded-top align-items-stretch justify-content-between">
				<!--Logotipo-->
				<div class="col-md-12 col-lg logo d-flex align-items-center justify-content-center justify-content-lg-start">
					<h2>Bienvenido(a)</h2>
					<span class="icono icon-dot">
						<p>Menu Principal</p>
					</span>
				</div>
				
				<!--Menu-->
				<nav class="col-md-12 col-lg-auto menu d-flex align-items-stretch flex-wrap flex-sm-nowrap">
					<a href="#" class="c-1 d-flex align-items-center">
						<div class="d-flex flex-column text-center">
							<span>Horario</span>
							<i class="icono icon-calendar"></i>
						</div>
					</a>
					<a href="#" class="c-2 d-flex align-items-center">
						<div class="d-flex flex-column text-center">
							<span>Tareas</span>
							<i class="icono icon-book"></i>
						</div>
					</a>
					<a href="#" class="c-3 d-flex align-items-center">
						<div class="d-flex flex-column text-center">
							<span>Material didáctico</span>
							<i class="icono icon-book-open"></i>
						</div>
					</a>
					<a href="cerrarsesion.php" class="c-4 d-flex align-items-center">
						<div class="d-flex flex-column text-center">
							<span>Cerrar sesión</span>
							
							<i class="icono icon-logout"></i>
						</div>
					</a>
				</nav>
			</div>

			<!--Slider-->
			<div class="row slider">
				<div class="col">
					<div class="carousel slide" id="slider" data-ride="carousel">
						<ol class="carousel-indicators">
							<li data-target="#slider" data-slide-to="0" class="active"></li>
							<li data-target="#slider" data-slide-to="1"></li>
							<li data-target="#slider" data-slide-to="2"></li>
							<li data-target="#slider" data-slide-to="3"></li>
							<li data-target="#slider" data-slide-to="4"></li>
						</ol>
						<div class="carousel-inner">
							<div class="carousel-item active">
								<a href="pg/MaterialEspaniol.html"><img src="img/espa.jpg" alt="Slide1" class="d-block img-fluid">
								</a>
							</div>
							<div class="carousel-item">
								<a href="pg/MaterialMatematicas.html">
									<img src="img/mt.jpg" alt="Slide2" class="d-block img-fluid">
								</a>
							</div>
							<div class="carousel-item">
								<a href="pg/ProximoMaterial.html">
									<img src="img/cdm.jpeg" alt="Slide3" class="d-block img-fluid">
								</a>
							</div>
							<div class="carousel-item">
								<a href="pg/ProximoMaterial.html">
									<img src="img/fce.jpeg" alt="Slide4" class="d-block img-fluid">
								</a>
							</div>
						</div>
						<div class="carousel-item">
							<img src="img/2.jpeg" alt="Slide5" class="d-block img-fluid">
						</div>
					</div>


					<!--Controles-->
					<a href="#slider" class="carousel-control-prev" data-slide="prev">
						<span class="carousel-control-prev-icon" aria-hidden="true"></span>
						<span class="sr-only">Anterior</span>
					</a>
					<a href="#slider" class="carousel-control-next" data-slide="next">
						<span class="carousel-control-next-icon" aria-hidden="true"></span>
						<span class="sr-only">Siguiente</span>
					</a>
				</div>
			</div>
		</div>
	</div>
</div>
</header>

<main>
	<div class="row acerca-de">

		<div class="col-12 col-lg-4 horario">
			<div class="horario">
				<div class="table-responsive">
					<div class="col">
						<h2 class="titulo">Horario</h2>
						<table class="table">
							<thead>
								<tr class="bg-primary">
									<th  scope="col">Materia|Día</th>
									<th scope="col">Lunes</th>
									<th scope="col">Martes</th>
									<th scope="col">Miercoles</th>
									<th scope="col">
									Jueves</th>
									<th scope="col">Viernes</th>
								</tr>
							</thead>
							<tbody>
								<tr>
									<th scope="row">Desafios Matematicos</th>
									<td></td>
									<td>X</td>
									<td></td>
									<td>X</td>
									<td>X</td>
								</tr>
								<tr>
									<th scope="row">Español</th>
									<td>X</td>
									<td></td>
									<td>X</td>
									<td></td>
									<td>X</td>
								</tr>
								<tr>
									<th scope="row">Historia</th>
									<td></td>
									<td>X</td>
									<td>x</td>
									<td>X</td>
									<td></td>
								</tr>
								<tr>
									<th scope="row">Geografia</th>
									<td>X</td>
									<td></td>
									<td>X</td>
									<td></td>
									<td>X</td>
								</tr>
								<tr>
									<th scope="row">Educacion Artistica</th>
									<td>X</td>
									<td>X</td>
									<td></td>
									<td>X</td>
									<td></td>
								</tr>
							</tbody>
						</table>
					</div>
				</div>
			</div>
		</div>

		<div class="col-12 col-lg-4 tareas">
			<h2 class="titulo">Tareas</h2>
			<p class="nombre">No se han asignado tareas todavia.</p>
		</div>

		<div class="col-12 col-lg-4 progreso">
			<h2 class="titulo">Progreso de avance de evaluación</h2>

			<!--Progress bar-->
			<p class="label">Lengua Materna. Español. Lecturas</p>
			<div class="progress">
				<div class="progress-bar" style="width: 75%">75%</div>
			</div>
			<p class="label">Matematicas</p>
			<div class="progress">
				<div class="progress-bar" style="width: 50%">50%</div>
			</div>
			<p class="label">Conocimiento del medio</p>
			<div class="progress">
				<div class="progress-bar" style="width: 25%">25%</div>
			</div>
			<p class="label">Formación civica y ética</p>
			<div class="progress">
				<div class="progress-bar" style="width: 0%">0%</div>
			</div>
		</div>

	</div>

	<div class="row contacto justify-content-center">
		<div class="col-12 col-lg-8">
			<h2 class="titulo">Contacto</h2>
			<form action="" class="formulario">
				<div class="form-group row">
					<div class="col-6 col-md-6">
						<input type="text" name="" id="nombre" placeholder="Nombre">
					</div>
					<div class="col-6 col-md-6">
						<input type="email" name="" id="correo" placeholder="Correo">
					</div>
				</div>

				<textarea name="" id="" placeholder="Recomendaciones, sugerencias, comentarios, etc."></textarea>
				<div class="form-group d-flex justify-content-center">
					<input type="submit" class="boton" value="Enviar">
				</div>	
			</form>
		</div>
	</div>
</main>

<footer>
	<div class="container">
		<!--Redes Sociales-->
		<div class="row redes-sociales justify-content-center">
			<div class="col-auto">
				<a href="https://www.twitter.com" class="icono icon-twitter-circled twitter"></a>
				<a href="https://www.facebook.com" class="icono icon-facebook facebook"></a>
				<a href="https://www.youtube.com" class="icono icon-youtube-play youtube"></a>
				<a href="https://www.instagram.com" class="icono icon-instagram instagram"></a>
			</div>
		</div>
	</div>
	<div class="row contador justify-content-auto">
		<div class="col-4 col-md-4">
			<p class="contador-texto bg-dark text-white"><script type="text/javascript">
				var ran
				ran = Math.round(Math.random()*50000)
				document.write("Usted es el visitante " + ran + ".")
			</script></p>
		</div>
	</div>
</footer>

<script src="https://code.jquery.com/jquery-3.2.1.slim.min.js" integrity="sha384-KJ3o2DKtIkvYIK3UENzmM7KCkRr/rE9/Qpg6aAZGJwFDMVNA/GpGFF93hXpG5KkN" crossorigin="anonymous"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.12.9/umd/popper.min.js" integrity="sha384-ApNbgh9B+Y1QKtv3Rn7W3mgPxhU9K/ScQsAP7hUibX39j7fakFPskvXusvfa0b4Q" crossorigin="anonymous"></script>
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0/js/bootstrap.min.js" integrity="sha384-JZR6Spejh4U02d8jOt6vLEHfe/JQGiRRSQQxSfFWpi1MquVdAyjUar5+76PVCmYl" crossorigin="anonymous"></script>
<script src="js/scripts.js"></script>


</body>
</html>