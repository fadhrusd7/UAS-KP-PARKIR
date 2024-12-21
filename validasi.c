#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_KENDARAAN 100

// Struktur data untuk mencatat detail kendaraan
typedef struct {
    char nomorKendaraan[20];
    char jenisKendaraan[20]; // Contoh: "Mobil" atau "Motor"
    int waktuMasuk;          // Format jam (24 jam, misalnya 14 untuk jam 2 siang)
    int waktuKeluar;         // Format jam
    int aktif;               // 1 jika kendaraan masih parkir, 0 jika sudah keluar
} Kendaraan;

// Array untuk menyimpan data kendaraan
Kendaraan kendaraan[MAX_KENDARAAN];
int jumlahKendaraan = 0;

// Fungsi untuk mencatat kendaraan masuk
void kendaraanMasuk() {
    if (jumlahKendaraan >= MAX_KENDARAAN) {
        printf("Maaf, kapasitas parkir penuh.\n");
        return;
    }

    char nomor[20];
    char jenis[20];
    int waktu;

    printf("Masukkan nomor kendaraan (contoh: R 1711 SR): ");
    getchar(); // Membersihkan buffer input
    fgets(nomor, sizeof(nomor), stdin);
    nomor[strcspn(nomor, "\n")] = 0; // Menghapus karakter newline

    printf("Masukkan jenis kendaraan (Mobil/Motor): ");
    scanf("%s", jenis);
    printf("Masukkan waktu masuk (jam 24 format, misalnya 14 untuk jam 2 siang): ");
    scanf("%d", &waktu);

    // Simpan detail kendaraan
    strcpy(kendaraan[jumlahKendaraan].nomorKendaraan, nomor);
    strcpy(kendaraan[jumlahKendaraan].jenisKendaraan, jenis);
    kendaraan[jumlahKendaraan].waktuMasuk = waktu;
    kendaraan[jumlahKendaraan].aktif = 1;
    jumlahKendaraan++;

    printf("\n--- Karcis Parkir Masuk ---\n");
    printf("Nomor Kendaraan: %s\n", nomor);
    printf("Jenis Kendaraan: %s\n", jenis);
    printf("Waktu Masuk: %d:00\n", waktu);
    printf("---------------------------\n");
    printf("Kendaraan berhasil dicatat.\n");
}

// Fungsi untuk mencatat kendaraan keluar
void kendaraanKeluar() {
    char nomor[20];
    int waktuKeluar;

    printf("Masukkan nomor kendaraan yang keluar: ");
    getchar(); // Membersihkan buffer input
    fgets(nomor, sizeof(nomor), stdin);
    nomor[strcspn(nomor, "\n")] = 0; // Menghapus karakter newline

    printf("Masukkan waktu keluar (jam 24 format, misalnya 16 untuk jam 4 sore): ");
    scanf("%d", &waktuKeluar);

    // Cari kendaraan berdasarkan nomor
    for (int i = 0; i < jumlahKendaraan; i++) {
        if (kendaraan[i].aktif && strcmp(kendaraan[i].nomorKendaraan, nomor) == 0) {
            kendaraan[i].waktuKeluar = waktuKeluar;
            kendaraan[i].aktif = 0;

            printf("\n--- Karcis Parkir Keluar ---\n");
            printf("Nomor Kendaraan: %s\n", kendaraan[i].nomorKendaraan);
            printf("Jenis Kendaraan: %s\n", kendaraan[i].jenisKendaraan);
            printf("Waktu Masuk: %d\n", kendaraan[i].waktuMasuk);
            printf("Waktu Keluar: %d:00\n", kendaraan[i].waktuKeluar);
            printf("Durasi Parkir: %d jam\n", kendaraan[i].waktuKeluar - kendaraan[i].waktuMasuk);
            printf("----------------------------\n");
            printf("Kendaraan berhasil keluar.\n");
            return;
        }
    }

    printf("Kendaraan dengan nomor %s tidak ditemukan atau sudah keluar.\n", nomor);
}

// Fungsi utama
int main() {
    int pilihan;

    do {
        printf("\n=== Sistem Parkir ===\n");
        printf("1. Kendaraan Masuk\n");
        printf("2. Kendaraan Keluar\n");
        printf("3. Keluar Program\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                kendaraanMasuk();
                break;
            case 2:
                kendaraanKeluar();
                break;
            case 3:
                printf("Terima kasih telah menggunakan sistem parkir.\n");
                break;
            default:
                printf("Pilihan tidak valid. Coba lagi.\n");
        }
    } while (pilihan != 3);

    return 0;
}
