#include <Keypad.h>
#include <Joystick.h>

#define ENABLE_PULLUPS
#define NUMROTARIES 0
#define NUMBUTTONS 4
#define NUMROWS 2
#define NUMCOLS 2




byte buttons[NUMROWS][NUMCOLS] = {
  {0,1},
  {2,3}
};

bool reverse_matrix[NUMCOLS*NUMROWS] = 
  {1,1,
  1,1};

byte reverse_buttons[NUMCOLS*NUMROWS] = 
  {4,5,
  6,7};

#define DIR_CCW 0x10
#define DIR_CW 0x20
#define R_START 0x0

byte rowPins[NUMROWS] = {A0,A1}; 
byte colPins[NUMCOLS] = {13,12}; 

Keypad buttbx = Keypad( makeKeymap(buttons), rowPins, colPins, NUMROWS, NUMCOLS); 

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
  JOYSTICK_TYPE_JOYSTICK, 8, 0,
  false, false, false, false, false, false,
  false, false, false, false, false);

void setup() {
  Serial.begin(9600);
  Joystick.begin();
  CheckAllButtonsInit();
  }

void loop() { 
  CheckAllButtons();
  
}

void CheckAllButtonsInit(void) {
  // set all on inactive first
  for (int i=0; i<sizeof(reverse_buttons); i++) {
    Joystick.setButton(reverse_buttons[i], 1);
  }
}

void CheckAllButtons(void) {
      if (buttbx.getKeys())
    {
       for (int i=0; i<LIST_MAX; i++)   
        {
           if ( buttbx.key[i].stateChanged )   
            {
            switch (buttbx.key[i].kstate) {  
                    case PRESSED:
                      // Serial.print(reverse_matrix[buttbx.key[i].kchar]);
                    case HOLD:
                      if(reverse_matrix[buttbx.key[i].kchar]){
                        Joystick.setButton(reverse_buttons[buttbx.key[i].kchar], 0);
                      }
                      Joystick.setButton(buttbx.key[i].kchar, 1);
                      break;
                    case RELEASED:
                    case IDLE:
                      if(reverse_matrix[buttbx.key[i].kchar]){
                        Joystick.setButton(reverse_buttons[buttbx.key[i].kchar], 1);
                      }
                      Joystick.setButton(buttbx.key[i].kchar, 0);
                      break;
            }
           }   
         }
     }
}





