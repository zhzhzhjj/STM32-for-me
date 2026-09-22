#ifndef __MPU6500_H_
#define __MPU6500_H_

void MPU6500_Init();
void MPU6500_WriteByte(uint8_t RegAddress, uint8_t Data);
uint8_t MPU6500_ReceiveByte(uint8_t RegAddress);
void MPU6500_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
						int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ);
uint8_t MPU6500_GetID(void);

#endif
