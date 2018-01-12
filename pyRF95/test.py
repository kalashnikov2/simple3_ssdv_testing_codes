#!/usr/bin/env python3
import rf95

# Create rf95 object with CS0 and external interrupt on pin 25
lora = rf95.RF95(24, 23, 22)

if not lora.init(): # returns True if found
	print("RF95 not found")
	quit(1)
else:
	print("RF95 LoRa mode ok")

# set frequency, power and mode
lora.set_frequency(915.5)
lora.set_tx_power(5)
lora.set_modem_config(Bw31_25Cr48Sf512)

# Send some data
lora.send([0x00, 0x01, 0x02, 0x03])
lora.wait_packet_sent()
# Send a string
lora.send(lora.str_to_data("$TELEMETRY TEST"))
lora.wait_packet_sent()

# Wait until data is available 
while not lora.available():
	pass
# Receive
#data = lora.recv()
#print (data)
#for i in data:
#	print(chr(i), end="")
#print()
lora.set_mode_idle()
