from random import randint
x = chr(48 + randint(1,9))
for i in range(456789):
    x += chr(48 + randint(0, 9))
x=int(x)
print(x)
print(x*x)
