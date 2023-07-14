/*
 * tm4c.h
 *
 *  Created on: 27 jul 2022
 *      Author: rober
 */

#ifndef TM4C_H_
#define TM4C_H_


#define SYSCTL_RCGCGPIO_R       (*((volatile uint32_t *)0x400FE608)) //Reloj del puerto
#define SYSCTL_RCGCI2C_R        (*((volatile uint32_t *)0x400FE620)) //Reloj de I2C
#define SYSCTL_PRGPIO_R        (*((volatile uint32_t *)0x400FEA08)) //Bandera de "Peripherial Ready"

#define SYSCTL_RCGCUART_R       (*((volatile uint32_t *)0x400FE618))
#define SYSCTL_PRUART_R         (*((volatile uint32_t *)0x400FEA18))

//REGISTROS DEL PUERTO B
#define GPIO_PORTB_DATA_R   (*((volatile uint32_t *)0x400593FC)) //Para los datos del puerto
#define GPIO_PORTB_DIR_R    (*((volatile uint32_t *)0x40059400)) //Para seleccionar función
#define GPIO_PORTB_AFSEL_R  (*((volatile uint32_t *)0x40059420)) //Para seleccionar función alterna
#define GPIO_PORTB_ODR_R    (*((volatile uint32_t *)0x4005950C)) //Para activar el Open Drain
#define GPIO_PORTB_DEN_R    (*((volatile uint32_t *)0x4005951C)) //Para activar función digital
#define GPIO_PORTB_PCTL_R   (*((volatile uint32_t *)0x4005952C)) //Para el control del puerto

//REGISTROS DEL MÓUDLO I2C
#define I2C0_MSA_R              (*((volatile uint32_t *)0x40020000)) //I2C Master Slave Adress
#define I2C0_MCS_R              (*((volatile uint32_t *)0x40020004)) //I2C Master Control Status
#define I2C0_MDR_R              (*((volatile uint32_t *)0x40020008)) //I2C Master Data Register
#define I2C0_MTPR_R             (*((volatile uint32_t *)0x4002000C)) //I2C Master Time Period
#define I2C0_MCR_R              (*((volatile uint32_t *)0x40020020)) //I2C Master Congirutation Register



#define I2C_MCS_ACK 0x00000008 //Transmmitter Acknowledge Enable
#define I2C_MCS_DATACK 0x00000008 // Data Acknowledge Enable
#define I2C_MCS_ADRACK 0x00000004 // Acknowledge Address
#define I2C_MCS_STOP 0x00000004 // Generate STOP
#define I2C_MCS_START 0x00000002 // Generate START
#define I2C_MCS_ERROR 0x00000002 // Error
#define I2C_MCS_RUN 0x00000001 // I2C Master Enable
#define MAXRETRIES 5 // number of receive attempts before giving up


/////// UART 0


#define UART0_DR_R              (*((volatile uint32_t *)0x4000C000))
#define UART0_RSR_R             (*((volatile uint32_t *)0x4000C004))
#define UART0_ECR_R             (*((volatile uint32_t *)0x4000C004))
#define UART0_FR_R              (*((volatile uint32_t *)0x4000C018))
#define UART0_ILPR_R            (*((volatile uint32_t *)0x4000C020))
#define UART0_IBRD_R            (*((volatile uint32_t *)0x4000C024))
#define UART0_FBRD_R            (*((volatile uint32_t *)0x4000C028))
#define UART0_LCRH_R            (*((volatile uint32_t *)0x4000C02C))
#define UART0_CTL_R             (*((volatile uint32_t *)0x4000C030))
#define UART0_IFLS_R            (*((volatile uint32_t *)0x4000C034))
#define UART0_IM_R              (*((volatile uint32_t *)0x4000C038))
#define UART0_RIS_R             (*((volatile uint32_t *)0x4000C03C))
#define UART0_MIS_R             (*((volatile uint32_t *)0x4000C040))
#define UART0_ICR_R             (*((volatile uint32_t *)0x4000C044))
#define UART0_DMACTL_R          (*((volatile uint32_t *)0x4000C048))
#define UART0_9BITADDR_R        (*((volatile uint32_t *)0x4000C0A4))
#define UART0_9BITAMASK_R       (*((volatile uint32_t *)0x4000C0A8))
#define UART0_PP_R              (*((volatile uint32_t *)0x4000CFC0))
#define UART0_CC_R              (*((volatile uint32_t *)0x4000CFC8))

