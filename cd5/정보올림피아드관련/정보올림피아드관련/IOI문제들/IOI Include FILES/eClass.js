var timer;
var stimer;
var totalAction = 0;
Action = new Array();
curStatus = 0;
preNullAvi = true;
var startActionTime = 0;
var pagePos;

function setActionArray(index, div, rm, preplay, time)
{
        this.index = index;
        this.div = div;
        this.rm = rm;
        this.preplay = preplay
        this.time = time;
}

function setDataBase(index, div, rm, preplay, time) { 
        Action[totalAction] = new setActionArray(index, div, rm, preplay, time);
        totalAction++;
}

function ActionTimer()
{
	stimer = setTimeout("ActionTimer()", 1000);
	startActionTime++;
}

function initText()
{
        for(i=0; i < totalAction; i++)
        {
                d = Action[i].div;

                if(document.layers) //넷스케이프용
                        document.layers[d].background = "white";
                else   //익스플로러용
                        document.all[d].style.background = "white";
        }
}

function ActiveText(str, avi, prePlay)
{
        initText();

        if(prePlay=="stop")
                top.vod.pl_video.DoStop();

        if(avi!=null)
	{
                top.vod.pl_video.SetSource(avi);
        	top.vod.pl_video.DoPlay();
		preNullAvi = false;
	}
	else
	{
		if(!preNullAvi)
		{
			top.vod.pl_video.SetSource("avi/algorithm.rm");
        		top.vod.pl_video.DoPlay();
			preNullAvi = true;
		}
	}

	if(str!=null)
	{
        	if(document.layers) //넷스케이프용
		{
                	document.layers[str].background = "#909Df0";
		}
        	else   //익스플로러용
		{
                	document.all[str].style.background = "#909Df0";
		}
	}

	startActionTime=0;
	ActionTimer();
}

function NextAction()
{
        if(curStatus >= totalAction) 
        {
                clearTimeout(timer);
                initText();
		curStatus = totalAction - 1;
        }
        else
        {
		if(Action[curStatus].preplay != "ani")
		{
                	ActiveText(Action[curStatus].div, Action[curStatus].rm, Action[curStatus].preplay);

			
                	timer = setTimeout("NextAction()", Action[curStatus].time);
		}
		else
		{
			var rtn = confirm('애니메이션을 보시겠습니까?'); 

			if (rtn == 1) 
				open(Action[curStatus].rm, "ani", "toolbar=0,location=0,directories=0,status=0,menubar=0");
			else
			{
                		timer = setTimeout("NextAction()", Action[curStatus].time);
			}
		}

                curStatus++;
        }
}

function rewind()
{
	stat = top.vod.pl_video.GetPlayState();

	if(stat==0 || stat==4)
	{
		if(curStatus)
		{
			curStatus--;
        		NextAction()
		}
	}
	else if(stat==3)
	{
		top.vod.pl_video.DoStop();
        	clearTimeout(timer);

		if(curStatus)
		{
			curStatus--;
        		NextAction()
		}
	}
}

function play()
{
	stat = top.vod.pl_video.GetPlayState();

	if(stat==0) // stopped
	{
        	NextAction();
	}
	else if(stat==4) // Paused
	{
		top.vod.pl_video.DoPlayPause();
        	timer = setTimeout("NextAction()", 
				   Action[curStatus].time-startActionTime);
		curStatus++;
	}
}

function pause()
{
	stat = top.vod.pl_video.GetPlayState();

	if(stat==3)
	{
		top.vod.pl_video.DoPause();
        	clearTimeout(timer);
		clearTimeout(stimer);
		if(curStatus) curStatus--;
	}
}

function stop()
{
	stat = top.vod.pl_video.GetPlayState();

	if(stat==3)
	{
		if(curStatus) curStatus--;
        	top.vod.pl_video.DoStop();
        	clearTimeout(timer);
	}
	else(stat==4)
	{
        	top.vod.pl_video.DoStop();
	}
}

function front()
{
	stat = top.vod.pl_video.GetPlayState();

	if(stat==0 || stat==4)
	{
		if(curStatus<totalAction)
		{
			curStatus++;
        		NextAction()
		}
	}
	else if(stat==3)
	{
		top.vod.pl_video.DoStop();
        	clearTimeout(timer);
        	NextAction()
	}
}


function play_stop()
{
        top.vod.pl_video.DoStop();
        clearTimeout(timer);
}

function faq(page)
{
/*
	top.qna.location = "faq.html";
 	f = top.tab.document;

	f.writeln('<html>');
	f.writeln('<head>');
	f.writeln('</head>');

	f.writeln('<body topmargin=0 leftmargin=0 marginwidth=0 marginheight=0 bgcolor=ffffff>');

	f.writeln('<table WIDTH="100%" height="100%" border=0 cellpadding=0 cellspacing=0>');
	f.writeln('<tr>');
	f.writeln('<td><img src="d:/work/BACktrack/../images/faq_select.gif" border="0" usemap="#ImageMap1">');
	f.writeln('</td>');
	f.writeln('</table>');
	f.writeln('<map name="ImageMap1">');

	f.write('<area shape="rect" coords="40, 4, 91, 20" onClick=\"window.open(\'http://pl.changwon.ac.kr/jsboard/list.php3?table=algorithm\', \'new\', \'toolbar=1, location=0, directories=0, status=0, menubar=0, scrollbars=1, resizable=1, copyhistory=no, width=750, height=500\'\)\"');
*/


/*
	f.write('onClick=\"window.open(\'http://pl.changwon.ac.kr/jsboard/list.php3?table=algorithm\', \'new\', \'toolbar=no,location=no,directories=no,status=no,menubar=no,scrollbars=auto, resizable=yes,copyhistory=no,width=600, height=600\'\)\"');
	f.write(' onClick=\"top.main.qna(\'pl.changwon.ac.kr/eClass/qna/Wcc481d077d95e.html');

*/
/*

	f.write(page);
	f.write('\');\">');
	f.writeln('</map>');
	f.writeln('</body>');
	f.writeln('</html>');
	f.close();
*/

}

function qna(url)
{
/*
	top.qna.location = url;
        f = top.tab.document;

        f.writeln('<html>');
        f.writeln('<head>');
        f.writeln('</head>');

        f.writeln('<body topmargin=0 leftmargin=0 marginwidth=0 marginheight=0 bgcolor=ffffff>');

        f.writeln('<table WIDTH="100%" height="100%" border=0 cellpadding=0 cellspacing=0>');
        f.writeln('<tr>');
	f.writeln('<td><img src="d:/work/BACktrack/../images/qna_select.gif" border="0" usemap="#ImageMap1">');
        f.writeln('</td>');

        f.writeln('</table>');
	f.writeln('<map name="ImageMap1">');
	f.write('<area shape="rect" coords="0, 4, 41, 20" href=http://pl.changwon.ac.kr/jsboard/list.php3?table=algorithm target=_blink ');
	f.writeln(' onClick="top.main.faq(top.main.pagePos);">');
	f.writeln('</map>');
        f.writeln('</body>');
        f.writeln('</html>');
        f.close();
*/
}
