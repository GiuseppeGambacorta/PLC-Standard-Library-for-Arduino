#ifndef trig_h
#define trig_h




class R_trig{

   private:

      bool _interlock;
      bool _output;

   public:

      void update(bool input);
      bool output();

};

class N_trig{

   private:

      bool _active;
      bool _interlock;
      bool _output;

   public:

      void update(bool input);
      bool output();

};

#endif 

