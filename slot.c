#include <stdio.h>

#define LANTAI 3
#define SLOT_PER_LANTAI 36
#define TOTAL_SLOT (LANTAI * SLOT_PER_LANTAI)

// Fungsi untuk menampilkan denah slot parkir di satu lantai
void tampilkan_denah_lantai(int slot_parkir[], int lantai, int slot_per_lantai) {
    printf("\nDenah Parkir Lantai %d:\n", lantai + 1);
    printf("--------------------------------------------\n");

    for (int i = 0; i < slot_per_lantai; i++) {
        int index = lantai * slot_per_lantai + i;
        // Menampilkan nomor slot dan status (kosong/ada)
        printf("| %-2d:%-6s ", i + 1, slot_parkir[index] == 0 ? "Kosong" : "Ada");
        
        // Tambah baris baru setiap 6 slot (6 kolom)
        if ((i + 1) % 6 == 0) {
            printf("|\n");
        }
    }
    printf("--------------------------------------------\n");
}

// Fungsi untuk menampilkan semua lantai
void tampilkan_status(int slot_parkir[], int total_slot, int slot_per_lantai) {
    for (int lantai = 0; lantai < LANTAI; lantai++) {
        tampilkan_denah_lantai(slot_parkir, lantai, slot_per_lantai);
    }
}

void isi_slot(int slot_parkir[], int index) {
    slot_parkir[index] = 1; // Tandai slot dengan "Ada"
}

void kosongkan_slot(int slot_parkir[], int index) {
    slot_parkir[index] = 0; // Tandai slot dengan "Kosong"
}

int main() {
    int slot_parkir[TOTAL_SLOT]; // Array untuk menyimpan status parkir
    
    // Inisialisasi semua slot sebagai kosong
    for (int i = 0; i < TOTAL_SLOT; i++) {
        slot_parkir[i] = 0;
    }
    
    int pilihan, lantai, slot;
    do {
        printf("\n--- SISTEM PARKIR MULTI-LANTAI ---\n");
        printf("1. Parkir Kendaraan di Slot Pilihan\n");
        printf("2. Kendaraan Keluar\n");
        printf("3. Tampilkan Status Parkir\n");
        printf("4. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);
        
        switch (pilihan) {
            case 1:
                printf("Masukkan lantai (1-%d): ", LANTAI);
                scanf("%d", &lantai);
                
                if (lantai > 0 && lantai <= LANTAI) {
                    tampilkan_denah_lantai(slot_parkir, lantai - 1, SLOT_PER_LANTAI);
                    printf("Masukkan nomor slot (1-%d): ", SLOT_PER_LANTAI);
                    scanf("%d", &slot);
                    
                    if (slot > 0 && slot <= SLOT_PER_LANTAI) {
                        int index = (lantai - 1) * SLOT_PER_LANTAI + (slot - 1);
                        
                        if (slot_parkir[index] == 0) {
                            isi_slot(slot_parkir, index);
                            printf("Kendaraan berhasil parkir di Lantai %d, Slot %d\n", lantai, slot);
                        } else {
                            printf("Slot %d di Lantai %d sudah terisi! Silakan pilih slot lain.\n", slot, lantai);
                        }
                    } else {
                        printf("Nomor slot tidak valid!\n");
                    }
                } else {
                    printf("Nomor lantai tidak valid!\n");
                }
                break;
            
            case 2:
                printf("Masukkan lantai (1-%d): ", LANTAI);
                scanf("%d", &lantai);
                
                if (lantai > 0 && lantai <= LANTAI) {
                    tampilkan_denah_lantai(slot_parkir, lantai - 1, SLOT_PER_LANTAI);
                    printf("Masukkan nomor slot (1-%d): ", SLOT_PER_LANTAI);
                    scanf("%d", &slot);
                    
                    if (slot > 0 && slot <= SLOT_PER_LANTAI) {
                        int index = (lantai - 1) * SLOT_PER_LANTAI + (slot - 1);
                        
                        if (slot_parkir[index] == 1) {
                            kosongkan_slot(slot_parkir, index);
                            printf("Slot %d di Lantai %d telah dikosongkan.\n", slot, lantai);
                        } else {
                            printf("Slot %d di Lantai %d sudah kosong!\n", slot, lantai);
                        }
                    } else {
                        printf("Nomor slot tidak valid!\n");
                    }
                } else {
                    printf("Nomor lantai tidak valid!\n");
                }
                break;
            
            case 3:
                tampilkan_status(slot_parkir, TOTAL_SLOT, SLOT_PER_LANTAI);
                break;
            
            case 4:
                printf("Keluar program.\n");
                break;
            
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 4);
    
    return 0;
}

