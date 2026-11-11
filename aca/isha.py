#nama : isha
#program study: innformatika
# tipe variable

print("hello word")

namasaya = input("masukan nama anda :") 
nama_kamu = int(input("masukan umur : "))
tinggisaya = float(input ("masukan tinggi :"))

print("perkenalkan nama saya" + namasaya + "umur kamu" + str(nama_kamu) + "tinggi saya" + str(tinggisaya))

print(f"perkenalkan nama saya {namasaya} umur saya {nama_kamu} tinggi saya {tinggisaya}")

#kondisi percbangan
#KISI 

angka1 = int(input("masukan angka"))
angka2 = int(input("masukan angka"))

if (angka1 > angka2):
    print(f"Angka {angka1} lebih besar dari pada angka {angka2}") ;
elif (angka1 == angka2):
    print(f"angka {angka1} sama dengan {angka2}")
    
else :
    print(f"angka {angka2} lebih besar dari pada {angka1}");

