/*
* Two phase traffic signal simulation on 8 x 8 Neopixel Matrix
* FSM Based Control
* Author: Vishweswar Eswaran
*/

#include <Adafruit_NeoPixel.h>
#define pixelPin     8
#define pixelCount   64

int AL_pixel = 3; 
int AL_pixel_side = 4; 

int AR_pixel = 59;
int AR_pixel_side = 60; 

int BL_pixel = 24;
int BL_pixel_side = 32;

int BR_pixel = 31;
int BR_pixel_side = 39;

Adafruit_NeoPixel pixel(pixelCount, pixelPin, NEO_GRB + NEO_KHZ800);


int count = 0;
int counter_max = 100;
int Y_threshold = 15; //green till yellow ~ value * 100 milliseconds
int R_threshold = 10; //yellow till all red ~ value * 100 milliseconds
int SHIFT_threshold = 5; //all red till transition ~ value * 100 milliseconds

enum traffic_light_color {GREEN, YELLOW, RED};
enum traffic_light_ID {AL, AR, BL, BR};

typedef struct traffic_light_model
{
  traffic_light_color my_color;
  traffic_light_ID my_ID;

} traffic_light;

traffic_light A_L; //ID = AL
traffic_light A_R; //ID = AR
traffic_light B_L; //ID = BL
traffic_light B_R; //ID = BR

enum control_state {START, TRANSITION_Y, ALL_R, SHIFTED};
control_state C1;

typedef struct state {
  traffic_light* A_L_ptr;
  traffic_light* A_R_ptr;
  traffic_light* B_L_ptr;
  traffic_light* B_R_ptr;

  traffic_light* last_green_before_all_red;

} signal_state;



void state_init(signal_state * intersection)
{
  intersection->A_L_ptr = &A_L;
  intersection->A_R_ptr = &A_R;
  intersection->B_L_ptr = &B_L;
  intersection->B_R_ptr = &B_R;

  intersection->A_L_ptr->my_color = GREEN;
  intersection->A_L_ptr->my_ID = AL;

  intersection->A_R_ptr->my_color = GREEN;
  intersection->A_R_ptr->my_ID = AR;

  intersection->B_L_ptr->my_color = RED;
  intersection->B_L_ptr->my_ID = BL;

  intersection->B_R_ptr->my_color = RED;
  intersection->B_R_ptr->my_ID = BR;

  intersection->last_green_before_all_red = &A_L;
}

void set_traffic_light_color(traffic_light * T, signal_state * intersection)
{
  switch (T->my_color)
  {
    case GREEN:
      set_green(T, intersection);
      break;
    case YELLOW:
      set_yellow(T);
      break;
    case RED:
      set_red(T);
      break;
    default:
      break;
  }
}

void execute_state(signal_state * intersection)
{
  set_traffic_light_color(intersection->A_L_ptr, intersection);
  set_traffic_light_color(intersection->A_R_ptr, intersection);
  set_traffic_light_color(intersection->B_L_ptr, intersection);
  set_traffic_light_color(intersection->B_R_ptr, intersection);
}


void set_green(traffic_light * T, signal_state * intersection)
{
  if (T->my_ID == AL)
  {
    /* Machine dependent function with I/Os */
    pixel.setPixelColor(AL_pixel, pixel.Color(0, 25, 0));
    pixel.setPixelColor(AL_pixel_side, pixel.Color(0, 25, 0));
     
    intersection->last_green_before_all_red = &A_L;
  }
  else if (T->my_ID == AR)
  {
    /* Machine dependent function with I/Os */
    pixel.setPixelColor(AR_pixel, pixel.Color(0, 25, 0));
    pixel.setPixelColor(AR_pixel_side, pixel.Color(0, 25, 0));


    intersection->last_green_before_all_red = &A_R;
  }
  else if (T->my_ID == BL)
  {
    /* Machine dependent function with I/Os */
    pixel.setPixelColor(BL_pixel, pixel.Color(0, 25, 0));
    pixel.setPixelColor(BL_pixel_side, pixel.Color(0, 25, 0));

    intersection->last_green_before_all_red = &B_L;
  }
  else if (T->my_ID == BR)
  {
    /* Machine dependent function with I/Os */
    pixel.setPixelColor(BR_pixel, pixel.Color(0, 25, 0));
    pixel.setPixelColor(BR_pixel_side, pixel.Color(0, 25, 0));

    intersection->last_green_before_all_red = &B_R;
  }


}

