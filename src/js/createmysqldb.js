/*
Koden i denne filen er hentet fra:
https://www.w3schools.com/nodejs/nodejs_mysql.asp
*/
var mysql = require('mysql');
var con = mysql.createConnection({
    host: "localhost",
    user: "root",
    password: "KlaanD87"
});

con.connect(function(err) {
    if(err) throw err;
    console.log("Koblet til!");
    con.query("CREATE DATABASE IF NOT EXISTS andersbo", function(err, result){
	if(err) throw err;
	console.log("Databasen ble opprettet.");
    });
});
