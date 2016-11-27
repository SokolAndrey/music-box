/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO 
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN takes care 
  of use the correct LED pin whatever is the board used.
  If you want to know what pin the on-board LED is connected to on your Arduino model, check
  the Technical Specs of your board  at https://www.arduino.cc/en/Main/Products
  
  This example code is in the public domain.

  modified 8 May 2014
  by Scott Fitzgerald
  
  modified 2 Sep 2016
  by Arturo Guadalupi
*/
// Notes
#define  c     3830    // 261 Hz 
#define  d     3400    // 294 Hz 
#define  e     3038    // 329 Hz 
#define  f     2864    // 349 Hz
#define fSharp 2702    // 369.99 Hz 
#define  g     2550    // 392 Hz 
#define  a     2272    // 440 Hz 
#define  b     2028    // 493 Hz 
#define  C     1912    // 523 Hz
#define CSharp 1798    // 556 Hz
#define  D     1703    // 587.32 Hz
#define FSharp 1351    // 739 Hz
// no sound
#define  R     0
#define THE_END -1

// Length 
#define l4 16
#define l3 24
#define l2 32
#define l1 64
#define l8 8
#define l16 4

int speakerOut = 2;

void setup() { 
  pinMode(speakerOut, OUTPUT);
}

// melodies
/* Jingle Bells
 * int melody[] = {e,e,e,   e,e,e,    e,g,c,d,      e,    f,f,f,f,      f,e,e,e,e,        e,d,d,e,       d,g,    e,e,e,    e,e,e,     e,g,c,d,      e,  f,f,f,f,     f,e,e,e,e,      g,g,f,d,     c,  R, R};
 * int beats[]  = {l4,l4,l2, l4,l4,l2, l4,l4,l3,l8, l1,   l4,l4,l3,l8,  l4,l4,l4,l8,l8,   l4,l4,l4,l4,   l2,l2,  l4,l4,l2, l4,l4,l2,  l4,l4,l3,l8,  l1, l4,l4,l4,l4, l4,l4,l4,l8,l8, l4,l4,l4,l4, l1, l1,l1};
*/

/* We wish you a MC
 * int melody[] = {d,   g,g,a,g,fSharp,     e,c,e,     a,a,b,a,g,        fSharp,d,fSharp,   b,b,C,b,a,        g,e,d,d,      e,a,fSharp,   g,b,     g,g,g,     fSharp,fSharp,   g,fSharp,e,     d,a,     b,a,a,g,g,      D,d,d,d,     e,a,fSharp,   g,  R, R};
 * int beats[]  = {l4,  l4, l8,l8,l8,l8,    l4,l4,l4,  l4,l8,l8,l8,l8,   l4,l4,l4,          l4,l8,l8,l8,l8,   l4,l4,l8,l8,  l4,l4,l4,     l2,l4,   l4,l4,l4,  l4,l2,           l4,l4,l4,       l2,l4,   l4,l8,l8,l8,l8, l4,l4,l8,l8, l4,l4,l4,     l2, l1,l1};
 */

// MELODY and TIMING  =======================================
//  melody[] is an array of notes, accompanied by beats[], 
//  which sets each note's relative length (higher #, longer note) 
int MCmelody[] = {d,   g,g,a,g,fSharp,     e,c,e,     a,a,b,a,g,        fSharp,d,fSharp,   b,b,C,b,a,        g,e,d,d,      e,a,fSharp,   g,b,     g,g,g,     fSharp,fSharp,   g,fSharp,e,     d,a,     b,a,a,g,g,      D,d,d,d,     e,a,fSharp,   g,  R, R, THE_END};
int MCbeats[]  = {l4,  l4, l8,l8,l8,l8,    l4,l4,l4,  l4,l8,l8,l8,l8,   l4,l4,l4,          l4,l8,l8,l8,l8,   l4,l4,l8,l8,  l4,l4,l4,     l2,l4,   l4,l4,l4,  l4,l2,           l4,l4,l4,       l2,l4,   l4,l8,l8,l8,l8, l4,l4,l8,l8, l4,l4,l4,     l2, l1,l1};
int MCMAX_COUNT = sizeof(MCmelody) / 2; // Melody length, for looping.

