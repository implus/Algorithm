first = """
3
0 0
0 1
1 0
3
1 0
1 1
0 1

3
0 0
0 1
1 0
3
2 0
2 1
1 1

3
0 0 
0 1
1 0
3
1 0
2 0
2 1

3
0 0
0 1
1 0
3
1 -1
2 0
1 1
"""
import random
maxn = 100000
Tbig = 16

smaxn = 1000
Tsmall = 500

def ran(st, end):
  return random.randint(st, end) 

def gao(fx, fy, n, dx):
  dy = 0
  for i in range(0, n):
    print fx, fy
    fx = fx + dx
    fy = fy + dy
    dy = dy + 1



print first
for t in range(0,Tbig):
  n = maxn
  print n
  gao(ran(0,maxn), ran(0,maxn), n, ran(0,10))
  print n
  gao(ran(0,maxn), ran(0,maxn), n, ran(0,10))

for t in range(0, Tsmall):
  #n = ran(3, smaxn);
  n = smaxn;
  print n
  gao(ran(0,smaxn), ran(0,smaxn), n, ran(0,10))
  print n
  gao(ran(0,smaxn), ran(0,smaxn), n, ran(0,10))

