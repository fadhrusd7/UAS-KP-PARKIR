#include <stdio.h>
#include <string.h>

#define MAX_KENDARAAN 100

// Struktur data untuk mencatat detail kendaraan
typedef struct {
    char nomorKendaraan[20];
    char jenisKendaraan[20]; // Contoh: "Mobil" atau "Motor"
    int waktuMasuk;          // Format jam (24 jam, misalnya 14 untuk jam 2 siang)
} Kendaraan;

// Array untuk menyimpan data kendaraan
Kendaraan kendaraan[MAX_KENDARAAN];
int jumlahKendaraan = 0; // Counter untuk kendaraan yang dicatat

// Fungsi untuk mencatat detail kendaraan
void catatDetailKendaraan() {
    if (jumlahKendaraan >= MAX_KENDARAAN) {
        printf("Maaf, kapasitas pencatatan penuh.\n");
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
    jumlahKendaraan++;

    printf("Detail kendaraan berhasil dicatat.\n");
}

// Fungsi untuk menampilkan data kendaraan yang dicatat
void tampilkanDataKendaraan() {
    if (jumlahKendaraan == 0) {
        printf("Belum ada kendaraan yang dicatat.\n");
        return;
    }

    printf("\nData Kendaraan yang Dicatat:\n");
    for (int i = 0; i < jumlahKendaraan; i++) {
        printf("Kendaraan %d:\n", i + 1);
        printf("  Nomor Kendaraan: %s\n", kendaraan[i].nomorKendaraan);
        printf("  Jenis Kendaraan: %s\n", kendaraan[i].jenisKendaraan);
        printf("  Waktu Masuk: %d:00\n", kendaraan[i].waktuMasuk);
    }
}

// Fungsi utama
int main() {
    int pilihan;

    do {
        printf("\n=== Pencatatan Detail Kendaraan ===\n");
        printf("1. Catat Kendaraan\n");
        printf("2. Tampilkan Data Kendaraan\n");
        printf("3. Keluar Program\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                catatDetailKendaraan();
                break;
            case 2:
                tampilkanDataKendaraan();
                break;
            case 3:
                printf("Terima kasih telah menggunakan sistem pencatatan.\n");
                break;
            default:
                printf("Pilihan tidak valid. Coba lagi.\n");
        }
    } while (pilihan != 3);

    return 0;
}