#define UART_FR_RI              0x00000100  // Ring Indicator
#define UART_FR_TXFE            0x00000080  // UART Transmit FIFO Empty
#define UART_FR_RXFF            0x00000040  // UART Receive FIFO Full
#define UART_FR_TXFF            0x00000020  // UART Transmit FIFO Full
#define UART_FR_RXFE            0x00000010  // UART Receive FIFO Empty
#define UART_FR_BUSY            0x00000008  // UART Busy
#define UART_FR_DCD             0x00000004  // Data Carrier Detect
#define UART_FR_DSR             0x00000002  // Data Set Ready
#define UART_FR_CTS             0x00000001  // Clear To Send

///////////GPIO PORT A

#define GPIO_PORTA_AHB_DATA_BITS_R                                            \
                                ((volatile uint32_t *)0x40058000)
#define GPIO_PORTA_AHB_DATA_R   (*((volatile uint32_t *)0x400583FC))
#define GPIO_PORTA_AHB_DIR_R    (*((volatile uint32_t *)0x40058400))
#define GPIO_PORTA_AHB_IS_R     (*((volatile uint32_t *)0x40058404))
#define GPIO_PORTA_AHB_IBE_R    (*((volatile uint32_t *)0x40058408))
#define GPIO_PORTA_AHB_IEV_R    (*((volatile uint32_t *)0x4005840C))
#define GPIO_PORTA_AHB_IM_R     (*((volatile uint32_t *)0x40058410))
#define GPIO_PORTA_AHB_RIS_R    (*((volatile uint32_t *)0x40058414))
#define GPIO_PORTA_AHB_MIS_R    (*((volatile uint32_t *)0x40058418))
#define GPIO_PORTA_AHB_ICR_R    (*((volatile uint32_t *)0x4005841C))
#define GPIO_PORTA_AHB_AFSEL_R  (*((volatile uint32_t *)0x40058420))
#define GPIO_PORTA_AHB_DR2R_R   (*((volatile uint32_t *)0x40058500))
#define GPIO_PORTA_AHB_DR4R_R   (*((volatile uint32_t *)0x40058504))
#define GPIO_PORTA_AHB_DR8R_R   (*((volatile uint32_t *)0x40058508))
#define GPIO_PORTA_AHB_ODR_R    (*((volatile uint32_t *)0x4005850C))
#define GPIO_PORTA_AHB_PUR_R    (*((volatile uint32_t *)0x40058510))
#define GPIO_PORTA_AHB_PDR_R    (*((volatile uint32_t *)0x40058514))
#define GPIO_PORTA_AHB_SLR_R    (*((volatile uint32_t *)0x40058518))
#define GPIO_PORTA_AHB_DEN_R    (*((volatile uint32_t *)0x4005851C))
#define GPIO_PORTA_AHB_LOCK_R   (*((volatile uint32_t *)0x40058520))
#define GPIO_PORTA_AHB_CR_R     (*((volatile uint32_t *)0x40058524))
#define GPIO_PORTA_AHB_AMSEL_R  (*((volatile uint32_t *)0x40058528))
#define GPIO_PORTA_AHB_PCTL_R   (*((volatile uint32_t *)0x4005852C))
#define GPIO_PORTA_AHB_ADCCTL_R (*((volatile uint32_t *)0x40058530))
#define GPIO_PORTA_AHB_DMACTL_R (*((volatile uint32_t *)0x40058534))
#define GPIO_PORTA_AHB_SI_R     (*((volatile uint32_t *)0x40058538))
#define GPIO_PORTA_AHB_DR12R_R  (*((volatile uint32_t *)0x4005853C))
#define GPIO_PORTA_AHB_WAKEPEN_R                                              \
                                (*((volatile uint32_t *)0x40058540))
#define GPIO_PORTA_AHB_WAKELVL_R                                              \
                                (*((volatile uint32_t *)0x40058544))
