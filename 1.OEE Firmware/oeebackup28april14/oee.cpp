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

string GPIO::logStartTime() {							// Methods to Get the RTC time

	char timeData[50];
	string startTime;
		
	time_t now = time(0);
	strftime(timeData,50,"%Y-%m-%d %H:%M:%S",std::localtime(&now));
	startTime = timeData;
	
return(startTime);		
}


/*========================================================================================================
	File: oee.cpp
	Description: This method locks the end time
	Method: log_end_time()	
==========================================================================================================*/

string GPIO::logEndTime() {							// Methods to record the RTC time 

	char timeData[50];
	string endTime;
		
	time_t now = time(0);
	strftime(timeData,50,"%Y-%m-%d %H:%M:%S",std::localtime(&now));
	endTime = timeData;
		
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

bool value0 = not input_array[0]->getval();	//LSB pin
bool value1 = not input_array[1]->getval();
bool value2 = not input_array[2]->getval();
bool value3 = not input_array[3]->getval();	//MSB pin	
//printf("%d",value0);
	uint8_t  modelPin[] = {value0,value1,value2,value3};
	uint8_t  modelNum=0,tempModelNum;
	
	for(int i=0 ;i<= 3;i++)
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


bool value0 = not input_array[4]->getval();		//LSB error pin
bool value1 = not input_array[5]->getval();
bool value2 = not input_array[6]->getval();
bool value3 = not input_array[7]->getval();
bool value4 = not input_array[8]->getval();
bool value5 = not input_array[9]->getval();
bool value6 = not input_array[10]->getval();
bool value7 = not input_array[11]->getval();		//MSB error pin
		 
//cout<<value0;
	uint8_t errorCode[] = {value0,value1,value2,value3,value4,value5,value6,value7};
	uint8_t  errorNum=0,tempErrorNum;
	
	for(int i=0 ;i<= 7;i++)
	{
		errorNum |= (errorCode[i] << i);
	}
	//cout << errorNum;
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

	for(int i=0;i<8;i++) {
	output_array[i]-> setval(0);
	}
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
	case 4: output_array[2]-> setval(1);break;
	case 8: output_array[3]-> setval(1);break;
	case 16: output_array[4]-> setval(1);break;
	case 32: output_array[5]-> setval(1);break;
	case 64: output_array[6]-> setval(1);break;
	case 128: output_array[7]-> setval(1);break;
}	
return;
}

/*========================================================================================================
	File: oee.cpp
	Description: This Methods detects the Start Time Pulse on GPIO of BBB
	class: OEE	
	Method: getStartTime()	
==========================================================================================================*/

string GPIO::getStartTime()
{
	
	return(logStartTime());
}

/*========================================================================================================
	File: oee.cpp
	Description: This Methods  detects the End Time Pulse on GPIO of BBB.
	class: OEE	
	Method: getEndTime()	
==========================================================================================================*/

string GPIO::getEndTime()
{
	return(logEndTime());
}


/*========================================================================================================
	File: oee.cpp
	Description: This Methods returns the final status of the cycle, Reads the pulse on GPIO of BBB
	class: OEE	
	Method: getResult()	
==========================================================================================================*/

string GPIO::getResult() {

	string result;	
		if((input_array[12]-> getval())!= 0)
		{	
			result ="Pass"; 
			return(result);		//if True then Result is "PASS else FAIL"
		}
		else 
		 	result = "Fail";
			return(result);
}

/*========================================================================================================
	File: oee.cpp
	Description: This Methods returns the final status of the cycle, Reads the pulse on GPIO of BBB
	class: MACHINE
	Method: readMachinePinMode()
==========================================================================================================*/

char GPIO::getMachinePinMode() {

	const int size = 100;
	char fileData[size];
	string modeNum = "1";
	string newModeNum;
	
	ifstream machine_para;				//creates an instance of ifstream "machine_para"
	machine_para.open("INF.txt");	//open the file
	//cout << "contents of Config File \n";
	for(int i=0;i<3;i++)
	{
		if(machine_para.eof() !=0)
		{
			cout << "exit from File \n";
			exit(1);
		}
		machine_para.getline(fileData,size);
		//cout << fileData[34]<< "\n";
	    newModeNum = fileData[9]<<'\n';
	}
	int num = modeNum.compare(newModeNum);
	if(num ==0)
	{
		return(1);
	}
	else return(2);
}	

/*========================================================================================================
	File: oee.cpp

	Description: This Methods returns the final status of the cycle, Reads the pulse on GPIO of BBB

	class: MACHINE
	Method: getMachineID()
==========================================================================================================*/

