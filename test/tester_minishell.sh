/bin/ls > result/ms01.txt
/bin/ls .. > result/ms10.txt
/bin/ls $HOME > result/ms11.txt
/bin/ls ~ > result/ms12.txt

echo > result/ms20.txt
echo "hello""world" > result/ms21.txt
echo "hello" "world" > result/ms22.txt
echo hello world > result/ms23.txt
echo -n asdf > result/ms24.txt

/bin/ls .. > result/ms30.txt ; echo a b ; echo c d > result/ms32.txt

echo '\a\b\c' > result/ms40.txt
echo "\"" > result/ms41.txt
echo \" > result/ms42.txt
ls '..' > result/ms43.txt
ls '' > result/ms44.txt
echo '$HOME' > result/ms45.txt
echo "$HOME" > result/ms46.txt

ls .. > result/ms50.txt >> result/ms51.txt
grep I < result/ms51.txt > result/ms52.txt

cat result/ms52.txt | grep a | wc> result/ms60.txt
cat sdfijdsifsojfdi | grep a | wc > result/ms61.txt