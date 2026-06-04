#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <fstream>

using namespace std;

struct DataPeserta {
    int id;
    string namaPanjang;
    string namaPanggilan;
    string tglLahir;
    string jenisKelamin;
    string noHp;
    string email;
    string agency;
    float tinggiBadan;
    float beratBadan;
};

void tampilkanMenu();
void tambahPeserta(DataPeserta peserta[], int &jumlah);
void tampilkanSemuaPeserta(DataPeserta peserta[], int jumlah);
void cariPesertaByNama(DataPeserta peserta[], int jumlah);
void cariPesertaById(DataPeserta peserta[], int jumlah);
void hapusPeserta(DataPeserta peserta[], int &jumlah);
void updatePeserta(DataPeserta peserta[], int jumlah);
void hitungDanTampilkanBMI(float tinggi, float berat);
void tampilkanHeader();
void clearScreen();

void hitungStatistikRekursif(DataPeserta peserta[], int indeks, int jumlah, int &underweight, int &normal, int &overweight, int &obesitas);
float hitungTotalTinggiRekursif(DataPeserta peserta[], int indeks, int jumlah);
float hitungTotalBeratRekursif(DataPeserta peserta[], int indeks, int jumlah);
void tampilkanRataRataRekursif(DataPeserta peserta[], int jumlah);
void tampilkanStatistikBMI(DataPeserta peserta[], int jumlah);

void sortingMenu(DataPeserta peserta[], int jumlah);
void sortByIDAscending(DataPeserta peserta[], int jumlah);
void sortByIDDescending(DataPeserta peserta[], int jumlah);
void sortByNamaAscending(DataPeserta peserta[], int jumlah);
void sortByNamaDescending(DataPeserta peserta[], int jumlah);
void sortByTinggiAscending(DataPeserta peserta[], int jumlah);
void sortByTinggiDescending(DataPeserta peserta[], int jumlah);
void sortByBMIAscending(DataPeserta peserta[], int jumlah);
void sortByBMIDescending(DataPeserta peserta[], int jumlah);
void swapPeserta(DataPeserta &a, DataPeserta &b);

void simpanKeFile(DataPeserta peserta[], int jumlah);
void muatDariFile(DataPeserta peserta[], int &jumlah);

int main() {
    const int MAKS_PESERTA = 100;
    DataPeserta daftarPeserta[MAKS_PESERTA];
    int jumlahPeserta = 0;
    int pilihan;

    muatDariFile(daftarPeserta, jumlahPeserta);

    do {
        tampilkanMenu();
        cout << "Pilih menu (1-10): ";
        cin >> pilihan;
        cin.ignore();

        switch(pilihan) {
            case 1:
                tambahPeserta(daftarPeserta, jumlahPeserta);
                simpanKeFile(daftarPeserta, jumlahPeserta);
                break;
            case 2:
                tampilkanSemuaPeserta(daftarPeserta, jumlahPeserta);
                break;
            case 3:
                cariPesertaByNama(daftarPeserta, jumlahPeserta);
                break;
            case 4:
                cariPesertaById(daftarPeserta, jumlahPeserta);
                break;
            case 5:
                hapusPeserta(daftarPeserta, jumlahPeserta);
                simpanKeFile(daftarPeserta, jumlahPeserta);
                break;
            case 6:
                updatePeserta(daftarPeserta, jumlahPeserta);
                simpanKeFile(daftarPeserta, jumlahPeserta);
                break;
            case 7:
                sortingMenu(daftarPeserta, jumlahPeserta);
                break;
            case 8:
                tampilkanStatistikBMI(daftarPeserta, jumlahPeserta);
                break;
            case 9:
                tampilkanRataRataRekursif(daftarPeserta, jumlahPeserta);
                break;
            case 10:
                simpanKeFile(daftarPeserta, jumlahPeserta);
                cout << "\nTerima kasih! Program selesai.\n";
                break;
            default:
                cout << "\nPilihan tidak valid! Silakan coba lagi.\n";
        }

        if(pilihan != 10) {
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.get();
            clearScreen();
        }

    } while(pilihan != 10);

    return 0;
}

