document.write("Oppgave 1: ");
var i = -10;
while(i <= 19){
	document.write(i + " ");
	++i;
}

document.write("<br>Oppgave 2: ");
i = 10;
while(i <= 40){
	if(i % 2 === 0)
		document.write(i + " ");

	i++;
}

document.write("<br>Oppgave 3: ");
i = 300;
while(i <= 333){
	if(i % 2 !== 0)
		document.write(i + " ");

	i++;
}

document.write("<br>Oppgave 4: ");
i = 5;
while(i <= 50){
	if(i % 5 === 0 && i % 3 === 0)
		document.write(i + " ");

	i++;
}