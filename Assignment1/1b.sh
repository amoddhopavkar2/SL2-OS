#Write a program to implement an address book with options given below:
	#1. Create address book.
	#2. View address book.
	#3. Insert a record.
	#4. Search a record.
	#5. Delete a record.
	#6. Modify a record.
	#7. Exit.

#!/bin/sh
while :
do
	echo "\n---MAIN MENU---\n"				#Print the main menu
	echo "1. CREATE ADDRESS BOOK:"
	echo "2. INSERT A RECORD:"
	echo "3. VIEW ADDRESS BOOK:"
	echo "4. SEARCH A RECORD:"
	echo "5. DELETE A RECORD:"
	echo "6. MODIFY A RECORD:"
	echo "7. EXIT:"
	echo "\nENTER YOUR CHOICE[1-7]:\c"
	read ch 

	create()								#Function to create a file
	{
		echo "\nENTER NAME OF THE ADDRESS BOOK:\c"
		read addBook
		while [ -e $addBook.txt ]			#Validation whether the file already exists
		do
			echo "\nADDRESS BOOK ALREADY EXISTS!\nPLEASE ENTER A NEW NAME:\c"
			read addBook
		done
		touch "$addBook.txt"
		echo "NAME \tADDRESS \tCITY \tSTATE \tPINCODE \tPHONE NO">$addBook.txt
		echo "------------------------------------------------------------------">>$addBook.txt
	}

	insert()								#Function to insert records
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
		
		echo "$name \t$add \t\t$city \t$state \t$pin \t\t$phno">>$addBook.txt
	}
	
	display()								#Display function
	{
		echo "\n"
		cat $addBook.txt		
	}
	
	search()								#Search function
	{
		echo "\nEnter a phone no to search:\c"
		read key
		grep -i "$key" $addBook.txt
		if [ $? -ne 0 ]
		then
			echo "\nRECORD NOT FOUND!"
		fi
	}
	
	delete()								#Delete function
	{
		echo "\nEnter a phone no to delete:\c"
		read key
		grep -i -v "$key" $addBook.txt>zzz.txt		#If record not found then copied to a new file
		if [ $? -ne 0 ]
		then
			echo "\nRECORD DOES NOT EXIST!"				
		else
			echo "\nRECORD DELETED SUCCESSFULLY!"
		fi
		
		mv zzz.txt "$addBook.txt"						#New file moved as old file
		
		display 							#Display function called
	}
	
	modify()								#Modify function
	{
		echo "\nEnter a phone no to modify the record:\c"
		read key
		grep -i -v "$key" $addBook.txt>zzz.txt		#If record not found then copied to a new file
		if [ $? -ne 0 ]
		then
			echo "\nRECORD DOES NOT EXIST!"
		fi
		
		mv zzz.txt "$addBook.txt"						#New file moved as old file
		
		insert 								#Insert function called
		display	 							#Display function called
	}

	case "$ch" in 							#Switch case structure
		1) create;;
		
		2) x=1
		   while [ "$x" -eq 1 ]
		   do
		   	insert 							#Insert function called
		   	echo "\nDO YOU WANT TO INSERT ANOTHER RECORD?[1-YES|0-NO]:\c"
		   	read x
		   done;;
		
		3) display;;						#Display function called
		
		4) search;;							#Search function called
		
		5) delete;;							#Delete function called
		
		6) modify;;							#Modify function called
		
		7) echo "BYE $USER!"				#'$USER' gives the current user
		   exit 1;;
		   
		*) echo "\nENTER A VAILD OPTION BETWEEN 1 TO 7!";;
	esac
done
