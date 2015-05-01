#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include "fsgpio_pin.h"
//#include <fstream>
#include <ctime>
#include <inttypes.h>


using namespace std;

void getModelID();
void edgeDetect();

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
	FSGPIO_Pin* input_array[IN_NUM];
 	FSGPIO_Pin* output_array[OUT_NUM];


int input_gpio[] ={P8_7,P8_9,P8_11,P8_13,
		   P8_15,P8_17,P8_19,P8_26,
		   P8_18,P8_16,P8_14,P8_12,
		   P8_10,P8_8,P9_11,P9_13,
		   P9_15,P9_21,P9_23,P9_27 };
				   
int output_gpio[] = {P9_14,P9_12,P9_16,P9_22,P9_24,P9_26,P9_30,P9_42};


int main()
{	
	
	int result=0;
	
//Export all GPIOs and setdirectios as IN and OUT and Activate Gpio

/*	FSGPIO_Pin led_pin(2);
	FSGPIO_Pin led_set(15);
	led_pin.activate();
	led_pin.setdir(0);
	led_set.activate();
	led_set.setdir(0);
	cout << "Display Output"<<endl;
	
	for(int i=0;i<10;i++)
	{	cout<<led_pin.getval()<<'\n';
		cout<<led_set.getval()<<'\n';
				
		usleep(100000);
		cout<<led_pin.getval()<<'\n';
		cout<<led_set.getval()<<'\n';
		usleep(1000000);	//20ms
	}
	return 0;
}	*/


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
	for(int i=0;i<10;i++)
	{
		edgeDetect();
		getModelID();
	}
return 0;
}

void getModelID()
{
	bool value0 = not input_array[0]->getval();
	bool value1 = not input_array[1]->getval();
	bool value2 = not input_array[2]->getval();
	bool value3 = not input_array[3]->getval();
	
	uint8_t no[8]={value0,value1,value2,value3};
	uint8_t num=0;
	
	for(int i=0;i<=7;i++)
	printf("%d",no[i]);
	for(int i=0;i<=3;i++)
	{
		num |= (no[i] << i);
	}
	printf("\n%d",num);
	
		
}

void edgeDetect()
{
	bool previous=1;
	bool current;
	current=input_array[14]->getval();
	if(previous != current)
	{	previous =current;
		cout <<"detected falling edge"<<'\n';
	}
	else cout <<"In a HIGH State Only";
}

	




