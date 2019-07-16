#!/bin/sh
while :
do
	echo "\n---MAIN MENU---\n"
	echo "1)CREATE:"
	echo "2)INSERT:"
	echo "3)DISPLAY:"
	echo "4)SEARCH:"
	echo "5)DELETE:"
	echo "6)MODIFY:"
	echo "7)EXIT:"
	echo "\nENTER YOUR CHOICE[1-7]:\c"
	read ch

	case "$ch" in

		1) 	echo "\nENTER NAME OF THE FILE:\c"
			read fileName
			touch "$fileName.txt"
			echo "NAME \tROLL NO \tCLASS \tPHONE NO">$fileName.txt
			;;

		2)	x=1
			y=1
			while [ "$x" -eq "$y" ]
			do
				echo "\nName of the student:\c"
				read name
				echo "\nRoll no. of the student:\c"
				read rollno
				echo "\nClass of the student:\c"
				read class
				echo "\nPhone no. of the student:\c"
				read phno
				echo "$name \t$rollno \t\t$class \t$phno">>$fileName.txt
				echo "\nDO YOU WANT TO INSERT ANOTHER RECORD?[1-Yes|0-No]:\c"
				read x
			done
			;;

		3) 	cat $fileName.txt
			;;

		4)	echo "\nEnter a Roll no. to search:\c"
			read key
			grep -i "$key" $fileName.txt
			;;

		5)	echo "\nEnter a Roll no. to delete:\c"
			read key
			grep -v -i "$key" $fileName.txt>file1.txt
			mv file1.txt "$fileName.txt"
			;;
			
		7)	echo "\nBye $USER!\n"
			exit 1
			;;
			
		*)	echo "\nINVALID CHOICE!"
			;;
		esac
done
