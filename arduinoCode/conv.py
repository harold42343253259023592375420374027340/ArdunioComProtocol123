def conv(uletters):
    temp = []
    with open("charset.txt", "r") as f:
        letters = f.read().splitlines()
    for letter in uletters:
        for bit in bin(letters.index(letter))[2:]:
            temp.append(bit)
    return temp

with open("msg.txt","r") as f:
    file = f.read()

val = conv(file)
with open("msg.dat","w") as f:
    f.write(str(val).replace("[","{").replace("]","}").replace("'",""))