#!/bin/bash

touch f1 | echo -n "a" > f1
touch f2 
touch f3 | echo -n "aaaaa" > f3

result=`./task_11.sh f1 f2 --size= hgf`

echo "Test 3:
Эталонный ответ: 
Аргумент --size= принимает только числовые значения
Выводимый ответ:"
echo $result

rm -r f1 f2 f3