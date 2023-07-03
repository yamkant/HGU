; This following is added to remove the compiler warning.    
	AREA    __DEFINES_STM32F4_xx_DUMMY, CODE, READONLY

; Peripheral_memory_map
RCC_BASE	  EQU (0x40023800)
FLASH_BASE    EQU (0x40023C00) ; FLASH(up to 1 MB) base address
PERIPH_BASE   EQU (0x40000000) ; Peripheral base address

; AHB1 peripherals
GPIOA_BASE  	EQU (0x40020000)
GPIOB_BASE  	EQU (0x40020400)
GPIOC_BASE  	EQU (0x40020800)
GPIOD_BASE  	EQU (0x40020C00)
GPIOE_BASE  	EQU (0x40021000)
GPIOH_BASE		EQU (0x40021C00)

; Reset and Clock Control (RCC)
RCC_CR  		EQU  0x00  
RCC_PLLCFGR     EQU  0x04  
RCC_CFGR        EQU  0x08  
RCC_CIR     	EQU  0x0C  
RCC_AHB1RSTR	EQU  0x10  
RCC_AHB2RSTR	EQU  0x14  
RCC_APB1RSTR    EQU  0x20  
RCC_APB2RSTR   	EQU  0x24  
RCC_AHB1ENR    	EQU  0x30  
RCC_AHB2ENR   	EQU  0x34  
RCC_APB1ENR    	EQU  0x40  
RCC_APB2ENR   	EQU  0x44  
RCC_AHB1LPENR   EQU  0x50  
RCC_AHB2LPENR   EQU  0x54  
RCC_APB1LPENR   EQU  0x60  
RCC_APB2LPENR   EQU  0x64  
RCC_BDCR		EQU  0x70  
RCC_CSR   		EQU  0x74  
RCC_SSCGR   	EQU  0x80  
RCC_PLLI2SCFGR  EQU  0x84  
RCC_DCKCFGR   	EQU  0x8C  

; General Purpose I/O (GPIO)
GPIO_MODER      EQU  0x00      ; GPIO port mode register,               Address offset: 0x00
GPIO_OTYPER     EQU  0x04      ; GPIO port output type register,        Address offset: 0x04
GPIO_OSPEEDR    EQU  0x08      ; GPIO port output speed register,       Address offset: 0x08
GPIO_PUPDR      EQU  0x0C      ; GPIO port pull-up/pull-down register,  Address offset: 0x0C
GPIO_IDR        EQU  0x10      ; GPIO port input data register,         Address offset: 0x10
GPIO_ODR        EQU  0x14      ; GPIO port output data register,        Address offset: 0x14
GPIO_BSRR       EQU  0x18      ; GPIO port bit set/reset  register,     Address offset: 0x18
GPIO_LCKR       EQU  0x1C      ; GPIO port configuration lock register, Address offset: 0x1C
GPIO_AFRL       EQU  0x20      ; GPIO alternate function registers,     Address offset: 0x20-0x24
GPIO_AFRH       EQU  0x24      ; GPIO alternate function registers,     Address offset: 0x20-0x24

; *****************************************************************************
;
;                         Reset and Clock Control
;
; *****************************************************************************
; ********************  Bit definition for RCC_CR register  *******************
RCC_CR_MSION                EQU (0x00000001)      ; Internal Multi Speed oscillator (MSI) clock enable
RCC_CR_MSIRDY               EQU (0x00000002)      ; Internal Multi Speed oscillator (MSI) clock ready flag
RCC_CR_MSIPLLEN             EQU (0x00000004)      ; Internal Multi Speed oscillator (MSI) PLL enable
RCC_CR_MSIRGSEL             EQU (0x00000008)      ; Internal Multi Speed oscillator (MSI) range selection

; MSIRANGE configuration : 12 frequency ranges available
RCC_CR_MSIRANGE             EQU (0x000000F0)       ; Internal Multi Speed oscillator (MSI) clock Range
RCC_CR_MSIRANGE_0           EQU (0x00000000)       ; Internal Multi Speed oscillator (MSI) clock Range 100 KHz
RCC_CR_MSIRANGE_1           EQU (0x00000010)       ; Internal Multi Speed oscillator (MSI) clock Range 200 KHz
RCC_CR_MSIRANGE_2           EQU (0x00000020)       ; Internal Multi Speed oscillator (MSI) clock Range 400 KHz
RCC_CR_MSIRANGE_3           EQU (0x00000030)       ; Internal Multi Speed oscillator (MSI) clock Range 800 KHz
RCC_CR_MSIRANGE_4           EQU (0x00000040)       ; Internal Multi Speed oscillator (MSI) clock Range 1 MHz
RCC_CR_MSIRANGE_5           EQU (0x00000050)       ; Internal Multi Speed oscillator (MSI) clock Range 2 MHz
RCC_CR_MSIRANGE_6           EQU (0x00000060)       ; Internal Multi Speed oscillator (MSI) clock Range 4  MHz
RCC_CR_MSIRANGE_7           EQU (0x00000070)       ; Internal Multi Speed oscillator (MSI) clock Range 8 KHz
RCC_CR_MSIRANGE_8           EQU (0x00000080)       ; Internal Multi Speed oscillator (MSI) clock Range 16 MHz
RCC_CR_MSIRANGE_9           EQU (0x00000090)       ; Internal Multi Speed oscillator (MSI) clock Range 24 MHz
RCC_CR_MSIRANGE_10          EQU (0x000000A0)       ; Internal Multi Speed oscillator (MSI) clock Range 32 MHz
RCC_CR_MSIRANGE_11          EQU (0x000000B0)       ; Internal Multi Speed oscillator (MSI) clock Range 48  MHz

