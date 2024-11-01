# Reverse engineered `SAC9010QC` / `SAC12010QC` IR protocol
Reverse engineered IR protocol for HomeFit Living / Alaska `SAC9010QC` / `SAC12010QC` remote control based on an `NEC 756504012` IC. It is [apparently](https://www.aliexpress.com/wholesale?SearchText=Gree+Y512) also known as the "`Gree Y502 / Y512`" remote and the silkscreen on the PCB states "`Gree 5I2`".

If you want to go straight to the juicy parts, go checkout [protocol.md](protocol.md).

The [documentation](documentation) directory contains the `SAC9010QC` / `SAC12010QC` manual and other resources used. The [pics](pics) directory contains some photos of the remote control, it's PCB and my test setup. [dumps](dumps) contains a few [PulseView](https://sigrok.org/wiki/PulseView) dumps of the IR signal as captured by my [DSLogic Plus](https://nl.aliexpress.com/item/33023055743.html).

Finally, [src](src) contains a simple webserver that can be used to control the AC unit by using a REST protocol. It uses the WiFiManager for initial WiFi setup (connect to it's accesspoint, enter your WiFi SSID and password) and after that you can go to it's IP and do a `GET` on `/state` to get the current state (as managed by the ESP, not the *actual* state of the AC unit, since that cannot be read). The response will look like:

```json
{
	"power": false,
	"temperature": 20,
	"fanspeed": 0,
	"mode": "COOL",
	"swing": false,
	"sleep": false,
	"humid": false,
	"light": false,
	"ionizer": false,
	"save": false,
	"timer": 0
}
```

The same JSON can be used to send a new state to the AC unit. Use the same `/state` endpoint and use the `PUT` method. The modes are: `AUTO`, `COOL`, `DEHUMIDIFY`, `FAN` and `HEAT` and are case-insensitive. Fanspeed `0` is `Auto` and can be `0` to `3`. Temperature can range from `16` to `30`. The timer is specified in half-hour increments and can range from `0` to `48` (24 hours). So if you want to set a timer for 13.5 hours use the value `27` (`13.5hr / 0.5hr increments = 27`). The `air1` and `air2` values (see [protocol](protocol.md), bits 24 and 25) are currently not exposed over REST. The webserver uses [IRremoteESP8266](https://github.com/crankyoldgit/IRremoteESP8266) for sending the IR commands (using the [Teco](https://github.com/crankyoldgit/IRremoteESP8266/blob/master/SupportedProtocols.md) protocol).

This is the actual remote:

<img src="https://github.com/RobThree/SAC12010QC/blob/main/pics/remote_front_closed.jpg?raw=true" alt="SAC12010QC remote control" width="250">