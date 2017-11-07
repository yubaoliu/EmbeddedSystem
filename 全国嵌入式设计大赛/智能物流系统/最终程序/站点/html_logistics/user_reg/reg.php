<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3c.org/TR/1999/REC-html401-19991224/loose.dtd">
<!-- saved from url=(0037)http://www.buaa.edu.cn/yxsz/index.htm -->
<HTML xmlns="http://www.w3.org/1999/xhtml"><HEAD><TITLE>智能物流系统--作品介绍</TITLE>
<META http-equiv=Content-Type content="text/html; charset=utf-8"><LINK media=all 
href="../智能物流系统.files/base.css" type=text/css rel=stylesheet>
<META content="MSHTML 6.00.2900.5659" name=GENERATOR></HEAD>
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




//-->

</SCRIPT>
 </SPAN></DIV></DIV></DIV>
<DIV class=banner><IMG height=176 
src="../智能物流系统.files/page_01.jpg" width=992> </DIV>
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
      注册成功</P>
</div>
<div class="con">
				<div class="gy01">
					<h3>注册成功</a></h3>
					<div class="conn">
													<div class="conn">


<p>

			
<?php
//echo date("Y-m-d H:i",time());
if(!isset($_POST['submit'])){
	exit('非法访问!');
}
$username = $_POST['username'];
$password = $_POST['password'];
$telephone = $_POST['telephone'];
//注册信息判断
if(!preg_match('/^[\w\x80-\xff]{3,15}$/', $username)){
	exit('错误：用户名不符合规定。<a href="javascript:history.back(-1);">返回</a>');
}
if(strlen($password) < 6){
	exit('错误：密码长度不符合规定。<a href="javascript:history.back(-1);">返回</a>');
}
if(strlen($telephone)!= 11){
	exit('错误：电话号码格式错误。<a href="javascript:history.back(-1);">返回</a>');
}
//包含数据库连接文件
include('conn.php');
//检测用户名是否已经存在
$check_query = mysql_query("select uname from  REGISTER where uname='$username' limit 1");
if(mysql_fetch_array($check_query)){
	echo '错误：用户名 ',$username,' 已存在。<a href="javascript:history.back(-1);">返回</a>';
	exit;
}
//写入数据
//$password = htmlspecialchars($password);
$regdate = time();
$password = MD5($password);

$sql = "INSERT INTO REGISTER(uname,password,telephone,regdate)VALUES('$username','$password','$telephone','$regdate')";
if(mysql_query($sql,$conn)){
    
	exit('用户注册成功！点击此处 <a href="../index.html">登录</a>');
} else {
	echo '抱歉！添加数据失败：',mysql_error(),'<br />';
	echo '点击此处 <a href="javascript:history.back(-1);">返回</a> 重试';
}
?>
</p>

</DIV>

		</div>
		
		
	</div>
	</DIV>
<DIV class="ser_footer">版权所有 2011 曲阜师范大学（日照校区） 地址：山东省日照市东港区烟台路80号　 邮编：276826 
<BR>建设维护：<A href="" 计算机科学学院</A>　　电子邮箱:<A 
href="mailto:syc109r@163.com">syc109r@163.com</A> <BR></DIV></div>

</body></html>