RCC_CR_HSION                EQU (0x00000100)       ; Internal High Speed oscillator (HSI16) clock enable
RCC_CR_HSIKERON             EQU (0x00000200)       ; Internal High Speed oscillator (HSI16) clock enable for some IPs Kernel
RCC_CR_HSIRDY               EQU (0x00000400)       ; Internal High Speed oscillator (HSI16) clock ready flag
RCC_CR_HSIASFS              EQU (0x00000800)       ; HSI16 Automatic Start from Stop

RCC_CR_HSEON                EQU (0x00010000)       ; External High Speed oscillator (HSE) clock enable
RCC_CR_HSERDY               EQU (0x00020000)       ; External High Speed oscillator (HSE) clock ready
RCC_CR_HSEBYP               EQU (0x00040000)       ; External High Speed oscillator (HSE) clock bypass
RCC_CR_CSSON                EQU (0x00080000)       ; HSE Clock Security System enable

RCC_CR_PLLON                EQU (0x01000000)       ; System PLL clock enable
RCC_CR_PLLRDY               EQU (0x02000000)       ; System PLL clock ready
RCC_CR_PLLSAI1ON            EQU (0x04000000)       ; SAI1 PLL enable
RCC_CR_PLLSAI1RDY           EQU (0x08000000)       ; SAI1 PLL ready
RCC_CR_PLLSAI2ON            EQU (0x10000000)       ; SAI2 PLL enable
RCC_CR_PLLSAI2RDY           EQU (0x20000000)       ; SAI2 PLL ready

; ********************  Bit definition for RCC_PLLCFGR register  **************
RCC_PLLCFGR_PLLSRC          EQU (0x00000003)

RCC_PLLCFGR_PLLSRC_MSI      EQU (0x00000001)      ; MSI oscillator source clock selected
RCC_PLLCFGR_PLLSRC_HSI      EQU (0x00000002)      ; HSI16 oscillator source clock selected
RCC_PLLCFGR_PLLSRC_HSE      EQU (0x00000003)      ; HSE oscillator source clock selected

RCC_PLLCFGR_PLLM            EQU (0x00000070)
RCC_PLLCFGR_PLLM_0          EQU (0x00000010)
RCC_PLLCFGR_PLLM_1          EQU (0x00000020)
RCC_PLLCFGR_PLLM_2          EQU (0x00000040)

RCC_PLLCFGR_PLLN            EQU (0x00007F00)
RCC_PLLCFGR_PLLN_0          EQU (0x00000100)
RCC_PLLCFGR_PLLN_1          EQU (0x00000200)
RCC_PLLCFGR_PLLN_2          EQU (0x00000400)
RCC_PLLCFGR_PLLN_3          EQU (0x00000800)
RCC_PLLCFGR_PLLN_4          EQU (0x00001000)
RCC_PLLCFGR_PLLN_5          EQU (0x00002000)
RCC_PLLCFGR_PLLN_6          EQU (0x00004000)

RCC_PLLCFGR_PLLPEN          EQU (0x00010000)
RCC_PLLCFGR_PLLP            EQU (0x00020000)
RCC_PLLCFGR_PLLQEN          EQU (0x00100000)

RCC_PLLCFGR_PLLQ            EQU (0x00600000)
RCC_PLLCFGR_PLLQ_0          EQU (0x00200000)
RCC_PLLCFGR_PLLQ_1          EQU (0x00400000)

RCC_PLLCFGR_PLLREN          EQU (0x01000000)
RCC_PLLCFGR_PLLR            EQU (0x06000000)
RCC_PLLCFGR_PLLR_0          EQU (0x02000000)
RCC_PLLCFGR_PLLR_1          EQU (0x04000000)

; ********************  Bit definition for RCC_CFGR register  *****************
; SW configuration
RCC_CFGR_SW                 EQU (0x00000003)      ; SW[1:0] bits (System clock Switch)
RCC_CFGR_SW_0               EQU (0x00000001)      ;Bit 0
RCC_CFGR_SW_1               EQU (0x00000002)      ;Bit 1

RCC_CFGR_SW_MSI             EQU (0x00000000)      ; MSI oscillator selection as system clock
RCC_CFGR_SW_HSI             EQU (0x00000001)      ; HSI16 oscillator selection as system clock
RCC_CFGR_SW_HSE             EQU (0x00000002)      ; HSE oscillator selection as system clock
RCC_CFGR_SW_PLL             EQU (0x00000003)      ; PLL selection as system clock

; SWS configuration
RCC_CFGR_SWS                EQU (0x0000000C)      ; SWS[1:0] bits (System Clock Switch Status)
RCC_CFGR_SWS_0              EQU (0x00000004)      ;Bit 0
RCC_CFGR_SWS_1              EQU (0x00000008)      ;Bit 1

RCC_CFGR_SWS_MSI            EQU (0x00000000)      ; MSI oscillator used as system clock
RCC_CFGR_SWS_HSI            EQU (0x00000004)      ; HSI16 oscillator used as system clock
RCC_CFGR_SWS_HSE            EQU (0x00000008)      ; HSE oscillator used as system clock
RCC_CFGR_SWS_PLL            EQU (0x0000000C)      ; PLL used as system clock

; HPRE configuration
RCC_CFGR_HPRE               EQU (0x000000F0)      ; HPRE[3:0] bits (AHB prescaler)
RCC_CFGR_HPRE_0             EQU (0x00000010)      ;Bit 0
RCC_CFGR_HPRE_1             EQU (0x00000020)      ;Bit 1
RCC_CFGR_HPRE_2             EQU (0x00000040)      ;Bit 2
RCC_CFGR_HPRE_3             EQU (0x00000080)      ;Bit 3

