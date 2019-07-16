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

	create()
	{
		echo "\nENTER NAME OF THE FILE:\c"
		read fileName
		while [ -e $fileName.txt ]
		do
			echo "\nFILE ALREADY EXISTS!\nPLEASE ENTER A NEW FILENAME:\c"
			read fileName
		done
		touch "$fileName.txt"
		echo "NAME \tROLL NO \tCLASS \tPHONE NO">$fileName.txt
		echo "-----------------------------------------">>$fileName.txt
	}

	insert()
	{
		echo "\nName of the student:\c"
		read name
		echo "\nRoll no. of the student:\c"
		read rollno
		echo "\nClass of the student:\c"
		read class
		echo "\nPhone no. of the student:\c"
		read phno
		echo "$name \t$rollno \t\t$class \t$phno">>$fileName.txt
	}

	display()
	{
		cat $fileName.txt
	}

	search()
	{
		echo "\nEnter a Roll no. to search:\c"
		read key
		grep -i -w "$key" $fileName.txt
		if [ $? -ne 0 ]
		then
			echo "\nRECORD NOT FOUND!"
		fi
	}

	delete()
	{
		echo "\nEnter a Roll no. to delete:\c"
		read key
		grep -v -i -w "$key" $fileName.txt>zzz.txt
		if [ $? -ne 0 ]
		then
			echo "\nRECORD DOES NOT EXIST!"
		else
			echo "\nRECORD DELETED SUCCESSFULLY!"
		fi
		mv zzz.txt "$fileName.txt"
	}

	modify()
	{
		echo "\nEnter a Roll no. to modify:\c"
		read key
		grep -i -v -w "$key" $fileName.txt>zzz.txt
		if [ $? -ne 0 ]
		then 
			echo "\nRECORD DOES NOT EXIST!"
		fi
		mv zzz.txt "$fileName.txt"
	}
		
	case "$ch" in
		1) 	create;;

		2)	x=1
			while [ "$x" -eq 1 ]
			do
				insert
				echo "\nDO YOU WANT TO INSERT ANOTHER RECORD?[1-Yes|0-No]:\c"
				read x
			done;;

		3) 	display;;

		4)	search;;

		5)	delete
			display;;
				
		6)	modify
			insert
			display;;
				
		7)	echo "\nBye $USER!\n"
			exit 1;;
				
		*)	echo "\nENTER A VALID CHOICE BETWEEN 1 TO 7!";;
	esac
done
