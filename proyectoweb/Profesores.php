<?php

?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="author" content="Jorge Bernardo Castelán Hidalgo">
    <title>
        Avance del Profesor
    </title>
    <!-- El codigo de estilo para las dos tablas esta en el archivo styles_boards.css -->
    <style>

        table{
            font-family:sans-serif;
            border: 4px solid darkblue;
            border-collapse: collapse;
            text-align: center;
            margin-left: auto;
            margin-right: auto;
            width: 90%;
            height: 300px;

        }

        caption{
            font-size: 2rem;
            font-weight: bold;
            margin-bottom: 1rem;
        }

        th,td{
            border: 2px solid darkblue;
            padding: 2.5rem;
        }

        tr:nth-child(4) td:nth-child(2){
            background-color: deepskyblue;
            letter-spacing: 90px;
            padding-left: 50px;
            text-transform: uppercase;
        }

        td:first-child,th,tfoot{
            background-color: deepskyblue;
        }

    </style>

</head>

<body>
    <div style="text-align: center; font-family: 'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif;">
        <h1>
            <u>AVANCES DEL PROFESOR</u>
        </h1>
    </div>
    <h2 style="background-color: rgb(127, 255, 212);">
        <img src="logo.jpg" alt="página_principal">
        <map name="PagPrinc"></map>

        <!-- Para Opcion de Inicio -->
        <div style="text-align: right;" class="enlace" role="link">
            <a href="cerrarsesion.php" style="text-align: start; font-size: 30px;">Cerrar Sesion</a>
    </h2> 
    <table>
        <caption>Datos de profesor</caption>
        <colgroup>
            <col>
            <col>
        </colgroup>
        <thead>
            <tr>
                <th>NOMBRES</th>
                <th>GRUPO</th>
                <th>NOMBRE DE USUARIO</th>
                <th>CONTRASEÑA</th>
            </tr>
        </thead>
        <tbody>
            <tr>
                <th>Profesor 01</th>
                <th></th>
                <th></th>
                <th></th>
            </tr>
            <tr>
                <th>Profesor 02</th>
                <th></th>
                <th></th>
                <th></th>
            </tr>
            <tr>
                <th>Profesor 03</th>
                <th></th>
                <th></th>
                <th></th>
            </tr>
            <tr>
                <th>Profesor NN</th>
                <th></th>
                <th></th>
                <th></th>
            </tr>
        </tbody>
    </table>
</body>
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
</footer>
</body>
</html>