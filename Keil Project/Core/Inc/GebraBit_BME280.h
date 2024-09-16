/*
 * ________________________________________________________________________________________________________
 * Copyright (c) 2020 GebraBit Inc. All rights reserved.
 *
 * This software, related documentation and any modifications thereto (collectively “Software”) is subject
 * to GebraBit and its licensors' intellectual property rights under U.S. and international copyright
 * and other intellectual property rights laws. 
 *
 * GebraBit and its licensors retain all intellectual property and proprietary rights in and to the Software
 * and any use, reproduction, disclosure or distribution of the Software without an express license agreement
 * from GebraBit is strictly prohibited.
 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT 
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT IN  
 * NO EVENT SHALL GebraBit BE LIABLE FOR ANY DIRECT, SPECIAL, INDIRECT, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, 
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
 * OF THE SOFTWARE.
 * @Author       	: Mehrdad Zeinali
 * ________________________________________________________________________________________________________
 */
#ifndef	_BME280__H_
#define	_BME280__H_
#include "main.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "spi.h"
#include "string.h"
#include "math.h"

/************************************************
 *         USER BANK 0 REGISTER MAP             *
 ***********************************************/ 
#define BME280_ID                            (0xD0)
#define BME280_RESET                         (0xE0)
#define BME280_TEMP_PRESS_CALIB00_CALIB25    (0x88)//0x88 TO 0xA1
#define BME280_HUMIDITY_CALIB26_CALIB41      (0xE1)//0xE1 TO 0xE7
#define BME280_CTRL_MEAS                     (0xF4)
#define BME280_CTRL_HUM                      (0xF2)
#define BME280_CONFIG                        (0xF5)
#define BME280_DATA_ADDR                     (0xF7)//PRESS_MSB
#define BME280_STATUS                        (0xF3) 
/*----------------------------------------------*
 *           USER REGISTER MAP End              *
 *----------------------------------------------*/ 

/************************************************
 *         MSB Bit Start Location Begin         *
 ***********************************************/ 
#define START_MSB_BIT_AT_0                    0
#define START_MSB_BIT_AT_1                    1
#define START_MSB_BIT_AT_2                    2
#define START_MSB_BIT_AT_3                    3
#define START_MSB_BIT_AT_4                    4
#define START_MSB_BIT_AT_5                    5
#define START_MSB_BIT_AT_6                    6
#define START_MSB_BIT_AT_7                    7
/*----------------------------------------------*
 *        MSB Bit Start Location End            *
 *----------------------------------------------*/ 
/************************************************
 *          Bit Field Length Begin              *
 ***********************************************/ 
#define BIT_LENGTH_1                          1
#define BIT_LENGTH_2                          2
#define BIT_LENGTH_3                          3
#define BIT_LENGTH_4                          4
#define BIT_LENGTH_5                          5
#define BIT_LENGTH_6                          6
#define BIT_LENGTH_7                          7
#define BIT_LENGTH_8                          8
/*----------------------------------------------*
 *          Bit Field Length End                *
 *----------------------------------------------*/
 /************************************************
 *          Register Values Begin                *
 ***********************************************/ 
#define BME280_SOFT_RESET_CMD                      0xB6
#define BME280_FIFO_FLUSH_CMD                      0xB0
#define BME280_TURN_SENSOR_OFF                     0
#define PRESS_TEMP_CALIBRATION_DATA_BUFFER_SIZE    26
#define HUMIDITY_CALIBRATION_DATA_BUFFER_SIZE      7
#define REGISTER_RAW_DATA_BYTE_QTY                 8   
#define SEA_LEVEL_PRESSURE									     	101325
/*----------------------------------------------*
 *           Register Values End                *
 *----------------------------------------------*/
/*
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/**************************************************
 *     Values For Disable And Enable Functions    *
 **************************************************/ 
typedef enum Ability 
{  
	Disable = 0     ,                      
	Enable     
}BME280_Ability;        
/**************************************************
 *      			  Values For Power Mode     		    *
 **************************************************/ 
typedef enum Power_Mode
{
	SLEEP_MODE  = 0,        							
	FORCED_MODE = 1, 											                   
	NORMAL_MODE = 3
} BME280_Power_Mode;
/**************************************************************
 *        				 Values For Oversampling			    		      *
 **************************************************************/ 
