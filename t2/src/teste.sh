for (( c=20; c<=40; c++ ))
do  
    ./a.out $c > $c.in
    ./quimica < $c.in 2> $c.out
done