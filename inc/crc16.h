/*
 * crc16.h
 *
 *  Created on: 18/03/2014
 *      Author: Renato Coral Sampaio
 */

#ifndef CRC16_H_
#define CRC16_H_
#include <stdint.h>

short CRC16(short crc, char data);
short calcula_CRC(unsigned char *commands, int size);
int verifica_crc(unsigned char *mensagem, int size, short crc_recebido);

#endif /* CRC16_H_ */
