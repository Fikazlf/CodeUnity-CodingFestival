#include <iostream> // Library untuk input-output standar
#include <fstream> // Library untuk manipulasi file
#include <vector> // Library untuk menggunakan struktur data vector
#include <algorithm> // Library untuk algoritma umum
#include <iomanip> // Library untuk manipulasi output dengan presisi dan lebar tertentu
#include <sstream> // Library untuk operasi string stream

using namespace std; // Menggunakan namespace standard untuk mempermudah penggunaan fungsi standar

// Struktur untuk menyimpan informasi barang
struct Barang {
    string nama;
    double HargaBeli;
    int JumlahBeli;
    double HargaJual;
    int JumlahTerjual;
};

// Fungsi untuk membaca data dari file
vector<Barang> bacaData(const string& file_name) {
    vector<Barang> daftar_barang;
    ifstream file(file_name);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string nama;
            double HargaBeli, HargaJual;
            int JumlahBeli, JumlahTerjual;
            char separator;
            if (getline(ss, nama, '|') >> HargaBeli >> separator >> JumlahBeli >> separator >> HargaJual >> separator >> JumlahTerjual) {
                daftar_barang.push_back({nama, HargaBeli, JumlahBeli, HargaJual, JumlahTerjual});
            }
        }
        file.close();
    } else {
        cout << "Gagal membuka file." << endl;
    }
    return daftar_barang;
}

// Fungsi untuk menampilkan data barang
void tampilkanData(const vector<Barang>& daftar_barang) {
    cout << "\n===================================================================================================================" << endl;
    cout << "No\t| " << setw(20) << left << "Nama" << "| " << setw(15) << left << "Harga Beli" << "| "
         << setw(15) << left << "Jumlah Beli" << "| " << setw(15) << left << "Harga Jual" << "| "
         << setw(15) << left << "Jumlah Terjual" << endl;
    cout << "===================================================================================================================" << endl;
    int nomor = 1;
    for (const auto& barang : daftar_barang) {
        cout << nomor << '\t' << "| " << setw(20) << left << barang.nama << "| " 
             << setw(15) << left << barang.HargaBeli << "| " 
             << setw(15) << left << barang.JumlahBeli << "| " 
             << setw(15) << left << barang.HargaJual << "| " 
             << setw(15) << left << barang.JumlahTerjual << endl;
        nomor++;
    }
    cout << endl;
}

// Fungsi untuk mengurutkan data berdasarkan jumlah barang terjual secara ascending
void urutkanData(vector<Barang>& daftar_barang) {
    sort(daftar_barang.begin(), daftar_barang.end(), [](const Barang& a, const Barang& b) {
        return a.JumlahTerjual < b.JumlahTerjual;
    });
}

// Fungsi untuk mencari barang berdasarkan nama
void cariBarang(const vector<Barang>& daftar_barang, const string& nama) {
    cout << "\nHasil pencarian untuk '" << nama << "':" << endl << endl;
    bool ditemukan = false;
    for (const auto& barang : daftar_barang) {
        if (barang.nama == nama) {
            cout << "===================================================================================================================" << endl;
            cout << setw(20) << left << "Nama" << setw(15) << left << "Harga Beli" << setw(15) 
                    << left << "Jumlah Beli" << setw(15) << left << "Harga Jual" << setw(15) << left 
                    << "Jumlah Terjual" << endl;
            cout << "===================================================================================================================" << endl;
            cout << setw(20) << left << barang.nama << setw(15) << left << barang.HargaBeli << setw(15) 
                    << left << barang.JumlahBeli << setw(15) << left << barang.HargaJual << setw(15) << left 
                    << barang.JumlahTerjual << endl;
            cout << "===================================================================================================================" << endl;
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan) {
        cout << "Barang tidak ditemukan." << endl;
    }
    cout << endl;
}

// Fungsi untuk menghitung dan menampilkan keuntungan per barang
void hitungKeuntungan(const vector<Barang>& daftar_barang) {
    cout << "\n===================================================================================================" << endl;
    cout << "Keuntungan per barang : " << endl;
    cout << "===================================================================================================" << endl;
    int nomor = 1;
    for (const auto& barang : daftar_barang) {
        double keuntungan = (barang.HargaJual * barang.JumlahTerjual) - (barang.HargaBeli * barang.JumlahBeli);
        cout << nomor << '\t' << setw(20) << left << barang.nama << setw(15) << left << "Keuntungan : " << keuntungan << endl;
        nomor++;
    }
    cout << endl;
}

// Fungsi untuk menyimpan hasil keuntungan ke dalam file output
void simpanKeuntungan(const vector<Barang>& daftar_barang) {
    ofstream file("laporan.txt");
    if (file.is_open()) {
        file << setw(20) << left << "Nama Barang" << setw(15) << left << "Harga Beli" << setw(15) << left << "Jumlah Beli" << setw(15) 
        << left << "Harga Jual" << setw(15) << left << "Jumlah Terjual" << setw(15) << left << "Keuntungan" << endl;
        file << "===================================================================================================================" << endl;
        
        double total_keuntungan = 0.0;
        for (const auto& barang : daftar_barang) {
            double keuntungan = (barang.HargaJual * barang.JumlahTerjual) - (barang.HargaBeli * barang.JumlahBeli);
            total_keuntungan += keuntungan;
            file << setw(20) << left << barang.nama << setw(15) << left << barang.HargaBeli << setw(15) << left 
                << barang.JumlahBeli << setw(15) << left << barang.HargaJual << setw(15) << left 
                << barang.JumlahTerjual << setw(15) << left << keuntungan << endl;
        }
        file << "===================================================================================================================" << endl;
        file << "Total Keuntungan Keseluruhan: " << fixed << setprecision(2) << total_keuntungan << endl;
        file.close();
        cout << "\nData keuntungan telah disimpan dalam file laporan.txt" << endl;
    } else {
        cout << "Gagal menyimpan file." << endl;
    }
}

int main() {
    vector<Barang> daftar_barang = bacaData("DaftarBarang.txt");
    int pilihan;
    string nama_barang;
    do {
        cout << "Menu:" << endl;
        cout << "1. Tampilkan Data Barang" << endl;
        cout << "2. Urutkan Data Berdasarkan Jumlah Terjual" << endl;
        cout << "3. Cari Barang" << endl;
        cout << "4. Hitung dan Tampilkan Keuntungan" << endl;
        cout << "5. Simpan Keuntungan ke File" << endl;
        cout << "6. Keluar" << endl;
        cout << "Pilihan Anda : ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilkanData(daftar_barang);
                break;
            case 2:
                urutkanData(daftar_barang);
                cout << "\nData berhasil diurutkan berdasarkan jumlah terjual." << endl << endl;
                tampilkanData(daftar_barang); // Menampilkan data setelah pengurutan
                break;
            case 3:
                cout << "\nMasukkan nama barang yang ingin dicari: ";
                cin.ignore();
                getline(cin, nama_barang);
                cariBarang(daftar_barang, nama_barang);
                break;
            case 4:
                hitungKeuntungan(daftar_barang);
                break;
            case 5:
                simpanKeuntungan(daftar_barang);
                break;
            case 6:
                cout << "Terima kasih!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    } while (pilihan != 6);

    return 0;
}
