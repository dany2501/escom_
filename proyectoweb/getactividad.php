<?php
#Autor: Ruiz Casimiro René Guillermo
$conn = new mysqli("localhost", "root", "root", "basededatos");
	if($conn->connect_error) {
	exit('Could not connect');
}

$sql = "select fechap, nactividad, nombreactividad, pagina, fechaentrega from 'actividad'";

$result = $conn -> query($sql);

if($result !== false && $$result -> num_rows > 0){
	while ($row = $result ->fetch_assoc()) {
		echo "<tr> <th>".$row["fechap"]."</th> <th>".$row["nactividad"]."</th> <th>".$row["nombreactividad"]."</th> <th>".$row["pagina"]."</th> <th>".$row["fechaentrega"]."</th> </tr>";
		#aquí va la fila de la tabla
	}
}
else{
	echo "<tr> <th>Sin registros</th> <th>.</th> <th>.</th> <th>.</th> <th>.</th> </tr>";
	#fila vacia
}

$conn->close();

?>