if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
inoremap <silent> <Plug>NERDCommenterInsert  <BS>:call NERDComment('i', "insert")
noremap  :bd
map  :copen 
nmap  :FZF 
nmap  :Merginal 
nnoremap 	 :bn
noremap <NL> ==
map  <Plug>(ctrlp)
nnoremap  : call Toggle_transparent()
nmap <silent> ,,0 <Plug>FontsizeDefault
nmap <silent> ,,- <Plug>FontsizeDec
nmap <silent> ,,+ <Plug>FontsizeInc
nmap <silent> ,,= <Plug>FontsizeBegin
nmap ,ca <Plug>NERDCommenterAltDelims
xmap ,cu <Plug>NERDCommenterUncomment
nmap ,cu <Plug>NERDCommenterUncomment
xmap ,cb <Plug>NERDCommenterAlignBoth
nmap ,cb <Plug>NERDCommenterAlignBoth
xmap ,cl <Plug>NERDCommenterAlignLeft
nmap ,cl <Plug>NERDCommenterAlignLeft
nmap ,cA <Plug>NERDCommenterAppend
xmap ,cy <Plug>NERDCommenterYank
nmap ,cy <Plug>NERDCommenterYank
xmap ,cs <Plug>NERDCommenterSexy
nmap ,cs <Plug>NERDCommenterSexy
xmap ,ci <Plug>NERDCommenterInvert
nmap ,ci <Plug>NERDCommenterInvert
nmap ,c$ <Plug>NERDCommenterToEOL
xmap ,cn <Plug>NERDCommenterNested
nmap ,cn <Plug>NERDCommenterNested
xmap ,cm <Plug>NERDCommenterMinimal
nmap ,cm <Plug>NERDCommenterMinimal
xmap ,c  <Plug>NERDCommenterToggle
nmap ,c  <Plug>NERDCommenterToggle
xmap ,cc <Plug>NERDCommenterComment
nmap ,cc <Plug>NERDCommenterComment
nmap ,J :ClangFormatAutoToggle 
nmap ,d :NERDTreeClose 
vmap gx <Plug>NetrwBrowseXVis
nmap gx <Plug>NetrwBrowseX
nnoremap <SNR>86_: :=v:count ? v:count : ''
vnoremap <silent> <Plug>NetrwBrowseXVis :call netrw#BrowseXVis()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#BrowseX(netrw#GX(),netrw#CheckIfRemote(netrw#GX()))
map <C-P> <Plug>(ctrlp)
nnoremap <silent> <Plug>(ctrlp) :CtrlP
noremap <silent> <Plug>BufTabLine.Go(-1) :exe 'b'.get(buftabline#user_buffers(),-1,'')
noremap <silent> <Plug>BufTabLine.Go(10) :exe 'b'.get(buftabline#user_buffers(),9,'')
noremap <silent> <Plug>BufTabLine.Go(9) :exe 'b'.get(buftabline#user_buffers(),8,'')
noremap <silent> <Plug>BufTabLine.Go(8) :exe 'b'.get(buftabline#user_buffers(),7,'')
noremap <silent> <Plug>BufTabLine.Go(7) :exe 'b'.get(buftabline#user_buffers(),6,'')
noremap <silent> <Plug>BufTabLine.Go(6) :exe 'b'.get(buftabline#user_buffers(),5,'')
noremap <silent> <Plug>BufTabLine.Go(5) :exe 'b'.get(buftabline#user_buffers(),4,'')
noremap <silent> <Plug>BufTabLine.Go(4) :exe 'b'.get(buftabline#user_buffers(),3,'')
noremap <silent> <Plug>BufTabLine.Go(3) :exe 'b'.get(buftabline#user_buffers(),2,'')
noremap <silent> <Plug>BufTabLine.Go(2) :exe 'b'.get(buftabline#user_buffers(),1,'')
noremap <silent> <Plug>BufTabLine.Go(1) :exe 'b'.get(buftabline#user_buffers(),0,'')
nnoremap <silent> <SNR>46_quit :call fontsize#quit()
nnoremap <silent> <SNR>46_setDefault :call fontsize#setDefault()
nnoremap <silent> <SNR>46_default :call fontsize#default()
nnoremap <silent> <SNR>46_dec :call fontsize#dec()
nnoremap <silent> <SNR>46_inc :call fontsize#inc()
nnoremap <silent> <SNR>46_begin :call fontsize#begin()
xnoremap <silent> <Plug>NERDCommenterUncomment :call NERDComment("x", "Uncomment")
nnoremap <silent> <Plug>NERDCommenterUncomment :call NERDComment("n", "Uncomment")
xnoremap <silent> <Plug>NERDCommenterAlignBoth :call NERDComment("x", "AlignBoth")
nnoremap <silent> <Plug>NERDCommenterAlignBoth :call NERDComment("n", "AlignBoth")
xnoremap <silent> <Plug>NERDCommenterAlignLeft :call NERDComment("x", "AlignLeft")
nnoremap <silent> <Plug>NERDCommenterAlignLeft :call NERDComment("n", "AlignLeft")
nnoremap <silent> <Plug>NERDCommenterAppend :call NERDComment("n", "Append")
xnoremap <silent> <Plug>NERDCommenterYank :call NERDComment("x", "Yank")
nnoremap <silent> <Plug>NERDCommenterYank :call NERDComment("n", "Yank")
xnoremap <silent> <Plug>NERDCommenterSexy :call NERDComment("x", "Sexy")
nnoremap <silent> <Plug>NERDCommenterSexy :call NERDComment("n", "Sexy")
xnoremap <silent> <Plug>NERDCommenterInvert :call NERDComment("x", "Invert")
nnoremap <silent> <Plug>NERDCommenterInvert :call NERDComment("n", "Invert")
nnoremap <silent> <Plug>NERDCommenterToEOL :call NERDComment("n", "ToEOL")
xnoremap <silent> <Plug>NERDCommenterNested :call NERDComment("x", "Nested")
nnoremap <silent> <Plug>NERDCommenterNested :call NERDComment("n", "Nested")
xnoremap <silent> <Plug>NERDCommenterMinimal :call NERDComment("x", "Minimal")
nnoremap <silent> <Plug>NERDCommenterMinimal :call NERDComment("n", "Minimal")
xnoremap <silent> <Plug>NERDCommenterToggle :call NERDComment("x", "Toggle")
nnoremap <silent> <Plug>NERDCommenterToggle :call NERDComment("n", "Toggle")
xnoremap <silent> <Plug>NERDCommenterComment :call NERDComment("x", "Comment")
nnoremap <silent> <Plug>NERDCommenterComment :call NERDComment("n", "Comment")
nnoremap <C-T> : call Toggle_transparent()
nmap <C-G> :Merginal 
nmap <C-F> :FZF 
nmap <F2> :NERDTree %:h
nmap <F1> :TagbarToggle
noremap <C-J> ==
noremap <C-D> :bd
nnoremap <S-Tab> :bp
map <C-E> :copen 
map <F3> :set list! 
map <F6> :w  :!python % 
map <F7> :w  :!python main.py 
map <F8> :w  :!make  :!./build.o& 
inoremap { {}ki
let &cpo=s:cpo_save
unlet s:cpo_save
set background=dark
set backspace=indent,eol,start
set backupdir=~/.cache/vim/backup//
set directory=~/.cache/vim/swap//
set expandtab
set fileencodings=ucs-bom,utf-8,default,latin1
set guifont=Anonymous\ Pro\ for\ Powerline\ Bold\ 20
set guioptions=agimt
set helplang=fr
set laststatus=2
set listchars=tab:>-,extends:>,precedes:<,space:·
set path=~/Programming/CPP/RogueLikeCPP/**
set ruler
set runtimepath=~/.vim,~/.vim/bundle/Vundle.vim,~/.vim/bundle/vim-airline,~/.vim/bundle/vim-airline-themes,~/.vim/bundle/rainbow,~/.vim/bundle/nerdcommenter,~/.vim/bundle/nerdtree,~/.vim/bundle/vim,~/.vim/bundle/python-syntax,~/.vim/bundle/gruvbox,~/.vim/bundle/molokai,~/.vim/bundle/tagbar,~/.vim/bundle/ctags,~/.vim/bundle/vim-fugitive,~/.vim/bundle/vim-merginal,~/.vim/bundle/nord-vim,~/.vim/bundle/materialbox,~/.vim/bundle/vim-fontsize,~/.vim/bundle/simple-dark,~/.vim/bundle/vim-buftabline,~/.vim/bundle/ctrlp.vim,~/.vim/bundle/fzf,~/.vim/bundle/vim-clang-format,/usr/share/vim/vimfiles,/usr/share/vim/vim82,/usr/share/vim/vimfiles/after,~/.vim/after,~/.vim/bundle/Vundle.vim,~/.vim/bundle/Vundle.vim/after,~/.vim/bundle/vim-airline/after,~/.vim/bundle/vim-airline-themes/after,~/.vim/bundle/rainbow/after,~/.vim/bundle/nerdcommenter/after,~/.vim/bundle/nerdtree/after,~/.vim/bundle/vim/after,~/.vim/bundle/python-syntax/after,~/.vim/bundle/gruvbox/after,~/.vim/bundle/molokai/after,~/.vim/bundle/tagbar/after,~/.vim/bundle/ctags/after,~/.vim/bundle/vim-fugitive/after,~/.vim/bundle/vim-merginal/after,~/.vim/bundle/nord-vim/after,~/.vim/bundle/materialbox/after,~/.vim/bundle/vim-fontsize/after,~/.vim/bundle/simple-dark/after,~/.vim/bundle/vim-buftabline/after,~/.vim/bundle/ctrlp.vim/after,~/.vim/bundle/fzf/after,~/.vim/bundle/vim-clang-format/after
set shiftwidth=4
set showtabline=2
set suffixes=.bak,~,.o,.info,.swp,.aux,.bbl,.blg,.brf,.cb,.dvi,.idx,.ilg,.ind,.inx,.jpg,.log,.out,.png,.toc
set tabline=%!buftabline#render()
set tabstop=4
set timeoutlen=1500
set undodir=~/.cache/vim/undo//
" vim: set ft=vim :
