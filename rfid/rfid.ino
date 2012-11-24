// define constants for pins
int SUCCESS = 10;
int ERROR = 13;

// variables to keep state
int readVal = 0; // individual character read from serial
unsigned int readData[10]; // data read from serial
int counter = -1; // counter to keep position in the buffer
char tagId[11]; // final tag ID converted to a string

char* authorizedTags[4]; // array to hold the list of authorized tags

// fills the list of authorzied tags
void initAuthorizedTags() {
	// add your own tag IDs here
  authorizedTags[0] = "0400680B85"; 
  authorizedTags[1] = "0400063EB9"; 
  authorizedTags[2] = "040004F3F5"; 
  authorizedTags[3] = "04006813AB"; 
}

void setup() {                
  Serial.begin(9600);
  pinMode(SUCCESS, OUTPUT);
  pinMode(ERROR, OUTPUT);
  initAuthorizedTags();
}

// check if the tag ID we just read is any of the authorized tags
int checkTag() {
  int i;
  
  for (i = 0; i < 4; ++i) {
    if (strcmp(authorizedTags[i], tagId) == 0) {
      return 1;
    }
  }
  return 0;
}

// convert the int values read from serial to ASCII chars
void parseTag() {
  int i;
  for (i = 0; i < 10; ++i) {
    tagId[i] = readData[i];
  }
  tagId[10] = 0;
}

// once a whole tag is read, process it
void processTag() {
	// convert id to a string
  parseTag();
	
	// print it
  printTag();
	
	// check if the tag is authorized
  if (checkTag() == 1) {
    tagSuccess(); // if so, perform an action (blink a led, open a door, etc...)
  } else {
    tagFailed(); // otherwise, inform user of failure
  }
}

void printTag() {
  Serial.print("Tag value: ");
  Serial.println(tagId);
}

// perform an action when an authorized tag was read
void tagSuccess() {
  Serial.println("Tag authorized.");
	
	// here, we simply turn on the success LED for 2s
  digitalWrite(SUCCESS, HIGH);
  digitalWrite(ERROR, LOW);
  delay(2000);
}

// inform the user that the tag is not authorized
void tagFailed() {
  Serial.println("Unauthorized access!");
	
  digitalWrite(SUCCESS, LOW);
  digitalWrite(ERROR, HIGH);
  delay(2000);
}

// this function clears the rest of data on the serial, to prevent multiple scans
void clearSerial() {
  while (Serial.read() >= 0) {
		; // do nothing
	}
}

void loop() {
	// turn LEDs off
  digitalWrite(SUCCESS, LOW);
  digitalWrite(ERROR, LOW);

	if (Serial.available() > 0) {
		// read the incoming byte:
		readVal = Serial.read();
		
		// a "2" signals the beginning of a tag
		if (readVal == 2) {
			counter = 0; // start reading
		} 
		// a "3" signals the end of a tag
		else if (readVal == 3) {
			// process the tag we just read
			processTag();
			
			// clear serial to prevent multiple reads
			clearSerial();
			
			// reset reading state
			counter = -1;
		}
		// if we are in the middle of reading a tag
		else if (counter >= 0) {
			// save valuee
			readData[counter] = readVal;
			
			// increment counter
			++counter;
		} 
	}
}