#define GPIO_PORTA_AHB_WAKESTAT_R                                             \
                                (*((volatile uint32_t *)0x40058548))
#define GPIO_PORTA_AHB_PP_R     (*((volatile uint32_t *)0x40058FC0))
#define GPIO_PORTA_AHB_PC_R     (*((volatile uint32_t *)0x40058FC4))



//////////GPIO PORT D
#define GPIO_PORTD_AHB_DATA_R   (*((volatile uint32_t *)0x4005B3FC))
#define GPIO_PORTD_AHB_DIR_R    (*((volatile uint32_t *)0x4005B400))
#define GPIO_PORTD_AHB_IS_R     (*((volatile uint32_t *)0x4005B404))
#define GPIO_PORTD_AHB_IBE_R    (*((volatile uint32_t *)0x4005B408))
#define GPIO_PORTD_AHB_IEV_R    (*((volatile uint32_t *)0x4005B40C))
#define GPIO_PORTD_AHB_IM_R     (*((volatile uint32_t *)0x4005B410))
#define GPIO_PORTD_AHB_RIS_R    (*((volatile uint32_t *)0x4005B414))
#define GPIO_PORTD_AHB_MIS_R    (*((volatile uint32_t *)0x4005B418))
#define GPIO_PORTD_AHB_ICR_R    (*((volatile uint32_t *)0x4005B41C))
#define GPIO_PORTD_AHB_AFSEL_R  (*((volatile uint32_t *)0x4005B420))
#define GPIO_PORTD_AHB_DR2R_R   (*((volatile uint32_t *)0x4005B500))
#define GPIO_PORTD_AHB_DR4R_R   (*((volatile uint32_t *)0x4005B504))
#define GPIO_PORTD_AHB_DR8R_R   (*((volatile uint32_t *)0x4005B508))
#define GPIO_PORTD_AHB_ODR_R    (*((volatile uint32_t *)0x4005B50C))
#define GPIO_PORTD_AHB_PUR_R    (*((volatile uint32_t *)0x4005B510))
#define GPIO_PORTD_AHB_PDR_R    (*((volatile uint32_t *)0x4005B514))
#define GPIO_PORTD_AHB_SLR_R    (*((volatile uint32_t *)0x4005B518))
#define GPIO_PORTD_AHB_DEN_R    (*((volatile uint32_t *)0x4005B51C))
#define GPIO_PORTD_AHB_LOCK_R   (*((volatile uint32_t *)0x4005B520))
#define GPIO_PORTD_AHB_CR_R     (*((volatile uint32_t *)0x4005B524))
#define GPIO_PORTD_AHB_AMSEL_R  (*((volatile uint32_t *)0x4005B528))
#define GPIO_PORTD_AHB_PCTL_R   (*((volatile uint32_t *)0x4005B52C))
#define GPIO_PORTD_AHB_ADCCTL_R (*((volatile uint32_t *)0x4005B530))
#define GPIO_PORTD_AHB_DMACTL_R (*((volatile uint32_t *)0x4005B534))
#define GPIO_PORTD_AHB_SI_R     (*((volatile uint32_t *)0x4005B538))
#define GPIO_PORTD_AHB_DR12R_R  (*((volatile uint32_t *)0x4005B53C))
#define GPIO_PORTD_AHB_WAKEPEN_R                                              \
                                (*((volatile uint32_t *)0x4005B540))
#define GPIO_PORTD_AHB_WAKELVL_R                                              \
                                (*((volatile uint32_t *)0x4005B544))
#define GPIO_PORTD_AHB_WAKESTAT_R                                             \
                                (*((volatile uint32_t *)0x4005B548))
#define GPIO_PORTD_AHB_PP_R     (*((volatile uint32_t *)0x4005BFC0))
#define GPIO_PORTD_AHB_PC_R     (*((volatile uint32_t *)0x4005BFC4))



///////////GPIO PORTE

