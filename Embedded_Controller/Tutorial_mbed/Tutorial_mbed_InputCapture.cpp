#include "mbed.h"

Serial      pc(USBTX, USBRX, 9600);
PwmOut      trig(D10); // Trigger ги
InterruptIn echo(D7);  // Echo ги
Timer       tim;

int begin = 0;
int end = 0;

void rising() {
	begin = tim.read_us();
}

void falling() {
	end = tim.read_us();
}

int main(void) {
	float distance = 0;

	trig.period_ms(60);     // period      = 60ms
	trig.pulsewidth_us(10); // pulse-width = 10us

	echo.rise(&rising);
	echo.fall(&falling);

	tim.start();

	while (1) {
		distance = (float)(end - begin) / 58; // [cm]
		pc.printf("Distance = %.2f[cm]\r\n", distance);
		wait(0.5);
	}

}


