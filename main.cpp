#include <iostream>
using namespace std;
#include <limits>
#include <string>

// penerapan struct
struct Laundry
{
    int id;
    string username;
    string nama;
    float berat;
    string paket;
    string layanan;
    float harga;
    string status;
};

// penerapan single linked list
struct Node
{
    Laundry data;
    Node *next;
};

// penerapan tree
struct TreeLayanan
{
    string nama;
    TreeLayanan *anak;
    TreeLayanan *saudara;
};

struct Akun
{
    string username;
    string password;
    string role;
};

// penerapan pointer
Node *head = NULL;
Node *tail = NULL;
Node *stackHapus = NULL;

// penerapan array
string statusOrderan[4] = {"Menunggu", "Diproses", "Selesai", "Diambil"};
string paketList[2] = {"Reguler", "Ekspress"};

string layananList[3] = {"Cuci (Pakaian)", "Lipat", "Setrika"};

int hargaReguler[3] = {5000, 2000, 5000};
int hargaEkspress[3] = {8000, 4000, 8000};

int id = 0;

Akun daftarAkun[4] = {
    {"pelanggan1", "123", "pelanggan"},
    {"pelanggan2", "123", "pelanggan"},
    {"petugas1", "123", "petugas"},
    {"petugas2", "123", "petugas"}};

bool sudahLogin = false;
string roleLogin = "";
string usernameLogin = "";

TreeLayanan rootLayanan = {"Layanan", NULL, NULL};
TreeLayanan nodeReguler = {"Reguler", NULL, NULL};
TreeLayanan nodeEkspress = {"Ekspress", NULL, NULL};
TreeLayanan nodeRegulerCuci = {"Cuci (Pakaian)", NULL, NULL};
TreeLayanan nodeRegulerLipat = {"Lipat", NULL, NULL};
TreeLayanan nodeRegulerSetrika = {"Setrika", NULL, NULL};
TreeLayanan nodeEkspressCuci = {"Cuci (Pakaian)", NULL, NULL};
TreeLayanan nodeEkspressLipat = {"Lipat", NULL, NULL};
TreeLayanan nodeEkspressSetrika = {"Setrika", NULL, NULL};

void jeda();
string bacaNama(const string &prompt);
bool login();
void logout();

bool login()
{
    string username, password;

    cout << "========= LOGIN =========" << endl;

    username = bacaNama("Username: ");
    password = bacaNama("Password: ");

    for (int i = 0; i < 4; i++)
    {
        if (daftarAkun[i].username == username &&
            daftarAkun[i].password == password)
        {

            sudahLogin = true;
            roleLogin = daftarAkun[i].role;
            usernameLogin = daftarAkun[i].username;

            cout << "\nLogin berhasil sebagai "
                 << roleLogin << "!\n";

            jeda();
            return true;
        }
    }

    cout << "\nLogin gagal!\n";
    jeda();
    return false;
}

void logout()
{
    sudahLogin = false;
    roleLogin = "";
    usernameLogin = "";

    cout << "\nLogout berhasil!\n";
    jeda();
}

