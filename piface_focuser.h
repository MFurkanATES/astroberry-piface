/*******************************************************************************
  Copyright(c) 2016 Radek Kaczorek  <rkaczorek AT gmail DOT com>

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Library General Public
 License version 2 as published by the Free Software Foundation.
 .
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Library General Public License for more details.
 .
 You should have received a copy of the GNU Library General Public License
 along with this library; see the file COPYING.LIB.  If not, write to
 the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 Boston, MA 02110-1301, USA.
*******************************************************************************/

#ifndef PIFACEFOCUS_H
#define PIFACEFOCUS_H

#include <indifocuser.h>

class IndiPiFaceFocuser : public INDI::Focuser
{
    protected:
    private:
        ISwitch FocusResetS[1];
        ISwitchVectorProperty FocusResetSP;
        ISwitch GPIOSelectS[2];
        ISwitchVectorProperty GPIOSelectSP;
        ISwitch MotorDirS[2];
        ISwitchVectorProperty MotorDirSP;
        ISwitch FocusParkingS[2];
        ISwitchVectorProperty FocusParkingSP;
		INumber FocusBacklashN[1];
		INumberVectorProperty FocusBacklashNP;
		INumber MotorDelayN[1];
		INumberVectorProperty MotorDelayNP;
    public:
        IndiPiFaceFocuser();
        virtual ~IndiPiFaceFocuser();

        const char *getDefaultName();

        virtual bool Connect();
        virtual bool Disconnect();
        virtual bool initProperties();
        virtual bool updateProperties();
        virtual void ISGetProperties (const char *dev);

        virtual bool ISNewNumber (const char *dev, const char *name, double values[], char *names[], int n);
        virtual bool ISNewSwitch (const char *dev, const char *name, ISState *states, char *names[], int n);
        virtual bool saveConfigItems(FILE *fp);

		virtual IPState MoveFocuser(FocusDirection dir, int speed, int duration);
        virtual IPState MoveAbsFocuser(int ticks);
        virtual IPState MoveRelFocuser(FocusDirection dir, int ticks);
		virtual int StepperMotor(int steps, FocusDirection dir);
		virtual bool AbortFocuser();
		FocusDirection dir;
		int mcp23s17_fd;
		int step_index;
};

#endif
