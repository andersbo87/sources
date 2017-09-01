/*
Denne filen har kode som er hentet fra:
https://www.w3schools.com/nodejs/nodejs_mysql.asp
*/
var mysql = require('mysql');
var con = mysql.createConnection({
    host: "localhost",
    user: "root",
    password: "KlaanD87",
    database: "andersbo"
});

con.connect(function(err) {
    if(err) throw err;
    console.log("Koblet til!");
    sql = "CREATE TABLE IF NOT EXISTS kunde(navn varchar(40), adresse varchar(100))";
    con.query(sql, function(err, result){
	if(err) throw err;
	console.log("Tabellen ble opprettet.");
    });
    sql = "INSERT INTO kunde(navn, adresse) VALUES('Ola Nordmann', 'Norgeveien 1A')";
    con.query(sql, function(err, result){
	if(err) throw err;
	console.log("Satte inn én rad.");
    });
    con.query("SELECT * FROM kunde", function(err, result, fields){
	if(err) throw err;
	console.log(result);
    });
});
process._getActiveRequests();
process._getActiveHandles();
process.exitCode= 0;
