#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Konfigurasi Layar OLED 128x64
#define LEBAR_LAYAR 128
#define TINGGI_LAYAR 64
Adafruit_SSD1306 display(LEBAR_LAYAR, TINGGI_LAYAR, &Wire, -1);

// Konstanta Pin Hardware
const int PIN_TRIG   = 5;
const int PIN_ECHO   = 18;
const int PIN_GAS    = 34;
const int PIN_BUZZER = 19;
const int BATAS_GAS_BAHAYA = 2000;

// Konstanta Frekuensi Nada Musik (Hz)
#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_D5  587
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_G5  784
#define NOTE_A5  880
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_E6  1319

// Variabel Status & Pewaktu
String statusSekarang = "NORMAL";
int tingkatEnergi = 85;
int arahLirik = 0;

unsigned long waktuTerakhirInteraksi = 0;
unsigned long waktuMulaiDidekati     = 0;
unsigned long waktuMulaiDekatSekali  = 0;
unsigned long waktuAnimasiIdle       = 0;
unsigned long waktuKurangEnergi      = 0;

bool sedangDidekati    = false;
bool sempatDekatSekali = false;

// Variabel Mini-Game Tebak Angka
bool sedangMainTebak = false;
int angkaRahasia = 0;

// 1. FUNGSI PEMBACA SENSOR (Return Value 'int')

int bacaJarakCm() {
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  long durasi = pulseIn(PIN_ECHO, HIGH, 25000);
  if (durasi == 0) return 999;

  return durasi * 0.034 / 2;
}

int bacaKadarGas() {
  return analogRead(PIN_GAS);
}

// 2. FUNGSI ANIMASI WAJAH OLED

void wajahNormal(int geserX, bool berkedip) {
  display.clearDisplay();

  if (berkedip) {
    display.fillRect(28 + geserX, 27, 26, 4, WHITE);
    display.fillRect(74 + geserX, 27, 26, 4, WHITE);
  } else {
    display.fillRoundRect(28 + geserX, 14, 26, 28, 8, WHITE);
    display.fillRoundRect(74 + geserX, 14, 26, 28, 8, WHITE);
  }

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(16, 54);
  display.printf("MOCHI | ENERGI:%d%%", tingkatEnergi);
  display.display();
}

void wajahSenang(String pesan) {
  display.clearDisplay();
  display.fillCircle(41, 30, 14, WHITE);
  display.fillRect(25, 30, 32, 16, BLACK);

  display.fillCircle(87, 30, 14, WHITE);
  display.fillRect(71, 30, 32, 16, BLACK);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(14, 54);
  display.println(pesan);
  display.display();
}

void wajahManja() {
  display.clearDisplay();
  display.fillCircle(36, 21, 6, WHITE);
  display.fillCircle(46, 21, 6, WHITE);
  display.fillTriangle(30, 23, 52, 23, 41, 36, WHITE);

  display.fillCircle(82, 21, 6, WHITE);
  display.fillCircle(92, 21, 6, WHITE);
  display.fillTriangle(76, 23, 98, 23, 87, 36, WHITE);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(14, 54);
  display.println("HEHE... ENAK DIELUS");
  display.display();
}

void wajahCilukba() {
  display.clearDisplay();
  display.fillCircle(41, 30, 13, WHITE);
  display.fillRect(26, 30, 30, 15, BLACK);
  display.drawCircle(87, 25, 11, WHITE);
  display.fillCircle(87, 25, 5, WHITE);

  display.fillCircle(64, 37, 7, WHITE);
  display.fillRect(55, 30, 18, 7, BLACK);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(22, 54);
  display.println("CILUKBA! HAHA!");
  display.display();
}

void wajahLapar() {
  display.clearDisplay();
  display.drawCircle(41, 25, 12, WHITE);
  display.drawCircle(41, 25, 6, WHITE);
  display.drawCircle(87, 25, 12, WHITE);
  display.drawCircle(87, 25, 6, WHITE);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 54);
  display.println("LAPAR... KETIK 'makan'");
  display.display();
}

