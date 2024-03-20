/*

*/

enum traffic_light{GREEN, YELLOW, RED}; 

traffic_light A_L; 
traffic_light A_R; 
traffic_light B_L; 
traffic_light B_R;

enum control_state {START, TRANSITION_Y, ALL_R, SHIFTED}; 
control_state C1; 

typedef struct state { 
  traffic_light *A_L; 
  traffic_light *A_R; 
  traffic_light *B_L; 
  traffic_light *B_R;
  
  traffic_light *last_green_before_all_red; 
  
} signal_state; 

void state_init(State * intersection)
{
  *(intersection->A_L) = GREEN; 
  *(intersection->A_R) = RED; 
  *(intersection->B_L) = RED;
  *(intersection->B_R) = RED; 
  
  last_green_before_all_red = A_L; 
  
  
}

void execute_state(signal_state * intersection)
{
  
 for(traffic_light T = A_L; T <= B_R; T++)
 {
     switch(*(intersection->T))
     {
       case GREEN:
       set_green(T); 
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
  
}

void set_green(traffic_light T)
{
  switch(T)
  {
    case(A_L):
    /* Machine dependent function with I/Os */ 
    break; 
    case(A_R):
    /* Machine dependent function with I/Os */ 
    break; 
    case(B_L):
    /* Machine dependent function with I/Os */ 
    break; 
    case(B_R):
    /* Machine dependent function with I/Os */ 
    break; 
  
  }
}

void set_yellow(traffic_light T)
{
  
   switch(T)
  {
    case(A_L):
    /* Machine dependent function with I/Os */ 
    break; 
    case(A_R):
    /* Machine dependent function with I/Os */ 
    break; 
    case(B_L):
    /* Machine dependent function with I/Os */ 
    break; 
    case(B_R):
    /* Machine dependent function with I/Os */ 
    break; 
  
  }
  
}

void set_red(traffic_light T)
{
  switch(T)
  {
    case(A_L):
    /* Machine dependent function with I/Os */ 
    break; 
    case(A_R):
    /* Machine dependent function with I/Os */ 
    break; 
    case(B_L):
    /* Machine dependent function with I/Os */ 
    break; 
    case(B_R):
    /* Machine dependent function with I/Os */ 
    break; 
  
  }
  
}

void transition_shift(signal_state * traffic_signal)
{
  switch(traffic_signal->last_green_before_all_red)
  {
    case A_L: 
    *(traffic_signal->A_L) = RED;
    *(traffic_signal->A_R) = GREEN;
    *(traffic_signal->B_L) = RED;
    *(traffic_signal->B_R) = RED;
    break; 
    case A_R:
    *(traffic_signal->A_L) = RED;
    *(traffic_signal->A_R) = RED;
    *(traffic_signal->B_L) = GREEN;
    *(traffic_signal->B_R) = RED;
    break; 
    case B_L:
    *(traffic_signal->A_L) = RED;
    *(traffic_signal->A_R) = RED;
    *(traffic_signal->B_L) = RED;
    *(traffic_signal->B_R) = GREEN;
    break; 
    case B_R: 
    *(traffic_signal->A_L) = GREEN;
    *(traffic_signal->A_R) = RED;
    *(traffic_signal->B_L) = RED;
    *(traffic_signal->B_R) = RED;
    break; 
    
    default: 
    *(traffic_signal->A_L) = GREEN;
    *(traffic_signal->A_R) = RED;
    *(traffic_signal->B_L) = RED;
    *(traffic_signal->B_R) = RED;
    break; 
    
  }
}

void  transition_R(signal_state * traffic_signal)
{
  
}

void control_logic(uint8_t counter, bool reset, signal_state * traffic_signal)
{
  
  switch(C1) {
    
    
  case(START): 
    
    state_init(traffic_signal);
    
    if(reset)
      C1 =  START; 
    else if(counter == Y_threshold)
      C1 = TRANSITION_Y; 
     transition_Y(traffic_signal);
    else 
      C1 = START; 
      
    break;
    
    case(TRANSITION_Y): 
    execute_state(traffic_signal); 
    if(reset)
      C1 =  START; 
    else if(counter == R_threshold)
      C1 = ALL_R; 
      transition_R(traffic_signal);
    else 
      C1 = TRANSITION_Y; 
    break;
    
    case(ALL_R): 
    execute_state(traffic_signal); 
    
    if(reset)
      C1 =  START; 
    else if(counter == SHIFT_threshold)
      C1 = SHIFTED; 
      transition_shift(traffic_signal);
    else 
      C1 = ALL_R; 
    break;
    
    case(SHIFTED):
    
    execute_state(traffic_signal); 
    
    if(reset)
      C1 =  START; 
    else if(counter == Y_threshold)
      C1 = TRANSITION_Y; 
      transition_Y(traffic_signal);
    else 
      C1 = SHIFTED; 
    break;
    
    break;
    
  }
  
}

void setup() {
    
}

void loop() {
    
}
