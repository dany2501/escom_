<?php
#Autor: Ruiz Casimiro René Guillermo
$conn = new mysqli("localhost", "root", "root", "basededatos");
	if($conn->connect_error) {
	exit('Could not connect');
}

$sql = "select Nombre, ActEntregadas, Calif from 'listaalumnos'";

$result = $conn -> query($sql);

if($result !== false && $result->num_rows > 0){
	while ($row = $result ->fetch_assoc()) {
		echo "<tr> <th>".$row["Nombre"]."</th> <th>".$row["ActEntregadas"]."</th> <th>".$row["Calif"]."</th> </tr>";
		#aquí va la fila de la tabla
	}
}
else{
	echo "<tr> <th>Sin registros</th> <th>.</th> <th>.</th> </tr>";
	#fila vacia
}

$conn->close();

?>