print ("Tugas membuat Program")

nama_robot = str(input("Masukkan nama robot anda:")) 
nilai_jarak = float(input("Masukkan Jarak:"))
baterai = int(input("Masukkan Baterai:"))

if (baterai <= 20):
    print(f"baterai hampir habis, perlu dilakukan pengecesan ")
elif baterai == 100:
    print(f"baterai full, robot siap bergerak sejauh {nilai_jarak} meter")
elif (baterai >= 20 - baterai <= 99):
    print(f"Baterai aman {baterai} dan siap bergerak sejauh {nilai_jarak} meter")
else:
    print("Baterai tidak aman")
