#ifndef MCAL_SPI_SPI_H
#define MCAL_SPI_SPI_H


void masterInit(void);
void masterTransmit(char spiData);
char masterReceive(void);


#endif /* spi_H_ */