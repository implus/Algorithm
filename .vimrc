autocmd BufNewFile *.cpp,*.[ch],*.sh,*.java exec ":call SetTitle()" 
""定义函数SetTitle，自动插入文件头 
func SetTitle() 
    "如果文件类型为.sh文件 
    if &filetype == 'sh' 
        call setline(1,"\#########################################################################") 
        call append(line("."), "\# File Name: ".expand("%")) 
        call append(line(".")+1, "\# Author: implus") 
        call append(line(".")+2, "\# mail: 674592809@qq.com") 
        call append(line(".")+3, "\# Created Time: ".strftime("%c")) 
        call append(line(".")+4, "\#########################################################################") 
        call append(line(".")+5, "\#!/bin/bash") 
        call append(line(".")+6, "") 
    else 
        call setline(1, "/*************************************************************************") 
        call append(line("."), "    > File Name: ".expand("%")) 
        call append(line(".")+1, "    > Author: implus") 
        call append(line(".")+2, "    > Mail: 674592809@qq.com") 
        call append(line(".")+3, "    > Created Time: ".strftime("%c")) 
        call append(line(".")+4, " ************************************************************************/") 
        call append(line(".")+5, "")
        call append(line(".")+6, "#include<iostream>")
        call append(line(".")+7, "#include<cstdio>")
        call append(line(".")+8, "#include<cstdlib>")
        call append(line(".")+9, "#include<cstring>")
        call append(line(".")+10, "#include<vector>")
        call append(line(".")+11, "#include<algorithm>")
        call append(line(".")+12, "#include<cmath>")
        call append(line(".")+13, "#include<map>")
		call append(line(".")+14, "#include<string>")
		call append(line(".")+15, "#include<set>")
		call append(line(".")+16, "#include<queue>")
		call append(line(".")+17, "#include<stack>")
        call append(line(".")+18, "using namespace std;")
        call append(line(".")+19, "typedef long long ll;")
        call append(line(".")+20, "typedef pair<int,int> pii;")
        call append(line(".")+21, "#define ls (rt<<1)")
        call append(line(".")+22, "#define rs (rt<<1|1)")
        call append(line(".")+23, "#define lson l,m,ls")
        call append(line(".")+24, "#define rson m+1,r,rs")
        call append(line(".")+25, "")
    endif
    "新建文件后，自动定位到文件末尾
    autocmd BufNewFile * normal G
endfunc 

set nu ci si ai et sw=4 sts=4 ts=4
nmap <F9> :make %< <CR>
nmap <F2> :vs %<.in <CR>
nmap <F5> :!./%< < %<.in <CR>
