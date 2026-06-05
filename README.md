# 🧺 Laundrify (Sistem Manajemen Laundry Sederhana)

## 📌 Deskripsi

Aplikasi ini merupakan sistem manajemen laundry sederhana berbasis C++ yang dibuat untuk memenuhi tugas implementasi struktur data. Sistem ini memungkinkan pengguna untuk mengelola data laundry mulai dari penerimaan order, proses pencucian, hingga penyelesaian, pembayaran, dan pemulihan data yang terhapus.

---

## 🎯 Tujuan

* Mengimplementasikan konsep:

  * Array
  * Struct
  * Pointer
  * Linked List (Single Linked List)
  * Tree
  * Queue
  * Stack
* Menerapkan operasi dasar CRUD (Create, Read, Update, Delete)

---

## ⚙️ Fitur Utama

* ✅ Menambahkan data laundry
* ✅ Menampilkan data laundry
* ✅ Menampilkan antrian pesanan
* ✅ Mengubah data laundry
* ✅ Menghapus data laundry
* ✅ Undo hapus pesanan
* ✅ Menghitung harga berdasarkan berat cucian
* ✅ Status laundry (Menunggu, Diproses, Selesai, Diambil)
* ✅ Pilihan paket Reguler dan Ekspress dengan layanan bercabang

---

## 🧱 Struktur Data yang Digunakan

### 1. Struct

Digunakan untuk merepresentasikan data laundry:

```cpp
struct Laundry {
    int id;
    string nama;
    float berat;
    float harga;
    string status;
    bool online = true;
};
```

---

### 2. Linked List (Single Linked List)

Digunakan untuk menyimpan data laundry secara dinamis:

```cpp
struct Node {
    Laundry data;
    Node* next;
};
```

---

### 3. Pointer

Digunakan untuk menghubungkan node dalam linked list, antrian, dan stack undo:

```cpp
Node* head = NULL;
```

---

### 4. Array

Digunakan untuk menyimpan status pesanan:

```cpp
string statusOrderan[8] = {"Menunggu Penjemputan", "Dijemput", "Menunggu Pembayaran", "Diproses", "Siap Diantar", "Siap Diambil", "Diantar", "Diambil"};
```

---

### 5. Tree

Digunakan untuk menampilkan cabang pilihan layanan berdasarkan paket:

```cpp
struct TreeLayanan {
  string nama;
  TreeLayanan* anak;
  TreeLayanan* saudara;
};
```

---

### 6. Queue

Digunakan agar pesanan baru otomatis masuk ke antrian paling belakang.

---

### 7. Stack

Digunakan untuk menyimpan data pesanan yang dihapus agar bisa di-restore lewat menu undo.

---

## 🔄 Alur Sistem

1. Pengguna memasukkan data laundry (nama, berat, dll)
2. Sistem menampilkan struktur tree layanan untuk paket Reguler atau Ekspress
3. Sistem menyimpan data ke dalam antrian dan linked list
4. Data diproses dengan status:

   * Menunggu Penjemputan
   * Dijemput
   * Menunggu Pembayaran
   * Diproses
   * Siap Diantar
   * Siap Diambil
   * Diantar
   * Diambil
5. Data yang dihapus disimpan di stack agar bisa di-restore
6. Pengguna dapat:

  * Melihat data
  * Melihat antrian
  * Menambah data
  * Mengubah data
  * Menghapus data
  * Membatalkan hapus terakhir

---

## 📋 Menu Program

```
=== AUTENTIKASI LAUNDRIFY ===
1. Login
2. Keluar
```

```
=== PELANGGAN LAUNDRIFY ===
1. Lihat Pesanan
2. Buat Pesanan
3. Bayar Pesanan
4. Lihat Layanan Laundry
5. Logout
```

```
=== PETUGAS LAUNDRIFY ===
1. Tambah Pesanan
2. Tampilkan Pesanan
3. Tampilkan Antrian
4. Jemput Pesanan
5. Input Berat Pesanan
6. Pembayaran
7. Ubah Status Pesanan
8. Antar Pesanan
9. Pengambilan Pesanan
10. Hapus Pesanan
11. Undo Hapus Pesanan
12. Statistik
13. Logout
```


---

## 🚀 Cara Menjalankan Program

1. Compile program:

```
g++ main.cpp -o laundrify
```

2. Jalankan program:

```
./laundrify
```

---

## 👨‍💻 Author

Dibuat oleh: Kelompok 3 SDDA 2C
Sebagai tugas implementasi struktur data dalam bahasa C++

---
