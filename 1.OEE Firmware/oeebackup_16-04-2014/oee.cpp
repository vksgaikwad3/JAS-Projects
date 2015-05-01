/**************************************************************
*File:oee.cpp
*Description: This file contains the  Methods of class OEE
*Date:27-03-2014
*
*
*
*
****************************************************************/

#include "oee.h"
#include "fsgpio_pin.h"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <ctime>
#include <string>

using namespace std;

 



/*========================================================================================================
	File: oee.cpp/
	Description: This File Contains the Methods of configuring the Beagle Bone Black Hardware
	class: OEE	
	Method: GpioInit()	
==========================================================================================================*/
int GPIO::GpioInit() {

/* GPIOs numbers */

int input_gpio[] ={P8_7,P8_9,P8_11,P8_13,
		   P8_15,P8_17,P8_19,P8_26,
		   P8_18,P8_16,P8_14,P8_12,
		   P8_10,P8_8,P9_11,P9_13,
		   P9_15,P9_21,P9_23,P9_27 };
				   
int output_gpio[] = {P9_14,P9_12,P9_16,P9_22,P9_24,P9_26,P9_30,P9_42};
/* Import and Set Direction and Activate the all GPIOs */

	for(int pin=0;pin < IN_NUM;pin++)
	{
		FSGPIO_Pin* temp_gpio = new FSGPIO_Pin();
		temp_gpio->import_pin(input_gpio[pin]);
		cout << input_gpio[pin] <<endl;	
		temp_gpio->activate();
		temp_gpio->setdir(0);				//set as Input pins
		input_array[pin] = temp_gpio;		// store referance of Instances
	}

	for(int pin=0;pin < OUT_NUM;pin++)
	{
		FSGPIO_Pin* temp_gpio = new FSGPIO_Pin();
		temp_gpio->import_pin(output_gpio[pin]);
		cout << output_gpio[pin] <<endl;	
		temp_gpio->activate();
		temp_gpio->setdir(1);				//set as output pins
		output_array[pin] = temp_gpio;		// store referance of Instances
	}
	return(0);	
}



/*========================================================================================================
	File: oee.cpp
	Description: This method locks the start time 
	Method: log_start_time()	
==========================================================================================================*/

char* GPIO::logStartTime() {							// Methods to Get the RTC time

	char* local_time;
	char* startTime;
		
	time_t now = time(0);
	local_time = ctime(&now);
	startTime = local_time;
	
return(startTime);		
}


/*========================================================================================================
	File: oee.cpp
	Description: This method locks the end time
	Method: log_end_time()	
==========================================================================================================*/

char* GPIO::logEndTime() {							// Methods to record the RTC time 

	char* local_time;
	char* endTime; 
	
	time_t now = time(0);
	local_time = ctime(&now);
	endTime = local_time;	
	
return(endTime);								
}


/*========================================================================================================
	File: oee.cpp
	Description: This Method returns the ModelID and load into database tables
	class: OEE	
	Method: GetModelID()	
==========================================================================================================*/

int GPIO::getModelID() {
/* Total 4 GPIOs are assign for the Machine ID 2^6 = 64 combinations */
// P8_7,P8_8,P8_9,P8_10

bool value0 = input_array[0]->getval();	//LSB pin
bool value1 = input_array[1]->getval();
bool value2 = input_array[2]->getval();
bool value3 = input_array[3]->getval();	//MSB pin	
//printf("%d",value0);
	uint8_t  modelPin[8] = {value0,value1,value2,value3};
	uint8_t  modelNum=0,tempModelNum;
	
	
	for(int i=0 ;i<= 4;i++)
	{	
		modelNum |= (modelPin[i] << i);
	}
	tempModelNum = modelNum;			//store model_num in a temporary variable
	
return (modelNum);								             																													                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
}



/*========================================================================================================
	File: oee.cpp
	Description: This method returns the Error code and send code into database
	class: OEE	
	Method: GetError_code()	
==========================================================================================================*/