#define GPIO_PORTE_AHB_DATA_R   (*((volatile uint32_t *)0x4005C3FC))
#define GPIO_PORTE_AHB_DIR_R    (*((volatile uint32_t *)0x4005C400))
#define GPIO_PORTE_AHB_IS_R     (*((volatile uint32_t *)0x4005C404))
#define GPIO_PORTE_AHB_IBE_R    (*((volatile uint32_t *)0x4005C408))
#define GPIO_PORTE_AHB_IEV_R    (*((volatile uint32_t *)0x4005C40C))
#define GPIO_PORTE_AHB_IM_R     (*((volatile uint32_t *)0x4005C410))
#define GPIO_PORTE_AHB_RIS_R    (*((volatile uint32_t *)0x4005C414))
#define GPIO_PORTE_AHB_MIS_R    (*((volatile uint32_t *)0x4005C418))
#define GPIO_PORTE_AHB_ICR_R    (*((volatile uint32_t *)0x4005C41C))
#define GPIO_PORTE_AHB_AFSEL_R  (*((volatile uint32_t *)0x4005C420))
#define GPIO_PORTE_AHB_DR2R_R   (*((volatile uint32_t *)0x4005C500))
#define GPIO_PORTE_AHB_DR4R_R   (*((volatile uint32_t *)0x4005C504))
#define GPIO_PORTE_AHB_DR8R_R   (*((volatile uint32_t *)0x4005C508))
#define GPIO_PORTE_AHB_ODR_R    (*((volatile uint32_t *)0x4005C50C))
#define GPIO_PORTE_AHB_PUR_R    (*((volatile uint32_t *)0x4005C510))
#define GPIO_PORTE_AHB_PDR_R    (*((volatile uint32_t *)0x4005C514))
#define GPIO_PORTE_AHB_SLR_R    (*((volatile uint32_t *)0x4005C518))
#define GPIO_PORTE_AHB_DEN_R    (*((volatile uint32_t *)0x4005C51C))
#define GPIO_PORTE_AHB_LOCK_R   (*((volatile uint32_t *)0x4005C520))
#define GPIO_PORTE_AHB_CR_R     (*((volatile uint32_t *)0x4005C524))
#define GPIO_PORTE_AHB_AMSEL_R  (*((volatile uint32_t *)0x4005C528))
#define GPIO_PORTE_AHB_PCTL_R   (*((volatile uint32_t *)0x4005C52C))
#define GPIO_PORTE_AHB_ADCCTL_R (*((volatile uint32_t *)0x4005C530))
#define GPIO_PORTE_AHB_DMACTL_R (*((volatile uint32_t *)0x4005C534))
#define GPIO_PORTE_AHB_SI_R     (*((volatile uint32_t *)0x4005C538))
#define GPIO_PORTE_AHB_DR12R_R  (*((volatile uint32_t *)0x4005C53C))
#define GPIO_PORTE_AHB_WAKEPEN_R                                              \
                                (*((volatile uint32_t *)0x4005C540))
#define GPIO_PORTE_AHB_WAKELVL_R                                              \
                                (*((volatile uint32_t *)0x4005C544))
#define GPIO_PORTE_AHB_WAKESTAT_R                                             \
                                (*((volatile uint32_t *)0x4005C548))
#define GPIO_PORTE_AHB_PP_R     (*((volatile uint32_t *)0x4005CFC0))
#define GPIO_PORTE_AHB_PC_R     (*((volatile uint32_t *)0x4005CFC4))

//*****************************************************************************
//
// GPIO registers (PORTH AHB)
//
//*****************************************************************************
#define GPIO_PORTH_AHB_DATA_BITS_R                                            \
                                ((volatile uint32_t *)0x4005F000)
