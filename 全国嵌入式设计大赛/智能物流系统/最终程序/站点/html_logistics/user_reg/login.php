


<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3c.org/TR/1999/REC-html401-19991224/loose.dtd">
<!-- saved from url=(0037)http://www.buaa.edu.cn/yxsz/index.htm -->
<HTML xmlns="http://www.w3.org/1999/xhtml"><HEAD><TITLE>智能物流系统--作品介绍</TITLE>
<META http-equiv=Content-Type content="text/html; charset=utf-8"><LINK media=all 
href="../智能物流系统.files/base.css" type=text/css rel=stylesheet>
<META content="MSHTML 6.00.2900.5659" name=GENERATOR>
</HEAD>
<BODY>
<DIV id=wrap>
<DIV id=header>
<DIV class=top>
<DIV class=logo><A href="http://www.buaa.edu.cn/"><IMG height=67 
src="../智能物流系统.files/logo.jpg" width=311></A></DIV>
<DIV class=top_rig>
<DIV class=rad01><A href="http://www.cie-eec.org/bcb/index.htm" target=_blank>博创杯</A>&nbsp;|&nbsp;<A href="http://www.qrnu.edu.cn/800.asp" target=_blank>校园门户系统</A></DIV>
<DIV class=top_ser1><SPAN class=time>今天是
<SCRIPT language=JavaScript><!--
var dayNames = new Array("星期日","星期一","星期二","星期三","星期四","星期五","星期六");
Stamp = new Date();
document.write("" + Stamp.getFullYear() + "."+(Stamp.getMonth() + 1) +"."+Stamp.getDate()+" " + dayNames[Stamp.getDay()] +"");


function InputCheck(InsertForm)
{
  if (InsertForm.ic.value == "")
  {
    alert("请输IC!");
    InsertForm.ic.focus();
    return (false);
  }
}
//-->

</SCRIPT>
 </SPAN></DIV></DIV></DIV>

<DIV class=nav>
<UL>
<li><a href="../System.html">作品介绍</a> </li>
  <li><a href="../Group.html">团队介绍</a> </li>
  <li><a href="../gps.html">全球定位模块</a> </li>
  <li><a href="../gprs.html ">无线通讯模块</a></li>
  <li><a href="../service.html ">后台服务器</a> </li>
  <li><a href="../rfid.html">FRID出入库管理</a> </li>
  <li><a href="../che.html" >智能小车</a> </li>
  <li><a href="../ditu.html">电子地图</a> </li>
	</ul></div>
	</div>
<div id="content">
		
		<div class="sec_con01">
			<div class="title">
				<P>您现在的位置：                 <a href="../index.html">首页</a>&raquo;
       登陆</P>
</div>
<div class="con">
				<div class="gy01">
					<h3> 客户查询</a></h3>
					<div class="conn">
													<div class="conn">


<p>
<?php
session_start();

//注销登录
if($_GET['action'] == "logout"){
	//unset($_SESSION['userid']);
	unset($_SESSION['username']);
	echo '注销登录成功！点击此处 <a href="login.html">登录</a>';
	exit;
}

//登录
if(!isset($_POST['submit'])){
	exit('非法访问!');
}

$username = htmlspecialchars($_POST['username']);
$password = MD5($_POST['password']);

//包含数据库连接文件
include('conn.php');

//检测用户名及密码是否正确
$check_query = mysql_query("select uname from REGISTER where uname='$username' and password='$password' limit 1");
if($result = mysql_fetch_array($check_query)){
     if($username=="root"){
	//登录成功
	     echo $username,' 欢迎你！进入 <a href="../index2.html">管理员中心</a><br />';}
        else 
          { echo $username,' 欢迎你！进入客户查询  请输入货物IC号</a><br />';?>
<form name="InsertForm" method="post" action="my.php" onSubmit="return InputCheck(this)">
<p>
<label for="IC" class="label">货物IC:</label>
<input id="IC" name="IC" type="text" class="input" />
<p/>
<p>
<input type="submit" name="submit" value="  确 定  " class="left" />
</p>
</form><?php }?>
	<?php exit;
} 
else {
	exit('登录失败！点击此处 <a href="javascript:history.back(-1);">返回</a> 重试');
}
?>

</p>

</DIV>

		</div>
		
		
	</div>
<DIV class="ser_footer">版权所有 2011 曲阜师范大学（日照校区） 地址：山东省日照市东港区烟台路80号　 邮编：276826 
<BR>建设维护：<A href="" 计算机科学学院</A>　　电子邮箱:<A 
href="mailto:syc109r@163.com">syc109r@163.com</A> <BR></DIV></div>

</body></html>
