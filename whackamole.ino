int moles = 5;

int leds[5];
int buttons[5];

//starting delay
float moleHang = 3000;

int badHits = 0;
int score = 0;

int prevRandom = 0;

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
  }
}

void loop()
{
  // way to time how long the led is on
  int count = 0;
  //generate random number
  int random = genRand();
  
  //set led(mole) to on based on random number, and corresponding button
  int curLed = random + 9;
  int curButton = random + 3;
  
  //while the time of moleHang(in ms) is not past
  while(count < moleHang)
  {
    //turn on the mole every iteration
	digitalWrite(curLed, true);
    
    //check if currect button is true
    if(digitalRead(curButton))
  	{
      //increment score
      score++;
      
      //speed up game after a successful mole hit
      moleHang = moleHang * 0.95;
      
      //break out of while and start new loop()
      break;
  	}
    
    //time in ms per unit of moleHang
    delay(1);
    count++;
  }
  
  //reset game clear board
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
}

//generate random number from 0 to how many moles in play
int genRand()
{
  return random(0, moles);
}

//mock function for a gameover scenario
int gameover()
{
  for(int i = 0; i < moles; i++)
  {
    digitalWrite(9+i, true);
  }
  
  return 0;
}
