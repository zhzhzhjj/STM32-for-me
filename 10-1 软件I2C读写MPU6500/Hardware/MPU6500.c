#include "stm32f10x.h"                  // Device header
#include "MYI2C.h"
#include "MPU6500_Reg.h"

#define MPU6500_Address   0xD0



void MPU6500_WriteByte(uint8_t RegAddress, uint8_t Data)
{
	uint8_t ack;

    MYI2C_Start();

    MYI2C_SendByte(MPU6500_Address);
    ack = MYI2C_ReceiveAck();
    if (ack != 0) { MYI2C_Stop(); return; }

    MYI2C_SendByte(RegAddress);
    ack = MYI2C_ReceiveAck();
    if (ack != 0) { MYI2C_Stop(); return; }

    MYI2C_SendByte(Data);
    ack = MYI2C_ReceiveAck();
    if (ack != 0) { MYI2C_Stop(); return; }

    MYI2C_Stop();
}

uint8_t MPU6500_ReceiveByte(uint8_t RegAddress)
{
	uint8_t ack, Data;

    MYI2C_Start();

    MYI2C_SendByte(MPU6500_Address);          // 写地址 0xD0
    ack = MYI2C_ReceiveAck();
    if (ack != 0) { MYI2C_Stop(); return 0; }

    MYI2C_SendByte(RegAddress);               // 寄存器地址
    ack = MYI2C_ReceiveAck();
    if (ack != 0) { MYI2C_Stop(); return 0; }

    MYI2C_Start();                            // 重复起始

    MYI2C_SendByte(MPU6500_Address | 0x01);   // 读地址 0xD1
    ack = MYI2C_ReceiveAck();
    if (ack != 0) { MYI2C_Stop(); return 0; }

    Data = MYI2C_ReceiveByte();               // 读一个字节
    MYI2C_SendAck(1);                         // NACK，表示不再读
    MYI2C_Stop();

    return Data;                              // 必须返回
	
}


void MPU6500_Init()
{
	MYI2C_Init();
	MPU6500_WriteByte(MPU6500_PWR_MGMT_1, 0x01);		//电源管理寄存器1，取消睡眠模式，选择时钟源为X轴陀螺仪
	MPU6500_WriteByte(MPU6500_PWR_MGMT_2, 0x00);		//电源管理寄存器2，保持默认值0，所有轴均不待机
	MPU6500_WriteByte(MPU6500_SMPLRT_DIV, 0x09);		//采样率分频寄存器，配置采样率
	MPU6500_WriteByte(MPU6500_CONFIG, 0x06);			//配置寄存器，配置DLPF
	MPU6500_WriteByte(MPU6500_GYRO_CONFIG, 0x18);	//陀螺仪配置寄存器，选择满量程为±2000°/s
	MPU6500_WriteByte(MPU6500_ACCEL_CONFIG, 0x18);	//加速度计配置寄存器，选择满量程为±16g
}

uint8_t MPU6500_GetID(void)
{
	return MPU6500_ReceiveByte(MPU6500_WHO_AM_I);		//返回WHO_AM_I寄存器的值
}

void MPU6500_GetData(int16_t *AccX, int16_t *AccY, int16_t *AccZ, 
						int16_t *GyroX, int16_t *GyroY, int16_t *GyroZ)
{
	uint8_t DataH, DataL;								//定义数据高8位和低8位的变量
	
	DataH = MPU6500_ReceiveByte(MPU6500_ACCEL_XOUT_H);		//读取加速度计X轴的高8位数据
	DataL = MPU6500_ReceiveByte(MPU6500_ACCEL_XOUT_L);		//读取加速度计X轴的低8位数据
	*AccX = (DataH << 8) | DataL;					//数据拼接，通过输出参数返回
	                                
	DataH = MPU6500_ReceiveByte(MPU6500_ACCEL_YOUT_H);		//读取加速度计Y轴的高8位数据
	DataL = MPU6500_ReceiveByte(MPU6500_ACCEL_YOUT_L);		//读取加速度计Y轴的低8位数据
	*AccY = (DataH << 8) | DataL;					//数据拼接，通过输出参数返回
	                                
	DataH = MPU6500_ReceiveByte(MPU6500_ACCEL_ZOUT_H);		//读取加速度计Z轴的高8位数据
	DataL = MPU6500_ReceiveByte(MPU6500_ACCEL_ZOUT_L);		//读取加速度计Z轴的低8位数据
	*AccZ = (DataH << 8) | DataL;					//数据拼接，通过输出参数返回
	                                
	DataH = MPU6500_ReceiveByte(MPU6500_GYRO_XOUT_H);		//读取陀螺仪X轴的高8位数据
	DataL = MPU6500_ReceiveByte(MPU6500_GYRO_XOUT_L);		//读取陀螺仪X轴的低8位数据
	*GyroX = (DataH << 8) | DataL;					//数据拼接，通过输出参数返回
	                                
	DataH = MPU6500_ReceiveByte(MPU6500_GYRO_YOUT_H);		//读取陀螺仪Y轴的高8位数据
	DataL = MPU6500_ReceiveByte(MPU6500_GYRO_YOUT_L);		//读取陀螺仪Y轴的低8位数据
	*GyroY = (DataH << 8) | DataL;					//数据拼接，通过输出参数返回
	                                
	DataH = MPU6500_ReceiveByte(MPU6500_GYRO_ZOUT_H);		//读取陀螺仪Z轴的高8位数据
	DataL = MPU6500_ReceiveByte(MPU6500_GYRO_ZOUT_L);		//读取陀螺仪Z轴的低8位数据
	*GyroZ = (DataH << 8) | DataL;						//数据拼接，通过输出参数返回
}


