#Buatlah sebuah program yang yang memiliki 3 variabel Robot(str), Jarak(float), dan baterai(int). 3 varibel diinputkan oleh pengguna. kondisi:
#Jika baterai < 20 cetak “baterai hampir habis, perlu dilakukan pengecesan”
#Jika baterai 100 cetak “baterai full, robot siap bergerak sejauh (nilai jarak) meter”
#Jika baterai 20-99 “Baterai aman (nilai baterai)% dan siap bergerak sejauh (nilai jarak) 

robot = input("Masukan nama robot: ")
jarak = float(input("Masukan jarak yang ditempuh: "))
baterai = int(input("Masukan persentase baterai: "))

print(f"Robot {robot} siap bergerak sejauh {jarak} meter dengan baterai {baterai}%")

if baterai < 20:
    print("baterai hampir habis, perlu dilakukan pengecesan")
elif baterai == 100:
    print(f"baterai full, robot {robot} siap bergerak sejauh {jarak} meter")
else:
    print(f"Baterai aman {baterai}% dan siap bergerak sejauh {jarak} meter")