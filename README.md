# MX-5 Control Unit
<a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-nd/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-nd/4.0/">Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License</a>.
# This is work in progress!
Android app and a controller for my 2001 Mazda MX-5, based on Arduino MEGA, used to control exhaust valves and allow for some automation. Communication between android application and arduino achieved using HC-05 module (Bluetooth 2.0). This module will be later exchanged for HC-10 (BT 4.0LE) and HC-05 module will be used for communication with OBD2 reader based on ELM327 chip.
Exhaust valves are controlled with a relay and an IRF520 MOSFET driver module.

# TODO features
- Intelligent control schemes based on OBD2 data (e.g. opening and closing windows when soft top is down based on speed to limit the amount of wind felt inside).
- Change of window switches to touch screen for control of windows with additional functionality (e.g. lowering windows a bit when raising the soft top and then automatically closing them back up). 
