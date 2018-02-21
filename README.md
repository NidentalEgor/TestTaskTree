[![Build Status](https://travis-ci.org/NidentalEgor/TestTaskTree.svg?branch=master)](https://travis-ci.org/NidentalEgor/TestTaskTree/builds)

#### **Техническое задание в [TestTask.txt](https://github.com/NidentalEgor/Unzipper/blob/master/TestTask.txt)**

#### **Получение проекта:**
```sh
git clone --recursive https://github.com/NidentalEgor/TestTaskTree.git
cd Build
[bash linux.sh / windows.cmd] [Release / Debug]
```
#### **Сборка:**
Собирается с помощью Visual Studio 2015 и gcc 5.4.0.
#### **Структура дерева в файле:**

неограниченное количество записей вида
**<тип_узла количество_потомков значение_узла>**, где
**тип_узла** может принимать следующие значения:
0 - целое число
1 - вещественное число
2 - строка

#### **Сериализация в консоль:**
Узлы разных уровней разделены строкой **Level #**.
Потомки узла в рамках одного уровня разделены **пробелом**. 
Потомки разных узлов в рамках одного уровня разделены **вертикальной чертой**.

#### **Зависимости:**
Для сборки необходим boost (рекомендуемая версия 1.62) и
переменная среды BOOST_ROOT, указывающая на папку с boost-ом(Windows).