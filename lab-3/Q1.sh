#!/bin/bash
numReg='^[0-9]+$'

function check_is_num(){
   if ! [[ $1 =~ $numReg ]] ; then
   echo "error: $1 is Not a number"
   return 0
fi 
return 1
}

first=$1
second=$2
check_is_num $first
is_first_num=$?

check_is_num $second
is_second_num=$?

if [ $is_first_num -gt 0 ] && [ $is_second_num -gt 0 ]
then
    sum=$(expr $first + $second)
    echo "sum: $sum"


    if [ $first -gt $second ] 
    then    
        echo "greater number is: $fisrt"
    elif [ $first -lt $second ] 
    then
        echo "greater number is: $second"
    else
        echo "numbers are equal!"
    fi
fi