int GPIO::getErrorCode() {
/*Total 8 GPIOs are assign for the Error code */
/* P8_11,P8_12,P8_13,P8_14,P8_15,P8_16,P8_17,P8_18 */


bool value0 = ~(input_array[4]->getval());		//LSB error pin
bool value1 = ~(input_array[5]->getval());
bool value2 = ~(input_array[6]->getval());
bool value3 = ~(input_array[7]->getval());
bool value4 = ~(input_array[8]->getval());
bool value5 = ~(input_array[9]->getval());
bool value6 = ~(input_array[10]->getval());
bool value7 = ~(input_array[11]->getval());		//MSB error pin
		 
cout<<value0;
	uint8_t errorCode[] = {value0,value1,value2,value3,value4,value5,value6,value7};
	uint8_t  errorNum=0,tempErrorNum;
	
	for(int i=0 ;i<= 8;i++)
	{
		errorNum |= (errorCode[i] << i);
	}
	
	tempErrorNum = errorNum;				//store in temporary variable
	
return(errorNum);

}

/*========================================================================================================
	File: oee.cpp
	Description: This Methods to Reset  the panel Leds
	class: OEE	
	Method: ResetPanelLed()	
==========================================================================================================*/
void GPIO::resetPanelLed() {

	output_array[0]-> setval(0);
	output_array[1]-> setval(0);
	output_array[2]-> setval(0);
	output_array[3]-> setval(0);
	output_array[4]-> setval(0);
	output_array[5]-> setval(0);
	output_array[6]-> setval(0);
	output_array[7]-> setval(0);
	
return;
}


/*========================================================================================================
	File: oee.cpp
	Description: This Methods to set  the panel Leds
	class: OEE	
	Method: SetPanelLed()	
==========================================================================================================*/
void GPIO::setPanelLed(int errorNum) {

	int choice = errorNum;
switch(choice)
{
	case 1: output_array[0]-> setval(1);break;
	case 2: output_array[1]-> setval(1);break;
	case 3: output_array[2]-> setval(1);break;
	case 4: output_array[3]-> setval(1);break;
	case 5: output_array[4]-> setval(1);break;
	case 6: output_array[5]-> setval(1);break;
	case 7: output_array[6]-> setval(1);break;
	case 8: output_array[7]-> setval(1);break;
}	
return;
}

/*========================================================================================================
	File: oee.cpp
	Description: This Methods to get the ReasonCode for error
	class: OEE	
	Method: GetReasonCode()	
==========================================================================================================

int DOWNTIME::GetReasonCode()
{
    return(GetErrorCode());
}						*/
/*========================================================================================================
	File: oee.cpp
	Description: This Methods detects the Start Time Pulse on GPIO of BBB
	class: OEE	
	Method: GetStartTime()	
==========================================================================================================*/

char* GPIO::getStartTime()
{
	
	return(logStartTime());
}



/*========================================================================================================
	File: oee.cpp
	Description: This Methods  detects the End Time Pulse on GPIO of BBB.
	class: OEE	
	Method: GetEndTime()	
==========================================================================================================*/

char* GPIO::getEndTime()
{
	return(logEndTime());
}


/*========================================================================================================
	File: oee.cpp
	Description: This Methods returns the final status of the cycle, Reads the pulse on GPIO of BBB
	class: OEE	
	Method: GetResult()	
==========================================================================================================*/

std::string GPIO::getResult() {

	std::string result;	
		if((input_array[12]-> getval())!= 0)
		{	
			result ="pass"; 
			return(result);		//if True then Result is "PASS else FAIL"
		}
		else 
		 	result = "fail";
			return(result);
		
}


/*========================================================================================================
	File: oee.cpp
	Description: This Methods returns the final status of the cycle, Reads the pulse on GPIO of BBB
	class: MACHINE
	Method: ReadMachineConfig()
==========================================================================================================*/

char GPIO::readMachineConfig() {

	const int size = 50;
	char line[size];
	
	ifstream machine_para;				//creates an instance of ifstream "machine_para"
	machine_para.open("config.txt");	//open the file
	cout << "contents of Config File \n";
	for(int i=0;i<=4;i++)
	{
		if(machine_para.eof() !=0)
		{
			cout << "exit from File \n";
			exit(1);
		}
		machine_para.getline(line,size);
		cout << line << "\n";
	}
	return 0;
}		 