RCC_CFGR_HPRE_DIV1          EQU (0x00000000)      ; SYSCLK not divided
RCC_CFGR_HPRE_DIV2          EQU (0x00000080)      ; SYSCLK divided by 2
RCC_CFGR_HPRE_DIV4          EQU (0x00000090)      ; SYSCLK divided by 4
RCC_CFGR_HPRE_DIV8          EQU (0x000000A0)      ; SYSCLK divided by 8
RCC_CFGR_HPRE_DIV16         EQU (0x000000B0)      ; SYSCLK divided by 16
RCC_CFGR_HPRE_DIV64         EQU (0x000000C0)      ; SYSCLK divided by 64
RCC_CFGR_HPRE_DIV128        EQU (0x000000D0)      ; SYSCLK divided by 128
RCC_CFGR_HPRE_DIV256        EQU (0x000000E0)      ; SYSCLK divided by 256
RCC_CFGR_HPRE_DIV512        EQU (0x000000F0)      ; SYSCLK divided by 512

; PPRE1 configuration
RCC_CFGR_PPRE1              EQU (0x00000700)      ; PRE1[2:0] bits (APB2 prescaler)
RCC_CFGR_PPRE1_0            EQU (0x00000100)      ;Bit 0
RCC_CFGR_PPRE1_1            EQU (0x00000200)      ;Bit 1
RCC_CFGR_PPRE1_2            EQU (0x00000400)      ;Bit 2

RCC_CFGR_PPRE1_DIV1         EQU (0x00000000)      ; HCLK not divided
RCC_CFGR_PPRE1_DIV2         EQU (0x00000400)      ; HCLK divided by 2
RCC_CFGR_PPRE1_DIV4         EQU (0x00000500)      ; HCLK divided by 4
RCC_CFGR_PPRE1_DIV8         EQU (0x00000600)      ; HCLK divided by 8
RCC_CFGR_PPRE1_DIV16        EQU (0x00000700)      ; HCLK divided by 16

; PPRE2 configuration
RCC_CFGR_PPRE2              EQU (0x00003800)      ; PRE2[2:0] bits (APB2 prescaler)
RCC_CFGR_PPRE2_0            EQU (0x00000800)      ;Bit 0
RCC_CFGR_PPRE2_1            EQU (0x00001000)      ;Bit 1
RCC_CFGR_PPRE2_2            EQU (0x00002000)      ;Bit 2

RCC_CFGR_PPRE2_DIV1         EQU (0x00000000)      ; HCLK not divided
RCC_CFGR_PPRE2_DIV2         EQU (0x00002000)      ; HCLK divided by 2
RCC_CFGR_PPRE2_DIV4         EQU (0x00002800)      ; HCLK divided by 4
RCC_CFGR_PPRE2_DIV8         EQU (0x00003000)      ; HCLK divided by 8
RCC_CFGR_PPRE2_DIV16        EQU (0x00003800)      ; HCLK divided by 16

RCC_CFGR_STOPWUCK           EQU (0x00008000)      ; Wake Up from stop and CSS backup clock selection

; MCOSEL configuration
RCC_CFGR_MCOSEL             EQU (0x07000000)      ; MCOSEL [2:0] bits (Clock output selection)
RCC_CFGR_MCOSEL_0           EQU (0x01000000)      ;Bit 0
RCC_CFGR_MCOSEL_1           EQU (0x02000000)      ;Bit 1
RCC_CFGR_MCOSEL_2           EQU (0x04000000)      ;Bit 2

RCC_CFGR_MCO_PRE            EQU (0x70000000)      ; MCO prescaler
RCC_CFGR_MCO_PRE_1          EQU (0x00000000)      ; MCO is divided by 1
RCC_CFGR_MCO_PRE_2          EQU (0x10000000)      ; MCO is divided by 2
RCC_CFGR_MCO_PRE_4          EQU (0x20000000)      ; MCO is divided by 4
RCC_CFGR_MCO_PRE_8          EQU (0x30000000)      ; MCO is divided by 8
RCC_CFGR_MCO_PRE_16         EQU (0x40000000)      ; MCO is divided by 16

; ********************  Bit definition for RCC_CIER register  *****************
RCC_CIER_LSIRDYIE           EQU (0x00000001)
RCC_CIER_LSERDYIE           EQU (0x00000002)
RCC_CIER_MSIRDYIE           EQU (0x00000004)
RCC_CIER_HSIRDYIE           EQU (0x00000008)
RCC_CIER_HSERDYIE           EQU (0x00000010)
RCC_CIER_PLLRDYIE           EQU (0x00000020)
RCC_CIER_PLLSAI1RDYIE       EQU (0x00000040)
RCC_CIER_PLLSAI2RDYIE       EQU (0x00000080)
RCC_CIER_LSECSSIE           EQU (0x00000200)

; ********************  Bit definition for RCC_CIFR register  *****************
RCC_CIFR_LSIRDYF            EQU (0x00000001)
RCC_CIFR_LSERDYF            EQU (0x00000002)
RCC_CIFR_MSIRDYF            EQU (0x00000004)
RCC_CIFR_HSIRDYF            EQU (0x00000008)
RCC_CIFR_HSERDYF            EQU (0x00000010)
RCC_CIFR_PLLRDYF            EQU (0x00000020)
RCC_CIFR_PLLSAI1RDYF        EQU (0x00000040)
RCC_CIFR_PLLSAI2RDYF        EQU (0x00000080)
RCC_CIFR_CSSF               EQU (0x00000100)
RCC_CIFR_LSECSSF            EQU (0x00000200)

