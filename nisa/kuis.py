robot = input("Masukkan nama robot anda: ") 
jarak = float(input("Masukkan jarak: "))
baterai = int(input("Masukkan baterai: "))

if (baterai < 20):
    print(f"baterai hampir habis, perlu dilakukan pengecesan")
elif (baterai == 100):
    print(f"baterai full, robot siap bergerak sejauh {jarak} meter")
else:
    print(f"Baterai aman {baterai}% dan siap bergerak sejauh {jarak} meter")