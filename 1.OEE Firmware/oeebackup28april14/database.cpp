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
//#include "/usr/include/c++/bits/basic_string.h"
#include <string.h>
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
  int y=  mysql_query (connect,"show tables");                              
    cout << "Y:"<< y<<'\n';                                                                      
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
void dB :: logToCycle(string customerID,string machineID,string modelName,string startTime,string endTime,string result)
{	
	 string queryText;
	
	/** Add MySQL Query */
 
	queryText= "INSERT INTO oee.cycles (customerID,machineID,modelName,startTime,endTime,result) VALUES ('"+ customerID +"','"+ machineID +"','"+modelName +"','"+ startTime +"','"+ endTime +"','"+ result+"')";
	//cout<<queryText<<'\n';
	int cQuery=mysql_query (connect,queryText.c_str());
	cout << "To Cycle :"<< cQuery<<'\n';
	fprintf(stderr,"%s\n", mysql_error(connect));
	
}

/**
 *--------------------------------------------------------------------
 *       Class:  dB
 *      Method:  dB :: logToDownTime()
 * Description:  send mysql query to database
 *--------------------------------------------------------------------
 */
void dB ::logToDownTime(string customerID,string machineID,string modelName,string startTime,string endTime,string errorNum)
{	
	string queryText;
	
	/** Add MySQL Query */
 
	queryText= "INSERT INTO oee.downtime (customerID,machineID,modelName,startTime,endTime,reasonCode) VALUES('"+ customerID +"','"+ machineID +"','"+ modelName +"','"+ startTime +"','"+ endTime +"','"+ errorNum +"')"; 
	
	//cout<<queryText;
	
	int dQuery = mysql_query (connect,queryText.c_str());
	cout << "To Downtime :"<< dQuery<<'\n';
	fprintf(stderr,"%s\n", mysql_error(connect));
}

/**
 *--------------------------------------------------------------------
 *       Class:  dB
 *      Method:  dB :: getModelName()
 * Description:  send mysql query to get MOdelName from modelinfo table *--------------------------------------------------------------------
 */
string dB ::getModelName(string modelID)
{	
	string queryText,modelName;
	
	/** Add MySQL Query */
 
	queryText= "SELECT modelName FROM oee.modelinfo  WHERE modelID="+ modelID +";"; 
	
	//cout<<queryText;
	int mQuery = mysql_query (connect,queryText.c_str());
	cout << '\n'<<"From modelinfo:"<< mQuery<<'\n';
	//fprintf(stderr,"%d\n", mysql_error(connect));
	
	res_set = mysql_store_result(connect);			//store the result
	row= mysql_fetch_row(res_set);
	modelName = row[0];
	//printf("Data: %s",row[0]);
	//cout <<"ModelName:"<<modelName<<'\n';
	mysql_free_result(res_set);						//free Data
	
	return(modelName);
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