; ********************  Bit definition for RCC_CICR register  *****************
RCC_CICR_LSIRDYC            EQU (0x00000001)
RCC_CICR_LSERDYC            EQU (0x00000002)
RCC_CICR_MSIRDYC            EQU (0x00000004)
RCC_CICR_HSIRDYC            EQU (0x00000008)
RCC_CICR_HSERDYC            EQU (0x00000010)
RCC_CICR_PLLRDYC            EQU (0x00000020)
RCC_CICR_PLLSAI1RDYC        EQU (0x00000040)
RCC_CICR_PLLSAI2RDYC        EQU (0x00000080)
RCC_CICR_CSSC               EQU (0x00000100)
RCC_CICR_LSECSSC            EQU (0x00000200)

; ********************  Bit definition for RCC_AHB1ENR register  **************
RCC_AHB1ENR_GPIOAEN         EQU (0x00000001)
RCC_AHB1ENR_GPIOBEN         EQU (0x00000002)
RCC_AHB1ENR_GPIOCEN         EQU (0x00000004)
RCC_AHB1ENR_GPIODEN         EQU (0x00000008)
RCC_AHB1ENR_GPIOEEN         EQU (0x00000010)
RCC_AHB1ENR_GPIOHEN         EQU (0x00000080)
RCC_AHB1ENR_CRCEN         	EQU (0x00001000)
RCC_AHB1ENR_DMA1EN          EQU (0x00200000)
RCC_AHB1ENR_DMA2EN          EQU (0x00400000)

; ********************  Bit definition for RCC_APB1ENR register  **************
RCC_APB1ENR_TIM2EN         EQU (0x00000001)
RCC_APB1ENR_TIM3EN         EQU (0x00000002)
RCC_APB1ENR_TIM4EN         EQU (0x00000004)
RCC_APB1ENR_TIM5EN         EQU (0x00000008)
RCC_APB1ENR_WWDGEN         EQU (0x00000800)
RCC_APB1ENR_SPI2EN         EQU (0x00004000)
RCC_APB1ENR_SPI3EN         EQU (0x00008000)
RCC_APB1ENR_USART2EN       EQU (0x00020000)
RCC_APB1ENR_I2C1EN         EQU (0x00200000)
RCC_APB1ENR_I2C2EN         EQU (0x00400000)
RCC_APB1ENR_I2C3EN         EQU (0x00800000)
RCC_APB1ENR_PWREN          EQU (0x10000000)

; ********************  Bit definition for RCC_APB2ENR register  **************
RCC_APB2ENR_TIM1EN        	EQU (0x00000001)
RCC_APB2ENR_USART1EN        EQU (0x00000010)
RCC_APB2ENR_USART6EN        EQU (0x00000020)
RCC_APB2ENR_ADC1EN	        EQU (0x00000100)
RCC_APB2ENR_SDIOEN          EQU (0x00000800)
RCC_APB2ENR_SPI1EN          EQU (0x00001000)
RCC_APB2ENR_SPI4EN        	EQU (0x00002000)
RCC_APB2ENR_SYSCFGEN	    EQU (0x00004000)
RCC_APB2ENR_TIM9EN         	EQU (0x00010000)
RCC_APB2ENR_TIM10EN         EQU (0x00020000)
RCC_APB2ENR_TIM11EN         EQU (0x00040000)
RCC_APB2ENR_SPI5EN          EQU (0x00100000)


; ********************  Bit definition for RCC_CSR register  ******************
RCC_CSR_LSION               EQU (0x00000001)
RCC_CSR_LSIRDY              EQU (0x00000002)
RCC_CSR_RMVF                EQU (0x01000000)
RCC_CSR_BORRSTF             EQU (0x02000000)
RCC_CSR_PINRSTF             EQU (0x04000000)
RCC_CSR_PORRSTF             EQU (0x08000000)
RCC_CSR_SFTRSTF             EQU (0x10000000)
RCC_CSR_IWDGRSTF            EQU (0x20000000)
RCC_CSR_WWDGRSTF            EQU (0x40000000)
RCC_CSR_LPWRRSTF            EQU (0x80000000)

