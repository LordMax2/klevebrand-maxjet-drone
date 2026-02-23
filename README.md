# Klevebrand MaxJet Drone

Open-source C++ flight controller **specifically for an airplanes**, built around one clear idea: **it doesn't need to be harder than it needs to be**.

This project takes the core from [Klevebrand All-Drone Controller](https://github.com/LordMax2/klevebrand-all-drone-controller) and implements everything you need for a solid, flyable airplane.

Optimized for AVR microcontrollers like the **ATmega2560**, but should work on any AVR with enough RAM.

## Features

- **High-performance C++ code** — clean, simple, easy to understand, modern C++
- **Optimized for AVR microcontrollers** — tuned especially for ATmega2560, lightweight and efficient
- **Precise motion tracking** — uses the excellent **BNO085** 9-DOF IMU (gyro + accel + mag)
- **Self-calibrating PID stabilization** — the killer feature from the core library:  
  **Black Box optimization** + **Simulated Annealing** automatically tunes PID values  
  → no endless manual tweaking for different motors, props, batteries or frames  
  → gets noticeably better the more you fly it  
  → quietly keeps adapting in real-time to wind, temperature, motor wear, etc.
- **Radio support** — works with standard PWM receivers + can use 4G/LTE modems for serious long-range control
- **GNSS/GPS** — Available GPS interface to be able to implement autopilot or real time flying metrics of GNSS/GPS data.

## Artificial Intelligence for PID Calibration

Tuning PID for an airplane so it flies stable and feels good is usually time-consuming, fiddly, and frustrating.

This flight controller fixes that.

It uses a **Simulated Annealing** algorithm to run small test movements on its own, then smartly adjusts the PID parameters. This black-box method finds a near-optimal tune with almost no work from you — giving crisp, stable flight much faster.

The optimization **keeps running quietly during normal flights** and adapts on the fly to things like gusty wind, rain, aging motors, different battery levels, or prop changes.

Over time it tunes itself to match **your flying style** — making the airplane feel more and more dialed-in the way **you** like to fly.

## How it relates to Klevebrand All-Drone Controller

This is the **airplane-specific implementation** built on top of the general-purpose library:  
https://github.com/LordMax2/klevebrand-all-drone-controller

- The core lib handles the universal PID logic, sensor abstraction, self-tuning magic, etc.
- MaxJet Drone adds the airplane-specific mixer, motor outputs, servo outputs, receiver parsing, and AVR optimizations so you can actually build and fly an airplane right away.

## License

MIT License — see the `LICENSE` file.
