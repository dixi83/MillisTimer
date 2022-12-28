#ifndef MILLISTIMER_H
#define MILLISTIMER_H

#if ARDUINO >= 100
 #include <Arduino.h>
 #define Constant(x) F(x)
#elif defined(WIRING)
 #include <Wiring.h>
#else
 #include <WProgram.h>
 #define Constant(x) x
#endif

class MillisTimer;
typedef void (*millisTimerEventHandler)(MillisTimer&);

class MillisTimer
{
  public:
    MillisTimer(uint32_t interval = 0, millisTimerEventHandler handler = NULL);

    void expiredHandler(millisTimerEventHandler handler);
    void setInterval(uint32_t interval);
    void setRepeats(uint32_t repeat);      // number of times to repeat, (0) for indefinitely (default)
    void setTargetTime(uint32_t targetTime);
    uint32_t getTargetTime() const;
    uint32_t getRemainingTime() const;
    uint32_t getRemainingRepeats() const;  // Number of repeats remaining.
    bool isRunning() const;
    void stop();
    void start();
    void startFrom(uint32_t startTime);
    void reset();
    bool expired();
    void run();

    uint8_t ID;

  private:
    enum { RUNNING, STOPPED, EXPIRED } m_state;
    
    uint32_t m_targetTime;
    uint32_t m_remainingTime;
    uint32_t m_interval;
    uint32_t m_repeat;
    uint32_t m_repeatCount;
    millisTimerEventHandler cb_onExpired;
};

#endif
