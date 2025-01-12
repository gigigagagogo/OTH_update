import java.sql.*;
import java.util.*;
public class Exercise_2 {
    static Scanner sc = new Scanner(System.in);
    public static void main(String[] args) {
        String user = "bar31549";
        String password = "bar31549";
        String host = "jdbc:postgresql://hera.hs-regensburg.de:5432/" + user;
        String table = sc.nextLine();
        printTable(host,user,password,table);
    }

    public static void printTable(String host, String user, String password, String r) {
        try{
            Connection conn = DriverManager.getConnection(host,user,password);
            Statement stmt = conn.createStatement();
            ResultSet result = stmt.executeQuery("select * from " + r);

            ResultSetMetaData rsmd = result.getMetaData();
            System.out.println(rsmd);
            for(int i = 1; i <= rsmd.getColumnCount(); i++)
                System.out.print(rsmd.getColumnName(i)+"\t\t");
            System.out.println();

            while (result.next()) {
                for (int i = 1; i <= rsmd.getColumnCount(); i++) {
                    Object attribute = result.getObject(i);
                    System.out.print(attribute.toString()+" ");
                }
                System.out.println();
            }
            stmt.close();
            result.close();
            conn.close();
        }catch (SQLException e){
            e.printStackTrace();
        }
    }

}
