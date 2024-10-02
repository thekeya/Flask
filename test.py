def encrypt(text,s):
    result = ""

    for i in range(len(text)):
        char = text[i]
        if char == " ":
            result += " "
        elif (char.isupper()):
            result += chr((ord(char) + s-65) % 26 + 65)
        else:
            result += chr((ord(char) + s - 97) % 26 + 97)
    return result

def decrypt(text,s):
    result = ""
    for i in range(len(text)):
        char = text[i]
        if char == " ":
            result += " "
        elif char.isupper():
            result += chr((ord(char) - s -65)%26 + 65)
        else:
            result += chr((ord(char) - s - 97) % 26 + 97)
    return result

text = input("Enter Plain Text:")
s = int(input("Enter Key:"))
print ("Text  : " + text)
print ("Shift : " + str(s))
print ("Cipher: " + encrypt(text,s))
cipher = encrypt(text,s)
print("decryption: "+ decrypt(cipher,s))
