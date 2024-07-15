
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

static const brain_pin_e injPins[] = {
        Gpio::Cat_ingect_H_1,
	Gpio::Cat_ingect_H_2,
	Gpio::Cat_ingect_H_3,
	Gpio::Cat_ingect_H_4,
	Gpio::Cat_ingect_5,
	Gpio::Cat_ingect_6,
	Gpio::Cat_ingect_7,
	Gpio::Cat_ingect_8,
	
};

static const brain_pin_e ignPins[] = {
	Gpio::Cat_IGN_1,
	Gpio::Cat_IGN_2,
	Gpio::Cat_IGN_3,
	Gpio::Cat_IGN_4,
	Gpio::Cat_IGN_5,
	Gpio::Cat_IGN_6,
	Gpio::Cat_IGN_7,
	Gpio::Cat_IGN_8,
	
};

static void setInjectorPins() {
	copyArray(engineConfiguration->injectionPins, injPins);
}

static void setIgnitionPins() {
	copyArray(engineConfiguration->ignitionPins, ignPins);
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
