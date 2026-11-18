#include <iostream> 
#include <cstdio>
#include <string>
using namespace std;
// Kode % (Format Specifier): %d = int/bool, %f = float/double, %c = char, %s = string (wajib .c_str())

// Fungsi void tanpa parameter (hanya menjalankan perintah)
void cetakGaris() {
    printf("------------------------------\n");
}

// Fungsi void dengan parameter
void sapaUser(string nama) {
    printf("Halo, %s!\n", nama.c_str());
}

// Fungsi dengan return value (mengembalikan nilai hasil proses)
int hitungTambah(int a, int b) {
    return a + b;
}

int main() {
// 1. TIPE DATA & VARIABEL
    int angkaBulat = 10;
    float angkaDesimal = 3.14f;
    double desimalPresisi = 3.141592;
    char karakter = 'A';
    bool status = true;
    string teks = "Belajar C++";
    const int NILAI_TETAP = 100;

    printf("Teks        : %s\n", teks.c_str());
    printf("Angka Bulat : %d\n", angkaBulat);
    printf("Float       : %.2f\n", angkaDesimal);
    printf("Double      : %f\n", desimalPresisi);
    printf("Karakter    : %c\n", karakter);
    printf("Boolean     : %d\n", status);
    printf("Konstanta   : %d\n", NILAI_TETAP);
    cetakGaris();

// 2. INPUT & OUTPUT (I/O)
    string nama;
    int nilai;

    printf("Masukkan nama (1 kata) : ");
    cin >> nama;
    printf("Masukkan nilai (0-100) : ");
    cin >> nilai;
    cetakGaris();

// 3. KONDISI / PERCABANGAN (IF - ELSE)
    if (nilai < 0 || nilai > 100) { //simbol (||) itu untuk Or
        printf("Nilai tidak valid!\n");
    } else if (nilai >= 80 && nilai <= 100) { //simbol (&&) itu untuk and
        printf("Predikat: A (Sangat Baik)\n");
    } else if (nilai >= 60) {
        printf("Predikat: B (Lulus)\n");
    } else {
        printf("Predikat: C (Mengulang)\n");
    }
    cetakGaris();

// 4. PERULANGAN (LOOPS)
    // Perulangan FOR
    printf("Perulangan FOR (1 sampai 5): ");
    for (int i = 1; i <= 5; i++) {
        printf("%d ", i);
    }
    printf("\n");

    // Perulangan WHILE
    printf("Perulangan WHILE (mundur dari 3): ");
    int hitung = 3;
    while (hitung > 0) {
        printf("%d ", hitung);
        hitung--;
    }
    printf("\n");
    cetakGaris();

    sapaUser(nama);

    int hasil = hitungTambah(15, 25);
    printf("Hasil fungsi tambah (15 + 25) = %d", hasil);

    return 0;
}