void tampilkanMenu() {
    cout << "\n==============================================\n";
    cout << "        SISTEM CASTING MODEL - PANITIA         \n";
    cout << "==============================================\n";
    cout << "1. Tambah Peserta Baru\n";
    cout << "2. Tampilkan Semua Peserta\n";
    cout << "3. Cari Peserta (berdasarkan Nama)\n";
    cout << "4. Cari Peserta (berdasarkan ID)\n";
    cout << "5. Hapus Peserta\n";
    cout << "6. Update Data Peserta\n";
    cout << "7. Sorting Data Peserta\n";
    cout << "8. Statistik BMI (Rekursif)\n";
    cout << "9. Rata-rata Tinggi/Berat (Rekursif)\n";
    cout << "10. Keluar & Simpan\n";
    cout << "==============================================\n";
}

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void tampilkanHeader() {
    cout << left;
    cout << setw(5) << "ID"
         << setw(20) << "Nama Panjang"
         << setw(15) << "Panggilan"
         << setw(12) << "Tgl Lahir"
         << setw(10) << "JK"
         << setw(15) << "No HP"
         << setw(25) << "Email"
         << setw(15) << "Agency"
         << setw(10) << "Tinggi"
         << setw(10) << "Berat"
         << setw(10) << "BMI" << endl;
    cout << string(140, '-') << endl;
}

void hitungDanTampilkanBMI(float tinggi, float berat) {
    float tinggiM = tinggi / 100.0;
    float bmi = berat / (tinggiM * tinggiM);

    string kategori;

    if(bmi < 18.5) {
        kategori = "Underweight";
    } else if(bmi < 25.0) {
        kategori = "Normal";
    } else if(bmi < 30.0) {
        kategori = "Overweight";
    } else {
        kategori = "Obesitas";
    }

    cout << fixed << setprecision(1) << bmi << " (" << kategori << ")";
}

float hitungBMIValue(float tinggi, float berat) {
    float tinggiM = tinggi / 100.0;
    return berat / (tinggiM * tinggiM);
}

void tambahPeserta(DataPeserta peserta[], int &jumlah) {
    if(jumlah >= 100) {
        cout << "\nMaaf, kuota peserta sudah penuh!\n";
        return;
    }

    cout << "\n--- FORM PENDAFTARAN CASTING MODEL ---\n";

    peserta[jumlah].id = jumlah + 1;

    cout << "Nama Panjang      : ";
    getline(cin, peserta[jumlah].namaPanjang);

    cout << "Nama Panggilan    : ";
    getline(cin, peserta[jumlah].namaPanggilan);

    cout << "Tanggal Lahir     : ";
    getline(cin, peserta[jumlah].tglLahir);

    cout << "Jenis Kelamin (L/P): ";
    getline(cin, peserta[jumlah].jenisKelamin);

    cout << "Nomor HP          : ";
    getline(cin, peserta[jumlah].noHp);

    cout << "Email             : ";
    getline(cin, peserta[jumlah].email);

    cout << "Agency (independen/agency): ";
    getline(cin, peserta[jumlah].agency);

    cout << "Tinggi Badan (cm) : ";
    cin >> peserta[jumlah].tinggiBadan;

    cout << "Berat Badan (kg)  : ";
    cin >> peserta[jumlah].beratBadan;

    jumlah++;
    cout << "\n Peserta berhasil ditambahkan! (ID: " << jumlah << ")\n";
}

void tampilkanSemuaPeserta(DataPeserta peserta[], int jumlah) {
    if(jumlah == 0) {
        cout << "\nBelum ada peserta yang terdaftar.\n";
        return;
    }

    cout << "\n--- DAFTAR SEMUA PESERTA CASTING ---\n";
    tampilkanHeader();

    for(int i = 0; i < jumlah; i++) {
        cout << left;
        cout << setw(5) << peserta[i].id
             << setw(20) << peserta[i].namaPanjang.substr(0, 18)
             << setw(15) << peserta[i].namaPanggilan
             << setw(12) << peserta[i].tglLahir
             << setw(10) << peserta[i].jenisKelamin
             << setw(15) << peserta[i].noHp
             << setw(25) << peserta[i].email.substr(0, 23)
             << setw(15) << peserta[i].agency
             << setw(10) << fixed << setprecision(1) << peserta[i].tinggiBadan
             << setw(10) << peserta[i].beratBadan;

        hitungDanTampilkanBMI(peserta[i].tinggiBadan, peserta[i].beratBadan);
        cout << endl;
    }
}

