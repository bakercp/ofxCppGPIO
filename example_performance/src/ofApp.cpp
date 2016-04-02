// =============================================================================
//
// Copyright (c) 2016 Christopher Baker <http://christopherbaker.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


#include "ofApp.h"


void ofApp::setup()
{
    testOutput();
    // testPWM();
}

void ofApp::testOutput()
{
    // Bind GPIO pin 18.

    GPIO::DigitalOut out(18);

    // Test the maximum output frequency we can reach on a GPIO output by simply
    // switching it on and off.

    int64_t numPulses = 10000000;
    int64_t nanoSecondsPerSecond = 1000 * 1000 * 1000;
    double secondsPerMegaSecond = 1000000;
    int64_t period = 0; // Period in nanoseconds.
    int64_t shortestPeriod = std::numeric_limits<int64_t>::max();
    int64_t frequency = 0; // Frequency in Hz.
    double frequencyMHz = 0; // Frequncy in MHz.
    {
        auto start = std::chrono::steady_clock::now();


        for (auto x = 0; x < numPulses; ++x)
        {
            out.on();
            out.off();
        }

        auto end = std::chrono::steady_clock::now();

        int64_t ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        period = ns / numPulses;

        frequency = nanoSecondsPerSecond / period;

        frequencyMHz = frequency / secondsPerMegaSecond;

        std::cout << "for-loop-test:" << std::endl;
        std::cout << "# Pulses: " << numPulses << " in " << ns << std::endl;
        std::cout << "\tPeriod: " << period << " ns." << std::endl;;
        std::cout << "\t  Freq: " << frequency << " Hz (" << frequencyMHz << " MHz)" << std::endl;
        std::cout << std::endl;
    }


    shortestPeriod = std::min(shortestPeriod, period);

    // Test again, but this time with 10 output switches in one loop - to see
    // the effect the loop control has.
    {
        auto start = std::chrono::steady_clock::now();

        for (int x = 0; x < numPulses / 10; ++x)
        {
            out.on();
            out.off();
            out.on();
            out.off();
            out.on();
            out.off();
            out.on();
            out.off();
            out.on();
            out.off();
            out.on();
            out.off();
            out.on();
            out.off();
            out.on();
            out.off();
            out.on();
            out.off();
            out.on();
            out.off();
        }

        auto end = std::chrono::steady_clock::now();

        int64_t ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        period = ns / numPulses;

        frequency = nanoSecondsPerSecond / period;
        frequencyMHz = frequency / secondsPerMegaSecond;

        std::cout << "for-loop-unwind-test:" << std::endl;
        std::cout << "# Pulses: " << numPulses << " in " << ns << std::endl;
        std::cout << "\tPeriod: " << period << " ns." << std::endl;;
        std::cout << "\t  Freq: " << frequency << " Hz (" << frequencyMHz << " MHz)" << std::endl;
        std::cout << std::endl;
    }

    shortestPeriod = std::min(shortestPeriod, period);

    numPulses = numPulses / 100;

    // Determine how long a minimum sleep() request of 1 nanoseconds really
    // takes until it returns (compare result to nanoseconds measured in above
    // loop).
    {
        auto start = std::chrono::steady_clock::now();
        auto sleep = std::chrono::nanoseconds(1);

        for (int x = 0; x < numPulses; ++x)
        {
            std::this_thread::sleep_for(sleep);
            out.on();
            out.off();
        }

        auto end = std::chrono::steady_clock::now();

        int64_t ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

        period = ns / numPulses;

        frequency = nanoSecondsPerSecond / period;
        frequencyMHz = frequency / secondsPerMegaSecond;

        std::cout << "min-sleep-test:" << std::endl;
        std::cout << "# Pulses: " << numPulses << " in " << ns << " w/ " << sleep.count() << " ns sleep." << std::endl;
        std::cout << "\tPeriod: " << period << " ns." << std::endl;;
        std::cout << "\t  Freq: " << frequency << " Hz" << std::endl;
        std::cout << "\t  Freq: " << frequency << " Hz (" << frequencyMHz << " MHz)" << std::endl;

        auto minsleep = period - shortestPeriod;

        std::cout << std::endl;
        std::cout << "Minimum sleep time is " << minsleep << " ns (" << (minsleep / 1000.0) << " μs)" << std::endl;
    }
}



void ofApp::testPWM()
{
    std::cout << "Testing PWM output." << std::endl;

    GPIO::PWMOut pwm(23, 100, 0);

    for (int l = 0; l < 20; ++l) {

        for (int p = 0; p < 100; ++p)
        {
            pwm.set_ratio(p);
            std::this_thread::sleep_for(std::chrono::microseconds(5000));
        }

        for (int p = 100; p > 0; --p)
        {
            pwm.set_ratio(p);
            std::this_thread::sleep_for(std::chrono::microseconds(5000));
        }
        
    }
}
