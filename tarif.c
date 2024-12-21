#include <stdio.h>
#include <string.h>

float hitung(int durasi, char jenis);
void menu();
void save(const char *platNomor, char jenis, int durasi, float tarif);

int main() {
    int pilihan;
    int durasi, jumlahmotor = 0, jumlahmobil = 0;
    char jenis;
    char platNomor[50]; 
    float tarif, pendapatan = 0;

    do {
        menu();
        printf("Pilih menu: ");
        scanf("%d", &pilihan);
        getchar(); 

        switch (pilihan) {
        case 1:
            printf("Masukkan jenis kendaraan: ");
            scanf(" %c", &jenis);
            getchar(); 

            if (jenis != 'M' && jenis != 'C') {
                printf("Jenis kendaraan tidak valid. Silakan coba lagi.\n");
                break;
            }

            printf("Masukkan plat nomor kendaraan: ");
            fgets(platNomor, sizeof(platNomor), stdin);
            platNomor[strcspn(platNomor, "\n")] = 0;

            printf("Masukkan durasi parkir: ");
            if (scanf("%d", &durasi) != 1 || durasi <= 0) {
                printf("Durasi parkir tidak valid. Masukkan angka positif.\n");
                while (getchar() != '\n');
                break;
            }

            tarif = hitung(durasi, jenis);
            pendapatan += tarif;

            if (jenis == 'M') jumlahmotor++;
            else jumlahmobil++;

            save(platNomor, jenis, durasi, tarif);

            printf("\n=== Struk Parkir ===\n");
            printf("Plat Nomor: %s\n", platNomor);
            printf("Jenis Kendaraan: %s\n", jenis == 'M' ? "Motor" : "Mobil");
            printf("Durasi Parkir: %d jam\n", durasi);
            printf("Total Biaya: Rp%.2f\n", tarif);
            printf("====================\n\n");
            break;

        case 2:
            printf("\n=== Laporan Sementara ===\n");
            printf("Total Motor: %d\n", jumlahmotor);
            printf("Total Mobil: %d\n", jumlahmobil);
            printf("Pendapatan Sementara: Rp%.2f\n", pendapatan);
            printf("==========================\n\n");
            break;

        case 3:
            printf("Terima kasih telah menggunakan sistem parkir!\n");
            break;

        default:
            printf("Pilihan tidak valid. Silakan coba lagi.\n");
        }
    } while (pilihan != 3);

    return 0;
}

float hitung(int durasi, char jenis) {
    float tarif = 0;

    if (jenis == 'M') { // Motor
        if (durasi <= 2) {
            tarif = 2000;
        } else if (durasi < 24) {
            tarif = 2000 + (durasi - 2) * 2000;
        } else {
            tarif = 20000;
        }
    } else if (jenis == 'C') { // Mobil
        if (durasi <= 2) {
            tarif = 5000;
        } else if (durasi < 24) {
            tarif = 5000 + (durasi - 2) * 3000;
        } else {
            tarif = 50000;
        }
    }

    return tarif;
}

void menu() {
    printf("\n=== Parkir Mall Fadhil ===\n");
    printf("1. Bayar Parkir\n");
    printf("2. Lihat Laporan Sementara\n");
    printf("3. Keluar\n");
    printf("============================\n");
}

void save(const char *platNomor, char jenis, int durasi, float tarif) {
    FILE *file = fopen("parkir_log.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file untuk menyimpan data transaksi.\n");
        return;
    }

    fprintf(file, "Plat Nomor: %s\n", platNomor);
    fprintf(file, "Jenis Kendaraan: %s\n", jenis == 'M' ? "Motor" : "Mobil");
    fprintf(file, "Durasi Parkir: %d jam\n", durasi);
    fprintf(file, "Total Biaya: Rp%.2f\n", tarif);
    fprintf(file, "-----------------------\n");

    fclose(file);
}

