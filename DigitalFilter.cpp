/*
  DigitalFilter - Bibliothek für verschiedene Digitale Filter

  Stefan Schlee, 2020
*/

#include "DigitalFilter.h"
#include "Arduino.h"

Notch_Order2::Notch_Order2(uint16_t fg, uint16_t fs, float a)
{
	float wn = (float)fg * 2 * PI / (float)fs;	//diskrete Frequenz
	float cosWn = cosf(wn);  //Zwischenspeicher für weitere Rechnungen

	//Filterkoeffizienten
	k = (1 - 2*a*cosWn + a*a) / (1 - 2*cosWn +1);
	b1 = -2*cosWn;
	a0 = -(a*a);
	a1 = 2*a*cosWn;
	// Serial.println(k);
	// Serial.println(b1);
	// Serial.println(a0);
	// Serial.println(a1);
	
	//Speicher mit 0 initialisieren
	u[0] = 0;
	u[1] = 0;
	y[0] = 0;
	y[1] = 0;
	y[2] = 0; 
}

/*
	return Filtered Value
*/
float Notch_Order2::get_Value()
{
	return y[0];
}

/*
	update Filtered Value and return
*/
float Notch_Order2::update(float newVal)
{
	y[0] = k* (newVal + b1 * u[0] + u[1]) + a1 * y[1] + a0 * y[2];

	//shift Speicher
	u[1] = u[0];
	u[0] = newVal;

	y[2] = y[1];
	y[1] = y[0];

	//return new Y
	return y[0];
}


Biquad::Biquad(float b0, float b1, float b2, float a1, float a2)
{
	this->b0 = b0;
	this->b1 = b1;
	this->b2 = b2;
	this->a1 = a1;
	this->a2 = a2;

	//Speicher mit 0 initialisieren
	u[0] = 0;
	u[1] = 0;
	y[0] = 0;
	y[1] = 0;
	y[2] = 0; 
}

float Biquad::get_Value()
{
	return y[0];
}

float Biquad::update(float newVal)
{
	y[0] = newVal*b0 + u[0]*b1 + u[1]*b2 - y[1]*a1 - y[2]*a2;

	//shift Speicher
	u[1] = u[0];
	u[0] = newVal;

	y[2] = y[1];
	y[1] = y[0];

	//return new Y
	return y[0];
}

PT1::PT1(float fg, float fs)
{
	float T = 1 / (2*PI*(float)fg); //Zeitkonstante
	float Ts = 1 / (float)fs;	//Abtastzeit

	b = Ts / (Ts + 2*T);
	a1 = (Ts-2*T) / (Ts+2*T);

	//Speicher mit 0 initialisieren
	u = 0;
	y[0] = 0;
	y[1] = 0;
}

float PT1::get_Value()
{
	return y[0];
}

float PT1::update(float newVal)
{
	y[0] = b * (newVal + u) - a1 * y[1];

	//shift Speicher
	u = newVal;

	y[1] = y[0];

	return y[0];
}