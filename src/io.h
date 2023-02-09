#ifndef io_h
#define io_h




class Input{
 private:
  int _pin;
 
 public:
  // Costructur where there is the Pinmode Setup
  Input(int input_pin);

  // a Method for read the actual state
  bool IsActive();

};

class Output {

  private:
    int _pin;

   
  public:
    // Costructur where there is the Pinmode Setup
    Output(int input_pin);
     
    //Controlling the Output 
    void On();
    void Off();

    // a Method for read the actual state
    bool IsActive();

};

#endif 

