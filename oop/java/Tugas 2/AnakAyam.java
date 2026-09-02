/* 
Nama Program    : Anak Ayam
Nama Pembuat    : Muhammad Athar Alfarisi
NPM             : 140810250005
Tanggal Buat    : 01/09/2026
Deskripsi       : Penggunaan konsep perulangan dalam java menggunakan anak ayam 
*/

import java.util.Scanner;

public class AnakAyam {
    static Scanner sc = new Scanner(System.in);

    public static void main(String[] args){
        Integer input = inputInteger("Banyak anak ayam (minimal 1): ");

        for (int i = input; i > 0;) {
            if (i != 0) System.out.println("Anak ayam turunlah " + i);
            --i;
            
            if (i > 0) {
                System.out.println("Mati satu tinggallah " + i);   
            } else {
                System.out.println("Mati satu tinggal induknya.");
            }
        }
    }

    static Integer inputInteger(String pesan){
        Integer input;

        while (true) {
            System.out.println(pesan);
            input = Integer.parseInt(sc.nextLine());

            if (input > 0) break;

            System.out.println("input error(): nilai tidak valid");
        }

        return input;
    }
}