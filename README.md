# E-Paper Photo Frame
<img src="https://github.com/indoorgeek/e-paper-photo-frame/assets/63697764/35777b24-68b3-4633-81bd-d01a18f0da1c" width=75% height=75%> <br/>
Someone has rightly said that "Memories are special moments that tell our story!". I wanted to build something which can bring back the old memories from my favorite places. I had recently got my hands on an e-paper display and such displays mimic the appearance of ink on a good old paper. Perfect! I made a photo frame using a PCB showing my favorite places on a map. Touching any one of the location pads displays an image from that place on the e-paper display.
# The Plan
The brains of the project is an ESP32 microcontroller. I chose this microcontroller mainly for its touch sensing capability on 10 GPIO pins.

The plan is to display a few of my favorite places on a map on the PCB's silkscreen layer. The copper touchpads would then be placed pointing at the locations. The PCB will have a cutout in the middle for the e-paper display i.e. the PCB itself will be a part of the frame. PCB will have a black solder mask along with an ENIG finish. White silkscreen on a black background and gold-plated touchpads. Sweet!

Next, I have to select my favorite images from each location, prepare them for the e-paper display in bitmap (BMP) format, and store them on an SD card.

The next step is to write a code that detects touch and displays an image from that place.

Finally, the last step is to design and 3D print a body to hold all the electronics.
