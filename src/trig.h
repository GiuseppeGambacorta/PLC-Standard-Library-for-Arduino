#ifndef trig_h
#define trig_h




class R_trig{

private:
   bool interlock;
   bool output;
public:


 //Actual Trig Feedback
 void update(bool input);
 bool Q();
};

class N_trig{

private:
   bool interlock;
   bool output;
public:


 //Actual Trig Feedback
 void update(bool input);
 bool Q();
};

#endif 

