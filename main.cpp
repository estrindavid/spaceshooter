

Section I – Program Code

/* Student Name: David Estrine
   Title of Sketch: Space Shooter
   Description of Sketch: A space shooter game using a ultrasonic sensor as a controller together with the serial monitor and nokia lcd display to display information.
   Date of Completion: Jan 2024
*/

#define LCD_CE 5 // define LCD_CE to the pin connected to the CS pin of the LCD display
#define LCD_RESET 6 // define LCD_CE to the pin connected to the RST pin of the LCD display
#define LCD_DC 4 // define LCD_CE to the pin connected to the DC pin of the LCD display
#define LCD_DIN 3 // define LCD_CE to the pin connected to the DIN pin of the LCD display
#define LCD_CLK 2 // define LCD_CE to the pin connected to the CLK pin of the LCD display
#define LCD_C LOW // Define the state of LCD_C
#define LCD_D HIGH // Define the state of LCD_D
int index = 0; // Set the index starting point for the for loop

// Variables used within the program

// Spaceship variables
int ssPosition; // create a variable to track the spaceships position
int random1; // create a variable to store a random number randomizing the way the spaceships movement is calculated
int ssIndex = 195; // create a variable to track the spaceships index position on the grap array
int ssDivisor = 3; // create a variable to keep the divisor used to calculate the spaceship position

// Obstacle Variables
int obsRandom; // create a variable to return a random value to choose between which obstacle to use for each level
int obsRandomChoice = 2; // create a variable that holds the number of choices that the obstacle random number can be for its position
int ssRandomChoice = 5; // create a variable that holds the number of choices that the spaceship random number can be for its movement
byte obstacleHex1; // create a variable to track the first obstacles hexadecimal number
byte obstacleHex2; // create a variable to track the second obstacles hexadecimal number
int obsFrame = 1; // create a variable to the obstacles animations starting frame
int obsLevel = 1; // create a variable to track the obstacles current level
int obsIndex = 278; // create a variable to track the obstacles index position on the grap array

// Main Game Variables
bool loseMessage = false; // create a variable to track if a losing message has been shown to the user
bool startGame = false; // create a variable to track if the game has been started
String monitorInput; // create a variable to store the Serial monitor's input
int gameDelay = 35; // create a variable to store the delay between each frame on the lcd display
bool gameOver = false; // create a variable to track whether the game has ended
int unconnectedPin = 13; // create a variable to store a pin number that has no connections to it

// Ultrasonic sensor variables
int pingPin = 10; // Create a variable that holds the pin number of the pin that sends out ultrasonic bursts
int inPin = 9; // Create a variable that hold the pin number of the pin that receive the pulse back
long objectDuration; // Create a variable that stores the value gotten back from the ultrasonic sensor
long objectCm; // Create a variable that stores the ultrasonic sensors output in centimeters

byte grap[] = // Create an array storing a frames hexadecimal information for every pixel on the lcd display
{
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,


  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF,

  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF,

  0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00,

  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF,

  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
  0xFF, 0xFF, 0xFF, 0xFF,


  0x04F, 0x049, 0x049, 0x079,  0x00, 0x07F, 0x09, 0x09, 0x0F,  0x00, 0x07F, 0x09, 0x09, 0x07F, 0x00, 0x07F, 0x041,
  0x041, 0x041, 0x00, 0x07F, 0x049, 0x049, 0x049, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04F, 0x049, 0x049, 0x079, 0x00, 0x07F, 0x08, 0x08, 0x07F,
  0x00, 0x07F, 0x041, 0x041, 0x07F, 0x00, 0x07F, 0x041, 0x041, 0x07F,  0x00, 0x01, 0x01, 0x07F, 0x01, 0x01,
};


void LCD_Initialise(void) { // create a function to initialise the lcd display

  pinMode (LCD_CE, OUTPUT); // set CS pin on the lcd display as an output
  pinMode(LCD_RESET, OUTPUT); // set RST pin on the lcd display as an output
  pinMode(LCD_DC, OUTPUT); // set DC pin on the lcd display as an output
  pinMode(LCD_DIN, OUTPUT); // set DIN pin on the lcd display as an output
  pinMode(LCD_CLK, OUTPUT); // set CLK pin on the lcd display as an output
  digitalWrite(LCD_RESET, LOW); // send a low signal to the lcd's RST pin
  digitalWrite(LCD_RESET, HIGH); // send a high signal to the lcd's RST pin
  LCD_Write(LCD_C, 0x21); // set the lcd display's extended commands
  LCD_Write(LCD_C, 0xB9); // set the lcd's Vop (Contrast)
  LCD_Write(LCD_C, 0x04); // set the lcd's Temp coefficient
  LCD_Write(LCD_C, 0x14); // set the lcd's bias mode to be 1:48
  LCD_Write(LCD_C, 0x20); // set the lcd's Basic Commands
  LCD_Write(LCD_C, 0x0C); // set the lcd to be in normal mode
}

