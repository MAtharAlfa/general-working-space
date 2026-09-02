/* 
Nama Program    : Program Pemeriksa Biner
Nama Pembuat    : Muhammad Athar Alfarisi
NPM             : 140810250005
Tanggal Buat    : 01/09/2026
Deskripsi       : Program memeriksa biner antara dua nilai dan operasi-operasinya
*/

import java.util.Scanner;

public class BitOperations {
    static Scanner sc = new Scanner(System.in);
    static public void main(String[] args){
        final int A = 53, B = 19;

        System.out.println("Nilai biner 53:");
        System.out.print("Biner: "); printIntegerToBinary(A);
        System.out.print("Hex: "); printIntegerToHex(A);
        System.out.print("Octal: "); printIntegerToOctal(A);
        System.out.println("\n");

        System.out.println("Nilai biner 19:");
        System.out.print("Biner: "); printIntegerToBinary(B);
        System.out.print("Hex: "); printIntegerToHex(B);
        System.out.print("Octal: "); printIntegerToOctal(B);
        System.out.println("\n");

        System.out.println("Hasil Operasi Biner 53 AND 19:");
        System.out.println("Desimal: " + (A & B));
        System.out.print("Biner: "); printIntegerToBinary(A & B);
        System.out.print("Hex: "); printIntegerToHex(A & B);
        System.out.print("Octal: "); printIntegerToOctal(A & B);
        System.out.println("\n");

        System.out.println("Hasil Operasi Biner 53 OR 19:");
        System.out.println("Desimal: " + (A | B));
        System.out.print("Biner: "); printIntegerToBinary(A | B);
        System.out.print("Hex: "); printIntegerToHex(A | B);
        System.out.print("Octal: "); printIntegerToOctal(A | B);
        System.out.println("\n");

        System.out.println("Hasil Operasi Biner 53 XOR 19:");
        System.out.println("Desimal: " + (A ^ B));
        System.out.print("Biner: "); printIntegerToBinary(A ^ B);
        System.out.print("Hex: "); printIntegerToHex(A ^ B);
        System.out.print("Octal: "); printIntegerToOctal(A ^ B);
        System.out.println("\n");

        System.out.println("Hasil Operasi Biner left shift 53 sebanyak 2:");
        System.out.println("Desimal: " + (A << 2));
        System.out.print("Biner: "); printIntegerToBinary(A << 2);
        System.out.print("Hex: "); printIntegerToHex(A << 2);
        System.out.print("Octal: "); printIntegerToOctal(A << 2);
        System.out.println("\n");

        System.out.println("Hasil Operasi Biner right shift 19 sebanyak 1:");
        System.out.println("Desimal: " + (B >> 1));
        System.out.print("Biner: "); printIntegerToBinary(B >> 1);
        System.out.print("Hex: "); printIntegerToHex(B >> 1);
        System.out.print("Octal: "); printIntegerToOctal(B >> 1);
    }

    static void printIntegerToBinary(Integer nilai){
        StringBuilder hasil = new StringBuilder();
        while (nilai > 0) {
            Integer temp = nilai % 2;
            hasil.append(temp.toString());
            nilai /= 2;     
        }

        System.out.println("0b" + hasil.reverse().toString());
    }

    static void printIntegerToOctal(Integer nilai){
        StringBuilder hasil = new StringBuilder();
        while (nilai > 0) {
            Integer temp = nilai % 8;
            hasil.append(temp.toString());
            nilai /= 8;     
        }

        System.out.println("0o" + hasil.reverse().toString());
    }

    static void printIntegerToHex(Integer nilai){
        StringBuilder hasil = new StringBuilder();
        while (nilai > 0) {
            Integer temp = nilai % 16;
            if (temp < 10) {
                hasil.append(temp.toString());   
            } else {
                switch (temp) {
                    case 10:
                        hasil.append('A');
                        break;
                    case 11:
                        hasil.append('B');
                        break;
                    case 12:
                        hasil.append('C');
                        break;
                    case 13:
                        hasil.append('D');
                        break;
                    case 14:
                        hasil.append('E');
                        break;
                    case 15:
                        hasil.append('F');
                        break;
                
                    default:
                        System.out.println();
                        System.out.println("error");
                        break;
                }
            }
            nilai /= 16;     
        }

        System.out.println("0x" + hasil.reverse().toString());
    }
}
