int moles = 5;

int leds[5];
int buttons[5];

//moleHang aka how long the moles hang around!
float moleHang = 5000;

//keep track of who's winning
int badHits = 0;
int score = 0;

int prevRandom = 0;

//setup all buttons and leds
void setup()
{
  randomSeed(analogRead(0));
  for(int i = 0; i < moles; i++)
  {
    pinMode(9+i, OUTPUT);
    pinMode(3+i, INPUT);
  }
  
  pinMode(1, OUTPUT);
  pinMode(0, OUTPUT);
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
          if(digitalRead(curButton))
          {
            //increment score
            score++;

            //speed up game after a successful mole hit
            moleHang = moleHang * 0.95;

            //shine the green LED
            digitalWrite(1, true);
            delay(20);

            //break out of while and start new loop()
            break;
          }
          else
          {
            //increment bad hits!
            badHits++;

            //shine the red LED!
            digitalWrite(0, true);
            delay(20);
            
            break;
          }
        }  
      }
  	}
    
    //check if currect button is true
    
    
    
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
int gameover()
{
  for(int i = 0; i < moles; i++)
  {
    digitalWrite(9+i, true);
  }
  
  return 0;
}
