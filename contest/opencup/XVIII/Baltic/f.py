K = 38
print('if head == nil { } else {')
print('if head #next == nil { } else {')
for i in range(K):
  print('var%d = head' % (i))
print('loop {')
for i in range(K-1):
  print('  if var%d #next == nil {' % (K - 1))
  print('    break')
  print('  } else {')
  print('    var%d = var%d #next' % (K-1, K-1))
  print('  }')
for i in range(K-1):
    s = i
    while s >= 10:
      print(('  var%d = var%d' % (i, i)) + (' #next' * 10))
      s -= 10
    if s > 0:
      print(('  var%d = var%d' % (i, i)) + (' #next' * s))
print('}')
for i in range(K-1):
  start = "var%d" % (i)
  end   = "var%d" % (i + 1)
  s = """if %s == %s { }
else {
  i = %s
  loop {
    if i #next == %s {
      break
    } else {
      j = i
      loop {
        if j #next == %s {
          break
        } else {
          tmp = j #next #next
          if tmp #value < j #next #value {
            j #next #next = tmp #next
            tmp #next = j #next
            j #next = tmp
          } else { }
          j = j #next
        }
      }
      i = i #next
    }
  }
}""" % (start, end, start, end, end)
  print(s)
for i in range(1, K-1):
  s1 = "var%d" % (0)
  s2 = "var%d" % (i)
  s3 = "var%d" % (i + 1)
  s = """
if %s == %s { }
else {
  if %s == %s { }
  else {
    now = head
    p1 = %s #next
    e1 = %s
    p2 = %s #next
    e2 = %s
    nxt = %s #next
    e1 #next = nil
    e2 #next = nil
    loop {
      if p1 == nil {
        if p2 == nil {
          break
        } else {
          now #next = p2
          now = now #next
          p2 = p2 #next
        }
      } else {
        if p2 == nil {
          now #next = p1
          now = now #next
          p1 = p1 #next
        } else {
          if p2 #value < p1 #value {
            now #next = p2
            now = now #next
            p2 = p2 #next
          } else {
            now #next = p1
            now = now #next
            p1 = p1 #next
          }
        }
      }
    }
    now #next = nxt
    %s = now
  }
}
""" % (s1, s2, s2, s3, s1, s2, s2, s3, s3, s3)
  print(s)
s = """
if head #next == nil { } else {
  if head #next #value < head #value {
    i = head
    head = head #next
    j = head
    loop {
      if j #next == nil {
        j #next = i
        i #next = nil
        break
      } else {
        if j #next #value < i #value {
          j = j #next
        } else {
          i #next = j #next
          j #next = i
          break
        }
      }
    }
  } else { }
}
"""
print(s)
print('} }')
