int moles = 5;

int leds[5];
int buttons[5];

//moleHang aka how long the moles hang around!
float moleHang = 5000;

//keep track of who's winning
int badHits = 0;
int score = 0;
int roundCount = 0;
bool badHit = false;
bool goodHit = false;

//keep track of how long the game has been on
extern volatile unsigned long timer0_millis;
unsigned long time = 0;
unsigned long timeGameStart = 0;

int prevRandom = 0;

//setup all buttons and leds
void setup()
{
  //Serial.begin(9600);
  //Serial.println("--- Start Serial Monitor SEND_RCVE ---");
  
  randomSeed(analogRead(0));
  for(int i = 0; i < moles; i++)
  {
    pinMode(9+i, OUTPUT);
    pinMode(3+i, INPUT);
  }
  
  pinMode(1, OUTPUT);
  pinMode(0, OUTPUT);
  
  while(!digitalRead(7))
  {
    startScreen();
  }
  
  setMillis(0);
  reset();
}

void loop()
{
  // way to time how long the led is on
  int count = 0;
  badHit = false;
  goodHit = false;
  
  time = millis();
  
  if(time >= 20000)
  {
    gameOver();
  }
  
  //generate random number
  int random = genRand();
  
  //set led(mole) to on based on random number, and corresponding button
  int curLed = random + 9;
  int curButton = random + 3;
  
  int whileTime = randMoleHang();
  
  //while the time of moleHang(in ms) is not past
  while(count < whileTime)
  {
    if(count > whileTime/2)
    {
      //turn on the mole every iteration
    digitalWrite(curLed, true);    
    
      for(int i = 0; i < moles; i++)
      {
        if(digitalRead(3+i))
        {
              
        //check if currect button is true
          if(digitalRead(curButton))
          {
            //increment score
            goodHit = true;

            //shine the green LED
            digitalWrite(1, true);
            delay(20);

            //break out of while and start new loop()
            break;
          }
          else
          {
            badHit = true;

            //shine the red LED!
            digitalWrite(0, true);
            delay(20);
            
            break;
          }
        }  
      }
    }
    
    //time in ms per unit of moleHang
    delay(1);
    count++;
  }
  
  //reset game clear board
  roundCount++;
  keepScore();
  
  //speed up game after a successful mole hit
  moleHang = 500 + (moleHang * 0.70);

  reset();
}

void reset()
{
  //loop through all buttons and lights set all to false
  for(int i = 0; i < moles; i++)
  {
    digitalWrite(9+i, false);
    digitalWrite(3+i, false);
  }
  
  digitalWrite(1, false);
  digitalWrite(0, false);
}

//generate random number from 0 to how many moles in play
int genRand()
{
  return random(0, moles);
}

//generating random time for moles to hang around
int randMoleHang()
{
  return random(500, moleHang);  
}

//mock function for a gameover scenario
int gameOver()
{
  //Serial.println(score);
  //Serial.println(badHits);
  if(score >= badHits)
  {
    while(true)
    {
      for(int i = 0; i < moles; i++)
      {
        digitalWrite(9+i, true);
      }

      digitalWrite(0, true);
      digitalWrite(1, true);
      
      delay(1000);
      
      for(int i = 0; i < moles; i++)
      {
        digitalWrite(9+i, false);
      }

      digitalWrite(0, false);
      digitalWrite(1, false);
      
      delay(1000);
    }
    
  }
  else
  {
    for(int i = 0; i < moles; i++)
    {
      digitalWrite(9+i, true);
    }

    digitalWrite(0, true);
    digitalWrite(1, true);
  }
  
}

void startScreen()
{
  for(int i = 0; i < moles; i++)
  {
    digitalWrite(9+i, true);
  }
  
  digitalWrite(0, true);
  digitalWrite(1, true);
}

void keepScore()
{
  if(badHit == false && goodHit == false)
  {
    badHits++;
    
    //shine the red LED!
    digitalWrite(0, true);
    delay(100);
  }
  else if(goodHit == true)
  {
    score++;
    
    //shine the red LED!
    digitalWrite(1, true);
    delay(100);
  }
  else
  {
    badHits++;
    
    //shine the red LED!
    digitalWrite(0, true);
    delay(100);
  }
}

//Sets the millis value
//Not my code, taken from https://tomblanch.wordpress.com/2013/07/27/resetting_millis/
void setMillis(unsigned long new_millis)
{
  uint8_t oldSREG = SREG;
 
  cli();
  timer0_millis = new_millis;
  SREG = oldSREG;
}
