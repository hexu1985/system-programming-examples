from http.server import BaseHTTPRequestHandler, HTTPServer
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

HTML_CONTENT = """
<!DOCTYPE html>
<html>
  <head><title>Vending Info</title></head>
  <body>
    <h1>Vending Info</h1>
    <p>Total Coins Inserted: {0}</p>
    <p>Total Vending Operations: {1}</p>
  </body>
</html>
"""

class WebHandler(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header('Content-type', 'text/html')
        self.end_headers()
        response_body = HTML_CONTENT.format(coin_count, vend_count).encode()
        self.wfile.write(response_body)

print('Press CTRL-C to exit program.')
server = HTTPServer(('', 8080), WebHandler)
try:
    server.serve_forever()
except KeyboardInterrupt:
    pass
finally:
    server.server_close()
