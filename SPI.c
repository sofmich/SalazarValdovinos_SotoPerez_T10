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
	 if (SPI_MASTER == master_or_slave) {
		switch (channel) {
		case SPI_0:
			SPI0->MCR |= SPI_MCR_MSTR_MASK;
			break;
		case SPI_1:
			SPI1->MCR |= SPI_MCR_MSTR_MASK;
			break;
		case SPI_2:
			SPI2->MCR |= SPI_MCR_MSTR_MASK;
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
			SPI1->MCR &= ~SPI_MCR_MSTR_MASK;
			break;
		case SPI_2:
			SPI2->MCR &= ~SPI_MCR_MSTR_MASK;
			break;
		default:
			break;
		}
	}

 }
/*It activate the TX and RX FIFOs of the SPI depending on the value of enableOrdisable*/
 void SPI_fifo(spi_channel_t channel, spi_enable_fifo_t enable_or_disable)
 {
	 if (SPI_DISABLE_FIFO == enable_or_disable) {
		switch (channel) {
		case SPI_0:

			SPI0->MCR &= ~(SPI_MCR_DIS_RXF_MASK);
			SPI0->MCR &= ~(SPI_MCR_DIS_TXF_MASK);
			break;
		case SPI_1:

			SPI1->MCR &= ~(SPI_MCR_DIS_RXF_MASK); /*Disable RX (data in)*/
			SPI1->MCR &= ~(SPI_MCR_DIS_TXF_MASK); /*Disable TX (data out*/
			break;
		case SPI_2:

			SPI2->MCR &= ~(SPI_MCR_DIS_RXF_MASK);
			SPI2->MCR &= ~(SPI_MCR_DIS_TXF_MASK);
			break;
		default:
			break;
		}
	} else {
		switch (channel) {
		case SPI_0:

			SPI0->MCR |= SPI_MCR_DIS_RXF_MASK; /*Enable RX (data in)*/
			SPI0->MCR |= SPI_MCR_DIS_TXF_MASK; /*Enable TX (data out)*/
			break;
		case SPI_1:

			SPI1->MCR |= SPI_MCR_DIS_RXF_MASK;
			SPI1->MCR |= SPI_MCR_DIS_TXF_MASK;
			break;
		case SPI_2:

			SPI2->MCR |= SPI_MCR_DIS_RXF_MASK;
			SPI2->MCR |= SPI_MCR_DIS_TXF_MASK;
			break;
		default:
			break;
		}
	}
 }
/*It selects the clock polarity depending on the value of cpol*/
 void SPI_clock_polarity(spi_channel_t channel, spi_polarity_t cpol)
 {
	 if (SPI_HIGH_POLARITY == cpol) {
		switch (channel) {
		case SPI_0:
			SPI0->CTAR[0] |= SPI_CTAR_CPOL_MASK; /*Clock polarity is high*/
			break;
		case SPI_1:
			SPI1->CTAR[0] |= SPI_CTAR_CPOL_MASK;
			break;
		case SPI_2:
			SPI2->CTAR[0] |= SPI_CTAR_CPOL_MASK;
			break;
		default:
			break;
		}
	} else {
		switch (channel) {
		case SPI_0:
			SPI0->CTAR[0] &= ~SPI_CTAR_CPOL_MASK; /*Clock polarity is low*/
			break;
		case SPI_1:
			SPI1->CTAR[0] &= ~SPI_CTAR_CPOL_MASK;
			break;
		case SPI_2:
			SPI2->CTAR[0] &= ~SPI_CTAR_CPOL_MASK;
			break;
		default:
			break;
		}
	}

 }
/*It selects the frame size depending on the value of frameSize and the macros that are defined above*/
 void SPI_frame_size(spi_channel_t channel, uint32_t frame_size)
 {
	 /*First clean the field and then set the size*/
	 switch (channel) {
	 	case SPI_0:
	 		SPI0->CTAR[0] &= ~(SPI_CTAR_FMSZ_MASK);
	 		SPI0->CTAR[0] |= frame_size;
	 		break;
	 	case SPI_1:
	 		SPI1->CTAR[0] &= ~(SPI_CTAR_FMSZ_MASK);
	 		SPI1->CTAR[0] |= frame_size;
	 		break;
	 	default:
	 		SPI2->CTAR[0] &= ~(SPI_CTAR_FMSZ_MASK);
	 		SPI2->CTAR[0] |= frame_size;
	 		break;
	 	}
 }
/*It selects the clock phase depending on the value of cpha*/
 void SPI_clock_phase(spi_channel_t channel, spi_phase_t cpha)
 {
	 /*Select High or Low phase*/
	if (SPI_HIGH_PHASE == cpha) {
		switch (channel) {
		case SPI_0:
			SPI0->CTAR[0] |= SPI_CTAR_CPHA_MASK;
			break;
		case SPI_1:
			SPI1->CTAR[0] |= SPI_CTAR_CPHA_MASK;
			break;
		case SPI_2:
			SPI2->CTAR[0] |= SPI_CTAR_CPHA_MASK;
			break;
		default:
			break;
		}
	} else {
		switch (channel) {
		case SPI_0:
			SPI0->CTAR[0] &= ~SPI_CTAR_CPHA_MASK;
			break;
		case SPI_1:
			SPI1->CTAR[0] &= ~SPI_CTAR_CPHA_MASK;
			break;
		case SPI_2:
			SPI2->CTAR[0] &= ~SPI_CTAR_CPHA_MASK;
			break;
		default:
			break;
		}
	}

 }
