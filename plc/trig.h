#ifndef trig_h
#define trig_h

class Trig {
public:
    virtual void processInput(bool input) = 0;
    virtual bool isActive() const = 0;
    virtual void operator()(bool input) = 0;
    virtual ~Trig() = default;  
};


class R_trig : public Trig{

   private:

      bool interlock;
      bool output;

   public:

      void processInput(bool input) override;
      bool isActive() const override;
      void operator ()(bool input) override;

};

class N_trig  :public Trig{

   private:

      R_trig trig;
      bool interlock;
     

   public:

      void processInput(bool input) override;
      bool isActive() const override;

};

#endif 

