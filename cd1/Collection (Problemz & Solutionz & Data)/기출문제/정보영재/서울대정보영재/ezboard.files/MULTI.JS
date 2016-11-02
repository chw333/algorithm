function MultiSubmit( form_name, input_name, input_value )
{

  var   i, max = 0, form = document.forms[form_name].selnum;

  if( !form ) return;
  if( form.length >= 0 )
  {
    for( i = 0; i < form.length; i++ )
    {
      if( form[i].type != "checkbox" ) continue;
      if( form[i].checked )
        max++;
    }
  }
  else
  {
    if( form.checked )
      max++;
  }
  if( !max ) {  alert('Select one article at least!');  return; }
  document.forms[form_name][input_name].value = input_value;
  document.forms[form_name].submit();
}

function SelectAll()
{
  var   i, form = document.forms["SelForm"].selnum;

  if( !form ) return;
  if( form.length >= 0 )
  {
    for( i = 0; i < form.length; i++ )
    {
      if( form[i].type != "checkbox" ) continue;
      form[i].checked = !form[i].checked;
    }
  }
  else
    form.checked = !form.checked;
}

function _popwin( target, furl, fwidth, fheight, fopt )
{
  var fsbar   = "yes";
  var fresize = "yes";
  var fstatus = "1";

  if( !fwidth ) fwidth = 500;
  if( !fheight) fheight= 400;
  if( fopt )
  {
    fsbar   = "no";
    fresize = "no";
    fstatus = "0";
  }
  window.open( furl, target, 'width=' + fwidth + ',height=' + fheight + ',resizable=' + fresize + ',scrollbars=' + fsbar + ',status=' + fstatus );
}
/*
function RemoteWindow( url )
{
//  var subtarget = window.opener.href;
//  window.open( url, subtarget,'width=500,height=400,resizable=yes,scrollbars=yes,status=1');
  _popwin( "PopWin", url )
}

function EzConfirm( aform, name, msg )
{
  if( !aform[name].value && !confirm( msg ) )
    return  false;
  aform.submit();
  return  true;
}
*/