void LCD_Write(byte dc, byte data) // Create a function taking 2 parameters dc & data that would display a pixel on the lcd display
{
  digitalWrite(LCD_DC, dc); // send a certain signal to the DC pin depending on the parameter
  digitalWrite(LCD_CE, LOW); // send a low signal to the CS pin on the lcd display
  shiftOut(LCD_DIN, LCD_CLK, MSBFIRST, data); // send the data to the lcd using SPI communication
  digitalWrite(LCD_CE, HIGH); // send a high signal to the CS pin on the lcd display
}

void drawSpaceship(long distance) { // Create a function taking a distance in centimeters as a parameter that updates the spaceships 
      // position

  if (obsLevel > 10) { // check if the obstacles level is greater than 10
  
    if (obsFrame == 1) { // check if the obstacles frame is 1
    
      random1 = random(ssRandomChoice); // create a new random number within 0 and 4 to be stored in random1
      
    }
    
    distance = (distance / ssDivisor) - random1; // calculate the distance using the random value and divisor factor
    
  } else {
    
    distance = (distance) / ssDivisor; // calculate the distance using the divisor factor
    
  }
  if (distance <= 1) { // check if the new distance is less than 1
  
    grap[ssIndex] = 0x0A0; // set the spaceships back hexadecimal value for the first position
    grap[ssIndex + 1] = 0x040; // set the spaceships front hexadecimal value for the first position
    ssPosition = 1; // set the spaceships position to correlate with what is displayed on the lcd display
    
  } else if (distance > 1 and distance <= 2) { // check if the new distance is between 1 and 2
  
    grap[ssIndex] = 0x050; // set the spaceships back hexadecimal value for the second position
    grap[ssIndex + 1] = 0x020; // set the spaceships front hexadecimal value for the second position
    ssPosition = 2; // set the spaceships position to correlate with what is displayed on the lcd display
    
  } else if (distance > 2 and distance <= 3) { // check if the new distance is between 2 and 3
  
    grap[ssIndex] = 0x028; // set the spaceships back hexadecimal value for the third position
    grap[ssIndex + 1] = 0x010; // set the spaceships front hexadecimal value for the third position
    ssPosition = 3; // set the spaceships position to correlate with what is displayed on the lcd display
    
  } else if (distance > 3 and distance <= 4) { // check if the new distance is between 3 and 4
  
    grap[ssIndex] = 0x014; // set the spaceships back hexadecimal value for the fourth position
    grap[ssIndex + 1] = 0x08; // set the spaceships front hexadecimal value for the fourth position
    ssPosition = 4; // set the spaceships position to correlate with what is displayed on the lcd display
    
  } else if (distance > 4 and distance <= 5) { // check if the new distance is between 4 and 5
  
    grap[ssIndex] = 0x0A; // set the spaceships back hexadecimal value for the fifth position
    grap[ssIndex + 1] = 0x04; // set the spaceships front hexadecimal value for the fifth position
    ssPosition = 5; // set the spaceships position to correlate with what is displayed on the lcd display
    
  } else { // check if the new distance is over 5
  
    grap[ssIndex] = 0x05; // set the spaceships back hexadecimal value for any other position
    grap[ssIndex + 1] = 0x02; // set the spaceships front hexadecimal value for any other position
    ssPosition = 6; // set the spaceships position to correlate with what is displayed on the lcd display

  }
}

