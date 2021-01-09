***********************************************************************************************

TM4C TERMINAL DEMO APPLICATION

Author:		Ameya Phadke
Date created:	8th Jan 2021
Date modified:	8th Jan 2021


***********************************************************************************************


*********************************** About the project *****************************************

This is a small past time project I have made while trying to learn about various
commandline tools used for embedded development. The project has been developed 
using command line tools like vim, make, arm-none-eabi-gcc toolchain. Git has been 
used for version control. The project served a purpose of getting myself aquainted
to these tools while developing something fun.

***********************************************************************************************


**********************************About the application****************************************

The projects implements a terminal application wherein the Ek-tm4c129exl evaluation
board can be connected to a computer as a serial device using uart and on board uart
to usb converter. After connecting to the serial device using a software like putty
or command line tool like cu, the board then presents the user a terminal like 
interface where the user can input various commands to control some of the peripherals
on tm4c microcontroller.

***********************************************************************************************


****************************************Get started********************************************

1.	Clone the repository on to your machine.

2.	build the project by issuing 'make all' command in terminal from root directory of the
	repo.

3.	The elf file generated can be loaded on to ek-tm4c129exl by using either openocd
	with on board icdi debugger. or alternatevely any other usb flashser tool can be used
   
	For using openocd, issue following commands in terminal from root dir of repo clone
   
	i)	make load
   
	Open another terminal window and enter
   
	ii)	telnet localhost 4444
	
	In the same window
	
	iii) reset init
	
	iv)	 flash write_image erase tm4c.elf
   
	v)	reset
	
	vi) shutdown (used to exit openocd )

Now the terminal application is flashed on to the tm4c board.


***********************************Using the application***************************************

Once the program is loaded on to tm4c the board can be disconnected and the program will
remain in the flash. To use the tm4c terminal application follow the steps as below.

1. Connect the tm4c evaluation board to your pc using a usb cable

2. Open any serial communication program like putty or cu.

3.	Connect using the following settings
		
		* 115200 baudrate
		* 8 bit data
		* parity none
		* stop bit 1
		* (if using putty )change the backspace key to use control-H 


4.	After connection is done press reset on board and you will be greated with welcome
	screen on terminal.

***************************************supported commands**************************************

Once the board is connected to terminal and displaying the welcome message there are a 
bunch of commands that are implemented for controling various leds on the board.

* Commands

1. blink

This command controls the blinking behavious of led1 on board. By passing vrious arguments
along with the command the blinking can be stopped, started as well as the period of blinking
can be changed.

i)	'Blink on'	(start blinking)
ii)	'Blink off'	(stop blinking)

iii) 'Blink period XX' ( period of blinking is changed to XX number of System Ticks)


2. pwm

This command can be used to control the pwm signal connected to the led3 on board.
Following arguments can be passed along with the pwm command.

i)	'pwm fade'	(Starts a fade animation effect on the led connected to pwm output)
ii)	'pwm XX'	(Changes the duty cycle of pwm wave to XX% where 0 <= XX <= 100)


3. led2

This simple command can be used to turn the onboard led 2 on or off using following arguments

i)	led2 on		(turns the led 2 on)
ii)	led2 off	(turns the led2 off)



*************************************How the application works**********************************

The application works using a simple foreground-background software architecture. The CPU is in
low power state when all the background work and foreground work is done. The SysTick Timer
present on chip produces periodic System Ticks that interrupt and wake up the cpu from sleep.
The ISR then does all the periodic work such as polling the uart for new data, processing the
received data, updating the state of leds etc.

Following is the flow of the application.

	RESET
	  |
	  |
	  |
	  v
	INIT TASKS
	  |
	  |
	  |
	  v		Interrupt
    -->Sleep state ------------------->SysTick Handler
    |     |					|
    |     |					|
    |     |					|
    |     v					v
    |  Background Task			MainAppTask
    |     |					|
    <------<----------------------------------<--


When Systick interrupt occurs the isr calls the mainAppTask. In the main app task Following
tasks are called

* pwm update
* led update
* terminal update task

pwm update task regularly updates pwm values and he animation effect.
led update task updates the blinking variables for led blinking.
terminal update task parses the input command buffer and executes the commands enterd by
the user.


There is only 1 background task in the application which is to send the data in the output 
buffer through uart. When all the data in output buffer is sent the CPU can go back to sleep
in waiting for interrupt state.


***************************************Directory Structure***************************************

The application has following directory structure

/-
  |
  |
  |
  |
  |
  All the makefiles,
  executable
  debug related files
  |
  |
  ---------src/---------Application related source files
			|
			|
			------hal/------HAL source files
			|
			|
			|
			------inc/------Application related headers
					|
					|
					-------hal/-----HAL headers
					|
					-------core/----microcontroller
							specific headers
								


***********************************Future scope and modifications********************************

**HAL files make this project very much portable. By replacing the HAL files by HAL files for
  other microcontrollers, This project can be very easily ported to any other platform.

**The commands are implemented in a separate source file and a list of commands is maintained,
  thus making it very easy to add any new commands or modify existing commands in the future.

**The actual physical layer of how data is sent(UART in this case) is a separate layer. This
  results in the flexibility of using any kind of communication protocol for tranfering data to 
  the microcontroller. The UART file can be replaced with any other communication interface such
  as an ethernet driver, SPI, I2C or CAN driver for communication with the temrinal.

**In future CPU load can be reduced by further utilizing the on chip DMA for doing the transfers
  to and from uart to the allocated buffer memory.



***************************************************************************************************