void wajahKaget() {
  display.clearDisplay();
  display.drawLine(28, 16, 50, 27, WHITE);
  display.drawLine(28, 38, 50, 27, WHITE);
  display.drawLine(100, 16, 78, 27, WHITE);
  display.drawLine(100, 38, 78, 27, WHITE);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(12, 54);
  display.println("EH! DEKET BANGET!");
  display.display();
}

void wajahPusingGas() {
  display.clearDisplay();
  display.drawLine(28, 15, 52, 39, WHITE);
  display.drawLine(52, 15, 28, 39, WHITE);
  display.drawLine(76, 15, 100, 39, WHITE);
  display.drawLine(100, 15, 76, 39, WHITE);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 54);
  display.println("UHUK! ADA GAS/ASAP!");
  display.display();
}

// =========================================================================
// 3. FUNGSI SUARA, LAGU SERU & MODE ULANG TAHUN
// =========================================================================

void suaraSapa() {
  tone(PIN_BUZZER, NOTE_C5, 90);
  delay(100);
  tone(PIN_BUZZER, NOTE_E5, 120);
  delay(130);
  noTone(PIN_BUZZER);
}

void suaraManja() {
  int nada[] = {NOTE_E5, NOTE_G5, NOTE_A5, NOTE_C6};
  for (int i = 0; i < 4; i++) {
    tone(PIN_BUZZER, nada[i], 70);
    delay(80);
  }
  noTone(PIN_BUZZER);
}

void suaraCilukba() {
  tone(PIN_BUZZER, NOTE_G4, 80);
  delay(90);
  tone(PIN_BUZZER, NOTE_C5, 80);
  delay(90);
  tone(PIN_BUZZER, NOTE_E5, 150);
  delay(160);
  noTone(PIN_BUZZER);
}

void suaraKaget() {
  tone(PIN_BUZZER, 1900, 70);
  delay(80);
  tone(PIN_BUZZER, 2400, 110);
  delay(120);
  noTone(PIN_BUZZER);
}

void suaraAlarmGas() {
  tone(PIN_BUZZER, 2600, 120);
  delay(130);
  tone(PIN_BUZZER, 1400, 120);
  delay(130);
  noTone(PIN_BUZZER);
}

