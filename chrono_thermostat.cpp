/*	Thermostat R 0.1 16.11.2013
 *	Project by: Giorgio Manenti
 * 	Connection spec:
 *
 * 	LCD lcd(12, 11, 10, 7, 8, 9, 6);
 * 	RELAY (D4)
 * 	RTC i2C (A4,A5)
 * 	DHT11 temp, hum (D2)
 * 	10K pot (A2)
 * 	RGB LED (D3 green, D5 red)
 * 	LCD backlight (D13)
 *
 */

// Do not remove the include below
#include "chrono_thermostat.h"



//Define for Graphic LCD128x64 controller ST7920 SPI
#define LCD_RS  8  // Arduino-Pin an Display RS
#define LCD_RW  9  // Arduino-Pin RW LCD
#define LCD_EN	6  // Arduino-Enable LCD

//components to Arduino Pins
int relay 		= 12;
int pot_pin 	= 0;
int red_led 	= 11;
int green_led 	= 10;
int lcd_bkl		= 3;

//variables declaration
float act_temp 	= 0.0;
float set_temp 	= 15.0;
int hum 		= 0;
int last_time 	= 0;
int hys 		= 1;
int night_temp 	= 17;
int prev_temp 	= 0;
int prev_time 	= 0;
int delay_set 	= 10;

//Initialize components

//***********************DHT11 sensor********************
int idDHT11pin = 2; 									//Digital pin for comunications DHT11
int idDHT11intNumber = 0;								//interrupt number (must be the one that use the previus defined pin (see table above) DHT11
void dht11_wrapper(); 									// must be declared before the lib initialization
idDHT11 DHT11(idDHT11pin,idDHT11intNumber,dht11_wrapper);

//***********************LCD library*********************
U8GLIB_ST7920_128X64_1X u8g(6, 9, 8);					// SPI Com: SCK = en = 18, MOSI = rw = 16, CS = di = 17


void setup()
{
	Serial.begin(9600);
	pinMode(relay, OUTPUT);
	pinMode(green_led, OUTPUT);
	pinMode(red_led, OUTPUT);
	pinMode(lcd_bkl, OUTPUT);

	analogWrite(lcd_bkl, 255);

	//check the RTC status
	setSyncProvider(RTC.get);
	if(timeStatus()!= timeSet)
	{
		u8g.setFont(u8g_font_unifont);//u8g.setFont(u8g_font_osb21);
		u8g.drawStr( 0, 22, ">> RTC FAIL");
	}

	else
	{
		u8g.setFont(u8g_font_unifont);//u8g.setFont(u8g_font_osb21);
		u8g.drawStr( 0, 22, ">> RTC OK");
	}


	delay(3000);

	//Clear the screen


}


void printDigits(int digits)  //function print 0 before numbers < 10
{
	//if(digits < 10) tft.print('0');
	//tft.print(digits);
}


/*-------------------------Analog sensor reading------------------

float analog_temp(int pinread)
{
	int a = 0;
	int voltage = 0;
	for(int x = 0; x<=19;x++)
	{
		a += analogRead(pinread);
		delay(10);
	}

	voltage = a / 20;

	Serial.println(voltage);

	float tempC =((voltage * 0.00488)-0.5) / 0.01;
	Serial.println(tempC);
	return tempC;

}

-------------------------------------------------------------------*/


void dht11_wrapper() //necessary to initialize the idDHT11 library
{
	DHT11.isrCallback();
}

void stop_pump() //turn off the relay and set the LED to RED
{
	digitalWrite(relay, 0);
	analogWrite(red_led, 255);
	analogWrite(green_led, 0);
}

void start_pump() //turn on the relay and set the LED to GREEN
{
	digitalWrite(relay, 1);
	analogWrite(red_led, 0);
	analogWrite(green_led, 255);
}

/*void print_tft()
{


	//clock, date and time

	tft.setTextSize(1);
//date
	tft.setTextColor(ST7735_BLACK, ST7735_WHITE);
	tft.setCursor(12,4);
	printDigits(day());
	tft.setCursor(24,4);
	tft.print('-');
	tft.setCursor(30,4);
	printDigits(month());
	tft.setCursor(42,4);
	tft.print('-');
	tft.setCursor(49,4);
	tft.print(year());
//time
	tft.setCursor(86,4);
	printDigits(hour());
	tft.setCursor(98,4);
	tft.print(':');
	tft.setCursor(104,4);
	printDigits(minute());

	tft.drawLine(1,16,126,16,ST7735_BLACK);
	tft.drawLine(1,65,126,65,ST7735_BLACK);
	tft.drawLine(63,16,63,65,ST7735_BLACK);

	tft.setTextSize(1);
	tft.setCursor(5,25);
	tft.print("Room temp");
	tft.setCursor(70,25);
	tft.print("Room hum");

	tft.setTextSize(2);
	tft.setCursor(18,40);
	tft.print(act_temp,0);
	//Serial.println(now_temp);
	tft.setCursor(84,40);
	tft.print(DHT11.getHumidity(),0);
	tft.setCursor(5,80);
	tft.setTextSize(3);
	tft.print(set_temp,1);




	tft.setCursor(5,12);
    tft.setTextColor(ST7735_WHITE);
    tft.print("Room temp:");


    tft.setTextColor(ST7735_RED, ST7735_BLACK);
    tft.setCursor(70,12);
    tft.print(DHT11.getCelsius());
    Serial.println(DHT11.getCelsius(),0);

	tft.setCursor(5,23);
    tft.setTextColor(ST7735_WHITE);
    tft.print("Room hum:");


    tft.setTextColor(ST7735_RED, ST7735_BLACK);
    tft.setCursor(70,23);
    tft.print(DHT11.getHumidity());
    Serial.println(DHT11.getHumidity(),0);


    tft.drawLine(5,33,118,33,ST7735_BLUE);




    tft.println(" ");

    delay(100);

}*/

