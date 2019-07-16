#!/bin/sh

while :
do
	echo "MAIN MENU"
	echo "1)Create a record:"
	echo "2)Display the record:"
	echo "3)Exit:"
	echo "Enter your choice[1-3]:"
	read ch

	case $ch in
		1) echo "Enter the name:"
		   read name
		   echo "Enter phone no:"
		   read phno
		   ;;
		   
		   
		2) echo "Name: $name"
		   echo "Phone No:$phno"
		   ;;
		   
		3) echo "Bye $USER!"
		   exit 0
		   ;;
	esac
done
