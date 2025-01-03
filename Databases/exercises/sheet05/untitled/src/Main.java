import java.sql.*;
import java.util.Scanner;


public class Main {
    public static String url = "jdbc:postgresql://hera.hs-regensburg.de:5432/bar31549";
    public static String username="bar31549";
    public static void main(String[] args) {
        String pass;
        Scanner scan = new Scanner(System.in);
        pass = scan.nextLine();
        dbConnection(url,username,pass);
    }

    public static void dbConnection(String url, String username, String password){
        try(Connection cont = DriverManager.getConnection(url,username,password);
            Statement stat= cont.createStatement();
        ){
            ResultSet set = stat.executeQuery("SELECT name FROM instructor");

            while (set.next()){
                System.out.println(set.getString("name"));
            }
            
        }catch(SQLException e){
            System.out.println("Exception: " + e);

        }
    }

}