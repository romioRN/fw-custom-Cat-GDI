
#include "pch.h"
#include "Cat_GDI_meta.h"


static void setInjectorPins() {
	engineConfiguration->injectionPins[0] = Gpio::Cat_ingect_H_1;
	engineConfiguration->injectionPins[1] = Gpio::Cat_ingect_H_2;
	engineConfiguration->injectionPins[2] = Gpio::Cat_ingect_H_3;
	engineConfiguration->injectionPins[3] = Gpio::Cat_ingect_H_4;
	engineConfiguration->injectionPins[4] = Gpio::Cat_ingect_5;
	engineConfiguration->injectionPins[5] = Gpio::Cat_ingect_6;
	engineConfiguration->injectionPins[6] = Gpio::Cat_ingect_7;
	engineConfiguration->injectionPins[7] = Gpio::Cat_ingect_8;
}

static void setIgnitionPins() {
	engineConfiguration->ignitionPins[0] = Gpio::Cat_IGN_1;
	engineConfiguration->ignitionPins[1] = Gpio::Cat_IGN_2;
	engineConfiguration->ignitionPins[2] = Gpio::Cat_IGN_3;
	engineConfiguration->ignitionPins[3] = Gpio::Cat_IGN_4;
	engineConfiguration->ignitionPins[4] = Gpio::Cat_IGN_5;
	engineConfiguration->ignitionPins[5] = Gpio::Cat_IGN_6;
	engineConfiguration->ignitionPins[6] = Gpio::Cat_IGN_7;
	engineConfiguration->ignitionPins[7] = Gpio::Cat_IGN_8;
}

static void setEtbConfig() {
	// TLE9201 driver
	// This chip has three control pins:
	// DIR - sets direction of the motor
	// PWM - pwm control (enable high, coast low)
	// DIS - disables motor (enable low)

	// Throttle #1
	// PWM pin
	engineConfiguration->etbIo[0].controlPin = Gpio::D12;
	// DIR pin
	engineConfiguration->etbIo[0].directionPin1 = Gpio::D10;
	// Disable pin
	engineConfiguration->etbIo[0].disablePin = Gpio::D11;

	// Throttle #2
	// PWM pin
	engineConfiguration->etbIo[1].controlPin = Gpio::D13;
	// DIR pin
	engineConfiguration->etbIo[1].directionPin1 = Gpio::D9;
	// Disable pin
	engineConfiguration->etbIo[1].disablePin = Gpio::D8;

	// we only have pwm/dir, no dira/dirb
	engineConfiguration->etb_use_two_wires = false;
}

static void setupVbatt() {
	// 5.6k high side/10k low side = 1.56 ratio divider
	engineConfiguration->analogInputDividerCoefficient = 1.56f;
	
	// 6.34k high side/ 1k low side
	engineConfiguration->vbattDividerCoeff = (92.0f / 10.0f); 

	// Battery sense on PA7
	engineConfiguration->vbattAdcChannel = EFI_ADC_7;

	engineConfiguration->adcVcc = 3.3f;
}

// PE3 is error LED, configured in board.mk
Gpio getCommsLedPin() {
	return Gpio::E4;
}

Gpio getRunningLedPin() {
	return Gpio::E5;
}

Gpio getWarningLedPin() {
	return Gpio::E6;
}

static void setupSdCard() {
	engineConfiguration->sdCardSpiDevice = SPI_DEVICE_3;
	engineConfiguration->sdCardCsPin = Gpio::D2;

	engineConfiguration->is_enabled_spi_3 = true;
	engineConfiguration->spi3sckPin = Gpio::C10;
	engineConfiguration->spi3misoPin = Gpio::C11;
	engineConfiguration->spi3mosiPin = Gpio::C12;


}

void setBoardConfigOverrides() {
	setupVbatt();
	setEtbConfig();
	setupSdCard();

	//engineConfiguration->clt.config.bias_resistor = 2490;
	//engineConfiguration->iat.config.bias_resistor = 2490;

	//CAN 1 bus overwrites
	engineConfiguration->canRxPin = Gpio::D0;
	engineConfiguration->canTxPin = Gpio::D1;

	//CAN 2 bus overwrites
	engineConfiguration->can2RxPin = Gpio::B12;
	engineConfiguration->can2TxPin = Gpio::B13;

	engineConfiguration->lps25BaroSensorScl = Gpio::B10;
	engineConfiguration->lps25BaroSensorSda = Gpio::B11;

        engineConfiguration->is_enabled_spi_5 = true;
	engineConfiguration->spi5sckPin = Gpio::F7;
	engineConfiguration->spi5misoPin = Gpio::F8;
	engineConfiguration->spi5mosiPin = Gpio::F9;
}

void setBoardDefaultConfiguration(void) {
	
	setInjectorPins();
	setIgnitionPins();
      
	engineConfiguration->isSdCardEnabled = true;
}



// board-specific configuration setup
//void setBoardDefaultConfiguration() {

//setIgnitionPins();
//setIgnitionPins();

	
    // engineConfiguration->injectionPins[0] = Gpio::F13;
    // engineConfiguration->ignitionPins[0] = Gpio::E15;

//      engineConfiguration->triggerInputPins[0] = Gpio::B1;
//	engineConfiguration->triggerInputPins[1] = Gpio::Unassigned;

//	engineConfiguration->map.sensor.hwChannel = EFI_ADC_3;

//	engineConfiguration->clt.adcChannel = EFI_ADC_1;

//	engineConfiguration->iat.adcChannel = EFI_ADC_2;


    	// 5.6k high side/10k low side = 1.56 ratio divider
  //  	engineConfiguration->analogInputDividerCoefficient = 1.56f;

    	// 6.34k high side/ 1k low side
//    	engineConfiguration->vbattDividerCoeff = (6.34 + 1) / 1;

//	engineConfiguration->adcVcc = 3.3f;

//	engineConfiguration->clt.config.bias_resistor = 2490;
//	engineConfiguration->iat.config.bias_resistor = 2490;


	// Battery sense on PA0
//	engineConfiguration->vbattAdcChannel = EFI_ADC_0;
//}
