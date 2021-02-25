varX	EQU 3
			AREA firstcode, code, readonly ;Declare new area
			ENTRY				;Declare as entry point
			ALIGN 				;Ensures that __main addresses the following instruction.
__main		FUNCTION			;Enable Debug
			EXPORT __main		;Make __main as global to access from startup file
				
			MOVS r0,#varX
			MOVS r1,#0
			PUSH {r0}
			BL FACT
QUIT		B QUIT

FACT		POP{r0}
RET			CMP r0,#1
			BLE RETURN1
			PUSH{r1,lr}
			MOVS r1,r0
			SUBS r0,r0,#1
			BL RET
			MULS r0,r1,r0
			POP{r1,pc}
			
RETURN1		MOVS r0,#1
			BX LR
			ENDFUNC
			END