; *****************************************************************************
;
;                            General Purpose I/O
;
; *****************************************************************************
; ******************  Bits definition for GPIO_MODER register  ****************
GPIO_MODER_MODER0           EQU (0x00000003)
GPIO_MODER_MODER0_0         EQU (0x00000001)
GPIO_MODER_MODER0_1         EQU (0x00000002)
GPIO_MODER_MODER1           EQU (0x0000000C)
GPIO_MODER_MODER1_0         EQU (0x00000004)
GPIO_MODER_MODER1_1         EQU (0x00000008)
GPIO_MODER_MODER2           EQU (0x00000030)
GPIO_MODER_MODER2_0         EQU (0x00000010)
GPIO_MODER_MODER2_1         EQU (0x00000020)
GPIO_MODER_MODER3           EQU (0x000000C0)
GPIO_MODER_MODER3_0         EQU (0x00000040)
GPIO_MODER_MODER3_1         EQU (0x00000080)
GPIO_MODER_MODER4           EQU (0x00000300)
GPIO_MODER_MODER4_0         EQU (0x00000100)
GPIO_MODER_MODER4_1         EQU (0x00000200)
GPIO_MODER_MODER5           EQU (0x00000C00)
GPIO_MODER_MODER5_0         EQU (0x00000400)
GPIO_MODER_MODER5_1         EQU (0x00000800)
GPIO_MODER_MODER6           EQU (0x00003000)
GPIO_MODER_MODER6_0         EQU (0x00001000)
GPIO_MODER_MODER6_1         EQU (0x00002000)
GPIO_MODER_MODER7           EQU (0x0000C000)
GPIO_MODER_MODER7_0         EQU (0x00004000)
GPIO_MODER_MODER7_1         EQU (0x00008000)
GPIO_MODER_MODER8           EQU (0x00030000)
GPIO_MODER_MODER8_0         EQU (0x00010000)
GPIO_MODER_MODER8_1         EQU (0x00020000)
GPIO_MODER_MODER9           EQU (0x000C0000)
GPIO_MODER_MODER9_0         EQU (0x00040000)
GPIO_MODER_MODER9_1         EQU (0x00080000)
GPIO_MODER_MODER10          EQU (0x00300000)
GPIO_MODER_MODER10_0        EQU (0x00100000)
GPIO_MODER_MODER10_1        EQU (0x00200000)
GPIO_MODER_MODER11          EQU (0x00C00000)
GPIO_MODER_MODER11_0        EQU (0x00400000)
GPIO_MODER_MODER11_1        EQU (0x00800000)
GPIO_MODER_MODER12          EQU (0x03000000)
GPIO_MODER_MODER12_0        EQU (0x01000000)
GPIO_MODER_MODER12_1        EQU (0x02000000)
GPIO_MODER_MODER13          EQU (0x0C000000)
GPIO_MODER_MODER13_0        EQU (0x04000000)
GPIO_MODER_MODER13_1        EQU (0x08000000)
GPIO_MODER_MODER14          EQU (0x30000000)
GPIO_MODER_MODER14_0        EQU (0x10000000)
GPIO_MODER_MODER14_1        EQU (0x20000000)
GPIO_MODER_MODER15          EQU (0xC0000000)
GPIO_MODER_MODER15_0        EQU (0x40000000)
GPIO_MODER_MODER15_1        EQU (0x80000000)

; ******************  Bits definition for GPIO_OTYPER register  ***************
GPIO_OTYPER_OT_0            EQU (0x00000001)
GPIO_OTYPER_OT_1            EQU (0x00000002)
GPIO_OTYPER_OT_2            EQU (0x00000004)
GPIO_OTYPER_OT_3            EQU (0x00000008)
GPIO_OTYPER_OT_4            EQU (0x00000010)
GPIO_OTYPER_OT_5            EQU (0x00000020)
GPIO_OTYPER_OT_6            EQU (0x00000040)
GPIO_OTYPER_OT_7            EQU (0x00000080)
GPIO_OTYPER_OT_8            EQU (0x00000100)
GPIO_OTYPER_OT_9            EQU (0x00000200)
GPIO_OTYPER_OT_10           EQU (0x00000400)
GPIO_OTYPER_OT_11           EQU (0x00000800)
GPIO_OTYPER_OT_12           EQU (0x00001000)
GPIO_OTYPER_OT_13           EQU (0x00002000)
GPIO_OTYPER_OT_14           EQU (0x00004000)
GPIO_OTYPER_OT_15           EQU (0x00008000)

; ******************  Bits definition for GPIO_OSPEEDR register  **************
GPIO_OSPEEDER_OSPEEDR0      EQU (0x00000003)
GPIO_OSPEEDER_OSPEEDR0_0    EQU (0x00000001)
GPIO_OSPEEDER_OSPEEDR0_1    EQU (0x00000002)
GPIO_OSPEEDER_OSPEEDR1      EQU (0x0000000C)
GPIO_OSPEEDER_OSPEEDR1_0    EQU (0x00000004)
GPIO_OSPEEDER_OSPEEDR1_1    EQU (0x00000008)
GPIO_OSPEEDER_OSPEEDR2      EQU (0x00000030)
GPIO_OSPEEDER_OSPEEDR2_0    EQU (0x00000010)
GPIO_OSPEEDER_OSPEEDR2_1    EQU (0x00000020)
GPIO_OSPEEDER_OSPEEDR3      EQU (0x000000C0)
GPIO_OSPEEDER_OSPEEDR3_0    EQU (0x00000040)
GPIO_OSPEEDER_OSPEEDR3_1    EQU (0x00000080)
GPIO_OSPEEDER_OSPEEDR4      EQU (0x00000300)
GPIO_OSPEEDER_OSPEEDR4_0    EQU (0x00000100)
GPIO_OSPEEDER_OSPEEDR4_1    EQU (0x00000200)
GPIO_OSPEEDER_OSPEEDR5      EQU (0x00000C00)
GPIO_OSPEEDER_OSPEEDR5_0    EQU (0x00000400)
GPIO_OSPEEDER_OSPEEDR5_1    EQU (0x00000800)
GPIO_OSPEEDER_OSPEEDR6      EQU (0x00003000)
GPIO_OSPEEDER_OSPEEDR6_0    EQU (0x00001000)
GPIO_OSPEEDER_OSPEEDR6_1    EQU (0x00002000)
GPIO_OSPEEDER_OSPEEDR7      EQU (0x0000C000)
GPIO_OSPEEDER_OSPEEDR7_0    EQU (0x00004000)
GPIO_OSPEEDER_OSPEEDR7_1    EQU (0x00008000)
GPIO_OSPEEDER_OSPEEDR8      EQU (0x00030000)
GPIO_OSPEEDER_OSPEEDR8_0    EQU (0x00010000)
GPIO_OSPEEDER_OSPEEDR8_1    EQU (0x00020000)
GPIO_OSPEEDER_OSPEEDR9      EQU (0x000C0000)
GPIO_OSPEEDER_OSPEEDR9_0    EQU (0x00040000)
GPIO_OSPEEDER_OSPEEDR9_1    EQU (0x00080000)
GPIO_OSPEEDER_OSPEEDR10     EQU (0x00300000)
GPIO_OSPEEDER_OSPEEDR10_0   EQU (0x00100000)
GPIO_OSPEEDER_OSPEEDR10_1   EQU (0x00200000)
GPIO_OSPEEDER_OSPEEDR11     EQU (0x00C00000)
GPIO_OSPEEDER_OSPEEDR11_0   EQU (0x00400000)
GPIO_OSPEEDER_OSPEEDR11_1   EQU (0x00800000)
GPIO_OSPEEDER_OSPEEDR12     EQU (0x03000000)
GPIO_OSPEEDER_OSPEEDR12_0   EQU (0x01000000)
GPIO_OSPEEDER_OSPEEDR12_1   EQU (0x02000000)
GPIO_OSPEEDER_OSPEEDR13     EQU (0x0C000000)
GPIO_OSPEEDER_OSPEEDR13_0   EQU (0x04000000)
GPIO_OSPEEDER_OSPEEDR13_1   EQU (0x08000000)
GPIO_OSPEEDER_OSPEEDR14     EQU (0x30000000)
GPIO_OSPEEDER_OSPEEDR14_0   EQU (0x10000000)
GPIO_OSPEEDER_OSPEEDR14_1   EQU (0x20000000)
GPIO_OSPEEDER_OSPEEDR15     EQU (0xC0000000)
GPIO_OSPEEDER_OSPEEDR15_0   EQU (0x40000000)
GPIO_OSPEEDER_OSPEEDR15_1   EQU (0x80000000)

