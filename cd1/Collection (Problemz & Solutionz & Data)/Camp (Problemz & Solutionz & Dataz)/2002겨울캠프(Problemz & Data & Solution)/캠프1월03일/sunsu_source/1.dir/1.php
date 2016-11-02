<?

######################################################
# Variables from mother php program
#
# $userfile      : 시스템내에 존재하는 upload한 파일 
# $userfile_name : upload한 파일 
# $userfile_size : upload한 파일 사이즈
# $userfile_type : upload한 파일 타입
######################################################

// For debugging echo "시스템 임시파일   : $userfile<br>";
echo "<br>평가 시스템으로 업로드된 파일이름 : $userfile_name(size:${userfile_size}bytes, type:$userfile_type)<br>\n";

flush();

######################################################
# Variables defined this php program
#
# $V_problem     : 문제의 이름
# $V_workingdir  : posix_getpid()
# $V_extension   : upload한 파일의 확장자 
# $tok           : 토큰 분리를 위해 사용한 임시 변수
# $V_score       : 평가 점수
# $V_ret         : 함수 실행 후 리턴값을 보관
# $V_datadir     : 데이터가 존제하는 곳
###################################################### 

$curdir=exec( "/bin/pwd" ); 
$kkk=basename($curdir);
$V_problem=strtok($kkk, "." );

# $V_problem="%Ryu-Geun-Moon%";
$V_workingdir=posix_getpid();
$tok=strtok($userfile_name, "." );
while ($tok) {
	$V_extension=strtolower($tok);
	$tok=strtok(".");
	# echo "$V_extension ";
}
$V_score=0;
$V_datadir="rgm.data";
$V_sourcedir="Source.rgm";
/* For debugging
echo "V_problem    :$V_problem<br>";
echo "V_workingdir :$V_workingdir<br>";
echo "V_extension  :$V_extension<br>";
echo "<br>";
*/


#####################################################
# Checking if file-uploading is OK
#####################################################

if ( $userfile_size == 0 ) { 
	echo "<br>파일 업로드가 성공적으로 수행되지 못했습니다.<br>";
	exit; 
} else {
	echo "<br>파일 업로드가 성공적으로 수행되었습니다.<br>";
}

flush();

if ( !chdir ( "$V_sourcedir" ) ) exit;

passthru ( "/bin/cp $userfile $userfile_name 2>&1", $V_ret );
if ( $V_ret != 0 ) exit;

passthru ("/bin/chmod 000 $userfile_name", $V_ret );
if ( $V_ret != 0 ) exit;

echo "<br>소스가 성공적으로 제출되었습니다. 수고했습니다.<br>";
?>
