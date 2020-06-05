Open Test Project is an open source Universal Testing machine loosely based off CNC-Kitchens Open Source Universal Test machine

This product is through two parts, and is built with the Arduino DUE and its two COM ports in mind, and its erease button
While not required, running without it would potentially lead to lost reading information.
This guide is also written with the machine schematics that are a part of the Open Test Project. Any alterations that deviates or builds on this are up to the user to document

How to use:
NOTE, TO AVOID INJURY AND DAMAGE OF THE MACHINE, ALWAYS BE PRESENT WHEN TESTING, AND STAY IN RANGE OF THE EMERGENCY STOP BUTTON

1. Alter the opt_sketch Test variables to fit your needs (see documentation for an explanation)
2. Start the OTP_GUI python program. Set the port to the one not used by the Arduino IDE, set the com frequency and name of the SVG output file
3. Click Start. The program will automatically give an error message if no connection can be established
4. Upload the altered Sketch to the Arduino.

To stop:
When testing is done, cut the power to the stepper motors, or upload a new sketch to the Ardunio with the "idle" globale variable set to true.

NOTE:
The GUI will freeze as the program is running, as is standard when using Tkinter for an application like this
When running the values that are read will be printed.
It is safe to force stop the program at any point, this will simply result in the read values to not get printed