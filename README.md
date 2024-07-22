# KKN BINA DESA UNIVERSITAS MULAWARMAN
## PROKER KELOMPOK:
## 1. Filtrasi Air
## 2. Pakan peliharaan otomatis

## NAMA DAN ANGGOTA KELOMPOK 
1. 2109106096 - Filipus Manik

## Deskripsi
Alat monitoring kekeruhan air yang kami buat memanfaatkan sensor pH dan sensor kekeruhan (turbidity sensor) untuk memantau kualitas air secara real-time. Sensor pH digunakan untuk mengukur tingkat keasaman air, sementara turbidity sensor mengukur tingkat kekeruhan air. Data dari kedua sensor tersebut dikirimkan ke broker MQTT dan ditampilkan secara langsung di aplikasi yang dibuat dengan Kodular. Untuk memudahkan identifikasi kondisi air, alat ini dilengkapi dengan LED indikator yang akan menyala sesuai dengan hasil pengukuran: LED merah untuk kondisi kritis, LED kuning untuk kondisi waspada, dan LED hijau untuk kondisi aman.

Selain itu, kami juga mengembangkan alat pakan peliharaan otomatis yang menggunakan sensor jarak dan RTC (Real-Time Clock). Sensor jarak digunakan untuk mendeteksi keberadaan hewan peliharaan di dekat tempat pakan, sementara RTC berfungsi sebagai penentu waktu pemberian pakan secara terjadwal. Alat ini memungkinkan pemberian pakan secara otomatis pada waktu yang telah ditentukan, serta memastikan pakan hanya diberikan saat hewan peliharaan berada di dekat alat. Dengan kombinasi sensor jarak dan RTC, alat ini mampu menjaga jadwal pemberian pakan yang konsisten dan efisien, memastikan hewan peliharaan mendapatkan nutrisi yang dibutuhkan tepat waktu.


## Metode IOT 
### Metode Alat Monitoring Kekeruhan Air
1. Pemasangan Sensor:

- Sensor pH: Dipasang di dalam air untuk mengukur tingkat keasaman atau alkalinitas air.
- Sensor Turbidity: Juga ditempatkan di dalam air untuk mendeteksi tingkat kekeruhan, yang mengindikasikan jumlah partikel tersuspensi dalam air.

2. Pengumpulan Data:

Kedua sensor mengirimkan data analog ke mikrokontroler (seperti Arduino atau ESP32) yang telah diprogram untuk membaca dan mengolah data tersebut.

3. Pengiriman Data:

Data yang telah diolah oleh mikrokontroler dikirimkan ke broker MQTT secara nirkabel. MQTT adalah protokol pesan yang ringan dan ideal untuk komunikasi IoT.

4. Visualisasi Data:

Data yang diterima oleh broker MQTT kemudian ditampilkan secara real-time di aplikasi yang dibuat dengan Kodular. Aplikasi ini memvisualisasikan hasil pengukuran dalam bentuk grafik atau indikator lainnya.

5. Indikator LED:

Berdasarkan data yang diterima, mikrokontroler akan mengaktifkan LED indikator: LED merah untuk kondisi air yang kritis, LED kuning untuk kondisi waspada, dan LED hijau untuk kondisi aman.


## Komponen yang digunakan
1. 4 buah lampu LED
2. 1 buah bread board
3. 1 buah esp8266
4. 3 buah Jumper female to male
5. 1 Buah Jumper male to male
6. 4 Buah Resistor
7. 1 Buah DHT11

## Board Schematic

![Board Schematic](https://github.com/Kuuhaku456/posttest3-praktikum-iot-unmul/blob/main/Gambar_Real_Sketsa.jpg)

## Link video 
[Lampiran Video](https://drive.google.com/file/d/1igVZu2edogFl3B3rgP7S3eKV7EmxxCEB/view?usp=sharing)
