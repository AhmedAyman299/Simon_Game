[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/dFo5kUEQ)
# Video Link :
https://drive.google.com/drive/folders/1PB52smQiOUqtGSExqPXWEj3KQ2-pSy83?usp=sharing 
# TinkerCad link :
https://www.tinkercad.com/things/3jF6bHw0hvu/editel?returnTo=%2Fthings%2F2uVl27DKVmY-exquisite-wluff&sharecode=w6227A7NsTZ4fRIlC3LZFJa3bUMaxXgSrzfsB7i6nXU
# The Code :
## 1 - Code explanation 

- ### We start our code with the declaration of the global variables that may store a single value or an array of values

- ### then the void setup(), which contain:
  
    - LEDs and buttons pins state.
    - buzeer pin state.
    - the randomSeed() function, which makes the arduino starts the random sequence generation that is used in random() function in the loops later, we put inside       it the pin A0, which is really not connected to anything in the circuit, but it's actually gets a slightly small effect from the noise in the environment            every time we power the Arduino, so that unpredictable reading is fed into randomSeed() which then makes random() produces different sequence each time you        start the game.
    - the most important one, the serial.begin that starts that makes the Arduino able to show results in the serial monitor.
- ### There are two functions we used and one boolean to make that code work correctly :
  
  - #### function 1 : void random_selection()
      - This function doesn't return a value; its function is to pick one new random direction and add it to the end of the sequence
      - I first create a variable called randomity to save in it the value of the random (0,4), which asks for a random whole number between (0,1,2,3), so                 every time it picks up a different number and starts it, and this sequence is saved inside randomity
      - I first make the sequence[] save a place for 20 characters in the memory when we declared it at the beginning of the code, and another variable is                 currentRound, which is also declared but with inital value = 0, so  when we put it together sequence[currentRound] = randomity we make the random                  sequence started initially when currentRound = 0 and then increases this sequence by increasing the currentRound and appending the new sequence to the             old one givng us the whole game sequence until round 19 ( because we save in the sequence only 20 characters )
      - I don't forget to put currentRound++ to increase the value of currentRound by 1 every time
  
  - #### function 2 : void planback_sequence()
    
      - This function doesn't return a value; it just performs an action (lighting up LEDs in order) and finishes, where it walks through the entire sequence               recorded so far, turning each corresponding LED on and off in order, replaying the whole pattern from the beginning to every single round.
      - The meaning of leds[sequence[h]] is very easy, it says that according to the value of h ( which by the way increases linearly from 0 until it achieve a            value < currentRound ), so let's say that we have now a sequence[1,0,3] and the currentRound now = 3
        we when h = 0 ---> sequence[0] = 1 ---> leds[1] = pin 8
                h = 1 ---> sequence[1] = 0 ---> leds[0] = pin 7
                h = 2 ---> sequence[2] = 3 ---> leds[3] = pin 9
        So, in this sequence inside the for loop I put this in, the LEDs will flash in this order, giving it a random flashing sequence
        But when h = 3, which is = currentRound, the for loop stops until the next round and repeats the whole flashing sequence again, adding to it the new               random value inside the sequence[]
        
  - #### Boolean function: bool get_player_input()
    
      - When this function is completely done, it will hand back either true or false, nothing else
      - bool got_Press = false ----> acts as a switch where it is in normal state off (false), no button has been pressed
      - We know that a while loop does its work when only the value inside its parentheses is true, so let's put while(!get_Press), which means while(true) to             start the loop
      - if (millis()-start_time>=5000) ----> this means if no button is pressed for 5 seconds, do what is inside the if condition
      - The importance of ( return false; ) inside if is to immediately exit the bool function when the player passes 5 seconds without pressing any button,               giving it a returned false value
      - inside the for loop, a counter with variable b checks for all buttons at position b, check: is it currently being pressed, and if it is correct, flip the          switch from before to "on", if not, return false, which means as we said before
      - the most confusing part is ( while (digitalRead(buttons[b]) == LOW) {} ) ----> its importance is that it ensures the circuit doesn't concern as long as             you are still pressing a specific button, where without it your press may be considered inside the next sequence, which may be wrong
      - If the function the end of the loop, it means it got through all the z steps (the whole outer loop finished) without ever hitting one of the two return            false lines above, meaning every single button press was correct and on time. So it hands back true ( return true; )

    After we finish defining all these functions, we must insert them inside the main void loop to make the code run as long as the circuit works

- ### the void loop()
    -This is Arduino's special function that runs automatically, over and over, forever, once the board is powered on
    - I call the two functions I created: random_selection() & planback_sequence()
    - the part bool good = get_player_input(); ----> Calls get_player_input(), which waits for the player to press buttons that may be true or false
    - then put a condition, which said when good = true do something and if good = false do another thisng
    - the while ( true ){} inside the else if is to stop the game when we press the wrong button, where logically the program is stuck inside the while loop doing       nothing else; the code doesn't stop, but it is still running in an infinite loop with no conditions doing nothing,
      Why can't we replace it with ( break; )? ----> because break doesn't work when it is inside an if/else condition, it only works inside loops and switch            statement


## 2 - Future Work 
 - I hope to learn the way to add the point of making the user choose between 3 levels classified according to their number of rounds and how fast the delay time    is 

      