void cariPesertaByNama(DataPeserta peserta[], int jumlah) {
    if(jumlah == 0) {
        cout << "\nBelum ada peserta terdaftar.\n";
        return;
    }

    string cariNama;
    cout << "\nMasukkan nama yang dicari: ";
    getline(cin, cariNama);

    bool ditemukan = false;

    for(int i = 0; i < jumlah; i++) {
        string namaLower = peserta[i].namaPanjang;
        string cariLower = cariNama;

        for(char &c : namaLower) c = tolower(c);
        for(char &c : cariLower) c = tolower(c);

        if(namaLower.find(cariLower) != string::npos) {
            if(!ditemukan) {
                cout << "\n--- HASIL PENCARIAN ---\n";
                tampilkanHeader();
                ditemukan = true;
            }

            cout << left;
            cout << setw(5) << peserta[i].id
                 << setw(20) << peserta[i].namaPanjang
                 << setw(15) << peserta[i].namaPanggilan
                 << setw(12) << peserta[i].tglLahir
                 << setw(10) << peserta[i].jenisKelamin
                 << setw(15) << peserta[i].noHp
                 << setw(25) << peserta[i].email
                 << setw(15) << peserta[i].agency
                 << setw(10) << peserta[i].tinggiBadan
                 << setw(10) << peserta[i].beratBadan;

            hitungDanTampilkanBMI(peserta[i].tinggiBadan, peserta[i].beratBadan);
            cout << endl;
        }
    }

    if(!ditemukan) {
        cout << "\nPeserta dengan nama \"" << cariNama << "\" tidak ditemukan.\n";
    }
}

void cariPesertaById(DataPeserta peserta[], int jumlah) {
    if(jumlah == 0) {
        cout << "\nBelum ada peserta terdaftar.\n";
        return;
    }

    int cariId;
    cout << "\nMasukkan ID peserta yang dicari: ";
    cin >> cariId;
    cin.ignore();

    int kiri = 0, kanan = jumlah - 1;
    int tengah;
    bool ditemukan = false;

    while(kiri <= kanan && !ditemukan) {
        tengah = (kiri + kanan) / 2;

        if(peserta[tengah].id == cariId) {
            ditemukan = true;
        } else if(cariId < peserta[tengah].id) {
            kanan = tengah - 1;
        } else {
            kiri = tengah + 1;
        }
    }

    if(ditemukan) {
        cout << "\n--- DATA PESERTA DITEMUKAN ---\n";
        cout << "ID              : " << peserta[tengah].id << endl;
        cout << "Nama Panjang    : " << peserta[tengah].namaPanjang << endl;
        cout << "Nama Panggilan  : " << peserta[tengah].namaPanggilan << endl;
        cout << "Tanggal Lahir   : " << peserta[tengah].tglLahir << endl;
        cout << "Jenis Kelamin   : " << peserta[tengah].jenisKelamin << endl;
        cout << "Nomor HP        : " << peserta[tengah].noHp << endl;
        cout << "Email           : " << peserta[tengah].email << endl;
        cout << "Agency          : " << peserta[tengah].agency << endl;
        cout << "Tinggi Badan    : " << peserta[tengah].tinggiBadan << " cm" << endl;
        cout << "Berat Badan     : " << peserta[tengah].beratBadan << " kg" << endl;
        cout << "BMI             : ";
        hitungDanTampilkanBMI(peserta[tengah].tinggiBadan, peserta[tengah].beratBadan);
        cout << endl;
    } else {
        cout << "\nPeserta dengan ID " << cariId << " tidak ditemukan.\n";
    }
}

void hapusPeserta(DataPeserta peserta[], int &jumlah) {
    if(jumlah == 0) {
        cout << "\nBelum ada peserta terdaftar.\n";
        return;
    }

    int hapusId;
    cout << "\nMasukkan ID peserta yang akan dihapus: ";
    cin >> hapusId;
    cin.ignore();

    int indeksHapus = -1;
    for(int i = 0; i < jumlah; i++) {
        if(peserta[i].id == hapusId) {
            indeksHapus = i;
            break;
        }
    }

    if(indeksHapus == -1) {
        cout << "\nPeserta dengan ID " << hapusId << " tidak ditemukan.\n";
        return;
    }

    for(int i = indeksHapus; i < jumlah - 1; i++) {
        peserta[i] = peserta[i + 1];
        peserta[i].id = i + 1;
    }

    jumlah--;
    cout << "\n Peserta dengan ID " << hapusId << " berhasil dihapus.\n";
}

