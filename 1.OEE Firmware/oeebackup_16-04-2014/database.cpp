/*
 * ===================================================================
 *
 *       Filename:  database.cpp
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
 *  Include mysql.h file local header file(declaration of class)
 *------------------------------------------------------------------*/

#include "database.h"
#include "oee.h"
#include <string>
/**
 *--------------------------------------------------------------------
 *       Class:  dB
 *      Method:  dB :: dB()
 * Description:  Constructor to initialize database conectivity
 *--------------------------------------------------------------------
 */

dB :: dB()
{
    connect = mysql_init(NULL);
    if ( !connect )
    {
        cout << "MySQL Initialization Failed";
    }   

    connect = mysql_real_connect(connect, SERVER, USER, PASSWORD, DATABASE, 3306,NULL,0);
    
    if ( connect )
    {
        cout << "Connection Succeeded\n";
    }
    
    else
    {
        cout << "Connection Failed\n";
    }
}

/**
 *--------------------------------------------------------------------
 *       Class:  dB
 *      Method:  dB :: ShowTables()
 * Description:  Show tables in database
 *--------------------------------------------------------------------
 */

void dB :: ShowTables()
{
    /** Add MySQL Query */
    mysql_query (connect,"show tables");                              
                                                                          
    i = 0;
                                                                         
    res_set = mysql_store_result(connect);                              
                                                                          
    unsigned int numrows = mysql_num_rows(res_set);                   
                                                                          
    cout << " Tables in " << DATABASE << " database " << endl;        
                                                                         
    while (((row=mysql_fetch_row(res_set)) != NULL))
    {                                                                 
        cout << row[i] << endl;                                       
    }
}

/**
 *--------------------------------------------------------------------
 *       Class:  dB
 *      Method:  dB :: logToCycle()
 * Description:  send mysql query to database
 *--------------------------------------------------------------------
 */
char* dB :: logToCycle(char* startTime,char* endTime,std::string result)
{	
	std::string queryText;
	
	/** Add MySQL Query */
 
	queryText= std::string("INSERT INTO oee.cycles(startTime,endTime,result) VALUES('") +startTime +"','"+ endTime +"','"+ result +"')"; 

	mysql_query (connect,"queryText");

}

/**
 *--------------------------------------------------------------------
 *       Class:  dB
 *      Method:  dB :: logToDownTime()
 * Description:  send mysql query to database
 *--------------------------------------------------------------------
 */
char* dB :: logToDownTime(char* startTime,char* endTime,char errorNum)
{	
	std::string queryText;
	
	/** Add MySQL Query */
 
	queryText= std::string("INSERT INTO oee.cycles(startTime,endTime,reasonCode) VALUES ('") + startTime +"',' ";
	queryText = queryText + endTime +"')";
	//queryText +=errorNum +"')"; 
	
	cout<<queryText;
	//mysql_query (connect,"INSERT INTO oee.cycles(startTime,endTime,reasonCode) VALUES ('"+ startTime +"','"+ 
//endTime +"','"+ errorNum +')");
	//mysql_query (connect,"queryText");
}

/**
 *--------------------------------------------------------------------
 *       Class:  dB
 *      Method:  dB :: ~MySQL()
 * Description:  Destructor of dB class for closing mysql
 *               connection
 *--------------------------------------------------------------------
 */

dB :: ~dB()
{
    mysql_close (connect);
}
