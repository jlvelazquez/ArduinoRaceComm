# ArduinoRaceComm
Arduino computer for endurance racing

W O R K I N P R O G R E S S   

This Arduino project implements an easy-to-use, lowcost bi-directional communication system between driver and box team.

Future developments will take this to a full race computer system for data logging and beyond. 
It's my first Arduino project.

# Premises / pre-requisites

- Low cost gadget
- Easy to use
- Portable: battery powered, low consumption is a must
- Eye catching

# Arduino components and modules

- Arduino Mega
- LCD Display 16x2 + potentiometer to set lcd brightness (specially important in night driving)
- GSM Module (SIM 800L)
- Joystick
- Momentary buttons
- Buzzer. Sounds are implemented to improve user experience, offering audible response to interface changes
- A cool enclosure. This computer has to be practical and cool
- Batteries. First version will use a power bank for Arduino Mega connected to USB port (5V - 500mA) and a LiPo 1S (3.7V) for the GSM Module. The initial idea is to make a 100% portable version. Future implementations will be able to connect to car lighter or directly to the 12V car battery. Estimated operating time with 9000mAh is more than 30 hours in "normal use" (whatever normal use means)
- Bunch of wires, resistors and stuff

# Usage

Communications are based in GSM technology (SMS). Maybe future versions will implement GPRS and web sockets, I know SMS are not cool.

This gadget features a LCD screen, a set of momentary buttons and a joystick:

	-	Buttons send predefined messages to box.
	-	Joystick implements an interface for navigating all the features shown in the LCD screen.
	-	Messages received are shown on the LCD