robot = input("Masukkan nama robot : ")
jarak = float(input("Masukkan jarak : "))
baterai = int(input("Masukkan baterai : "))

if (baterai < 20):
    print("baterai hampir habis, perlu dilakukan pengecesan")
elif (baterai == 100):
    print(f"baterai full, robot siap bergerak sejauh {jarak} meter")
elif (baterai >= 20 - baterai <= 99):
    print(f"Baterai aman {baterai}% dan siap bergerak sejauh {jarak} meter")
else:
    print("Robot tidak bisa bergerak")