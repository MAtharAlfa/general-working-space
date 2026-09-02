import java.util.Scanner;

public class Main {
    static Scanner sc = new Scanner(System.in);
    public static void main(String[] args){
        System.out.println("Program Penghitung Nilai");
        String nama = inputString("Nama: ");
        int kuis = inputInteger("Nilai Kuis:");
        int uts = inputInteger("Nilai UTS:");
        int uas = inputInteger("Nilai UAS:");

        Mahasiswa mahasiswa = new Mahasiswa(nama, uts, uas, kuis);

        System.out.println(mahasiswa.hitungNilaiAkhir());
    }

    static String inputString(String message){
        System.out.println(message);
        return sc.nextLine(); 
    }

    static Integer inputInteger(String message){
        System.out.println(message);
        return Integer.parseInt(sc.nextLine()); 
    }
}
