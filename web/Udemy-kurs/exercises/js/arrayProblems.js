// Oppgave 1
function printReverse(arr)
{
	for(var i = arr.length-1; i >= 0; i--)
		console.log(arr[i]);
}

// oppgave 2
function isUniform(arr){
	var res = arr[0];
	for(var i = 1; i < arr.length; i++){
		if(res !== arr[i]){
			return false;
		}
	}
	return true;
}

// Oppgave 3
function sumArray(arr)
{
	var sum = 0;
	for(var i = 0; i < arr.length; i++)
		sum+=arr[i];
	return sum;
}

// Oppgave 4
function max(arr)
{
	var highest = 0;
	for(var i = 0; i < arr.length; i++)
	{
		if(arr[i] > highest)
			highest = arr[i];
	}
	return highest;
}

console.log("Oppgave 1");
printReverse([0, 1, 2, 3, 4, 5, 6, 7, 8, 9]);
printReverse(["a", "b", "c", "d", "e", "f", "g", "h", "i", "j"]);

console.log("Oppgave 2");
console.log(isUniform([1,1,1,1]));
console.log(isUniform([1,2,1,1]));
console.log(isUniform(["p", "b", "a"]));
console.log(isUniform(["a", "a", "a"]));

console.log("Oppgave 3");
console.log(sumArray([1, 2, 3]));
console.log(sumArray([10, 3, 10, 4]));
console.log(sumArray([-5, 100]));

console.log("Oppgave 4");
console.log(max([1, 2, 3]));
console.log(max([10, 3, 10, 4]));
console.log(max([-5, 100]));