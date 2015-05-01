/*
 * ===================================================================
 *
 *       Filename:  database.h
 *
 *    Description:  Definition of dB Class for accessing database
 *
 *        Created:  Wendesday 9 April 2014
 *       Compiler:  gcc
 *
 *         Author:  Vikas Gaikwad, vikas@jambhekar.com
 *        License:  GNU General Public License
 *      Copyright:  Copyright (c) 2014, Great Developers
 *
 * ===================================================================
 */


/**-------------------------------------------------------------------
 *  Header file
 *------------------------------------------------------------------*/

#include <iostream>
#include <mysql.h>
//#include "my_global.h"
	
/**-------------------------------------------------------------------
 *  using namespace std
 *------------------------------------------------------------------*/

using namespace std;



/**-------------------------------------------------------------------
 *  define variables for DB Details
 *------------------------------------------------------------------*/

#define SERVER 	 "192.168.1.5"
#define USER	 "root"
#define PASSWORD "root"
#define DATABASE "oee"

/**
 * ===================================================================
 *        Class:  dB
 *  Description:  MySQL class for database accessability
 * ===================================================================
 */

class dB {
    protected:
        /** dB connectivity Variables */
        MYSQL *connect;
        MYSQL_RES *res_set;
        MYSQL_ROW row;

        unsigned int i;

    public:
        /** dB Constructor */
        dB();

		/** Function to show tables in database */
		void ShowTables();
		void logToCycle(string ,string ,string );
		void logToDownTime(string ,string ,char);
        /** dB Destructor */
        ~dB();
};


