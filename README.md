# coffeeControl
An Arduino sketch for my coffee machine addon. 
A scale under the coffee machine keeps track of the state of the machine and how much coffee left in the thermos.

The hardware
- An Arduino Uno
- Ethernet shield
- Two pushbuttons to adjust scale to empty weight and full weight
- A 8-led neopixel array for displaying state, brewing time left and coffee left
- a bathroom scale. I replaced the electronics with a aomplifier and AD-converter 

Features
Keeps track of the coffee machine and post the status to a web server as well as showing it on the LED array.
The coffee machine stands on the scale and the weight of the machine and water/coffee give me the information i need to detect the state.

States
0 empty, weight is below minimum weight+margin
1 brewing, last state was empty and weight is now full-margin. Countdown timer is started to keep track of when cofee is done.
2 coffe ready, countdown timer has reached 0 and weight is above empty+margin. Weight gives percent coffee left

Todo

-leds flicker as they are updated every main loop cycle