#define GPIO_PORTH_AHB_DATA_R   (*((volatile uint32_t *)0x4005F3FC))
#define GPIO_PORTH_AHB_DIR_R    (*((volatile uint32_t *)0x4005F400))
#define GPIO_PORTH_AHB_IS_R     (*((volatile uint32_t *)0x4005F404))
#define GPIO_PORTH_AHB_IBE_R    (*((volatile uint32_t *)0x4005F408))
#define GPIO_PORTH_AHB_IEV_R    (*((volatile uint32_t *)0x4005F40C))
#define GPIO_PORTH_AHB_IM_R     (*((volatile uint32_t *)0x4005F410))
#define GPIO_PORTH_AHB_RIS_R    (*((volatile uint32_t *)0x4005F414))
#define GPIO_PORTH_AHB_MIS_R    (*((volatile uint32_t *)0x4005F418))
#define GPIO_PORTH_AHB_ICR_R    (*((volatile uint32_t *)0x4005F41C))
#define GPIO_PORTH_AHB_AFSEL_R  (*((volatile uint32_t *)0x4005F420))
#define GPIO_PORTH_AHB_DR2R_R   (*((volatile uint32_t *)0x4005F500))
#define GPIO_PORTH_AHB_DR4R_R   (*((volatile uint32_t *)0x4005F504))
#define GPIO_PORTH_AHB_DR8R_R   (*((volatile uint32_t *)0x4005F508))
#define GPIO_PORTH_AHB_ODR_R    (*((volatile uint32_t *)0x4005F50C))
#define GPIO_PORTH_AHB_PUR_R    (*((volatile uint32_t *)0x4005F510))
#define GPIO_PORTH_AHB_PDR_R    (*((volatile uint32_t *)0x4005F514))
#define GPIO_PORTH_AHB_SLR_R    (*((volatile uint32_t *)0x4005F518))
#define GPIO_PORTH_AHB_DEN_R    (*((volatile uint32_t *)0x4005F51C))
#define GPIO_PORTH_AHB_LOCK_R   (*((volatile uint32_t *)0x4005F520))
#define GPIO_PORTH_AHB_CR_R     (*((volatile uint32_t *)0x4005F524))
#define GPIO_PORTH_AHB_AMSEL_R  (*((volatile uint32_t *)0x4005F528))
#define GPIO_PORTH_AHB_PCTL_R   (*((volatile uint32_t *)0x4005F52C))
#define GPIO_PORTH_AHB_ADCCTL_R (*((volatile uint32_t *)0x4005F530))
#define GPIO_PORTH_AHB_DMACTL_R (*((volatile uint32_t *)0x4005F534))
#define GPIO_PORTH_AHB_SI_R     (*((volatile uint32_t *)0x4005F538))
#define GPIO_PORTH_AHB_DR12R_R  (*((volatile uint32_t *)0x4005F53C))
#define GPIO_PORTH_AHB_WAKEPEN_R                                              \
                                (*((volatile uint32_t *)0x4005F540))
#define GPIO_PORTH_AHB_WAKELVL_R                                              \
                                (*((volatile uint32_t *)0x4005F544))
#define GPIO_PORTH_AHB_WAKESTAT_R                                             \
                                (*((volatile uint32_t *)0x4005F548))
#define GPIO_PORTH_AHB_PP_R     (*((volatile uint32_t *)0x4005FFC0))
#define GPIO_PORTH_AHB_PC_R     (*((volatile uint32_t *)0x4005FFC4))

/////////GPIO PORT K

