#ifndef octosnake_h
#define octosnake_h

#include <Servo.h>

//-- Macro for converting from degrees to radians
#ifndef DEG2RAD
  #define DEG2RAD(g) ((g)*M_PI)/180
#endif

class Oscillator{

    public:
        Oscillator();
        float refresh();
        void reset();
        float time_to_radians(double time);
        float degrees_to_radians(float degrees);
        float degrees_to_time(float degrees);
        void setPeriod(int period);
        void setAmplitude(int amplitude);
        void setPhase(int phase);
        void setOffset(int offset);
        void setTrim(int trim);
        void setTime(unsigned long ref);
        unsigned long getTime();

    private:
        int _period;
        int _amplitude;
        int _phase;
        int _offset;
        int _trim;
        bool _stop;
        unsigned long _ref_time = 0;
        float _delta_time = 0;
};

#endif
