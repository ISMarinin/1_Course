#!/bin/bash
pushd .
name=test
rm -rf $name && mkdir $name && cd $name
echo "До:"
tee -a f1.txt << EOF
1
3
4
2
EOF
tee -a f2.txt << EOF
c
a
b
d
EOF
echo "После:"
ls | sort -bd f1.txt f2.txt
echo "Сравнение файлов:"
diff -u f1.txt f2.txt
echo "Поиск цифры 2 в f1.txt:"
grep -hn 2 f1.txt > f3.txt
cat f3.txt
echo "Удаление левой секции текста:"
cut -d":" -f2 f3.txt
echo "Подсчет кол-ва строк в f2.txt:"
wc -l f2.txt
echo "Замена c на d в f2.txt:" 
cat f2.txt | tr c d
echo "Поиск f1.txt:"
find ./f1.txt
echo "Размер f1.txt:"
du -h ./f1.txt
popd