<?php
?>

<!DOCTYPE html>            
<html>                  
    <head>                 
        <meta charset="UTF-8">      
        <meta name="author" content="Erick Saúl Quezada Almazán">                   
        <title>                 
            Avance de Administradores              
		</title>      
	</head> 

    <body>              
        <div style="text-align: center; font-family:'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif;">
            <h1>            
                <u>AVANCES DEL ADMINISTRADOR</u>
			</h1>           
		</div> 
		<h2 style="background-color: rgb(127, 255, 212);">                
            <img src="logo.jpg" alt="logo_sitio"alt="página_principal">
            <map name="PagPrinc">                
            </map>
        <!--Boton de cuenta-->
            <div style="text-align:right" class="enlace" role="link">
                <a href="cerrarsesion.php" style="text-align: right; font-size: 30px;">Cerrar Sesión</a>
            </div>
        </h2>       
    <!--Cuerpo: Imágenes de selección (Alumnos/Profesores)-->
    <h2 style="text-align: center;" >Seleccione una opción:</h2>
		<br>
        <div align="center">
		<img src="ALUMNO.jpg" alt="computadora" align="center" usemap="#class" width="732" height="392">
        </div>
            <map name="class">
			<area shape="rect" coords="6,10,306,381" alt="Alumno" href="Alumno.html">
			<area shape="rect" coords="423,11,718,384" alt="Profe" href="Profesor.html">
		</map>
    </body>
    <!--Footer: Botones de contacto (FB/TWITTER/WA/E-MAIL)-->
	<footer style="background-color: aquamarine;">
        <p>
            <h3>En caso de alguna duda, contáctenos:</h3>
        </p>
        <button class="enlace" role="link" onclick="window.location='https://www.facebook.com/ericksaul.quezada/'">
            FACEBOOK
        </button>
        
        <button class="enlace" role="link" onclick="window.location='https://twitter.com'">
            TWITTER
        </button>
        
        <button class="enlace" role="link" onclick="window.location='https://chat.whatsapp.com/GCbwBkZFzOs96cDYiX7LCf'">
            WHATSAPP
        </button>
        <a href="mailto:saul_9527@hotmail.com">Mándanos un e-mail!</a>
</html>
