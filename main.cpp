#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Tugas {
    string nama;
    string matkul;
    string deadline;
    bool selesai;
};

struct User {
    string nama;
    string nim;
};

const int MAX = 100;
Tugas daftarTugas[MAX];
int jumlahTugas = 0;

User daftarUser[] = {
    {"raka", "001"},
    {"budi", "002"},
    {"siti", "003"}
};
int jumlahUser = 3;

int hitungAktif(int n) {
    if (n == 0) return 0;
    if (!daftarTugas[n - 1].selesai)
        return 1 + hitungAktif(n - 1);
    return hitungAktif(n - 1);
}

bool login(string nama, string nim) {
    for (int i = 0; i < jumlahUser; i++) {
        if (daftarUser[i].nama == nama && daftarUser[i].nim == nim)
            return true;
    }
    return false;
}

void tampilMenu() {
    cout << "\n========= MENU TASKKU =========\n";
    cout << "1. Tambah Tugas\n";
    cout << "2. Lihat Tugas Aktif\n";
    cout << "3. Hapus Tugas\n";
    cout << "4. Tandai Tugas Selesai\n";
    cout << "5. Lihat Riwayat Selesai\n";
    cout << "6. Simpan ke File\n";
    cout << "0. Keluar\n";
    cout << "================================\n";
    cout << "Tugas aktif: " << hitungAktif(jumlahTugas) << "\n";
    cout << "Pilihan: ";
}

void tambahTugas() {
    if (jumlahTugas >= MAX) {
        cout << "Daftar tugas penuh!\n";
        return;
    }
    cout << "\n--- Tambah Tugas Baru ---\n";
    cout << "Nama tugas  : ";
    cin.ignore();
    getline(cin, daftarTugas[jumlahTugas].nama);
    cout << "Mata kuliah : ";
    getline(cin, daftarTugas[jumlahTugas].matkul);
    cout << "Deadline    : ";
    getline(cin, daftarTugas[jumlahTugas].deadline);
    daftarTugas[jumlahTugas].selesai = false;
    jumlahTugas++;
    cout << "Tugas berhasil ditambahkan!\n";
}

void lihatTugas() {
    cout << "\n--- Daftar Tugas Aktif ---\n";
    bool ada = false;
    int no = 1;
    for (int i = 0; i < jumlahTugas; i++) {
        if (!daftarTugas[i].selesai) {
            cout << no << ". " << daftarTugas[i].nama
                 << " | " << daftarTugas[i].matkul
                 << " | Deadline: " << daftarTugas[i].deadline << "\n";
            no++;
            ada = true;
        }
    }
    if (!ada) cout << "Tidak ada tugas aktif.\n";
}

void hapusTugas() {
    lihatTugas();
    if (hitungAktif(jumlahTugas) == 0) return;
    cout << "Nomor tugas yang dihapus: ";
    int nomor;
    cin >> nomor;

    int hitungan = 0, idx = -1;
    for (int i = 0; i < jumlahTugas; i++) {
        if (!daftarTugas[i].selesai) {
            hitungan++;
            if (hitungan == nomor) { idx = i; break; }
        }
    }

    if (idx == -1) {
        cout << "Nomor tidak valid.\n";
        return;
    }

    for (int i = idx; i < jumlahTugas - 1; i++) {
        daftarTugas[i] = daftarTugas[i + 1];
    }
    jumlahTugas--;
    cout << "Tugas berhasil dihapus!\n";
}

void tandaiSelesai() {
    lihatTugas();
    if (hitungAktif(jumlahTugas) == 0) return;
    cout << "Nomor tugas yang selesai: ";
    int nomor;
    cin >> nomor;

    int hitungan = 0;
    for (int i = 0; i < jumlahTugas; i++) {
        if (!daftarTugas[i].selesai) {
            hitungan++;
            if (hitungan == nomor) {
                daftarTugas[i].selesai = true;
                cout << "Tugas '" << daftarTugas[i].nama << "' ditandai selesai!\n";
                return;
            }
        }
    }
    cout << "Nomor tidak valid.\n";
}

void lihatRiwayat() {
    cout << "\n--- Riwayat Tugas Selesai ---\n";
    bool ada = false;
    int no = 1;
    for (int i = 0; i < jumlahTugas; i++) {
        if (daftarTugas[i].selesai) {
            cout << no << ". " << daftarTugas[i].nama
                 << " | " << daftarTugas[i].matkul
                 << " | " << daftarTugas[i].deadline
                 << " [SELESAI]\n";
            no++;
            ada = true;
        }
    }
    if (!ada) cout << "Belum ada tugas yang diselesaikan.\n";
}

void simpanKeFile() {
    ofstream file("arsip_tugas.txt");
    if (!file) {
        cout << "Gagal membuka file!\n";
        return;
    }
    file << "===== ARSIP TUGAS TASKKU =====\n\n";
    for (int i = 0; i < jumlahTugas; i++) {
        file << "Tugas    : " << daftarTugas[i].nama << "\n";
        file << "Matkul   : " << daftarTugas[i].matkul << "\n";
        file << "Deadline : " << daftarTugas[i].deadline << "\n";
        file << "Status   : " << (daftarTugas[i].selesai ? "SELESAI" : "AKTIF") << "\n";
        file << "---\n";
    }
    file.close();
    cout << "Tersimpan di arsip_tugas.txt\n";
}

int main() {
    cout << "==============================\n";
    cout << "     Selamat datang di TASKKU \n";
    cout << "==============================\n";

    string nama, nim;
    bool loginBerhasil = false;
    do {
        cout << "\nNama (username) : ";
        cin >> nama;
        cout << "NIM  (password) : ";
        cin >> nim;
        loginBerhasil = login(nama, nim);
        if (!loginBerhasil)
            cout << "Login gagal! Coba lagi.\n";
    } while (!loginBerhasil);

    cout << "\nHalo, " << nama << "! Login berhasil.\n";

    int pilihan = -1;
    while (pilihan != 0) {
        tampilMenu();
        cin >> pilihan;

        switch (pilihan) {
            case 1: tambahTugas();   break;
            case 2: lihatTugas();    break;
            case 3: hapusTugas();    break;
            case 4: tandaiSelesai(); break;
            case 5: lihatRiwayat();  break;
            case 6: simpanKeFile();  break;
            case 0:
                simpanKeFile();
                cout << "\nSampai jumpa, " << nama << "!\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    }

    return 0;
}