// Lagu Super Mario Bros
void nyanyiLaguSeru() {
  // Daftar nada (0 = jeda istirahat)
  int melodi[] = {
    // Intro
    NOTE_E5, NOTE_E5, 0, NOTE_E5, 0, NOTE_C5, NOTE_E5, NOTE_G5, 0, NOTE_G4, 0,
    // Bait 1
    NOTE_C5, 0, NOTE_G4, 0, NOTE_E4, 0, NOTE_A4, NOTE_B4, NOTE_AS4, NOTE_A4,
    NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_G5, 0, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_B4, 0,
    // Bait 2 (Pengulangan)
    NOTE_C5, 0, NOTE_G4, 0, NOTE_E4, 0, NOTE_A4, NOTE_B4, NOTE_AS4, NOTE_A4,
    NOTE_G4, NOTE_E5, NOTE_G5, NOTE_A5, NOTE_F5, NOTE_G5, 0, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_B4, 0,
    // Penutup: Efek Suara Koin Mario!
    NOTE_B5, NOTE_E6
  };

  // Panjang ketukan tiap nada (1 = 135 ms)
  int ketukan[] = {
    // Intro
    1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2,
    // Bait 1
    2, 1, 2, 1, 2, 1, 2, 2, 1, 2,
    1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1,
    // Bait 2
    2, 1, 2, 1, 2, 1, 2, 2, 1, 2,
    1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1,
    // Penutup Koin
    1, 4
  };

  int jumlahNada = sizeof(melodi) / sizeof(melodi[0]);
  const int TEMPO_MS = 135; 

  for (int i = 0; i < jumlahNada; i++) {
    unsigned long mulaiKetukan = millis();
    int totalDurasi = ketukan[i] * TEMPO_MS;

    // 1. Bunyikan nada di latar belakang terlebih dahulu agar tempo tidak terganggu OLED
    if (melodi[i] > 0) {
      // Bunyi dibuat 82% dari total durasi agar ada jeda putus-putus (staccato) yang jelas
      tone(PIN_BUZZER, melodi[i], totalDurasi * 0.82);
    } else {
      noTone(PIN_BUZZER);
    }

    // 2. Gambar animasi Mochi bernyanyi di OLED
    display.clearDisplay();
    int goyang = (i % 2 == 0) ? -3 : 3;

    // Mata senang bergoyang
    display.fillCircle(41 + goyang, 25, 12, WHITE);
    display.fillRect(27 + goyang, 25, 28, 14, BLACK);
    display.fillCircle(87 + goyang, 25, 12, WHITE);
    display.fillRect(73 + goyang, 25, 28, 14, BLACK);

    // Mulut & Not Balok bergerak mengikuti ketukan nada
    if (melodi[i] > 0) {
      int ukuranMulut = (melodi[i] >= NOTE_G5) ? 7 : 5; // Mulut lebih lebar saat nada tinggi
      display.fillCircle(64, 37, ukuranMulut, WHITE);

      // Not balok kiri & kanan
      int naikTurun = (i % 3) * 3;
      display.fillCircle(12, 16 + naikTurun, 3, WHITE);
      display.drawLine(15, 16 + naikTurun, 15, 6 + naikTurun, WHITE);
      display.drawLine(15, 6 + naikTurun, 19, 8 + naikTurun, WHITE);

      display.fillCircle(112, 20 - naikTurun, 3, WHITE);
      display.drawLine(115, 20 - naikTurun, 115, 10 - naikTurun, WHITE);
      display.drawLine(115, 10 - naikTurun, 119, 12 - naikTurun, WHITE);
    } else {
      display.fillRect(58, 36, 12, 3, WHITE); // Mulut menutup saat jeda
    }

    display.setTextSize(1);
    display.setTextColor(WHITE);
    if (i >= jumlahNada - 2) {
      display.setCursor(26, 54);
      display.println("TING-TING! KOIN!");
    } else {
      display.setCursor(14, 54);
      display.println("MARIO TIME~ LA LA!");
    }
    display.display();

    // 3. Tunggu sisa waktu ketukan secara presisi
    while (millis() - mulaiKetukan < (unsigned long)totalDurasi) {
      delay(5);
    }
  }

  noTone(PIN_BUZZER);
}

// Gambar Kue Ulang Tahun di OLED
void gambarKueUltah(bool apiMenyala, String teksBawah) {
  display.clearDisplay();

  display.fillRoundRect(36, 34, 56, 14, 3, WHITE);
  display.drawLine(36, 40, 92, 40, BLACK);
  display.fillRoundRect(46, 24, 36, 10, 2, WHITE);
  display.fillRect(62, 14, 4, 10, WHITE);

  if (apiMenyala) {
    display.fillCircle(64, 10, 3, WHITE);
    display.fillTriangle(61, 10, 67, 10, 64, 4, WHITE);
  } else {
    display.drawLine(64, 12, 61, 7, WHITE);
    display.drawLine(61, 7, 66, 3, WHITE);
  }

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 54);
  display.println(teksBawah);
  display.display();
}

// Mode Ulang Tahun Lengkap + Interaksi Tiup Lilin!
void rayakanUlangTahun() {
  int melodiUltah[] = {
    NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_F4, NOTE_E4,
    NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, NOTE_G4, NOTE_F4,
    NOTE_C4, NOTE_C4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_E4, NOTE_D4,
    NOTE_AS4, NOTE_AS4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_F4
  };

  int durasiUltah[] = {
    200, 200, 400, 400, 400, 750,
    200, 200, 400, 400, 400, 750,
    200, 200, 400, 400, 400, 400, 750,
    200, 200, 400, 400, 400, 850
  };

  Serial.println("[MOCHI] Selamat Ulang Tahun! Nyanyi dulu ya...");

  for (int i = 0; i < 25; i++) {
    unsigned long mulai = millis();
    tone(PIN_BUZZER, melodiUltah[i], durasiUltah[i] * 0.85);
    gambarKueUltah(true, "HAPPY BIRTHDAY TO YOU!");
    while (millis() - mulai < (unsigned long)durasiUltah[i]) {
      delay(5);
    }
  }
  noTone(PIN_BUZZER);

  Serial.println("[MOCHI] Sekarang TIUP LILINNYA! (Dekatkan tangan ke sensor < 12 cm)");
  gambarKueUltah(true, "TIUP LILIN! (<12 cm)");

  unsigned long mulaiTunggu = millis();
  while (millis() - mulaiTunggu < 8000) {
    if (bacaJarakCm() < 12) {
      break;
    }
    delay(50);
  }

  gambarKueUltah(false, "WISH GRANTED! YEAY!");
  Serial.println("[MOCHI] Hore! Lilin padam, semoga panjang umur & sukses!");

  int fanfare[] = {NOTE_C5, NOTE_E5, NOTE_G5, NOTE_C6};
  for (int i = 0; i < 4; i++) {
    tone(PIN_BUZZER, fanfare[i], 120);
    delay(140);
  }
  noTone(PIN_BUZZER);
  delay(1500);
}

