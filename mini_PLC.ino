
// ELECTROVANNE 1
//DÉBUT
int on_off1   = 1; 

int jour_1I    = 4; // 0=Dim, 1=Lun, 2=Mar, 3=Mer, 4=Jeu, 5=Ven, 6=Sam
int time_1I   = 14;
int minute_1I = 36; 
//FIN
int jour_1F    = 4; // 0=Dim, 1=Lun, 2=Mar, 3=Mer, 4=Jeu, 5=Ven, 6=Sam
int time_1F   = 14; 
int minute_1F = 37;

// ELECTROVANNE 2
//DÉBUT
int on_off2   = 1;

int jour_2I    = 4; // 0=Dim, 1=Lun, 2=Mar, 3=Mer, 4=Jeu, 5=Ven, 6=Sam
int time_2I   = 14;
int minute_2I = 37;
// FIN
int jour_2F    = 2; // 0=Dim, 1=Lun, 2=Mar, 3=Mer, 4=Jeu, 5=Ven, 6=Sam
int time_2F   = 14;
int minute_2F = 38;

// ELECTROVANNE 3
//DÉBUT
int on_off3   = 1;

int jour_3I    = 2; // 0=Dim, 1=Lun, 2=Mar, 3=Mer, 4=Jeu, 5=Ven, 6=Sam
int time_3I   = 12;
int minute_3I = 18;
//FIN
int jour_3F    = 2; // 0=Dim, 1=Lun, 2=Mar, 3=Mer, 4=Jeu, 5=Ven, 6=Sam
int time_3F   = 14;
int minute_3F = 19;

// ELECTROVANNE 4
//DÉBUT
int on_off4   = 1;

int jour_4I    = 2; // 0=Dim, 1=Lun, 2=Mar, 3=Mer, 4=Jeu, 5=Ven, 6=Sam
int time_4I   = 14;
int minute_4I = 32;
//FIN
int jour_4F    = 2; // 0=Dim, 1=Lun, 2=Mar, 3=Mer, 4=Jeu, 5=Ven, 6=Sam
int time_4F   = 14;
int minute_4F = 34;

#include <Wire.h>
#include "Sodaq_DS3231.h"
//#include <DS3231.h>
#include <LiquidCrystal_I2C.h> // Debe descargar la Libreria que controla el I2C
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2); //  *  lcd: SDA (pinA4), SCL(pinA5)
char JourDeSemaine[][6] = { "Dim", "Lun", "Mar", "Mer", "Jeu", "Ven", "Sam" };
//year, month, date, hour, min, sec and week-day(starts from 0 and goes to 6)
//writing any non-existent time-data may interfere with normal operation of the RTC.
//Take care of week-day also.
//DateTime dt(2021, 06, 25, 14, 06, 0, 5); // une seule fois
const int InA1 = A0;
const int InA2 = A1;
const int InA3 = A2;
const int InA4 = A3;
const int InD1 = 9;
const int InD2 = 10;

const int EV1 = 4;
const int EV2 = 5;
const int EV3 = 6;
const int EV4 = 7;
const int M1 = 3;
const int M2 = 2;

void setup() {
  Wire.begin();
  rtc.begin();
  // une seule fois pour regler l'heure
  //rtc.setDateTime(dt); //Adjust date-time as defined 'dt' above 
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  // La ligne définit la date, l'heure et le jour de la semaine, la ligne doit être supprimée lors du deuxième chargement
  
  pinMode(InA1, INPUT);
  pinMode(InA2, INPUT);
  pinMode(InA3, INPUT);
  pinMode(InA4, INPUT);
  pinMode(InD1, INPUT);
  pinMode(InD2, INPUT);

  pinMode(EV1, OUTPUT);
  pinMode(EV2, OUTPUT);
  pinMode(EV3, OUTPUT);
  pinMode(EV4, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);

}

