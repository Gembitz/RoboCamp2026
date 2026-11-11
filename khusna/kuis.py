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