int bacaPilihan(int min, int max)
{
    int pilihan;

    while (true)
    {
        if (cin >> pilihan && pilihan >= min && pilihan <= max)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return pilihan;
        }

        cout << "Input tidak valid! Masukkan angka " << min << "-" << max << ": ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

float bacaFloatPositif(const string &prompt)
{
    float nilai;

    while (true)
    {
        cout << prompt;
        if (cin >> nilai && nilai > 0)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return nilai;
        }

        cout << "Input tidak valid!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string bacaNama(const string &prompt)
{
    string nilai;

    while (true)
    {
        cout << prompt;
        getline(cin >> ws, nilai);

        if (!nilai.empty())
        {
            return nilai;
        }

        cout << "Nama tidak boleh kosong!" << endl;
    }
}

char bacaKonfirmasi(const string &prompt)
{
    char nilai;

    while (true)
    {
        cout << prompt;
        if (cin >> nilai)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (nilai == 'y' || nilai == 'Y' || nilai == 'n' || nilai == 'N')
            {
                return nilai;
            }
        }

        cout << "Input tidak valid! Masukkan y/n." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void tampilTreeLayanan(TreeLayanan *node, int level = 0)
{
    while (node != NULL)
    {
        for (int i = 0; i < level; i++)
        {
            cout << "  ";
        }
        cout << "- " << node->nama << endl;

        if (node->anak != NULL)
        {
            tampilTreeLayanan(node->anak, level + 1);
        }

        node = node->saudara;
    }
}

int pilihLayananTree(TreeLayanan *cabang, int hargaPaket[3], string dipilih[3], bool sudahDipilih[3])
{
    int jumlah = 0;
    char lanjut = 'y';

    cout << "\nMenu layanan untuk paket ini:" << endl;
    tampilTreeLayanan(cabang, 1);

    do
    {
        if (jumlah >= 3)
        {
            cout << "\nSemua layanan sudah dipilih." << endl;
            break;
        }

        cout << "\nPilih layanan:" << endl;
        for (int i = 0; i < 3; i++)
        {
            cout << i + 1 << ". " << layananList[i];
            if (sudahDipilih[i])
            {
                cout << " [sudah dipilih]";
            }
            cout << endl;
        }

        int pilih = bacaPilihan(1, 3);

        if (sudahDipilih[pilih - 1])
        {
            cout << "Layanan ini sudah dipilih. Pilih layanan lain." << endl;
            continue;
        }

        sudahDipilih[pilih - 1] = true;
        if (!dipilih[0].empty())
        {
            dipilih[0] += " + ";
        }
        dipilih[0] += layananList[pilih - 1];
        jumlah++;

        if (lanjut != 'n' && jumlah < 3)
        {
            lanjut = bacaKonfirmasi("Tambah layanan lagi? (y/n): ");
        }
        else
        {
            lanjut = 'n';
        }
    } while (lanjut == 'y' || lanjut == 'Y');

    return jumlah;
}

void inisialisasiTreeLayanan()
{
    rootLayanan.anak = &nodeReguler;

    nodeReguler.saudara = &nodeEkspress;
    nodeReguler.anak = &nodeRegulerCuci;

    nodeRegulerCuci.saudara = &nodeRegulerLipat;
    nodeRegulerLipat.saudara = &nodeRegulerSetrika;

    nodeEkspress.anak = &nodeEkspressCuci;

    nodeEkspressCuci.saudara = &nodeEkspressLipat;
    nodeEkspressLipat.saudara = &nodeEkspressSetrika;
}

void enqueuePesanan(Node *baru)
{
    baru->next = NULL;

    if (head == NULL)
    {
        head = baru;
        tail = baru;
    }
    else
    {
        tail->next = baru;
        tail = baru;
    }
}

void tampilAntrian()
{
    Node *temp = head;
    int nomor = 1;

    cout << "========= ANTRIAN PESANAN =========" << endl;

    if (temp == NULL)
    {
        cout << "Antrian masih kosong!" << endl;
        jeda();
        return;
    }

    while (temp != NULL)
    {
        cout << nomor << ". ID " << temp->data.id
             << " | " << temp->data.nama
             << " | User: " << temp->data.username
             << " | Status: " << temp->data.status << endl;

        temp = temp->next;   
        nomor++;
    }

    jeda();
}

void pushHapusPesanan(const Laundry &data)
{
    Node *baru = new Node;
    baru->data = data;
    baru->next = stackHapus;
    stackHapus = baru;
}

void undoHapusPesanan()
{
    cout << "========= UNDO HAPUS PESANAN =========" << endl;

    if (stackHapus == NULL)
    {
        cout << endl
             << "Tidak ada data yang bisa di-restore!" << endl;
        jeda();
        return;
    }

    Node *restore = stackHapus;
    stackHapus = stackHapus->next;

    enqueuePesanan(restore);

    cout << endl
         << "Data berhasil di-restore!" << endl;
    jeda();
}

void jeda()
{
    string space;
    cout << endl
         << "Tekan ENTER untuk melanjutkan.";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, space);
}

void tampilPesanan()
{
    Node *temp = head;
    int nomor = 1;

    cout << "========= DAFTAR DATA PESANAN =========" << endl;
    if (temp == NULL)
    {
        cout << endl
             << "Data kosong!" << endl;
        jeda();
        return;
    }

    while (temp != NULL)
    {
        cout << "Antrian ke-" << nomor << endl;
        cout << "ID Pesanan: " << temp->data.id << endl;
        cout << "Nama: " << temp->data.nama << endl;
        cout << "Berat: " << temp->data.berat << " kg" << endl;
        cout << "Paket: " << temp->data.paket << endl;
        cout << "Layanan: " << temp->data.layanan << endl;
        cout << "Harga: Rp. " << temp->data.harga << endl;
        cout << "Status: " << temp->data.status << endl;
        cout << "----------------------" << endl;

        temp = temp->next;
        nomor++;
    }

    jeda();
}

void tampilPesananPelanggan()
{
    Node *temp = head;
    int nomor = 1;

    cout << "========= PESANAN SAYA =========" << endl;

    bool ada = false;

    while (temp != NULL)
    {

        if (temp->data.username == usernameLogin)
        {

            cout << "Pesanan ke-" << nomor << endl;
            cout << "ID Pesanan: " << temp->data.id << endl;
            cout << "Nama: " << temp->data.nama << endl;
            cout << "Berat: " << temp->data.berat << " kg" << endl;
            cout << "Paket: " << temp->data.paket << endl;
            cout << "Layanan: " << temp->data.layanan << endl;
            cout << "Harga: Rp. " << temp->data.harga << endl;
            cout << "Status: " << temp->data.status << endl;
            cout << "----------------------" << endl;

            ada = true;
            nomor++;
        }

        temp = temp->next;
    }

    if (!ada)
    {
        cout << "\nBelum ada pesanan!" << endl;
    }

    jeda();
}

void tambahPesanan()
{
    if (roleLogin != "pelanggan")
    {
        cout << "Hanya pelanggan yang bisa membuat pesanan!\n";
        jeda();
        return;
    }

    Node *baru = new Node;

    cout << "========= TAMBAH DATA PESANAN =========" << endl;
    cout << "ID Pesanan: " << id << endl;
    baru->data.id = id;

    baru->data.username = usernameLogin;
    baru->data.nama = usernameLogin;
    baru->data.berat = 0;

    int pilihPaket;
    cout << "\nPilih Paket:" << endl;
    for (int i = 0; i < 2; i++)
    {
        cout << i + 1 << ". " << paketList[i] << endl;
    }
    pilihPaket = bacaPilihan(1, 2);

    string gabunganLayanan = "";
    int totalHargaPerKg = 0;

    TreeLayanan *paketTerpilih = NULL;

    cout << "\nStruktur Pilihan Layanan:" << endl;
    tampilTreeLayanan(rootLayanan.anak);

    if (pilihPaket == 1)
    {
        paketTerpilih = &nodeReguler;
    }
    else
    {
        paketTerpilih = &nodeEkspress;
    }

    cout << "\nCabang layanan untuk paket " << paketList[pilihPaket - 1] << ":" << endl;
    tampilTreeLayanan(paketTerpilih->anak, 1);

    bool sudahDipilih[3] = {false, false, false};
    string layananTerpilih[1] = {""};

    int jumlahLayananDipilih = 0;
    if (pilihPaket == 1)
    {
        jumlahLayananDipilih = pilihLayananTree(paketTerpilih->anak, hargaReguler, layananTerpilih, sudahDipilih);
        for (int i = 0; i < 3; i++)
        {
            if (sudahDipilih[i])
            {
                totalHargaPerKg += hargaReguler[i];
                if (!gabunganLayanan.empty())
                {
                    gabunganLayanan += " + ";
                }
                gabunganLayanan += layananList[i];
            }
        }
    }
    else
    {
        jumlahLayananDipilih = pilihLayananTree(paketTerpilih->anak, hargaEkspress, layananTerpilih, sudahDipilih);
        for (int i = 0; i < 3; i++)
        {
            if (sudahDipilih[i])
            {
                totalHargaPerKg += hargaEkspress[i];
                if (!gabunganLayanan.empty())
                {
                    gabunganLayanan += " + ";
                }
                gabunganLayanan += layananList[i];
            }
        }
    }

    if (jumlahLayananDipilih == 0)
    {
        cout << "\nMinimal pilih satu layanan!" << endl;
        delete baru;
        jeda();
        return;
    }

    baru->data.harga = 0;

    baru->data.status = "Menunggu";
    baru->data.paket = paketList[pilihPaket - 1];
    baru->data.layanan = gabunganLayanan;

    enqueuePesanan(baru);

    id++;

    cout << "\nData berhasil ditambahkan ke antrian!" << endl;
    jeda();
}

void inputBeratPesanan()
{
    Node *temp = head;
    int idCari;

    cout << "INPUT BERAT PESANAN" << endl;

    if (temp == NULL)
    {
        cout << "\nData kosong!" << endl;
        jeda();
        return;
    }

    tampilPesanan();

    cout << "Masukkan ID Pesanan: ";
    idCari = bacaPilihan(0, 1000000);

    while (temp != NULL)
    {

        if (temp->data.id == idCari)
        {

            if (temp->data.berat > 0)
            {
                cout << "\nBerat sudah diinput!" << endl;
                jeda();
                return;
            }

            float berat = bacaFloatPositif("Masukkan berat (kg): ");
            temp->data.berat = berat;

            int totalHargaPerKg = 0;

            for (int i = 0; i < 3; i++)
            {
                if (temp->data.layanan.find(layananList[i]) != string::npos)
                {

                    if (temp->data.paket == "Reguler")
                        totalHargaPerKg += hargaReguler[i];
                    else
                        totalHargaPerKg += hargaEkspress[i];
                }
            }

            temp->data.harga = berat * totalHargaPerKg;
            temp->data.status = "Diproses";

            cout << "\nBerat berhasil diinput!" << endl;
            cout << "Total harga: Rp. " << temp->data.harga << endl;

            jeda();
            return;
        }

        temp = temp->next;
    }

    cout << "\nData tidak ditemukan!" << endl;
    jeda();
}

void ubahStatusPesanan()
{
    Node *temp = head;
    int id, pilihanStatus;

    cout << "========= UBAH STATUS PESANAN =========" << endl;
    if (temp == NULL)
    {
        cout << endl
             << "Data kosong!" << endl;
        jeda();
        return;
    }

    while (temp != NULL)
    {

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
    id = bacaPilihan(0, 1000000);

    while (temp != NULL)
    {
        if (temp->data.id == id)
        {
            cout << "Ubah Status (1-4): " << endl;
            cout << "1. Menunggu" << endl;
            cout << "2. Diproses" << endl;
            cout << "3. Selesai" << endl;
            cout << "4. Diambil" << endl;

            pilihanStatus = bacaPilihan(1, 4);

            temp->data.status = statusOrderan[pilihanStatus - 1];

            cout << endl
                 << "Data berhasil diubah!" << endl;
            jeda();
            return;
        }

        temp = temp->next;
    }

    cout << endl
         << "Data tidak ditemukan!" << endl;
    jeda();
}

void hapusPesanan(int id)
{
    Node *temp = head, *prev = NULL;

    while (temp != NULL && temp->data.id != id)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        cout << endl
             << "Data tidak ditemukan!" << endl;
        jeda();
        return;
    }

    char konfirmasi;
    konfirmasi = bacaKonfirmasi("Yakin ingin hapus? (y/n): ");

    if (konfirmasi != 'y' && konfirmasi != 'Y')
    {
        cout << endl
             << "Penghapusan data dibatalkan." << endl;
        jeda();
        return;
    }

    if (prev == NULL)
    {
        head = temp->next;
    }
    else
    {
        prev->next = temp->next;
    }

    if (temp == tail)
    {
        tail = prev;
    }

    pushHapusPesanan(temp->data);

    delete temp;
    cout << endl
         << "Data berhasil dihapus!" << endl;
    jeda();
}

void pembayaran()
{
    int idCari;
    cout << "Masukkan ID Pesanan: ";
    idCari = bacaPilihan(0, 1000000);

    Node *temp = head;

    while (temp != NULL)
    {
        if (temp->data.id == idCari)
        {

            if (temp->data.status == "Menunggu" || temp->data.status == "Diproses")
            {
                cout << "Pesanan belum selesai!\n";
                jeda();
                return;
            }

            if (temp->data.status == "Diambil")
            {
                cout << "Pesanan sudah dibayar!\n";
                jeda();
                return;
            }

            cout << "\n===== PEMBAYARAN =====\n";
            cout << "Nama   : " << temp->data.nama << endl;
            cout << "Total  : Rp. " << temp->data.harga << endl;

            float bayar, kembalian;

            do
            {
                cout << "Uang bayar: ";
                if (cin >> bayar && bayar >= temp->data.harga)
                {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }

                cout << "Uang kurang atau tidak valid! Masukkan lagi.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

            } while (true);

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

int pelanggan()
{
    int pilih;

    do
    {
        cout << endl
             << "========= PELANGGAN LAUNDRIFY =========" << endl;
        cout << "1. Lihat Pesanan " << endl;
        cout << "2. Buat Pesanan" << endl;
        cout << "3. Bayar Pesanan" << endl;
        cout << "4. Lihat Layanan Laundry" << endl;
        cout << "5. Logout" << endl;
        cout << "Pilih: ";
        pilih = bacaPilihan(1, 5);
        cout << endl;

        switch (pilih)
        {
        case 1:
            tampilPesananPelanggan();
            break;

        case 2:
            tambahPesanan();
            break;

        case 3:
            pembayaran();
            break;
        case 4:
            cout << "========= INFORMASI LAYANAN LAUNDRY =========" << endl;
            tampilTreeLayanan(rootLayanan.anak);
            jeda();
            break;
        case 5:
            logout();
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
        }

    } while (pilih != 5);

    return 0;
}

int petugas()
{
    int pilih, id;

    // inisialisasiTreeLayanan();

    do
    {
        cout << endl
             << "========= PETUGAS LAUNDRIFY =========" << endl;
        cout << "1. Tampilkan Pesanan" << endl;
        cout << "2. Tampilkan Antrian" << endl;
        cout << "3. Tambah Pesanan" << endl;
        cout << "4. Input Berat Pesanan" << endl;
        cout << "5. Ubah Status Pesanan" << endl;
        cout << "6. Hapus Pesanan" << endl;
        cout << "7. Pembayaran" << endl;
        cout << "8. Undo Hapus Pesanan" << endl;
        cout << "9. Logout" << endl;
        cout << "Pilih: ";
        pilih = bacaPilihan(1, 10);
        cout << endl;

        switch (pilih)
        {
        case 1:
            tampilPesanan();
            break;
        case 2:
            tampilAntrian();
            break;
        case 3:
            tambahPesanan();
            break;
        case 4:
            inputBeratPesanan();
            break;
        case 5:
            ubahStatusPesanan();
            break;
        case 6:
            cout << "Masukkan ID: ";
            id = bacaPilihan(0, 1000000);
            hapusPesanan(id);
            break;
        case 7:
            pembayaran();
            break;
        case 8:
            undoHapusPesanan();
            break;
        case 9:
            logout();
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
        }

    } while (pilih != 9);

    return 0;
}

int main()
{
    int pilih;

    inisialisasiTreeLayanan();

    do
    {
        cout << endl
             << "========= LAUNDRIFY =========" << endl;
        cout << "1. Login" << endl;
        cout << "2. Keluar" << endl;
        cout << "Pilih: ";
        pilih = bacaPilihan(1, 2);
        cout << endl;

        switch (pilih)
        {

        case 1:
            if (login())
            {

                if (roleLogin == "pelanggan")
                {
                    pelanggan();
                }
                else if (roleLogin == "petugas")
                {
                    petugas();
                }
            }
            break;

        case 2:
            break;

        default:
            cout << "Pilihan tidak valid!" << endl;
        }

    } while (pilih != 2);

    return 0;
}