void animasiMakan() {
  for (int i = 0; i < 4; i++) {
    display.clearDisplay();
    display.fillCircle(41, 26, 11, WHITE);
    display.fillRect(28, 26, 26, 13, BLACK);
    display.fillCircle(87, 26, 11, WHITE);
    display.fillRect(74, 26, 26, 13, BLACK);

    if (i % 2 == 0) {
      display.fillCircle(64, 38, 6, WHITE);
      tone(PIN_BUZZER, 900, 60);
    } else {
      display.fillRect(56, 37, 16, 3, WHITE);
      tone(PIN_BUZZER, 1200, 60);
    }

    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(14, 54);
    display.println("NYAM! ENERGI NAIK!");
    display.display();
    delay(220);
  }
  noTone(PIN_BUZZER);
}

// 4. FUNGSI INTERAKSI SERIAL MONITOR & MINI-GAME

void cekPerintahSerial() {
  if (Serial.available() > 0) {
    String perintah = Serial.readStringUntil('\n');
    perintah.trim();
    perintah.toLowerCase();

    waktuTerakhirInteraksi = millis();

    if (sedangMainTebak) {
      int tebakan = perintah.toInt();
      if (tebakan < 1 || tebakan > 100) {
        Serial.println("[GAME] Masukkan angka 1 sampai 100 ya!");
        return;
      }

      if (tebakan == angkaRahasia) {
        sedangMainTebak = false;
        tingkatEnergi = min(100, tingkatEnergi + 15);
        Serial.printf("[GAME] BENAR! Angkanya %d! Energi Mochi +15%%\n", angkaRahasia);
        wajahSenang("TEBAKAN KAMU BENAR!");
        suaraManja();
        delay(1200);
      } else {
        Serial.printf("[GAME] Salah! Tebakanmu %s dari angka Mochi. Coba lagi (1-100):\n",
                      (tebakan > angkaRahasia) ? "TERLALU BESAR" : "TERLALU KECIL");
        suaraKaget();
      }
      return;
    }

    if (perintah == "makan") {
      tingkatEnergi = min(100, tingkatEnergi + 25);
      Serial.printf("[MOCHI] Makasih! Energi sekarang: %d%%\n", tingkatEnergi);
      animasiMakan();
    } 
    else if (perintah == "nyanyi") {
      Serial.println("[MOCHI] Konser dimulai! Super Mario Theme~");
      nyanyiLaguSeru();
    } 
    else if (perintah == "ultah") {
      rayakanUlangTahun();
    }
    else if (perintah == "tebak") {
      sedangMainTebak = true;
      angkaRahasia = random(1, 101);
      Serial.println("[GAME] Mochi memikirkan angka 1 sampai 100. Coba tebak!");
      wajahSenang("TEBAK ANGKA 1 - 100!");
      suaraSapa();
    }
    else if (perintah == "status") {
      Serial.printf("[STATUS] Mood: %s | Energi: %d%% | Jarak: %d cm | Gas: %d\n",
                    statusSekarang.c_str(), tingkatEnergi, bacaJarakCm(), bacaKadarGas());
    } 
    else {
      Serial.println("Ketik: 'makan', 'nyanyi', 'ultah', 'tebak', atau 'status'");
    }
  }
}

