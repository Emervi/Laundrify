#include <iostream>
using namespace std;
#include <limits>

// penerapan struct
struct Laundry {
    int id;
    string nama;
    float berat;
    string paket;
    string layanan;
    float harga;
    string status;
};

// penerapan single linked list
struct Node {
    Laundry data;
    Node* next;
};

// penerapan pointer
Node* head = NULL;

// penerapan array
string statusOrderan[4] = {"Menunggu", "Diproses", "Selesai", "Diambil"};
string paketList[2] = {"Reguler", "Ekspress"};

string layananList[3] = {"Cuci (Pakaian)", "Lipat", "Setrika"};

int hargaReguler[3]  = {5000, 2000, 5000};
int hargaEkspress[3] = {8000, 4000, 8000};

int id = 0;

void jeda() {
    string space;
    cout << endl << "Tekan ENTER untuk melanjutkan.";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, space);
}

void tampilPesanan() {
    Node* temp = head;

    cout << "========= DAFTAR DATA PESANAN =========" << endl;
    if (temp == NULL) {
        cout << endl << "Data kosong!" << endl;
        jeda();
        return;
    }

    while (temp != NULL) {
        cout << "ID Pesanan: " << temp->data.id << endl;
        cout << "Nama: " << temp->data.nama << endl;
        cout << "Berat: " << temp->data.berat << " kg" << endl;
        cout << "Paket: " << temp->data.paket << endl;
        cout << "Layanan: " << temp->data.layanan << endl;
        cout << "Harga: Rp. " << temp->data.harga << endl;
        cout << "Status: " << temp->data.status << endl;
        cout << "----------------------" << endl;

        temp = temp->next;
    }

    jeda();
}

void tambahPesanan() {
    Node* baru = new Node;

    cout << "========= TAMBAH DATA PESANAN =========" << endl;
    cout << "ID Pesanan: " << id << endl;
    baru->data.id = id;

    do {
        cout << "Nama: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, baru->data.nama);

        if (baru->data.nama.empty()) {
            cout << "Nama tidak boleh kosong!" << endl;
        }
    } while (baru->data.nama.empty());

    do {
        cout << "Berat (kg): ";
        cin >> baru->data.berat;

        if (baru->data.berat <= 0) {
            cout << "Berat tidak valid!" << endl;
        }
    } while (baru->data.berat <= 0);

    int pilihPaket;
    cout << "\nPilih Paket:" << endl;
    for(int i = 0; i < 2; i++){
        cout << i+1 << ". " << paketList[i] << endl;
    }
    cin >> pilihPaket;

    while(pilihPaket < 1 || pilihPaket > 2){
        cout << "Pilihan tidak valid! Pilih lagi: ";
        cin >> pilihPaket;
    }

    int pilih;
    char lanjut;

    string gabunganLayanan = "";
    int totalHargaPerKg = 0;

    bool sudahDipilih[3] = {false, false, false};
    int jumlahLayananDipilih = 0;

    do {
        if (jumlahLayananDipilih >= 3) {
            cout << "\nSemua layanan sudah dipilih!" << endl;
            break;
        }

        cout << "\nPilih Layanan:" << endl;
        bool adaYangTersedia = false;

        for(int i = 0; i < 3; i++){
            if (!sudahDipilih[i]) {
                cout << i+1 << ". " << layananList[i] << endl;
                adaYangTersedia = true;
            } else {
                cout << i+1 << ". [Sudah dipilih]" << endl;
            }
        }

        if (!adaYangTersedia) break;

        cout << "Pilih: ";
        cin >> pilih;

        while(pilih < 1 || pilih > 3){
            cout << "Pilihan tidak valid! Pilih antara 1-3: ";
            cin >> pilih;
        }

        if (sudahDipilih[pilih - 1]) {
            cout << "Layanan ini sudah dipilih! Silakan pilih layanan lain." << endl;
            continue;
        }

        sudahDipilih[pilih - 1] = true;
        jumlahLayananDipilih++;

        if(pilihPaket == 1){
            totalHargaPerKg += hargaReguler[pilih - 1];
        } else {
            totalHargaPerKg += hargaEkspress[pilih - 1];
        }

        if(gabunganLayanan != ""){
            gabunganLayanan += " + ";
        }
        gabunganLayanan += layananList[pilih - 1];

        if (jumlahLayananDipilih < 3) {
            cout << "Tambah layanan lagi? (y/n): ";
            cin >> lanjut;
        } else {
            cout << "\nSemua layanan sudah dipilih!" << endl;
            lanjut = 'n';
        }

    } while(lanjut == 'y' || lanjut == 'Y');

    baru->data.harga = totalHargaPerKg * baru->data.berat;

    baru->data.status = "Menunggu";
    baru->data.paket = paketList[pilihPaket - 1];
    baru->data.layanan = gabunganLayanan;

    baru->next = NULL;

    if (head == NULL) {
        head = baru;
    } else {
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = baru;
    }

    id++;

    cout << "\nData berhasil ditambahkan!" << endl;
    jeda();
}

