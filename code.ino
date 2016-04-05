#include <Servo.h> // include Servo library 
#include <math.h>  // include math library

Servo horizontal; // horizontal servo
int servoh = 90; // stand horizontal servo

Servo vertical; // vertical servo 
int servov = 90; // stand vertical servo

// LDR pin connections
// name = analogpin;
int ldrlt = 0; //LDR top left
int ldrrt = 1; //LDR top rigt
int ldrld = 2; //LDR down left
int ldrrd = 3; //ldr down rigt

//////////////////////////////////////////////////  
//PUT YOUR LATITUDE, LONGITUDE, AND TIME ZONE HERE
  float latitude = 26.3338;
  float longitude = 91.2667;
  float timezone = 5.5;
//////////////////////////////////////////////////  
  
//If you live in the southern hemisphere, it would probably be easier
//for you if you make north as the direction where the azimuth equals
//0 degrees. To do so, switch the 0 below with 180.  
  float northOrSouth = 180;



  //SET TIME AND DATE HERE//////////////
  float year = 2015;
  float month2 = 11;
  float day = 11;
  float hour2 = 5 ;
  float minute2 = 0 ;
  int second = 0;
  //hour2 = 12;//Use 24hr clock (ex: 1:00pm = 13:00) and don't use daylight saving time.
  //minute2 = 0;
  //END SET TIME AND DATE /////////////

/////////////////////////////////////////////////////////// 
//MISC. VARIABLES
///////////////////////////////////////////////////////////  
  float pi = 3.14159265;
  float altitude;
  float azimuth;
  float delta;
  float h;
  unsigned long delaytime = 1000;
  int readtime = 1;
/////////////////////////////////////////////////////////// 
//END MISC. VARIABLES
///////////////////////////////////////////////////////////
  
void setup(){
  Serial.begin(9600);
  
  // servo connections
  // name.attach(pin);
  horizontal.attach(9); 
  vertical.attach(10);
}

