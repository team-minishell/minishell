rm ./result/*.txt
bash < tester_bash.sh
../minishell < tester_minishell.sh
for var in 01 10 11 12 20 21 22 23 24 30 32 40 41 42 43 44 45 46 50 51 52 60 61
do
  diff result/bash$var.txt result/ms$var.txt
  if [ $? -eq 0 ] ; then
    echo "$var ok";
  else
    echo "diff in $var"
  fi
done
