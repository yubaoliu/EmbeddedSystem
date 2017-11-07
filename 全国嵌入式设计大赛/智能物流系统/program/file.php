<html>
<head>
</head>
<body>
<?php
	$fp=fopen("receive.txt","r");
	while(!feof($fp))
	{
  	  echo fgets($fp,1024);
	}

	fclose($fp);
?>
</body>


</html>

