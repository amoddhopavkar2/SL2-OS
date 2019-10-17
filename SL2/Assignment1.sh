#!/bin/sh
while :
do
	echo "\n---MAIN MENU---\n"
	echo "1. CREATE:"
	echo "2. INSERT:"
	echo "3. DISPLAY:"
	echo "4. SEARCH:"
	echo "5. MODIFY:"
	echo "6. DELETE:"
	echo "7. EXIT:"
	echo "\nENTER YOUR CHOICE: \c"
	read ch

	create() {
		echo "\nENTER NAME OF THE ADDRESS BOOK:\c"
		read addBook
		while [ -e $addBook ]
		do
			echo "\nADDRESS BOOK ALREADY EXISTS!\nENTER A NEW NAME:\c"
			read addBook
		done
		touch "$addBook"
		echo "ROLL \tNAME \tCLASS \tMARKS \tPHONE NO">$addBook
		echo "-----------------------------------------------------">>$addBook
	}

	insert() {
		echo "\nENTER ROLL NO:\c"
		read roll 
		echo "\nENTER NAME:\c"
		read name
		echo "\nENTER CLASS:\c"
		read class 
		echo "\nENTER MARKS:\c"
		read marks
		echo "\nENTER PHONE NO:\c"
		while true
		do
			read phno 
			len1=$(echo -n $phno | wc -m)
			if test $len1 -eq 10 ; then
				break;
			else
				echo "\nENTER A VALID PHONE NO:\c"
			fi
		done
		echo "$roll \t$name \t$class \t$marks \t$phno">>$addBook
	}

	display () {
		echo "\n"
		cat $addBook
	}

	search () {
		echo "\nENTER A ROLL NO TO SEARCH:\c"
		read key
		grep -q -w "$key" $addBook
		if [ $? -ne 0 ]
		then
			echo "\nRECORD NOT FOUND!"
		else
			echo "\nRECORD FOUND!\n"
			grep -i -w "$key" $addBook 
		fi
	}

	modify () {
		echo "\nENTER A ROLL NO TO SEARCH:\c"
		read key
		grep -q -w "$key" $addBook
		if [ $? -ne 0 ]
		then
			echo "\nRECORD NOT FOUND!"
		else
			grep -i -v -w -q "$key" $addBook>temp
			mv temp "$addBook"
			insert 
		fi
	}

	delete () {
		echo "\nENTER A ROLL NO TO SEARCH:\c"
		read key
		grep -q -w "$key" $addBook
		if [ $? -ne 0 ]
		then
			echo "\nRECORD NOT FOUND!"
		else
			grep -i -v -w "$key" $addBook>temp
			mv temp "$addBook"
			echo "\nRECORD DELETED SUCCESSFULLY!\n" 
		fi
	}

	case "$ch" in
		1) create;;
		
		2) x=1
		   while [ "$x" -eq 1 ]
		   do
		   		insert
		   		echo "\nDO YOU WANT TO INSERT ANOTHER RECORD?[1-YES|0-NO]:\c"
		   		read x
		   	done;;

		3) display;;

		4) search;;

		5) modify;;

		6) delete;;

		7) exit 1;;

		*) echo "\nENTER A VALID OPTION!\n";;
	esac
done