void ubahStatusPesanan() {
    Node* temp = head;
    int id, pilihanStatus, pass = 0;

    cout << "========= UBAH STATUS PESANAN =========" << endl;
    if (temp == NULL) {
        cout << endl << "Data kosong!" << endl;
        jeda();
        return;
    }

    while (temp != NULL) {

        cout << "ID Pesanan: " << temp->data.id << endl;
        cout << "Nama: " << temp->data.nama << endl;
        cout << "Berat: " << temp->data.berat << endl;
        cout << "Harga: " << temp->data.harga << endl;
        cout << "Status: " << temp->data.status << endl;
        cout << "----------------------" << endl;

        temp = temp->next;
    }

    temp = head;
    cout << "Masukan ID Pesanan: ";
    cin >> id;

    while (temp != NULL) {
        if (temp->data.id == id) {
            cout << "Ubah Status (1-4): " << endl;
            cout << "1. Menunggu" << endl;
            cout << "2. Dicuci" << endl;
            cout << "3. Selesai" << endl;
            cout << "4. Diambil" << endl;

            do {
                cin >> pilihanStatus;

                if (pilihanStatus != 1 && pilihanStatus != 2 && pilihanStatus != 3 && pilihanStatus != 4) {
                    cout << endl << "Pilihan tidak ada." << endl;
                    cout << "Ubah Status (1-4): ";
                }

            } while (pilihanStatus != 1 && pilihanStatus != 2 && pilihanStatus != 3 && pilihanStatus != 4);
            
            temp->data.status = statusOrderan[pilihanStatus - 1];

            cout << endl << "Data berhasil diubah!" << endl;
            jeda();
            return;
        }

        temp = temp->next;
    }

    cout << endl << "Data tidak ditemukan!" << endl;
    jeda();
}

void hapusPesanan(int id) {
    Node *temp = head, *prev = NULL;

    while (temp != NULL && temp->data.id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        cout << endl << "Data tidak ditemukan!" << endl;
        jeda();
        return;
    }

    char konfirmasi;
    cout << "Yakin ingin hapus? (y/n): ";
    cin >> konfirmasi;

    if (konfirmasi != 'y' && konfirmasi != 'Y') {
        cout << endl << "Penghapusan data dibatalkan." << endl;
        jeda();
        return;
    }

    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }


    delete temp;
    cout << endl << "Data berhasil dihapus!" << endl;
    jeda();
}

void pembayaran() {
    int idCari;
    cout << "Masukkan ID Pesanan: ";
    cin >> idCari;

    Node* temp = head;

    while (temp != NULL) {
        if (temp->data.id == idCari) {

            if (temp->data.status == "Menunggu" || temp->data.status == "Dicuci") {
                cout << "Pesanan belum selesai!\n";
                jeda();
                return;
            }

            if (temp->data.status == "Diambil") {
                cout << "Pesanan sudah dibayar!\n";
                jeda();
                return;
            }

            cout << "\n===== PEMBAYARAN =====\n";
            cout << "Nama   : " << temp->data.nama << endl;
            cout << "Total  : Rp. " << temp->data.harga << endl;

            float bayar, kembalian;

            do {
                cout << "Uang bayar: ";
                cin >> bayar;

                if (bayar < temp->data.harga) {
                    cout << "Uang kurang! Masukkan lagi.\n";
                }

            } while (bayar < temp->data.harga);

            kembalian = bayar - temp->data.harga;

            cout << "Kembalian: Rp. " << kembalian << endl;

            temp->data.status = "Diambil";

            cout << "Pembayaran berhasil!\n";

            jeda();
            return;
        }

        temp = temp->next;
    }

    cout << "Data tidak ditemukan!\n";
    jeda();
}

int main() {
    int pilih, id;

    do {
        cout << endl << "========= LAUNDRIFY =========" << endl;
        cout << "1. Tampilkan Pesanan" << endl;
        cout << "2. Tambah Pesanan" << endl;
        cout << "3. Ubah Status Pesanan" << endl;
        cout << "4. Hapus Pesanan" << endl;
        cout << "5. Pembayaran" << endl;
        cout << "6. Keluar" << endl;
        cout << "Pilih: ";
        cin >> pilih;
        cout << endl;

        switch (pilih) {
            case 1: tampilPesanan(); break;
            case 2: tambahPesanan(); break;
            case 3: ubahStatusPesanan(); break;
            case 4:
                do {
                    cout << "Masukkan ID: ";
                    cin >> id;

                    if (id < 0) {
                        cout << "ID tidak valid!" << endl;
                    }
                } while (id < 0);
                hapusPesanan(id);
                break;
            case 5: pembayaran(); break;
            case 6: break;
            default: cout << "Pilihan tidak valid!" << endl;
        }

    } while (pilih != 6);

    return 0;
}