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

// The port for connection
int speakerOut = 2;

// Set the pins
void setup() { 
  pinMode(speakerOut, OUTPUT);
}
/*
 * The melody should be initialize as follows:
 * The first array of integers should contain the notes(see definition above).
 * The second one should contain the length of the appropriate note.
 * The array of notes MUST end with THE_END symbol.
 */
int MCmelody[] = {d,   g,g,a,g,fSharp,     e,c,e,     a,a,b,a,g,        fSharp,d,fSharp,   b,b,C,b,a,        g,e,d,d,      e,a,fSharp,   g,b,     g,g,g,     fSharp,fSharp,   g,fSharp,e,     d,a,     b,a,a,g,g,      D,d,d,d,     e,a,fSharp,   g,  R, R, THE_END};
int MCbeats[]  = {l4,  l4, l8,l8,l8,l8,    l4,l4,l4,  l4,l8,l8,l8,l8,   l4,l4,l4,          l4,l8,l8,l8,l8,   l4,l4,l8,l8,  l4,l4,l4,     l2,l4,   l4,l4,l4,  l4,l2,           l4,l4,l4,       l2,l4,   l4,l8,l8,l8,l8, l4,l4,l8,l8, l4,l4,l4,     l2, l1,l1};

int JBmelody[] = {e,e,e,   e,e,e,    e,g,c,d,      e,    f,f,f,f,      f,e,e,e,e,        e,d,d,e,       d,g,    e,e,e,    e,e,e,     e,g,c,d,      e,  f,f,f,f,     f,e,e,e,e,      g,g,f,d,     c,  R, R, THE_END};
int JBbeats[]  = {l4,l4,l2, l4,l4,l2, l4,l4,l3,l8, l1,   l4,l4,l3,l8,  l4,l4,l4,l8,l8,   l4,l4,l4,l4,   l2,l2,  l4,l4,l2, l4,l4,l2,  l4,l4,l3,l8,  l1, l4,l4,l4,l4, l4,l4,l4,l8,l8, l4,l4,l4,l4, l1, l1,l1};

int* mels[] = {MCmelody, JBmelody};
int* bs[] = {MCbeats, JBbeats};

// The tempo for melodies
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
