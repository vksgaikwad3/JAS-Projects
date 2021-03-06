#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "fsgpio_pin.h"

using namespace std;

int main (void)
{
	int result = 0;

	FSGPIO_Pin led_pin(44); 	  					//create new GPIO object to be attached to  GPIO44
	result |= led_pin						.activate(); 					//export the pin
	result |= led_pin.setdir(1); 					// Set to output

	if (result == 0)
		cout << " GPIO pins exported" << endl;
	else
	{
		cerr << "Error: A GPIO file operation failed - running as non-root?" << endl;
		exit(1);
	}

	// Do a simple toggle as fast as possible.
    while(1)
    {
		led_pin.setval(1);
		led_pin.setval(0);
    }

    cout << "Exiting....." << endl;
    return 0;
}

