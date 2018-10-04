function average(arr)
{
	var n = 0, total = 0;
	while(n < arr.length){
		total+=arr[n];
		n++;
	}
	return Math.round(total/n);
}

var scores = [90, 98, 100, 86, 94];
console.log(average(scores));

var secondScores = [40, 65, 77, 82, 80, 54, 73, 63, 95, 49];
console.log(average(secondScores));