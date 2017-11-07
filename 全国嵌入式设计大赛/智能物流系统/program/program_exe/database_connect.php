<html>
<body>
text
<?php
if(!$id=mysql_connect("localhost","root","123456"))
{
 echo "open database false";
 exit;
}
echo "open database success";
if(!mysql_select_db("logistics",$id))
{
 echo "database select error";
 exit;
}
echo "database select success";
  $fp=fopen("data.txt","r");
  $content=fgets($fp);
//echo $content;
 $str=split('\|',$content);

//$sql="INSERT INTO user1 VALUES('000000','a','b','c','d','e','f')";
$sql="INSERT INTO user1 VALUES('000000','$str[1]','$str[3]','$str[5]','$str[7]','$str[9]','$str[11]')";
$excu=mysql_query($sql,$id);
if($excu)
{
echo "database insert success";
}
else
{
	echo "database insert error";
	echo mysql_error();
}
 ?>
</body>
 </html>
  
