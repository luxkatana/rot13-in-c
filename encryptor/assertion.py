
def rot13(input_string: str) -> str:
    rot13_charset = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm"
    alphabet_charset = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'
    result: str = ''
    for character in input_string:
        if character in "!\"#$%&'()*+,-./:;<=>?@[\]^_`{|}~ \t\n0123456789":
            result += character
        elif alphabet_charset.find(character) != -1:
            result += rot13_charset[alphabet_charset.find(character)]
        
    return result

with open("./result.txt", 'r') as file:
    output = file.read().rstrip()
with open("./test", 'r') as file:
    expected = rot13(file.read())

if expected.rstrip() != output.rstrip():
    print("./result.txt is not the same as ./test")
else:
    print("OK")
    