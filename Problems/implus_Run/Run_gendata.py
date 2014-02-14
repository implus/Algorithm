first="""2 3
1 1
2 3
1 0
0 1
1 1"""
import random

def ran(st, end):
  return random.randint(st, end)

n = 100000
m = 100000
maxx = 10000000
maxy = 10000000

print first
for t in range(0, 10):
  print n, m
  for i in range(0, n):
    print ran(1, maxx), ran(1, maxy)
  for i in range(0, m):
    print ran(-maxx, maxx), ran(-maxy, maxy)


n = 1000
m = 1000
for t in range(0, 500):
  print n, m
  for i in range(0, n):
    print ran(1, maxx), ran(1, maxy)
  for i in range(0, m):
    print ran(-maxx, maxx), ran(-maxy, maxy)
