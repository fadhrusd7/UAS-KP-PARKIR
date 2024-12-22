#ifndef FUNGSI_H
#define FUNGSI_H

#include <stdio.h>
#include <string.h>

#define MAX_KENDARAAN 100
#define SLOT_PER_LANTAI_MOBIL 36
#define SLOT_PER_LANTAI_MOTOR 72
#define LANTAI_MOBIL 2
#define LANTAI_MOTOR 1

typedef struct {
    char nomorKendaraan[20];
    char jenisKendaraan[20];
    int waktuMasuk;
    int waktuKeluar;
    int aktif;
    int slot;
    int lantai;
} Kendaraan;

Kendaraan kendaraan[MAX_KENDARAAN];
int jumlahKendaraan = 0;

void tampilkan_denah(int slot_parkir[], int lantai, int slot_per_lantai) {
    printf("\nDenah Parkir Lantai %d:\n", lantai + 1);
    printf("--------------------------------------------\n");

    for (int i = 0; i < slot_per_lantai; i++) {
        printf("| %-2d:%-6s ", i + 1, slot_parkir[i] == 0 ? "Kosong" : "Ada");
        if ((i + 1) % 6 == 0) {
            printf("|\n");
        }
    }
    printf("----------------------------------------------------------------------\n");
}

void kendaraanMasuk(int slot_parkir[], int slot_per_lantai, int lantai, const char *jenis) {
    if (jumlahKendaraan >= MAX_KENDARAAN) {
        printf("Maaf, kapasitas parkir penuh.\n");
        return;
    }

    char nomor[20];
    int jamMasuk, menitMasuk;

    printf("Masukkan nomor kendaraan (contoh: R 1711 SR): ");
    getchar(); // Membersihkan buffer input
    fgets(nomor, sizeof(nomor), stdin);
    nomor[strcspn(nomor, "\n")] = 0; // Menghapus karakter newline

    printf("Masukkan waktu masuk (jam menit, format 24 jam): ");
    if (scanf("%d %d", &jamMasuk, &menitMasuk) != 2 || jamMasuk < 0 || jamMasuk >= 24 || menitMasuk < 0 || menitMasuk >= 60) {
        printf("Waktu masuk tidak valid. Jam harus antara 0-23 dan menit harus antara 0-59.\n");
        while (getchar() != '\n'); // Membersihkan buffer input
        return;
    }

    int waktuMasuk = jamMasuk * 60 + menitMasuk;

    strcpy(kendaraan[jumlahKendaraan].nomorKendaraan, nomor);
    strcpy(kendaraan[jumlahKendaraan].jenisKendaraan, jenis);
    kendaraan[jumlahKendaraan].waktuMasuk = waktuMasuk;
    kendaraan[jumlahKendaraan].aktif = 1;
    kendaraan[jumlahKendaraan].lantai = lantai;

    tampilkan_denah(slot_parkir, lantai, slot_per_lantai);

    printf("Masukkan nomor slot yang ingin digunakan (1-%d): ", slot_per_lantai);
    int slot;
    if (scanf("%d", &slot) != 1 || slot <= 0 || slot > slot_per_lantai) {
        printf("Nomor slot tidak valid!\n");
        while (getchar() != '\n'); // Membersihkan buffer input
        return;
    }

    if (slot_parkir[slot - 1] == 0) {
        slot_parkir[slot - 1] = 1;
        kendaraan[jumlahKendaraan].slot = slot - 1;
        printf("Kendaraan berhasil diparkir di Lantai %d, Slot %d.\n", lantai + 1, slot);
        jumlahKendaraan++;

        printf("\n--- Karcis Parkir Masuk U N S MALL---\n");
        printf("Nomor Kendaraan: %s\n", nomor);
        printf("Jenis Kendaraan: %s\n", jenis);
        printf("Waktu Masuk: %d:%02d\n", jamMasuk, menitMasuk);
        printf("Slot Parkir: Lantai %d, Slot %d\n", lantai + 1, slot);
        printf("---------------------------\n");
        printf("Kendaraan berhasil dicatat.\n");
    } else {
        printf("Slot %d di Lantai %d sudah terisi.\n", slot, lantai + 1);
    }
}

float hitung(int durasi, char jenis[20]) {
    float tarif = 0;

    if (strcmp(jenis, "Motor") == 0) {
        if (durasi <= 2) {
            tarif = 2000;
        } else if (durasi < 24) {
            tarif = 2000 + (durasi - 2) * 2000;
        } else {
            tarif = 20000;
        }
    } else if (strcmp(jenis, "Mobil") == 0) {
        if (durasi <= 2) {
            tarif = 5000;
        } else if (durasi < 24) {
            tarif = 5000 + (durasi - 2) * 3000;
        } else {
            tarif = 50000;
        }
    } else {
        printf("Jenis kendaraan tidak valid.\n");
    }

    return tarif;
}

