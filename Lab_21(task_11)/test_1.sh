#!/bin/bash

touch f1 | echo -n "a" > f1
touch f2 
touch f3 | echo -n "aaaaa" > f3

result=`./task_11.sh f1 f2 --size= 5`

echo "Test 1:
Эталонный ответ: 
ok
Выводимый ответ:"

touch f4
diff f2 f3 > f4
if [[ -s f4 ]]; then
echo -e "wrong\n"
else
echo -e "ok\n"
fi

rm -r f1 f2 f3 f4