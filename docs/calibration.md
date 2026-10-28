# Ultrasonic Sensor Calibration & Geometry Math

## Volume Formula
For a cylindrical or rectangular tank with flat bottom:
$$\text{Water Height (cm)} = \text{Empty Distance} - \text{Measured Distance}$$
$$\text{Water Percentage (\%)} = \left(\frac{\text{Water Height}}{\text{Tank Height}}\right) \times 100$$
$$\text{Current Volume (Liters)} = \left(\frac{\text{Water Percentage}}{100}\right) \times \text{Capacity (L)}$$

## Setup Calibration Steps
1. Measure the internal height of the empty reservoir from bottom to overflow rim (`TANK_HEIGHT_CM`).
2. Measure the physical clearance between the sensor face and the overflow rim (`SENSOR_OFFSET_CM`).
3. Set `EMPTY_DISTANCE_CM = TANK_HEIGHT_CM + SENSOR_OFFSET_CM`.