void drawObstacle (int level, int frame) { // create a function taking 2 parameters level and frame to updates obstacles position
  if (level == 1) { // Check if the level is 1
  
    obstacleHex1 = 0x080; // set the first objects hexadecimal for level 1
    obstacleHex2 = 0x01; // set the second objects hexadecimal for level 1
    
  } else if (level == 2) { // Check if the level is 2
  
    obstacleHex1 = 0x0C0; // set the first objects hexadecimal for level 2
    obstacleHex2 = 0x03; // set the second objects hexadecimal for level 2
    
  } else if (level == 3) { // Check if the level is 3
  
    obstacleHex1 = 0x0E0; // set the first objects hexadecimal for level 3
    obstacleHex2 = 0x07; // set the second objects hexadecimal for level 3
    
  } else if (level == 4) { // Check if the level is 4
  
    obstacleHex1 = 0x0F0; // set the first objects hexadecimal for level 4
    obstacleHex2 = 0x0F; // set the second objects hexadecimal for level 4
    
  } else if (level == 5) { // Check if the level is 5
  
    obstacleHex1 = 0x0F8; // set the first objects hexadecimal for level 5
    obstacleHex2 = 0x01F; // set the second objects hexadecimal for level 5
    
  } else if (level == 6) { // Check if the level is 6
  
    obstacleHex1 = 0x081; // set the first objects hexadecimal for level 6
    obstacleHex2 = 0x081; // set the second objects hexadecimal for level 6
    
  } else if (level == 7) { // Check if the level is 7
  
    obstacleHex1 = 0x0C1; // set the first objects hexadecimal for level 7
    obstacleHex2 = 0x083; // set the second objects hexadecimal for level 7
    
  } else if (level == 8) { // Check if the level is 8
  
    obstacleHex1 = 0x0E1; // set the first objects hexadecimal for level 8
    obstacleHex2 = 0x087; // set the second objects hexadecimal for level 8
    
  } else if (level == 9) { // Check if the level is 9
  
    obstacleHex1 = 0x0F1; // set the first objects hexadecimal for level 9
    obstacleHex2 = 0x08F; // set the second objects hexadecimal for level 9
    
  } else if (level == 10) { // Check if the level is 10
  
    obstacleHex1 = 0x0E3; // set the first objects hexadecimal for level 10
    obstacleHex2 = 0x0C7; // set the second objects hexadecimal for level 10
    
  } else { // Check if the level is over 10
  
    // keep level 10's obstacles hexadecimal
    
    if (gameDelay > 0) { // check if the gameDelay is greater than 0
      gameDelay == floor(gameDelay / 2); // set the new gamedelay to make the game faster and harder (halved and floored)
    }
  }

  if (frame == 1) { // check if the first frame is being set
  
    obsRandom = random(obsRandomChoice); // calculate a randomized obstacle variable between 0 and 1
    
    if (obsRandom == 1) { // check if the obstacle randomized value is 1
    
      grap[obsIndex] = obstacleHex1; // set the first obstacles hexadecimal value for the current level
      
    } else { // check if the randomized value is not 1
    
      grap[obsIndex] = obstacleHex2; // set the second obstacles hexadecimal value for the current level
      
    }
    
  } else if (frame < 82) { // check if the frame is not the first but is within the first 82 frames (before the last frame)
  
    grap[obsIndex] = 0x00;  // reset the previous obstacles frame with a blank hexadecimal value
    obsIndex = obsIndex - 1; // set the obstacles index value to the new index value
    
    if (obsRandom == 1) { // check if the obstacle randomized value is 1
    
      grap[obsIndex] = obstacleHex1; // set the first obstacles hexadecimal value for the current level
      
    } else { // check if the obstacle randomized value is a different value than 1
      
      grap[obsIndex] = obstacleHex2; // set the second obstacles hexadecimal value for the current level
      
    }
  } else { // check if the frame is the last frame of the obstacle
    
    grap[obsIndex] = 0x00;  // reset the previous obstacles frame with a blank hexadecimal value
    
  }
}

