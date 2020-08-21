# "Simple Command"
/bin/ls > result/bash01.txt

# "Arguments"
/bin/ls .. > result/bash10.txt
/bin/ls $HOME > result/bash11.txt
/bin/ls ~ > result/bash12.txt

# "echo"
echo > result/bash20.txt
echo "hello""world" > result/bash21.txt
echo "hello" "world" > result/bash22.txt
echo hello world > result/bash23.txt
echo -n asdf > result/bash24.txt

# semicolon
/bin/ls .. > result/bash30.txt ; echo a b ; echo c d > result/bash32.txt

# quotes
echo '\a\b\c' > result/bash40.txt
echo "\"" > result/bash41.txt
echo \" > result/bash42.txt
ls '..' > result/bash43.txt
ls '' > result/bash44.txt
echo '$HOME' > result/bash45.txt
echo "$HOME" > result/bash46.txt

# redirection
ls .. > result/bash50.txt >> result/bash51.txt
grep I < result/bash51.txt > result/bash52.txt

# pipe
cat result/bash52.txt | grep a | wc > result/bash60.txt
cat sdfijdsifsojfdi | grep a | wc > result/bash61.txt