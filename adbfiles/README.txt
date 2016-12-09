
adbLink is tested using the Amazon Fire TV and the Nvidia Shield. 

To run adbLink you need to first set up your device and discover your
IP address and change some settings.


Set up Amazon Fire TV/Stick
============================
From the main (Launcher) screen of AFTV, select Settings.

Select System > Developer Options.

Select ADB debugging.

For USB connections, select USB debugging. Please note that this will disable external storage.

Apps from unknown sources allows you to install apps from other applications, e.g. ES Explorer.

Get the IP Address From the main screen of AFTV, select Settings.

Select System > About > Network. Make note of the IP address listed on this screen.


Set up Nvidia Shield
======================
From the main (Launcher) screen of Shield, select "Settings".

Select About
Scroll down to "Build"

Click "Build" six or seven times. This will tun on "Developer Options"

In the "Preferences" section of settings, open "Developer options"

Turn USB debugging On
Turn Network debugging On

Under Settings->Personal->Security, turn "Unknown sources" On.
Under Settings->Device->Network, make note of your IP address

Next, connect your Shield to your PC via the supplied USB cable. A dialog will pop-up on the Shield asking you to authorize your connection. Confirm the connection and tell the Shield to remember it.

This initial connection via USB is required. Once you have authorized the USB connection, your connection via IP address will be authorized as well.


When your device is set up and you know your device's IP address you are
ready to run adbLink:

1. Start adbLink
2. Press "New"
3. Enter your device data
4. Save the device record
5. Press "Connect"

Once you are up and running, please explore adbLink's help menu for more information.
