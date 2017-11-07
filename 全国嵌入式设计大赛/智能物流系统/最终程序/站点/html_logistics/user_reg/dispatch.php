
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
<DIV class=logo><A IMG height=67 
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
       TuanDui</P>
</div>
<div class="con">
				<div class="gy01">
					<h3>车辆调度</a></h3>
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
$truckid = $_POST['truckid'];

$ic = $_POST['ic'];

$destination = $_POST['destination'];

//注册信息判断
if(strlen($truxkid) > 20){
	exit('错误：ic长度不符合规定。<a href="javascript:history.back(-1);">返回</a>');
}
if(strlen($ic) > 30){
	exit('错误：goodsname长度不符合规定。<a href="javascript:history.back(-1);">返回</a>');
}

if(strlen($destination) > 30){
	exit('错误：目的地长度不符合规定。<a href="javascript:history.back(-1);">返回</a>');
}

//包含数据库连接文件
include('conn.php');
//写入数据
$sql = "INSERT INTO  DEPARTURE(truckid,ic,destination)VALUES('$truckid','$ic','$destination')";

if(mysql_query($sql,$conn)){?>
<tr><?php echo "恭喜您，注册成功！";?></tr>
<div align=center> 
      <table width=600 align=center border=1  cellpadding="0" cellspacing="0" style="color:#886677;font-size:15px;"> 
    
             <tr>
             <td width=100  height=22 bgcolor=#E6E6E6>车辆ID号:</td>
             <td width=200  bgcolor=Sliver><?php echo $truckid ?></td>
             </tr>
             <tr>
             <td width=18% bgcolor=#E6E6E6>货物IC号:</td>
             <td width=10%><?php echo $ic?></td>
             </tr>
              <tr>
             <td width=10% bgcolor=#E6E6E6>目  的  地:</td>
              <td width=10%><?php echo $destination ?></td>
              </tr>
	</table>
</div>
	<tr><?php echo "提交成功！点击此处 <a href=../index2.html>返回</a>";?></tr>
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
<div class="ser_footer">
		版权所有  2010  北京航空航天大学 地址：北京市海淀区学院路37号　 邮编：100191 电话：82317114<br /> 
		建设维护：<a href="http://nic.buaa.edu.cn" target="_blank">网络信息中心</a>　　电子邮箱:<a href="mailto:webmaster@buaa.edu.cn">webmaster@buaa.edu.cn</a> 京ICP备05004617 文保网安备案号1101080018
	</div></div>

</body></html>

