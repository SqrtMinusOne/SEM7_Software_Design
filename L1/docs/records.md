# Настройка среды
`apt install clang`

## vim
Плагины:
Plug 'octol/vim-cpp-enhanced-highlight'
Plug 'zchee/deoplete-clang'

Настройки:
let g:deoplete#sources#clang#libclang_path = '/usr/lib/llvm-6.0/lib/libclang.so.1'
let g:deoplete#sources#clang#clang_header = '/usr/lib/llvm-6.0/lib/clang/6.0.0/include'

# Библиотеки
## GTest
`apt install libgtest-dev`
`cd /usr/src/googletest/googletest`
`sudo cmake CMakeLists.txt`
`sudo make`
`sudo ln *.a /usr/lib`

