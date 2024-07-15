
#include "pch.h"
#include "Cat_GDI_meta.h"

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

static void setInjectorPins() {
	engineConfiguration->injectionPins[0] = Gpio::Cat_ingect_H_1;
	engineConfiguration->injectionPins[1] = Gpio::Cat_ingect_H_2;
	engineConfiguration->injectionPins[2] = Gpio::Cat_ingect_H_3;
	engineConfiguration->injectionPins[3] = Gpio::Cat_ingect_H_3;
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








// board-specific configuration setup
void setBoardDefaultConfiguration() {
    // engineConfiguration->injectionPins[0] = Gpio::F13;
    // engineConfiguration->ignitionPins[0] = Gpio::E15;

//   engineConfiguration->triggerInputPins[0] = Gpio::B1;
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
}