void updatePeserta(DataPeserta peserta[], int jumlah) {
    if(jumlah == 0) {
        cout << "\nBelum ada peserta terdaftar.\n";
        return;
    }

    int updateId;
    cout << "\nMasukkan ID peserta yang akan diupdate: ";
    cin >> updateId;
    cin.ignore();

    int indeksUpdate = -1;
    for(int i = 0; i < jumlah; i++) {
        if(peserta[i].id == updateId) {
            indeksUpdate = i;
            break;
        }
    }

    if(indeksUpdate == -1) {
        cout << "\nPeserta dengan ID " << updateId << " tidak ditemukan.\n";
        return;
    }

    cout << "\n--- UPDATE DATA PESERTA (kosongkan Enter jika tidak ingin mengubah) ---\n";

    string input;

    cout << "Nama Panjang [" << peserta[indeksUpdate].namaPanjang << "]: ";
    getline(cin, input);
    if(!input.empty()) peserta[indeksUpdate].namaPanjang = input;

    cout << "Nama Panggilan [" << peserta[indeksUpdate].namaPanggilan << "]: ";
    getline(cin, input);
    if(!input.empty()) peserta[indeksUpdate].namaPanggilan = input;

    cout << "Tanggal Lahir [" << peserta[indeksUpdate].tglLahir << "]: ";
    getline(cin, input);
    if(!input.empty()) peserta[indeksUpdate].tglLahir = input;

    cout << "Jenis Kelamin [" << peserta[indeksUpdate].jenisKelamin << "]: ";
    getline(cin, input);
    if(!input.empty()) peserta[indeksUpdate].jenisKelamin = input;

    cout << "Nomor HP [" << peserta[indeksUpdate].noHp << "]: ";
    getline(cin, input);
    if(!input.empty()) peserta[indeksUpdate].noHp = input;

    cout << "Email [" << peserta[indeksUpdate].email << "]: ";
    getline(cin, input);
    if(!input.empty()) peserta[indeksUpdate].email = input;

    cout << "Agency [" << peserta[indeksUpdate].agency << "]: ";
    getline(cin, input);
    if(!input.empty()) peserta[indeksUpdate].agency = input;

    cout << "Tinggi Badan [" << peserta[indeksUpdate].tinggiBadan << "]: ";
    getline(cin, input);
    if(!input.empty()) peserta[indeksUpdate].tinggiBadan = stof(input);

    cout << "Berat Badan [" << peserta[indeksUpdate].beratBadan << "]: ";
    getline(cin, input);
    if(!input.empty()) peserta[indeksUpdate].beratBadan = stof(input);

    cout << "\n Data peserta berhasil diupdate!\n";
}

void hitungStatistikRekursif(DataPeserta peserta[], int indeks, int jumlah,
                              int &underweight, int &normal, int &overweight, int &obesitas) {
    if(indeks >= jumlah) return;

    float bmi = hitungBMIValue(peserta[indeks].tinggiBadan, peserta[indeks].beratBadan);

    if(bmi < 18.5) underweight++;
    else if(bmi < 25.0) normal++;
    else if(bmi < 30.0) overweight++;
    else obesitas++;

    hitungStatistikRekursif(peserta, indeks + 1, jumlah, underweight, normal, overweight, obesitas);
}

void tampilkanStatistikBMI(DataPeserta peserta[], int jumlah) {
    if(jumlah == 0) {
        cout << "\nBelum ada data peserta.\n";
        return;
    }

    int underweight = 0, normal = 0, overweight = 0, obesitas = 0;
    hitungStatistikRekursif(peserta, 0, jumlah, underweight, normal, overweight, obesitas);

    cout << "\n--- STATISTIK BMI PESERTA (REKURSIF) ---\n";
    cout << "Underweight (BMI < 18.5) : " << underweight << " peserta\n";
    cout << "Normal (BMI 18.5-24.9)   : " << normal << " peserta\n";
    cout << "Overweight (BMI 25-29.9) : " << overweight << " peserta\n";
    cout << "Obesitas (BMI >= 30)     : " << obesitas << " peserta\n";
    cout << "Total                    : " << jumlah << " peserta\n";
}

float hitungTotalTinggiRekursif(DataPeserta peserta[], int indeks, int jumlah) {
    if(indeks >= jumlah) return 0;
    return peserta[indeks].tinggiBadan + hitungTotalTinggiRekursif(peserta, indeks + 1, jumlah);
}