void loop(){
  
  int temp;
  
  // Take input if readtime = 1
  while(readtime == 1){
    
  Serial.println("Enter 1 to take inputs else 2 to use default inputs : "); //Prompt User for input
  while (Serial.available()==0) {          //Wait for user input  
  }
  temp=Serial.parseInt();
  if(temp!=1)
  { goto Label10;}
  
  Label1: Serial.println("year: "); //Prompt User for input
  while (Serial.available()==0) {          //Wait for user input  
  }
  year=Serial.parseFloat();                 //Read user input into myName
  if(year>=1900 && year<=2100)
  {Serial.print("year: "); Serial.println(year);}
  else{ Serial.print("wrong input enter again ..."); goto Label1;}
  
  Label2: Serial.println("month: ");        //Prompt User for input
  while (Serial.available()==0)  {  
  }
  month2=Serial.parseFloat();                      //Read user input into age
  if(month2>=1 && month2<=12)
  {Serial.print("month: "); Serial.println(month2);}
  else{ Serial.print("wrong input enter again ..."); goto Label2;}
  
  Label3: Serial.println("day: ");      //Prompt User for input
  while (Serial.available()==0)  {  
  }
  day=Serial.parseFloat();                //Read user input into height
 if(day>=1 && day<=31)
  {Serial.print("day: "); Serial.println(day);}
  else{ Serial.print("wrong input enter again ..."); goto Label3;}
  
  Label4: Serial.println("hour: ");      //Prompt User for input
  while (Serial.available()==0)  { 
  }
  hour2=Serial.parseFloat();
  if(hour2>=1 && hour2<=24)
  {Serial.print("hour: "); Serial.println(hour2);}
  else{ Serial.print("wrong input enter again ..."); goto Label4;}

  Label5: Serial.println("minute: ");      //Prompt User for input
  while (Serial.available()==0)  {  
  }
  minute2=Serial.parseFloat();
  if(minute2>=0 && minute2<=60)
  {Serial.print("minute: "); Serial.println(minute2);}
  else{ Serial.print("wrong input enter again ..."); goto Label5;}

  Label6: Serial.println("latitude: ");      //Prompt User for input
  while (Serial.available()==0)  {  
  }
  latitude=Serial.parseFloat();
  if(latitude>=-90 && latitude<=90)
  {Serial.print("latitude: "); Serial.println(latitude);}
  else{ Serial.print("wrong input enter again ..."); goto Label6;}

  Label7: Serial.println("longitude: ");      //Prompt User for input
  while (Serial.available()==0)  {  
  }
  longitude=Serial.parseFloat();
  if(longitude>=-180 && longitude<=180)
  {Serial.print("longitude: "); Serial.println(longitude);}
  else{ Serial.print("wrong input enter again ..."); goto Label7;}

  Label8: Serial.println("timezone: ");      //Prompt User for input
  while (Serial.available()==0)  {  
  }
  timezone=Serial.parseFloat();
  if(timezone>=-24 && timezone<=24)
  {Serial.print("timezone: "); Serial.println(timezone);}
  else{ Serial.print("wrong input enter again ..."); goto Label8;}

  Label9: Serial.println("If you live in the southern hemisphere, enter 180 else 0: ");      //Prompt User for input
  while (Serial.available()==0)  {  
  }
  northOrSouth=Serial.parseFloat();
  if(northOrSouth==0 || northOrSouth==180)
  {Serial.print("0 or 180: "); Serial.println(northOrSouth);}
  else{ Serial.print("wrong input enter again ..."); goto Label9;}
    
  
 Label10: readtime = 0;
 latitude = latitude * pi/180;
}


  // Measure time start in micro sec
  unsigned long start = micros();
  
  int lt = analogRead(ldrlt); // top left
  int rt = analogRead(ldrrt); // top right
  int ld = analogRead(ldrld); // down left
  int rd = analogRead(ldrrd); // down rigt

  int dtime = analogRead(4)/20; // read potentiometers // used to adjust weightage of LDR Mechanism over Tracking algorithm
  int tol = analogRead(5)/4; //difference tolerance between ldr readings i.e sensitivity of the ldr configuration
  
  int avt = (lt + rt) / 2; // average value top
  int avd = (ld + rd) / 2; // average value down
  int avl = (lt + ld) / 2; // average value left
  int avr = (rt + rd) / 2; // average value right

  int dvert = avt - avd; // check the diffirence of up and down
  int dhoriz = avl - avr;// check the diffirence og left and right


// Start of Code to measure light intensity
if (-1*tol > dvert || dvert > tol) // check if the difference is in the tolerance else change vertical angle
{
if (avt > avd)
{
servov = ++servov;
if (servov > 180)
{
servov = 180;
}
}
else if (avt < avd)
{
servov= --servov;
if (servov < 0)
{
servov = 0;
}
}
//vertical.write(servov);
}

if (-1*tol > dhoriz || dhoriz > tol) // check if the difference is in the tolerance else change horizontal angle
{
if (avl > avr)
{
servoh = --servoh;
if (servoh < 0)
{
servoh = 0;
}
}
else if (avl < avr)
{
servoh = ++servoh;
if (servoh > 180)
{
servoh = 180;
}
}
else if (avl == avr)
{
// nothing
}
//horizontal.write(servoh);
}

// End of Code to measure light intensity


  //START OF THE CODE THAT CALCULATES THE POSITION OF THE SUN
  float n = daynum(month2) + day;//NUMBER OF DAYS SINCE THE START OF THE YEAR. 
  
  delta = .409279 * sin(2 * pi * ((284 + n)/365.25));//SUN'S DECLINATION.
  
  day = dayToArrayNum(day);//TAKES THE CURRENT DAY OF THE MONTH AND CHANGES IT TO A LOOK UP VALUE ON THE HOUR ANGLE TABLE.
  
  h = (FindH(day,month2)) + longitude + (timezone * -1 * 15);//FINDS THE NOON HOUR ANGLE ON THE TABLE AND MODIFIES IT FOR THE USER'S OWN LOCATION AND TIME ZONE.
  h = ((((hour2 + minute2/60) - 12) * 15) + h)*pi/180;//FURTHER MODIFIES THE NOON HOUR ANGLE OF THE CURRENT DAY AND TURNS IT INTO THE HOUR ANGLE FOR THE CURRENT HOUR AND MINUTE.
  
  altitude = (asin(sin(latitude) * sin(delta) + cos(latitude) * cos(delta) * cos(h)))*180/pi;//FINDS THE SUN'S ALTITUDE.
    
  azimuth = ((atan2((sin(h)),((cos(h) * sin(latitude)) - tan(delta) * cos(latitude)))) + (northOrSouth*pi/180)) *180/pi;//FINDS THE SUN'S AZIMUTH.

 
  //END OF THE CODE THAT CALCULATES THE POSITION OF THE SUN
  int modified_azimuth, modified_altitude;
  if(azimuth<90){
    modified_azimuth = 90 + azimuth;
  } else if (azimuth<180) {
    modified_azimuth = azimuth - 90;
  } else if (azimuth<270) {
    modified_azimuth = azimuth - 90;
  } else if (azimuth<360) {
    modified_azimuth = azimuth - 270;
  } else {
    modified_azimuth = 180;
  }
  
  if(altitude<0){
    modified_azimuth = 180;
  }

  //LDR + Tracker combiner code
  int modified2_azimuth = (dtime*servoh + (50-dtime)*modified_azimuth)/50;
  
  horizontal.write(modified2_azimuth);

  modified_altitude = altitude;
  if ( azimuth>90 && azimuth<270){
    modified_altitude = 180 - altitude;
  }
  if (modified_altitude > 180 || modified_altitude < 0){
    modified_altitude = 0;
  }

  //LDR + Tracker combiner code
  int modified2_altitude = (dtime*servov + (50-dtime)*modified_altitude)/50;
  vertical.write(modified2_altitude);

  Serial.print(" WeightOfLDR = ");
  Serial.print(dtime);
  Serial.print(" Hour = ");
  Serial.print(hour2); 
  Serial.print(" Min = ");
  Serial.print(minute2);
  Serial.print(" Altitude = ");
  Serial.print(altitude);  
  Serial.print("  Azimuth = ");
  Serial.print(azimuth);
  Serial.print("  Vert = ");
  Serial.print(modified_altitude);  
  Serial.print("  Horiz = ");
  Serial.println(modified_azimuth);

  // Clock ticker. Modify to change to real time clock.
  /*second++;
  if(second == 60){
    second = 0;
    minute2++;
  }*/
  minute2 += 5;
  if(minute2 >= 60) {
    minute2 -= 60;
    hour2++;
  }
  if(hour2==24){
    hour2 = 0;
  }


  // Measure time end in micro sec
  unsigned long endtime = micros();
  unsigned long delta = endtime - start;
  //Serial.println(delta);
  //Serial.println(1000 - delta/1000);
  delay(delaytime - delta/1000);
  //delay(1000);


}//End Void Loop






