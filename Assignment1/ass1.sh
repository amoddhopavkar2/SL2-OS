#!/bin/sh
while :
do
	echo "\n---MAIN MENU---\n"
	echo "1. CREATE ADDRESS BOOK:"
	echo "2. INSERT A RECORD:"
	echo "3. VIEW ADDRESS BOOK:"
	echo "4. SEARCH A RECORD:"
	echo "5. DELETE A RECORD:"
	echo "6. MODIFY A RECORD:"
	echo "7. EXIT:"
	echo "\nENTER YOUR CHOICE[1-7]:\c"
	read ch 

	create()
	{
		echo "\nENTER NAME OF THE ADDRESS BOOK:\c"
		read addBook
		while [ -e $addBook.txt ]
		do
			echo "\nADDRESS BOOK ALREADY EXISTS!\nPLEASE ENTER A NEW NAME:\c"
			read addBook
		done
		touch "$addBook.txt"
		echo "NAME \tADDRESS \tCITY \tSTATE \tPINCODE \tPHONE NO">$addBook.txt
	}

	insert()
	{
		echo "\nEnter Name:\c"
		read name
		echo "\nEnter Address:\c"
		read add
		echo "\nEnter City:\c"
		read city
		echo "\nEnter State:\c"
		read state
		echo "\nEnter Pincode:\c"
		read pin
		echo "\nEnter Phone No:\c"
		read phno
		
		echo "$name \t$add \t$city \t$state \t$pin \t$phno">>addBook.txt
	}
	
	display()
	{
		echo"\n"
		cat $addBook.txt	
	}
	
	search()
	{
		echo "\nEnter a phone no to search:\c"
		read key
		grep -i -w "$key" $addBook.txt
		if [ $? -ne 0 ]
		then
			echo "\nRECORD NOT FOUND!"
		fi
	}
	
	delete()
	{
		echo "\nEnter a phone no to delete:\c"
		read key
		grep -i -v -w "$key" $addBook.txt>zzz.txt
		if [ $? -ne 0 ]
		then
			echo "\nRECORD DOES NOT EXIST!"
		else
			echo "\nRECORD DELETED SUCCESSFULLY!"
		fi
		
		mv zzz.txt "$addBook.txt"
		
		display
	}
	
	modify()
	{
		echo "\nEnter a phone no to modify the record:\c"
		read key
		grep -i -v -w "$key" addBook.txt>zzz.txt
		if [ $? -ne 0 ]
		then
			echo "\nRECORD DOES NOT EXIST!"
		fi
		
		mv zzz.txt "$addBook.txt"
		
		insert
		display	
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
		
		5) delete;;
		
		6) modify;;
		
		7) echo "BYE $USER!"
		   exit 1;;
		   
		*) echo "\nENTER A VAILD OPTION BETWEEN 1 TO 7!";;
	esac
done
