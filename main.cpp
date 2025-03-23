#include <iostream>
#include <cmath>
#include "capacitor.h"

using namespace std;

void currentCharging(Capacitor &c, double I_const,int timesteps, double dt) {
	c.current[0] = I_const;
	c.time[0] = 0.0;
  	c.voltage[0] = 0.0;
	
	//time 0 voltage across capacitor is 0, loops through, increases over time
    	for (int i = 1; i < timesteps; i++) {
        	c.time[i] = c.time[i - 1] + dt;
        	c.voltage[i]= c.voltage[i - 1] +(I_const * dt / c.C);
        	c.current[i] = I_const;
	
		//output every 200 timesteps
		if (i %200== 0) {
            		cout 
			<< c.time[i]
                 	<< c.voltage[i]
                 	<< c.current[i] 
			<< endl;
		}            
	}
}

void voltageCharging(Capacitor &c, double V0, double R, int timesteps, double dt) {
	c.time[0]= 0.0;
 	c.voltage[0]= 0.0;
	c.current[0]= V0 / R;

	//loops through, decreases voltage over time
    	for (int i = 1; i < timesteps; i++) {
        	c.time[i] = c.time[i - 1] + dt;
        	c.current[i] =c.current[i - 1] - (c.current[i - 1] * dt /(R * c.C));
        	c.voltage[i] =c.voltage[i - 1] + (c.current[i - 1] * dt / c.C);
	//every 200 timesteps
        if (i %200 == 0) {
            cout 
		<< c.time[i]
                 << c.voltage[i]
                 << c.current[i]
		 << endl;
        }
    }
}	

//print function for capacitor
void printCap(const Capacitor &c, int index) {
    	cout 	
		<< "Time: " << index << " = " << c.time[index]
         	<< " Voltage: " << index << " = " << c.voltage[index]
         	<< " Current: " << index << " = " << c.current[index] 
		<< endl;
}

int main() {

	
	//setting var value consts
    	const double dt = 1e-10;
    	const double final_time = 5e-6;
    	const int timesteps = static_cast<int>(final_time/ dt);
    	const double R = 1000.0;
    	const double C_value = 100e-12;
    	const double I_const = 1e-2;
    	const double V0 = 10.0;

    	Capacitor c_current, c_voltage;
    	c_current.C = C_value;
    	c_voltage.C = C_value;

	//voltage and current
    	c_current.time = new double[timesteps];
    	c_current.voltage = new double[timesteps];
    	c_current.current = new double[timesteps];

    	c_voltage.time= new double[timesteps];
    	c_voltage.voltage= new double[timesteps];
    	c_voltage.current= new double[timesteps];

	//calling all functions
    	currentCharging(c_current, I_const, timesteps, dt);
    	voltageCharging(c_voltage, V0, R, timesteps, dt);
    	printCap(c_current, 200);
    	printCap(c_voltage, 200);
	
	//freeing memory
    	delete[]c_current.time;
    	delete[]c_current.voltage;
    	delete[]c_current.current;
    	delete[]c_voltage.time;
    	delete[]c_voltage.voltage;
    	delete[]c_voltage.current;

    	return 0;
}
	
