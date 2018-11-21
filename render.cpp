#include <Bela.h>
#include <CapTouch.h>

CapTouch touchSensor;


void loop(void*)
{
	while(!gShouldStop)
	{
		if(touchSensor.ready()) {
			touchSensor.readI2C();
			for(unsigned int i = 0; i < sizeof(touchSensor.rawData)/sizeof(int); i++) {
    			printf("%5d ", touchSensor.rawData[i]);
			}	
		}
		usleep(50000);
	}
}

bool setup(BelaContext *context, void *userData)
{
	touchSensor.setup();
	Bela_scheduleAuxiliaryTask(Bela_createAuxiliaryTask(loop, 50, "I2C-read", NULL));
	return true;
}

void render(BelaContext *context, void *userData)
{
}

void cleanup(BelaContext *context, void *userData)
{
	touchSensor.cleanup();
}