typedef enum Pressure_Oversampling
{										
	 X1_OVERSAMPLING    = 1 , 									
	 X2_OVERSAMPLING    = 2 ,										  
	 X4_OVERSAMPLING    = 3 ,                    
	 X8_OVERSAMPLING    = 4 ,											
	 X16_OVERSAMPLING   = 5		                  
} BME280_Sensor_Oversampling;
/**************************************************************
 *        						Values For StandBy Time 	   			      *
 **************************************************************/ 
typedef enum Inactive_Duration
{
	 INACTIVE_DURATION_5_mS        = 0 ,                  
	 INACTIVE_DURATION_62P5_mS     = 1 ,									
	 INACTIVE_DURATION_125_mS      = 2 ,									
	 INACTIVE_DURATION_250_mS      = 3 ,
	 INACTIVE_DURATION_500_mS      = 4 ,                  
	 INACTIVE_DURATION_1000_mS     = 5 ,									
	 INACTIVE_DURATION_10_mS       = 6 ,									
	 INACTIVE_DURATION_20_mS       = 7 
} BME280_Inactive_Duration;
/**************************************************************
 *        				Values For Filter Coefficient      	 			  *
 **************************************************************/ 
typedef enum IIR_Filter_Coefficient
{
	 FILTER_OFF             = 0 ,                  
	 FILTER_COEFFICIENT_2   = 1 ,									
	 FILTER_COEFFICIENT_4   = 2 ,									
	 FILTER_COEFFICIENT_8   = 3 ,
	 FILTER_COEFFICIENT_16  = 4 
} BME280_IIR_Filter_Coefficient;
/*************************************************
 *         Values For Data Preparation           *
 **************************************************/ 
typedef enum Preparation
{  
	IS_Ready = 0     ,                      
	IS_NOT_Ready     
}BME280_Preparation;
/*************************************************
 *           Values For Reset Process             *
 **************************************************/ 
typedef enum 
{  
	DONE     = 0     ,                      
	FAILED   = 1    
}BME280_Reset_Status;

 /*************************************************
 *  Defining BME280 Register & Data As Struct   *
 **************************************************/
typedef	struct BME280
{
	  uint8_t                       	REGISTER_CACHE;
	  BME280_Reset_Status         		RESET;
	  uint8_t                       	DEVICE_ID;
	  BME280_Preparation							CONVERSION_RESULT;
	  BME280_Preparation							NVM_DATA;
		BME280_Power_Mode 				  	  POWER_MODE;
		BME280_Ability                  TEMPERATURE;
		BME280_Ability                  PRESSURE;
		BME280_Ability                  HUMIDITY;
	  BME280_Sensor_Oversampling			TEMPERATURE_OVERSAMPLING;
	  BME280_Sensor_Oversampling			PRESSURE_OVERSAMPLING;
	  BME280_Sensor_Oversampling			HUMIDITY_OVERSAMPLING;
	  BME280_IIR_Filter_Coefficient   IIR_FILTER_TIME_CONATANT;
	  BME280_Inactive_Duration        INACTIVE_DURATION;
		uint8_t 												PRESS_TEMP_CALIBRATION_DATA[PRESS_TEMP_CALIBRATION_DATA_BUFFER_SIZE];
		uint8_t 												HUMIDITY_CALIBRATION_DATA[HUMIDITY_CALIBRATION_DATA_BUFFER_SIZE];
    int32_t 												dig_t1;
    int32_t 												dig_t2;
    int32_t 												dig_t3;
    uint16_t 												dig_p1;
    int16_t 												dig_p2;
    int16_t 												dig_p3;
    int16_t 												dig_p4;
    int16_t												 	dig_p5;
    int16_t 												dig_p6;
    int16_t 												dig_p7;
    int16_t 												dig_p8;
    int16_t 												dig_p9;
    int32_t 												dig_h1;
    int32_t 												dig_h2;
    int32_t 												dig_h3;
    int32_t 												dig_h4;
    int32_t 												dig_h5;
    int32_t 												dig_h6;
		int32_t 												FINE_TEMP_RESOLUTIN;
		uint8_t 												REGISTER_RAW_DATA_BUFFER[REGISTER_RAW_DATA_BYTE_QTY];
		uint32_t 											  REGISTER_RAW_PRESSURE;
		uint32_t 												REGISTER_RAW_TEMPERATURE;
		uint32_t 												REGISTER_RAW_HUMIDITY;
		double 													COMPENSATED_TEMPERATURE;
	  double 													COMPENSATED_PRESSURE;
		double 													ALTITUDE;
		double 													COMPENSATED_HUMIDITY;
}GebraBit_BME280;
/*
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: */
/********************************************************
 *Declare Read&Write BME280 Register Values Functions *
 ********************************************************/
