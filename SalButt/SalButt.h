#pragma once
#ifndef BUTTTICK_H
#define BUTTTICK_H
    //---ConfigDefines---//
        #define normal 0
        #define reverse 1

    //---Button's class---/
    class SalButt
    {
        //---Public space---//
            public:
            //---Constructor---//
                SalButt(unsigned int pin, bool mode);
            //---Destructor---//
                ~SalButt();
            //---Button Tick---//
                void tick();
            //---Button Initialization---//
                void init();
            //---Function that return true if button is pressing now---//
                bool isPressingNow();
            //---Function that return true if button is holding now---//
                bool isHoldingNow();
            //---Function that return true if button have pressed---//
                bool havePressed();
            //---Function that return true if button have released---//
                bool haveReleased();
            //---Function that return true if button have toggled---//
                bool haveToggled();
            //---Function that return true if button have holded---//
                bool haveHolded();
            //---Function that return count of clicks---//
                unsigned int returnCountClicks();
            //---Function that set TimeHold---//
                void setTimeHold(unsigned int _timeHold);
            //---Function that set tickPeriod---//
                void setTickPeriod(unsigned int _tickPeriod);

        //---Private space---//
            private:
            //---Button character variables---//
                unsigned short int _pin;
                bool _buttState;
                bool _mode;
            //---Tick variables---//
                unsigned int tickPeriod;
                unsigned long tickTmr;
            //---"Pressed" variables---//
                bool pressFlag, onePressFlag;
            //---"Released" variables---//
                bool oneReleaseFlag;
            //---"Toggled" variables---//
                bool oneToggleFlag;
            //---"Holded" variables---//
                unsigned int timeHold;
                unsigned long holdTmr;
                bool holdState, holdFlag;
            //---"CounterClicks" variables---//
                unsigned short int cc, ccOut;
                unsigned long ccTmr;
    };
#endif