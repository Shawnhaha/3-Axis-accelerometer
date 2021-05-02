This lab introduces interrupts and interfacing 3-Axis accelerometer using MSP432 development kit and the Booster pack MKII board.

1. Display “3-Axis Accelerometer” as the title on the first line of the LCD screen. Center the title on the LCD screen and make sure next line is empty. Display “Input tilt angle (x) angle:” left aligned on the next line of the LCD and accept the angle input. Range -90° to +90°. Display “Input rotate (y) angle:” left aligned on the next line of the LCD and accept the angle input. Range -90° to +90°
2. User-inputsfortherequiredtilt(x)angleandrequiredrotate(y)angleshouldbeset through interrupt enabled push buttons: S1 (J4.33), S2 (J4.32), and S1 (P1.1)
3. The LCD should display the current tilt (x) angle and rotate (y) angle of the accelerometer on the next available line every 1⁄2 a second (without using delay loop)
4. Ifthetilt(x)angleandtherotate(y)anglefromtheMKII’saccelerometerisalmost same as the user input, turn on the buzzer (beep) for a short duration, blink the green LED (J4.38) on the MK II board, and display “Matched!” on the LCD. Reset the application after matching the user’s input by LCD output and switch input through S1 (P1.1).
