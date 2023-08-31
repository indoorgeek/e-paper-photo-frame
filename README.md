# E-Paper Photo Frame
<img src="https://github.com/indoorgeek/e-paper-photo-frame/assets/63697764/35777b24-68b3-4633-81bd-d01a18f0da1c" width=100% height=100%> <br/>
Someone has rightly said that "Memories are special moments that tell our story!". I wanted to build something which can bring back the old memories from my favorite places. I had recently got my hands on an e-paper display and such displays mimic the appearance of ink on a good old paper. Perfect! I made a photo frame using a PCB showing my favorite places on a map. Touching any one of the location pads displays an image from that place on the e-paper display.
# The Plan
<img src="https://github.com/indoorgeek/e-paper-photo-frame/assets/63697764/1db81bf2-5271-4688-8421-f55b18a1f48f" width=100% height=100%>
The brains of the project is an ESP32 microcontroller. I chose this microcontroller mainly for its touch sensing capability on 10 GPIO pins.

The plan is to display a few of my favorite places on a map on the PCB's silkscreen layer. The copper touchpads would then be placed pointing at the locations. The PCB will have a cutout in the middle for the e-paper display i.e. the PCB itself will be a part of the frame. PCB will have a black solder mask along with an ENIG finish. White silkscreen on a black background and gold-plated touchpads. Sweet!

Next, I have to select my favorite images from each location, prepare them for the e-paper display in bitmap (BMP) format, and store them on an SD card.

The next step is to write a code that detects touch and displays an image from that place.

Finally, the last step is to design and 3D print a body to hold all the electronics.
# PCB Design
<p float="center">
  <img src="https://github.com/indoorgeek/e-paper-photo-frame/assets/63697764/6c97721e-c358-483b-8634-59490c4dcb4e" width="40%"/>
  <img src="https://github.com/indoorgeek/e-paper-photo-frame/assets/63697764/8e0e9cc7-e7c2-4f11-928c-0996cf30f2ad" width="40%"/> 
</p>
The first step is to create a silkscreen layer showing the layout of the maps. I wanted only the roads to be visible on the map. For that, I used [this](https://mapstyle.withgoogle.com/) amazing tool by Google Maps. It allows us to edit a lot of things visible on the map. I removed all the buildings and labels and set the color of the road to black and the rest of everything to white. I then grabbed a screenshot and converted the image into PNG showing only the roads and some other stuff that I wanted to be on the silkscreen layer. Finally, after converting the PNG to DXF (which shows just the outline), I imported it onto the silkscreen layer. Pretty sure that there's an efficient way of doing it.

Next, I designed the copper touchpads (as a PCB footprint) to look like the map 'location' symbol. I then placed the pads on the front copper layer at appropriate locations. When it comes to capacitive touchpads, there are few rules which you need to follow. You can read a complete guide on touchpad design [here](https://github.com/ESP32DE/esp-iot-solution-1/blob/master/documents/touch_pad_solution/touch_sensor_design_en.md). That's a lot but this is the minimum I followed and it worked:
- Trace length should not exceed 300mm
- Trace width < 0.18mm (7 mil)
- The angle between two connecting trace segments should not be less than 90 degrees
- No ground plane directly behind (i.e. on bottom layer) or beside the pad. The guide tells us to add a 'hatched' ground plane but that would have affected the appearance. Anyway, it worked for me.
- No ground plane besides the traces
- Pads and traces on the separate layers
- Make sure that there is no ground pour under ESP32's antennae.

I finally exported the gerber files and sent them to [JLCPCB](https://jlcpcb.com/) for fabrication.

# Time for Code
## Preparing Images
Refer this amazing [guide](https://learn.adafruit.com/preparing-graphics-for-e-ink-displays/convert-with-photoshop) by Adafruit to convert images into proper readable format using Photoshop.<br/>
Before you copy your images on the SD card, make sure that the image file names are in UPPERCASE. For example, PIC1.BMP.
## Code
The code basically performs the following functions:
- It checks if a touch is detected using touch interrupts and displays an image associated with that touchpad
- If the time elapsed is > 1hr, it displays a joke/quote from the internet (for fun!)<br/>

I am pulling jokes from [JokeAPI](https://official-joke-api.appspot.com/) and quotes from [Quotable](https://github.com/lukePeavey/quotable). The data is received in JSON format which is deserialized to get the required jokes/quotes.

I have used the following libraries in the code:
- 4.3-inch [EPD](https://github.com/Arduinolibrary/DFRobot_E_paper) library by DFRobots
- [ArduinoJson](https://github.com/bblanchon/ArduinoJson) by bblanchon

All other libraries should be already there by default when you install the boards.