float hitungTotalBeratRekursif(DataPeserta peserta[], int indeks, int jumlah) {
    if(indeks >= jumlah) return 0;
    return peserta[indeks].beratBadan + hitungTotalBeratRekursif(peserta, indeks + 1, jumlah);
}

void tampilkanRataRataRekursif(DataPeserta peserta[], int jumlah) {
    if(jumlah == 0) {
        cout << "\nBelum ada data peserta.\n";
        return;
    }

    float totalTinggi = hitungTotalTinggiRekursif(peserta, 0, jumlah);
    float totalBerat = hitungTotalBeratRekursif(peserta, 0, jumlah);

    cout << "\n--- RATA-RATA DATA PESERTA (REKURSIF) ---\n";
    cout << "Rata-rata Tinggi Badan: " << fixed << setprecision(1)
         << (totalTinggi / jumlah) << " cm\n";
    cout << "Rata-rata Berat Badan : " << (totalBerat / jumlah) << " kg\n";
}

void swapPeserta(DataPeserta &a, DataPeserta &b) {
    DataPeserta temp = a;
    a = b;
    b = temp;
}

void sortByIDAscending(DataPeserta peserta[], int jumlah) {
    for(int i = 0; i < jumlah - 1; i++) {
        for(int j = 0; j < jumlah - i - 1; j++) {
            if(peserta[j].id > peserta[j + 1].id) {
                swapPeserta(peserta[j], peserta[j + 1]);
            }
        }
    }
    cout << "\n Data berhasil diurutkan berdasarkan ID (Ascending)\n";
}

void sortByIDDescending(DataPeserta peserta[], int jumlah) {
    for(int i = 0; i < jumlah - 1; i++) {
        for(int j = 0; j < jumlah - i - 1; j++) {
            if(peserta[j].id < peserta[j + 1].id) {
                swapPeserta(peserta[j], peserta[j + 1]);
            }
        }
    }
    cout << "\n Data berhasil diurutkan berdasarkan ID (Descending)\n";
}

void sortByNamaAscending(DataPeserta peserta[], int jumlah) {
    for(int i = 0; i < jumlah - 1; i++) {
        for(int j = 0; j < jumlah - i - 1; j++) {
            if(peserta[j].namaPanjang > peserta[j + 1].namaPanjang) {
                swapPeserta(peserta[j], peserta[j + 1]);
            }
        }
    }
    cout << "\n Data berhasil diurutkan berdasarkan Nama (A-Z)\n";
}

void sortByNamaDescending(DataPeserta peserta[], int jumlah) {
    for(int i = 0; i < jumlah - 1; i++) {
        for(int j = 0; j < jumlah - i - 1; j++) {
            if(peserta[j].namaPanjang < peserta[j + 1].namaPanjang) {
                swapPeserta(peserta[j], peserta[j + 1]);
            }
        }
    }
    cout << "\n Data berhasil diurutkan berdasarkan Nama (Z-A)\n";
}

void sortByTinggiAscending(DataPeserta peserta[], int jumlah) {
    for(int i = 0; i < jumlah - 1; i++) {
        for(int j = 0; j < jumlah - i - 1; j++) {
            if(peserta[j].tinggiBadan > peserta[j + 1].tinggiBadan) {
                swapPeserta(peserta[j], peserta[j + 1]);
            }
        }
    }
    cout << "\n Data berhasil diurutkan berdasarkan Tinggi (Terendah ke Tertinggi)\n";
}

void sortByTinggiDescending(DataPeserta peserta[], int jumlah) {
    for(int i = 0; i < jumlah - 1; i++) {
        for(int j = 0; j < jumlah - i - 1; j++) {
            if(peserta[j].tinggiBadan < peserta[j + 1].tinggiBadan) {
                swapPeserta(peserta[j], peserta[j + 1]);
            }
        }
    }
    cout << "\n Data berhasil diurutkan berdasarkan Tinggi (Tertinggi ke Terendah)\n";
}

void sortByBMIAscending(DataPeserta peserta[], int jumlah) {
    for(int i = 0; i < jumlah - 1; i++) {
        for(int j = 0; j < jumlah - i - 1; j++) {
            float bmi1 = hitungBMIValue(peserta[j].tinggiBadan, peserta[j].beratBadan);
            float bmi2 = hitungBMIValue(peserta[j + 1].tinggiBadan, peserta[j + 1].beratBadan);
            if(bmi1 > bmi2) {
                swapPeserta(peserta[j], peserta[j + 1]);
            }
        }
    }
    cout << "\n Data berhasil diurutkan berdasarkan BMI (Ascending)\n";
}

