[![Build Status](https://travis-ci.org/NidentalEgor/TestTaskTree.svg?branch=master)](https://travis-ci.org/NidentalEgor/TestTaskTree/builds)

Получение проекта: git clone --recursive https://github.com/NidentalEgor/TestTaskTree.git

Описание задания в файле TestTaskTree.pdf.

Структура дерева в файле:

неограниченное количество записей вида
<тип_узла количество_потомков значение_узла>

тип_узла:
0 - целое число
1 - вещественное число
2 - строка

Сериализация в консоль:
Узлы разных уровней разделены строкой "Level #".
Потомки узла в рамках одного уровня разделены пробелом ' '. 
Потомки разных узлов в рамках одного уровнЯ разделены вертикальной чертой '|'.

Для сборки необходим boost (рекомендуемая версия 1.62) и
переменная среды BOOST_ROOT, указывающая на папку с boost-ом(Windows).