; ******************  Bits definition for GPIO_PUPDR register  ****************
GPIO_PUPDR_PUPDR0           EQU (0x00000003)
GPIO_PUPDR_PUPDR0_0         EQU (0x00000001)
GPIO_PUPDR_PUPDR0_1         EQU (0x00000002)
GPIO_PUPDR_PUPDR1           EQU (0x0000000C)
GPIO_PUPDR_PUPDR1_0         EQU (0x00000004)
GPIO_PUPDR_PUPDR1_1         EQU (0x00000008)
GPIO_PUPDR_PUPDR2           EQU (0x00000030)
GPIO_PUPDR_PUPDR2_0         EQU (0x00000010)
GPIO_PUPDR_PUPDR2_1         EQU (0x00000020)
GPIO_PUPDR_PUPDR3           EQU (0x000000C0)
GPIO_PUPDR_PUPDR3_0         EQU (0x00000040)
GPIO_PUPDR_PUPDR3_1         EQU (0x00000080)
GPIO_PUPDR_PUPDR4           EQU (0x00000300)
GPIO_PUPDR_PUPDR4_0         EQU (0x00000100)
GPIO_PUPDR_PUPDR4_1         EQU (0x00000200)
GPIO_PUPDR_PUPDR5           EQU (0x00000C00)
GPIO_PUPDR_PUPDR5_0         EQU (0x00000400)
GPIO_PUPDR_PUPDR5_1         EQU (0x00000800)
GPIO_PUPDR_PUPDR6           EQU (0x00003000)
GPIO_PUPDR_PUPDR6_0         EQU (0x00001000)
GPIO_PUPDR_PUPDR6_1         EQU (0x00002000)
GPIO_PUPDR_PUPDR7           EQU (0x0000C000)
GPIO_PUPDR_PUPDR7_0         EQU (0x00004000)
GPIO_PUPDR_PUPDR7_1         EQU (0x00008000)
GPIO_PUPDR_PUPDR8           EQU (0x00030000)
GPIO_PUPDR_PUPDR8_0         EQU (0x00010000)
GPIO_PUPDR_PUPDR8_1         EQU (0x00020000)
GPIO_PUPDR_PUPDR9           EQU (0x000C0000)
GPIO_PUPDR_PUPDR9_0         EQU (0x00040000)
GPIO_PUPDR_PUPDR9_1         EQU (0x00080000)
GPIO_PUPDR_PUPDR10          EQU (0x00300000)
GPIO_PUPDR_PUPDR10_0        EQU (0x00100000)
GPIO_PUPDR_PUPDR10_1        EQU (0x00200000)
GPIO_PUPDR_PUPDR11          EQU (0x00C00000)
GPIO_PUPDR_PUPDR11_0        EQU (0x00400000)
GPIO_PUPDR_PUPDR11_1        EQU (0x00800000)
GPIO_PUPDR_PUPDR12          EQU (0x03000000)
GPIO_PUPDR_PUPDR12_0        EQU (0x01000000)
GPIO_PUPDR_PUPDR12_1        EQU (0x02000000)
GPIO_PUPDR_PUPDR13          EQU (0x0C000000)
GPIO_PUPDR_PUPDR13_0        EQU (0x04000000)
GPIO_PUPDR_PUPDR13_1        EQU (0x08000000)
GPIO_PUPDR_PUPDR14          EQU (0x30000000)
GPIO_PUPDR_PUPDR14_0        EQU (0x10000000)
GPIO_PUPDR_PUPDR14_1        EQU (0x20000000)
GPIO_PUPDR_PUPDR15          EQU (0xC0000000)
GPIO_PUPDR_PUPDR15_0        EQU (0x40000000)
GPIO_PUPDR_PUPDR15_1        EQU (0x80000000)

; ******************  Bits definition for GPIO_IDR register  ******************
GPIO_IDR_IDR_0              EQU (0x00000001)
GPIO_IDR_IDR_1              EQU (0x00000002)
GPIO_IDR_IDR_2              EQU (0x00000004)
GPIO_IDR_IDR_3              EQU (0x00000008)
GPIO_IDR_IDR_4              EQU (0x00000010)
GPIO_IDR_IDR_5              EQU (0x00000020)
GPIO_IDR_IDR_6              EQU (0x00000040)
GPIO_IDR_IDR_7              EQU (0x00000080)
GPIO_IDR_IDR_8              EQU (0x00000100)
GPIO_IDR_IDR_9              EQU (0x00000200)
GPIO_IDR_IDR_10             EQU (0x00000400)
GPIO_IDR_IDR_11             EQU (0x00000800)
GPIO_IDR_IDR_12             EQU (0x00001000)
GPIO_IDR_IDR_13             EQU (0x00002000)
GPIO_IDR_IDR_14             EQU (0x00004000)
GPIO_IDR_IDR_15             EQU (0x00008000)

