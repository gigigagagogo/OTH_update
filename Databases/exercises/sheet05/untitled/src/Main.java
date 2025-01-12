import java.util.Scanner;
import java.sql.*;

public class Main {
    static Scanner sc = new Scanner(System.in);
    public static void main(String[] args) {
        System.out.println("user and password:");

        String user = "bar31549";
        String password = "bar31549";
        String host = "jdbc:postgresql://hera.hs-regensburg.de:5432/" + user;
        connection(host,user,password);

    }

    public static void connection(String dbid, String userid, String pass) {
        try{
            Connection conn = DriverManager.getConnection(dbid, userid, pass);
            PreparedStatement pstmt;
            ResultSet result;
            System.out.println("Inserisci un instructor name:");
            String nome = sc.nextLine();
            pstmt = conn.prepareStatement("SELECT i.id, i.name from instructor i where i.name like ?");
            pstmt.setString(1,"%" + nome + "%");
            result = pstmt.executeQuery();
            while (result.next()) {
                System.out.print(result.getString("id"));
                System.out.print(" ");
                System.out.println(result.getString("name"));
            }
            System.out.println("Inserisci un instructor id:");
            String id = sc.nextLine();
            pstmt = conn.prepareStatement("SELECT * from instructor i where i.id like ?");
            pstmt.setString(1,"%" + id + "%");
            result = pstmt.executeQuery();
            if(!result.next()) {
                System.out.println("No instructor found");
            }else {
                pstmt = conn.prepareStatement("SELECT distinct i.id, i.course_id, i.year, i.semester  from teaches i where i.id like ?");
                pstmt.setString(1,"%" + id + "%");
                result = pstmt.executeQuery();
                if (!result.next()) {
                    System.out.println("Instructor no teach!");
                }else{
                    while (result.next()) {
                        System.out.print(result.getString("course_id"));
                        System.out.print(" ");
                        System.out.println(result.getString("year"));
                        System.out.print(" ");
                        System.out.println(result.getString("semester"));
                    }
                }
            }
            conn.close();
            result.close();
            pstmt.close();
        }catch (SQLException e){
            e.printStackTrace();
        }
    }

}
