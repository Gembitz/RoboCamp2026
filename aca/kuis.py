#nama: isha
#kuis 1
robot : input
jarak :float
baterai :int

robot =input("masukan nama robot :")
jarak=float(input("masukkan jarak robot :"))
baterai=int(input("masukkan baterai robot :"))


if  (baterai >20 ):
    print("baterai hampir habis,perlu dilakukan pengecesan baterai")
elif (baterai == 100 ):
    print("baterai full, robot siap bergerak sejauh {} (nilai jarak) meter".format(jarak))
else:
    print("Baterai aman ({}%) dan siap bergerak sejauh {} (nilai jarak) meter".format(baterai, jarak))

 