void checkCollision(int level) { // Create a function taking a level that checks if a collision has occurred for every level

  if (level == 1) { // Check if the level is 1
   // Check which side the obstacle is on
   
    if (obsRandom == 1) { // Check if the obstacle random value is 1
    
      if (ssPosition == 1) { // Check if the spaceship position is where the obstacle is (1)
      
        gameOver = true; // Set the game to be over (gameOver variable to be true)
        
      }
    } else { // Check if the obstacle random value is not 1
    
      if (ssPosition == 6) { // Check if the spaceship position is where the obstacle is (6)
      
        gameOver = true; // Set the game to be over (gameOver variable to be true)
        
      }
    }
  } else if (level == 2) { // Check if the level is 2
  
   // Check which side the obstacle is on
   
    if (obsRandom == 1) { // Check if the obstacle random value is 1
    
      if (ssPosition < 3) { // Check if the spaceship position is where the obstacle is (less than 3)
      
        gameOver = true; // Set the game to be over (gameOver variable to be true)
        
      }
    } else { // Check if the obstacle random value is not 1
    
      if (ssPosition > 4) { // Check if the spaceship position is where the obstacle is (greater than 4)
      
        gameOver = true; // Set the game to be over (gameOver variable to be true)
        
      }
    }
  } else if (level == 3) { // Check if the level is 3
  
   // Check which side the obstacle is on
   
    if (obsRandom == 1) { // Check if the obstacle random value is 1
    
      if (ssPosition < 4) { // Check if the spaceship position is where the obstacle is (less than 4)
      
        gameOver = true; // Set the game to be over (gameOver variable to be true)
        
      }
    } else { // Check if the obstacle random value is not 1
    
      if (ssPosition > 3) { // Check if the spaceship position is where the obstacle is (greater than 3)
      
        gameOver = true; // Set the game to be over (gameOver variable to be true)
        
      }
    }
  } else if (level == 4) { // Check if the level is 4
  
   // Check which side the obstacle is on
   
    if (obsRandom == 1) { // Check if the obstacle random value is 1
    
      if (ssPosition < 5) { // Check if the spaceship position is where the obstacle is (less than 5)
      
        gameOver = true; // Set the game to be over (gameOver variable to be true)
        
      }
    } else { // Check if the obstacle random value is not 1
    
      if (ssPosition > 2) { // Check if the spaceship position is where the obstacle is (greater than 2)
      
        gameOver = true; // Set the game to be over (gameOver variable to be true)
        
      }
    }
  } else if (level == 5) { // Check if the level is 5
  
   // Check which side the obstacle is on
   
    if (obsRandom == 1) { // Check if the obstacle random value is 1
    
      if (ssPosition < 6) { // Check if the spaceship position is where the obstacle is (less than 6)
      
        gameOver = true; // Set the game to be over (gameOver variable to be true)
        
      }
    } else { // Check if the obstacle random value is not 1
    
      if (ssPosition > 1) { // Check if the spaceship position is where the obstacle is (greater than 1)
      
        gameOver = true; // Set the game to be over (gameOver variable to be true)
        
      }
    }
  } else if (level == 6) { // Check if the level is 6
  
   // Check which side the obstacle is on
   
    if (ssPosition == 1 || ssPosition == 6) { // Check if the spaceship position is where the obstacle is (1 or 6)
    
      gameOver = true; // Set the game to be over (gameOver variable to be true)
      
    }
  } else if (level == 7) { // Check if the level is 7
  
   // Check which side the obstacle is on
   
    if (obsRandom == 1) { // Check if the obstacle random value is 1
    
      if (ssPosition < 3 || ssPosition == 6) { // Check if the spaceship position is where the obstacle is (less than 3 or 6)
      
        gameOver = true; // Set the game to be over (gameOver variable to be true)
        
      }
    } else { // Check if the obstacle random value is not 1
    
      if  (ssPosition > 4 || ssPosition == 1) { // Check if the spaceship position is where the obstacle is (greater than 4 or 1)
      
        gameOver = true; // Set the game to be over (gameOver variable to be true)
        
      }
    }
  } else if (level == 8) { // Check if the level is 8
  
   // Check which side the obstacle is on
   
    if (obsRandom == 1) { // Check if the obstacle random value is 1
    
      if (ssPosition < 4 || ssPosition == 6) { // Check if the spaceship position is where the obstacle is (less than 4 or 6)
      
        gameOver = true; // Set the game to be over (gameOver variable to be true)
        
      }
    } else { // Check if the obstacle random value is not 1
    
      if (ssPosition > 3 || ssPosition == 1) { // Check if the spaceship position is where the obstacle is (greater than 3 or 1)
      
        gameOver = true; // Set the game to be over (gameOver variable to be true)
        
      }
    }
  } else if (level == 9) { // Check if the level is 9
  
   // Check which side the obstacle is on
   
    if (obsRandom == 1) { // Check if the obstacle random value is 1
    
      if (ssPosition != 5) { // Check if the spaceship position is where the obstacle is (not 5)
      
        gameOver = true; // Set the game to be over (gameOver variable to be true)
        
      }
    } else { // Check if the obstacle random value is not 1
    
      if (ssPosition != 2) { // Check if the spaceship position is where the obstacle is (not 2)
      
        gameOver = true; // Set the game to be over (gameOver variable to be true)
        
      }
    }
  } else { // Check if the level is greater than 9
  
   // Check which side the obstacle is on
   
    if (obsRandom == 1) { // Check if the obstacle random value is 1
    
      if (ssPosition != 4) { // Check if the spaceship position is where the obstacle is (not 4)
      
        gameOver = true; // Set the game to be over (gameOver variable to be true)
        
      }
    } else { // Check if the obstacle random value is not 1
    
      if (ssPosition != 3) { // Check if the spaceship position is where the obstacle is (not 3)
      
        gameOver = true; // Set the game to be over (gameOver variable to be true)
        
      }
    }
  }
}



