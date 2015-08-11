/* 
 * File:   Hardware.h
 * Author: Richard Greene
 * Definitions of pins and other hardware-related items
 * Created on March 14, 2014, 9:14 AM
 */

#ifndef HARDWARE_H
#define	HARDWARE_H

#define I2C2_PORT           (1) // corresponds to I2C2 on BBB, P9 pins 19 & 20
#define I2C1_PORT           (2) // corresponds to I2C1 on BBB, P9 pins 17 & 18
#define I2C0_PORT           (0) // corresponds to I2C0 on BBB

#define MOTOR_SLAVE_ADDRESS (0x10) // slave address for motor controller
#define MOTOR_INTERRUPT_PIN (60)  // GPIO P9-12, interrupt from motor controller

#define UI_SLAVE_ADDRESS    (0x11) // slave address for UI board
#define UI_COMMAND          (0x20) // command register address for UI board
// button status register for UI board, reading it clears button bits
#define BTN_STATUS          (0x30)  
#define DISPLAY_STATUS      (0x31) // display status register for UI board
#define UI_INTERRUPT_PIN    (30)   // GPIO 30 P9-11, interrupt from UI board

#define ERROR_STATUS        (0xFF) // there was an error on the UI board

// UI board status register values 
#define BTN1_PRESS          (0x01) // press of button 1 
#define BTN1_HOLD           (0x02) // hold of button 1 
#define BTN2_PRESS          (0x04) // press of button 2 
#define BTN2_HOLD           (0x08) // hold of button 2 
#define BTNS_1_AND_2_PRESS  (BTN1_PRESS | BTN2_PRESS)  // press of buttons 1 & 2
#define UI_BOARD_BUSY       (0x10) // indicates when commands cannot be sent

// UI board commands
#define CMD_START 0x98 // Frame start command
#define CMD_END 0x99 // Frame end command
#define CMD_SYNC 0x97 // Sync command
#define CMD_RESET 0x96 // Reset command
#define CMD_RING 0x01 // Put in ring command mode
#define CMD_OLED 0x02 // Put in OLED command mode
#define CMD_RING_OFF 0x01 // Turn ring off
#define CMD_RING_SEQUENCE 0x02 // Start a ring sequence (0 to stop)
#define CMD_RING_LED 0x03 // Set a ring LED to given value
#define CMD_RING_LEDS 0x04 // Set all ring LEDS to given value
#define CMD_OLED_SETTEXT 0x01 // Set OLED text flush left
#define CMD_OLED_CENTERTEXT 0x06 // Set OLED text centered on x
#define CMD_OLED_RIGHTTEXT 0x07 // Set OLED text flush right
#define CMD_OLED_CLEAR 0x02 // Clear OLED 
#define CMD_OLED_ON 0x03 // Turn OLED on
#define CMD_OLED_OFF 0x04 // Turn OLED off
#define CMD_SLEEP 0x03 // Set screensaver awake time
// maximum string length for front panel's I2C buffer
#define MAX_OLED_STRING_LEN (20) 
#define NUM_LEDS_IN_RING (21)

#define DOOR_SENSOR_PIN      (47)   // GPIO1_15
#define ROTATION_SENSOR_PIN  (27)   // GPIO0_27
#define BUTTON2_DIRECT       (45)   // GPIO1_13 connects to front panel button 2 

#define PROJECTOR_SLAVE_ADDRESS  (0x1a) // slave address for projector
#define PROJECTOR_HW_STATUS_REG  (0x20) // hardware status register
// projector register addresses must have their msb set to enable writing 
#define PROJECTOR_LED_ENABLE_REG (0x10 | 0x80) // LED(s) enable register 
#define PROJECTOR_ENABLE_LEDS    (0x7) // value to enable projector's LED(s))
#define PROJECTOR_DISABLE_LEDS   (0x0) // value to disable projector's LED(s))
#define PROJECTOR_LED_CURRENT_REG (0x4B | 0x80) // LED(s) current register 
#define PROJECTOR_LED_PWM_POLARITY_REG (0x0B | 0x80) // PWM polarity register 
// though the datasheet says a value of 0 provides normal polarity, it actually
// appears to provide reversed polarity
#define PROJECTOR_PWM_POLARITY_NORMAL   (0x01) 


#define ETHERNET_INTERFACE ("eth0")  // first (and only) Ethernet interface)
#define WIFI_INTERFACE     ("wlan0") // first (and only) wireless interface)
#define WIFI_ACCESS_POINT_MODE  (3)  // Mode:Master



#endif	/* HARDWARE_H */

