/*
 * main.c
 *
 *  Created on: Jan 26, 2019
 *      Author: Ahmed Tarek
 */

#include<util/delay.h>

/*max_no_itrations: max number our 7seg can count */
#define max_no_itrations    10
#define intialization_value 0
#define zero				0xbf
#define one					0x06
#define two					0x5b
#define three				0x4f
#define four				0x66
#define five				0x6d
#define six					0x7d
#define seven				0x07
#define eight				0x7f
#define nine				0x6f

#define red					0x01
#define yellow				0x02
#define green				0x04
/*max_no_leds: number of leds in the traffic light*/
#define max_no_leds			3

typedef unsigned char u8;

typedef union {

	struct {
		u8 Bit0 : 1;
		u8 Bit1 : 1;
		u8 Bit2 : 1;
		u8 Bit3 : 1;
		u8 Bit4 : 1;
		u8 Bit5 : 1;
		u8 Bit6 : 1;
		u8 Bit7 : 1;

	}BitAcess;

	u8 Byteacess;

}Register;

void main(void)
{	/*this array include number of 7seg from 0 to 9*/
	u8 seven_seg[max_no_itrations] = {zero, one, two, three, four, five, six, seven, eight, nine};

	/*this array include three color of traffic light*/
	u8 traffic_light[3]={red,yellow,green};

	/*this variable point to which number will appear on 7seg*/
	u8 number_on_7seg;

	/*this variable point to which led will turn on */
	u8 color_of_led;

	/* set D0 as output pin, DDRD -> bit0 = 1*/
	//*((u8*) 0x31) = 0x01;

	/*to access bit by bit  */
	((Register*) 0x31) -> Byteacess = 0xff;
	((Register*) 0x3A) -> Byteacess = 0xff;

	((Register*) 0x32) -> Byteacess = 0xff;

	/*to access bit by bit  */
	while(1)
	{
		/* set D(color_of_led) to high level (5v)
			 * PORTD -> bit 0 =1
			 */
		for(color_of_led=intialization_value; color_of_led<max_no_leds ;color_of_led++)
		{

			/* set D(number_on_7seg) to high level (5v)
				 * PORTD -> bit 0 =1
				 */
			for(number_on_7seg=intialization_value ; number_on_7seg < max_no_itrations ; number_on_7seg++)
			{
				((Register*) 0x3B) -> Byteacess = seven_seg[(max_no_itrations-1)-number_on_7seg];
				_delay_ms(100);
			}
			((Register*) 0x32) -> Byteacess = traffic_light[color_of_led];

		}
	}
}