void loop()
{
int segundo_I = 0;
int segundo_F = 0;
  ////Read Real Time Clock
  DateTime now = rtc.now();
  lcd.setCursor(0, 0);
  rtc.convertTemperature();             //convert current temperature into registers
  lcd.print("T:");
  lcd.print(rtc.getTemperature()); //read registers and display the temperature
  lcd.print((char)223);            // on ajoute le symbole ° après la valeur de la température
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print(now.date(), DEC);
  lcd.print('/');
  lcd.print(now.month(), DEC);
  lcd.print(' ');
  lcd.print(now.hour(), DEC);
  lcd.print(':');
  lcd.print(now.minute(), DEC);
  lcd.print(':');
  lcd.print(now.second(), DEC);
  lcd.print(' ');
  lcd.print(JourDeSemaine[now.dayOfWeek()]);
  
  // ELECTROVANNE 1
  if (on_off1 == 1) {
    if ((now.dayOfWeek() == jour_1I && now.hour() == time_1I && now.minute() == minute_1I )|| digitalRead(InD1)) {
      lcd.setCursor(10, 0);
      lcd.print("EV1 ON");
      digitalWrite(EV1, 1);
      digitalWrite(M2, 1);
      digitalWrite(M1, 1);
    }
  }
  if ((now.dayOfWeek() == jour_1F && now.hour() == time_1F && now.minute() == minute_1F)|| !digitalRead(InD1)) {
          lcd.setCursor(10, 0);
      lcd.print("EV OFF");
    digitalWrite(EV1, 0);
    digitalWrite(M2, 0);
    digitalWrite(M1, 0);
  }

  // ELECTROVANNE 2
  if (on_off2 == 1) {
    if (now.dayOfWeek() == jour_2I && now.hour() == time_2I && now.minute() == minute_2I) {
    lcd.setCursor(10, 0);
    lcd.print("EV2 ON");
      digitalWrite(EV2, 1);
      digitalWrite(M2, 1);
      digitalWrite(M1, 1);
    }
  }
  if ((now.dayOfWeek() == jour_2F && now.hour() == time_2F && now.minute() == minute_2F)) {
          lcd.setCursor(10, 0);
      lcd.print("EV OFF");
    digitalWrite(EV2, 0);
    digitalWrite(M2, 0);
    digitalWrite(M1, 0);
  }
  // ELECTROVANNE 3
  if (on_off3 == 1) {
    if (now.dayOfWeek() == jour_3I && now.hour() == time_3I && now.minute() == minute_3I) {
         lcd.setCursor(10, 0);
      lcd.print("EV3 ON");
      digitalWrite(EV3, 1);
      digitalWrite(M2, 1);
      digitalWrite(M1, 1);
    }
  }
  if ((now.dayOfWeek() == jour_3F && now.hour() == time_3F && now.minute() == minute_3F)) {
          lcd.setCursor(10, 0);
      lcd.print("EV OFF");
    digitalWrite(EV3, 0);
    digitalWrite(M2, 0);
    digitalWrite(M1, 0);
  }

  // ELECTROVANNE 4
  if (on_off4 == 1) {
    if ((now.dayOfWeek() == jour_4I && now.hour() == time_4I && now.minute() == minute_4I)|| digitalRead(InD2)) {
    lcd.setCursor(10, 0);
    lcd.print("EV4 ON");
      digitalWrite(EV4, 1);
      digitalWrite(M2, 1);
      digitalWrite(M1, 1);
    }
  }
  if ((now.dayOfWeek() == jour_4F && now.hour() == time_4F && now.minute() == minute_4F)|| !digitalRead(InD2)) {
          lcd.setCursor(10, 0);
      lcd.print("EV OFF");
    digitalWrite(EV4, 0);
    digitalWrite(M2, 0);
    digitalWrite(M1, 0);
  }

  if (on_off1 == 0 || on_off2 == 0 || on_off3 == 0 || on_off4 == 0) {
    if(on_off1 == 1 && on_off2 == 1 && on_off3 == 1 && on_off4 == 1){
    digitalWrite(M2, 0);
    digitalWrite(M1, 0);
  }
  }
}
