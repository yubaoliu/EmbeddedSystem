<html>
<body>
<?php
session_start();

//检测是否登录，若没登录则转向登录界面
if(!isset($_SESSION['userid'])){
header("Location:login.html");
exit();
}

//包含数据库连接文件
include('conn.php');
$userid = $_SESSION['userid'];
$username = $_SESSION['username'];
$traid=$_SESSION['traid'];
$user_query = mysql_query("select * from user2 where uid=$userid limit 1");
$row = mysql_fetch_array($user_query);
echo '用户信息：<br />';
echo '用户ID：',$userid,'<br />';
echo '用户名：',$username,'<br />';
echo '邮箱：',$row['email'],'<br />';
echo '注册日期：',date("Y-m-d", $row['regdate']),'<br />';
echo '<a href="login.php?action=logout">注销</a> 登录<br />';
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

