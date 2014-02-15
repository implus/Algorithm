import random

def ran(st, end):
  return random.randint(st, end)

maxx = 100000
minx = -100000
oma = 100
omi = -100
case = 50000

for t in range(0, case):
  o = (ran(omi, oma), ran(omi, oma), ran(omi, oma))
  r = ran(1, 100)
  print o[0], o[1], o[2], r
  mi = -10*r
  ma = 10*r
  for i in range(0, 3):
    while(True):
      p = (o[0] + ran(mi, ma), o[1] + ran(mi, ma), o[2] + ran(mi, ma))
      dx = p[0] - o[0]
      dy = p[1] - o[1]
      dz = p[2] - o[2]
      d = dx*dx + dy*dy + dz*dz
      if(d > r):
        print p[0], p[1], p[2]
        break

for t in range(0, case):
  o = (ran(omi, oma), ran(omi, oma), ran(omi, oma))
  r = ran(1, 100)
  print o[0], o[1], o[2], r
  mi = -100*r
  ma = 100*r
  for i in range(0, 3):
    while(True):
      p = (o[0] + ran(mi, ma), o[1] + ran(mi, ma), o[2] + ran(mi, ma))
      dx = p[0] - o[0]
      dy = p[1] - o[1]
      dz = p[2] - o[2]
      d = dx*dx + dy*dy + dz*dz
      if(d > r):
        print p[0], p[1], p[2]
        break

for t in range(0, case):
  o = (0, 0, 0)
  r = ran(2, 100)
  print o[0], o[1], o[2], r
  print 0, 0, r + ran(1, 10*r)
  print 0, r + ran(1, 10*r), 0
  print r + ran(1, 10*r), 0, 0





