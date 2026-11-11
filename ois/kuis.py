#nama : kholishid dzihni khasyiyona
#npm:26670024

#kuiz1

nama = "robot"
jarak = float(input("masukan jarak"))
baterai = int(input("masukan baterai"))

if (baterai < 20):
    print("baterai hampir habis  : " + str(baterai))
elif (baterai == 100):
    print(f"baterai full {baterai}% dan siap dijalankan {jarak}m  ")
else :
    print(f"baterai masih aman {baterai}% dan siap dijalankan {jarak}m ")      





