#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include "fsgpio_pin.h"
//#include <fstream>
#include <ctime>


using namespace std;


int main()
{	
	
	int result=0;
	
//Export all GPIOs and setdirectios as IN and OUT and Activate Gpio

	FSGPIO_Pin led_pin(2);
	FSGPIO_Pin led_set(15);
	led_pin.activate();
	led_pin.setdir(1);
	led_set.activate();
	led_set.setdir(1);
	cout << "Display Output"<<endl;
	
	for(int i=0;i<10;i++)
	{	led_pin.setval(1);
		led_set.setval(1);
		usleep(100000);
		led_pin.setval(0);
		led_set.setval(0);
		usleep(1000000);	//20ms
	}
	return 0;
}
	




