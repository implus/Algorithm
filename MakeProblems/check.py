

import os
checkTitle = 'implus_check'

os.system('g++ ' + checkTitle + '.cpp -o check')

lst = os.listdir('./')
for f in lst:
	w = f.split('.')
	if(len(w) < 2):
		continue
	if w[1] == 'in':
		os.system('time ./check < ' + f + ' > ' + w[0] + '_check.out')
		os.system('diff ' + w[0] + '.out ' + w[0] + '_check.out')
		os.system('rm ' + w[0] + '_check.out')
os.system('rm -f check')


