#include <stdio.h>

#define SLOT_PER_LANTAI_MOBIL 36
#define SLOT_PER_LANTAI_MOTOR 72
#define LANTAI_MOBIL 2
#define LANTAI_MOTOR 1

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
    printf("--------------------------------------------\n");
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

int main() {
    int slot_mobil[LANTAI_MOBIL][SLOT_PER_LANTAI_MOBIL] = {0};
    int slot_motor[LANTAI_MOTOR][SLOT_PER_LANTAI_MOTOR] = {0};

    int pilihan, jenis_kendaraan, lantai;

    do {
        printf("\n--- SISTEM PARKIR MULTI-LANTAI ---\n");
        printf("1. Parkir Kendaraan\n");
        printf("2. Kendaraan Keluar\n");
        printf("3. Tampilkan Status Parkir\n");
        printf("4. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                printf("Pilih jenis kendaraan:\n");
                printf("1. Motor (Lantai 1)\n");
                printf("2. Mobil (Lantai 2 dan 3)\n");
                printf("Pilih jenis kendaraan: ");
                scanf("%d", &jenis_kendaraan);

                if (jenis_kendaraan == 1) {
                    lantai = 0; // Motor hanya di lantai 1
                    parkir_kendaraan(slot_motor[lantai], SLOT_PER_LANTAI_MOTOR, lantai);
                } else if (jenis_kendaraan == 2) {
                    printf("Masukkan lantai untuk mobil (2-3): ");
                    scanf("%d", &lantai);

                    if (lantai >= 2 && lantai <= 3) {
                        parkir_kendaraan(slot_mobil[lantai - 2], SLOT_PER_LANTAI_MOBIL, lantai - 2);
                    } else {
                        printf("Lantai tidak valid untuk mobil.\n");
                    }
                } else {
                    printf("Jenis kendaraan tidak valid!\n");
                }
                break;

            case 2:
                printf("Pilih jenis kendaraan:\n");
                printf("1. Motor\n");
                printf("2. Mobil\n");
                printf("Pilih jenis kendaraan: ");
                scanf("%d", &jenis_kendaraan);

                if (jenis_kendaraan == 1) {
                    lantai = 0; // Motor hanya di lantai 1
                    keluarkan_kendaraan(slot_motor[lantai], SLOT_PER_LANTAI_MOTOR, lantai);
                } else if (jenis_kendaraan == 2) {
                    printf("Masukkan lantai kendaraan keluar (2-3): ");
                    scanf("%d", &lantai);

                    if (lantai >= 2 && lantai <= 3) {
                        keluarkan_kendaraan(slot_mobil[lantai - 2], SLOT_PER_LANTAI_MOBIL, lantai - 2);
                    } else {
                        printf("Lantai tidak valid untuk mobil.\n");
                    }
                } else {
                    printf("Jenis kendaraan tidak valid!\n");
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
                printf("Keluar dari sistem parkir.\n");
                break;

            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 4);

    return 0;
}
