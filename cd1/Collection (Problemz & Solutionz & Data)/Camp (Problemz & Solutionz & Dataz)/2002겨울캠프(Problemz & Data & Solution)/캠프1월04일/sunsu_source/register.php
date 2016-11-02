<?

# Variables
# $userfile      : 시스템내에 존재하는 upload한 파일
# $userfile_name : upload한 파일
# $userfile_size : upload한 파일 사이즈
# $userfile_type : upload한 파일 타입

echo "<br>올려진 문제 파일 :$userfile_name(size:${userfile_size}bytes, type:$userfile_type)<br>";

# Variables
# $V_problem
# $V_extension
# $V_ret
# $V_datadir

$tok=strtok($userfile_name, "." );
$V_problem=$tok;
while ($tok) {
	$V_extension=strtolower($tok);
	$tok=strtok(".");
}

$V_datadir="rgm.data";
$V_sourcedir="Source.rgm";


if (  $V_extension != "zip" ) {
	echo "ZIP 화일이 아닙니다.";
	exit;
}

if ( is_dir ( "$V_problem.dir" ) ) {
	passthru ("/bin/rm -fr $V_problem.dir 2>&1", $V_ret );
	if ( $V_ret != 0 ) exit;
}
	
passthru("/bin/mkdir $V_problem.dir 2>&1", $V_ret);
if ( $V_ret != 0 ) exit;

passthru("/bin/chmod 777 $V_problem.dir 2>&1", $V_ret);
if ( $V_ret != 0 ) exit;

passthru("/bin/cp -f $userfile temp/$V_problem.$V_extension 2>&1", $V_ret );
if ( $V_ret != 0 ) exit;

if ( !chdir( "$V_problem.dir" ) ) exit;

passthru("/bin/mkdir $V_datadir 2>&1", $V_ret);
if ( $V_ret != 0 ) exit;
passthru("/bin/mkdir $V_sourcedir 2>&1", $V_ret);
if ( $V_ret != 0 ) exit;

if ( !chdir( "$V_datadir" ) ) exit;

passthru("/bin/cp $userfile $V_problem.$V_extension 2>&1", $V_ret);
if ( $V_ret != 0 ) exit;

passthru("/usr/bin/unzip $V_problem.$V_extension 2>&1", $V_ret );
if ( $V_ret != 0 ) exit;

passthru("/bin/cp $V_problem.jpg .. 2>&1", $V_ret );
if ( $V_ret != 0 ) exit;

if ( !chdir( ".." ) ) exit;

passthru("/bin/ln -s ../babo.htm index.htm 2>&1", $V_ret );
if ( $V_ret != 0 ) exit;

passthru("/bin/ln -s ../showprob.php show.php 2>&1", $V_ret );
if ( $V_ret != 0 ) exit;

passthru("/bin/ln -s ../template.php $V_problem.php 2>&1", $V_ret );
if ( $V_ret != 0 ) exit;

if ( !chdir( ".." ) ) exit;

echo "<br>upload ok!<br>";

passthru("./replace.sh href.txt $V_problem >> index.htm", $V_ret);
if ( $V_ret != 0 ) exit;

echo "<br>성공적으로 문제가 추가 되었습니다.<br>";
echo "<br>새로운 문제를 등록해 주신 선생님! 진심으로 감사드립니다.";
