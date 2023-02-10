
int IR = 12;
int LDR = A3;

int blue_light_pin = 9;
int green_light_pin = 10;
int red_light_pin = 11;


int High = 255;
int Low = 0;
void setup()

{

pinMode(blue_light_pin, OUTPUT);
pinMode(green_light_pin, OUTPUT);
pinMode(red_light_pin, OUTPUT);

pinMode(IR, INPUT);

pinMode(LDR, INPUT);

}

void loop() {

int LDRValue = analogRead(LDR);

Serial.print("sensor = ");

Serial.print(LDRValue);

delay (500);





if (digitalRead(IR) == LOW)
  
    {
if (LDRValue> 75)
    {
RGB_color(0, 0, 0); // Black
Serial.println("It's Bright Outside; Lights status: OFF");
    }
else if (LDRValue < 75){

RGB_color(0, 255, 0); // Green
delay (5000);
Serial.println("It's Dark Outside but No motion ; LED Lights status: ON");

    }
 }
else if (digitalRead(IR) == HIGH)
      {
  if (LDRValue> 75)
    {
RGB_color(0, 0, 0); // Black
Serial.println("It's Bright Outside; Lights status: OFF");
    }
  else if  (50< LDRValue< 75 )
      {



RGB_color(0, 0, 255); // Blue
Serial.println("It's Dark Outside; LED Lights status: ON");

    }
 else
      {

RGB_color(255, 0, 0); //Red

Serial.println("It's very Dark Outside; LED Lights status: ON");

    }
  
  }
}
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
