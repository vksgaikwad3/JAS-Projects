#include "fsgpio_pin.h"

using namespace std;

FSGPIO_Pin::FSGPIO_Pin()		//constructor of FSGPIO_Pin
{
	m_GPIONum = -1;
	m_sGPIONum = "";
	m_active = 0;
}

FSGPIO_Pin::FSGPIO_Pin(int num)		//constructor of FSGPIO_Pin with input argument
{
	m_GPIONum = -1;
	m_sGPIONum = "";
	connectGPIO(num);
	m_active = 0;
}

int FSGPIO_Pin::import_pin(int num)		//created new instance to import GPIO pin
{
	m_GPIONum = -1;
	m_sGPIONum = "";
	connectGPIO(num);
	m_active = 0;
}

int FSGPIO_Pin::connectGPIO(int num)
{
	// If this pin was previously exported then unexport it.
	if (m_GPIONum > 0 and m_active)
		deactivate();

	//Configure for GPIO pin number (num)
	if (num < 0 or num > MAX_GPIO)
	{
			m_sGPIONum = "";
			m_GPIONum = -1;
			return -1;
	}

	// Create the integer and string repesentations of the GPIO number
	m_GPIONum = num;
	ostringstream convert;
	convert << m_GPIONum;
	m_sGPIONum = convert.str();

	return 0;
}

int FSGPIO_Pin::activate()
{
	string export_str = STR_EXPORT_FN;
	string dirfile_str = STR_GPIO_PRE + m_sGPIONum + STR_DIR_POST;
	string valfile_str = STR_GPIO_PRE + m_sGPIONum + STR_VALUE_POST;

	// Open "export" file. Convert C++ string to C string. Required for all Linux path names
	ofstream exportgpio(export_str.c_str());
	if (!exportgpio)
		return FSGPIO_FILEERR;

	exportgpio << m_sGPIONum ; 					// write GPIO number to export
	exportgpio.close(); 										// close export file

	m_GPIODirOutFile.open(dirfile_str.c_str());	// Open the GPIO direction control files
	if (!m_GPIODirOutFile)
		return FSGPIO_FILEERR;

	m_GPIODirInFile.open(dirfile_str.c_str());
	if (!m_GPIODirInFile)
		return FSGPIO_FILEERR;

	m_GPIOValOutFile.open(valfile_str.c_str());	// Open the GPIO value files
	if (!m_GPIOValOutFile)
		return FSGPIO_FILEERR;

	m_GPIOValInFile.open(valfile_str.c_str());
	if (!m_GPIOValInFile)
		return FSGPIO_FILEERR;

	m_active = 1;
	return 0;
}

int FSGPIO_Pin::deactivate()
{
	string unexport_str = STR_UNEXPORT_FN;

	// If the pin is not setup then abort with error
	if (m_active < 1)
		return -1;

	// Open unexport file
	ofstream unexportgpio(unexport_str.c_str());
	if (unexportgpio < 0)
		return FSGPIO_FILEERR;

	unexportgpio << m_sGPIONum ; 		// write GPIO number to unexport
	unexportgpio.close(); 							// close unexport file

	if (m_GPIODirOutFile.is_open())			// Close the open dir files
		m_GPIODirOutFile.close();

	if (m_GPIODirInFile.is_open())
		m_GPIODirInFile.close();

	if (m_GPIOValOutFile.is_open())			// Close the open value files
		m_GPIOValOutFile.close();

	if (m_GPIOValInFile.is_open())
		m_GPIOValInFile.close();

	m_active = 0;
	return 0;
}

int FSGPIO_Pin::setdir(int dir)
{
	string	s_dir;

	// If the pin is not setup then abort with error
	if (m_active < 1)
		return -1;

        if (!m_GPIODirOutFile)
			return FSGPIO_FILEERR;

		if (dir != 0)
			s_dir = STR_OUT;
		else
			s_dir = STR_IN;

        m_GPIODirOutFile << s_dir; 					// Write direction to direction file
        m_GPIODirOutFile.clear();						// Reset to beginning of the file
        m_GPIODirOutFile.seekp(0, ios::beg);

        return 0;
}

int FSGPIO_Pin::setval(int val)
{
	string	s_val;

	// If the pin is not setup then abort with error
	if (m_active < 1)
		return FSGPIO_RDYERR;

	if (!m_GPIOValOutFile)
		return FSGPIO_FILEERR;

	if (val != 0)
		s_val = STR_HIGH;
	else
		s_val = STR_LOW;

	m_GPIOValOutFile << s_val ;				// Write to value file
	m_GPIOValOutFile.clear();					// Reset to the beginning of the file
	m_GPIOValOutFile.seekp(0, ios::beg);
	return 0;
}

int FSGPIO_Pin::getval()
{
	int		val = -1;
	string		s_val;

	// If the pin is not setup then abort with error
	if (m_active < 1)
		return -1;

    if (!m_GPIOValInFile)
		return FSGPIO_FILEERR;

    m_GPIOValInFile >> s_val ;  	//read gpio value

    if(s_val != "0")
        val = HIGH;
    else
        val = LOW;

    m_GPIOValInFile.clear(); 						// Reset to the beginning of the file
    m_GPIOValInFile.seekg(0, ios::beg);
    return val;
}

int FSGPIO_Pin::get_GPIONum()
{ return m_GPIONum; }
