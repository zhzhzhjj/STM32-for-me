#ifndef __MYI2C_H_
#define __MYI2C_H_

void MYI2C_Init(void);
void MYI2C_Start(void);
void MYI2C_Stop(void);
void MYI2C_SendByte(uint8_t Byte);
uint8_t MYI2C_ReceiveByte(void);
void MYI2C_SendAck(uint8_t AckBit);
uint8_t MYI2C_ReceiveAck(void);



#endif