/*It selects the baud rate depending on the value of baudRate and the macros that are defined above*/
 void SPI_baud_rate(spi_channel_t channel, uint32_t baud_rate)
 {
	switch (channel) {
	case SPI_0:
		SPI0->CTAR[0] &= ~(SPI_CTAR_BR_MASK);
		SPI0->CTAR[0] |= SPI_CTAR_BR(baud_rate); /*Select the bd of transmission or rx*/
		break;
	case SPI_1:
		SPI1->CTAR[0] &= ~(SPI_CTAR_BR_MASK);
		SPI1->CTAR[0] |= SPI_CTAR_BR(baud_rate);
		break;
	case SPI_2:
		SPI2->CTAR[0] &= ~(SPI_CTAR_BR_MASK);
		SPI2->CTAR[0] |= SPI_CTAR_BR(baud_rate);
		break;
	default:
		break;
	}
 }
/*It selects if MSB or LSM bits is first transmitted*/
 void SPI_msb_first(spi_channel_t channel, spi_lsb_or_msb_t msb)
 {
	 /*Less significant bit ffirst*/
	 if (SPI_LSM == msb) {
	 		switch (channel) {
	 		case SPI_0:
	 			SPI0->CTAR[0] |= SPI_CTAR_LSBFE_MASK;
	 			break;
	 		case SPI_1:
	 			SPI1->CTAR[0] |= SPI_CTAR_LSBFE_MASK;
	 			break;
	 		case SPI_2:
	 			SPI2->CTAR[0] |= SPI_CTAR_LSBFE_MASK;
	 			break;
	 		default:
	 			break;
	 		}
	 	} else {
	 		/*Most significant bit first*/
	 		switch (channel) {
	 		case SPI_0:
	 			SPI0->CTAR[0] &= ~SPI_CTAR_LSBFE_MASK;
	 			break;
	 		case SPI_1:
	 			SPI1->CTAR[0] &= ~SPI_CTAR_LSBFE_MASK;
	 			break;
	 		case SPI_2:
	 			SPI2->CTAR[0] &= ~SPI_CTAR_LSBFE_MASK;
	 			break;
	 		default:
	 			break;
	 		}
	 	}
 }
/*It stars the SPI transmission by modifying the value of HALT bit*/
void SPI_start_tranference(spi_channel_t channel)
{
	switch (channel) {
	case SPI_0:
		SPI0->MCR &= ~SPI_MCR_HALT_MASK;
		break;
	case SPI_1:
		SPI1->MCR &= ~SPI_MCR_HALT_MASK;
		break;
	case SPI_2:
		SPI2->MCR &= ~SPI_MCR_HALT_MASK;
		break;
	default:
		break;
	}
}
/*It stops the SPI transmission by modifying the value of HALT bit*/
void SPI_stop_tranference(spi_channel_t channel)
{
	switch (channel) {
		case SPI_0:
			SPI0->MCR |= SPI_MCR_HALT_MASK;
			break;
		case SPI_1:
			SPI1->MCR |= SPI_MCR_HALT_MASK;
			break;
		case SPI_2:
			SPI2->MCR |= SPI_MCR_HALT_MASK;
			break;
		default:
			break;
		}
}
/*It transmits the information contained in data*/
uint8_t SPI_tranference(spi_channel_t channel, uint8_t data)
{
	/*Sends information of 1byte length*/
	SPI0->PUSHR = (data);
	while (0 == (SPI0->SR & SPI_SR_TCF_MASK));
	SPI0->SR = SPI_SR_TCF_MASK;

}
/*It configures the SPI for transmission, this function as arguments receives a pointer to a constant structure where are all
 * the configuration parameters*/
void SPI_init(const spi_config_t* config_struct)
{
	/*Enable the clock*/
	SPI_clk(config_struct->spi_channel);

	/*GPIO pin control register configuration from struct*/
	GPIO_clock_gating(config_struct->spi_gpio_port.gpio_port_name);
	/*It needs to pins to get the output and set the clock or input*/
	GPIO_pin_control_register(config_struct->spi_gpio_port.gpio_port_name,
			config_struct->spi_gpio_port.spi_clk, &(config_struct->pin_config));
	GPIO_pin_control_register(config_struct->spi_gpio_port.gpio_port_name,
			config_struct->spi_gpio_port.spi_sout, &(config_struct->pin_config));

	/*SPI configuration of all spi parameters *use all functions above* */
	SPI_set_master(config_struct->spi_channel, config_struct->spi_master);
	SPI_fifo(config_struct->spi_channel, config_struct->spi_enable_fifo);
	SPI_clock_polarity(config_struct->spi_channel, config_struct->spi_polarity);
	SPI_frame_size(config_struct->spi_channel, config_struct->spi_frame_size);
	SPI_clock_phase(config_struct->spi_channel, config_struct->spi_phase);
	SPI_baud_rate(config_struct->spi_channel, config_struct->spi_baudrate);
	SPI_msb_first(config_struct->spi_channel, config_struct->spi_lsb_or_msb);
	SPI_enable(config_struct->spi_channel);

}
