import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.sql.Connection; 
import java.sql.DriverManager; 
import java.sql.SQLException; 


import com.mysql.jdbc.Statement;


public class test { 

public static void main(String args[]) { 
Connection con = null; 

try { 
Class.forName("com.mysql.jdbc.Driver").newInstance(); 
con = DriverManager.getConnection("jdbc:mysql://127.0.0.1:3306/logistics", "root", "abcd123"); 
File file = new File("/home/kenan/workspace/receive.txt");
Statement stmt=(Statement)con.createStatement();
//LinkedList<String> list = new LinkedList<String>();
if (file.exists() && file.isFile()) {
 try{      String time="";   
	 while(true){
              BufferedReader input = new BufferedReader(new FileReader(file));
              
             
            	 
              String text=input.readLine();
                   String[] str=text.split("\\|");
              if(str[4].equals(time)){}
              else{
                   if(str[0].equals("#TRUCK0"))
{
                	   String strsdf="INSERT INTO TRUCK0 VALUES('";
                	   strsdf += str[2] + "','";
                	   strsdf += str[4] + "','";
                	   strsdf += str[6] + "','";
                	   strsdf += str[8] + "','";
                	   strsdf += str[10] + "','";
                	   strsdf += str[12] + "')";
                	   stmt.execute(strsdf);
                	    time=str[4];
}
else {
	String strsdf="INSERT INTO TRUCK1 VALUES('";
	   strsdf += str[2] + "','";
	   strsdf += str[4] + "','";
	   strsdf += str[6] + "','";
	   strsdf += str[8] + "','";
	   strsdf += str[10] + "','";
	   strsdf += str[12] + "')";
	stmt.execute(strsdf);
	 time=str[4];
}
              } 
}
  

  
                 
                         
}
              //while((text = input.readLine()) != null)
      
 //list.add(text);          
          catch(IOException ioException){
              System.err.println("File Error!");
          }
if(!con.isClosed()) 
System.out.println("Successfully connected to " + "MySQL server using TCP/IP..."); 
}} catch(Exception e) { 
System.err.println("Exception: " + e.getMessage()); 
} finally { 
try { 
if(con != null) 
con.close(); 
} catch(SQLException e) {} 
} 
}

} 
