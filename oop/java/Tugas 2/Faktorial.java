/* 
Nama Program    : Faktorial
Nama Pembuat    : Muhammad Athar Alfarisi
NPM             : 140810250005
Tanggal Buat    : 01/09/2026
Deskripsi       : Program menerima input integer lalu memberi nilai faktorial
*/

import java.util.Scanner;

public class Faktorial{
    static Scanner sc = new Scanner(System.in);
    static public void main(String[] args){
        System.out.println("Program penghitung kombinatorik");
        Integer n = inputInteger("Masukan nilai N: ", 0);
        Integer r = inputInteger("Masukan nilai R: ", 0);

        System.out.print("Hasil: " + kombinasi(n, r));
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

    static Integer factorial(Integer n){
        if (n == 1 || n == 0) return 1;
        return n*(factorial(n-1));
    }

    static Integer kombinasi(Integer n, Integer r) {
        return factorial(n)/(factorial(n-r)*factorial(r));
    }
}