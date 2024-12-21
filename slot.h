#ifndef SLOT_H
#define SLOT_H

#define SLOT_PER_LANTAI_MOBIL 36
#define SLOT_PER_LANTAI_MOTOR 72
#define LANTAI_MOBIL 2
#define LANTAI_MOTOR 1

void tampilkan_denah(int slot_parkir[], int lantai, int slot_per_lantai);
void parkir_kendaraan(int slot_parkir[], int slot_per_lantai, int lantai);
void keluarkan_kendaraan(int slot_parkir[], int slot_per_lantai, int lantai);

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

#endif
