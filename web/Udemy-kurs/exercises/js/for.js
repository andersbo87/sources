document.write("Oppgave 1: ");
for(var i = -10; i <= 19; i++)
	document.write(i + " ");

document.write("<br>Oppgave 2: ");
for(var i = 10; i <= 40; i++){
	if(i % 2 === 0)
		document.write(i + " ");
}


document.write("<br>Oppgave 3: ");
for(var i = 300; i <= 333; i++){
	if(i % 2 !== 0)
		document.write(i + " ");
}

document.write("<br>Oppgave 4: ");
for (i = 5; i <= 50; i++){
	if(i % 5 === 0 && i % 3 === 0)
		document.write(i + " ");
}