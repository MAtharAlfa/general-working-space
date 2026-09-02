/* 
Nama Program    : Program Pencetak Bintang
Nama Pembuat    : Muhammad Athar Alfarisi
NPM             : 140810250005
Tanggal Buat    : 01/09/2026
Deskripsi       : Program memasukan input n untuk membuat pola selebar input n
*/

import java.util.Scanner;

public class CetakBintang {
    static Scanner sc = new Scanner(System.in);
    static public void main(String[] args){
        Integer input = inputInteger("Jumlah Kolom: ", 1);

        System.out.println("\nSegitiga: ");
        cetakBintangPola1(input);
        System.out.println("Segitiga (pakai while): ");
        cetakBintangPola1While(input);
        System.out.println("Pola Dua");
        cetakBintangPola2(input);
        System.out.println("Pola Dua (pakai while):");
        cetakBintangPola2While(input);
    }

    static void cetakBintangPola1(Integer jumlahKolom){
        boolean goLeft = false; //default to going right first then left
        for(int helper = 0, i = 0; i < jumlahKolom + (jumlahKolom - 1); ++i){ //helper for logic, i for counter.

            System.out.print((i + 1) + ". ");
            for(int j = 0; j < jumlahKolom; ++j){
                if (j <= helper) {
                    System.out.print("*");
                } else {
                    System.out.print(" ");
                }
            }
            
            //if intended width is reached then go left with "*""
            if (helper == (jumlahKolom - 1)){
                goLeft = true;
            }

            //dictate direction
            if (goLeft == false){
                ++helper;
            } else{
                --helper;
            }

            System.out.println();
        }
    }

    static void cetakBintangPola1While(Integer jumlahKolom){
        boolean goLeft = false; //default to going right first then left
        int helper = 0, i = 0;
        while (i < jumlahKolom + (jumlahKolom - 1)){

            System.out.print((i + 1) + ". ");
            for(int j = 0; j < jumlahKolom; ++j){
                if (j <= helper) {
                    System.out.print("*");
                } else {
                    System.out.print(" ");
                }
            }
            
            //if intended width is reached then go left with "*""
            if (helper == (jumlahKolom - 1)){
                goLeft = true;
            }

            //dictate direction
            if (goLeft == false){
                ++helper;
            } else{
                --helper;
            }

            System.out.println();
            ++i;
        }
    }

    static void cetakBintangPola2(Integer jumlahKolom){ 
        boolean goRight = false;
        for(int helper = jumlahKolom-1, i = 0; i < jumlahKolom + (jumlahKolom - 1); ++i){ //helper for logic, i for counter. helper -1 biar shift

            System.out.print((i + 1) + ". ");
            for(int j = 0; j < jumlahKolom; ++j){
                if (j <= helper) {
                    System.out.print("*");
                } else {
                    System.out.print(" ");
                }
            }
            
            //if intended width is reached then go right with " "
            if (helper == 0){ //set 0 as the absolute turning point
                goRight = true;
            }

            //dictate direction
            if (goRight == false){
                --helper;
            } else{
                ++helper;
            }

            System.out.println();
        }
    }

    static void cetakBintangPola2While(Integer jumlahKolom){ 
        boolean goRight = false;
        int helper = jumlahKolom-1, i = 0;

        while (i < jumlahKolom + (jumlahKolom - 1)) {
            System.out.print((i + 1) + ". ");
            for(int j = 0; j < jumlahKolom; ++j){
                if (j <= helper) {
                    System.out.print("*");
                } else {
                    System.out.print(" ");
                }
            }
            
            //if intended width is reached then go right with " "
            if (helper == 0){ //set 0 as the absolute turning point
                goRight = true;
            }

            //dictate direction
            if (goRight == false){
                --helper;
            } else{
                ++helper;
            }

            System.out.println();
            ++i;
        }
    }

    static Integer inputInteger(String pesan, int min){
        Integer input;

        while (true) {
            System.out.println(pesan);
            input = Integer.parseInt(sc.nextLine());

            if (input >= min) break;

            System.out.println("input error(): nilai tidak valid");
        }

        return input;
    }
}
