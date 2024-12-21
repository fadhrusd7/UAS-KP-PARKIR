#include <stdio.h>
#include <string.h>
#include "fungsi.h"


int main() {

    int slot_mobil[LANTAI_MOBIL][SLOT_PER_LANTAI_MOBIL] = {0};
    int slot_motor[LANTAI_MOTOR][SLOT_PER_LANTAI_MOTOR] = {0};

    int pilihan, jenis_kendaraan, lantai;

    char nomor[20];
    char jenis[20];
    int waktu;
    
    printf("----PARKIR----\n");
    printf("--------------\n");
    printf("YU EN ES PLAZA\n");
    printf("--------------\n");
    do {
        printf("\n1. Kendaraan Masuk\n");
        printf("2. Kendaraan Keluar\n");
        printf("3. Cek Slot Parkir\n");
        printf("4. Cek Data\n");
        printf("5. Keluar Program\n");
        printf("Pilih menu: ");
        int pilihan;
        scanf("%d", &pilihan);
        switch (pilihan) {
            case 1:
                kendaraanMasuk(nomor, jenis, waktu);
                parkir_kendaraan(slot_motor[0], SLOT_PER_LANTAI_MOTOR, 0);
                break;
            case 2:
                kendaraanKeluar();
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
                FILE *file = fopen("parkir_log.txt", "r");
                if(file == NULL){
                    printf("Error opening file\n");
                    return 1;
                    fclose(file);
                }
            case 5:
                printf("Terima kasih telah menggunakan program ini.\n");
                return 0;
            default:
                printf("Menu tidak valid. Silakan coba lagi.\n");
        }
    } while (1);
}
    
