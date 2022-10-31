#include<LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,5,6,7);   //rs,e,d4,d5,d6,d7

int Vin=5;        //voltage at 5V pin of arduino
float Vout=0;     //voltage at A0 pin of arduino
float R1=5000;    //value of known resistance
float R2=0;       //value of unknown resistance
int a2d_data=0;
char input;    
float buffer=0;   

int analogInputv = 3;
float Voutv = 0.00;
float Vinv = 0.00;
float R1v = 1000000.00; // resistance of R1 (1000K) 
float R2v= 100000.00; // resistance of R2 (100K) 
int valv= 0;

void setup() 
{
  Serial.begin(9600);
pinMode(analogInputv, INPUT);
 lcd.begin(16,2);
}

void loop()
{
  while(Serial.available()>0){
  input= Serial.read();

  if (input=='O'){
     lcd.clear();
    a2d_data=analogRead(A0);
    if(a2d_data)
     {
    buffer=a2d_data*Vin;
    Vout=(buffer)/1024.0;
    buffer=Vout/(Vin-Vout); 
    R2=R1*buffer;

    lcd.setCursor(4,0);
    lcd.print("Ohm meter");

    lcd.setCursor(0,1);
    lcd.print("R(ohm)= ");
    lcd.print(R2);
    
    
  }}
  else if (input=='A'){
 lcd.clear();
 int voltage_value0 = analogRead(A1);
int voltage_value1 = analogRead(A2);
 
 int subraction_value =(voltage_value0 - voltage_value1) ;
 float temp_val = (subraction_value*0.00488);
 
 float current_value = (temp_val/100);
    lcd.setCursor(4,0);
    lcd.print("Ammeter");

    lcd.setCursor(0,1);
    lcd.print("A(Amps) = ");
      lcd.print(current_value);
   
  }
  else if (input=='E'){
     lcd.clear();
     lcd.setCursor(1,0);
    lcd.print("Welcome!");
    lcd.setCursor(1,1);
    lcd.print("Plz Choose Mode");
  }
  else if (input=='V'){
 valv = analogRead(analogInputv);
 Voutv = (valv * 5.00) / 1024.00;
 Vinv = Voutv / (R2v/(R1v+R2v));
 
lcd.begin(16, 2);
 lcd.setCursor(1,0);
    lcd.print("voltmeter");

    lcd.setCursor(0,1);
    lcd.print("v(volt) = ");
      lcd.print( Vinv);
      Serial.print( Vinv );
      Serial.print("\n");
  delay (1000);
} }
  
}
