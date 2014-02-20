first = """3 3 2
0 1 0
1 0 0
0 0 0

3 3 1
0 1 0
1 0 0
0 0 0

4 4 2
0 1 0 0
1 1 0 1
0 0 1 1
0 1 1 0

4 4 2
0 1 0 0
1 1 0 1
0 0 1 1
0 1 0 0
"""

import random
def ran(st, end):
  return random.randint(st, end);


for t in range(0, 4):
  n = ran(990, 1000)
  m = ran(990, 1000)
  k = ran(100, 1000)
  flag = ran(0, 1)
  print n, m, k
  for i in range(0, n):
    for j in range(0, m):
      if flag:
        print 0,
      else:
        print 1,
      #print ran(0, 1),
    print ""

for t in range(0, 10):
  n = ran(990, 1000)
  m = ran(990, 1000)
  k = ran(100, 1000)
  print n, m, k
  for i in range(0, n):
    for j in range(0, m):
      if ran(0, 100) < 5:
        print 1,
      else:
        print 0,
      #print ran(0, 1),
    print ""


for t in range(0, 30):
  n = ran(100, 200)
  m = ran(100, 200)
  k = ran(100, 200)
  print n, m, k
  for i in range(0, n):
    for j in range(0, m):
      if ran(0, 100) < 10:
        print 1,
      else:
        print 0,
      #print ran(0, 1),
    print ""

for t in range(0, 30):
  n = ran(100, 200)
  m = ran(100, 200)
  k = ran(0, 1000)
  print n, m, k
  for i in range(0, n):
    for j in range(0, m):
      if ran(0, 100) < 10:
        print 1,
      else:
        print 0,
      #print ran(0, 1),
    print ""


for t in range(0, 30):
  n = ran(100, 200)
  m = ran(100, 200)
  k = ran(100, 200)
  print n, m, k
  for i in range(0, n):
    for j in range(0, m):
      print ran(0, 1),
    print ""

for t in range(0, 10):
  n = ran(100, 200)
  m = ran(100, 200)
  k = ran(0, 1000)
  print n, m, k
  for i in range(0, n):
    for j in range(0, m):
      if ran(0, 100) > 10:
        print 1,
      else:
        print 0,
    print ""



  n = ran(990, 1000)
  m = ran(990, 1000)
  k = ran(100, 1000)