void kendaraanKeluar(int slot_parkir[], int slot_per_lantai, int lantai) {
    char nomor[20];
    int jamKeluar, menitKeluar;

    printf("Masukkan nomor kendaraan yang keluar: ");
    getchar(); // Membersihkan buffer input
    fgets(nomor, sizeof(nomor), stdin);
    nomor[strcspn(nomor, "\n")] = 0; // Menghapus karakter newline

    printf("Masukkan waktu keluar (jam menit, format 24 jam): ");
    if (scanf("%d %d", &jamKeluar, &menitKeluar) != 2 || jamKeluar < 0 || jamKeluar >= 24 || menitKeluar < 0 || menitKeluar >= 60) {
        printf("Waktu keluar tidak valid. Jam harus antara 0-23 dan menit harus antara 0-59.\n");
        while (getchar() != '\n'); // Membersihkan buffer input
        return;
    }

    int waktuKeluar = jamKeluar * 60 + menitKeluar;

    for (int i = 0; i < jumlahKendaraan; i++) {
        if (kendaraan[i].aktif && strcmp(kendaraan[i].nomorKendaraan, nomor) == 0) {
            kendaraan[i].waktuKeluar = waktuKeluar;
            kendaraan[i].aktif = 0;

            int durasi = waktuKeluar - kendaraan[i].waktuMasuk;
            if (durasi < 0) {
                durasi += 1440;
            }
            durasi = (durasi + 59) / 60;

            float tarif = hitung(durasi, kendaraan[i].jenisKendaraan);

            printf("\n--- Karcis Parkir Keluar U N S MALL---\n");
            printf("Nomor Kendaraan: %s\n", kendaraan[i].nomorKendaraan);
            printf("Jenis Kendaraan: %s\n", kendaraan[i].jenisKendaraan);
            printf("Waktu Masuk: %d:%02d\n", kendaraan[i].waktuMasuk / 60, kendaraan[i].waktuMasuk % 60);
            printf("Waktu Keluar: %d:%02d\n", jamKeluar, menitKeluar);
            printf("Durasi Parkir: %d jam\n", durasi);
            printf("Tarif Parkir: Rp%.2f\n", tarif);
            printf("----------------------------\n");
            printf("Kendaraan berhasil keluar.\n");

            FILE *file = fopen("parkir_log.txt", "a");
            if (file == NULL) {
                printf("Gagal membuka file.\n");
                return;
            }
            fprintf(file, "Nomor Kendaraan: %s\n", kendaraan[i].nomorKendaraan);
            fprintf(file, "Jenis Kendaraan: %s\n", kendaraan[i].jenisKendaraan);
            fprintf(file, "Waktu Masuk: %d:%02d\n", kendaraan[i].waktuMasuk / 60, kendaraan[i].waktuMasuk % 60);
            fprintf(file, "Waktu Keluar: %d:%02d\n", jamKeluar, menitKeluar);
            fprintf(file, "Durasi Parkir: %d jam\n", durasi);
            fprintf(file, "Tarif Parkir: Rp%.2f\n", tarif);
            fprintf(file, "----------------------------\n");
            fclose(file);

            slot_parkir[kendaraan[i].slot] = 0;
            printf("Slot %d di Lantai %d berhasil dikosongkan.\n", kendaraan[i].slot + 1, kendaraan[i].lantai + 1);

            return;
        }
    }

    printf("Kendaraan dengan nomor %s tidak ditemukan atau sudah keluar.\n", nomor);
}

void Carikendaraan() {
    char nomor[20];
    printf("Masukkan nomor kendaraan yang dicari: ");
    getchar(); // Membersihkan buffer input
    fgets(nomor, sizeof(nomor), stdin);
    nomor[strcspn(nomor, "\n")] = 0; // Menghapus karakter newline

    for (int i = 0; i < jumlahKendaraan; i++) {
        if (kendaraan[i].aktif && strcmp(kendaraan[i].nomorKendaraan, nomor) == 0) {
            printf("Kendaraan ditemukan!\n");
            printf("Nomor Kendaraan: %s\n", kendaraan[i].nomorKendaraan);
            printf("Jenis Kendaraan: %s\n", kendaraan[i].jenisKendaraan);
            printf("Waktu Masuk: %d:%02d\n", kendaraan[i].waktuMasuk / 60, kendaraan[i].waktuMasuk % 60);
            printf("Slot Parkir: Lantai %d, Slot %d\n", kendaraan[i].lantai + 1, kendaraan[i].slot + 1);
            return;
        }
    }

    printf("Kendaraan dengan nomor %s tidak ditemukan.\n", nomor);
}

#endif
