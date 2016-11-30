# Restoring a Photon to factory clean state


## Resetting ownership (from another user)

With Photons only (not Core or Electron), you have the ability to take ownership in close proximity, as long as the device was not part of a product creator product. If it was part of a product, it must first be removed from a product from the product console for security reasons.

It’s best to put the Photon in safe listening mode: Hold down the RESET and SETUP, release RESET and continue to hold down SETUP until it blinks magenta, then release. Wait for it to breathe magenta. If it goes back to blinking magenta, probably because it was set up on a different Wi-Fi network, that’s OK, you can still proceed to the next step.

Hold down the SETUP button again until the Photon blinks blue, then release.

Now use the iOS or Android Particle app to add the device to your account. You will be prompted that it is owned by someone else, but you should be able to take ownership immediately if you say Yes.

If you use the CLI instead of the phone app, a different process is used that sends an email to the owner. This is because the CLI method can be invoked from anywhere on the Internet, whereas the phone app in listening mode requires that you have the device in your possession.

After successfully taking ownership of the device you can then unclaim it from your account. If you want to restore the software and make it really clean, you can also perform the following steps.

If the device is owned by you it's often easier to use the CLI or Particle Build as described below.


## Resetting settings

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

Unclaim the device from your account. If the device is claimed to your account you can use the command line, the Particle Build (Web IDE). Here’s the command line version (insert your device ID):

```
particle device remove 0123456789ABCDEFGHI
```

If you don't know your device ID, hold down the SETUP button until it blinks blue (if not already blinking blue) and use the command:

```
particle identify
```

If the device is not on your account, such as from a classroom or hackathon situation, you may need to use the phone technique, above.


## Resetting firmware

Put the device in DFU mode (blinking yellow) and flash Tinker.

```
particle flash --usb tinker
```

If you want to set the system firmware back to the factory default of 0.4.9:

Download [system-part1-0.4.9-photon.bin](https://github.com/spark/firmware/releases/download/v0.4.9-rc.3/system-part1-0.4.9-photon.bin) and [system-part2-0.4.9-photon.bin](https://github.com/spark/firmware/releases/download/v0.4.9-rc.3/system-part2-0.4.9-photon.bin) from the [github release site](https://github.com/spark/firmware/releases/tag/v0.4.9-rc.3).

Put the Photon in DFU mode and issue the commands:

```
particle flash --usb system-part1-0.4.9-photon.bin
particle flash --usb system-part2-0.4.9-photon.bin
```


## Resetting keys

Reset server key in case it was changed to a local server (optional):

While still in DFU mode:

```
particle keys server
```

Generate new keys (optional):

```
particle keys new
particle keys load device.der
```

## Resetting the claim code

The part that is often missed is clearing the claim code. You need a file that’s 64 bytes long and consists of 0xff bytes, except for the first byte, which is 0x00. Then you flash this to the device in DFU mode:

```
dfu-util -d 2b04:d006 -a 1 -s 1762:64 -D clear_claim.bin
```

Be very careful with that command, typing one wrong number can cause massive headaches by corrupting the configuration! That’s the step that’s necessary to prevent the phone app from saying that the device has already been registered. If you skip this step, users can still claim the device, but they'll get a warning that it has been claimed (even though it's no longer claimed).

Now reset your device and you should be able to claim it with a different user with no warnings, as if it was fresh from the factory.

