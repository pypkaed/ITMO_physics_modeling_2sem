#pragma once
#include <iostream>

class Lunolet {
public:
    double x = 0, y = 1738;
    double mass = 2000, cargoMas = 200;
    double gasMas = 4000, Vp = 3660; // Vp - скорость истечения продуктов сгорания

    double height, distanceLeft = -74;
    double angle, gasConsumption, maneuverTime;
    double Vx = 0, Vy = 0, lastV = 0, accel;
    bool delivered = false;

    void update();
    void update_speed();
    void update_position();
    void update_rotation();
    void free_fall();
    void jet_effect();
    void show();
    void delivery_status();
};

class Station {
public:
    double const firstCosmicSpeed = 460.5; // на высоте 47 км, km/h
    double x = 1785, y = 0, distanceLeft = -74;
    double maneuverTime, angle = 0;

    void update();
    void show();
};
