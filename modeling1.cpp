#include <cmath>
#include <iostream>
#include "lunolet.h"
using namespace std;

//const double g = 1.62, maxOverload = 29.43;
//const double moonRad = 1738, maxHeight = 47;

int main() {
    Lunolet lunolet;
    Station station;
    station.distanceLeft = sqrt(pow(station.x - lunolet.x, 2) + pow(station.y - lunolet.y, 2));

    short command;
    while (true) {
        cout << "--- Choose the command ---\n1. New maneuver\n2. Show current situation\n";
        cout << "3. Exit\nYour command: ";
        cin >> command;
        switch (command) {
            case 1: {
                cout << "Angle: ";
                cin >> lunolet.angle;
                cout << "Gas consumption: ";
                cin >> lunolet.gasConsumption;
                cout << "Maneuver time: ";
                cin >> lunolet.maneuverTime;
                station.maneuverTime = lunolet.maneuverTime;
                station.update();
                lunolet.update();
                station.distanceLeft = sqrt(pow(station.x - lunolet.x, 2) + pow(station.y - lunolet.y, 2));

                if (station.distanceLeft <= 0.05) {
                    cout << "You're near the station.\n";
                    if (lunolet.Vy > 0.83 || lunolet.Vx > 0.28)
                        cout << "The conditions for delivery are not met (moving too fast)\n.";
                    else {
                        lunolet.cargoMas = 0;
                        lunolet.delivered = true;
                        cout << "The package has been delivered.\n";
                    }
                }

                break;
            }
            case 2: {
                lunolet.show();
                station.show();
                break;
            }
            default: {
                cout << "Exiting.\n";
                return 0;
            }
        }
    }
}