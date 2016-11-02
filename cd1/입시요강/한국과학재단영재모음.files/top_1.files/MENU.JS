var show_submenu = false;


function MM_preloadImages() { //v2.0
  if (document.images) {
    var imgFiles = MM_preloadImages.arguments;
    if (document.preloadArray==null) document.preloadArray = new Array();
    var i = document.preloadArray.length;
    with (document) for (var j=0; j<imgFiles.length; j++) if (imgFiles[j].charAt(0)!="#"){
      preloadArray[i] = new Image;
      preloadArray[i++].src = imgFiles[j];
  } }
}



function MM_swapImgRestore_mainmenu() { //v2.0
  if (document.MM_swapImgData_mainmenu != null){
    for (var i=0; i<(document.MM_swapImgData_mainmenu.length-1); i+=2)
      document.MM_swapImgData_mainmenu[i].src = document.MM_swapImgData_mainmenu[i+1];
  }        
}

function MM_swapImage_mainmenu() { //v2.0
  var i,j=0,objStr,obj,swapArray=new Array,oldArray=document.MM_swapImgData_mainmenu;
  for (i=0; i < (MM_swapImage_mainmenu.arguments.length-2); i+=3) {
    objStr = MM_swapImage_mainmenu.arguments[(navigator.appName == 'Netscape')?i:i+1];
    if ((objStr.indexOf('document.layers[')==0 && document.layers==null) ||
        (objStr.indexOf('document.all[')   ==0 && document.all   ==null))
      objStr = 'document'+objStr.substring(objStr.lastIndexOf('.'),objStr.length);
    obj = eval(objStr);
    if (obj != null) {
      swapArray[j++] = obj;
      swapArray[j++] = (oldArray==null || oldArray[j-1]!=obj)?obj.src:oldArray[j];
      obj.src = MM_swapImage_mainmenu.arguments[i+2];
  } }
  document.MM_swapImgData_mainmenu = swapArray; //used for restore
}

function MM_showHideLayers() { //v2.0
  var i, visStr, args, theObj;
  args = MM_showHideLayers.arguments;
  for (i=0; i<(args.length-2); i+=3) { //with arg triples (objNS,objIE,visStr)
    visStr   = args[i+2];
    if (navigator.appName == 'Netscape' && document.layers != null) {
      theObj = eval(args[i]);
      	if (theObj){ 
		theObj.visibility = visStr;
		if(visStr == 'show')
			show_submenu = true;
		else
			show_submenu = false;
	}
    } else if (document.all != null) { //IE
      	if (visStr == 'show'){
		 visStr = 'visible'; //convert vals
		show_submenu = true; 
	}
      	if (visStr == 'hide') {
		visStr = 'hidden';
		show_submenu = false;
	}
      theObj = eval(args[i+1]);
      if (theObj) theObj.style.visibility = visStr;
  } }
}

	function hidehighlight(){
		if(show_submenu == false)
			MM_swapImgRestore_mainmenu();
	}
	
	function netscapehider(){
		window.document.foundationsubmenu.visibility = "hidden";
		window.document.worksubmenu.visibility = "hidden";
		window.document.researchsubmenu.visibility = "hidden";
		window.document.bbssubmenu.visibility = "hidden";
		window.document.linksubmenu.visibility = "hidden";
		show_submenu = false;
		hidehighlight();
	}
	
	function iehider(){
		if(window.event.toElement && window.event.toElement.className != "menu"){
			document.all.foundationsubmenu.style.visibility = "hidden";
			document.all.worksubmenu.style.visibility = "hidden";
			document.all.researchsubmenu.style.visibility = "hidden";
			document.all.bbssubmenu.style.visibility = "hidden";
			document.all.linksubmenu.style.visibility = "hidden";
			show_submenu = false;
			hidehighlight();
		}
	}
	
