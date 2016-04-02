# ofxCppGPIO
A openFrameworks addon wrapping CppGPIO, a C++11 GPIO library for embedded systems on Linux.

This is currently designed to work with Raspberry Pi and is an alternative to the slower SYSFS GPIO approach.

See the examples for use.

## Performance

A quick performance test on a Raspberry Pi 3 in Release mode:

```
for-loop-test:
# Pulses: 10000000 in 241598592
	Period: 24 ns.
	  Freq: 41666666 Hz (41.6667 MHz)

for-loop-unwind-test:
# Pulses: 10000000 in 240994171
	Period: 24 ns.
	  Freq: 41666666 Hz (41.6667 MHz)

min-sleep-test:
# Pulses: 100000 in 6084006480 w/ 1 ns sleep.
	Period: 60840 ns.
	  Freq: 16436 Hz
	  Freq: 16436 Hz (0.016436 MHz)

Minimum sleep time is 60816 ns (60.816 μs)
```

![Screenshot](https://github.com/bakercp/ofxCppGPIO/raw/master/docs/screen_41.7MHz.png)
_41.7MHz Square(ish) Wave_

## A Collection of Square Waves

![Screenshot](https://github.com/bakercp/ofxCppGPIO/raw/master/docs/screen.png)
