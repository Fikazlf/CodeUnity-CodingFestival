#include <iostream>     // Library untuk input-output standar
#include <fstream>      // Library untuk operasi file input-output
#include <vector>       // Library untuk menggunakan struktur data vektor
#include <iomanip>      // Library untuk mengatur presisi output
#include <algorithm>    // Library untuk fungsi sort()

using namespace std;

// Struktur untuk menyimpan data karyawan
struct Karyawan {
    string nama;
    int kursus1;
    int kursus2;
    int kursus3;
    int total_penjualan;
    double komisi;
    double gaji_bersih;
};

// Fungsi untuk menghitung komisi
double hitungKomisi(int totalPenjualan) {
    double target = 500000;
    double komisi = 0;
    if (totalPenjualan >= target) {
        komisi = (target * 0.1) + ((totalPenjualan - target) * 0.15);
    }
    // Tidak ada komisi jika total penjualan kurang dari target
    return komisi;
}

// Fungsi untuk menghitung gaji bersih
double hitungGajiBersih(double komisi) {
    double gaji_pokok = 3000000;
    return gaji_pokok + komisi;
}

int main() {
    vector<Karyawan> karyawanList;

    // Membaca data karyawan dari file
    ifstream file("sales.txt");
    if (!file) {
        cout << "File tidak ditemukan." << endl;
        return 1;
    }

    string nama;
    int kursus1, kursus2, kursus3;
    while (file >> nama >> kursus1 >> kursus2 >> kursus3) {
        int totalPenjualan = (kursus1 * 100000) + (kursus2 * 150000) + (kursus3 * 200000);
        double komisi = hitungKomisi(totalPenjualan);
        double gajiBersih = hitungGajiBersih(komisi);
        karyawanList.push_back({nama, kursus1, kursus2, kursus3, totalPenjualan, komisi, gajiBersih});
    }
    file.close();

    // Pilihan menu
    int pilihan;
    cout << "Pilih menu:" << endl;
    cout << "1. Menghitung komisi" << endl;
    cout << "2. Menghitung gaji bersih" << endl;
    cout << "3. Mengurutkan data" << endl;
    cout << "4. Jumlah penjualan setiap kursus" << endl;
    cout << "5. Jumlah keseluruhan yang harus dibayar oleh perusahaan" << endl;
    cin >> pilihan;

    // Menangani pilihan menu
    switch (pilihan) {
        case 1:
            cout << setw(15) << "Nama" << setw(15) << "Course 1" << setw(15) << "Course 2" << setw(15) << "Course 3" << setw(15) << "Total Penjualan" << setw(15) << "Komisi" << endl;
            for (const auto& karyawan : karyawanList) {
                cout << setw(15) << karyawan.nama << setw(15) << karyawan.kursus1 << setw(15) << karyawan.kursus2 << setw(15) << karyawan.kursus3 << setw(15) << fixed << setprecision(0) << karyawan.total_penjualan << setw(15) << fixed << setprecision(0) << karyawan.komisi << endl;
            }
            break;
        case 2:
            cout << setw(15) << "Nama" << setw(15) << "Course 1" << setw(15) << "Course 2" << setw(15) << "Course 3" << setw(15) << "Komisi" << setw(15) << "Gaji bersih" << endl;
            for (const auto& karyawan : karyawanList) {
                cout << setw(15) << karyawan.nama << setw(15) << karyawan.kursus1 << setw(15) << karyawan.kursus2 << setw(15) << karyawan.kursus3 << setw(15) << fixed << setprecision(0) << karyawan.komisi << setw(15) << fixed << setprecision(0) << karyawan.gaji_bersih << endl;
            }
            break;
        case 3:
            sort(karyawanList.begin(), karyawanList.end(), [](const Karyawan& a, const Karyawan& b) {
                return a.total_penjualan > b.total_penjualan;
            });
            cout << setw(15) << "Nama" << setw(15) << "Course 1" << setw(15) << "Course 2" << setw(15) << "Course 3" << setw(15) << "Total Penjualan" << endl;
            for (const auto& karyawan : karyawanList) {
                cout << setw(15) << karyawan.nama << setw(15) << karyawan.kursus1 << setw(15) << karyawan.kursus2 << setw(15) << karyawan.kursus3 << setw(15) << fixed << setprecision(0) << karyawan.total_penjualan << endl;
            }
            break;
        case 4: {
            int totalKursus1 = 0, totalKursus2 = 0, totalKursus3 = 0;
            for (const auto& karyawan : karyawanList) {
                totalKursus1 += karyawan.kursus1;
                totalKursus2 += karyawan.kursus2;
                totalKursus3 += karyawan.kursus3;
            }
            cout << "Total Penjualan Perkursus" << endl;
            cout << "-----------------------------------" << endl;
            cout << "Kursus 1: " << totalKursus1 << endl;
            cout << "Kursus 2: " << totalKursus2 << endl;
            cout << "Kursus 3: " << totalKursus3 << endl;
            break;
        }
        case 5: {
            double totalPembayaran = 0;
            for (const auto& karyawan : karyawanList) {
                totalPembayaran += karyawan.gaji_bersih;
            }
            cout << fixed << "Total Keseluruhan yang Dibayar oleh Perusahaan: " << setprecision(0) << totalPembayaran << endl;
            break;
        }
        default:
            cout << "Pilihan tidak valid." << endl;
    }

    return 0;
}