/**************************************************************************************************************************
*Name:Vikas Gaikwad
*Platform : ARM Cortex- A8(Beagle Bone Black)
*Prog.Lang:C++
*Project: OEE Firmware for Digital I/O Card
*Company: JAS
*/


/* Task Access BBB GPIOs .Here we have total 24 Digital I/O ports(signals) to BBB from PLC or from USR or Machine
*  The parameters in this Code are:
* 1.Machine ID: (Entered by user and its Fixed /but can be configurable )
* 2.Model ID: (Entered by user During Start of Shift)
* 3.Start Time (Input on single Digital GPIO pin): Its a method of detecting the edges on port pin,When Pin is "HIGH" Read  *	the RTC and LOCk the Time and store it to "Database" 
* 4.STOP Time:(Input on single Digital GPIO pin): Its a method of detecting the edges on port pin,When Pin is "HIGH" Read the *	RTC and LOCk the Time as a STOP Time();    
* 5.RESULT:The Result is also one Digital input based on Status of the final product is "PASS" or "FAIL" .This pin has to be *       monitored when STOP Time(); is LOCKED ((Result == PASS) || (Result == FAIL)). Just monitor that Pin and log to 	  *       Database.
* 6.Function: Read_RTC(), lock_RTC_time();
* 7.ERROR AND REASON CODES: In this 8 pins are assigned to the user to and monitore the port pin status, pulse coming on pin *	is the Error_Start_Time(); and the Hole Status of PORT is Error_Reason_Code(); 
*
*
***************************************************************************************************************************/

#include "fsgpio_pin.h"
#include "oee.h"
#include "database.h"


int main()
{	
	GPIO cycle,machine;				// created Objects of Class "GPIO"
	
	dB mysql;	
						//database object
	char* cycleStartTime; 
	char* cycleEndTime;
	std::string cycleResult;
	char* startDownTime;
	char* endDownTime;
	char reasonCode;
	bool flag;
	
	int errorNum;
	int modelid;
	int input_gpio[IN_NUM];
	int output_gpio[OUT_NUM];

	unsigned int PreviousState=0;
	unsigned int CurrentState;
	unsigned int EndPreviousState = 0;
	unsigned int EndCurrentState ;
	
		
	
	cycle.GpioInit();						//Import all GPIOs and set DIR,VAL as MODE
	mysql.ShowTables();						//Send Query to show tables
	
	
	//machine.readMachineConfig();					// Read the "Config file Contents 
 	
while(1)
{
	int pinMode = 1;						//read from machineConfig File
	if(pinMode == 1 || pinMode == 2)
	{
							//Single Gpio pin is used for startTime and endTime pulse
			
		CurrentState = cycle.input_array[14]->getval();
		if(PreviousState != CurrentState)			//detected rising edge for startTime
		{
			 cycleStartTime=cycle.getStartTime();	//stored in a temp varible
	   		 PreviousState = CurrentState;
		}
	}
		

	//Look for ModelID inputs
	if(cycle.getModelID() > 0)
	{
		//log into cycle table ,store in a tepm variable
		modelid= cycle.getModelID();
		
	}
		
	//Now Check for Error conditions
		
	if(cycle.getErrorCode() > 0)
	{	
		 flag = true;
		 startDownTime = cycle.getStartTime();
		 reasonCode = cycle.getErrorCode();
		 cycle.setPanelLed(reasonCode);
	
		 if(flag == true)
		{
			if(cycle.getErrorCode() == 0)				//error reset condition
			{	
		 	 endDownTime= cycle.getEndTime();
			
			 cycle.resetPanelLed();
	       
	       		//mysql.logToDownTime(startDownTime,endDownTime,reasonCode);
			}
		}
	}
	mysql.logToDownTime(startDownTime,endDownTime,reasonCode);		
	if(pinMode == 1)
	{
								//again check pin mode for End Time
		CurrentState = cycle.input_array[14]->getval();
		if(PreviousState != CurrentState)			//Detected End pulse
		{
			cycleEndTime = cycle.getEndTime();
			PreviousState = CurrentState;
		}
		
				
	}
	else if(pinMode == 2)
	{	
																
		EndCurrentState = cycle.input_array[15]->getval();// Read the Gpio pin here and store the result inCurrentState	
		if(EndPreviousState != EndCurrentState)				
			{	
				cycleEndTime= cycle.getEndTime();	//log System time as cycle End Time	
				EndPreviousState = EndCurrentState;	// Update State
			}
	
	}			
	
	cycleResult = cycle.getResult();
	
	//mysql.logToCycle(cycleStartTime,cycleEndTime,cycleResult);
	//cout <<reasonCode;	
}
return 0;

}
	






