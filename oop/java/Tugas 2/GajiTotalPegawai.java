/* 
Nama Program    : Hitung Gaji Total
Nama Pembuat    : Muhammad Athar Alfarisi
NPM             : 140810250005
Tanggal Buat    : 01/09/2026
Deskripsi       : Program memasukan input nama dan golongan untuk mencari gaji pokok, tunjangan, potongan, dan gaji utama
*/

import java.util.Scanner;

public class GajiTotalPegawai {
    static Scanner sc = new Scanner(System.in);

    static public void main(String[] args){
        System.out.println("Tentukan Gaji Pegawai");
        String nama = inputString("Masukan nama: ");
        Integer golongan = inputInteger("Masukan golongan: ", 1, 4);
        System.out.println("Pegawai " + nama + " memiliki gaji utama sebesar: " + tentukanGT(golongan) + "\nDetail lengkapnya sebagai berikut:\n");
        cetakSemuaData(nama, golongan);
    }

    static void cetakSemuaData(String nama, Integer golongan){
        System.out.println("Nama: " + nama);
        System.out.println("Golongan: " + golongan);
        System.out.println("Gaji Pokok: " + tentukanGP(golongan));
        System.out.println("Tunjangan: " + tentukanTunjangan(golongan));
        System.out.println("Potongan: " + tentukanPotongan(golongan));
        System.out.println("Gaji Total: " + tentukanGT(golongan));
    }

    //Gaji Utama
    static Float tentukanGT(Integer golongan){
        Integer gajiPokok = tentukanGP(golongan);

        return (float)gajiPokok + tentukanTunjangan(golongan) - tentukanPotongan(golongan);
    }

    static Float tentukanTunjangan(Integer golongan){
        return tentukanGP(golongan)*tentukanKonstantaTunjangan(golongan);
    }

    static Float tentukanPotongan(Integer golongan){
        return tentukanGP(golongan)*tentukanKonstantaPotongan(golongan);
    }

    //Gaji Pokok
    static Integer tentukanGP(Integer golongan){
        if (golongan == 1) return 1500000;
        if (golongan == 2) return 2000000;
        if (golongan == 3) return 3000000;
        if (golongan == 4) {return 5000000;}
        else return -1;
    }
    
    static Float tentukanKonstantaTunjangan(Integer golongan){
        if (golongan == 1) return 0.1f;
        if (golongan == 2 || golongan == 3) return 0.12f;
        if (golongan == 4) {return 0.15f;}
        else return -1.0f;
    }

    static Float tentukanKonstantaPotongan(Integer golongan){
        if (golongan == 1) return 0.01f;
        if (golongan == 2 || golongan == 3) return 0.02f;
        if (golongan == 4) {return 0.04f;}
        else return -1.0f;
    }

    static String inputString(String pesan){
        System.out.println(pesan);
        return sc.nextLine();
    }

    static Integer inputInteger(String pesan, int min, int max){
        Integer input;

        while (true) {
            System.out.println(pesan);
            input = Integer.parseInt(sc.nextLine());

            if (input >= min && input <= max) break;

            System.out.println("input error(): nilai tidak valid");
        }

        return input;
    }
}
