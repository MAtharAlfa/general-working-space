import java.util.Scanner;
import java.lang.Math;

public class HitungLuasOOP {
    static Scanner sc = new Scanner(System.in);
    public static void main(String[] args){
        PersegiPanjang persegi1 = new PersegiPanjang(3, 4);
        PersegiPanjang persegi2 = new PersegiPanjang();
        PersegiPanjang persegi3 = new PersegiPanjang();

        persegi1.cetakPersegiPanjang();

        persegi2.setPanjang(6);
        persegi2.setLebar(8);
        System.out.println("---------------------------------------");
        System.out.println("Panjang: " + persegi2.getPanjang());
        System.out.println("Lebar: " + persegi2.getLebar());
        System.out.println("Luas: " + persegi2.cariLuas());
        System.out.println("Keliling: " + persegi2.cariKeliling());
        System.out.println("Diagonal: " + persegi2.cariDiagonal());
        System.out.println("---------------------------------------");

        persegi3.setPersegiPanjang(9, 12);
        persegi3.cetakPersegiPanjang();
    }

    static Integer inputInteger(String pesan){
        System.out.println(pesan);
        return Integer.parseInt(sc.nextLine());
    } 
}

class PersegiPanjang {
    private double panjang;
    private double lebar;

    PersegiPanjang(){}
    PersegiPanjang(int panjang, int lebar){
        this.panjang = panjang;
        this.lebar = lebar;
    }

    public double getLebar() {
        return lebar;
    }
    public double getPanjang() {
        return panjang;
    }
    public void setLebar(double lebar) {
        this.lebar = lebar;
    }
    public void setPanjang(double panjang) {
        this.panjang = panjang;
    }
    public void setPersegiPanjang(double panjang, double lebar){
        this.panjang = panjang;
        this.lebar = lebar;
    }
    public void cetakPersegiPanjang(){
        System.out.println("---------------------------------------");
        System.out.println("Panjang: " + panjang);
        System.out.println("Lebar: " + lebar);
        System.out.println("Luas: " + cariLuas());
        System.out.println("Keliling: " + cariKeliling());
        System.out.println("Diagonal: " + cariDiagonal());
        System.out.println("---------------------------------------");
    }
    public double cariLuas(){
        return (panjang * lebar);
    }
    public double cariKeliling(){
        return (2*(panjang + lebar));
    }
    public double cariDiagonal(){
        return Math.sqrt(Math.pow(panjang, 2) + Math.pow(lebar,2));
    }
}