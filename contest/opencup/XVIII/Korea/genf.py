from random import randint
print(15)
for i in range(15):
    print(' '.join( str(randint(1, 10**9)) for j in range(i+1,16) ))