string GPIO::getMachineID() {

	const int size = 100;
	char fileData[size],tempID[3];
	string newMachineID;
	
	ifstream machine_para;				//creates an instance of ifstream "machine_para"
	machine_para.open("INF.txt");	//open the file
	//cout << "contents of Config File \n";
	for(int i=0;i<2;i++)
	{
		if(machine_para.eof() !=0)
		{
			cout << "exit from File \n";
			exit(1);
		}
		machine_para.getline(fileData,size);
		//cout << fileData[34]<< "\n";
		for(int count =10;count<12;count++) {
	    	tempID[count -10]= fileData[count];
	    } 
	    newMachineID = tempID;
	}
	return(newMachineID);
}	



/*========================================================================================================
	File: oee.cpp
	Description: This Methods returns the final status of the cycle, Reads the pulse on GPIO of BBB
	class: MACHINE
	Method: getCustomerID()
==========================================================================================================*/

string GPIO::getCustomerID() {

	const int size = 100;
	char fileData[size];
	char tempCustomerID[6];
	string newCustomerID;
	
	ifstream machine_para;				//creates an instance of ifstream "machine_para"
	machine_para.open("INF.txt");		//open the file
	//cout << "contents of Config File \n";
	for(int i=0;i<1;i++)
	{
		if(machine_para.eof() !=0)
		{
			cout << "exit from File \n";
			exit(1);
		}
		machine_para.getline(fileData,size);
		//cout << fileData[34]<< "\n";
		for(int count=11;count<16;count++) {
	    	tempCustomerID[count -11] = fileData[count]; 		//store CustomerID in a string
	    }
	    newCustomerID = tempCustomerID;
	}
	return(newCustomerID);
}	

/*========================================================================================================

	File: oee.cpp

	Description: This Methods will check for BBB Authentications like serial num,board-name,header,revsion etc

	class: Authentication
	Method: BBBauth()
==========================================================================================================*/

int Authentication :: BBBauth() 
{
	int size=50;
	char serialData[size];
	char boardData[size];
	char headerData[size];
	char revisionNum[size];
	string serialkey ="3513BBBK1083";
	string boardName ="A335BNLT";
	string header ="aa 55 33 ee";
	string revision ="0A5C";
	
	string Skey,Bname,Hdr,Rvsn;
	
	ifstream serialFile,boardFile,headerFile,revisionFile;				//creates an instance of ifstream "file"
	serialFile.open("/sys/devices/bone_capemgr.8/baseboard/serial-number");		//open the file
/* Check for Serial number */	
	cout << "contents of Config File \n";
	for(int i=0;i<1;i++)
	{
		if(serialFile.eof() !=0)
		{
			cout << "exit from File \n";
			exit(1);
		}
		serialFile.getline(serialData,size);
	}
		
	Skey = serialData;
	int Snum = serialkey.compare(Skey);
	cout <<Snum<<'\n';
/* Check for Board-Name	*/
	boardFile.open("/sys/devices/bone_capemgr.8/baseboard/board-name");
	for(int i=0;i<1;i++)
	{
		if(boardFile.eof() !=0)
		{
			cout << "exit from File \n";
			exit(1);
		}
		boardFile.getline(boardData,size);
	}
	Bname = boardData;
	int Bnum = boardName.compare(Bname);
	cout<<Bnum<<'\n';
/* Check for Header Num */
	headerFile.open("/sys/devices/bone_capemgr.8/baseboard/header");
	for(int i=0;i<1;i++)
	{
		if(headerFile.eof() !=0)
		{
			cout << "exit from File \n";
			exit(1);
		}
		headerFile.getline(headerData,size);
	}
	Hdr = headerData;
	int Hnum = header.compare(Hdr);
	cout<<Hnum<<'\n';
/* check for Revioson Num */	
	revisionFile.open("/sys/devices/bone_capemgr.8/baseboard/revision");
	for(int i=0;i<1;i++)
	{
		if(revisionFile.eof() !=0)
		{
			cout << "exit from File \n";
			exit(1);
		}
		revisionFile.getline(revisionNum,size);
	}
	Rvsn = revisionNum;
	int Rsnum = revision.compare(Rvsn);
	cout<<Rsnum<<'\n';
	
	if(Snum ==0 && Bnum ==0 && Hnum ==0 && Rsnum ==0)
	{
		cout << "all parameters are match correctly"<<'\n';
		return (1);
	}
	else cout <<" Auth Fail Please try again"<<'\n';
	return(0);
}
	
	
	
	
	
	
	
	
	
