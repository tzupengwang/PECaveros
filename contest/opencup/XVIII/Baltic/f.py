print('if head == nil { } else {')
print('if head #next == nil { } else {')

def merge(s1, s2, s3):
  ret = """
if %s == %s { }
else {
  if %s == %s { }
  else {
    now = %s
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
""" % (s1, s2, s2, s3, s1, s1, s2, s2, s3, s3, s3)
  return ret


def LIS(ptr):
  ret = """
loop {
  if %s #next == nil {
    break
  } else {
    if %s #next #value < %s #value {
      break
    } else {
      %s = %s #next
    }
  }
}""" % (ptr, ptr, ptr, ptr, ptr)
  return ret

s = """
ptr1 = head #next
%s
if ptr1 #next == nil {
} else {
  ptr2 = ptr1 #next
  %s
  %s
  loop {
    if ptr2 #next == nil {
      break
    } else {
      ptr3 = ptr2 #next
      %s
      if ptr3 #next == nil {
        break
      } else { }
      ptr4 = ptr3 #next
      %s
      %s
      ptr2 = ptr4
    }
  }
}
""" % (LIS("ptr1"), LIS("ptr2"), merge("head", "ptr1", "ptr2"),LIS("ptr3"), LIS("ptr4"), merge("ptr2", "ptr3", "ptr4"))
for i in range(18):
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
