<?php

?>

<!DOCTYPE html>            
<html>                  
<head>                 
    <meta charset="UTF-8">      
    <meta name="author" content="Erick Saúl Quezada Almazán y Johan Ali Rojas Hernandez">   
    <link rel="stylesheet" type="text/css" href="normalize.css">
    <title>                 
        Plataforma (home)                
    </title>   
    <style>

        html{
            font-size: 62.5%;
        }

        body{
            font-family: 'Lato', sans-serif; /*El estilo de tipografia que se esta utilizando en todo el texto*/
            font-size: 1.6rem; 
            margin: 0;
            padding: 0;
            background: url(bg.jpeg) no-repeat center top;
            background-size: cover;
            font-family: sans-serif;
            height: 100vh;
        }
        .site-header.inicio{
            background-position: center center;
        }
        .main{
            padding-top: 20rem;
        }
        .contenedor{
            max-width: 120rem; /*rem se utiliza para escalar todos los dispositivos que estan en el mercado*/
            margin-left: auto; 
            margin-right: auto;
        }
        .contenido-header{
            display: flex;
            flex-direction: column;
            position: fixed;
            left: 0;
            top:0;
            width: 100%;
        }
        .barra{
            font-family: 'Lato', sans-serif;
            display:flex;
            background: white;
            justify-content: space-between;
            align-items: center;
            padding-top: 2rem;
            position: fixed;
            left: 0;
            top:0;
            width: 100%;

        }
        .navegacion a{
            color: black;
            text-decoration: none;
            font-size: 2rem;
            margin-right:2rem;
            text-transform: uppercase;
            text-decoration: none;
            transition: all .3s;
        }

        .navegacion a:hover {
            color:#0E8C9B;
        }
        .navegacion a:last-child{
            border: 2px solid #0E8C9B;
        }
    </style>   
</head> 

<body>        
    <header class="site-header inicio">
        <div class="contenedor contenido-header">
            <div class="barra">
                <a href="https://www.escom.ipn.mx/">
                   <img src="escom.PNG" width="200" height="120" alt="Logotipo"> 
               </a>
               <nav class="navegacion">
                   <a href="login2.php">Iniciar Sesión</a> 
                   <a href="Registro.php">Registrate</a>
               </nav>
           </div>
       </div>
   </header>  
   <main class="main">   
    <div style="text-align: center; font-family:'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif;">          
    </div> 
    <h2>                
        <map name="PagPrinc">                
        </map>
        <div align="center">
            <h1>            
                <u>BIENVENIDO A "MI CURSO EN LÍNEA (BÁSICO I)</u>
            </h1> 
        </div>
        <br>
        <br>
        <br>
        <br>
        <br>
        <br>
        <br>
        <br>
        <br>
        <br>
        <br>
        <br>
        <!--Boton de cuenta-->
    </main> 
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