void setup()   {

  Serial.begin(9600); // Begin the serial monitor
  LCD_Initialise(); // Call the LCD_Initilaise function to initialize the nokia 5110 lcd display
  // Ultrasonic sensor ping pin and in pins
  pinMode(pingPin, OUTPUT); // Set the pingPin to send out output from the arduino.
  pinMode(inPin, INPUT); // Set the inPin to receive input into the arduino
  randomSeed(analogRead(unconnectedPin)); // Call the randomSeed function to randomize the seed with a changing value

  // Print out text
  Serial.println("Welcome to Space Shoot! \n Enter \"Start\" to start the game!"); // Print out instructions to play the game on the 
// Serial Monitor
}

void loop() {
  
  if (startGame == false) { // Check if the game has been started
  
    if (Serial.available() > 0) { // Check if there is any input in the serial monitor
    
      monitorInput = Serial.readString(); // Set monitorInput to be the serial monitor input in a string
      monitorInput.trim(); // Take out unnecessary spaces from monitorInput
      monitorInput.toUpperCase(); // Capitalize all the letters in the monitorInput string
      
      if (monitorInput == "START") { // Check if monitorInput is "START"
      
        startGame = true; // Set the startGame variable to true to stop checking the serial monitor
      }
    }
    
  } else { // Check if the game has started

    if (gameOver == false) { // Check if the game has not finished
      // Ultrasonic sensor code

      // Make sure to start that there is no pulse/signal sent from the pingPin

      digitalWrite(pingPin, LOW); // Send out a LOW signal through the pingPin
      delayMicroseconds(2); // Delay the program for a set amount of microseconds

      // Send out a high pulse/signal through the pingPing to send a ultrasonic burst

      digitalWrite(pingPin, HIGH); // Send out a HIGH signal through the pingPin
      delayMicroseconds(10); // Delay the program for a set amount of microseconds

      // Stop sending out the high pulse/signal through the pingPin

      digitalWrite(pingPin, LOW); // Send out a LOW signal through pingPin

      objectDuration = pulseIn(inPin, HIGH); // Receive a signal from the inPin and store it in objectDuration

      // Convert the signal received into inches and centimeters

      objectCm = (objectDuration / 29 / 2); // Convert the objectDuration input into a value in centimeters

      drawSpaceship(objectCm); // Call the drawSpaceship function to update the frame and position of the spaceship

      drawObstacle(obsLevel, obsFrame); // Call the drawObstacle function to update the frame and position of the obstacle
      
      for (index = 0; index < (84 * 48) / 8; index++) { // Loop for the number of pixels on the lcd display
      
        LCD_Write(LCD_D, grap[index]); // Call the LCD_Write function to put a pixel onto the lcd display
      }
      
      obsFrame++; // Set the obstacles frame to increase by 1
      
      if (obsFrame == 82) { // Check if the obstacle frame is at the final frame (82)
      
        checkCollision(obsLevel); // Call the checkCollision function to check if the user has collided with the obstacle
        grap[obsIndex] = 0x00; // Set the last frame of the obstacle to a blank hexadecimal value
        obsLevel++; // Set the obstacles level to increase by 1
        obsFrame = 1; // Set the obstacle frame back to the starting frame
        obsIndex = 278; // Set the obstacle index back to the starting value of the level
        
        if (gameOver == false) { // Check if the game has not ended
        
          Serial.println("You have now entered level " + String(obsLevel) + "."); // Print out the new level the player has entered on 
       // the serial monitor
        }
      }
      
      delay(gameDelay); // Delay the program for gameDelay milliseconds
      
    } else { // Check if the game has finished
    
      if (loseMessage == false) { // Check if the lose message has yet to be printed
      
        Serial.println("Game Over"); // Print on the serial monitor that the game is over
        Serial.println("Your score is " + String(obsLevel - 1) + "!"); // Print on the serial monitor the users final score
        loseMessage = true; // Set the lose message to already be printed to not repeat it
        
      }
    }
  }


}