//THIS CODE TURNS THE MONTH INTO THE NUMBER OF DAYS SINCE JANUARY 1ST.
//ITS ONLY PURPOSE IS FOR CALCULATING DELTA (DECLINATION), AND IS NOT USED IN THE HOUR ANGLE TABLE OR ANYWHERE ELSE.
      float daynum(float month){
       float day;
       if (month == 1){day=0;}
       if (month == 2){day=31;}       
       if (month == 3){day=59;}       
       if (month == 4){day=90;}
       if (month == 5){day=120;}
       if (month == 6){day=151;}
       if (month == 7){day=181;}
       if (month == 8){day=212;}
       if (month == 9){day=243;}
       if (month == 10){day=273;}
       if (month == 11){day=304;}
       if (month == 12){day=334;} 
       return day; 
      }

//THIS CODE TAKES THE DAY OF THE MONTH AND DOES ONE OF THREE THINGS: ADDS A DAY, SUBTRACTS A DAY, OR
//DOES NOTHING. THIS IS DONE SO THAT LESS VALUES ARE REQUIRED FOR THE NOON HOUR ANGLE TABLE BELOW.
       int dayToArrayNum(int day){
            if ((day == 1) || (day == 2) || (day == 3)){day = 0;}
            if ((day == 4) || (day == 5) || (day == 6)){day = 1;}  
            if ((day == 7) || (day == 8) || (day == 9)){day = 2;}
            if ((day == 10) || (day == 11) || (day == 12)){day = 3;}
            if ((day == 13) || (day == 14) || (day == 15)){day = 4;}
            if ((day == 16) || (day == 17) || (day == 18)){day = 5;}
            if ((day == 19) || (day == 20) || (day == 21)){day = 6;}
            if ((day == 22) || (day == 23) || (day == 24)){day = 7;}
            if ((day == 25) || (day == 26) || (day == 27)){day = 8;}
            if ((day == 28) || (day == 29) || (day == 30) || (day == 31)){day = 9;}
          return day;
       }

