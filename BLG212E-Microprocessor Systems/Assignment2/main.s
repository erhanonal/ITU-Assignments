;Erhan Önal 150170713

Adress_SYST_CSR  	EQU	0xE000E010 	;Adress for the SYST_CSR
Adress_SYST_RVR		EQU 0xE000E014	;Adress for the SYST_RVR
val_SYST_RVR		EQU 0x00011940	;Calculated value for SYST_RVR 1 ms*72 Mhz=72000d=0x11940
disable_SYST_CSR	EQU 0x00000006	;Value that disables SYST_CSR
enable_SYST_CSR		EQU 0x00000007	;Value that enables SYST_CSR
index				EQU 0x00000028	;index value for allocating necessary array space in memory. 0x28=40d, 10 integer values 
	
		AREA     NEW_ARRAY,DATA, READWRITE	;Define this part will write in data area
		ALIGN	
__Array_Start
arr     SPACE    index				;Allocate space from memory 
__Array_End

		AREA main, READONLY, CODE 
		ENTRY 
		ALIGN
__main 	FUNCTION	
		EXPORT __main
					
		
		LDR r1, =3;
		LDR r2,=6;
		LDR r3, =0x20003020
		LDR r4, =0x20004018
		BL erhan
		

		
		STR r1,[r3,#4]
		STR r2,[r4,#8]

erhan	LDR r7,=8;
		BX LR
		ENDP

		END
			
