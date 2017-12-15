int moles = 5;

int leds[5];
int buttons[5];
bool isHit[5];
int hitCount = 0;
unsigned long time;
float moleHang = 3000;
int score = 0;

bool buttonState = false;
bool lastButtonState = false;
int buttonPushCounter = 0;

void setup()
{
  randomSeed(analogRead(0));
  for(int i = 0; i < moles; i++)
  {
    pinMode(9+i, OUTPUT);
    pinMode(3+i, INPUT);
    
    isHit[i]=true;
  }
}

void loop()
{
  int count = 0;
  time = millis();
  int random = randLed();
  int curLed = random + 9;
  int curButton = random + 3;
  
  while(count < moleHang)
  {
	digitalWrite(curLed, true);
    
    if(digitalRead(curButton))
  	{
      score++;
      moleHang = moleHang * 0.90;
      
      break;
  	} 
       
    delay(1);
    count++;
  }
  
  
  /*for(int i = 0; i < moles; i++)
  {
    if(digitalRead(3+i))
    {
      digitalWrite(9+i, true);
      hitCount++;
    }
  }*/
    
  /*digitalWrite(13, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(13, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
  */
	reset();
}

void reset()
{
  for(int i = 0; i < moles; i++)
  {
    digitalWrite(9+i, false);
    //digitalWrite(3+i, false);
  }
}

int randLed()
{
  return random(0, moles);
}
