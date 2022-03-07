It's a small PoC to learn more about IoT devices, it's telemetry and how to communicate through a MQTT broker (Mosquitto).

First NodeMCU device has a LDR sensor that publishes telemetry data to the mosquitto broker;
Second NodeMCU device has a Led wired to it and is subscribed to mosquitto topic, based on the telemetry data it gets from the first device, it will turn the led on or off.
