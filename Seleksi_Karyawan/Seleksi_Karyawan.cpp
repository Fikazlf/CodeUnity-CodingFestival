#include <iostream>     // Library untuk input-output standar
#include <vector>       // Library untuk menggunakan struktur data vektor
#include <iomanip>      // Library untuk mengatur presisi output

using namespace std;    // Penggunaan namespace std untuk kemudahan penggunaan fungsi-fungsi standar

// Struktur untuk menyimpan data kandidat
struct Kandidat {
    string nama;
    int pendidikan;
    int prestasi;
    int keramahan;
    int kemampuan_berkomunikasi;
    int jarak_tempat_tinggal;
    int kecakapan;
    double bobot;
};

// Fungsi untuk menghitung bobot berdasarkan kriteria yang diberikan
double hitungBobot(const Kandidat& kandidat) {
    // Bobot dihitung dengan mengalikan nilai setiap kriteria dengan bobotnya masing-masing
    double bobot = (kandidat.pendidikan * 0.3) + (kandidat.prestasi * 0.1) +
                   (kandidat.keramahan * 0.2) + (kandidat.kemampuan_berkomunikasi * 0.15) +
                   (kandidat.jarak_tempat_tinggal * 0.05) + (kandidat.kecakapan * 0.2);
    return bobot;
}

int main() {
    int n;
    cout << "Masukkan jumlah kandidat: ";
    cin >> n;

    // Membuat vektor untuk menyimpan informasi setiap kandidat
    vector<Kandidat> kandidatList(n);

    // Meminta input informasi untuk setiap kandidat dari pengguna
    for (int i = 0; i < n; ++i) {
        cout << "Kandidat " << i + 1 << ":" << endl;
        cout << "Nama: ";
        cin >> kandidatList[i].nama;
        cout << "Pendidikan (1-5): ";
        cin >> kandidatList[i].pendidikan;
        cout << "Prestasi (1-5): ";
        cin >> kandidatList[i].prestasi;
        cout << "Keramahan (1-10): ";
        cin >> kandidatList[i].keramahan;
        cout << "Kemampuan berkomunikasi (1-10): ";
        cin >> kandidatList[i].kemampuan_berkomunikasi;
        cout << "Jarak tempat tinggal (1-10): ";
        cin >> kandidatList[i].jarak_tempat_tinggal;
        cout << "Kecakapan (1-10): ";
        cin >> kandidatList[i].kecakapan;
        kandidatList[i].bobot = hitungBobot(kandidatList[i]); // Menghitung bobot untuk setiap kandidat
    }

    // Cari kandidat dengan bobot terbesar
    double maxBobot = -1;
    int idxMaxBobot = -1;
    for (int i = 0; i < n; ++i) {
        if (kandidatList[i].bobot > maxBobot) {
            maxBobot = kandidatList[i].bobot;
            idxMaxBobot = i;
        }
    }

    // Tampilkan informasi setiap kandidat
    for (int i = 0; i < n; ++i) {
        cout << "------------------" << endl;
        cout << kandidatList[i].nama << endl;
        cout << "------------------" << endl;
        cout << "Pendidikan : " << kandidatList[i].pendidikan << endl;
        cout << "Prestasi : " << kandidatList[i].prestasi << endl;
        cout << "Keramahan : " << kandidatList[i].keramahan << endl;
        cout << "Kemampuan berkomunikasi : " << kandidatList[i].kemampuan_berkomunikasi << endl;
        cout << "Jarak tempat tinggal : " << kandidatList[i].jarak_tempat_tinggal << endl;
        cout << "Kecakapan : " << kandidatList[i].kecakapan << endl;
        cout << "Bobot : " << fixed << setprecision(1) << kandidatList[i].bobot << endl; // Menampilkan bobot dengan presisi 1 digit
    }

    // Tampilkan rekomendasi karyawan berdasarkan penilaian bobot
    cout << "------------------" << endl;
    cout << "Berdasarkan penilaian bobot, karyawan yang cocok adalah kandidat no " << idxMaxBobot + 1 << endl;

    return 0;
}
