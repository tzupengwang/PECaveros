import sys
cnt = 0
for line in sys.stdin:
  cnt += len(line.strip().split())
print(cnt)
