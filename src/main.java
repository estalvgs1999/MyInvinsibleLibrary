import java.util.ArrayList;

public class main {

    public static void main(String[] args){
        Metadata.Start();

        ArrayList<String> L = new ArrayList<String>();
        L.add("name");
        L.add("size");
//        ArrayList<String> L2= new ArrayList<String>();
//        L2.add("date");
//        ArrayList<String> L3= new ArrayList<String>();
//        L3.add("2019");
        ArrayList<String> L4= new ArrayList<String>();
        L4.add("Wajo");
        L4.add("200.0");
        Metadata.Insert(L,L4);
        Metadata.Select(null);

        Metadata.Close();
    }




}
