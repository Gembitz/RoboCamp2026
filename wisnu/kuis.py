robot = input("Masukan nama robot: ")
jarak = float(input("Masukan jarak yang akan ditempuh (dalam meter): "))
baterai = int(input("Masukan persentase baterai robot (0-100): "))

if baterai < 20:
    print("Baterai hampir habis, perlu dilakukan pengecesan")
elif baterai == 100:
    print(f"Baterai full, robot siap bergerak sejauh {jarak} meter")
else:
    print(f"Baterai aman {baterai}% dan siap bergerak sejauh {jarak} meter")
