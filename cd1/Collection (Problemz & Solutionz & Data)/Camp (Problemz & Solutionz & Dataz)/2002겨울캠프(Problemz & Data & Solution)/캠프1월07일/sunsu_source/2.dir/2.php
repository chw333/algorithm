<?

######################################################
# Variables from mother php program
#
# $userfile      : �ý��۳��� �����ϴ� upload�� ���� 
# $userfile_name : upload�� ���� 
# $userfile_size : upload�� ���� ������
# $userfile_type : upload�� ���� Ÿ��
######################################################

// For debugging echo "�ý��� �ӽ�����   : $userfile<br>";
echo "<br>�� �ý������� ���ε�� �����̸� : $userfile_name(size:${userfile_size}bytes, type:$userfile_type)<br>\n";

flush();

######################################################
# Variables defined this php program
#
# $V_problem     : ������ �̸�
# $V_workingdir  : posix_getpid()
# $V_extension   : upload�� ������ Ȯ���� 
# $tok           : ��ū �и��� ���� ����� �ӽ� ����
# $V_score       : �� ����
# $V_ret         : �Լ� ���� �� ���ϰ��� ����
# $V_datadir     : �����Ͱ� �����ϴ� ��
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
	echo "<br>���� ���ε尡 ���������� ������� ���߽��ϴ�.<br>";
	exit; 
} else {
	echo "<br>���� ���ε尡 ���������� ����Ǿ����ϴ�.<br>";
}

flush();

if ( !chdir ( "$V_sourcedir" ) ) exit;

passthru ( "/bin/cp $userfile $userfile_name 2>&1", $V_ret );
if ( $V_ret != 0 ) exit;

passthru ("/bin/chmod 000 $userfile_name", $V_ret );
if ( $V_ret != 0 ) exit;

echo "<br>�ҽ��� ���������� ����Ǿ����ϴ�. �����߽��ϴ�.<br>";
?>
