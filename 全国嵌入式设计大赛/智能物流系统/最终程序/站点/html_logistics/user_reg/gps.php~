<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3c.org/TR/1999/REC-html401-19991224/loose.dtd">
<!-- saved from url=(0037)http://www.buaa.edu.cn/yxsz/index.htm -->
<HTML xmlns="http://www.w3.org/1999/xhtml"><HEAD><TITLE>智能物流系统--作品介绍</TITLE>
<META http-equiv=Content-Type content="text/html; charset=utf-8"><LINK media=all 
href="../智能物流系统.files/base.css" type=text/css rel=stylesheet>
<META content="MSHTML 6.00.2900.5659" name=GENERATOR>
<meta http-equiv="Refresh" content=""</HEAD>
<BODY>
<DIV id=wrap>
<DIV id=header>
<DIV class=top>

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
				<P>您现在的位置：                 <a href="../index.html">首页</a>&raquo;
       GPS车辆地理信息</P>
</div>


				




<?php
session_start();

//echo date("Y-m-d H:i",time());
if(!isset($_POST['submit'])){
	//exit('非法访问!');
}
//检测是否登录，若没登录则转向登录界面
if(isset($_SESSION['username'])){
header("Location:login.html");
exit();
}
$truckid = ($_POST['truckid']);
//包含数据库连接文件
include('conn.php');

$result=mysql_query("select * from $truckid");

?>
<div class="gy01">
					<h3>GPS车辆地理信息 Of <?php echo $truckid ;?></a>  &nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp&nbsp<a href="../map.html" target=_blank>电子地图追踪</a></h3>
					<div class="conn">
 
<center>    
<table width=auto align=center bgcolor=Sliver border=1 style="  style="
       color:#886000;font-size:15px;"> 
<tr >      
            <td width=20%>日期</td>
            <td width=15%>时间</td>
            <td width=20%>纬度</td>
            <td width=20%>经度</td>
            <td width=15%>HIGH</td>
            <td width=10%>状态</td>    
</tr>  
      </table>
<div style="
        width:56%;
        height:200px;
        overflow:auto;
        overflow-x:auto;
        background-color: #eef3fa;">
      <table width=auto align=center bgcolor=#E6E6E6 border=1 style="color:#886000;font-size:15px;"> 
<?php while ($info=mysql_fetch_array($result,MYSQL_ASSOC)){?>
<tr>
<td width=15%><?php echo $info["date"]?></td>
<td width=15%><?php echo $info["time"] ?></td> 
<td width=25%><?php echo $info["latitude"] ?></td> 
<td width=25%><?php echo $info["lontitude"] ?></td> 
<td width=10%><?php echo $info["high"] ?></td> 
<td width=10%><?php echo $info["status"] ?></td> 
</tr>
<?php }?>       
 </table> 
</div>
<?php mysql_close($conn);?>
</center>	
	</div>
	</DIV>
<center><h3><form><p><input type=button value="重新载入"  onClick= "javascript:location.reload()" target="_self"></p></form> </a></h3></center><DIV class="ser_footer">版权所有 2011 曲阜师范大学（日照校区） 地址：山东省日照市东港区烟台路80号　 邮编：276826 
<BR>建设维护：<A href="" 计算机科学学院</A>　　电子邮箱:<A 
href="mailto:syc109r@163.com">syc109r@163.com</A> <BR></DIV></div>

</body></html>

