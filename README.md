# simple3_ssdv_testing_codes
ssdv para simple3 

codigos probados en el proceso de aprendisaje de como usar el RF96(modulo de TX/RX de dragino lora hat) a 915mhz para enviar SSDV de la sonda Simple3

https://es.pinout.xyz/pinout/spi

http://wiki.dragino.com/index.php?title=Lora/GPS_HAT

http://www.hoperf.com/upload/rf/RFM95_96_97_98W.pdf

http://piratas.cu.cc/doku.php?id=hub:ssdv:rf95

## RFM69
https://github.com/etrombly/RFM69

pruebas con el otro moduol RF69 que es a 433mhz

## RadioHead
https://github.com/hallard/RadioHead

libreria port para manejar el RF95(RFM95W-915-S2) desde la rpi3 y supuestamente soporta la dragino  lora hat

referencia arduino lib http://www.airspayce.com/mikem/arduino/RadioHead/  

## pyRF95
https://github.com/ladecadence/pyRF95

casi no lo he probado, creo que no instale bien el spidev en python3

## pySX127x
https://github.com/mayeranalytics/pySX127x

no se si trabaja con el modulo dragino sin modificaciones, o con el mudlo directo no me dio

## GEOLOC
https://github.com/manzerbredes/stageIFREMER   GEOLOC

codigo en c que tiene el mapero de referencia y es el unico que trabaja con la dragino lora hat sin alguna modificacion

ya esta modificado del original para tx en 915mhz y lo hace, solo falta leer el XXXXX.bin que da el ssdv para enviarlo en modo rtty

/ssdv   incluido con 2 imagenes de prueba, con originales




### referente de como transmmitir en python
https://github.com/DL7AD/ssdv/blob/master/transmit.py

https://github.com/projecthorus/wenet/blob/master/tx/tx_test_images.py

https://github.com/chrisstubbs93/PiCode/blob/master/FlightCode.py