// PROGRAM UTAMA (SETUP & LOOP)

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));

  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED gagal terdeteksi!");
    while (true);
  }

  Serial.println("==========================================");
  Serial.println("     ROBOT MOCHI INTERAKTIF SIAP!         ");
  Serial.println("Ketik perintah di Serial Monitor:");
  Serial.println(" - makan  : Beri makan Mochi");
  Serial.println(" - nyanyi : Mochi nyanyi lagu Mario Bros");
  Serial.println(" - ultah  : Rayakan ulang tahun + tiup lilin");
  Serial.println(" - tebak  : Main tebak angka 1-100");
  Serial.println(" - status : Cek data sensor & energi");
  Serial.println("==========================================");

  wajahNormal(0, false);
  suaraSapa();
  waktuTerakhirInteraksi = millis();
  waktuKurangEnergi = millis();
}

void loop() {
  unsigned long waktuSekarang = millis();

  cekPerintahSerial();
  if (sedangMainTebak) return;

  if (waktuSekarang - waktuKurangEnergi > 10000) {
    waktuKurangEnergi = waktuSekarang;
    if (tingkatEnergi > 10) tingkatEnergi -= 2;
  }

  int jarak = bacaJarakCm();
  int gas   = bacaKadarGas();

  // PRIORITAS 1: Bahaya Gas
  if (gas > BATAS_GAS_BAHAYA) {
    statusSekarang = "GAS";
    sedangDidekati = false;
    sempatDekatSekali = false;
    waktuTerakhirInteraksi = waktuSekarang;
    wajahPusingGas();
    suaraAlarmGas();
    return;
  }

  // PRIORITAS 2: Objek Sangat Dekat (< 10 cm)
  if (jarak < 10) {
    sedangDidekati = false;
    waktuTerakhirInteraksi = waktuSekarang;

    if (!sempatDekatSekali) {
      sempatDekatSekali = true;
      waktuMulaiDekatSekali = waktuSekarang;
      statusSekarang = "KAGET";
      wajahKaget();
      suaraKaget();
    }
  }
  // PRIORITAS 3: Interaksi Dekat (10 - 35 cm)
  else if (jarak >= 10 && jarak <= 35) {
    sempatDekatSekali = false;
    waktuTerakhirInteraksi = waktuSekarang;

    if (!sedangDidekati) {
      sedangDidekati = true;
      waktuMulaiDidekati = waktuSekarang;
      statusSekarang = "SENANG";
      wajahSenang("HALO TEMAN BARU!");
      suaraSapa();
    } 
    else if (waktuSekarang - waktuMulaiDidekati > 2500 && statusSekarang != "MANJA") {
      statusSekarang = "MANJA";
      wajahManja();
      suaraManja();
    }
  }
  // PRIORITAS 4: Tidak Ada Objek (> 35 cm)
  else {
    sedangDidekati = false;

    if (sempatDekatSekali) {
      sempatDekatSekali = false;
      if (waktuSekarang - waktuMulaiDekatSekali < 1200) {
        statusSekarang = "CILUKBA";
        wajahCilukba();
        suaraCilukba();
        delay(1200);
        return;
      }
    }

    if (tingkatEnergi <= 25) {
      if (statusSekarang != "LAPAR") {
        statusSekarang = "LAPAR";
        wajahLapar();
      }
    }
    else if (waktuSekarang - waktuTerakhirInteraksi > 15000) {
      if (statusSekarang != "NGANTUK") {
        statusSekarang = "NGANTUK";
        wajahNormal(0, true);
        display.setCursor(100, 10);
        display.println("zZz");
        display.display();
      }
    } 
    else {
      statusSekarang = "NORMAL";
      if (waktuSekarang - waktuAnimasiIdle > 2000) {
        waktuAnimasiIdle = waktuSekarang;
        int aksi = random(0, 4);
        if (aksi == 0) {
          wajahNormal(arahLirik, true);
          delay(120);
          wajahNormal(arahLirik, false);
        } else if (aksi == 1) {
          arahLirik = -6;
          wajahNormal(arahLirik, false);
        } else if (aksi == 2) {
          arahLirik = 6;
          wajahNormal(arahLirik, false);
        } else {
          arahLirik = 0;
          wajahNormal(arahLirik, false);
        }
      }
    }
  }

  delay(50);
}