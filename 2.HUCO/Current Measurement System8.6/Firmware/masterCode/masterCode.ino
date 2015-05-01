void Process_data();
void serialRead();
int serialBuffIndex = 0;
byte serialBuffer[2];
boolean isWaiting = false;
int Relays[8] ={2,3,4,5,6,7,8,9};
int Loads[8] ={11,12,13,14,15,16,17,18};

void setup() {
  

// put your setup code here, to run once:
Serial.begin(9600);
for(int i=0;i<8;i++)
  {
    pinMode(Relays[i],OUTPUT);
    pinMode(Loads[i],OUTPUT);
  }

}

void loop() {
  serialRead();
  delay(100); 
} 


void serialRead()
{ 
 
  if(Serial.available() > 0)                         
  {                          
    byte lastChar = byte(Serial.read());
    Serial.write(lastChar);
    if(isWaiting)
    {    
      //Serial.println("isWaiting case");    
        if(lastChar!='\n')
        {
           serialBuffer[serialBuffIndex] = lastChar;
           serialBuffIndex++ ;
           //Serial.println("t char not detected");
        }
        else
        {
            //Serial.println("T char detected");
          serialBuffIndex = 0;
          isWaiting = false ; 
          Process_data();      
        }
    }
    else
    {
      if(lastChar == '$')                       
       { //Serial.println("$ detected");
          isWaiting = true;
       }
    }
  }
}  
 void Process_data()
{ //Serial.println("in process function");
        if(serialBuffer[0]==2)   //set realays
        {//Serial.println("Set relays state");
          byte temp = serialBuffer[1];
          Serial.println(temp);
          for(int i = 0 ; i<8 ; i++)
          {
             byte val = temp & 0x01;
             Serial.println(val);
             digitalWrite(Relays[i],val);
             temp = temp >> 1;
          }
        }
        if(serialBuffer[0]==3)   //setload
        {//Serial.println("Set load state");
            byte temp = serialBuffer[1];
            for(int i = 0 ; i<8 ; i++)
            {
              byte val = temp & 0x01;
              digitalWrite(Loads[i],val);
              temp = temp >> 1;
           }        
       }
}
 
 
  // put your main code here, to run repeatedly:   

