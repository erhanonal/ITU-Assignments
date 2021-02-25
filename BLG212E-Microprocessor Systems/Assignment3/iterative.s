;Erhan Önal 150170713
index 	EQU 0x000020		;Declare index variable which will define how many fibonacci numbers to calculate

		AREA     NEW_ARRAY,DATA, READWRITE	;Define this part will write in data area
		ALIGN	
__Array_Start
arr     SPACE    index				;Allocate space from memory 
__Array_End
		
		
		AREA firstcode, code, readonly ;Declare new area
		ENTRY				;Declare as entry poin
		ALIGN 				;Ensures that __main addresses the following instruction.
__main	FUNCTION			;Enable Debug
		EXPORT __main		;Make __main as global to access from startup file

		MOVS r1,#index		;Move index value to R1
		LDR r0,=arr			;Load the start adress of array to R0
		MOVS r3,#0			;R3 will hold the iteration variable,initialize with 0
		MOVS r4,#4			;Load 4 to R4 to use in multiplication
		MULS r1,r4,r1		;Index value is multiplied by 4 in order to compare with iteration variable in R3
		
LOOP	CMP r1,r3			;Compare index in R1 with R3,iteration variable
		BEQ	QUIT			;If they are equal, exit the loop
		CMP	r3,#4			;Compare iteration variable R3 with 4
		BLE	ADD1			;If its less than or equal to 4,it is the first 2 members of fibonacci series, branch to ADD1 label
		MOVS r4,r3			;The loop iterates for the remaining members after adding fib(1) and fib(2), save the iteration variable to R4
		MOVS r5,r3			;Save the iteration variable to R5
		SUBS r4,r4,#4		;Substract 4 from R4, now it will point to fib(n-1) when added to array start
		SUBS r5,r5,#8		;Substract 8 from R5, now it will point to fib(n-2) when added to array start
		LDR r6,[r0,r4]		;Load fib(n-1) to R6
		LDR r7, [r0,r5]		;Load fib(n-2) to R7
		ADDS r6,r6,r7		;Add R6 and R7 and save to R6, R6 now holds fib(n)=fib(n-1)+fib(n-2)
		STR r6,[r0,r3]		;Store fib(n) in R6 to the location pointed by iteration variable+array start
		ADDS r3,r3,#4		;Increment the iteration varible R3 by 4
		B	LOOP			;Return to the start of the loop
		
QUIT	B QUIT				;Infinite loop to indicate function end	
			
ADD1	MOVS r4,#1			;Move 1 to r4
		STR r4,[r0,r3]		;Store the number to [array start+iteration variable R3]
		ADDS r3,r3,#4		;Increase the iteration varible by 4,since adresses move by 4
		B	LOOP			;return to LOOP
	


		
		ENDFUNC				;Finish Function
		END					;Finish Assebly File
