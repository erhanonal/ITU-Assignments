;Erhan Önal 150170713

index 	EQU 0x0000015	;Define the variable index which is the index of the fibonacci number to return in R1		
		AREA firstcode, code, readonly ;Declare new area
		ENTRY				;Declare as entry point
		ALIGN 				;Ensures that __main addresses the following instruction.
__main	FUNCTION			;Enable Debug
		EXPORT __main		;Make __main as global to access from startup file
			

		MOVS r1,#index	;Save the index at R1
		BL FIB			;Call FIB subroutine
		
QUIT	B QUIT			;Infinite loop to indicate function end

FIB		PUSH {r2,r3,lr}	;Push the values in R2,R3 and LR to stack. R2 and R3 holds intermediate values, LR holds return adress
		MOVS r2,r1		;Move the R1 value to R2
		CMP r2,#2		;Compare R2 to 2
		BLE ADD1		;Branch to ADD1 label if R2 is less than or equal to 2
		
		SUBS r1,r2,#1	;Set the function parameter to n-1
		BL	FIB			;Call FIB subroutine for n-1 while saving the return adress to LR
		
		MOVS r3,r1		;Save the return value to R3
		SUBS r1,r2,#2	;Set to function parameter to n-2
		BL	FIB			;Call FIB subroutine for n-2 while saving the return adress to LR
		
		ADDS r1,r3,r1	;Add the return value to R3, R3 holds fib(n)=fib(n-1)+fib(n-2)
		POP {r2,r3,pc}	;Pop the values R2 and R3 to registers, Pop the return adress to PC to continue program flow
		
		
ADD1	MOVS r1,#1	;If index<=2 , the result is 1, move 1 to the R1
		POP {r2,r3,pc}	;Pop the values R2 and R3 to registers, Pop the return adress to PC to continue program flow
		
		
		ENDFUNC				;Finish Function
		END					;Finish Assembly File
