	INCLUDE core_cm4_constants.s		; Load Constant Definitions
	INCLUDE stm32f4xx_constants.s      

	AREA    main, CODE, READONLY
	EXPORT	__main				; make __main visible to linker
	ENTRY			
				
__main	PROC	
    ; Enable the clock to GPIO Port A	
	LDR r0, =RCC_BASE
	LDR r1, [r0, #RCC_AHB1ENR]		
	ORR r1, r1, #RCC_AHB1ENR_GPIOAEN;
	STR r1, [r0, #RCC_AHB1ENR]		
	
	; GPIO setting (PA_5)
	LDR r0, =GPIOA_BASE
	LDR r1, [r0, #GPIO_MODER]
	AND r1, r1, #(~(0x03<<(2*5))) 	; clear bits
	ORR r1, r1, #(1<<2*5)			; 01: output mode
	STR r1, [r0, #GPIO_MODER]

	LDR r1, [r0, #GPIO_OSPEEDR]
	AND r1, r1, #(~(0x03<<(2*5))) 	; clear bits
	ORR r1, r1, #(2<<2*5)			; 01: fast speed
	STR r1, [r0, #GPIO_OSPEEDR]

	LDR r1, [r0, #GPIO_ODR]
	ORR r1, r1, #(1<<5)
	STR r1, [r0, #GPIO_ODR]

;	ENDP
		
stop 	B 		stop     		; dead loop & program hangs here

	ENDP
					
	ALIGN			

	AREA    myData, DATA, READWRITE
	ALIGN
array	DCD   1, 2, 3, 4
	END		