def decode_rot13(data: str) -> str:
    result = ''
    rot13_charset = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm"
    alphabet_charset = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'
    symbols = "!\"#$%&'()*+,-./:;<=>?@[\]^_`{|}~ \t\n0123456789"
    for character in data:
        if character in symbols:
            result += character
        elif character in rot13_charset:
            result += alphabet_charset[rot13_charset.find(character)]
    return result
with open("./test", "r") as testfile:
    test_d = decode_rot13(testfile.read())
with open("./result.txt", 'r') as resultfile:
    result = resultfile.read().rstrip("\n")
if result == test_d:
    print("OK")
else:
    print("./test is not the same as ./result.txt")