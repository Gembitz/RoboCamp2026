NamaRobot = str(input("Masukkan nama robot anda : "))
Jarak = float(input("Masukkan jarak yang ingin ditempuh : "))
Baterai = int(input("Masukkan baterai robot : "))

if Baterai < 20:
    print("baterai hampir habis, perlu dilakukan pengecesan")
elif Baterai == 100:
    print(f"baterai full, robot siap bergerak sejauh {Jarak} meter")
elif Baterai >= 20 - Baterai <= 99:
    print(f"Baterai aman {Baterai}% dan siap bergerak sejauh {Jarak} meter")
else:
    print("Baterai mbledos kang")

