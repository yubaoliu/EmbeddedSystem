<?php
//echo date("Y-m-d H:i",time());
if(!isset($_POST['submit'])){
	exit('�Ƿ�����!');
}
$username = $_POST['username'];
$password = $_POST['password'];
$telephone = $_POST['telephone'];
//ע����Ϣ�ж�
if(!preg_match('/^[\w\x80-\xff]{3,15}$/', $username)){
	exit('�����û��������Ϲ涨��<a href="javascript:history.back(-1);">����</a>');
}
if(strlen($password) < 6){
	exit('�������볤�Ȳ����Ϲ涨��<a href="javascript:history.back(-1);">����</a>');
}
if(strlen($telephone)!= 11){
	exit('����telephone��ʽ����<a href="javascript:history.back(-1);">����</a>');
}
//�������ݿ������ļ�
include('conn.php');
//����û����Ƿ��Ѿ�����
$check_query = mysql_query("select uname from  REGISTER where uname='$username' limit 1");
if(mysql_fetch_array($check_query)){
	echo '�����û��� ',$username,' �Ѵ��ڡ�<a href="javascript:history.back(-1);">����</a>';
	exit;
}
//д������
//$password = htmlspecialchars($password);
$regdate = time();
$password = MD5($password);

$sql = "INSERT INTO REGISTER(uname,password,telephone,regdate)VALUES('$username','$password','$telephone','$regdate')";
if(mysql_query($sql,$conn)){
	exit('�û�ע��ɹ�������˴� <a href="login.html">��¼</a>');
} else {
	echo '��Ǹ���������ʧ�ܣ�',mysql_error(),'<br />';
	echo '����˴� <a href="javascript:history.back(-1);">����</a> ����';
}
?>
