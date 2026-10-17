# ROS 2 Turtlesim - Konohagakure Symbol Visualizer

Repositori ini berisi implementasi ROS 2 Node berbasis C++ (`rclcpp`) untuk menggambar lambang **Konohagakure** pada simulator `turtlesim`. Program ini memanfaatkan layanan (*service*) ROS 2 untuk penjejakan titik koordinat yang presisi dan membentuk topologi logo secara akurat.

---

## 📌 Informasi Tugas & Pengumpulan
- **Nama/Identitas:** Arnan Refael Adriwinoto
- **Link Video Penjelasan & Demonstrasi:** [https://youtu.be/i18RL8rYgiw](https://youtu.be/i18RL8rYgiw)

---

## 🛠️ Arsitektur & Penjelasan Kode

### 1. Metode Teleportation Path Drawing
Program menggunakan service `/turtle1/teleport_absolute` dan `/turtle1/set_pen` untuk memindahkan *turtle* dari satu titik ke titik berikutnya dalam kurun waktu milidetik.
- **Service `/turtle1/teleport_absolute`:** Memindahkan kura-kura secara instan ke koordinat $(x, y)$ target tanpa memicu kalkulasi kinematic error.
- **Service `/turtle1/set_pen`:** Mengontrol warna ($R, G, B$), ketebalan garis, serta status pena (*on/off*) agar penumpukan garis tidak terjadi saat berpindah segmen.

### 2. Ekstraksi Topologi Skeleton Logo
Titik-titik koordinat pada `outerAndSpiralPath` dan `tailDiagonalPath` didapatkan dari hasil ekstraksi topologi gambar asli Konohagakure:
- **Goresan Utama (`outerAndSpiralPath`):** Menggambar dari ujung *spike* kanan atas, melingkupi bingkai luar, menuju bagian alas ekor, lalu melingkar secara kontinyu menuju pusat spiral daun.
- **Goresan Penutup (`tailDiagonalPath`):** Menggambar garis diagonal pendek untuk menutup bentuk segitiga pada ekor kiri bawah setelah satu kali pergerakan pena (*pen-up*).

---

## 💻 Cara Membangun (Build) dan Menjalankan

### Prasyarat:
- Ubuntu 22.04 LTS
- ROS 2 Humble Hawksbill
- Package dependensi: `rclcpp`, `turtlesim`

### Langkah-Langkah:
1. **Clone Repositori ke ROS 2 Workspace:**
   ```bash
   cd ~/ros2_ws/src
   git clone <LINK_REPO_GITHUB_KAMU>
