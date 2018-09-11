var alder = prompt("Hvor gammel er du? Svaret skal angis i antall år.");
/*
Kunne alltids ha lagt inn en sjekk for å sjekke om brukeren 
angir et realistisk antall år, f. eks. mellom 0 og 130,
men hopper over det nå. Går heller rett i gang med å regne ut
antall dager. simpleAnswer tar ikke høyde for skuddår.
*/
var simpleAnswer = alder * 365;

// Runder antall skuddår opp til nærmeste heltall:
var antSkuddAar = Math.ceil(alder/4);

// Regner antall år som ikke er skuddår:
var ingenSkuddAar = alder-antSkuddAar;

// Ganger svaret over med 365 for å få antall dager
var dagerIVanligAar = ingenSkuddAar*365;

/*
Dager i skuddår: Ganger antall skuddår med 366.
*/
var dagerISkuddAar = antSkuddAar*366;

// Legger antall dager i vanlig år 
// sammen med antall dager i skuddår:
var ans = dagerIVanligAar + dagerISkuddAar;

// En kraftig forenkling:
var noyaktigAntallDager = Math.ceil(alder*365.25);

// Skriver ut begge svarene:
console.log(simpleAnswer); // Forenklet svar, se kommentar over.
console.log(ans); // Nøyaktig svar, inkl skuddårsdager
console.log(noyaktigAntallDager);