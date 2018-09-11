var movie = [
	{
		title: "Ready Player One",
		rating: 5,
		hasWatched: false
	},
	{
		title: "Frozen",
		rating: 4.5,
		hasWatched: true
	},
	{
		title: "Tomb Raider",
		rating: 5,
		hasWatched: true
	},
	{
		title: "Les Miserables",
		rating: 3.5,
		hasWatched: true
	},
	{
		title: "The Phantom of the Opera",
		rating: 3,
		hasWatched: false
	},
	{
		title: "Olsenbanden jr. går under vann",
		rating: 2,
		hasWatched: true
	}
];

function iterate(arr)
{
	for(var i = 0; i < arr.length; i++)
	{
		if(!arr[i].hasWatched)
			console.log("Du har ikke sett filmen \"" + arr[i].title + "\" - " + arr[i].rating + " stjerner.");
		else
			console.log("Du har sett filmen \"" + arr[i].title + "\" - " + arr[i].rating + " stjerner.");
	}
}

iterate(movie);