void DHT11_acquiring() 	// get informations from DHT11 sensor
{
	DHT11.acquire();
	while (DHT11.acquiring());
	int result = DHT11.getStatus();
	switch (result)
		{
		  case IDDHTLIB_OK:
			  //Serial.println("OK");
			  break;
		  case IDDHTLIB_ERROR_CHECKSUM:
			  Serial.println("Error\n\r\tChecksum error");
			  break;
		  case IDDHTLIB_ERROR_ISR_TIMEOUT:
			  Serial.println("Error\n\r\tISR Time out error");
			  break;
		  case IDDHTLIB_ERROR_RESPONSE_TIMEOUT:
			  Serial.println("Error\n\r\tResponse time out error");
			  break;
		  case IDDHTLIB_ERROR_DATA_TIMEOUT:
			  Serial.println("Error\n\r\tData time out error");
			  break;
		  case IDDHTLIB_ERROR_ACQUIRING:
			  Serial.println("Error\n\r\tAcquiring");
			  break;
		  case IDDHTLIB_ERROR_DELTA:
			  Serial.println("Error\n\r\tDelta time to small");
			  break;
		  case IDDHTLIB_ERROR_NOTSTARTED:
			  Serial.println("Error\n\r\tNot started");
			  break;
		  default:
			  Serial.println("Unknown error");
			  break;
		}
}

int day_time()  //set the value according to day - hour
{
	int x = (hour());
	if(x > 6 && x < 23)
		return 1; 			//if daytime   set 1
	else
		return 2;			//if nighttime set 2
}

int seconds_elapsed()
{
	int elapsed_secs = 0;
	if(prev_time > second())                     //necessary to work with 60 base count
		{
		elapsed_secs = (60-prev_time)+second();
		}
	else
		{
		elapsed_secs = second() - prev_time;
		}
	return elapsed_secs;
}

int minutes_elapsed()
{
	int elapsed_mins = 0;
	if(last_time > minute())					//necessary to work with 60 base count
		{
		elapsed_mins = (60-last_time)+minute();
		}
	else
		{
		elapsed_mins = minute() - last_time;
		}
	return elapsed_mins;
}

void draw(float value) {
  // graphic commands to redraw the complete screen should be placed here
  u8g.setFont(u8g_font_unifont);
  //u8g.setFont(u8g_font_osb21);
  //u8g.drawStr( 0, 22, "act_temp");

//void U8GLIB::setPrintPos(u8g_uint_t x, u8g_uint_t y);

}
void loop()
{

	u8g.firstPage();
	  do {
		  u8g.setFont(u8g_font_5x7r);
		  u8g.setPrintPos(0, 20);
		  char temp[5];
		  dtostrf(act_temp,5,1,temp);
		  //u8g.setPrintPos(20,0);
		   //u8g.setFont(u8g_font_osb21);
		   u8g.print(act_temp);
		   //U8GLIB::setPrintPos(0,20);
		  //u8g.drawStr(4,24,temp);

	  } while( u8g.nextPage() );
	  /*u8g.firstPage();
	  do {
		  // graphic commands to redraw the complete screen should be placed here
		  u8g.setFont(u8g_font_unifont);
		  //u8g.setFont(u8g_font_osb21);
		  u8g.setCursorPos(0, 20);
		  u8g.print("act_temp");
	  } while( u8g.nextPage() );*/


	int x = 0;
	bool change_temp = 0;


	if(Serial.available())
	  {
	     time_t t = processSyncMessage();
	     if(t >0)
	     {
	        RTC.set(t);   // set the RTC and the system time to the received value
	        setTime(t);
	     }
	  }


	//get temp and date-time
	DHT11_acquiring();

	act_temp = (DHT11.getCelsius());


	//Read pot pin
	x = analogRead(pot_pin);
	x = map(x, 0, 1023, 15, 45);

	//if temp is set to the minumum turn off the control and backlight
	if (x == 15)
		{
		stop_pump();
		//print_LCD();
		//lcd.setCursor(11,0);
		//lcd.print("-OFF-");
		analogWrite(lcd_bkl, 5);
		goto stop;
		}

	//5 seconds after the last set turn off backlight
	if(seconds_elapsed() >= delay_set)
		analogWrite(lcd_bkl, 5);

	//if the potentiometer is turn set a new target temp and turn on backlight
	if(x != prev_temp)
		{
		analogWrite(lcd_bkl, 255);
		prev_time = (second());
		change_temp = 1;
		delay(100);
		}
	//if is daytime set the target temp by the potentiometer
	if (day_time() == 1)
		{
		set_temp = (((x+15)*10)/2)/10.00; // set temperature by potentiometer in 0.5°C
		//lcd.setCursor(11,0);
		//lcd.print(" set");
		//lcd.setCursor(15,0);
		//lcd.write(byte(0));
		}
	//else if is night time set the temp to night_temp value
	else if (day_time() == 2)
		{
		set_temp = night_temp;


		//lcd.setCursor(11,0);
		//lcd.print("sleep");
		}

	//if delay_time is past turn on the temp control

	if (minutes_elapsed() >= delay_set || change_temp == 1)
		{
		if (act_temp < (set_temp - hys)) //if room is cold turn on the heater
			{
			start_pump();
			last_time = (minute());
			}

		else //else if room is warm keep off the heater
			{
			stop_pump();
			last_time = (minute());
			}
		change_temp = 0;
		}

	// print SET on LCD, set prev_temp value
	//print_LCD();

	//print_tft();
	prev_temp = x;
	delay(100);
	stop:

	delay(5000);
}


