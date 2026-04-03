#include <iostream>
using namespace std;
#include <limits>

struct Laundry {
    int id;
    string nama;
    float berat;
    string paket;
    string layanan;
    float harga;
    string status;
};

struct Node {
    Laundry data;
    Node* next;
};

Node* head = NULL;

string statusOrderan[4] = {"Menunggu", "Diproses", "Selesai", "Diambil"};
string paketList[2] = {"Reguler", "Ekspress"};

string layananList[7] = {
    "Cuci (Pakaian)", "Lipat", "Setrika",
    "Bed Cover", "Selimut", "Sepatu", "Tas"
};

int hargaReguler[7]  = {5000, 2000, 5000, 30000, 25000, 35000, 25000};
int hargaEkspress[7] = {8000, 4000, 8000, 35000, 30000, 40000, 30000};

int id = 0;
float hargaPerKg = 5000;

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

    do {
        cout << "\nPilih Layanan:" << endl;
        for(int i = 0; i < 7; i++){
            cout << i+1 << ". " << layananList[i] << endl;
        }

        cout << "Pilih: ";
        cin >> pilih;

        while(pilih < 1 || pilih > 7){
            cout << "Pilihan tidak valid! Pilih lagi: ";
            cin >> pilih;
        }

        if(pilihPaket == 1){
            totalHargaPerKg += hargaReguler[pilih - 1];
        } else {
            totalHargaPerKg += hargaEkspress[pilih - 1];
        }

        if(gabunganLayanan != ""){
            gabunganLayanan += " + ";
        }
        gabunganLayanan += layananList[pilih - 1];

        cout << "Tambah layanan lagi? (y/n): ";
        cin >> lanjut;

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
            cout << "2. Diproses" << endl;
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
        cout << "Dibatalkan." << endl;
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

int main() {
    int pilih, id;

    do {
        cout << endl << "========= LAUNDRIFY =========" << endl;
        cout << "1. Tampilkan Pesanan" << endl;
        cout << "2. Tambah Pesanan" << endl;
        cout << "3. Ubah Status Pesanan" << endl;
        cout << "4. Hapus Pesanan" << endl;
        cout << "5. Keluar" << endl;
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
        }

    } while (pilih != 5);

    return 0;
}