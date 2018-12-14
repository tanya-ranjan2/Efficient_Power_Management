#define IR1                   11     /* digital pin input for ir sensor  */
#define IR2                   12      /* digital pin input for ir sensor  */
#define MAX_NUMB              99
int IR1_out = LOW; /* Avoiding initial false detections.    */
int IR2_out = LOW; /* Avoiding initial false detections.    */
int a = 2;  //For displaying segment "a"
int b = 3;  //For displaying segment "b"
int c = 4;  //For displaying segment "c"
int d = 5;  //For displaying segment "d"
int e = 6;  //For displaying segment "e"
int f = 7;  //For displaying segment "f"
int g = 8;  //For displaying segment "g"
int counter = 0;
int i = 0;
int ldr = A1;
int Light = 0;


void increaseAndDisplay() {
  counter++;
  if (counter > MAX_NUMB) {
    counter = 1;
  }
  //setDisplayValue(counter);

}

void decreaseAndDisplay() {
  if (counter) {
    counter--;
    //    setDisplayValue(counter);
  }
}


void displayDigit(int digit)
{ turnOff();
  //Conditions for displaying segment a
  if (digit != 1 && digit != 4)
    digitalWrite(a, LOW);

  //Conditions for displaying segment b
  if (digit != 5 && digit != 6)
    digitalWrite(b, LOW);

  //Conditions for displaying segment c
  if (digit != 2)
    digitalWrite(c, LOW);

  //Conditions for displaying segment d
  if (digit != 1 && digit != 4 && digit != 7)
    digitalWrite(d, LOW);

  //Conditions for displaying segment e
  if (digit == 2 || digit == 6 || digit == 8 || digit == 0)
    digitalWrite(e, LOW);

  //Conditions for displaying segment f
  if (digit != 1 && digit != 2 && digit != 3 && digit != 7)
    digitalWrite(f, LOW);
  if (digit != 0 && digit != 1 && digit != 7)
    digitalWrite(g, LOW);

}
void turnOff()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin (9600);
  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(ldr, INPUT);
  pinMode(13, OUTPUT);
  pinMode(a, OUTPUT);  //A
  pinMode(b, OUTPUT);  //B
  pinMode(c, OUTPUT);  //C
  pinMode(d, OUTPUT);  //D
  pinMode(e, OUTPUT);  //E
  pinMode(f, OUTPUT);  //F
  pinMode(g, OUTPUT);  //G
  displayDigit(0);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);


}

void sensor() {
  IR1_out = digitalRead(IR1);
  IR2_out = digitalRead(IR2);


  if (IR1_out == HIGH)
  {

    while (IR1_out == HIGH)
    {
      while (IR2_out == LOW)
      { IR2_out = digitalRead(IR2);
        displayn(counter);
        Serial.println("waiting for confirmation");
        displayn(counter);
        while (IR1_out == HIGH)
        { displayn(counter);
          IR1_out = digitalRead(IR1);

        }

        IR1_out = digitalRead(IR1);
        if (IR1_out == HIGH)
        {
          while (IR1_out == HIGH)
          {
            IR1_out = digitalRead(IR1);
            displayn(counter);
          }
          Serial.println("confirmation cancelled");
          // counter--;
          break;

        }
      }
      while (IR2_out == HIGH)
      { IR2_out = digitalRead(IR2);
        displayn(counter);
        if (IR2_out == LOW) {
          increaseAndDisplay();
        }
        Serial.println("confiremd");

        IR1_out = digitalRead(IR1);
      }

      //increaseAndDisplay();
      //displayDigit(counter);
      Serial.println(counter);
      // delay(2000);
    }
  }
  else if (IR2_out == HIGH)
  {
    while (IR2_out == HIGH)
    {
      while (IR1_out == LOW)
      { IR1_out = digitalRead(IR1); displayn(counter);
        while (IR2_out == HIGH)
        {
          IR2_out = digitalRead(IR2);
          displayn(counter);
        }

        IR2_out = digitalRead(IR2);
        if (IR2_out == HIGH)
        {
          while (IR2_out == HIGH)
          {
            IR2_out = digitalRead(IR2);
            displayn(counter);
          }
          // counter++;
          break;

        }
      }
      while (IR1_out == HIGH)
      { IR1_out = digitalRead(IR1); displayn(counter);
        if (IR1_out == LOW)
        {
          decreaseAndDisplay();
        }
      }
      IR2_out = digitalRead(IR2);//displayn(counter);
    }


    //decreaseAndDisplay();
    //displayDigit(counter);
    Serial.println(counter);

  }

  Light = analogRead(ldr);


  if (counter > 0 && Light <= 350) {
    digitalWrite(13, LOW);
  }

  else {
    digitalWrite(13, HIGH);
  }
}


void displayn(int num)
{
  //turnOff();
  //for (long int t = 0; t < 100; t++) {
  int j = num / 10;
  int I = num % 10;
  digitalWrite(10, LOW);
  displayDigit(I);
  digitalWrite(9, HIGH);
  delay(10);

  digitalWrite(9, LOW);
  displayDigit(j);
  digitalWrite(10, HIGH);
  delay(10);

  // }

}

void loop() {
  //
  //displayn(counter);
  sensor();
  displayn(counter);


}
