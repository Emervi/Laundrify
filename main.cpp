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
// Alur: Menunggu -> Dijemput -> Diproses -> Selesai -> Diantar -> Diambil
string statusOrderan[6] = {"Menunggu", "Dijemput", "Diproses", "Selesai", "Diantar", "Diambil"};
string paketList[2] = {"Reguler", "Ekspress"};

string layananList[3] = {"Cuci (Pakaian)", "Lipat", "Setrika"};

int hargaReguler[3] = {5000, 2000, 5000};
int hargaEkspress[3] = {8000, 4000, 8000};

// Id dimulai dari 1
int id = 1;

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

            cout << "\nLogin berhasil sebagai " << roleLogin << "!\n";

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

    cout << "\nBerikut adalah layanan yang tersedia untuk paket ini:" << endl;
    tampilTreeLayanan(cabang, 1);

    do
    {
        if (jumlah >= 3)
        {
            cout << "\nSemua layanan sudah dipilih." << endl;
            break;
        }

        cout << "\nSilakan pilih layanan yang diinginkan:" << endl;
        for (int i = 0; i < 3; i++)
        {
            cout << i + 1 << ". " << layananList[i];
            if (sudahDipilih[i])
            {
                cout << " [sudah dipilih]";
            }
            cout << endl;
        }
        cout << "Masukkan nomor layanan: ";

        int pilih = bacaPilihan(1, 3);

        if (sudahDipilih[pilih - 1])
        {
            cout << "Layanan ini sudah dipilih. Silakan pilih layanan lain." << endl;
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
            lanjut = bacaKonfirmasi("Apakah ingin menambah layanan lagi? (y/n): ");
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
        cout << "ID Pesanan : " << temp->data.id << endl;
        cout << "Nama       : " << temp->data.nama << endl;
        cout << "Berat      : " << temp->data.berat << " kg" << endl;
        cout << "Paket      : " << temp->data.paket << endl;
        cout << "Layanan    : " << temp->data.layanan << endl;
        cout << "Harga      : Rp. " << temp->data.harga << endl;
        cout << "Status     : " << temp->data.status << endl;
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
    bool ada = false;

    cout << "========= PESANAN SAYA =========" << endl;

    while (temp != NULL)
    {
        if (temp->data.username == usernameLogin)
        {
            cout << "Pesanan ke-" << nomor << endl;
            cout << "ID Pesanan : " << temp->data.id << endl;
            cout << "Nama       : " << temp->data.nama << endl;
            cout << "Berat      : " << temp->data.berat << " kg" << endl;
            cout << "Paket      : " << temp->data.paket << endl;
            cout << "Layanan    : " << temp->data.layanan << endl;
            cout << "Harga      : Rp. " << temp->data.harga << endl;
            cout << "Status     : " << temp->data.status << endl;
            cout << "----------------------" << endl;

            ada = true;
            nomor++;
        }

        temp = temp->next;
    }

    if (!ada)
    {
        cout << "\nBelum ada pesanan!" << endl;
        jeda();
        return;
    }

    // Cek apakah ada pesanan berstatus "Diantar" milik pelanggan ini
    bool adaDiantar = false;
    temp = head;
    while (temp != NULL)
    {
        if (temp->data.username == usernameLogin && temp->data.status == "Diantar")
        {
            adaDiantar = true;
            break;
        }
        temp = temp->next;
    }

    if (adaDiantar)
    {
        cout << "\n========= PESANAN SEDANG DIANTAR =========" << endl;
        cout << "Berikut adalah pesanan Anda yang sedang dalam perjalanan:" << endl;
        cout << "----------------------------------------------" << endl;

        temp = head;
        while (temp != NULL)
        {
            if (temp->data.username == usernameLogin && temp->data.status == "Diantar")
            {
                cout << "ID Pesanan : " << temp->data.id << endl;
                cout << "Nama       : " << temp->data.nama << endl;
                cout << "Paket      : " << temp->data.paket << endl;
                cout << "Layanan    : " << temp->data.layanan << endl;
                cout << "Berat      : " << temp->data.berat << " kg" << endl;
                cout << "Harga      : Rp. " << temp->data.harga << endl;
                cout << "Status     : " << temp->data.status << endl;
                cout << "----------------------" << endl;
            }
            temp = temp->next;
        }

        while (true)
        {
            cout << "\nMasukkan ID Pesanan yang ingin dikonfirmasi penerimaannya" << endl;
            cout << "(masukkan 0 untuk kembali): ";
            int idKonfirmasi = bacaPilihan(0, 1000000);

            if (idKonfirmasi == 0)
            {
                cout << "\nKembali ke menu." << endl;
                break;
            }

            bool ditemukan = false;
            temp = head;
            while (temp != NULL)
            {
                if (temp->data.id == idKonfirmasi)
                {
                    ditemukan = true;

                    if (temp->data.username != usernameLogin)
                    {
                        cout << "\nPesanan ini bukan milik Anda!" << endl;
                        break;
                    }

                    if (temp->data.status != "Diantar")
                    {
                        cout << "\nPesanan ini tidak berstatus Diantar!" << endl;
                        break;
                    }

                    cout << "\nPesanan ID " << temp->data.id << " - " << temp->data.layanan << endl;
                    cout << "Apakah pesanan sudah sampai ke tangan Anda?" << endl;
                    cout << "1. Ya, sudah sampai" << endl;
                    cout << "2. Belum" << endl;
                    cout << "Pilih: ";
                    int pilihSampai = bacaPilihan(1, 2);

                    if (pilihSampai == 1)
                    {
                        char konfirmasi = bacaKonfirmasi("Konfirmasi pesanan ini sudah diterima? (y/n): ");
                        if (konfirmasi == 'y' || konfirmasi == 'Y')
                        {
                            temp->data.status = "Diambil";
                            cout << "\nPesanan ID " << temp->data.id << " ditandai sebagai Diambil." << endl;
                            cout << "Terima kasih telah menggunakan Laundrify!" << endl;
                        }
                        else
                        {
                            cout << "\nKonfirmasi dibatalkan." << endl;
                        }
                    }
                    else
                    {
                        cout << "\nBaik, silakan tunggu pesanan Anda." << endl;
                    }
                    break;
                }
                temp = temp->next;
            }

            if (!ditemukan)
            {
                cout << "\nID Pesanan tidak ditemukan! Silakan masukkan ID yang valid." << endl;
            }
            else
            {
                break;
            }
        }
    }

    jeda();
}

// Cek apakah pelanggan punya pesanan yang bisa dibayar
bool pelangganPunyaPesananBisaBayar()
{
    Node *temp = head;
    while (temp != NULL)
    {
        if (temp->data.username == usernameLogin &&
            temp->data.status == "Dijemput" &&
            temp->data.berat > 0)
        {
            return true;
        }
        temp = temp->next;
    }
    return false;
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

    cout << "========= BUAT PESANAN BARU =========" << endl;
    cout << "ID Pesanan : " << id << endl;
    cout << "Username   : " << usernameLogin << endl;
    baru->data.id = id;
    baru->data.username = usernameLogin;
    baru->data.nama = usernameLogin;
    baru->data.berat = 0;

    cout << "\nSilakan pilih paket laundry:" << endl;
    for (int i = 0; i < 2; i++)
    {
        cout << i + 1 << ". " << paketList[i] << endl;
    }
    cout << "0. Kembali" << endl;
    cout << "Masukkan pilihan paket: ";
    int pilihPaket = bacaPilihan(0, 2);

    if (pilihPaket == 0)
    {
        cout << "\nPembuatan pesanan dibatalkan." << endl;
        delete baru;
        jeda();
        return;
    }

    string gabunganLayanan = "";
    int totalHargaPerKg = 0;

    TreeLayanan *paketTerpilih = NULL;

    cout << "\nBerikut adalah struktur lengkap pilihan layanan:" << endl;
    tampilTreeLayanan(rootLayanan.anak);

    if (pilihPaket == 1)
    {
        paketTerpilih = &nodeReguler;
    }
    else
    {
        paketTerpilih = &nodeEkspress;
    }

    cout << "\nLayanan yang tersedia untuk paket " << paketList[pilihPaket - 1] << ":" << endl;
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

    cout << "\n===== RINGKASAN PESANAN =====" << endl;
    cout << "ID Pesanan : " << id << endl;
    cout << "Username   : " << usernameLogin << endl;
    cout << "Paket      : " << paketList[pilihPaket - 1] << endl;
    cout << "Layanan    : " << gabunganLayanan << endl;
    cout << "Status     : Menunggu (akan dijemput petugas)" << endl;

    char konfirmasi = bacaKonfirmasi("\nKonfirmasi buat pesanan? (y/n): ");
    if (konfirmasi != 'y' && konfirmasi != 'Y')
    {
        cout << "\nPembuatan pesanan dibatalkan." << endl;
        delete baru;
        jeda();
        return;
    }

    enqueuePesanan(baru);
    id++;

    cout << "\nPesanan berhasil dibuat dan masuk ke antrian!" << endl;
    cout << "Tunggu petugas untuk menjemput pesanan Anda." << endl;
    jeda();
}

void inputBeratPesanan()
{
    Node *temp = head;
    bool adaPesananDijemput = false;

    cout << "========= INPUT BERAT PESANAN =========" << endl;
    cout << "Berikut adalah pesanan yang sudah dijemput dan siap diinput berat (Status: Dijemput):" << endl;
    cout << "----------------------------------------------" << endl;

    if (temp == NULL)
    {
        cout << "\nData kosong!" << endl;
        jeda();
        return;
    }

    while (temp != NULL)
    {
        if (temp->data.status == "Dijemput" && temp->data.berat == 0)
        {
            cout << "ID Pesanan : " << temp->data.id << endl;
            cout << "Username   : " << temp->data.username << endl;
            cout << "Nama       : " << temp->data.nama << endl;
            cout << "Paket      : " << temp->data.paket << endl;
            cout << "Layanan    : " << temp->data.layanan << endl;
            cout << "Status     : " << temp->data.status << endl;
            cout << "----------------------" << endl;
            adaPesananDijemput = true;
        }
        temp = temp->next;
    }

    if (!adaPesananDijemput)
    {
        cout << "\nTidak ada pesanan yang siap diinput berat." << endl;
        cout << "Pastikan pesanan sudah dijemput terlebih dahulu melalui menu Jemput Pesanan." << endl;
        jeda();
        return;
    }

    while (true)
    {
        cout << "\nMasukkan ID Pesanan yang ingin diinput beratnya" << endl;
        cout << "(masukkan 0 untuk kembali): ";
        int idCari = bacaPilihan(0, 1000000);

        if (idCari == 0)
        {
            cout << "\nKembali ke menu." << endl;
            jeda();
            return;
        }

        bool ditemukan = false;
        temp = head;
        while (temp != NULL)
        {
            if (temp->data.id == idCari)
            {
                ditemukan = true;

                if (temp->data.status == "Menunggu")
                {
                    cout << "\nPesanan ini belum dijemput!" << endl;
                    cout << "Silakan jemput pesanan terlebih dahulu melalui menu Jemput Pesanan." << endl;
                    break;
                }

                if (temp->data.berat > 0)
                {
                    cout << "\nBerat pesanan ini sudah diinput sebelumnya!" << endl;
                    break;
                }

                if (temp->data.status != "Dijemput")
                {
                    cout << "\nPesanan ini tidak dalam status Dijemput!" << endl;
                    break;
                }

                float berat = bacaFloatPositif("Masukkan berat pakaian (kg): ");
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

                cout << "\nBerat berhasil diinput!" << endl;
                cout << "Total harga: Rp. " << temp->data.harga << endl;
                cout << "Pelanggan kini dapat melakukan pembayaran." << endl;

                jeda();
                return;
            }
            temp = temp->next;
        }

        if (!ditemukan)
        {
            cout << "\nID Pesanan tidak ditemukan! Silakan masukkan ID yang valid." << endl;
        }
    }
}

void ubahStatusPesanan()
{
    Node *temp = head;
    int idPilih, pilihanStatus;

    cout << "========= UBAH STATUS PESANAN =========" << endl;
    if (temp == NULL)
    {
        cout << endl
             << "Data kosong!" << endl;
        jeda();
        return;
    }

    bool adaPesanan = false;
    cout << "Daftar pesanan yang sudah dibayar dan siap diubah status (Status: Diproses):" << endl;
    cout << "----------------------------------------------" << endl;
    while (temp != NULL)
    {
        if (temp->data.status == "Diproses")
        {
            cout << "ID Pesanan : " << temp->data.id << endl;
            cout << "Nama       : " << temp->data.nama << endl;
            cout << "Berat      : " << temp->data.berat << " kg" << endl;
            cout << "Harga      : Rp. " << temp->data.harga << endl;
            cout << "Status     : " << temp->data.status << endl;
            cout << "----------------------" << endl;
            adaPesanan = true;
        }
        temp = temp->next;
    }

    if (!adaPesanan)
    {
        cout << "\nTidak ada pesanan yang perlu diubah statusnya." << endl;
        cout << "Menu ini digunakan setelah pelanggan melakukan pembayaran." << endl;
        jeda();
        return;
    }

    while (true)
    {
        cout << "\nMasukkan ID Pesanan yang ingin diubah statusnya" << endl;
        cout << "(masukkan 0 untuk kembali): ";
        idPilih = bacaPilihan(0, 1000000);

        if (idPilih == 0)
        {
            cout << "\nKembali ke menu." << endl;
            jeda();
            return;
        }

        bool ditemukan = false;
        temp = head;
        while (temp != NULL)
        {
            if (temp->data.id == idPilih)
            {
                ditemukan = true;

                if (temp->data.status != "Diproses")
                {
                    cout << "\nPesanan ini tidak berstatus Diproses." << endl;
                    cout << "Hanya pesanan yang sudah dibayar (Diproses) yang bisa diubah statusnya di sini." << endl;
                    break;
                }

                cout << "\nStatus saat ini: " << temp->data.status << endl;
                cout << "Pilih status baru:" << endl;
                cout << "1. Diproses (tetap)" << endl;
                cout << "2. Selesai" << endl;
                cout << "Masukkan pilihan status: ";

                pilihanStatus = bacaPilihan(1, 2);

                if (pilihanStatus == 1)
                {
                    cout << "\nStatus tidak diubah." << endl;
                }
                else
                {
                    temp->data.status = "Selesai";
                    cout << "\nStatus berhasil diubah menjadi: Selesai" << endl;
                    cout << "Pesanan siap untuk diantar." << endl;
                }

                jeda();
                return;
            }
            temp = temp->next;
        }

        if (!ditemukan)
        {
            cout << "\nID Pesanan tidak ditemukan! Silakan masukkan ID yang valid." << endl;
        }
    }
}

void hapusPesanan(int idHapus)
{
    Node *temp = head, *prev = NULL;

    while (temp != NULL && temp->data.id != idHapus)
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
    konfirmasi = bacaKonfirmasi("Yakin ingin hapus pesanan ini? (y/n): ");

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
    Node *temp = head;
    bool adaPesananBisaBayar = false;

    cout << "========= PEMBAYARAN =========" << endl;
    cout << "Berikut adalah pesanan yang siap dibayar (Status: Dijemput, berat sudah diinput):" << endl;
    cout << "----------------------------------------------" << endl;

    while (temp != NULL)
    {
        bool cocok = false;
        if (roleLogin == "petugas" && temp->data.status == "Dijemput" && temp->data.berat > 0)
        {
            cocok = true;
        }
        else if (roleLogin == "pelanggan" && temp->data.status == "Dijemput" &&
                 temp->data.berat > 0 && temp->data.username == usernameLogin)
        {
            cocok = true;
        }

        if (cocok)
        {
            cout << "ID Pesanan : " << temp->data.id << endl;
            cout << "Nama       : " << temp->data.nama << endl;
            cout << "Paket      : " << temp->data.paket << endl;
            cout << "Layanan    : " << temp->data.layanan << endl;
            cout << "Berat      : " << temp->data.berat << " kg" << endl;
            cout << "Status     : " << temp->data.status << endl;
            cout << "Total      : Rp. " << temp->data.harga << endl;
            cout << "----------------------" << endl;
            adaPesananBisaBayar = true;
        }
        temp = temp->next;
    }

    if (!adaPesananBisaBayar)
    {
        cout << "\nTidak ada pesanan yang siap dibayar saat ini." << endl;
        jeda();
        return;
    }

    while (true)
    {
        cout << "\nMasukkan ID Pesanan yang ingin dibayar" << endl;
        cout << "(masukkan 0 untuk kembali): ";
        int idCari = bacaPilihan(0, 1000000);

        if (idCari == 0)
        {
            cout << "\nKembali ke menu." << endl;
            jeda();
            return;
        }

        bool ditemukan = false;
        temp = head;
        while (temp != NULL)
        {
            if (temp->data.id == idCari)
            {
                ditemukan = true;

                if (roleLogin == "pelanggan" && temp->data.username != usernameLogin)
                {
                    cout << "\nAnda hanya bisa membayar pesanan milik Anda sendiri!" << endl;
                    break;
                }

                if (temp->data.status == "Diambil")
                {
                    cout << "\nPesanan ini sudah dibayar dan diambil!\n";
                    break;
                }

                if (temp->data.status == "Menunggu")
                {
                    cout << "\nPesanan ini belum dijemput dan diproses oleh petugas!" << endl;
                    cout << "Pembayaran hanya bisa dilakukan setelah petugas menjemput dan input berat." << endl;
                    break;
                }

                if (temp->data.status != "Dijemput" || temp->data.berat == 0)
                {
                    cout << "\nPesanan ini belum siap untuk dibayar." << endl;
                    cout << "Pastikan petugas sudah menjemput dan menginput berat pesanan." << endl;
                    break;
                }

                cout << "\n===== DETAIL PEMBAYARAN =====\n";
                cout << "ID Pesanan : " << temp->data.id << endl;
                cout << "Nama       : " << temp->data.nama << endl;
                cout << "Paket      : " << temp->data.paket << endl;
                cout << "Layanan    : " << temp->data.layanan << endl;
                cout << "Berat      : " << temp->data.berat << " kg" << endl;
                cout << "Status     : " << temp->data.status << endl;
                cout << "Total      : Rp. " << temp->data.harga << endl;

                float bayar, kembalian;

                do
                {
                    cout << "\nMasukkan jumlah uang yang dibayarkan: Rp. ";
                    if (cin >> bayar && bayar >= temp->data.harga)
                    {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    }

                    cout << "Uang kurang atau tidak valid! Silakan masukkan lagi.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                } while (true);

                kembalian = bayar - temp->data.harga;

                cout << "Kembalian  : Rp. " << kembalian << endl;

                temp->data.status = "Diproses";

                cout << "\nPembayaran berhasil! Pesanan telah lunas." << endl;
                cout << "Status pesanan diubah ke: Diproses (sedang dikerjakan)." << endl;

                jeda();
                return;
            }
            temp = temp->next;
        }

        if (!ditemukan)
        {
            cout << "\nID Pesanan tidak ditemukan! Silakan masukkan ID yang valid." << endl;
        }
    }
}

void statistik()
{
    Node *temp = head;

    if (temp == NULL)
    {
        cout << "\nBelum ada data pesanan!\n";
        jeda();
        return;
    }

    int totalPesanan = 0;
    float totalPendapatan = 0;

    int countStatus[6] = {0, 0, 0, 0, 0, 0};
    int countLayanan[3] = {0, 0, 0};

    while (temp != NULL)
    {
        totalPesanan++;
        totalPendapatan += temp->data.harga;

        for (int i = 0; i < 6; i++)
        {
            if (temp->data.status == statusOrderan[i])
            {
                countStatus[i]++;
            }
        }

        for (int i = 0; i < 3; i++)
        {
            if (temp->data.layanan.find(layananList[i]) != string::npos)
            {
                countLayanan[i]++;
            }
        }

        temp = temp->next;
    }

    int maxIndex = 0;
    for (int i = 1; i < 3; i++)
    {
        if (countLayanan[i] > countLayanan[maxIndex])
        {
            maxIndex = i;
        }
    }

    cout << "\n========= STATISTIK LAUNDRY =========\n";
    cout << "Total Pesanan     : " << totalPesanan << endl;
    cout << "Total Pendapatan  : Rp. " << totalPendapatan << endl;

    cout << "\nJumlah per Status:\n";
    for (int i = 0; i < 6; i++)
    {
        cout << "- " << statusOrderan[i] << " : " << countStatus[i] << endl;
    }

    cout << "\nLayanan Paling Sering:\n";
    cout << layananList[maxIndex] << " (" << countLayanan[maxIndex] << "x)\n";

    cout << "====================================\n";

    jeda();
}

void jemputPesanan()
{
    Node *temp = head;
    bool ada = false;

    cout << "========= JEMPUT PESANAN =========" << endl;
    cout << "Berikut adalah pesanan yang menunggu dijemput (Status: Menunggu):" << endl;
    cout << "----------------------------------------------" << endl;

    while (temp != NULL)
    {
        if (temp->data.status == "Menunggu")
        {
            cout << "ID Pesanan : " << temp->data.id << endl;
            cout << "Username   : " << temp->data.username << endl;
            cout << "Nama       : " << temp->data.nama << endl;
            cout << "Paket      : " << temp->data.paket << endl;
            cout << "Layanan    : " << temp->data.layanan << endl;
            cout << "Status     : " << temp->data.status << endl;
            cout << "----------------------" << endl;
            ada = true;
        }
        temp = temp->next;
    }

    if (!ada)
    {
        cout << "\nTidak ada pesanan yang menunggu dijemput!" << endl;
        jeda();
        return;
    }

    while (true)
    {
        cout << "\nMasukkan ID Pesanan yang ingin dijemput" << endl;
        cout << "(masukkan 0 untuk kembali): ";
        int idCari = bacaPilihan(0, 1000000);

        if (idCari == 0)
        {
            cout << "\nKembali ke menu." << endl;
            jeda();
            return;
        }

        bool ditemukan = false;
        temp = head;
        while (temp != NULL)
        {
            if (temp->data.id == idCari)
            {
                ditemukan = true;

                if (temp->data.status != "Menunggu")
                {
                    cout << "\nPesanan ini tidak berstatus Menunggu!" << endl;
                    break;
                }

                cout << "\nDetail pesanan yang akan dijemput:" << endl;
                cout << "ID Pesanan : " << temp->data.id << endl;
                cout << "Username   : " << temp->data.username << endl;
                cout << "Paket      : " << temp->data.paket << endl;
                cout << "Layanan    : " << temp->data.layanan << endl;

                char konfirmasi = bacaKonfirmasi("\nKonfirmasi jemput pesanan ini? (y/n): ");
                if (konfirmasi != 'y' && konfirmasi != 'Y')
                {
                    cout << "\nPenjemputan dibatalkan." << endl;
                    jeda();
                    return;
                }

                temp->data.status = "Dijemput";
                cout << "\nPesanan ID " << idCari << " berhasil dijemput!" << endl;
                cout << "Status pesanan diubah ke: Dijemput" << endl;
                cout << "Silakan input berat pesanan melalui menu Input Berat Pesanan." << endl;
                jeda();
                return;
            }
            temp = temp->next;
        }

        if (!ditemukan)
        {
            cout << "\nID Pesanan tidak ditemukan! Silakan masukkan ID yang valid." << endl;
        }
    }
}

void antarPesanan()
{
    Node *temp = head;
    bool ada = false;

    cout << "========= ANTAR PESANAN =========" << endl;
    cout << "Berikut adalah pesanan yang siap diantar (Status: Selesai):" << endl;
    cout << "----------------------------------------------" << endl;

    while (temp != NULL)
    {
        if (temp->data.status == "Selesai")
        {
            cout << "ID Pesanan : " << temp->data.id << endl;
            cout << "Username   : " << temp->data.username << endl;
            cout << "Nama       : " << temp->data.nama << endl;
            cout << "Paket      : " << temp->data.paket << endl;
            cout << "Layanan    : " << temp->data.layanan << endl;
            cout << "Berat      : " << temp->data.berat << " kg" << endl;
            cout << "Harga      : Rp. " << temp->data.harga << endl;
            cout << "Status     : " << temp->data.status << endl;
            cout << "----------------------" << endl;
            ada = true;
        }
        temp = temp->next;
    }

    if (!ada)
    {
        cout << "\nTidak ada pesanan yang siap diantar!" << endl;
        jeda();
        return;
    }

    while (true)
    {
        cout << "\nMasukkan ID Pesanan yang ingin diantar" << endl;
        cout << "(masukkan 0 untuk kembali): ";
        int idCari = bacaPilihan(0, 1000000);

        if (idCari == 0)
        {
            cout << "\nKembali ke menu." << endl;
            jeda();
            return;
        }

        bool ditemukan = false;
        temp = head;
        while (temp != NULL)
        {
            if (temp->data.id == idCari)
            {
                ditemukan = true;

                if (temp->data.status != "Selesai")
                {
                    cout << "\nPesanan ini tidak berstatus Selesai!" << endl;
                    break;
                }

                cout << "\nDetail pesanan yang akan diantar:" << endl;
                cout << "ID Pesanan : " << temp->data.id << endl;
                cout << "Username   : " << temp->data.username << endl;
                cout << "Paket      : " << temp->data.paket << endl;
                cout << "Layanan    : " << temp->data.layanan << endl;
                cout << "Berat      : " << temp->data.berat << " kg" << endl;
                cout << "Harga      : Rp. " << temp->data.harga << endl;

                char konfirmasi = bacaKonfirmasi("\nKonfirmasi antar pesanan ini? (y/n): ");
                if (konfirmasi != 'y' && konfirmasi != 'Y')
                {
                    cout << "\nPengantaran dibatalkan." << endl;
                    jeda();
                    return;
                }

                temp->data.status = "Diantar";
                cout << "\nPesanan ID " << idCari << " sedang diantar!" << endl;
                cout << "Status pesanan diubah ke: Diantar" << endl;
                cout << "Pelanggan akan mengkonfirmasi penerimaan melalui menu Lihat Pesanan." << endl;
                jeda();
                return;
            }
            temp = temp->next;
        }

        if (!ditemukan)
        {
            cout << "\nID Pesanan tidak ditemukan! Silakan masukkan ID yang valid." << endl;
        }
    }
}

int pelanggan()
{
    int pilih;

    do
    {
        // Cek apakah ada pesanan yang bisa dibayar (status Dijemput dan berat > 0)
        bool bisaBayar = pelangganPunyaPesananBisaBayar();

        cout << endl
             << "========= PELANGGAN LAUNDRIFY =========" << endl;
        cout << "1. Lihat Pesanan" << endl;
        cout << "2. Buat Pesanan" << endl;
        if (bisaBayar)
        {
            cout << "3. Bayar Pesanan" << endl;
        }
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
            if (bisaBayar)
            {
                pembayaran();
            }
            else
            {
                cout << "Pilihan tidak tersedia saat ini." << endl;
                cout << "Menu Bayar Pesanan akan muncul setelah petugas menjemput dan menginput berat pesanan Anda." << endl;
                jeda();
            }
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
    int pilih, idInput;

    do
    {
        cout << endl
             << "========= PETUGAS LAUNDRIFY =========" << endl;
        cout << "1. Tampilkan Pesanan" << endl;
        cout << "2. Tampilkan Antrian" << endl;
        cout << "3. Input Berat Pesanan" << endl;
        cout << "4. Ubah Status Pesanan" << endl;
        cout << "5. Hapus Pesanan" << endl;
        cout << "6. Pembayaran" << endl;
        cout << "7. Undo Hapus Pesanan" << endl;
        cout << "8. Statistik" << endl;
        cout << "9. Jemput Pesanan" << endl;
        cout << "10. Antar Pesanan" << endl;
        cout << "11. Logout" << endl;
        cout << "Pilih: ";
        pilih = bacaPilihan(1, 11);
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
            inputBeratPesanan();
            break;
        case 4:
            ubahStatusPesanan();
            break;
        case 5:
        {
            cout << "========= HAPUS PESANAN =========" << endl;
            Node *temp = head;
            if (temp == NULL)
            {
                cout << "Data kosong!" << endl;
                jeda();
                break;
            }
            cout << "Daftar pesanan:" << endl;
            cout << "----------------------------------------------" << endl;
            while (temp != NULL)
            {
                cout << "ID Pesanan : " << temp->data.id
                     << " | " << temp->data.nama
                     << " | Status: " << temp->data.status << endl;
                temp = temp->next;
            }

            while (true)
            {
                cout << "\nMasukkan ID Pesanan yang ingin dihapus" << endl;
                cout << "(masukkan 0 untuk kembali): ";
                idInput = bacaPilihan(0, 1000000);
                if (idInput == 0)
                {
                    cout << "\nKembali ke menu." << endl;
                    jeda();
                    break;
                }

                bool ada = false;
                temp = head;
                while (temp != NULL)
                {
                    if (temp->data.id == idInput)
                    {
                        ada = true;
                        break;
                    }
                    temp = temp->next;
                }

                if (!ada)
                {
                    cout << "\nID Pesanan tidak ditemukan! Silakan masukkan ID yang valid." << endl;
                }
                else
                {
                    hapusPesanan(idInput);
                    break;
                }
            }
            break;
        }
        case 6:
            pembayaran();
            break;
        case 7:
            undoHapusPesanan();
            break;
        case 8:
            statistik();
            break;
        case 9:
            jemputPesanan();
            break;
        case 10:
            antarPesanan();
            break;
        case 11:
            logout();
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
        }

    } while (pilih != 11);

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