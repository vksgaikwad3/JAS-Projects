/**************************************************************
*File:oee_h
*Description: This file contains the members and Methods of class OEE
*Date:27-03-2014
*
*
*
*
****************************************************************/

#ifndef OEE_H
#define OEE_H

#include <iostream>
#include "fsgpio_pin.h"
#include <string>	

using namespace std;

#define IN_NUM	 20
#define OUT_NUM	 8


 
 
/* GPIos on P8 Header */
/*Header pin   gpio[num]	*/

#define P8_7 	66
#define P8_8 	67
#define P8_9 	69
#define P8_10 	68
#define P8_11 	45
#define P8_12 	44
#define P8_13 	23
#define	P8_14 	26
#define P8_15 	47
#define P8_16 	46
#define P8_17 	27	
#define	P8_18 	65
#define	P8_19 	22
#define	P8_26 	61

/* GPIos on P9 Header */
#define P9_11 	30
#define	P9_12 	60
#define P9_13 	31
#define	P9_14 	50
#define	P9_15 	48
#define	P9_16 	51
#define	P9_21 	3
#define	P9_22 	2
#define	P9_23 	49	
#define	P9_24 	15
#define	P9_26 	4
#define	P9_27 	115
#define	P9_30 	112
#define	P9_41 	116
#define	P9_42 	7 

class GPIO : public FSGPIO_Pin {

 

public:
	FSGPIO_Pin* input_array[IN_NUM];
 	FSGPIO_Pin* output_array[OUT_NUM];

	int GpioInit();
	char readMachineConfig();
	string logStartTime();
	string logEndTime();
	//bool isCycleStart();
	//boot isCycleEnd();
	string getStartTime();
	string getEndTime();
	int getModelID();
	int getErrorCode();
	string getResult();

	void setPanelLed(int);
	void resetPanelLed();
};
class Authentication {

	//static string serialNumber ="3513BBBK1083";
public:
	int BBBauth();
};

#endif 	//OEE_H
