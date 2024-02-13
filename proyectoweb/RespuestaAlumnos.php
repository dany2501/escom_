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
        Respuesta Alumnos
    </title>
    <script>
        function carga() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("tabla").innerHTML = this.responseText;
                }
            };
            xhttp.open("GET", "carga/getrespuestas.php", true);
            xhttp.send();
        }
    </script>
</head>

<body onload="carga()">
    <div style="text-align: center; font-family: 'Gill Sans', 'Gill Sans MT', Calibri, 'Trebuchet MS', sans-serif;">
        <h1>
            <u>RESPUESTA ALUMNOS</u>
        </h1>
    </div>
    <h2 style="background-color: rgb(127, 255, 212);">
        <img src="logo.jpg" alt="página_principal">
        <map name="PagPrinc"></map>

        <!-- Para Opcion de Inicio -->
        <div style="text-align: right;" class="enlace" role="link">
            <a href="cerrarsesion.php" style="text-align: start; font-size: 30px;">Cerrar Sesion</a>
    </h2> 
<!-- //////////////////////////////////////////////////////////////////////////////////////////// -->
        <table>
            <colgroup>
                <col>
                <col>
            </colgroup>
            <thead>
                <tr>
                    <th>NOMBRE ALUMNO</th>
                    <th>No ACTIVIDAD</th>
                    <th>NOMBRE ACTIVIDAD</th>
                    <th>RESPUESTAS</th>
                </tr>
            </thead>
            <tbody id = "tabla">
<!-- AJAX MAGICO -->
            </tbody>
        </table>
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