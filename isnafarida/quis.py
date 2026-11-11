#Nama           : isna farida
#program studi  :  informatika

robot = input("Masukan robot anda: ")
jarak = int(input("Masukan jarak robot anda: "))
baterai = float(input("Masukan baterai robot anda: "))

if baterai < 20:
    print("Baterai hampir habis, perlu dilakukan pengecasan")
elif baterai == 100:
    print(f"Baterai full, robot siap bergerak sejauh {jarak} meter")
else:
    print(f"Baterai aman {baterai}% dan siap bergerak sejauh {jarak} meter")

    