#ifndef io_h
#define io_h


#define NORMALY_OPEN 0
#define NORMALY_CLOSED 1

class Input{

  private:

    int _pin;
    bool _normalState;

  public:
  
    Input(int input_pin,bool normalState = NORMALY_OPEN);
    bool isActive();

};

class Output {

  private:

    int _pin;

  public:

    Output(int input_pin); 
    void on();
    void off();
    bool isActive();

};

#endif 

