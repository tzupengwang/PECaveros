
n, m = 8, 8
for x1 in range(n):
    for y1 in range(m):
        if (x1, y1) == (0, 0):
            continue
        if (x1, y1) == (0, 1):
            continue
        for x2 in range(n):
            for y2 in range(m):
                if (x2, y2) == (0, 0):
                    continue
                if (x2, y2) == (0, 1):
                    continue
                if (x1, y1) == (x2, y2):
                    continue
                for x3 in range(n):
                    for y3 in range(m):
                        if (x3, y3) == (0, 0):
                            continue
                        if (x3, y3) == (0, 1):
                            continue
                        if (x1, y1) == (x3, y3):
                            continue
                        if (x2, y2) == (x3, y3):
                            continue
                        print(n, m)
                        print(x1, y1, x2, y2, x3, y3)
