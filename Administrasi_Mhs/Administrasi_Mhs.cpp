#include <iostream> // Library untuk input-output standar
#include <fstream> // Library untuk manipulasi file
#include <string> // Library untuk tipe data string
#include <algorithm> // Library untuk algoritma umum
#include <sstream> // Library untuk stringstream
#include <iomanip> // Library untuk manipulator setw

using namespace std; // Menggunakan namespace standard untuk mempermudah penggunaan fungsi standar

// Maksimum jumlah mahasiswa
const int MAX_MAHASISWA = 100;

// Struktur untuk menyimpan data mahasiswa
struct Mahasiswa {
    string nama;
    string nim;
    string telepon;
};

// Fungsi untuk menambahkan data mahasiswa ke dalam array
void tambahData(Mahasiswa data[], int& jumlahMahasiswa, const Mahasiswa& mahasiswa) {
    if (jumlahMahasiswa < MAX_MAHASISWA) { // Memastikan tidak melebihi kapasitas maksimum
        data[jumlahMahasiswa] = mahasiswa; // Menambahkan data ke dalam array
        jumlahMahasiswa++; // Menambahkan jumlah mahasiswa
    } else {
        cout << "Kapasitas data penuh." << endl; // Menampilkan pesan jika sudah penuh
    }
}

// Fungsi untuk menghapus data mahasiswa dari array berdasarkan nim
void hapusData(Mahasiswa data[], int& jumlahMahasiswa, const string& nim) {
    for (int i = 0; i < jumlahMahasiswa; ++i) {
        if (data[i].nim == nim) { // Mencari data yang sesuai dengan NIM yang diinginkan
            for (int j = i; j < jumlahMahasiswa - 1; ++j) {
                data[j] = data[j + 1]; // Menggeser data ke kiri untuk menutupi data yang dihapus
            }
            jumlahMahasiswa--; // Mengurangi jumlah mahasiswa setelah penghapusan
            return;
        }
    }
    cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan." << endl; // Menampilkan pesan jika data tidak ditemukan
}

// Fungsi untuk mengurutkan data mahasiswa berdasarkan nim secara ascending
void urutkanData(Mahasiswa data[], int jumlahMahasiswa) {
    sort(data, data + jumlahMahasiswa, [](const Mahasiswa& a, const Mahasiswa& b) { return a.nim < b.nim; }); // Menggunakan fungsi sort dari library <algorithm>
}

// Fungsi untuk menampilkan data mahasiswa
void tampilkanData(const Mahasiswa data[], int jumlahMahasiswa) {
    cout << "Index |Nama                  |NIM           |No Telepon     |" << endl;
    cout << "-------------------------------------------------------------" << endl;
    for (int i = 0; i < jumlahMahasiswa; ++i) { // Looping untuk menampilkan setiap data mahasiswa
        cout << setw(5) << i + 1 << " |" << setw(22) << data[i].nama << "|" << setw(14) << data[i].nim << "|" << setw(15) << data[i].telepon << "|" << endl; // Menggunakan manipulator setw untuk menyesuaikan lebar kolom
    }
}

int main() {
    ifstream inputFile("data_mhs.txt"); // Membuka file input
    Mahasiswa data[MAX_MAHASISWA]; // Mendefinisikan array untuk menyimpan data mahasiswa
    int jumlahMahasiswa = 0; // Variabel untuk menyimpan jumlah mahasiswa yang sudah ada

    // Membaca data dari file dan memasukkannya ke dalam array
    if (inputFile.is_open()) { // Memeriksa apakah file berhasil dibuka
        string line;
        while (getline(inputFile, line)) { // Looping untuk membaca setiap baris dalam file
            stringstream ss(line);
            string nama, nim, telepon;

            // Memisahkan data menggunakan delimiter |
            getline(ss, nama, '|');
            getline(ss, nim, '|');
            getline(ss, telepon, '|');

            // Menghapus whitespace yang mungkin terdapat di awal atau akhir string
            nama.erase(nama.find_last_not_of(" \n\r\t") + 1);
            nim.erase(nim.find_last_not_of(" \n\r\t") + 1);
            telepon.erase(telepon.find_last_not_of(" \n\r\t") + 1);

            // Menyimpan data ke dalam array
            Mahasiswa mahasiswa;
            mahasiswa.nama = nama;
            mahasiswa.nim = nim;
            mahasiswa.telepon = telepon;
            tambahData(data, jumlahMahasiswa, mahasiswa); // Memanggil fungsi untuk menambahkan data
        }
        inputFile.close(); // Menutup file setelah selesai membaca
    } else {
        cout << "Gagal membuka file data_mhs.txt" << endl; // Menampilkan pesan jika gagal membuka file
        return 1; // Menghentikan program dengan status error
    }

    // Menggunakan input dari pengguna untuk melakukan manipulasi data
    int pilihan;
    cout << "Masukkan pilihan (1: tambah data, 2: hapus data, 3: urutkan data): ";
    cin >> pilihan;
    
    // Membersihkan karakter newline yang tersisa
    cin.ignore();

    switch (pilihan) {
        case 1: {
            cout << "Menambahkan data" << endl;
            Mahasiswa mahasiswa;
            cout << "Nama: ";
            getline(cin, mahasiswa.nama);
            cout << "NIM: ";
            getline(cin, mahasiswa.nim);
            cout << "Nomor Telepon: ";
            getline(cin, mahasiswa.telepon);
            tambahData(data, jumlahMahasiswa, mahasiswa); // Memanggil fungsi untuk menambahkan data
            break;
        }
        case 2: {
            cout << "Menghapus data" << endl;
            string nim;
            cout << "Masukkan NIM mahasiswa yang ingin dihapus: ";
            cin >> nim;
            hapusData(data, jumlahMahasiswa, nim); // Memanggil fungsi untuk menghapus data
            break;
        }
        case 3: {
            cout << "Mengurutkan data" << endl;
            urutkanData(data, jumlahMahasiswa); // Memanggil fungsi untuk mengurutkan data
            break;
        }
        default:
            cout << "Pilihan tidak valid" << endl;
            return 1; // Menghentikan program dengan status error
    }

    // Menampilkan data yang telah dimanipulasi
    tampilkanData(data, jumlahMahasiswa); // Memanggil fungsi untuk menampilkan data

    // Menulis kembali data ke dalam file
    ofstream outputFile("data_mhs.txt"); // Membuka file output
    if (outputFile.is_open()) { // Memeriksa apakah file berhasil dibuka
        for (int i = 0; i < jumlahMahasiswa; ++i) { // Looping untuk menulis setiap data ke dalam file
            outputFile << data[i].nama << "|" << data[i].nim << "|" << data[i].telepon << "|" << endl;
        }
        outputFile.close(); // Menutup file setelah selesai menulis
    } else {
        cout << "Gagal membuka file data_mhs.txt" << endl; // Menampilkan pesan jika gagal membuka file
        return 1; // Menghentikan program dengan status error
    }

    return 0; // Mengakhiri program dengan status sukses
}
