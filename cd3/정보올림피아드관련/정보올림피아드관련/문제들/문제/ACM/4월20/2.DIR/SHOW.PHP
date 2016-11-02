<html>
<head> <title>월드정보올림피아드 강남점 문제</title> </head>

<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0" marginwidth="0" marginheight="0" oncontextmenu="return false" onselectstart="return false" ondragstart="return false">

<?
$curdir=exec( "/bin/pwd" );
$kkk=basename($curdir);
$V_problem=strtok($kkk, "." );
echo "<img src='./$V_problem.jpg' >\n";
?>
<pre>
 위의 문제를 해결할 수 있는 소스를 작성하여 보내십시오.
 여러분이 작성한 소스는 자동으로 컴파일 됩니다. 소스의 확장자가 c/cpp/pas/bas인 경우만 채점이 가능합니다.
 강남점 학생들 파이팅!~

주의사항:
 전국대회에서 컴파일러가 Visual C, Visual Basic, Delphi로 바뀌었습니다.
 32bit컴파일러이기 때문에 int형과 long형은 차이가 없으며, 배열의 크기도 크게 할당할 수 있습니다.
 
</pre>
</body>
<br><hr>

<?
echo "<FORM ENCTYPE=\"multipart/form-data\" ACTION=\"$V_problem.php\" METHOD=POST>\n";
?>
<INPUT TYPE="hidden" name="MAX_FILE_SIZE" value="1000000">
보낼 파일의 이름: <INPUT NAME="userfile" TYPE="file">
<INPUT TYPE="submit" VALUE="보내기">
<br><br>
</FORM>
</html>
