/*
 * SPI.c
 *
 *  Created on: Mar 6, 2020
 *      Author: Momo
 */

#include "SPI.h"
/*it enable the clock module of the SPI by modifying the MDIS bits*/
 void SPI_enable(spi_channel_t channel)
 {
	 switch (channel) {
	 	case SPI_0:
	 		SPI0->MCR &= (~SPI_MCR_MDIS_MASK); //Enables the module clocks
	 		break;
	 	case SPI_1:
	 		SPI1->MCR &= (~SPI_MCR_MDIS_MASK); //Enables the module clocks
	 		break;
	 	case SPI_2:
	 		SPI2->MCR &= (~SPI_MCR_MDIS_MASK); //Enables the module clocks
	 		break;
	 	default:
	 		break;
	 	}
 }
/*It activate the clock gating*/
 void SPI_clk(spi_channel_t channel)
 {
	 switch (channel) {
	 	case SPI_0:
	 		SIM->SCGC6 |= SIM_SCGC6_SPI0_MASK;
	 		break;
	 	case SPI_1:
	 		SIM->SCGC6 |= SIM_SCGC6_SPI1_MASK;
	 		break;
	 	case SPI_2:
	 		SIM->SCGC3 |= SIM_SCGC3_SPI2_MASK;
	 		break;
	 	default:
	 		break;
	 	}
 }
/*It configure the SPI as a master or slave depending on the value of masterOrslave*/
 void SPI_set_master(spi_channel_t channel, spi_master_t master_or_slave)
 {
	 if (SPI_MASTER == masterOrSlave) {
		switch (channel) {
		case SPI_0:
			SPI0->MCR |= SPI_MCR_MSTR_MASK;
			break;
		case SPI_1:
			SPI1->MCR |= SPIx_MCR_MSTR_MASK;
			break;
		case SPI_2:
			SPI2->MCR |= SPIx_MCR_MSTR_MASK;
			break;
		default:
			break;
		}
	} else {
		switch (channel) {
		case SPI_0:
			SPI0->MCR &= ~SPI_MCR_MSTR_MASK;
			break;
		case SPI_1:
			SPI1->MCR &= ~SPIx_MCR_MSTR_MASK;
			break;
		case SPI_2:
			SPI2->MCR &= ~SPIx_MCR_MSTR_MASK;
			break;
		default:
			break;
		}
	}

 }
/*It activate the TX and RX FIFOs of the SPI depending on the value of enableOrdisable*/
 void SPI_fifo(spi_channel_t channel, spi_enable_fifo_t enable_or_disable)
 {
	 if (SPI_DISABLE_FIFO == enableOrDisable) {
		switch (channel) {
		case SPI_0:
			//Disable
			SPI0->MCR &= ~(SPI_MCR_DIS_RXF_MASK); //Disable RX (data in)
			SPI0->MCR &= ~(SPI_MCR_DIS_TXF_MASK); //Disable TX (data out)
			break;
		case SPI_1:
			//Disable
			SPI1->MCR &= ~(SPI_MCR_DIS_RXF_MASK); //Disable RX (data in)
			SPI1->MCR &= ~(SPI_MCR_DIS_TXF_MASK); //Disable TX (data out)
			break;
		case SPI_2:
			//Disable
			SPI2->MCR &= ~(SPI_MCR_DIS_RXF_MASK); //Disable RX (data in)
			SPI2->MCR &= ~(SPI_MCR_DIS_TXF_MASK); //Disable TX (data out)
			break;
		default:
			break;
		}
	} else {
		switch (channel) {
		case SPI_0:
			//Enable
			SPI0->MCR |= SPI_MCR_DIS_RXF_MASK; //Enable RX (data in)
			SPI0->MCR |= SPI_MCR_DIS_TXF_MASK; //Enable TX (data out)
			break;
		case SPI_1:
			//Enable
			SPI1->MCR |= SPI_MCR_DIS_RXF_MASK; //Enable RX (data in)
			SPI1->MCR |= SPI_MCR_DIS_TXF_MASK; //Enable TX (data out)
			break;
		case SPI_2:
			//Enable
			SPI2->MCR |= SPI_MCR_DIS_RXF_MASK; //Enable RX (data in)
			SPI2->MCR |= SPI_MCR_DIS_TXF_MASK; //Enable TX (data out)
			break;
		default:
			break;
		}
	}
 }
/*It selects the clock polarity depending on the value of cpol*/
 void SPI_clock_polarity(spi_channel_t channel, spi_polarity_t cpol);
/*It selects the frame size depending on the value of frameSize and the macros that are defined above*/
 void SPI_frame_size(spi_channel_t channel, uint32_t frame_size);
/*It selects the clock phase depending on the value of cpha*/
 void SPI_clock_phase(spi_channel_t channel, spi_phase_t cpha);
/*It selects the baud rate depending on the value of baudRate and the macros that are defined above*/
 void SPI_baud_rate(spi_channel_t channel, uint32_t baud_rate);
/*It selects if MSB or LSM bits is first transmitted*/
 void SPI_msb_first(spi_channel_t channel, spi_lsb_or_msb_t msb);
/*It stars the SPI transmission by modifying the value of HALT bit*/
void SPI_start_tranference(spi_channel_t channel);
/*It stops the SPI transmission by modifying the value of HALT bit*/
void SPI_stop_tranference(spi_channel_t channel);
/*It transmits the information contained in data*/
uint8_t SPI_tranference(spi_channel_t channel, uint8_t data);
/*It configures the SPI for transmission, this function as arguments receives a pointer to a constant structure where are all
 * the configuration parameters*/
void SPI_init(const spi_config_t* config_struct);
