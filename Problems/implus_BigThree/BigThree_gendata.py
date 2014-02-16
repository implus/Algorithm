first = """6 3
1 -2 3 4 0 -1
1 2 1 2 1 1
5 1
-2 1
1 0

4 1
-3 6 -1 2
1 2 3 1
1 -1

"""
print first

import random

def ran(st, end):
  return random.randint(st, end)

n = 10
q = 100
for t in range(0, 500):
  print n, q
  for v in range(0, n):
    print ran(-n, n),
  print ""

  for c in range(0, n):
    print ran(1, n + 1),
  print ""

  for i in range(0, q):
    print ran(-n, n), ran(-n, n)
  print ""


n = 100
q = 100
for t in range(0, 500):
  print n, q
  for v in range(0, n):
    print ran(-n, n),
  print ""

  for c in range(0, n):
    print ran(1, n + 1),
  print ""

  for i in range(0, q):
    print ran(-n, n), ran(-n, n)
  print ""

n = 100000
q = 100
for t in range(0, 2):
  print n, q
  for v in range(0, n):
    print ran(-n, n),
  print ""

  for c in range(0, n):
    print ran(1, n + 1),
  print ""

  for i in range(0, q):
    print ran(-n, n), ran(-n, n)
  print ""


n = 10000
q = 100
for t in range(0, 5):
  print n, q
  for v in range(0, n):
    print ran(-n, n),
  print ""

  for c in range(0, n):
    print ran(1, n + 1),
  print ""

  for i in range(0, q):
    print ran(-n, n), ran(-n, n)
  print ""

