
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

<DIV id=header>
<DIV class=top>
<DIV class=logo><IMG height=67 
src="../智能物流系统.files/logo.jpg" width=311></DIV>
<DIV class=top_rig>
<DIV class=rad01><A href="http://www.cie-eec.org/bcb/index.htm" target=_blank>博创杯</A>&nbsp;|&nbsp;<A href="http://www.qrnu.edu.cn/800.asp" target=_blank>校园门户系统</A></DIV>
<DIV class=top_ser1><SPAN class=time>今天是
<SCRIPT language=JavaScript>

<!--
var dayNames = new Array("星期日","星期一","星期二","星期三","星期四","星期五","星期六");
Stamp = new Date();
document.write("" + Stamp.getFullYear() + "."+(Stamp.getMonth() + 1) +"."+Stamp.getDate()+" " + dayNames[Stamp.getDay()] +"");//-->

</SCRIPT>
 </SPAN></DIV></DIV></DIV>
</div>
<head>
<DIV class=nav>
<UL>
   <LI><A href="../index.html">网站首页</A> </LI>
   <LI><A href="merchandise.html">货物入库登记</A> </LI>
   <LI><A href="dispatch.html">车辆调度</A> </LI>
   <LI><A href="swarehouse1.php">站点出库信息&nbsp&nbsp&nbsp</A> </LI>
   <LI><A href="swarehouse2.php">入库车辆信息&nbsp&nbsp</A> </LI>
   <LI><A href="gps.html">gps追踪&nbsp&nbsp</A> </LI>

  </UL></DIV></DIV>
<style type="text/css">

table {
    margin:10px;
    font:12px/180% Verdana, Arial;
    text-align:center;
    width:500px;
 
    overflow:scroll;
   
}
th {
    background:Silver;
}

</style>
</head>
<div id="content">
		
		<div class="sec_con01">
			<div class="title">
				<P>您现在的位置：                 <a href="../index2.html">首页</a>&raquo;
      出库车辆信息</P>
</div>
<div class="con">
				<div class="gy01">
					<h3>出库车辆信息</a></h3>
					<div class="conn">
													<div class="conn">

<center>

<?php

//包含数据库连接文件
include('conn.php');

$result=mysql_query("select * from  SWAREHOUSE1  where intime!=''and outtime!=''");



?>
<div style="
        width:80%;
        overflow:auto;
        overflow-x:auto;
        background-color:#eef3fa;">
      <table width=auto align=center bgcolor=Sliver border=1  style="
       color:#886000;font-size:15px;"> 
<tr >      
            <td width=30%>车辆编号</td>
            <td width=20%>货物名称</td>  
            <td width=20%>货物数量</td>  
            <td width=20%>客户姓名</td>  
            <td width=20%>目&nbsp&nbsp的&nbsp&nbsp地</td>  
            <td width=20%>客户电话</td>  
</tr>  


       <?php while ($info=mysql_fetch_array($result,MYSQL_ASSOC)){?>
<tr>
<td width=30%><?php echo $info["ic"];$ic= $info["ic"]?> </td>
    
  <?php $goods=mysql_query("select * from MERCHANDISE WHERE ic='$ic'");
      $row=mysql_fetch_array($goods);?>
<td width=20%><?php echo $row["goodsname"] ?></td>
 
<td width=20%><?php echo $row["quantity"] ?></td>

<td width=20%><?php echo $row["client"] ?></td>

<td width=20%><?php echo $row["destination"] ?></td>

<td width=30%><?php echo $row["rectelnum"] ?></td>
</tr>  
<?php }?>    
 </table> 
</div>
<?php mysql_close($conn);?>
</center>	
	</div>
	</DIV></div></div>
<DIV class="ser_footer">版权所有 2011 曲阜师范大学（日照校区） 地址：山东省日照市东港区烟台路80号　 邮编：276826 
<BR>建设维护：<A href="" 计算机科学学院</A>　　电子邮箱:<A 
href="mailto:syc109r@163.com">syc109r@163.com</A> <BR></DIV></div>

</body></html>