int JBmelody[] = {e,e,e,   e,e,e,    e,g,c,d,      e,    f,f,f,f,      f,e,e,e,e,        e,d,d,e,       d,g,    e,e,e,    e,e,e,     e,g,c,d,      e,  f,f,f,f,     f,e,e,e,e,      g,g,f,d,     c,  R, R, THE_END};
int JBbeats[]  = {l4,l4,l2, l4,l4,l2, l4,l4,l3,l8, l1,   l4,l4,l3,l8,  l4,l4,l4,l8,l8,   l4,l4,l4,l4,   l2,l2,  l4,l4,l2, l4,l4,l2,  l4,l4,l3,l8,  l1, l4,l4,l4,l4, l4,l4,l4,l8,l8, l4,l4,l4,l4, l1, l1,l1};
int JBMAX_COUNT = sizeof(JBmelody) / 2; // Melody length, for looping.

int* mels[] = {MCmelody, JBmelody};
int* bs[] = {MCbeats, JBbeats};

// Set overall tempo
long MCtempo = 25000;
long JBtempo = 15000;

long temps[] = {MCtempo, JBtempo};

// Set length of pause between notes
int pause = 1000;
// Loop variable to increase Rest length
int rest_count = 100; //<-BLETCHEROUS HACK; See NOTES

// Initialize core variables
int tone_ = 0;
int beat = 0;
long duration  = 0;

// PLAY TONE  ==============================================
// Pulse the speaker to play a tone for a particular duration
void playTone() {
  long elapsed_time = 0;
  if (tone_ > 0) { // if this isn't a Rest beat, while the tone has 
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {

      digitalWrite(speakerOut,HIGH);
      delayMicroseconds(tone_ / 2);

      // DOWN
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(tone_ / 2);

      // Keep track of how long we pulsed
      elapsed_time += (tone_);
    } 
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);  
    }                                
  }                                 
}


void loop() {
for(int i = 0; i < 2; i++){
  int* mel = mels[i];
  int* beats = bs[i];
  long tempo = temps[i];
  int len = getLength(mel);
  for(int i = 0; i < len; i++){
    tone_ = mel[i];
    beat = beats[i];

    duration = beat * tempo; // Set up timing

    playTone(); 
    // A pause between notes...
    delayMicroseconds(pause);
  }
}

}




int getLength(int* arr){
  int i = 0;
  while(arr[i++] != THE_END);
  return i-1;
}

/*
 * NOTES
 * The program purports to hold a tone for 'duration' microseconds.
 *  Lies lies lies! It holds for at least 'duration' microseconds, _plus_
 *  any overhead created by incremeting elapsed_time (could be in excess of 
 *  3K microseconds) _plus_ overhead of looping and two digitalWrites()
 *  
 * As a result, a tone of 'duration' plays much more slowly than a rest
 *  of 'duration.' rest_count creates a loop variable to bring 'rest' beats 
 *  in line with 'tone' beats of the same length. 
 * 
 * rest_count will be affected by chip architecture and speed, as well as 
 *  overhead from any program mods. Past behavior is no guarantee of future 
 *  performance. Your mileage may vary. Light fuse and get away.
 *  
 * This could use a number of enhancements:
 * ADD code to let the programmer specify how many times the melody should
 *     loop before stopping
 * ADD another octave
 * MOVE tempo, pause, and rest_count to #define statements
 * RE-WRITE to include volume, using analogWrite, as with the second program at
 *          http://www.arduino.cc/en/Tutorial/PlayMelody
 * ADD code to make the tempo settable by pot or other input device
 * ADD code to take tempo or volume settable by serial communication 
 *          (Requires 0005 or higher.)
 * ADD code to create a tone offset (higer or lower) through pot etc
 * REPLACE random melody with opening bars to 'Smoke on the Water'
 */
