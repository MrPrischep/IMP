// IMP project
// Simulátor hudebního nástroje
// Author: Kozhevnikov Dmitrii
// Login: xkozhe00

const int TONE_OUTPUT_PIN = 14;
const int TONE_PWM_CHANNEL = 0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(Serial.available()) {
    String melody = Serial.readStringUntil('\n'); // read string from command line
    if (melody == "-help") {
      // print help for user
      Serial.println("Input your melody in format: 'note delay note delay ...'");
      Serial.println("For delay: 1 = 100, 2 = 200, 3 = 300, 4 = 400, 5 = 500, 6 = 600, 7 = 700, 8 = 800, 9 = 900, 0 = 1000");
      Serial.println("For notes: A = A, B = B, b = Bb, C = C, c = Cs, D = D, E = E, e = Eb, F = F, f = Fs, G = G, g = Gs");
    } else {
      // main cycle
      ledcAttachPin(TONE_OUTPUT_PIN, TONE_PWM_CHANNEL);
      if (melody == "1") {
        Serial.println("Play default melody");
        melody = "A5E5A5E5A5g5g9g5E5g5E5g5A5A9A5E5A5E5A5g5g9g5E5g5E5g5A9";
      } else {
        Serial.println("Input melody is:");
        melody.replace(" ", "");  // delete white spaces
        Serial.println(melody);
      }
      
      int len = melody.length();  // melody len
      char notes[len/2];  // array for reading notes
      char times[len/2];  // array for reading time
      int delays[len/2];  // delays
      note_t play[len/2]; // notes
      int errorStatus = 0;
      // reading command line and sort
      for (int i = 0; i < len; i++) {
        if(i % 2 == 0) {
          notes[i / 2] = melody[i]; 
        } else {
          times[i / 2] = melody[i];
        }
      }

      // check notes and delays cycle
      for (int i = 0; i < len/2; i++) {
        // notes
        if (notes[i] == 'A') {
          play[i]= NOTE_A;
        } else if (notes[i] == 'B') {
          play[i] = NOTE_B;
        } else if (notes[i] == 'b') {
          play[i] = NOTE_Bb;
        } else if (notes[i] == 'C') {
          play[i] = NOTE_C;
        } else if (notes[i] == 'c') {
          play[i] = NOTE_Cs;
        } else if (notes[i] == 'D') {
          play[i] = NOTE_D;
        } else if (notes[i] == 'E') {
          play[i] = NOTE_E;
        } else if (notes[i] == 'e') {
          play[i] = NOTE_Eb;
        } else if (notes[i] == 'F') {
          play[i] = NOTE_F;
        } else if (notes[i] == 'f') {
          play[i] = NOTE_Fs;
        } else if (notes[i] == 'G') {
          play[i] = NOTE_G;
        } else if (notes[i] == 'g') {
          play[i] = NOTE_Gs;
        } else {
          errorStatus = i + 1;
        }
        // delays
        if (times[i] == '1') {
          delays[i] = 100;
        } else if (times[i] == '2') {
          delays[i] = 200;
        } else if (times[i] == '3') {
          delays[i] = 300;
        } else if (times[i] == '4') {
          delays[i] = 400;
        } else if (times[i] == '5') {
          delays[i] = 500;
        } else if (times[i] == '6') {
          delays[i] = 600;
        } else if (times[i] == '7') {
          delays[i] = 700;
        } else if (times[i] == '8') {
          delays[i] = 800;
        } else if (times[i] == '9') {
          delays[i] = 900;
        } else if (times[i] == '0') {
          delays[i] = 1000;
        } else {
          errorStatus = i + 1;
        }
      }

      if (errorStatus == 0) {
        // play melody
        for (int i = 0; i < len/2; i++) {
          ledcWriteNote(TONE_PWM_CHANNEL, play[i], 4);
          delay(delays[i]);
        }
      } else {
        Serial.println("Error in position:");
        Serial.println(errorStatus);
        Serial.println("For help write '-help'");
      }
      ledcDetachPin(TONE_OUTPUT_PIN); 
    }  
  }  
}
