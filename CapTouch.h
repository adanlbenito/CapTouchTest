#include <I2c.h>

class CapTouch : public I2c
{
	private:

		enum {
			kCommandNone = 0,
			kCommandMode = 1,
			kCommandScanSettings = 2,
			kCommandPrescaler = 3,
			kCommandNoiseThreshold = 4,
			kCommandIdac = 5,
			kCommandBaselineUpdate = 6,
			kCommandMinimumSize = 7,
			kCommandIdentify = 255
		};

		enum {
			kOffsetCommand = 0,
			kOffsetData = 4
		};
		
		enum {
			kNormalLengthDefault = 20,
			kRawLength = 60
		};
		
		bool isReady;
		uint8_t device_type_; // Which type of device is connected (if any)	
		uint8_t firmware_version_; // Firmware version running on the device

		uint8_t dataBuffer[kRawLength];
		int prepareForDataRead();

	public:
		static unsigned int constexpr numSensors = 26;
		int rawData[numSensors];

		enum Modes {
			NORMAL = 0,
			RAW = 1,
			BASELINE = 2,
			DIFF = 3
		};

		CapTouch();
		~CapTouch();
		CapTouch(int i2c_bus, int i2c_address);
		int setup(int i2c_bus = 1, int i2c_address = 0x18);
		void cleanup();
		
		bool ready(){ return isReady; }
		int setMode(uint8_t mode);
		int updateBaseLine();
		int prepareforDataRead();
		int readI2C();
		int identify();
};
