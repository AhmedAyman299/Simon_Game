//************* variable configuration **************\\ 

int sequence[20];      // it stores the game sequence (up to 20 rounds)**(acts as a permanent memory)**
int currentRound = 0;  // it says how many steps are in the sequence so far where it tracks both "how many steps exist" and "where to put the next one."
int score = 0;

// LEDS
int leds[4] = {7,8,9,10};

// BUTTONS
int buttons[4] = {3,4,5,6};

// BEZO 
const int buzzer = 11;
//****************


void setup() {
  // put your setup code here, to run once:
  for(int i=0;i<4;i++)
  {
    pinMode(leds[i],OUTPUT);
    pinMode(buttons[i],INPUT_PULLUP);
  }

  pinMode(buzzer,OUTPUT);
  randomSeed(analogRead(A0)); //it makes the sequence random according to the reading on A0 which not connected to power but affected by noise signals
  Serial.begin(9600);

}

void loop() {
  random_selection();
  playback_sequence();
  bool good = get_player_input();
  Serial.println(good);
  if (good == true)
  {
    score++;
    Serial.println("Great Choice");
    Serial.print("SCORE: ");
    Serial.println(score);
    delay(1000);
  } else if(good == false)
  {
    Serial.print("GAME OVER, Final Score: ");
    Serial.println(score);
    while (true) {}
  }
}
//this loop is to save randomity selection,where each every time it runs, it picks one new random direction and appends it to the end of the growing sequence//
void random_selection()
{
 int randomity = random(0,4);
 sequence[currentRound] = randomity;
 currentRound++;


}
void playback_sequence() {
  for (int h = 0; h < currentRound; h++) {
    digitalWrite(leds[sequence[h]], HIGH);
    delay(700);
    digitalWrite(leds[sequence[h]], LOW);
    delay(350);
  }
}

bool get_player_input() // a  new boolean function where when it finished it will return true (1) or false (0) like yes the player got the whole sequence right" or "no they didn't 
{
  for (int z = 0; z<currentRound; z++) //A loop that counts z from 0 up to currentRound - 1, where currentRound is how many steps are in the sequence right now
    {
      long start_time = millis(); //how many milliseconds since the Arduino turned on has been saved into start_time, i put it in the loop not to be golobal so the counter reseted every time player pressed a button and count 5 seconds 
      Serial.print("Start time: ");// this here is to be show the start time the counter start_time has been started from so no time calcuating error occurs
      Serial.println(start_time);
    
      bool got_Press = false; //acts as a switch that said at this moment no button has been pressed
      while (!got_Press)
      {
        if (millis()-start_time>=5000)
        {
          Serial.print("TIME OUT : ");
          Serial.println(millis());
          Serial.println("5 seconds have passed");
          Serial.println("try faster next time!");
          tone(buzzer,1000,350);
          return false;     //This fires when the player takes too long to press anything at all — 5 seconds pass with no button touched. 
        }
        for(int b = 0;b<4;b++)    //this loop checks the state of the buttons every time we loop 
        {
          if (digitalRead(buttons[b]) == LOW) 
          {
            got_Press = true;
              if (b != sequence[z]) 
              {
                Serial.println("Wrong button!");
                return false;
              }
          }
        while (digitalRead(buttons[b]) == LOW) {} // this actually do nothing but its small function is as long as the exact button is still being held down, just sit here and do nothing — don't move forward
            
          
        }



      }
      
    }
return true;
}