#define GPIO_PORTK_DATA_BITS_R  ((volatile uint32_t *)0x40061000)
#define GPIO_PORTK_DATA_R       (*((volatile uint32_t *)0x400613FC))
#define GPIO_PORTK_DIR_R        (*((volatile uint32_t *)0x40061400))
#define GPIO_PORTK_IS_R         (*((volatile uint32_t *)0x40061404))
#define GPIO_PORTK_IBE_R        (*((volatile uint32_t *)0x40061408))
#define GPIO_PORTK_IEV_R        (*((volatile uint32_t *)0x4006140C))
#define GPIO_PORTK_IM_R         (*((volatile uint32_t *)0x40061410))
#define GPIO_PORTK_RIS_R        (*((volatile uint32_t *)0x40061414))
#define GPIO_PORTK_MIS_R        (*((volatile uint32_t *)0x40061418))
#define GPIO_PORTK_ICR_R        (*((volatile uint32_t *)0x4006141C))
#define GPIO_PORTK_AFSEL_R      (*((volatile uint32_t *)0x40061420))
#define GPIO_PORTK_DR2R_R       (*((volatile uint32_t *)0x40061500))
#define GPIO_PORTK_DR4R_R       (*((volatile uint32_t *)0x40061504))
#define GPIO_PORTK_DR8R_R       (*((volatile uint32_t *)0x40061508))
#define GPIO_PORTK_ODR_R        (*((volatile uint32_t *)0x4006150C))
#define GPIO_PORTK_PUR_R        (*((volatile uint32_t *)0x40061510))
#define GPIO_PORTK_PDR_R        (*((volatile uint32_t *)0x40061514))
#define GPIO_PORTK_SLR_R        (*((volatile uint32_t *)0x40061518))
#define GPIO_PORTK_DEN_R        (*((volatile uint32_t *)0x4006151C))
#define GPIO_PORTK_LOCK_R       (*((volatile uint32_t *)0x40061520))
#define GPIO_PORTK_CR_R         (*((volatile uint32_t *)0x40061524))
#define GPIO_PORTK_AMSEL_R      (*((volatile uint32_t *)0x40061528))
#define GPIO_PORTK_PCTL_R       (*((volatile uint32_t *)0x4006152C))
#define GPIO_PORTK_ADCCTL_R     (*((volatile uint32_t *)0x40061530))
#define GPIO_PORTK_DMACTL_R     (*((volatile uint32_t *)0x40061534))
#define GPIO_PORTK_SI_R         (*((volatile uint32_t *)0x40061538))
#define GPIO_PORTK_DR12R_R      (*((volatile uint32_t *)0x4006153C))
#define GPIO_PORTK_WAKEPEN_R    (*((volatile uint32_t *)0x40061540))
#define GPIO_PORTK_WAKELVL_R    (*((volatile uint32_t *)0x40061544))
#define GPIO_PORTK_WAKESTAT_R   (*((volatile uint32_t *)0x40061548))
#define GPIO_PORTK_PP_R         (*((volatile uint32_t *)0x40061FC0))
#define GPIO_PORTK_PC_R         (*((volatile uint32_t *)0x40061FC4))


//////////GPIO PORTL




#define GPIO_PORTL_DATA_R       (*((volatile uint32_t *)0x400623FC))
#define GPIO_PORTL_DIR_R        (*((volatile uint32_t *)0x40062400))
#define GPIO_PORTL_AFSEL_R      (*((volatile uint32_t *)0x40062420))
#define GPIO_PORTL_ODR_R        (*((volatile uint32_t *)0x4006250C))
#define GPIO_PORTL_DEN_R        (*((volatile uint32_t *)0x4006251C))



//*****************************************************************************
//
// GPIO registers (PORTN)
//
//*****************************************************************************
#define GPIO_PORTN_DATA_BITS_R  ((volatile uint32_t *)0x40064000)
#define GPIO_PORTN_DATA_R       (*((volatile uint32_t *)0x400643FC))
#define GPIO_PORTN_DIR_R        (*((volatile uint32_t *)0x40064400))
#define GPIO_PORTN_IS_R         (*((volatile uint32_t *)0x40064404))
#define GPIO_PORTN_IBE_R        (*((volatile uint32_t *)0x40064408))
#define GPIO_PORTN_IEV_R        (*((volatile uint32_t *)0x4006440C))
#define GPIO_PORTN_IM_R         (*((volatile uint32_t *)0x40064410))
#define GPIO_PORTN_RIS_R        (*((volatile uint32_t *)0x40064414))
#define GPIO_PORTN_MIS_R        (*((volatile uint32_t *)0x40064418))
#define GPIO_PORTN_ICR_R        (*((volatile uint32_t *)0x4006441C))
#define GPIO_PORTN_AFSEL_R      (*((volatile uint32_t *)0x40064420))
#define GPIO_PORTN_DR2R_R       (*((volatile uint32_t *)0x40064500))
#define GPIO_PORTN_DR4R_R       (*((volatile uint32_t *)0x40064504))
#define GPIO_PORTN_DR8R_R       (*((volatile uint32_t *)0x40064508))
#define GPIO_PORTN_ODR_R        (*((volatile uint32_t *)0x4006450C))
#define GPIO_PORTN_PUR_R        (*((volatile uint32_t *)0x40064510))
#define GPIO_PORTN_PDR_R        (*((volatile uint32_t *)0x40064514))
#define GPIO_PORTN_SLR_R        (*((volatile uint32_t *)0x40064518))
#define GPIO_PORTN_DEN_R        (*((volatile uint32_t *)0x4006451C))
#define GPIO_PORTN_LOCK_R       (*((volatile uint32_t *)0x40064520))
#define GPIO_PORTN_CR_R         (*((volatile uint32_t *)0x40064524))
#define GPIO_PORTN_AMSEL_R      (*((volatile uint32_t *)0x40064528))
#define GPIO_PORTN_PCTL_R       (*((volatile uint32_t *)0x4006452C))
#define GPIO_PORTN_ADCCTL_R     (*((volatile uint32_t *)0x40064530))
#define GPIO_PORTN_DMACTL_R     (*((volatile uint32_t *)0x40064534))
#define GPIO_PORTN_SI_R         (*((volatile uint32_t *)0x40064538))
#define GPIO_PORTN_DR12R_R      (*((volatile uint32_t *)0x4006453C))
#define GPIO_PORTN_WAKEPEN_R    (*((volatile uint32_t *)0x40064540))
#define GPIO_PORTN_WAKELVL_R    (*((volatile uint32_t *)0x40064544))
#define GPIO_PORTN_WAKESTAT_R   (*((volatile uint32_t *)0x40064548))
#define GPIO_PORTN_PP_R         (*((volatile uint32_t *)0x40064FC0))
#define GPIO_PORTN_PC_R         (*((volatile uint32_t *)0x40064FC4))

