<html>
<body>
<?php
session_start();

//����Ƿ��¼����û��¼��ת���¼����
if(!isset($_SESSION['userid'])){
header("Location:login.html");
exit();
}

//�������ݿ������ļ�
include('conn.php');
$userid = $_SESSION['userid'];
$username = $_SESSION['username'];
$traid=$_SESSION['traid'];
$user_query = mysql_query("select * from user2 where uid=$userid limit 1");
$row = mysql_fetch_array($user_query);
echo '�û���Ϣ��<br />';
echo '�û�ID��',$userid,'<br />';
echo '�û�����',$username,'<br />';
echo '���䣺',$row['email'],'<br />';
echo 'ע�����ڣ�',date("Y-m-d", $row['regdate']),'<br />';
echo '<a href="login.php?action=logout">ע��</a> ��¼<br />';
$result=mysql_query("select * from $traid,$conn);
?>
<table width="320" height="30" border="1">
<?php while ($info=mysql_fetch_array($result,MYSQL_ASSOC)){?>
<tr>
<td width="20" heigth="10"><?php echo $info["date"]?></td>
<td width="20"><?php echo $info["time"]?></td>
<td width="20"><?php echo $info["latitude"]?></td>
<td width="20"><?php echo $info["lonitude"]?></td>
<td width="20"><?php echo $info["high"]?></td>
<td width="20"><?php echo $info["status"]?></td>
</tr><?php }?>

</table>
<?php mysql_close($conn);?>
</body>
</html>

