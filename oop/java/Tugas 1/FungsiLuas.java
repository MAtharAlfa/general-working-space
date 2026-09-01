/* 
Nama Program    : Hitung Persegi Panjang
Nama Pembuat    : Muhammad Athar Alfarisi
NPM             : 140810250005
Tanggal Buat    : 01/09/2026
Deskripsi       : Program memasukan input alas dan tinggi untuk mencari luas, keliling, dan panjang diagonal
*/

import java.util.Scanner;
import java.lang.Math;

public class FungsiLuas {
    static Scanner sc = new Scanner(System.in);

    public static void main(String[] args) {
        Float alas = inputFloat("Masukan nilai alas: ");
        Float tinggi = inputFloat("Masukan nilai tinggi: ");

        cetak(hitungLuas(alas, tinggi), hitungKeliling(alas, tinggi), hitungDiagonal(alas, tinggi));

        sc.close();
    }

    static Float inputFloat(String pesan) {
        System.out.println(pesan);
        Float input = Float.parseFloat(sc.nextLine());
        return (input);
    }

    static Float hitungLuas(Float alas, Float tinggi) {
        return (alas*tinggi);
    }

    static Float hitungKeliling(Float alas, Float tinggi) {
        return (2*(alas+tinggi));
    }

    static Float hitungDiagonal(Float alas, Float tinggi) {
        return (float)(Math.sqrt(Math.pow(alas, 2) + Math.pow(tinggi, 2)));
    }

    static void cetak(Float luas, Float keliling, Float diagonal) {
        System.out.println("Luas: " + luas);
        System.out.println("Keliling: " + keliling);
        System.out.println("Diagonal: " + diagonal);
    }
}