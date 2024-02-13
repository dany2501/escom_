<!-- Autor: Ruiz Casimiro René Guillermo-->
<?php

?>
<!DOCTYPE html>
<html lang="en">
<head>
<style>
    footer{
    padding: 15px;
    width: 97%;
    margin: auto;
    position: fixed;

    bottom: 0;
    z-index: 1;
    background-color: rgb(127, 255, 212);
}

.centro{
    border: 2px solid green;
    overflow: auto;
    padding: 15%;
/*Cambiar el padding top y bottom para centrar*/
}

.b{
    height: 30px;
    display: block;
    border: 1px solid black;
    /**/
    margin: auto;
    margin-top: 20px;
    width: 40%;
}

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
};
/*----------------------------------------------------

.clearfix::after {
  content: "";
  clear: both;
  display: table;
}*/
</style>
    <title>
        Principal profesor
    </title>

</head>

<body>
    <div style="text-align: center; font-family: 'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif;">
        <h1>
            <u>PROFESOR</u>
        </h1>
    </div>
    <h2 style="background-color: rgb(127, 255, 212);">
        <img src="logo.jpg" alt="página_principal">
        <div style="text-align: right;" class="enlace" role="link">
            <a href="cerrarsesion.php" style="text-align: start; font-size: 30px;">Cerrar Sesion</a>
        </div>
    </h2>
<!-- //////////////////////////////////////////////////////////////////////////////////////////// -->
    <section class="centro">
            <button id = "b1" class="b" onclick="location.href='ListaAlumno.php'">Lista de alumnos</button>
            <button id = "b2" class="b" onclick="location.href='TrabajoAlumnos.php'">Trabajos</button>
            <button id = "b3" class="b" onclick="location.href='AreaAlumnos.php'">Asignar tarea</button>
            <button id = "b4" class="b" onclick="location.href='RespuestaAlumnos.php'">Consultar respuestas</button>
    </section>
<!-- //////////////////////////////////////////////////////////////////////////////////////////// -->
</body>
<footer>
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