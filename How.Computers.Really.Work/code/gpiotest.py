from time import sleep
from gpiozero import LED, Button

button = Button(3)
led = LED(2)

while True:
    led.off()
    button.wait_for_press()
    led.on()
    sleep(1)
