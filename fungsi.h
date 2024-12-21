#ifndef VALIDASI_H
#define VALIDASI_H

#define MAX_KENDARAAN 100
#define SLOT_PER_LANTAI_MOBIL 36
#define SLOT_PER_LANTAI_MOTOR 72
#define LANTAI_MOBIL 2
#define LANTAI_MOTOR 1

// Struktur data untuk mencatat detail kendaraan
typedef struct {
    char nomorKendaraan[20];
    char jenisKendaraan[20]; // Contoh: "Mobil" atau "Motor"
    int waktuMasuk;          // Format waktu dalam menit (misal: 840 untuk jam 14:00)
    int waktuKeluar;         // Format waktu dalam menit
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
    int jamMasuk, menitMasuk;

    printf("Masukkan nomor kendaraan (contoh: R 1711 SR): ");
    getchar(); // Membersihkan buffer input
    fgets(nomor, sizeof(nomor), stdin);
    nomor[strcspn(nomor, "\n")] = 0; // Menghapus karakter newline

    printf("Masukkan jenis kendaraan (Mobil/Motor): ");
    scanf("%s", jenis);
    printf("Masukkan waktu masuk (jam menit, format 24 jam): ");
    scanf("%d %d", &jamMasuk, &menitMasuk);

    // Menghitung waktu masuk dalam menit
    int waktuMasuk = jamMasuk * 60 + menitMasuk;

    // Simpan detail kendaraan
    strcpy(kendaraan[jumlahKendaraan].nomorKendaraan, nomor);
    strcpy(kendaraan[jumlahKendaraan].jenisKendaraan, jenis);
    kendaraan[jumlahKendaraan].waktuMasuk = waktuMasuk;
    kendaraan[jumlahKendaraan].aktif = 1;
    jumlahKendaraan++;

    printf("\n--- Karcis Parkir Masuk ---\n");
    printf("Nomor Kendaraan: %s\n", nomor);
    printf("Jenis Kendaraan: %s\n", jenis);
    printf("Waktu Masuk: %d:%02d\n", jamMasuk, menitMasuk);
    printf("---------------------------\n");
    printf("Kendaraan berhasil dicatat.\n");
}

// Fungsi untuk menampilkan denah parkir
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

// Fungsi untuk memarkir kendaraan
void parkir_kendaraan(int slot_parkir[], int slot_per_lantai, int lantai) {
    if(kendaraan.jenisKendaraan == "Mobil"){
        
    }
    tampilkan_denah(slot_parkir, lantai, slot_per_lantai);
    printf("Masukkan nomor slot yang ingin digunakan (1-%d): ", slot_per_lantai);
    int slot;
    scanf("%d", &slot);

    if (slot > 0 && slot <= slot_per_lantai) {
        if (slot_parkir[slot - 1] == 0) {
            slot_parkir[slot - 1] = 1;
            printf("Kendaraan berhasil diparkir di Lantai %d, Slot %d.\n", lantai + 1, slot);
        } else {
            printf("Slot %d di Lantai %d sudah terisi.\n", slot, lantai + 1);
        }
    } else {
        printf("Nomor slot tidak valid!\n");
    }
}

// Fungsi untuk mengosongkan slot
void keluarkan_kendaraan(int slot_parkir[], int slot_per_lantai, int lantai) {
    tampilkan_denah(slot_parkir, lantai, slot_per_lantai);
    printf("Masukkan nomor slot yang ingin dikosongkan (1-%d): ", slot_per_lantai);
    int slot;
    scanf("%d", &slot);

    if (slot > 0 && slot <= slot_per_lantai) {
        if (slot_parkir[slot - 1] == 1) {
            slot_parkir[slot - 1] = 0;
            printf("Slot %d di Lantai %d berhasil dikosongkan.\n", slot, lantai + 1);
        } else {
            printf("Slot %d di Lantai %d sudah kosong.\n", slot, lantai + 1);
        }
    } else {
        printf("Nomor slot tidak valid!\n");
    }
}


float hitung(int durasi, char jenis[20]) {
    float tarif = 0;

    if (strcmp(jenis, "Motor") == 0) { // Motor
        if (durasi <= 2) {
            tarif = 2000;
        } else if (durasi < 24) {
            tarif = 2000 + (durasi - 2) * 2000;
        } else {
            tarif = 20000;
        }
    } else if (strcmp(jenis, "Mobil") == 0) { // Mobil
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

// Fungsi untuk kendaraan keluar
void kendaraanKeluar() {
    char nomor[20];
    int jamKeluar, menitKeluar;
    int durasiJam;

    printf("Masukkan nomor kendaraan yang keluar: ");
    getchar(); // Membersihkan buffer input
    fgets(nomor, sizeof(nomor), stdin);
    nomor[strcspn(nomor, "\n")] = 0; // Menghapus karakter newline

    printf("Masukkan waktu keluar (jam menit, format 24 jam): ");
    scanf("%d %d", &jamKeluar, &menitKeluar);

    // Menghitung waktu keluar dalam menit
    int waktuKeluar = jamKeluar * 60 + menitKeluar;

    // Cari kendaraan berdasarkan nomor
    for (int i = 0; i < jumlahKendaraan; i++) {
        if (kendaraan[i].aktif && strcmp(kendaraan[i].nomorKendaraan, nomor) == 0) {
            kendaraan[i].waktuKeluar = waktuKeluar;
            kendaraan[i].aktif = 0;

            // Hitung durasi dan tarif
            int durasi = (waktuKeluar - kendaraan[i].waktuMasuk);
            if (durasi < 0) {
                durasi += 1440; // Penanganan jika waktu keluar melewati tengah malam
            }
            durasi = durasi / 60; // Durasi dalam jam

            float tarif = hitung(durasi, kendaraan[i].jenisKendaraan);

            // Tampilkan struk
            printf("\n--- Karcis Parkir Keluar ---\n");
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

            return;
        }
    }

    printf("Kendaraan dengan nomor %s tidak ditemukan atau sudah keluar.\n", nomor);
}

#endif
