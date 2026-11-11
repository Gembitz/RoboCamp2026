robot = input("Nama Robot: ")
jarak = float(input("Masukan jarak: "))
baterai = int(input("Masukan baterai: "))

if baterai < 20:
    print("baterai hampir habis, perlu dilakukan pengisian ulang")

elif baterai == 100:
    print(f"baterai penuh, robot siap bergerak sejauh {jarak} meter")

else:
    print(f"baterai aman {baterai}% dan siap bergerak sejauh {jarak} meter")
