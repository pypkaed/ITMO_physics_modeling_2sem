#include "lunolet.h"
#include <cmath>

void Lunolet::update_speed() {
    accel = Vp * gasConsumption / gasMas / maneuverTime;
    if (accel > 29.43) { //maxOverload
        free_fall();
        return;
    }
    else
        jet_effect();
}

void Lunolet::update_position() {
    x += Vx * maneuverTime + accel * pow(maneuverTime, 2) / 2;
    y += Vy * maneuverTime + accel * pow(maneuverTime, 2) / 2;
}

void Lunolet::update_rotation() {
    angle = atan2(Vy, Vx) * 180 / M_PI;
}

void Lunolet::free_fall() {
        std::cout << "Falling free.\n";
        Vy -= 0.00162 * maneuverTime; // g, км/с^2
        accel -= 0.00162; // g, км/c^2
        x += Vx * maneuverTime;
        y -= Vy * maneuverTime;
        update_rotation();
}

void Lunolet::jet_effect() {
    if (gasMas - gasConsumption * maneuverTime > 0) {
        lastV = Vp * gasConsumption / gasMas;
        gasMas = gasMas - gasConsumption * maneuverTime;
        Vx += lastV * cos(angle * M_PI / 180);
        Vy += lastV * sin(angle * M_PI / 180);
    }
    else {
        std::cout << "There isn't enough gas left for this maneuver. You fell free.\n";
        free_fall();
    }
}

void Lunolet::show() {
    std::cout << "|   coords   | Vx | Vy | angle | delivered | gas |\n";
    std::cout << "| (" << round(x*100)/100 << "," << round(y*100)/100 << ") |  " << round(Vx*100)/100 << "  |  " << round(Vy*100)/100 << "  |   "
    << round(angle*100)/100 << "  |     "; delivery_status(); std::cout << "   | " << round(gasMas*100)/100 << " |\n";
    std::cout << "\n";
    // table: | coords | Vx | Vy | angle | delivered | gas |
    //        |  (x,y) | -- | -- |   --  |  yes/no   | --- |
}

void Station::show() {
    std::cout << "|   coords   |  distance  |\n";
    std::cout << "| (" << round(x*100)/100 << "," << round(y*100)/100 << ") |     " << distanceLeft << "   |\n";
    std::cout << "\n";
    // table: | coords | distance |
    //        |  (x,y) |    --    |
}

// https://www.cyberforum.ru/cpp-beginners/thread668623.html
void Station::update() {
    angle += M_PI / maneuverTime; // w ~ M_PI (T ~ 2 hours)
    x = 1785 * cos(maneuverTime * angle / 180 * M_PI); // x0 + R * cos(t*a); x0 = 0 - center
    // moonRad + maxHeight
    y = 1785 * sin(maneuverTime * angle / 180 * M_PI);
}

void Lunolet::update() {
    update_speed();
    update_position();
    update_rotation();
}

void Lunolet::delivery_status() {
    if (!delivered)
        std::cout << "NO";
    else
        std::cout << "YES";
}