; Old GPIO_IDR register bits definition, maintained for legacy purpose
GPIO_OTYPER_IDR_0           EQU GPIO_IDR_IDR_0
GPIO_OTYPER_IDR_1           EQU GPIO_IDR_IDR_1
GPIO_OTYPER_IDR_2           EQU GPIO_IDR_IDR_2
GPIO_OTYPER_IDR_3           EQU GPIO_IDR_IDR_3
GPIO_OTYPER_IDR_4           EQU GPIO_IDR_IDR_4
GPIO_OTYPER_IDR_5           EQU GPIO_IDR_IDR_5
GPIO_OTYPER_IDR_6           EQU GPIO_IDR_IDR_6
GPIO_OTYPER_IDR_7           EQU GPIO_IDR_IDR_7
GPIO_OTYPER_IDR_8           EQU GPIO_IDR_IDR_8
GPIO_OTYPER_IDR_9           EQU GPIO_IDR_IDR_9
GPIO_OTYPER_IDR_10          EQU GPIO_IDR_IDR_10
GPIO_OTYPER_IDR_11          EQU GPIO_IDR_IDR_11
GPIO_OTYPER_IDR_12          EQU GPIO_IDR_IDR_12
GPIO_OTYPER_IDR_13          EQU GPIO_IDR_IDR_13
GPIO_OTYPER_IDR_14          EQU GPIO_IDR_IDR_14
GPIO_OTYPER_IDR_15          EQU GPIO_IDR_IDR_15

; ******************  Bits definition for GPIO_ODR register  ******************
GPIO_ODR_ODR_0              EQU (0x00000001)
GPIO_ODR_ODR_1              EQU (0x00000002)
GPIO_ODR_ODR_2              EQU (0x00000004)
GPIO_ODR_ODR_3              EQU (0x00000008)
GPIO_ODR_ODR_4              EQU (0x00000010)
GPIO_ODR_ODR_5              EQU (0x00000020)
GPIO_ODR_ODR_6              EQU (0x00000040)
GPIO_ODR_ODR_7              EQU (0x00000080)
GPIO_ODR_ODR_8              EQU (0x00000100)
GPIO_ODR_ODR_9              EQU (0x00000200)
GPIO_ODR_ODR_10             EQU (0x00000400)
GPIO_ODR_ODR_11             EQU (0x00000800)
GPIO_ODR_ODR_12             EQU (0x00001000)
GPIO_ODR_ODR_13             EQU (0x00002000)
GPIO_ODR_ODR_14             EQU (0x00004000)
GPIO_ODR_ODR_15             EQU (0x00008000)

; Old GPIO_ODR register bits definition, maintained for legacy purpose
GPIO_OTYPER_ODR_0           EQU GPIO_ODR_ODR_0
GPIO_OTYPER_ODR_1           EQU GPIO_ODR_ODR_1
GPIO_OTYPER_ODR_2           EQU GPIO_ODR_ODR_2
GPIO_OTYPER_ODR_3           EQU GPIO_ODR_ODR_3
GPIO_OTYPER_ODR_4           EQU GPIO_ODR_ODR_4
GPIO_OTYPER_ODR_5           EQU GPIO_ODR_ODR_5
GPIO_OTYPER_ODR_6           EQU GPIO_ODR_ODR_6
GPIO_OTYPER_ODR_7           EQU GPIO_ODR_ODR_7
GPIO_OTYPER_ODR_8           EQU GPIO_ODR_ODR_8
GPIO_OTYPER_ODR_9           EQU GPIO_ODR_ODR_9
GPIO_OTYPER_ODR_10          EQU GPIO_ODR_ODR_10
GPIO_OTYPER_ODR_11          EQU GPIO_ODR_ODR_11
GPIO_OTYPER_ODR_12          EQU GPIO_ODR_ODR_12
GPIO_OTYPER_ODR_13          EQU GPIO_ODR_ODR_13
GPIO_OTYPER_ODR_14          EQU GPIO_ODR_ODR_14
GPIO_OTYPER_ODR_15          EQU GPIO_ODR_ODR_15

; ******************  Bits definition for GPIO_BSRR register  *****************
GPIO_BSRR_BS_0              EQU (0x00000001)
GPIO_BSRR_BS_1              EQU (0x00000002)
GPIO_BSRR_BS_2              EQU (0x00000004)
GPIO_BSRR_BS_3              EQU (0x00000008)
GPIO_BSRR_BS_4              EQU (0x00000010)
GPIO_BSRR_BS_5              EQU (0x00000020)
GPIO_BSRR_BS_6              EQU (0x00000040)
GPIO_BSRR_BS_7              EQU (0x00000080)
GPIO_BSRR_BS_8              EQU (0x00000100)
GPIO_BSRR_BS_9              EQU (0x00000200)
GPIO_BSRR_BS_10             EQU (0x00000400)
GPIO_BSRR_BS_11             EQU (0x00000800)
GPIO_BSRR_BS_12             EQU (0x00001000)
GPIO_BSRR_BS_13             EQU (0x00002000)
GPIO_BSRR_BS_14             EQU (0x00004000)
GPIO_BSRR_BS_15             EQU (0x00008000)
GPIO_BSRR_BR_0              EQU (0x00010000)
GPIO_BSRR_BR_1              EQU (0x00020000)
GPIO_BSRR_BR_2              EQU (0x00040000)
GPIO_BSRR_BR_3              EQU (0x00080000)
GPIO_BSRR_BR_4              EQU (0x00100000)
GPIO_BSRR_BR_5              EQU (0x00200000)
GPIO_BSRR_BR_6              EQU (0x00400000)
GPIO_BSRR_BR_7              EQU (0x00800000)
GPIO_BSRR_BR_8              EQU (0x01000000)
GPIO_BSRR_BR_9              EQU (0x02000000)
GPIO_BSRR_BR_10             EQU (0x04000000)
GPIO_BSRR_BR_11             EQU (0x08000000)
GPIO_BSRR_BR_12             EQU (0x10000000)
GPIO_BSRR_BR_13             EQU (0x20000000)
GPIO_BSRR_BR_14             EQU (0x40000000)
GPIO_BSRR_BR_15             EQU (0x80000000)