extern	uint8_t	GB_BME280_Read_Reg_Data ( uint8_t regAddr,uint8_t* data);
extern	uint8_t GB_BME280_Read_Reg_Bits (uint8_t regAddr,uint8_t start_bit, uint8_t len, uint8_t* data);
extern	uint8_t GB_BME280_Burst_Read(uint8_t regAddr,uint8_t *data, uint16_t byteQuantity);
extern	uint8_t GB_BME280_Write_Reg_Data(uint8_t regAddr, uint8_t data);
extern	uint8_t	GB_BME280_Write_Reg_Bits(uint8_t regAddr, uint8_t start_bit, uint8_t len, uint8_t data);
extern	uint8_t GB_BME280_Burst_Write		( uint8_t regAddr,uint8_t *data, 	uint16_t byteQuantity);
/********************************************************
 *       Declare BME280 Configuration Functions       *
 ********************************************************/
extern void GB_BME280_Soft_Reset ( GebraBit_BME280 * BME280 );
extern void	GB_BME280_Get_Device_ID(GebraBit_BME280 * BME280);
extern void GB_BME280_Check_NVM_Data(GebraBit_BME280 * BME280 ) ;
extern void GB_BME280_Check_Conversion_Transferred_Register(GebraBit_BME280 * BME280 );
extern void GB_BME280_Turn_Humidity_OFF(GebraBit_BME280* BME280);
extern void GB_BME280_Humidity_OverSampling(GebraBit_BME280* BME280 ,BME280_Sensor_Oversampling hum_over);
extern void GB_BME280_Turn_Temperature_OFF(GebraBit_BME280* BME280);
extern void GB_BME280_Temperature_OverSampling(GebraBit_BME280* BME280 ,BME280_Sensor_Oversampling temp_over);
extern void GB_BME280_Turn_Pressure_OFF(GebraBit_BME280* BME280);
extern void GB_BME280_Pressure_OverSampling(GebraBit_BME280* BME280 ,BME280_Sensor_Oversampling press_over);
extern void GB_BME280_Power_Mode(GebraBit_BME280* BME280 ,BME280_Power_Mode pmode);
extern void GB_BME280_Inactive_Duration(GebraBit_BME280 * BME280 , BME280_Inactive_Duration dur ) ;
extern void GB_BME280_IIR_Filter_Coefficient (GebraBit_BME280 * BME280 , BME280_IIR_Filter_Coefficient filter);
extern void GB_BME280_Power_Mode(GebraBit_BME280* BME280 ,BME280_Power_Mode pmode);
extern void GB_BME280_Calculate_Calibration_Coefficients(GebraBit_BME280 * BME280) ;
extern void GB_BME280_Twos_Complement_Converter(int32_t *value, uint8_t length) ;
extern void GB_BME280_Compensate_Temperature(GebraBit_BME280 * BME280) ;
extern void GB_BME280_Compensate_Pressure(GebraBit_BME280 * BME280) ;
extern void GB_BME280_Compensate_Humidity(GebraBit_BME280 * BME280);

/********************************************************
 *          Declare BME280 DATA Functions               *
 ********************************************************/
extern void GB_BME280_Get_Register_Raw_Pressure_Temperature_Humidity(GebraBit_BME280 * BME280 );
extern void GB_BME280_Altitude(GebraBit_BME280 * BME280);
extern void GB_BME280_Get_Data(GebraBit_BME280 * BME280 );
/********************************************************
 *          Declare BME280 HIGH LEVEL Functions       *
 ********************************************************/
extern void GB_BME280_initialize( GebraBit_BME280 * BME280 );
extern void GB_BME280_Configuration(GebraBit_BME280 * BME280);

#endif
