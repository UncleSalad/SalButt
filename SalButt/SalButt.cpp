#include <Arduino.h>
#include "SalButt.h"

//---Defines---//
    // #define debugMode

    #ifdef debugMode
        #define debugStart Serial.begin(9600)
        #define debug(x) Serial.println(x)
        #define debugVal(x, y) Serial.print(x);Serial.println(y)
    #else
        #define debugStart
        #define debug(x)
        #define debugVal(x, y)
    #endif

//---Constructor---//
    //---Function---//
        SalButt::SalButt(unsigned int pin, bool mode)
        {
            _pin = pin;
            _mode = mode;
        }
    /*How to use constructor
        SalButt ObjectName("pin");
        //do something...
    */

//---Destructor---//
    //---Function---//
        SalButt::~SalButt()
        {
        }
    /*How to use destructor
        ~SalButt ObjectName("pin");
        //do something...
    */
//---Button Initialization---//
    //---Function---//
    void SalButt::init()
    {
        debugStart;
        pinMode (_pin, INPUT_PULLUP);
        debug("Button Initialized");
    }
//---Button Tick---//
    //---Function---//
        void SalButt::tick()
        {
            if (millis() - tickTmr > tickPeriod)
            {
                if (_mode == reverse) _buttState = !digitalRead(_pin);
                else _buttState = digitalRead(_pin);
                tickTmr = millis();
            }

            if (ccOut) { ccOut = 0; }

            if (_buttState && !pressFlag)
            {
                pressFlag = true;
                cc++;
                holdTmr = millis();
                ccTmr = millis();
            }
            if (cc)
            {
                if (millis() - ccTmr > timeHold)
                {
                    ccOut = cc;
                    cc = 0;
                }
            }
            if (_buttState)
            {
                if (millis() - holdTmr > timeHold)
                {
                    holdState = true;
                }
            }
            if (!_buttState && pressFlag)
            {
                pressFlag = false;
                holdState = false;
            }
        }
    /*How to use button tick
        ZA_loop_A()
        {
            ObjectName.tick();
            //do something...
        }
    */

//---Function that return true if button is pressing now---//
    //---Function---//
        bool SalButt::isPressingNow() { return pressFlag; }
    /*How to use isPressingNow()
        if (ObjectName.isPressingNow())
        {
            //do something...
        }
    */

//---Function that return true if button is holding---//
    //---Function---//
    bool SalButt::isHoldingNow() { return holdState; }
    /*How to use isHoldingNow()
        if (ObjectName.isHoldingNow())
        {
            //do something...
        }
    */

//---Function that return true if button have pressed---//
    //---Function---//
    bool SalButt::havePressed()
    {
        if (pressFlag && !onePressFlag)
        {
            onePressFlag = true;
            return 1;
        }
        if (!pressFlag && onePressFlag)
        {
            onePressFlag = false;
            return 0;
        }
        return 0;
    }
    /*How to use havePressed()
        if (ObjectName.havePressed())
        {
            //do something...
        }
    */

//---Function that return true if button have released---//
    //---Function---//
    bool SalButt::haveReleased()
    {
        if (pressFlag && !oneReleaseFlag)
        {
            oneReleaseFlag = true;
            return 0;
        }
        else if (!pressFlag && oneReleaseFlag)
        {
            oneReleaseFlag = false;
            return 1;
        }
        else return 0;
    }
    /*How to use haveReleased()
        if (ObjectName.haveReleased())
        {
            //do something...
        }
    */

//---Function that return true if button have toggled---//
        bool SalButt::haveToggled()
        {
            if (pressFlag && !oneToggleFlag)
            {
                oneToggleFlag = true;
                return 1;
            }
            else if (!pressFlag && oneToggleFlag)
            {
                oneToggleFlag = false;
                return 1;
            }
            else return 0;
        }
    /*How to use haveToggled()
        if (ObjectName.haveToggled())
        {
            //do something...
        }
    */

//---Function that return true if button have holded---//
    //---Function---//
        bool SalButt::haveHolded()
        {
            if (holdState && !holdFlag)
            {
                holdFlag = true;
                return 0;
            }
            else if (!holdState && holdFlag)
            {
                holdFlag = false;
                return 1;
            }
            else return 0;
        }
    /*How to use haveHolded()
        if (ObjectName.haveHolded())
        {
            //do something...
        }
    */

//---Function that return count of clicks---//
    //---Function---//
        unsigned int SalButt::returnCountClicks()
        {
            if (ccOut && !holdState) { return ccOut; }
            else { return 0; }
        }
    /*How to use returnCountClicks()
        if (ObjectName.returnCountClicks())
        {
            //do something...
        }
    */

//---Function that set TimeHold---//
    //---Function---//
        void SalButt::setTimeHold(unsigned int _timeHold)  { timeHold = _timeHold; }
    /*How to use setTimeHold()
        ObjectName.setTimeHold()
    */

//---Function that set tickPeriod---//
    //---Function---//
        void SalButt::setTickPeriod(unsigned int _tickPeriod)  { tickPeriod = _tickPeriod; }
    /*How to use tickPeriod()
        ObjectName.tickPeriod()
    */