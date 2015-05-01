#include <iostream>
#include <stdio.h>
#include <inttypes.h>
using namespace std;

int main()
{

	uint8_t no[8] = {1,1,1,1,1,1,1,1};
	uint8_t  num=0;
	
	for(int i=0 ;i<= 8;i++)
	{
		num |= (no[i] << i);
	}
	printf("%d\n",num);
	
		
	switch(num)
	{
		case 255 : cout <<"I am in case 255"<<endl;
					break;
	}
	//else  
	//int num =0x00; cout<< num<< endl;

return 0;
}
