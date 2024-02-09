#include <iostream>     // Untuk input-output standar
#include <fstream>      // Untuk operasi file input-output
#include <sstream>      // Untuk operasi string stream
#include <vector>       // Untuk menggunakan vektor sebagai struktur data
#include <map>          // Untuk menggunakan map dalam menghitung frekuensi nilai
#include <algorithm>    // Untuk fungsi-fungsi umum seperti sort()
#include <cmath>        // Untuk operasi matematika seperti sqrt() dan pow()
#include <iomanip>      // Untuk mengatur presisi output, misalnya setprecision()

using namespace std;    // Penggunaan namespace std untuk kemudahan penggunaan fungsi-fungsi standar

// Struktur untuk menyimpan data mahasiswa
struct Mahasiswa {
    string nama;
    vector<int> nilai;
};

// Fungsi untuk menghitung rata-rata nilai
double hitungRata(const vector<int>& nilai) {
    double total = 0;
    for (int n : nilai) {
        total += n;
    }
    return total / nilai.size();
}

// Fungsi untuk menghitung median nilai
int hitungMedian(const vector<int>& nilai) {
    vector<int> temp(nilai); // Membuat salinan vektor untuk diurutkan
    sort(temp.begin(), temp.end()); // Mengurutkan nilai-nilai
    int size = temp.size();
    if (size % 2 == 0) { // Jika jumlah elemen genap
        return (temp[size / 2 - 1] + temp[size / 2]) / 2; // Ambil rata-rata dua nilai tengah
    } else {
        return temp[size / 2]; // Ambil nilai tengah
    }
}

// Fungsi untuk menghitung standar deviasi
double hitungStandarDeviasi(const vector<int>& nilai) {
    double rata = hitungRata(nilai); // Hitung rata-rata
    double total = 0;
    for (int n : nilai) {
        total += pow(n - rata, 2); // Jumlahkan kuadrat selisih antara nilai dan rata-rata
    }
    return sqrt(total / nilai.size()); // Akar dari rata-rata kuadrat selisih
}

// Fungsi untuk menghitung modus
vector<int> hitungModus(const vector<int>& nilai) {
    map<int, int> frekuensi; // Map untuk menyimpan frekuensi kemunculan setiap nilai
    for (int n : nilai) {
        frekuensi[n]++; // Tambahkan frekuensi kemunculan nilai
    }
    int maxFrekuensi = 0;
    for (auto& pair : frekuensi) {
        maxFrekuensi = max(maxFrekuensi, pair.second); // Cari frekuensi kemunculan maksimum
    }
    vector<int> modus;
    for (auto& pair : frekuensi) {
        if (pair.second == maxFrekuensi) { // Jika frekuensi sama dengan frekuensi maksimum
            modus.push_back(pair.first); // Tambahkan nilai ke modus
        }
    }
    return modus;
}

// Fungsi untuk membaca data dari file
vector<Mahasiswa> bacaData(const string& filename) {
    vector<Mahasiswa> data;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File tidak dapat dibuka." << endl; // Pesan kesalahan jika gagal membuka file
        return data;
    }
    string line;
    while (getline(file, line)) {
        Mahasiswa mhs;
        istringstream iss(line);
        iss >> mhs.nama;
        int nilai;
        while (iss >> nilai) {
            mhs.nilai.push_back(nilai); // Membaca nilai dari setiap baris dan menyimpannya
        }
        data.push_back(mhs); // Menambahkan mahasiswa ke vektor data
    }
    file.close();
    return data;
}

// Fungsi untuk menulis hasil statistik ke file
void tulisHasil(const string& filename, const string& hasil) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "File tidak dapat dibuat." << endl; // Pesan kesalahan jika gagal membuat file
        return;
    }
    file << hasil; // Menulis hasil statistik ke file
    file.close();
    cout << "File txt berhasil dibuat dengan hasil statistik." << endl; // Pesan sukses
}