void sortByBMIDescending(DataPeserta peserta[], int jumlah) {
    for(int i = 0; i < jumlah - 1; i++) {
        for(int j = 0; j < jumlah - i - 1; j++) {
            float bmi1 = hitungBMIValue(peserta[j].tinggiBadan, peserta[j].beratBadan);
            float bmi2 = hitungBMIValue(peserta[j + 1].tinggiBadan, peserta[j + 1].beratBadan);
            if(bmi1 < bmi2) {
                swapPeserta(peserta[j], peserta[j + 1]);
            }
        }
    }
    cout << "\n Data berhasil diurutkan berdasarkan BMI (Descending)\n";
}

void sortingMenu(DataPeserta peserta[], int jumlah) {
    if(jumlah == 0) {
        cout << "\nBelum ada peserta terdaftar.\n";
        return;
    }

    int pilihan;
    cout << "\n--- MENU SORTING DATA PESERTA ---\n";
    cout << "1. Berdasarkan ID (Ascending)\n";
    cout << "2. Berdasarkan ID (Descending)\n";
    cout << "3. Berdasarkan Nama (A-Z)\n";
    cout << "4. Berdasarkan Nama (Z-A)\n";
    cout << "5. Berdasarkan Tinggi (Terendah-Tertinggi)\n";
    cout << "6. Berdasarkan Tinggi (Tertinggi-Terendah)\n";
    cout << "7. Berdasarkan BMI (Ascending)\n";
    cout << "8. Berdasarkan BMI (Descending)\n";
    cout << "Pilih sorting (1-8): ";
    cin >> pilihan;
    cin.ignore();

    switch(pilihan) {
        case 1: sortByIDAscending(peserta, jumlah); break;
        case 2: sortByIDDescending(peserta, jumlah); break;
        case 3: sortByNamaAscending(peserta, jumlah); break;
        case 4: sortByNamaDescending(peserta, jumlah); break;
        case 5: sortByTinggiAscending(peserta, jumlah); break;
        case 6: sortByTinggiDescending(peserta, jumlah); break;
        case 7: sortByBMIAscending(peserta, jumlah); break;
        case 8: sortByBMIDescending(peserta, jumlah); break;
        default: cout << "\nPilihan tidak valid!\n"; return;
    }

    tampilkanSemuaPeserta(peserta, jumlah);
    simpanKeFile(peserta, jumlah);
}

void simpanKeFile(DataPeserta peserta[], int jumlah) {
    ofstream file("daftarPeserta.txt");

    if(!file.is_open()) {
        cout << "\n Peringatan: Gagal menyimpan ke file!\n";
        return;
    }

    file << jumlah << endl;

    for(int i = 0; i < jumlah; i++) {
        file << peserta[i].id << endl;
        file << peserta[i].namaPanjang << endl;
        file << peserta[i].namaPanggilan << endl;
        file << peserta[i].tglLahir << endl;
        file << peserta[i].jenisKelamin << endl;
        file << peserta[i].noHp << endl;
        file << peserta[i].email << endl;
        file << peserta[i].agency << endl;
        file << peserta[i].tinggiBadan << endl;
        file << peserta[i].beratBadan << endl;
    }

    file.close();
    cout << "\n Data berhasil disimpan ke daftarPeserta.txt (" << jumlah << " peserta)\n";
}

void muatDariFile(DataPeserta peserta[], int &jumlah) {
    ifstream file("daftarPeserta.txt");

    if(!file.is_open()) {
        cout << "\n File daftarPeserta.txt tidak ditemukan. Memulai dengan data kosong.\n";
        jumlah = 0;
        return;
    }

    file >> jumlah;
    file.ignore();

    for(int i = 0; i < jumlah && i < 100; i++) {
        file >> peserta[i].id;
        file.ignore();
        getline(file, peserta[i].namaPanjang);
        getline(file, peserta[i].namaPanggilan);
        getline(file, peserta[i].tglLahir);
        getline(file, peserta[i].jenisKelamin);
        getline(file, peserta[i].noHp);
        getline(file, peserta[i].email);
        getline(file, peserta[i].agency);
        file >> peserta[i].tinggiBadan;
        file >> peserta[i].beratBadan;
        file.ignore();
    }

    file.close();
    cout << "\nData berhasil dimuat dari daftarPeserta.txt (" << jumlah << " peserta)\n";
}
