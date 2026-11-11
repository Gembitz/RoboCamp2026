nama = str(input("Masukan nama anda : "))
npm = int(input("Masukkan npm anda : "))

if npm <= 270000000:
    print(f"Selamat {nama} berhasil menyelesaikan challange")
else:
    print("Yah, kamu masih gagal dengan ID: " + npm)