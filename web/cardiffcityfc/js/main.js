// JScript File
/*var siteAnswer = false;
function siteNotCompleted()
{
    var hasAnswered = siteAnswer;
    if(!hasAnswered)
    {
	var answer = confirm("Siden du besøker, er ikke ferdig ennå. Er du sikker på at du vil fortsette?");
	if(answer)
	{
	    alert("ja");
	    hasAnswered = true;
	}
	else
	{
	    hasAnswered = true;
	    alert("nei");
	    try
	    {
		history.back(1);
	    }
	    catch(e)
	    {
		alert(e);
	    }
	}
    }
    }*/

function disableselect(e)
{
	return false;
} 
function reEnable()
{
	return true;
} 
//if IE4+
document.onselectstart=new Function ("return false");
//if NS6
if (window.sidebar)
{
	document.onmousedown=disableselect;
	document.onclick=reEnable;
}
function noRightClick() 
{
	if (event.button==2)
		alert("Copyright 2005-2008 Anders. You are not allowed to copy anything from this site\n\n\nKopiering er ikke tillatt");
}
document.onmousedown=noRightClick;

