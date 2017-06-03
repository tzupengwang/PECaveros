with open('l.dump') as f:
  for i in f:
    a = i.strip().split()
    print('word[%s]=%s;' % (a[0], a[2]))
