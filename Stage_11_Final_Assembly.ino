#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16 ,2);
Servo myServo;

int joystickDeger;

int secilenSayi = 0;

int joystickButton;

int girilenSifre[4];

int hane = 0;

int yesilled = 7;

int kirmiziled = 6;

int buzzer = 8;

bool sifreDogru;

int dogruSifre[4] = {5, 2, 8, 0};

void setup() {

// Giriş pinleri
  pinMode(A1, INPUT_PULLUP);

  pinMode(yesilled, OUTPUT);
 
  pinMode(kirmiziled, OUTPUT);

  pinMode(buzzer, OUTPUT);

  digitalWrite(yesilled, LOW);

  digitalWrite(kirmiziled, LOW);

  digitalWrite(buzzer, LOW);

  myServo.attach(9);
  myServo.write(0);

// LCD başlatma
  lcd.init();
  lcd.backlight();

  lcd.setCursor(1,0);
  lcd.print("Smart Safe");

  lcd.setCursor(1,1);
  lcd.print("Loading...");
  delay(2000);

  lcd.clear();
  
  lcd.setCursor(1,0);
  lcd.print("Enter Password"); 

}

void loop() 
{

  joystickDeger = analogRead(A0);
  joystickButton = digitalRead(A1);
  
  // Sağa sola sayı değiştiren if'ler 
  if (joystickDeger > 600)
  {

  if (secilenSayi < 9)
  {

  secilenSayi++;

  }

  while (analogRead(A0) > 600)
  {

  }
  
 }
  
  if (joystickDeger < 400)
  {
  
  if (secilenSayi > 0)
  {
  
  secilenSayi--;

  }

  while (analogRead(A0) < 400)
  {

  }

  }
  

  // Seçilen sayıyı onaylayan
  if (joystickButton == LOW)
  {

  
  if (hane < 4)
  {
 girilenSifre[hane] = secilenSayi;

 hane++ ;

 secilenSayi = 0;
  
  }
  
  while (digitalRead(A1) == LOW)
  {

  }
}

 lcd.setCursor(0,1);
 lcd.print("                ");

 lcd.setCursor(4,1);

 for (int i = 0; i < 4; i++)
 {

  if (i < hane)
 {

  lcd.print(girilenSifre[i]);

 }

 else if (i == hane)
 {

 lcd.print(secilenSayi);
 }

 else
 {
   lcd.print("_");
 }

   lcd.print(" ");

 }
 if (hane == 4)
 {
 sifreDogru = true;

 for (int i = 0; i < 4; i++)
{

  if (girilenSifre[i] != dogruSifre[i])
  {
  
  sifreDogru = false;
  break;
 }
}

if (sifreDogru == true)
{

lcd.setCursor(0,1);
lcd.print("True Password");

digitalWrite(buzzer, HIGH);
delay(200);

digitalWrite(buzzer, LOW);

myServo.write(90);

digitalWrite(yesilled, HIGH);

delay(10000);

myServo.write(0);

digitalWrite(yesilled, LOW);

lcd.setCursor(0,1);
lcd.print("                ");
hane = 0;

}

else 
{
  lcd.setCursor(0,1);
  lcd.print("Wrong Password");
  
   digitalWrite(kirmiziled, HIGH);
 
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);

  delay(1500);

  digitalWrite(kirmiziled, LOW);

  lcd.setCursor(0,1);
  lcd.print("                ");

  hane = 0;

}



 }
 
 } 