// Fungsi utama
int main() {
    vector<Mahasiswa> data = bacaData("datamhs.txt"); // Membaca data mahasiswa dari file
    if (data.empty()) {
        return 1; // Keluar dari program jika gagal membaca data
    }

    int pilihan;
    cout << "Pilih program (1-7) :\n\n";
    cout << "1. Rata-rata nilai\n";
    cout << "2. Median\n";
    cout << "3. Standar deviasi\n";
    cout << "4. Modus\n";
    cout << "5. Nilai tertinggi dan nama peserta yang memperoleh nilai tertinggi\n";
    cout << "6. Nilai terendah dan nama peserta yang memperoleh nilai terendah\n";
    cout << "7. Pembuatan file txt yang berisi semua hasil statistik.\n\n";
    cout << "Pilihan: ";
    cin >> pilihan;

    string hasil;

    switch (pilihan) { // Memilih opsi sesuai input pengguna
        case 1: // Hitung rata-rata per orang
            for (const Mahasiswa& mhs : data) {
                hasil += mhs.nama + ": " + to_string(hitungRata(mhs.nilai)) + "\n"; // Menambahkan hasil ke string
            }
            break;
        case 2: // Hitung median per mata kuliah
            for (size_t i = 0; i < data[0].nilai.size(); ++i) {
                vector<int> mataKuliah;
                for (const Mahasiswa& mhs : data) {
                    mataKuliah.push_back(mhs.nilai[i]); // Mengumpulkan nilai untuk setiap mata kuliah
                }
                hasil += "Mata Kuliah " + to_string(i + 1) + ": " + to_string(hitungMedian(mataKuliah)) + "\n"; // Menambahkan hasil ke string
            }
            break;
        case 3: // Hitung standar deviasi semua nilai
            {
                vector<int> semuaNilai;
                for (const Mahasiswa& mhs : data) {
                    semuaNilai.insert(semuaNilai.end(), mhs.nilai.begin(), mhs.nilai.end()); // Menggabungkan semua nilai ke satu vektor
                }
                hasil += "Standar Deviasi Semua Nilai ≈ " + to_string(hitungStandarDeviasi(semuaNilai)) + "\n"; // Menambahkan hasil ke string
            }
            break;
        case 4: // Hitung modus per mata kuliah
            for (size_t i = 0; i < data[0].nilai.size(); ++i) {
                vector<int> mataKuliah;
                for (const Mahasiswa& mhs : data) {
                    mataKuliah.push_back(mhs.nilai[i]); // Mengumpulkan nilai untuk setiap mata kuliah
                }
                vector<int> modus = hitungModus(mataKuliah); // Menghitung modus
                hasil += "Mata Kuliah " + to_string(i + 1) + ": ";
                for (int nilai : modus) {
                    hasil += to_string(nilai) + " "; // Menambahkan hasil ke string
                }
                hasil += "\n";
            }
            break;
        case 5: // Nilai tertinggi per mata kuliah
            for (size_t i = 0; i < data[0].nilai.size(); ++i) {
                int maxNilai = -1;
                string namaMaxNilai;
                for (const Mahasiswa& mhs : data) {
                    if (mhs.nilai[i] > maxNilai) {
                        maxNilai = mhs.nilai[i];
                        namaMaxNilai = mhs.nama;
                    } else if (mhs.nilai[i] == maxNilai) {
                        namaMaxNilai += " " + mhs.nama;
                    }
                }
                hasil += "Mata Kuliah " + to_string(i + 1) + ": " + to_string(maxNilai) + " " + namaMaxNilai + "\n"; // Menambahkan hasil ke string
            }
            break;
        case 6: // Nilai terendah per mata kuliah
            for (size_t i = 0; i < data[0].nilai.size(); ++i) {
                int minNilai = 101;
                string namaMinNilai;
                for (const Mahasiswa& mhs : data) {
                    if (mhs.nilai[i] < minNilai) {
                        minNilai = mhs.nilai[i];
                        namaMinNilai = mhs.nama;
                    } else if (mhs.nilai[i] == minNilai) {
                        namaMinNilai += " " + mhs.nama;
                    }
                }
                hasil += "Mata Kuliah " + to_string(i + 1) + ": " + to_string(minNilai) + " " + namaMinNilai + "\n"; // Menambahkan hasil ke string
            }
            break;
        case 7: // Buat file txt
            hasil += "Rata-rata Nilai:\n";
            for (const Mahasiswa& mhs : data) {
                hasil += mhs.nama + ": " + to_string(hitungRata(mhs.nilai)) + "\n"; // Menambahkan rata-rata nilai ke string
            }
            hasil += "\nMedian Nilai Per Mata Kuliah:\n";
            for (size_t i = 0; i < data[0].nilai.size(); ++i) {
                vector<int> mataKuliah;
                for (const Mahasiswa& mhs : data) {
                    mataKuliah.push_back(mhs.nilai[i]); // Mengumpulkan nilai untuk setiap mata kuliah
                }
                hasil += "Mata Kuliah " + to_string(i + 1) + ": " + to_string(hitungMedian(mataKuliah)) + "\n"; // Menambahkan median ke string
            }
            hasil += "\nStandar Deviasi Semua Nilai ≈ " + to_string(hitungStandarDeviasi(data[0].nilai)) + "\n"; // Menambahkan standar deviasi ke string
            hasil += "\nModus Mata Kuliah:\n";
            for (size_t i = 0; i < data[0].nilai.size(); ++i) {
                vector<int> mataKuliah;
                for (const Mahasiswa& mhs : data) {
                    mataKuliah.push_back(mhs.nilai[i]); // Mengumpulkan nilai untuk setiap mata kuliah
                }
                vector<int> modus = hitungModus(mataKuliah); // Menghitung modus
                hasil += "Mata Kuliah " + to_string(i + 1) + ": ";
                for (int nilai : modus) {
                    hasil += to_string(nilai) + " "; // Menambahkan modus ke string
                }
                hasil += "\n";
            }
            hasil += "\nNilai Tertinggi Mata Kuliah:\n";
            for (size_t i = 0; i < data[0].nilai.size(); ++i) {
                int maxNilai = -1;
                string namaMaxNilai;
                for (const Mahasiswa& mhs : data) {
                    if (mhs.nilai[i] > maxNilai) {
                        maxNilai = mhs.nilai[i];
                        namaMaxNilai = mhs.nama;
                    } else if (mhs.nilai[i] == maxNilai) {
                        namaMaxNilai += " " + mhs.nama;
                    }
                }
                hasil += "Mata Kuliah " + to_string(i + 1) + ": " + to_string(maxNilai) + " " + namaMaxNilai + "\n"; // Menambahkan nilai tertinggi ke string
            }
            hasil += "\nNilai Terendah Mata Kuliah:\n";
            for (size_t i = 0; i < data[0].nilai.size(); ++i) {
                int minNilai = 101;
                string namaMinNilai;
                for (const Mahasiswa& mhs : data) {
                    if (mhs.nilai[i] < minNilai) {
                        minNilai = mhs.nilai[i];
                        namaMinNilai = mhs.nama;
                    } else if (mhs.nilai[i] == minNilai) {
                        namaMinNilai += " " + mhs.nama;
                    }
                }
                hasil += "Mata Kuliah " + to_string(i + 1) + ": " + to_string(minNilai) + " " + namaMinNilai + "\n"; // Menambahkan nilai terendah ke string
            }
            tulisHasil("statistik_nilai.txt", hasil); // Menulis hasil ke file
            break;
        default:
            cout << "Pilihan tidak valid." << endl; // Pesan kesalahan jika pilihan tidak valid
            break;
    }

    cout << hasil; // Menampilkan hasil

    return 0;
}