void set_yellow(traffic_light * T)
{

  if (T->my_ID == AL)
  {
    /* Machine dependent function with I/Os */
    pixel.setPixelColor(AL_pixel, pixel.Color(25, 25, 0));
    pixel.setPixelColor(AL_pixel_side, pixel.Color(25, 25, 0));

  }
  else if (T->my_ID == AR)
  {
    /* Machine dependent function with I/Os */
    pixel.setPixelColor(AR_pixel, pixel.Color(25, 25, 0));
    pixel.setPixelColor(AR_pixel_side, pixel.Color(25, 25, 0));

  }
  else if (T->my_ID == BL)
  {
    /* Machine dependent function with I/Os */
    pixel.setPixelColor(BL_pixel, pixel.Color(25, 25, 0));
    pixel.setPixelColor(BL_pixel_side, pixel.Color(25, 25, 0));

  }
  else if (T->my_ID == BR)
  {
    /* Machine dependent function with I/Os */
    pixel.setPixelColor(BR_pixel, pixel.Color(25, 25, 0));
    pixel.setPixelColor(BR_pixel_side, pixel.Color(25, 25, 0));

  }

}

void set_red(traffic_light * T)
{

  if (T->my_ID == AL)
  {
    /* Machine dependent function with I/Os */
    pixel.setPixelColor(AL_pixel, pixel.Color(25, 0, 0));
    pixel.setPixelColor(AL_pixel_side, pixel.Color(25, 0, 0));
  }
  else if (T->my_ID == AR)
  {
    /* Machine dependent function with I/Os */
    pixel.setPixelColor(AR_pixel, pixel.Color(25, 0, 0));
    pixel.setPixelColor(AR_pixel_side, pixel.Color(25, 0, 0));

  }
  else if (T->my_ID == BL)
  {
    /* Machine dependent function with I/Os */
    pixel.setPixelColor(BL_pixel, pixel.Color(25, 0, 0));
    pixel.setPixelColor(BL_pixel_side, pixel.Color(25, 0, 0));

  }
  else if (T->my_ID == BR)
  {
    /* Machine dependent function with I/Os */
    pixel.setPixelColor(BR_pixel, pixel.Color(25, 0, 0));
    pixel.setPixelColor(BR_pixel_side, pixel.Color(25, 0, 0));

  }

}

void transition_shift(signal_state * intersection)
{
  switch (intersection->last_green_before_all_red->my_ID)
  {
    case AL:
      intersection->A_L_ptr->my_color = RED;
      intersection->A_R_ptr->my_color = RED;
      intersection->B_L_ptr->my_color = GREEN;
      intersection->B_R_ptr->my_color = GREEN;
      break;
    case AR:
      intersection->A_L_ptr->my_color = RED;
      intersection->A_R_ptr->my_color = RED;
      intersection->B_L_ptr->my_color = GREEN;
      intersection->B_R_ptr->my_color = GREEN;
      break;
    case BL:
      intersection->A_L_ptr->my_color = GREEN;
      intersection->A_R_ptr->my_color = GREEN;
      intersection->B_L_ptr->my_color = RED;
      intersection->B_R_ptr->my_color = RED;
      break;
    case BR:
      intersection->A_L_ptr->my_color = GREEN;
      intersection->A_R_ptr->my_color = GREEN;
      intersection->B_L_ptr->my_color = RED;
      intersection->B_R_ptr->my_color = RED;
      break;
    default:
      intersection->A_L_ptr->my_color = GREEN;
      intersection->A_R_ptr->my_color = GREEN;
      intersection->B_L_ptr->my_color = RED;
      intersection->B_R_ptr->my_color = RED;
      break;

  }
}

void  transition_R(signal_state * intersection)
{
  intersection->A_L_ptr->my_color = RED;
  intersection->A_R_ptr->my_color = RED;
  intersection->B_L_ptr->my_color = RED;
  intersection->B_R_ptr->my_color = RED;
}

void  transition_Y(signal_state * intersection)
{
  switch (intersection->last_green_before_all_red->my_ID)
  {
    case AL:
      intersection->A_L_ptr->my_color = YELLOW;
      intersection->A_R_ptr->my_color = YELLOW;
      intersection->B_L_ptr->my_color = RED;
      intersection->B_R_ptr->my_color = RED;
      break;
    case AR:
      intersection->A_L_ptr->my_color = YELLOW;
      intersection->A_R_ptr->my_color = YELLOW;
      intersection->B_L_ptr->my_color = RED;
      intersection->B_R_ptr->my_color = RED;
      break;
    case BL:
      intersection->A_L_ptr->my_color = RED;
      intersection->A_R_ptr->my_color = RED;
      intersection->B_L_ptr->my_color = YELLOW;
      intersection->B_R_ptr->my_color = YELLOW;
      break;
    case BR:
      intersection->A_L_ptr->my_color = RED;
      intersection->A_R_ptr->my_color = RED;
      intersection->B_L_ptr->my_color = YELLOW;
      intersection->B_R_ptr->my_color = YELLOW;
      break;
    default:
      intersection->A_L_ptr->my_color = YELLOW;
      intersection->A_R_ptr->my_color = YELLOW;
      intersection->B_L_ptr->my_color = RED;
      intersection->B_R_ptr->my_color = RED;
      break;

  }
}


void countUp()
{
  delay(100);
  count++;
  if (count == counter_max)
    count = 0;
}

int roadAL[8] = {2, 13, 18, 29, 34, 45, 50, 61}; 
int roadAL_side[8] = {1, 14, 17, 30, 33, 46, 49, 62}; 

