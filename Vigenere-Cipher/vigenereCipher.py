def enkripsi(text, key):
    k = 0
    output = ""
    for i in range(len(text)):
        if (text[i].isupper()):
            output += chr((((ord(text[i])-65)+(ord(key[k])-65)) % 26)+65)
            k = k+1
        elif (text[i].islower()):
            output += chr((((ord(text[i])-97)+(ord(key[k])-97)) % 26)+97)
            k = k+1
        else:
            output += " "

    return output


def dekripsi(text, key):
    k = 0
    output = ""
    for i in range(len(text)):
        if (text[i].isupper()):
            output += chr((((ord(text[i])-65)-(ord(key[k])-65)) % 26)+65)
            k = k+1
        elif (text[i].islower()):
            output += chr((((ord(text[i])-97)-(ord(key[k])-97)) % 26)+97)
            k = k+1
        else:
            output += " "

    return output


def generateKey(text, key):
    newKey = key

    while (len(newKey) < len(text)):
        newKey += key

    if (len(newKey) > len(text)):
        n = len(text) - len(newKey)
        newKey = newKey[0:n]

    return newKey


# ========================================================================
# plaintext = ""
ciphertext = ""
key = ""

plaintext = input("\nMasukkan Text\t: ")
key = input("Masukkan Key\t: ")
ciphertext = enkripsi(plaintext, generateKey(plaintext, key))
print("\n\nENKRIPSI")
print("Ciphertext : ", ciphertext)
print("\n\nDEKRIPSI")
print("Plaintext :", dekripsi(ciphertext, generateKey(ciphertext, key)))
