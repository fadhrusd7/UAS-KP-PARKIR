#include <stdio.h>
#include <string.h>
#include "fungsi.h"

#define MAX_KENDARAAN 100
#define SLOT_PER_LANTAI_MOBIL 36
#define SLOT_PER_LANTAI_MOTOR 72
#define LANTAI_MOBIL 2
#define LANTAI_MOTOR 1

int main() {

    int slot_mobil[LANTAI_MOBIL][SLOT_PER_LANTAI_MOBIL] = {0};
    int slot_motor[LANTAI_MOTOR][SLOT_PER_LANTAI_MOTOR] = {0};

    int pilihan, jenis_kendaraan, lantai;

    char nomor[20];
    char jenis[20];
    int waktu;
    
    printf("------PARKIR------\n");
    printf("------------------\n");
    printf("    U N S MALL    \n");
    printf("------------------\n");
    do {
        printf("\n1. Kendaraan Masuk\n");
        printf("2. Kendaraan Keluar\n");
        printf("3. Cek Slot Parkir\n");
        printf("4. Cari Kendaraan\n");
        printf("5. Cek Data\n");
        printf("6. Keluar Program\n");
        printf("Pilih menu: ");
        int pilihan;
        scanf("%d", &pilihan);
        switch (pilihan) {
            case 1:
                printf("1. Mobil\n2. Motor\nMasukkan jenis kendaraan : ");
                scanf("%d", &jenis_kendaraan);
                if (jenis_kendaraan == 1) {
                    printf("Masukkan lantai parkir (2 atau 3): ");
                    scanf("%d", &lantai);
                    if (lantai >= 2 && lantai <= 3) {
                        kendaraanMasuk(slot_mobil[lantai - 2], SLOT_PER_LANTAI_MOBIL, lantai - 1, "Mobil");
                    } else {
                        printf("Lantai tidak valid. Silakan coba lagi.\n");
                    }
                } else if (jenis_kendaraan == 2) {
                    kendaraanMasuk(slot_motor[0], SLOT_PER_LANTAI_MOTOR, 0, "Motor");
                } else {
                    printf("Jenis kendaraan tidak valid. Silakan coba lagi.\n");
                }
                break;
            case 2:
                printf("1. Mobil\n2. Motor\nMasukkan jenis kendaraan : ");
                scanf("%d", &jenis_kendaraan);
                if (jenis_kendaraan == 1) {
                    printf("Masukkan lantai parkir (2 atau 3): ");
                    scanf("%d", &lantai);
                    if (lantai >= 2 && lantai <= 3) {
                        kendaraanKeluar(slot_mobil[lantai - 2], SLOT_PER_LANTAI_MOBIL, lantai - 1);
                    } else {
                        printf("Lantai tidak valid. Silakan coba lagi.\n");
                    }
                } else if (jenis_kendaraan == 2) {
                    kendaraanKeluar(slot_motor[0], SLOT_PER_LANTAI_MOTOR, 0);
                } else {
                    printf("Jenis kendaraan tidak valid. Silakan coba lagi.\n");
                }
                break;
            case 3:
                printf("\n--- Status Parkir Motor (Lantai 1) ---\n");
                tampilkan_denah(slot_motor[0], 0, SLOT_PER_LANTAI_MOTOR);

                for (int i = 0; i < LANTAI_MOBIL; i++) {
                    printf("\n--- Status Parkir Mobil (Lantai %d) ---\n", i + 2);
                    tampilkan_denah(slot_mobil[i], i + 1, SLOT_PER_LANTAI_MOBIL);
                }
                break;
            case 4:
                printf("Cari Kendaraan Anda\n");
                Carikendaraan();
                break;
            case 5:
                FILE *file = fopen("parkir_log.txt", "r");
                if (file == NULL) {
                    printf("Gagal membuka file.\n");
                    return 1;
                }
                printf("\n--- Data Parkir ---\n");
                char c;
                while ((c = fgetc(file)) != EOF) {
                    printf("%c", c);
                }
                fclose(file);
                break;
            case 6:
                printf("Terima kasih telah menggunakan program ini.\n");
                return 0;
            default:
                printf("Menu tidak valid. Silakan coba lagi.\n");
        }
    } while (1);
}
    
