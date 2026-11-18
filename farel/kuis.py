
robot = input("Masukkan Nama Robot : ")
jarak = float(input("Masukkan Jarak : "))
baterai = int(input("Masukkan jumalah % Baterai Robot : "))

if (baterai < 20):
    print("baterai hampir habis, perlu dilakukan pengecesan")
elif (baterai == 100):
    print(f"baterai full, robot siap bergerak sejauh {jarak} meter")
else:
    print(f"Baterai aman {baterai}% dan siap bergerak sejauh {jarak} meter")