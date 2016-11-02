// copyright by  www.visualirc.com

browser_name = navigator.appName;
browser_version = parseFloat(navigator.appVersion); 

roll = 'false';

if (browser_name == "Netscape" && browser_version >= 3.0) { roll = 'true'; }
else if (browser_name == "Microsoft Internet Explorer" && browser_version >= 3.0) { roll = 'true'; }
else { roll = 'false'; }


function vin(str,eg) {
	if ( eg == 1 ) {
		msover(ref);
	}
	da(str);
}

function vout(eg) {
	if ( eg == 1 ) {
		msout();
	}
	nd();
}

function msover(ref) { 
        if (roll == 'true') {
                document.images["s"].src = eval(ref + ".src"); 
        }
}
function msout() { 
        if (roll == 'true') { 
                document.images["s"].src = st.src;
        } 
}


ns4 = (document.layers)? true:false
ie4 = (document.all)? true:false

// 1999 05,17 Insert
if (ie4) {
	if (navigator.userAgent.indexOf('MSIE 5')>0) {
		ie5 = true;
	} else {
		ie5 = false; }
} else {
	ie5 = false;
}

var width = "300";
var backcolor = "#744069";
var border = "2";
var fcolor = "#b3fdce";
var textcolor = "#74206b";
var offsetx = 10;
var offsety = 5;

var x = 0;
var y = 0;
var snow = 0;
var sw = 0;
var cnt = 0;
	
if ( (ns4) || (ie4) ) {
	if (ns4) over = document.overDiv
	if (ie4) over = overDiv.style
	document.onmousemove = mouseMove
	if (ns4) document.captureEvents(Event.MOUSEMOVE)
}


function da(html_str) {
	txt = "<TABLE WIDTH="+width+" BORDER=0 CELLPADDING="+border+" CELLSPACING=0 BGCOLOR=\""+backcolor+"\"><TR><TD align=left valign=center ><FONT  COLOR=\""+fcolor+"\" SIZE=\"2\" face=\"±¼¸²\"><B> µµ¿ò¸» </B></FONT><TABLE WIDTH=100% BORDER=0 CELLPADDING=3 CELLSPACING=0 BGCOLOR=\""+fcolor+"\"><TR><TD ><FONT COLOR=\"#"+textcolor+"\" SIZE=\"2\" face=\"±¼¸²\">"+ html_str +"</FONT></TD></TR></TABLE></TD></TR></TABLE>"
	disp(txt);
}

function disp(text) {
	if ( (ns4) || (ie4) ) {
		if ( (snow == 0) && (sw == 0) ) 	{
			moveTo(over,x+offsetx,y+offsety);
			layerWrite(text);
			showObject(over);
			snow = 1;
		}
	} else {
		status = text;
	}
}

function nd() {
	if ( cnt >= 1 ) { sw = 0 };
	if ( (ns4) || (ie4) ) {
		if ( sw == 0 ) {
			snow = 0;
			hideObject(over);
		} else {
			cnt++;
		}
	} else {
		status = "";
	}
}

function mouseMove(e) {
        if (ns4) {x=e.pageX; y=e.pageY;}
        if (ie4) {x=event.x; y=event.y;} // 1999/05/17 ¼öÁ¤
        if (ie5) {x=event.x+document.body.scrollLeft; y=event.y+document.body.scrollTop;}
        if (snow) {moveTo(over,x+offsetx,y+offsety)};
}



// Modified DynDuo functions by Dan Steinman

function showObject(obj) {
        if (ns4) obj.visibility = "show"
        else if (ie4) obj.visibility = "visible"
}

function hideObject(obj) {
        if (ns4) obj.visibility = "hide"
        else if (ie4) obj.visibility = "hidden"
}

function moveTo(obj,xL,yL) {
        obj.left = xL
        obj.top = yL
}

function layerWrite(txt) {
        if (ns4) {
                var lyr = document.overDiv.document
                lyr.open("text/html")
                lyr.write(txt)
                lyr.close()
        }
        else if (ie4) document.all["overDiv"].innerHTML = txt
}

// function by some netscape dude i think

function getCookieData(label)
{
var labelLen = label.length
var cLen = document.cookie.length
var i = 0
while (i < cLen) 
	{
	var j = i + labelLen
	if (document.cookie.substring(i,j) == label) 
		{
		var cEnd = document.cookie.indexOf(";",j)
		if (cEnd == -1)
			{
			cEnd = document.cookie.length
			}
		return unescape(document.cookie.substring(j+1,cEnd))
		}
	i++
	}
return ""
}