///////////I2C
#define I2C7_MCR_R              (*((volatile uint32_t *)0x400C3020))
#define I2C7_MTPR_R             (*((volatile uint32_t *)0x400C300C))
#define I2C7_MCS_R              (*((volatile uint32_t *)0x400C3004))
#define I2C7_MSA_R              (*((volatile uint32_t *)0x400C3000))
#define I2C7_MDR_R              (*((volatile uint32_t *)0x400C3008))

//////////ADC0

#define SYSCTL_RCGCADC_R        (*((volatile uint32_t *)0x400FE638))
#define SYSCTL_PRADC_R          (*((volatile uint32_t *)0x400FEA38))
#define SYSCTL_PLLSTAT_R        (*((volatile uint32_t *)0x400FE168))
#define SYSCTL_PLLFREQ0_R       (*((volatile uint32_t *)0x400FE160))


#define ADC0_ACTSS_R            (*((volatile uint32_t *)0x40038000))
#define ADC0_RIS_R              (*((volatile uint32_t *)0x40038004))
#define ADC0_IM_R               (*((volatile uint32_t *)0x40038008))
#define ADC0_ISC_R              (*((volatile uint32_t *)0x4003800C))
#define ADC0_OSTAT_R            (*((volatile uint32_t *)0x40038010))
#define ADC0_EMUX_R             (*((volatile uint32_t *)0x40038014))
#define ADC0_USTAT_R            (*((volatile uint32_t *)0x40038018))
#define ADC0_TSSEL_R            (*((volatile uint32_t *)0x4003801C))
#define ADC0_SSPRI_R            (*((volatile uint32_t *)0x40038020))
#define ADC0_SPC_R              (*((volatile uint32_t *)0x40038024))
#define ADC0_PSSI_R             (*((volatile uint32_t *)0x40038028))
#define ADC0_SAC_R              (*((volatile uint32_t *)0x40038030))
#define ADC0_DCISC_R            (*((volatile uint32_t *)0x40038034))
#define ADC0_CTL_R              (*((volatile uint32_t *)0x40038038))
#define ADC0_SSMUX0_R           (*((volatile uint32_t *)0x40038040))
#define ADC0_SSCTL0_R           (*((volatile uint32_t *)0x40038044))
#define ADC0_SSFIFO0_R          (*((volatile uint32_t *)0x40038048))
#define ADC0_SSFSTAT0_R         (*((volatile uint32_t *)0x4003804C))
#define ADC0_SSOP0_R            (*((volatile uint32_t *)0x40038050))
#define ADC0_SSDC0_R            (*((volatile uint32_t *)0x40038054))
#define ADC0_SSEMUX0_R          (*((volatile uint32_t *)0x40038058))
#define ADC0_SSTSH0_R           (*((volatile uint32_t *)0x4003805C))
#define ADC0_SSMUX1_R           (*((volatile uint32_t *)0x40038060))
#define ADC0_SSCTL1_R           (*((volatile uint32_t *)0x40038064))
#define ADC0_SSFIFO1_R          (*((volatile uint32_t *)0x40038068))
#define ADC0_SSFSTAT1_R         (*((volatile uint32_t *)0x4003806C))
#define ADC0_SSOP1_R            (*((volatile uint32_t *)0x40038070))
#define ADC0_SSDC1_R            (*((volatile uint32_t *)0x40038074))
#define ADC0_SSEMUX1_R          (*((volatile uint32_t *)0x40038078))
#define ADC0_SSTSH1_R           (*((volatile uint32_t *)0x4003807C))
#define ADC0_SSMUX2_R           (*((volatile uint32_t *)0x40038080))
#define ADC0_SSCTL2_R           (*((volatile uint32_t *)0x40038084))
#define ADC0_SSFIFO2_R          (*((volatile uint32_t *)0x40038088))
#define ADC0_SSFSTAT2_R         (*((volatile uint32_t *)0x4003808C))
#define ADC0_SSOP2_R            (*((volatile uint32_t *)0x40038090))
#define ADC0_SSDC2_R            (*((volatile uint32_t *)0x40038094))
#define ADC0_SSEMUX2_R          (*((volatile uint32_t *)0x40038098))
#define ADC0_SSTSH2_R           (*((volatile uint32_t *)0x4003809C))
#define ADC0_SSMUX3_R           (*((volatile uint32_t *)0x400380A0))
#define ADC0_SSCTL3_R           (*((volatile uint32_t *)0x400380A4))
#define ADC0_SSFIFO3_R          (*((volatile uint32_t *)0x400380A8))
#define ADC0_SSFSTAT3_R         (*((volatile uint32_t *)0x400380AC))
#define ADC0_SSOP3_R            (*((volatile uint32_t *)0x400380B0))
#define ADC0_SSDC3_R            (*((volatile uint32_t *)0x400380B4))
#define ADC0_SSEMUX3_R          (*((volatile uint32_t *)0x400380B8))
#define ADC0_SSTSH3_R           (*((volatile uint32_t *)0x400380BC))
#define ADC0_DCRIC_R            (*((volatile uint32_t *)0x40038D00))
#define ADC0_DCCTL0_R           (*((volatile uint32_t *)0x40038E00))
#define ADC0_DCCTL1_R           (*((volatile uint32_t *)0x40038E04))
#define ADC0_DCCTL2_R           (*((volatile uint32_t *)0x40038E08))
#define ADC0_DCCTL3_R           (*((volatile uint32_t *)0x40038E0C))
#define ADC0_DCCTL4_R           (*((volatile uint32_t *)0x40038E10))
#define ADC0_DCCTL5_R           (*((volatile uint32_t *)0x40038E14))
#define ADC0_DCCTL6_R           (*((volatile uint32_t *)0x40038E18))
#define ADC0_DCCTL7_R           (*((volatile uint32_t *)0x40038E1C))
#define ADC0_DCCMP0_R           (*((volatile uint32_t *)0x40038E40))
#define ADC0_DCCMP1_R           (*((volatile uint32_t *)0x40038E44))
#define ADC0_DCCMP2_R           (*((volatile uint32_t *)0x40038E48))
#define ADC0_DCCMP3_R           (*((volatile uint32_t *)0x40038E4C))
#define ADC0_DCCMP4_R           (*((volatile uint32_t *)0x40038E50))
#define ADC0_DCCMP5_R           (*((volatile uint32_t *)0x40038E54))
#define ADC0_DCCMP6_R           (*((volatile uint32_t *)0x40038E58))
#define ADC0_DCCMP7_R           (*((volatile uint32_t *)0x40038E5C))
#define ADC0_PP_R               (*((volatile uint32_t *)0x40038FC0))
#define ADC0_PC_R               (*((volatile uint32_t *)0x40038FC4))
#define ADC0_CC_R               (*((volatile uint32_t *)0x40038FC8))











#endif /* TM4C_H_ */
