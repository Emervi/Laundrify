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
* ✅ Status laundry (Proses, Selesai, Diambil)

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

Digunakan untuk menyimpan daftar harga per kg:

```cpp
float hargaPerKg[3] = {5000, 7000, 10000};
```

---

## 🔄 Alur Sistem

1. Pengguna memasukkan data laundry (nama, berat, dll)
2. Sistem menyimpan data ke dalam linked list
3. Data diproses dengan status:

   * Proses
   * Selesai
   * Diambil
4. Pengguna dapat:

   * Melihat data
   * Mengubah data
   * Menghapus data

---

## 📋 Menu Program

```
=== SISTEM LAUNDRY ===
1. Tambah Data
2. Tampilkan Data
3. Ubah Data
4. Hapus Data
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
