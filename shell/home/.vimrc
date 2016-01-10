"***************************************************************
" File Name        : .vimrc
" Author           : skytrails
" Email            : skytrails@163.com
" Create Time      : 2015年09月08日 星期二 06时35分
" Last Modify      : 2015年09月10日 星期四 09时01分
"***************************************************************

set nu
syntax on
"set ai    " eq: set autoindent
set si    " eq: set smartindent
set tabstop=4    " 设置tab键为4个空格
:let mapleader=',' 
nmap <leader>h <c-w>h
nmap <leader>j <c-w>j
nmap <leader>k <c-w>k
nmap <leader>l <c-w>l
"轻松编辑，更新vimrc文件
nmap <leader>e :tabedit $MYVIMRC<cr>
nmap <leader>s :so $MYVIMRC<cr>

imap jj <esc>
"插入文件注释
map <F11> :call AddComment()<cr>

"map =  :call MidComment()<cr>
"map = <esc>g*Nma0i"<esc>$a"<esc>$N
map - <esc>f"j0bbma0x"<esc>$x"<esc>`a
map = :call CommentLine()<cr>
map - <esc>f"j0bbma0x"<esc>$x"<esc>`a
map - :call UnCommentLine()<cr>
""""""""""""""""""""""""""""应用函数""""""""""""""""""""""""""""
function! CommentLine()
    if &filetype == 'vim'
      execute "normal ma0i\"\<esc>$a\""
    endif
endf
function! UnCommentLine()
    let l:f_comtype = 2
    if &filetype == 'vim'
      execute "normal msk$w"
      if getline('.')[col('.')-1] != '"' 
        execute "normal `s"
        return
      elseif getline('.')[col('$')-2] != '"'
        while getline('.')[col('$')-2] == ' '
          execute "normal $x"
        endw
        if getline('.')[col('$')-2] != '"'
          let l:f_comtype = 1   " 1 为单个，2为多个"
        endif
      else
      endif
      while getline('.')[0] == ' '
        execute "normal 0x"
      endw
      if l:f_comtype == 1
        execute "normal k$wx"
        return
      elseif l:f_comtype == 2
        execute "normal k$wx\<esc>$x\<esc>"
        return
      endif
      if getline('.')[col('.')-1] == '"'
         
      else
      endif
    endif
endf
" AddComment "
function! AddComment()
  if &filetype == "cpp" || &filetype == "c"
      if getline(1)[0] == '/'
        return
      endif
      call append(0,"/***************************************************************")
      call append(1,"\" File Name     : ".expand("%"))
      call append(2,"\" Author        : skytrails")
      call append(3,"\" Email         : skytrails@163.com")
      call append(4,"\" Create Time   : ".strftime("%Y-%m-%d %H:%M"))
      call append(5,"***************************************************************/")
  elseif &filetype  == "vim"
      if getline(1)[0] == '"'
        return
      endif
      call append(0,"\"***************************************************************")
      call append(1,"\" File Name     : ".expand("%"))
      call append(2,"\" Author        : skytrails")
      call append(3,"\" Email         : skytrails@163.com")
      call append(4,"\" Create Time   : ".strftime("%Y-%m-%d %H:%M"))
      call append(5,"\"***************************************************************")
  else
  endif
endf

autocmd FileType c,cpp,make,vim :call SetFileEnv()
func! SetFileEnv()
    if &filetype == 'cpp' || &filetype == 'c' || &filetype == 'vim'
      set expandtab
      set cindent shiftwidth=4 " 当行之间交错时使用4个空格
    elseif &filetype == 'make' 
    endif
endf

"debug  vim下设置自定义命令
"command! Debug :so ~/.vimrc

"vim下提交本地$HOME/.vimrc到svn版本库
command! Ci :!svn ci $SVN_VIMRC_FILE
command! Ch :!svn ci $SVN_LOGIN_PATH

