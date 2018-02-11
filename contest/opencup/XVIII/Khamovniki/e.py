n = int(input())

ones = 11

while ones <= n:
    print("%15d %d\n" % (ones, n // ones))
    ones = 10*ones + 1
