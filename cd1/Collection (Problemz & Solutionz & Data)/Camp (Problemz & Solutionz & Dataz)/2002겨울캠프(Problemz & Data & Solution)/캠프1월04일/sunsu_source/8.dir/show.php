<html>
<head> <title>���������ø��ǾƵ� ������ ����</title> </head>

<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0" oncontextmenu="return false" onselectstart="return false" ondragstart="return false">

<?
$curdir=exec( "/bin/pwd" );
$kkk=basename($curdir);
$V_problem=strtok($kkk, "." );
echo "<img src='./$V_problem.jpg' >\n";
?>
<pre>
 ���� ������ �ذ��� �� �ִ� �ҽ��� �ۼ��Ͽ� �����ʽÿ�.
 �������� �ۼ��� �ҽ��� �ڵ����� ������ �˴ϴ�. �ҽ��� Ȯ���ڰ� c/cpp/pas/bas�� ��츸 ä���� �����մϴ�.
 ������ �л��� ������!~

���ǻ���:
 ������ȸ���� �����Ϸ��� Visual C, Visual Basic, Delphi�� �ٲ�����ϴ�.
 32bit�����Ϸ��̱� ������ int���� long���� ���̰� ������, �迭�� ũ�⵵ ũ�� �Ҵ��� �� �ֽ��ϴ�.
 
</pre>
</body>
<br><hr>

<?
echo "<FORM ENCTYPE=\"multipart/form-data\" ACTION=\"$V_problem.php\" METHOD=POST>\n";
?>
<INPUT TYPE="hidden" name="MAX_FILE_SIZE" value="1000000">
���� ������ �̸�: <INPUT NAME="userfile" TYPE="file">
<INPUT TYPE="submit" VALUE="������">
<br><br>
</FORM>
</html>
