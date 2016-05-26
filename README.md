I think I’ve figured out how to restore a Photon to something pretty close to a clean from the factory condition. Registering the device on a new account using a phone no longer prompts that the device has already been claimed. Here are the steps. A script would be a wise choice here, but I thought I’d disseminate the information first.

Run this program to reset the antenna, IP configuration, Wi-Fi credentials and EEPROM:
```
#include "Particle.h"

STARTUP(WiFi.selectAntenna(ANT_INTERNAL));

void setup() {
    EEPROM.clear();

    WiFi.useDynamicIP();
    WiFi.clearCredentials();

    // So you can tell the operations have completed
    pinMode(D7, OUTPUT);
    digitalWrite(D7, HIGH);
}

void loop() {
}
```

Unclaim the device from your account. You can use the command line, the Particle Build (Web IDE) and presumably product creators have something in their dashboard. Here’s the command line version (insert your device ID):
```
particle device remove 0123456789ABCDEFGHI
```

Put the device in DFU mode (blinking yellow) and flash Tinker.
```
particle flash --usb tinker
```

Reset server key in case it was changed to a local server:

Download:
https://s3.amazonaws.com/spark-website/cloud_public.der

While still in DFU mode:
```
particle keys server cloud_public.der
```

Generate new keys:
```
particle keys new
particle keys load device.der
```

The part that I had been missing is clearing the claim code. You need a file that’s 64 bytes long and consists of 0xff bytes, except for the first byte, which is 0x00. Then you flash this to the device in DFU mode:
```
dfu-util -d 2b04:d006 -a 1 -s 1762:64 -D clear_claim.bin
```

Be very careful with that command, typing one wrong number can cause massive headaches by corrupting the configuration! By the way, that’s the step that’s necessary to prevent the phone app from saying that the device has already been registered.

Now reset your device and you should be able to claim it with a different user with no warnings. I tested it with both the Android and iOS Particle apps and it seems to work for me.

I hope this helps!

