#!/bin/bash

function pattern1(){
	for ((i=1;i<=5;i++))
	do
		for j in $(seq 1 $i)
		do
			echo -n "$i "
		done
		echo
	done
}

function pattern2(){
	for ((i=1;i<=6;i++))
	do
		for ((j=5;j>=$i;j--))
		do
			echo -n " "
		done
		for j in $(seq 1 $i)
		do
			echo -n "* "
		done
		echo
	done
	for ((i=1;i<=6;i++))
	do
		for ((j=1;j<$i;j++))
		do
			echo -n " "
		done
		for ((j=$i;j<=6;j++))
		do
			echo -n "* "
		done
		echo
	done
	
}

function pattern3(){
	for ((i=1;i<=5;i++))
	do
		
		for ((j=1;j<$i;j++))
		do
			echo -n "| "
		done
		echo "|_"
	done
}

case $1 in
	"1")
		pattern1
		;;
	"2")
		pattern2
		;;
	"3")
		pattern3
		;;	
esac
