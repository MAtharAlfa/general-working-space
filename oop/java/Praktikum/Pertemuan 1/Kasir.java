import java.util.Scanner;

class Barang {
    String namaBarang;
    Float hargaBarang;
    Integer jumlahBarang;
}

public class Kasir {
    static Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {

        Barang objekBarang = new Barang();

        objekBarang.namaBarang = sc.nextLine();
        objekBarang.jumlahBarang = Integer.parseInt(sc.nextLine());
        objekBarang.hargaBarang = sc.nextFloat();

        // System.out.println("Nama Barang: " + objekBarang.namaBarang);
        // System.out.println("Jumlah Barang: " + objekBarang.jumlahBarang);
        // System.out.println("Harga Barang: " + objekBarang.hargaBarang);

        System.out.printf("%s (%dx), Rp. %.2f", objekBarang.namaBarang, objekBarang.jumlahBarang, (objekBarang.hargaBarang * objekBarang.jumlahBarang));
    }
}