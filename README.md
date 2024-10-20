# Reverse engineered `SAC9010QC` / `SAC12010QC` IR protocol
Reverse engineered IR protocol for HomeFit Living / Alaska `SAC9010QC` / `SAC12010QC` remote control based on an `NEC 756504012` IC. It is [apparently](https://www.aliexpress.com/wholesale?SearchText=Gree+Y512) also known as the "`Gree Y502 / Y512`" remote and the silkscreen on the PCB states "`Gree 5I2`".

If you want to go straight to the juicy parts, go checkout [Docs/Protocol.md](Docs/Protocol.md).

The `Docs` directory contains the reverse engineered protocol description, the `SAC9010QC` / `SAC12010QC` manual and other resources used. In the `IRDumper` directory you'll find a quick'n'dirty tool I used to dump the binary values the remote sends to the AC unit. I put this all in a [spreadsheet](https://docs.google.com/spreadsheets/d/1pSQ7pgmrUBQDSEJBGOqifYe8MEUH_zT2gXGCYaq8Yak/edit?usp=sharing) and used that to 'decipher' the protocol. The `Photos` directory contains some photos of the remote control, it's PCB and my test setup. `SignalDumps` contains a few dumps of the IR signal as captured by [my oscilloscope](https://www.aliexpress.com/item/4000768225718.html).

This is the actual remote:

<img src="https://github.com/RobThree/SAC12010QC/blob/main/Photos/remote_front_closed.jpeg?raw=true" alt="SAC12010QC remote control" width="250">
