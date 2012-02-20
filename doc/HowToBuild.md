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
 * [Git](http://code.google.com/p/msysgit/downloads/list) -
   нужен _Full installer for official Git For Windows_
 * [MinGW](http://www.mingw.org/wiki/Getting_Started)

## Сборка

### Получаем исходники

#### Вариант 1

 1. На [странице проекта](https://github.com/xelez/markov/) есть кнопочка **ZIP**,
    с помощью которой можно скачать архив с исходниками
 
 2. Разархивируем этот архив

#### Вариант 2
 1. Ставим Git, например вот по этой [инструкции](http://kuroikaze85.wordpress.com/2009/12/16/git-on-windows/)
 2. Находим какую-нибудь папку, в которую скачаются исходники.
 3. Правой кнопкой мыши по ней и щелкаем _Git Bash_. Откроется чёрное окошечко.
 4. В него копируем `git clone https://github.com/xelez/markov.git` и жмём Enter.
 5. Git скачает исходники и в подпапку _markov_ .

### Ставим компилятор MinGW
 1. Скачиваем и устанавливаем.
 2. Добавляем путь к нему в PATH, например с помощью [RapidEE](http://www.rapidee.com/ru/download)

## Собираем
 1. Если нету компилятора, то ставим его.
 2. Если нету CMake, то, опять же, ставим его.
 3. Из главного меню запускаем CMake (gui)
 4. Указываем соответствующие директории
    * Source code - папка с исходниками (та, в которой лежит CMakeLists.txt)
    * build the binaries - подпапка _build_ в папке с исходниками (её нужно будет предварительно создать)
    * **Внимание!** В путях к папкам не должно быть пробелов.

 5. Нажимаем Configure
 6. Выбираем что генерировать будем MinGW Makefiles. Используем стандартные компиляторы.
 7. Нажимаем Finish. Если что-то пошло не так, то нужно убедиться, что переменная среды PATH
    задана верно и CMake ищет компиляторы в нужном месте.
 8. Изменяем CMAKE_BUILD_TYPE на Release.
 9. Ещё раз нажимаем Configure. Затем Generate.
 9. Пуск->Выполнить, запускаем cmd.exe
 9. `cd path_to_build_dir`
 9. `mingw32-make`
 9. Видим разные сообщения компиляции, если всё удачно и ошибок не возникло, то собранная программа будет в папке build
 
## Генерация документаци
 1. Ставим вначале Graphviz, а потом Doxygen
 2. Запускаем Doxywizard из Пуск->Программы->Doxygen
 2. В открывшемся окне File->Open и выбираем файл Doxyfile из папки с исходниками.
 3. Переходим на вкладку Run и нажимаем Run doxygen.
 4. Ждём, после чего html файлы будут в подпапке _doc/html_. Show HTML Output откроет браузер с документацией.

##TODO:
  может быть стоит расписать что происходит при нажатии каждой кнопочки...