from time import sleep
from gpiozero import LED, Button

vend_led = LED(2)
vend_button = Button(3)
coin_button = Button(4)
coin_count = 0
vend_count = 0

def print_credits():
    print('Credits: {0}'.format(coin_count - vend_count))

def coin_button_pressed():
    global coin_count
    coin_count += 1
    print_credits()

def vend_button_pressed():
    global vend_count
    if coin_count > vend_count:
        vend_count += 1
        print_credits()
        vend_led.on()
        sleep(0.3)
        vend_led.off()

coin_button.when_pressed = coin_button_pressed
vend_button.when_pressed = vend_button_pressed

input('Press Enter to exit the program.\n')
