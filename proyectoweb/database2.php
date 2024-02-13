<?php

$server = 'localhost';
$username = 'root';
$password = '';
$database = 'basedatos';

try {
  $conn = new PDO("mysql:host=$server;dbname=$database;", $username, $password, $rol_id);
} catch (PDOException $e) {
  die('Connection Failed: ' . $e->getMessage());
}

?>