//////////////////////////////////////////////////////////////
//HERE IS THE TABLE OF NOON HOUR ANGLE VALUES. THESE VALUES GIVE THE HOUR ANGLE, IN DEGREES, OF THE SUN AT NOON (NOT SOLAR NOON)
//WHERE LONGITUDE = 0. DAYS ARE SKIPPED TO SAVE SPACE, WHICH IS WHY THERE ARE NOT 365 NUMBERS IN THIS TABLE.
      float FindH(int day, int month){
      float h;
      
      if (month == 1){
            float h_Array[10]={
            -1.038,-1.379,-1.703,-2.007,-2.289,-2.546,-2.776,-2.978,-3.151,-3.294,};
            h = h_Array[day];}

      if (month == 2){
            float h_Array[10]={
            -3.437,-3.508,-3.55,-3.561,-3.545,-3.501,-3.43,-3.336,-3.219,-3.081,};
            h = h_Array[day];}

      if (month == 3){
            float h_Array[10]={
            -2.924,-2.751,-2.563,-2.363,-2.153,-1.936,-1.713,-1.487,-1.26,-1.035,};
            h = h_Array[day];}

      if (month == 4){
            float h_Array[10]={
            -0.74,-0.527,-0.322,-0.127,0.055,0.224,0.376,0.512,0.63,0.728,};
            h = h_Array[day];}

      if (month == 5){
            float h_Array[10]={
            0.806,0.863,0.898,0.913,0.906,0.878,0.829,0.761,0.675,0.571,};
            h = h_Array[day];}

      if (month == 6){
            float h_Array[10]={
            0.41,0.275,0.128,-0.026,-0.186,-0.349,-0.512,-0.673,-0.829,-0.977,};
            h = h_Array[day];}
            
      if (month == 7){
            float h_Array[10]={
            -1.159,-1.281,-1.387,-1.477,-1.547,-1.598,-1.628,-1.636,-1.622,-1.585,};
            h = h_Array[day];}

      if (month == 8){
            float h_Array[10]={
            -1.525,-1.442,-1.338,-1.212,-1.065,-0.9,-0.716,-0.515,-0.299,-0.07,};
            h = h_Array[day];}

      if (month == 9){
            float h_Array[10]={
            0.253,0.506,0.766,1.03,1.298,1.565,1.831,2.092,2.347,2.593,};
            h = h_Array[day];}

      if (month == 10){
            float h_Array[10]={
            2.828,3.05,3.256,3.444,3.613,3.759,3.882,3.979,4.049,4.091,};
            h = h_Array[day];}

      if (month == 11){
            float h_Array[10]={
            4.1,4.071,4.01,3.918,3.794,3.638,3.452,3.236,2.992,2.722,};
            h = h_Array[day];}

      if (month == 12){
            float h_Array[10]={
            2.325,2.004,1.665,1.312,0.948,0.578,0.205,-0.167,-0.534,-0.893,};
            h = h_Array[day];}

return h;
      }
//////////////////////////////////////////////////////////////

