#ifndef FSGPIO_PIN_H
#define FSGPIO_PIN_H

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

#define	STR_EXPORT_FN  		"/sys/class/gpio/export"
#define	STR_UNEXPORT_FN		"/sys/class/gpio/unexport"
#define STR_GPIO_PRE		"/sys/class/gpio/gpio"
#define	STR_VALUE_POST		"/value"
#define	STR_DIR_POST		"/direction"
#define	STR_EDGE_POST		"/edge"
#define	STR_ACTLOW_POST		"/active-low"
#define	STR_OUT				"out"
#define	STR_IN				"in"
#define	STR_HIGH			"1"
#define	STR_LOW				"0"

enum FSGPIO_CONSTANTS
{
	MAX_GPIO 	= 125,
	HIGH 			= 1,
	LOW 			= 0,
	INPUT 			= 0,
	OUTPUT 		= 1
};

enum FSGPIO_ERRORS
{
	FSGPIO_GENERR 	= -1,
	FSGPIO_FILEERR 	= -2,
	FSGPIO_RDYERR		= -3
};

class FSGPIO_Pin
{

/* FSGPIO_Pin
 * Purpose: Represents a
 */
 private:
    string m_sGPIONum; 		// GPIO number associated with the instance of an object
    int	m_GPIONum;		// Integer representing the GPIO pin number this object controls
    int	m_active;	// String representing the GPIO pin number this oject controls (used for file operations)

    ofstream	m_GPIODirOutFile;		// The direction file for this GPIO pin ,"ofstream" write to file.
    ifstream	m_GPIODirInFile;		// ifstream Read from File
    ofstream	m_GPIOValOutFile;	// The value file fot this GPIO pin.
    ifstream	m_GPIOValInFile;

public:
    FSGPIO_Pin();  		// create a GPIO object that controls GPIO45 default
    FSGPIO_Pin(int num);	// create a GPIO object that controls GPIO(name), where name is passed to this constructor
    int import_pin(int num);
    int connectGPIO(int num);		// connect object to a GPIO pin.
    int activate(); 							// exports GPIO
    int deactivate(); 						// unexport GPIO
    int setdir(int dir); 						// Set GPIO Direction
    int setval(int val); 						// Set GPIO Value (putput pins)
    int getval(); 								// Get GPIO Value (input/ output pins)
    int get_GPIONum(); 			 	// Return the GPIO number associated with the instance of an object
};

#endif // FSGPIO_PIN_H
