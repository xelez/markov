# Linux

## Сборка на Linux
Нужны: git, cmake, make, GCC

    git clone git clone https://github.com/xelez/markov.git
    cd markov
    mkdir -p build/release
    cd build/release
    cmake -DCMAKE_BUILD_TYPE=Release ../../
    make

## Генерация документации
Нужны: doxygen, graphviz

    cd markov
    doxygen

Документация будет в doc/html/

# Windows

## Ссылки на нужные программы
 * [CMake](http://www.cmake.org/cmake/resources/software.html)
 * [Doxygen](http://www.stack.nl/~dimitri/doxygen/download.html#latestsrc)
 * [Graphviz](http://www.graphviz.org/Download_windows.php)
 * Какой-нибудь компилятор, например [MinGW](http://www.mingw.org/wiki/Getting_Started)

# Сборка
 1. Получаем исходники с github`а любым способом, например на странице проэкта есть кнопочка ZIP,
    с помощью которой можно скачать архив с исходниками
 
 2. Разархивируем этот архив
 3. Последующие шаги будут позже.. =) (когда под рукой будет Windows)

# Генерация документаци
