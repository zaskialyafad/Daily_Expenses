#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { // untuk membuat tipe data baru yang menyimpan data nama saldo(tunai, debit, gopay, dll) dan isi saldo.
    char *nama;
    int isiSaldo;
} saldo; 

saldo dompet[6]; //array untuk menyipan jenis dompet

typedef struct
{
    char *kategori; //kategori pengeluaran atau pemasukkan misalnya untuk makan, minum, tranfer dan sebagainya.
    int jumlahUang; // jumlah uang yang masuk atau keluar
    char *dompet; //tempat uangnya
    char *tanggal; //tanggal transaksi dilakukan
    int saldoAwal; //saldo sebelum uang masuk atau kelur
    int saldoAkhir; ///saldo setelah uang masuk atau keluar
}transaksi;

transaksi riwayat [100]; // array untuk menyimpan riwayat
int pilihan; // untuk memilih menu yang ingin digunakan
int noRiwayat = 0; // indeks untuk array riwayat yang diinisiasi 0

void isiSaldoAwal() { // untuk mengisi isi saldo awal di dompet. Diiniasi setiap dompet isinya 0, 
    //isi saldo dimasukkan manual dengan menu tambah pemasukan
    dompet[0].nama = "Tunai";
    dompet[0].isiSaldo = 0;

    dompet[1].nama = "Debit";
    dompet[1].isiSaldo = 0;

    dompet[2].nama = "GoPay";
    dompet[2].isiSaldo = 0;

    dompet[3].nama = "ShopeePay";
    dompet[3].isiSaldo = 0;

    dompet[4].nama = "OVO";
    dompet[4].isiSaldo = 0;

    dompet[5].nama = "DANA";
    dompet[5].isiSaldo = 0;
}


void tampilkanDompet(){ //fungsi untuk menampilkan jenis-jenis dompet
    for (int i = 0; i < 6; i++) {
        printf("%d. %s\n", i + 1, dompet[i].nama);
    }
    printf ("Pilih jenis dompet : ");
    scanf ("%d", &pilihan);

    while (pilihan < 1 || pilihan > 6){
        printf("Pilihan tidak valid!\n");
        printf ("Pilih jenis dompet : ");
        scanf ("%d", &pilihan);
    }

}

void pemasukkan(){ // fungsi untuk menu pemasukan
    printf("\n");
    printf("=====Tambah Pemasukan=====\n");
    tampilkanDompet();
    char tempKategori[100], tempTanggal[20]; // untuk menaruh nilai sementara kategori dan tanggal
    int jumlah;
    printf("==============================\n");
    printf("\nKategori           : ");
    scanf(" %100s", tempKategori);

    printf("Jumlah pemasukkan   : Rp. ");
    scanf(" %d", &jumlah);

    printf("Tanggal (YYYY-MM-DD): ");
    scanf(" %20s", tempTanggal);

    //variabel dimasukkan ke riwayat
    riwayat[noRiwayat].kategori = strdup(tempKategori); //strrdup digunakan untuk menyalin input dari user
    riwayat[noRiwayat].jumlahUang = jumlah;
    riwayat[noRiwayat].tanggal = strdup(tempTanggal);
    riwayat[noRiwayat].dompet = strdup(dompet[pilihan - 1].nama);

    riwayat[noRiwayat].saldoAwal = dompet[pilihan - 1].isiSaldo;
    dompet[pilihan - 1].isiSaldo += jumlah;
    riwayat[noRiwayat].saldoAkhir = dompet[pilihan - 1].isiSaldo;

    noRiwayat++;
    printf("Pemasukkan telah dicatat! :D\n");
    printf("==============================\n");
    printf("\n");
}

void pengeluaran(){ //fungsi untuk menu pengeluaran
    //isinya masih sama dengan fungsi pemasukan tapi dimodifikasi sedikit
    printf("\n");
    printf("=====Tambah Pengeluaran=====\n");
    tampilkanDompet();
    char tempKategori[100], tempTanggal[20];
    int jumlah;
    printf("==============================\n");     
    printf("\nKategori              : ");
    scanf("%100s", tempKategori);

    printf("Jumlah Pengeluaran    : Rp.  ");
    scanf("%d", &jumlah);

    printf("Tanggal (YYYY-MM-DD)   : ");
    scanf("%20s", tempTanggal);

    riwayat[noRiwayat].kategori = strdup(tempKategori); 
    riwayat[noRiwayat].jumlahUang = jumlah;
    riwayat[noRiwayat].tanggal = strdup(tempTanggal);
    riwayat[noRiwayat].dompet = strdup(dompet[pilihan - 1].nama);

    riwayat[noRiwayat].saldoAwal = dompet[pilihan - 1].isiSaldo;
    dompet[pilihan - 1].isiSaldo -= jumlah;
    riwayat[noRiwayat].saldoAkhir = dompet[pilihan - 1].isiSaldo;

    noRiwayat++;
    printf("Pengeluaran telah dicatat! :D\n");
    printf("==============================\n");
    printf("\n");
};

void lihatSaldo(){ //fungsi untuk melihat isi saldo
    printf("==============================\n");
    for(int i = 0; i < 6; i++){
        printf("%d. %s : Rp. %d\n", i+1, dompet[i].nama, dompet[i].isiSaldo);
    }
    printf("==============================\n");
};

void tampilkanRiwayat() { //fungsi untuk menampilkan riwayat
    printf("==============================\n");
    printf("\n");
    printf("\n===== RIWAYAT =====\n");
    for (int i = 0; i < noRiwayat; i++) {
        printf("%d. [%s] %s - Rp%d (%s) (saldo awal : %d) (saldo akhir : %d)\n",
            i + 1, riwayat[i].tanggal, riwayat[i].kategori, riwayat[i].jumlahUang,
            riwayat[i].dompet, riwayat[i].saldoAwal, riwayat[i].saldoAkhir);
    }
    printf("==============================\n");
}

void beranda(){ //fungsi untuk menu utama
    do{
        printf("\n");
        printf ("===== MENU UTAMA =====\n");
        printf ("1. Tambah Pemasukan\n");
        printf ("2. Tambah Pengeluaran\n");
        printf ("3. Lihat Saldo\n");
        printf ("4. Lihat riwayat\n");
        printf ("0. Keluar\n");
        printf ("Pilih menu: ");
        scanf ("%d", &pilihan);
    
        if (pilihan == 1) {
                pemasukkan();
            } else if (pilihan == 2) {
                pengeluaran();  
            } else if (pilihan == 3) {
                lihatSaldo();
            } else if (pilihan == 4) {
                tampilkanRiwayat();
            } else if (pilihan == 0) {
                printf("Keluar dari program.\n");
            } else {
                printf("Pilihan tidak valid!\n");
            }
    } while (pilihan != 0);
    printf("\n");
}

void bersihkanMemori(){ //karena menggunakan strdup, perlu ada free() untuk enghindari memory leak
    for (int i = 0; i < noRiwayat; i++) {
        free(riwayat[i].kategori);
        free(riwayat[i].dompet);
        free(riwayat[i].tanggal);
    }
}


int main() { 
    isiSaldoAwal();
    beranda();
    bersihkanMemori();
    return 0;
}





