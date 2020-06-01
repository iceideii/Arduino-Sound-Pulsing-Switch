#include <Servo.h> //include the library for the servo motor

int MIC = A0; //sound detect component connected to A0 leg
boolean toggle = false; //recording the initial version of the toggle
int micVal; //record the detected volume

Servo servo; //set the Servo motor's name as servo

unsigned long current = 0; //record the current time stamp
unsigned long last = 0; //record the last time stamp
unsigned long diff = 0; //record the difference of time in between the two time stamps
unsigned int count = 0; //record the count of toggles

void setup() { //run for once

  servo.attach(2); //initialize the servo to connect to D-pin leg 2
  Serial.begin(9600); //initialize the serial
  servo.write(180); //make the servo turn to its initial angle
  
}

void loop() { //loop forever

  micVal = analogRead(MIC); //read the analog output

 Serial.println(micVal);
 delay(20);
  if (micVal > 180) { //if over the limit

    current = millis(); //record the current time stamp
    ++count; //add one to counted toggles

 //   Serial.print("count="); //output the toggled times
  //  Serial.println(count); //print out the number

    if (count >= 2) { //if the toggled count is already more than or equal than two, determine if the two time stamps lasted between 0.3~1.5 second
      diff = current - last; //calculate the difference of time in between the two time stamps
      if (diff > 300 && diff < 1500) { //determine if the two time stamps lasted between 0.3~1.5 second

        toggle = !toggle; //revert the current condition of the toggle
        count = 0; //make the count zero, get ready to test again

      } else { //if the time does not last in between the constrained counts, then revert the count to one

        count = 1; //do not count the count

      }
    }

    last = current; //use the current time stamp to update the last time stamp for the next comparison

    if (toggle) { //determine if the toggle is on

      servo.write(90); //servo will turn to 90 degrees for opening the light
      delay(3000); //delay 5 seconds
      servo.write(180); //servo will turn back to its original spot
      delay(1000); //delay another 5 seconds

      count = 0; //set count to initial number to recount

    }
    else {

      servo.write(180); //if the toggle does not work, than just stay at the initial 180 degrees

    }

  }

}
