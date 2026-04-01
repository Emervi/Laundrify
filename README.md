# 🧺 Laundrify (Sistem Manajemen Laundry Sederhana)

## 📌 Deskripsi

Aplikasi ini merupakan sistem manajemen laundry sederhana berbasis C++ yang dibuat untuk memenuhi tugas implementasi struktur data. Sistem ini memungkinkan pengguna untuk mengelola data laundry mulai dari penerimaan order, proses pencucian, hingga penyelesaian dan pembayaran.

---

## 🎯 Tujuan

* Mengimplementasikan konsep:

  * Array
  * Struct
  * Pointer
  * Linked List (Single Linked List)
* Menerapkan operasi dasar CRUD (Create, Read, Update, Delete)

---

## ⚙️ Fitur Utama

* ✅ Menambahkan data laundry
* ✅ Menampilkan data laundry
* ✅ Mengubah data laundry
* ✅ Menghapus data laundry
* ✅ Menghitung harga berdasarkan berat cucian
* ✅ Status laundry (Menunggu, Dicuci, Selesai, Diambil)

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

Digunakan untuk menghubungkan node dalam linked list:

```cpp
Node* head = NULL;
```

---

### 4. Array

Digunakan untuk menyimpan status pesanan:

```cpp
string statusOrderan[4] = {"Menunggu", "Dicuci", "Selesai", "Diambil"};
```

---

## 🔄 Alur Sistem

1. Pengguna memasukkan data laundry (nama, berat, dll)
2. Sistem menyimpan data ke dalam linked list
3. Data diproses dengan status:

   * Menunggu
   * Dicuci
   * Selesai
   * Diambil
4. Pengguna dapat:

   * Melihat data
   * Menambah data
   * Mengubah data
   * Menghapus data

---

## 📋 Menu Program

```
=== SISTEM LAUNDRY ===
1. Tambah Pesanan
2. Tampilkan Pesanan
3. Ubah Status Pesanan
4. Hapus Pesanan
5. Keluar
```

---

## 🚀 Cara Menjalankan Program

1. Compile program:

```
g++ laundry.cpp -o laundry
```

2. Jalankan program:

```
./laundry
```

---

## 👨‍💻 Author

Dibuat oleh: Kelompok 3 SDDA 2C
Sebagai tugas implementasi struktur data dalam bahasa C++

---
