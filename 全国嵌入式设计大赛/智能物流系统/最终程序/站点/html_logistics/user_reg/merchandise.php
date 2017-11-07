
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3c.org/TR/1999/REC-html401-19991224/loose.dtd">
<HTML xmlns="http://www.w3.org/1999/xhtml"><HEAD><TITLE>智能物流系统--作品介绍</TITLE>
<META http-equiv=Content-Type content="text/html; charset=utf-8"><LINK media=all 
href="../智能物流系统.files/base.css" type=text/css rel=stylesheet>
<META content="MSHTML 6.00.2900.5659" name=GENERATOR></HEAD>
<title>client order form</title>

  <style type="text/css">

    html{font-size:12px;}

	fieldset{width:520px; margin: 0 auto;}

	legend{font-weight:bold; font-size:14px;}

	label{float:left; width:70px; margin-left:10px;}

	.left{margin-left:80px;}

	.input{width:150px;}

	span{color: #666666;}

  </style>

<BODY>
<DIV id=wrap>
<DIV id=header>
<DIV class=top>
<DIV class=logo><A href="IMG height=67 
src="../智能物流系统.files/logo.jpg" width=311></A></DIV>
<DIV class=top_rig>
<DIV class=rad01><A href="http://www.cie-eec.org/bcb/index.htm" target=_blank>博创杯</A>&nbsp;|&nbsp;<A href="http://www.qrnu.edu.cn/800.asp" target=_blank>校园门户系统</A></DIV><DIV class=top_ser1><SPAN class=time>今天是
<SCRIPT language=JavaScript><!--
var dayNames = new Array("星期日","星期一","星期二","星期三","星期四","星期五","星期六");
Stamp = new Date();
document.write("" + Stamp.getFullYear() + "."+(Stamp.getMonth() + 1) +"."+Stamp.getDate()+" " + dayNames[Stamp.getDay()] +"");



//-->

</SCRIPT>
 </SPAN></DIV></DIV></DIV>

<DIV class=nav>
<UL>
   <LI><A href="../index.html">网站首页</A> </LI>
   <LI><A href="merchandise.html">货物入库登记</A> </LI>
   <LI><A href="dispatch.html">车辆调度</A> </LI>
   <LI><A href="swarehouse1.php">站点出库信息&nbsp&nbsp&nbsp</A> </LI>
   <LI><A href="swarehouse2.php">入库车辆信息&nbsp&nbsp</A> </LI>
   <LI><A href="gps.html">gps追踪&nbsp&nbsp</A> </LI>

	</ul></div>
	</div>
<div id="content">
		
		<div class="sec_con01">
<div class="title">
				<P>您现在的位置：                 <a href="../index.html">首页</a>&raquo;
       货物登记注册</P>
</div>
<div class="con">
				<div class="gy01">
					<h3>货物登记注册</a></h3>
					<div class="conn">
													<div class="conn">
<p >
<div align=center>
<?php
session_start();
//echo date("Y-m-d H:i",time());
if(!isset($_POST['submit'])){

	exit('非法访问!');

}
$ic = $_POST['ic'];
$goodsname = $_POST['goodsname'];
$quantity = $_POST['quantity'];
$client = $_POST['client'];
$destination = $_POST['destination'];
$rectelnum = $_POST['rectelnum'];
//注册信息判断
if(strlen($ic) > 20){
	exit('错误：ic长度不符合规定。<a href="javascript:history.back(-1);">返回</a>');
}
if(strlen($goodsname) > 30){
	exit('错误：货物名称长度不符合规定。<a href="javascript:history.back(-1);">返回</a>');
}
if(strlen($quantity) > 30){
	exit('错误：数量长度不符合规定。<a href="javascript:history.back(-1);">返回</a>');
}
if(strlen($client) > 30){
	exit('错误：客户名字长度不符合规定。<a href="javascript:history.back(-1);">返回</a>');
}

if(strlen($destination) > 30){
	exit('错误：目的地长度不符合规定。<a href="javascript:history.back(-1);">返回</a>');
}
//if(strlen($rectelnum ) != 11){
//	exit('错误：电话号码长度不符合规定。<a href="javascript:history.back(-1);">返回</a>');
//}
//包含数据库连接文件
include('conn.php');
//写入数据
$sql = "INSERT INTO  MERCHANDISE(ic,goodsname,quantity,client,destination,rectelnum)VALUES('$ic','$goodsname','$quantity','$client','$destination','$rectelnum')";
//$sql = "INSERT INTO  MERCHANDISE(ic,goodsname,quantity,client,destination,rectelnum)VALUES('98 97 55 ac','rutu','12','syc','rizhao','15006926965')";
if(mysql_query($sql,$conn)){?>
<tr><?php echo "货物登记注册成功！";?></tr>
<div align=center> 
      <table width=600 align=center border=1  cellpadding="0" cellspacing="0" style="color:#886677;font-size:15px;"> 
    
             <tr>
             <td width=100  height=22 bgcolor=#E6E6E6>货物IC号:</td>
             <td width=200  bgcolor=Sliver><?php echo $ic?></td>
             </tr>
             <tr>
             <td width=18% bgcolor=#E6E6E6>货物名字:</td>
             <td width=10%><?php echo $goodsname?></td>
             </tr>
             <tr>
              <td width=18% bgcolor=#E6E6E6>货物数量:</td>
              <td width=10%><?php echo $quantity ?></td>
             </tr>
              <tr>
            <td width=20% bgcolor=#E6E6E6>客户名字:</td>
              <td width=20%><?php echo $client ?></td> 
              </tr>
              <tr>
             <td width=10% bgcolor=#E6E6E6>目  的  地:</td>
              <td width=10%><?php echo $destination ?></td>
              </tr>
              <tr>
            <td width=10% bgcolor=#E6E6E6>客户电话:</td> 
            <td width=10%><?php echo $rectelnum ?></td> 
            </tr>
	</table>
</div>
	<tr><?php echo "<a href=../index2.html>返回</a>";?></tr>
</div>
    <?php //exit(' 提交成功！点击此处 <a href="mydispatch.php">登录</a>');
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

