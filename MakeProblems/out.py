originalTitle = 'number_count'
title = "easy_count"

#init name
import os
os.system('mv ' + originalTitle + '_description.txt ' + title + '_description.txt')
os.system('mv ' + originalTitle + '_solution.txt ' + title + '_solution.txt')
os.system('mv ' + originalTitle + '_gendata.cpp ' + title + '_gendata.cpp')
os.system('mv ' + originalTitle + '.cpp ' + title + '.cpp')


#gen .in && .out
os.system("g++ " + title + "_gendata.cpp -o gen")
os.system("./gen")
os.system("rm -f gen")


os.system("g++ " + title + ".cpp -o gao")
lst = os.listdir('./')
for f in lst:
	w = f.split('.')
	if(len(w) < 2):
		continue
	if w[1] == 'in':
		os.system("time ./gao < " + f + " > " + w[0] + ".out")
		os.system('mvim ' + w[0] + '.out')
os.system("rm -f gao")


#excel operation
import xlrd
import xlwt
wb = xlwt.Workbook()
ws = wb.add_sheet('sheet 1')

col = 0
row = 0
lst = os.listdir('./')
caseNum = 1
for f in lst:
	w = f.split('.')
	if(len(w) < 2):
		continue
	if w[1] == 'in':
		ww = w[0].split('_')
		sz = len(ww)
		if int(ww[sz - 1]) > caseNum:
			caseNum = int(ww[sz - 1])
	
gendata = open(title + '_gendata.cpp')
context = gendata.read()
gendata.close()
lis = []

ct = context.split('//')
flag = 0
for a in ct:
	if flag == 0:
		flag = 1
		continue
	b = a.split('\n')
	lis.append(b[0].decode('utf-8'))

for i in lis:
	print i

for i in range(1, caseNum + 1):

	row = i - 1

	value = title + '_' + str(i)
	ws.write(i, 0, value)

	value = title + '_' + str(i) + '.in'
	ws.write(i, 1, value)

	value = title + '_' + str(i) + '.out' 
	ws.write(i, 2, value)

	value = lis[i - 1]
	ws.write(i, 3, value)

row = caseNum + 2
col = 0

# line number
cpp = open(title + '.cpp')
cppv = cpp.read()
cpp.close()
cppn = len(cppv.split('\n'))
cppn = (cppn + 9) / 10 * 10
ws.write(row, col, str(cppn))
col = col + 1

#time
tmp = open(title + '_description.txt')
des = tmp.read()
timelimit = des.split('[Time-limit]')
time = ''
if( len(timelimit) > 1 ):
	time = (int) (timelimit[1].split(' ')[0])
	time = time / 1000
ws.write(row, col, str(time))
col = col + 1

#memory
memorylimit = des.split('[Memory-limit]')
memory = ''
if( len(memorylimit) > 1 ):
	memory = (int) (memorylimit[1].split(' ')[0])
	memory = memory / 1000
ws.write(row, col, str(memory))
col = col + 1

#description
description = des.split('[Description]')
d = ''
if( len(description) > 1 ):
	d = description[1].split('[/Description]')[0]
	d = d.decode('utf-8')
ws.write(row, col, d)
col = col + 1

#input
x = des.split('[Input]')
y = ''
if( len(x) > 1 ):
	y = x[1].split('[/Input]')[0]
	y = y.decode('utf-8')
ws.write(row, col, y)
col = col + 1

#output
x = des.split('[Output]')
y = ''
if( len(x) > 1 ):
	y = x[1].split('[/Output]')[0]
	y = y.decode('utf-8')
ws.write(row, col, y)
col = col + 1


#sample input
x = des.split('[Sample-input]')
y = ''
if( len(x) > 1 ):
	y = x[1].split('[/Sample-input]')[0]
	y = y.decode('utf-8')
ws.write(row, col, y)
col = col + 1

#sample output
x = des.split('[Sample-output]')
y = ''
if( len(x) > 1 ):
	y = x[1].split('[/Sample-output]')[0]
	y = y.decode('utf-8')
ws.write(row, col, y)
col = col + 1


#hint
x = des.split('[Hint]')
y = ''
if( len(x) > 1 ):
	y = x[1].split('[/Hint]')[0]
	y = y.decode('utf-8')
ws.write(row, col, y)
col = col + 1

#C++
ws.write(row, col, "C++")
col = col + 1

#solution
answer = open(title + '_solution.txt')
sol = answer.read()
sol = sol.decode('utf-8')
answer.close()
ws.write(row, col, sol)
col = col + 1


wb.save('tmp.xls')