; ******************  Bits definition for GPIO_BRR register  *****************
GPIO_BRR_BR_0               EQU (0x00000001)
GPIO_BRR_BR_1               EQU (0x00000002)
GPIO_BRR_BR_2               EQU (0x00000004)
GPIO_BRR_BR_3               EQU (0x00000008)
GPIO_BRR_BR_4               EQU (0x00000010)
GPIO_BRR_BR_5               EQU (0x00000020)
GPIO_BRR_BR_6               EQU (0x00000040)
GPIO_BRR_BR_7               EQU (0x00000080)
GPIO_BRR_BR_8               EQU (0x00000100)
GPIO_BRR_BR_9               EQU (0x00000200)
GPIO_BRR_BR_10              EQU (0x00000400)
GPIO_BRR_BR_11              EQU (0x00000800)
GPIO_BRR_BR_12              EQU (0x00001000)
GPIO_BRR_BR_13              EQU (0x00002000)
GPIO_BRR_BR_14              EQU (0x00004000)
GPIO_BRR_BR_15              EQU (0x00008000)

; ****************** Bit definition for GPIO_LCKR register ********************
GPIO_LCKR_LCK0              EQU (0x00000001)
GPIO_LCKR_LCK1              EQU (0x00000002)
GPIO_LCKR_LCK2              EQU (0x00000004)
GPIO_LCKR_LCK3              EQU (0x00000008)
GPIO_LCKR_LCK4              EQU (0x00000010)
GPIO_LCKR_LCK5              EQU (0x00000020)
GPIO_LCKR_LCK6              EQU (0x00000040)
GPIO_LCKR_LCK7              EQU (0x00000080)
GPIO_LCKR_LCK8              EQU (0x00000100)
GPIO_LCKR_LCK9              EQU (0x00000200)
GPIO_LCKR_LCK10             EQU (0x00000400)
GPIO_LCKR_LCK11             EQU (0x00000800)
GPIO_LCKR_LCK12             EQU (0x00001000)
GPIO_LCKR_LCK13             EQU (0x00002000)
GPIO_LCKR_LCK14             EQU (0x00004000)
GPIO_LCKR_LCK15             EQU (0x00008000)
GPIO_LCKR_LCKK              EQU (0x00010000)

; ****************** Bit definition for GPIO_AFRL register  *******************
GPIO_AFRL_AFRL0              EQU (0x0000000F)
GPIO_AFRL_AFRL1              EQU (0x000000F0)
GPIO_AFRL_AFRL2              EQU (0x00000F00)
GPIO_AFRL_AFRL3              EQU (0x0000F000)
GPIO_AFRL_AFRL4              EQU (0x000F0000)
GPIO_AFRL_AFRL5              EQU (0x00F00000)
GPIO_AFRL_AFRL6              EQU (0x0F000000)
GPIO_AFRL_AFRL7              EQU (0xF0000000)

; ****************** Bit definition for GPIO_AFRH register  *******************
GPIO_AFRH_AFRH0              EQU (0x0000000F)
GPIO_AFRH_AFRH1              EQU (0x000000F0)
GPIO_AFRH_AFRH2              EQU (0x00000F00)
GPIO_AFRH_AFRH3              EQU (0x0000F000)
GPIO_AFRH_AFRH4              EQU (0x000F0000)
GPIO_AFRH_AFRH5              EQU (0x00F00000)
GPIO_AFRH_AFRH6              EQU (0x0F000000)
GPIO_AFRH_AFRH7              EQU (0xF0000000)

; ******************  Bits definition for GPIO_ASCR register  ******************
GPIO_ASCR_EN_0               EQU (0x00000001)
GPIO_ASCR_EN_1               EQU (0x00000002)
GPIO_ASCR_EN_2               EQU (0x00000004)
GPIO_ASCR_EN_3               EQU (0x00000008)
GPIO_ASCR_EN_4               EQU (0x00000010)
GPIO_ASCR_EN_5               EQU (0x00000020)
GPIO_ASCR_EN_6               EQU (0x00000040)
GPIO_ASCR_EN_7               EQU (0x00000080)
GPIO_ASCR_EN_8               EQU (0x00000100)
GPIO_ASCR_EN_9               EQU (0x00000200)
GPIO_ASCR_EN_10              EQU (0x00000400)
GPIO_ASCR_EN_11              EQU (0x00000800)
GPIO_ASCR_EN_12              EQU (0x00001000)
GPIO_ASCR_EN_13              EQU (0x00002000)
GPIO_ASCR_EN_14              EQU (0x00004000)
GPIO_ASCR_EN_15              EQU (0x00008000)

	END