#include <stdio.h>
#include <unistd.h>         //Used for UART
#include <fcntl.h>          //Used for UART
#include <termios.h>        //Used for UART
#include <string.h>
#include "crc16.h"
#include "uart.h"

#define SERVER_CODE 0x01
#define CODE 0x23
#define INTERNAL_TEMP_CODE 0xC1
#define POTENT_TEMP_CODE 0xC2

int openUART() {

    int uart0_filestream = -1;

    uart0_filestream = open("/dev/serial0", O_RDWR | O_NOCTTY | O_NDELAY);      //Open in non blocking read/write mode
    if (uart0_filestream == -1)
    {
        printf("Erro - Não foi possível iniciar a UART.\n");
    }
    else
    {
        printf("UART inicializada!\n");
    }    
    struct termios options;
    tcgetattr(uart0_filestream, &options);
    options.c_cflag = B9600 | CS8 | CLOCAL | CREAD;     //<Set baud rate
    options.c_iflag = IGNPAR;
    options.c_oflag = 0;
    options.c_lflag = 0;
    tcflush(uart0_filestream, TCIFLUSH);
    tcsetattr(uart0_filestream, TCSANOW, &options);

    return uart0_filestream;

}
float readFromUART(int uart0_filestream, unsigned char subcode){

    unsigned char modbus_package[9];
    modbus_package[0] = SERVER_CODE;
    modbus_package[1] = CODE;
    modbus_package[2] = subcode;
    unsigned char matricula[4] = {7, 8, 8, 5};
    memcpy(&modbus_package[3], matricula, 4);

    short crc = calcula_CRC(modbus_package, 7);
    memcpy(&modbus_package[7], &crc, 2);

    printf("Buffers de memória criados!\n");
    
    if (uart0_filestream != -1)
    {
        printf("Escrevendo caracteres na UART ...");
        int count = write(uart0_filestream, modbus_package, 9);
        if (count < 0)
        {
            printf("UART TX error\n");
        }
        else
        {
            printf("escrito.\n");
        }
    }

    usleep(100000);

    //----- CHECK FOR ANY RX BYTES -----
    if (uart0_filestream != -1)
    {
        // Read up to 255 characters from the port if they are there
        unsigned char rx_buffer[256];
        int rx_length = read(uart0_filestream, (void*)rx_buffer, 255);      //Filestream, buffer to store in, number of bytes to read (max)
        if (rx_length < 0)
        {
            printf("Erro na leitura.\n"); //An error occured (will occur if there are no bytes)
        }
        else if (rx_length == 0)
        {
            printf("Nenhum dado disponível.\n"); //No data waiting
        }
        else
        {
            float number;
            short crcFromUart;
            unsigned char mensagem[7];
            memcpy(&number, &rx_buffer[rx_length-6], 4);
            memcpy(&crcFromUart, &rx_buffer[rx_length-2], 2);
            memcpy(mensagem, rx_buffer, 7);

            if(verifica_crc(rx_buffer, 7, crcFromUart)){
                close(uart0_filestream);
                return number;
            }else{
                close(uart0_filestream);
                return -1;
            }
        }
    }
    close(uart0_filestream);
    return -1;
}

float getInternalTemp() {

    float result = readFromUART(openUART(), INTERNAL_TEMP_CODE);
    while(result==-1){
        result = readFromUART(openUART(), INTERNAL_TEMP_CODE);
    }
    return result;
}
float getPotentiometerTemp(){
    float result = readFromUART(openUART(), POTENT_TEMP_CODE);
    while(result==-1){
        result = readFromUART(openUART(), POTENT_TEMP_CODE);
    }    
    return result;
}