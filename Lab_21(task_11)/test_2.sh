#!/bin/bash

touch f1 | echo -n "aa" > f1
touch f2 
touch f3 | echo -n "aaaaaaaaaa" > f3

result=`./task_11.sh f1 f2 --size= 5`

echo "Test 2:
Эталонный ответ: 
wrong
Выводимый ответ:"

touch f4
diff f2 f3 > f4
if [[ -s f4 ]]; then
echo -e "wrong\n"
else
echo -e "ok\n"
fi

rm -r f1 f2 f3 f4