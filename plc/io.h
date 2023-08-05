#ifndef io_h
#define io_h


#define NO 0
#define NC 1

class Input{

  private:

    int _pin;
    bool _normalState;

  public:
  
    Input(int input_pin,bool normalState = NO);
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

