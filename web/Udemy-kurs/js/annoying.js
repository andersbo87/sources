while(true)
{
	var ans = prompt("Are we there yet?").toLowerCase();
	if (ans.localeCompare("yes") === 0 || ans.localeCompare("yeah") === 0)
	{
		alert("We made it!");
		break;
	}
	if(ans.includes("yes") || ans.includes("yeah"))
	{
		alert("We made it!");
		break;
	}
}