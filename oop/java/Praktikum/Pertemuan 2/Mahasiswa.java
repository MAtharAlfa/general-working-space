public class Mahasiswa {
    private String nama;
    private float nilaiUTS;
    private float nilaiUAS;
    private float nilaiKuis;

    public void setMahasiswa(String nama, float nilaiUTS, float nilaiUAS, float nilaiKuis){
        this.nama = nama;
        this.nilaiUTS = nilaiUTS;
        this.nilaiUAS = nilaiUAS;
        this.nilaiKuis = nilaiKuis;
    }

    public Mahasiswa getMahasiswa(){
        return this;
    }

    public Mahasiswa(String nama, float nilaiUTS, float nilaiUAS, float nilaiKuis){
        this.nama = nama;
        this.nilaiUTS = nilaiUTS;
        this.nilaiUAS = nilaiUAS;
        this.nilaiKuis = nilaiKuis;
    }

    public void setNama(String nama){
        this.nama = nama;
    }
    public void setNilaiUTS(float nilaiUTS){
        this.nilaiUTS = nilaiUTS;
    }
    public void setNilaiUAS(float nilaiUAS){
        this.nilaiUAS = nilaiUAS;
    }
    public void setNilaiKuis(float nilaiKuis){
        this.nilaiKuis = nilaiKuis;
    }
    public String getNama(){
        return this.nama;
    }
    public float getNilaiUTS(){
        return this.nilaiUTS;
    }
    public float getNilaiUAS(){
        return this.nilaiUAS;
    }
    public float getNilaiKuis(){
        return this.nilaiKuis;
    }

    float hitungNilaiAkhir(){
        return this.nilaiKuis*0.2f + this.nilaiUTS*0.4f + this.nilaiUAS*0.4f;
    }
}