int roadAR[8] = {5, 10, 21, 26, 37, 42, 53, 58}; 
int roadAR_side[8] = {6, 9, 22, 25, 38, 41, 54, 57}; 


int roadBR[8] = {40, 41, 42, 43, 44, 45, 46, 47}; 
int roadBR_side[8] = {55, 54, 53, 52, 51, 50, 49, 48}; 

int roadBL[8] = {15, 14, 13, 12, 11, 10, 9, 8}; 
int roadBL_side[8] = {16, 17, 18, 19, 20, 21, 22, 23}; 

void driveB(int delayTime)
{
  for(int i = 0; i <= 7; i++)
  {
    pixel.setPixelColor(roadBR[i], pixel.Color(0, 25, 50));
    pixel.setPixelColor(roadBR_side[i], pixel.Color(50, 0, 25));
    
    pixel.setPixelColor(roadBL[i], pixel.Color(0, 25, 50));
    pixel.setPixelColor(roadBL_side[i], pixel.Color(50, 0, 25));
    pixel.show(); 
    delay(delayTime);
    pixel.setPixelColor(roadBR[i], pixel.Color(0, 0, 0));
    pixel.setPixelColor(roadBR_side[i], pixel.Color(0, 0, 0));
    
    pixel.setPixelColor(roadBL[i], pixel.Color(0, 0, 0));
    pixel.setPixelColor(roadBL_side[i], pixel.Color(0, 0, 0));  
    pixel.show(); 
  }
  
}


void driveA(int delayTime)
{
  for(int i = 0, j = 7; i <= 7; i++, j--)
  {
    pixel.setPixelColor(roadAL[j], pixel.Color(0, 25, 50));
    pixel.setPixelColor(roadAL_side[j], pixel.Color(50, 0, 25));
    
    pixel.setPixelColor(roadAR[i], pixel.Color(0, 25, 50));
    pixel.setPixelColor(roadAR_side[i], pixel.Color(50, 0, 25));
    pixel.show(); 
    delay(delayTime);
    pixel.setPixelColor(roadAL[j], pixel.Color(0, 0, 0));
    pixel.setPixelColor(roadAL_side[j], pixel.Color(0, 0, 0));
    pixel.setPixelColor(roadAR[i], pixel.Color(0, 0, 0));
    pixel.setPixelColor(roadAR_side[i], pixel.Color(0, 0, 0));    
    pixel.show(); 
  }
  
}

void control_logic(bool reset, signal_state * intersection)
{

  countUp(); //increment the counter

  switch (C1) {

    case (START):

      state_init(intersection);
      
      if(intersection->last_green_before_all_red->my_ID == AL || intersection->last_green_before_all_red->my_ID == AR)
        driveA(100); 
      else if(intersection->last_green_before_all_red->my_ID == BL || intersection->last_green_before_all_red->my_ID == BR)
        driveB(100); 

      if (reset)
        C1 =  START;
      else if (count >= Y_threshold) {
        C1 = TRANSITION_Y;
        transition_Y(intersection);
        count = 0; //reset the counter
      }
      else
        C1 = START;
      break;

    case (TRANSITION_Y):

      execute_state(intersection); //executes state
      
      if(intersection->last_green_before_all_red->my_ID == AL || intersection->last_green_before_all_red->my_ID == AR)
        driveA(50); 
      else if(intersection->last_green_before_all_red->my_ID == BL || intersection->last_green_before_all_red->my_ID == BR)
        driveB(50); 
        
      if (reset)
        C1 =  START;
      else if (count >= R_threshold) {
        C1 = ALL_R;
        transition_R(intersection);
        count = 0; //reset the counter
      }
      else
        C1 = TRANSITION_Y;
      break;

    case (ALL_R):
      execute_state(intersection);

      if (reset)
        C1 =  START;
      else if (count >= SHIFT_threshold) {
        C1 = SHIFTED;
        transition_shift(intersection);
        count = 0; //reset the counter
      }
      else
        C1 = ALL_R;
      break;

    case (SHIFTED):

      execute_state(intersection);

       if(intersection->last_green_before_all_red->my_ID == AL || intersection->last_green_before_all_red->my_ID == AR)
        driveA(100); 
      else if(intersection->last_green_before_all_red->my_ID == BL || intersection->last_green_before_all_red->my_ID == BR)
        driveB(100); 
      
      if (reset)
        C1 =  START;
      else if (count >= Y_threshold) {
        C1 = TRANSITION_Y;
        transition_Y(intersection);
        count = 0; //reset the counter
      }
      else
        C1 = SHIFTED;
      break;

  }
}


signal_state uoft_intersection; //the intersection name

void setup() {

  count = 0;
  control_state C1 = START;

  pixel.begin();
  pixel.clear();
 state_init(&uoft_intersection);
 execute_state(&uoft_intersection);
  pixel.show();
}

void loop() {

  control_logic(false, &uoft_intersection);
  pixel.show();
}
