#include <iostream>
using namespace std;

struct Laundry {
    int id;
    string nama;
    float berat;
    float harga;
    string status;
};

struct Node {
    Laundry data;
    Node* next;
};

Node* head = NULL;

string statusOrderan[4] = {"Menunggu", "Dicuci", "Selesai", "Diambil"};

int id = 0;
float hargaPerKg = 5000;

void jeda() {
    string space;
    cout << endl << "Tekan ENTER untuk melanjutkan.";
    cin.ignore();
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
        cout << "Berat: " << temp->data.berat << endl;
        cout << "Harga: " << temp->data.harga << endl;
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
    cout << "Nama: ";
    cin >> baru->data.nama;
    cout << "Berat (kg): ";
    cin >> baru->data.berat;

    baru->data.harga = baru->data.berat * hargaPerKg;
    baru->data.status = "Menunggu";

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

    cout << endl << "Data berhasil ditambahkan!" << endl;
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
                cout << "Masukkan ID: ";
                cin >> id;
                hapusPesanan(id);
                break;
        }

        

    } while (pilih != 5);

    return 0;
}