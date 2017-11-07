package logistics;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.sql.Connection; 
import java.sql.DriverManager; 
import java.sql.ResultSet;
import java.sql.SQLException; 
import com.mysql.jdbc.Statement;
import java.sql.*;
public class logistics {

	public static void main(String[] args) 
	{
		Connection con = null; 

		try { 
			Class.forName("com.mysql.jdbc.Driver").newInstance(); 
			con = DriverManager.getConnection("jdbc:mysql://127.0.0.1:3306/logistics", "root", ""); 
			File file1 = new File("/var/www/html/station_exe/receive.txt");
			Statement stmt=(Statement)con.createStatement();
			if (file1.exists()&& file1.isFile()) {
				try{      
					String time=" ";  
					while(true){


						BufferedReader input1 = new BufferedReader(new FileReader(file1));
						String text1=input1.readLine();
						String[] str1=text1.split("\\$");

						if(str1[4].equals(time)){}
						else{
							if(str1[0].equals("#TRUCK0"))
							{
								String strsdf="INSERT INTO TRUCK0 VALUES('";
								strsdf += str1[2] + "','";
								strsdf += str1[4] + "','";
								strsdf += str1[6] + "','";
								strsdf += str1[8] + "','";
								strsdf += str1[10] + "','";
								strsdf += str1[12] + "')";
								stmt.execute(strsdf);
								time=str1[4];
							}
							else {
								String strsdf="INSERT INTO TRUCK1 VALUES('";
								strsdf += str1[2] + "','";
								strsdf += str1[4] + "','";
								strsdf += str1[6] + "','";
								strsdf += str1[8] + "','";
								strsdf += str1[10] + "','";
								strsdf += str1[12] + "')";
								stmt.execute(strsdf);
								time=str1[4];
							}                  
						}              
						File file2 = new File("/var/www/html/station_exe/ic.txt");
						
						if (file2.exists()&& file2.isFile()){
							BufferedReader input2 = new BufferedReader(new FileReader(file2));
							String text2=input2.readLine();
							String sql="select ic from SWAREHOUSE1 where ic='"+text2+"'";
							
							ResultSet rs=stmt.executeQuery(sql);
							if(text2==null){}
							else{
								if(rs.next()){
									java.sql.Date date = new java.sql.Date(System.currentTimeMillis());
									String datetime = date.toString();
									String sdf="UPDATE  SWAREHOUSE1 SET outtime='"+ datetime + "' where ic='"+text2+"'";
									stmt.execute(sdf);
								}
								else
								{
									java.sql.Date date = new java.sql.Date(System.currentTimeMillis());
									String datetime = date.toString();
									String sdf="INSERT INTO SWAREHOUSE1(ic,intime) VALUES('";
									sdf +=text2+ "','";
									sdf += datetime + "')";
									stmt.execute(sdf);
									System.out.print("hello2");
									String sqd="select destination,rectelnum from MERCHANDISE where ic='"+text2+"'";
									
									ResultSet r=stmt.executeQuery(sqd);
									System.out.print(r);
								    if(r.next()){
								    	System.out.print("hello3");
										System.out.print(r.getString("destination"));
										if(r.getString("destination").equals("rizhao"))
										{
											File f = new File("/var/www/html/station_exe/sendmessage.txt");
											BufferedWriter out = new BufferedWriter(new FileWriter(f));
											out.write(r.getString("rectelnum"));
											
											out.close();
										}
										System.out.print("win");
									}else {System.out.print("helsdfgds");}
									
								} 

								BufferedWriter output = new BufferedWriter(new FileWriter(file2));
								output.write("");
								output.close();


							}
						}

					}



				}
				catch(Exception e) { 
					System.err.println("Exception1: " + e.getMessage()); 
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
