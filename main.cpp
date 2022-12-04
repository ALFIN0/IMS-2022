/********************************* main.cpp ***********************************
 * 
 * Projekt IMS 2022
 * 
 * Název okruhu : 11. Model pomocí celulárního automatu
 * Vybrané téma : Šíření termitů
 * 
 * Řešitelé :   Patrik Dvorščák (xdvors15)
 *              Lada Krofingerová (xkrofi00)
 * 
 * Datum : 28.11.2022
 * 
 *****************************************************************************/

#include "main.h"
#include <iostream>
#include <string.h>
#include <fstream>

void printHelp()
{
    std::cout << "IMS project - Model of cellular automaton\n";
    std::cout << "  Theme - Spread of termites is forested areas with impact temperature\n\n";
    std::cout << "Parameters:\n";
    std::cout << "  Required:\n";
    std::cout << "    -t X: time in weeks of simulation\n";
    std::cout << "  Optional:\n";
    std::cout << "    -x X: width of field, default 400\n";
    std::cout << "    -y X: height of field, default 400\n";
    std::cout << "    -T X: average temperature of simulation in Celsius, default 20\n";
    std::cout << "    -p X: percentage of forestation, default 50\n";
    std::cout << "    -n X: number of termite colonies, default 2\n";
    std::cout << "    -s X: size of termite colonies, default 2, options [1,2,3] - 1 is smallest\n";
    std::cout << "    -f X: statistics file, default standard output\n";
    std::cout << "    -h: print help\n";
}

int main(int argc, char** argv)
{
    int c;
    int height = 400;
    int width = 400;
    int temp = 20;
    int percentage = 50;
    int coloniesCount = 2;
    int time = 0;
    CellTermiteState coloniesSize = CellTermiteState::MEDIUM;
    std::ofstream outStats;

    while((c = getopt(argc, argv, "x:t:y:T:p:n:s:f:h")) != -1)
    {
        switch(c)
        {
            case 'x':
                if (atoi(optarg) <= 0) {
                    std::cerr << "ERR: Wrong parameter of width, -x must be integer > 0\n";
                    exit(EXIT_FAILURE);
                }
                width = atoi(optarg);
                break;
            case 't':
                if (atoi(optarg) <= 0) {
                    std::cerr << "ERR: Wrong parameter of time, -t must be integer > 0\n";
                    exit(EXIT_FAILURE);
                }
                time = atoi(optarg);
                break;
            case 'y':
                if (atoi(optarg) <= 0) {
                    std::cerr << "ERR: Wrong parameter of height, -y must be integer > 0\n";
                    exit(EXIT_FAILURE);
                }
                height = atoi(optarg);
                break;
            case 'T':
                if (atoi(optarg) <= 0 || atoi(optarg) > 50) {
                    std::cerr << "ERR: Wrong parameter of temperature, -T must be integer > 0 and < 50\n";
                    exit(EXIT_FAILURE);
                }
                temp = atoi(optarg);
                break;
            case 'p':
                if ((atoi(optarg) <= 0 || atoi(optarg) > 100) && strcmp(optarg, "0")) {
                    std::cerr << "ERR: Wrong parameter of forest coverage percentage, -p must be integer >= 0 and <= 100\n";
                    exit(EXIT_FAILURE);
                }
                percentage = atoi(optarg);
                break;
            case 'n':
                if (atoi(optarg) <= 0) {
                    std::cerr << "ERR: Wrong parameter of colonies count, -n must be integer > 0\n";
                    exit(EXIT_FAILURE);
                }
                coloniesCount = atoi(optarg);
                break;
            case 's':
                if (strcmp(optarg, "1") && strcmp(optarg, "2") && strcmp(optarg, "3")) {
                    std::cerr << "ERR: Wrong parameter of colonies size, -s must value 1, 2 or 3\n";
                    exit(EXIT_FAILURE);
                }
                if (!strcmp(optarg, "1")) {
                    coloniesSize = CellTermiteState::LOW;
                } else if (!strcmp(optarg, "2")) {
                    coloniesSize = CellTermiteState::MEDIUM;
                } else if (!strcmp(optarg, "3")) {
                    coloniesSize = CellTermiteState::HIGH;
                }
                break;
            case 'f':
                outStats.open(optarg, std::ios::out | std::ios::app);
                break;
            case 'h':
                printHelp();
                return EXIT_SUCCESS;
            default:
                break;
        }
    }
    if (!time) {
        std::cerr << "ERR: Missing parameter time -t\n";
        exit(EXIT_FAILURE);
    }
    
    Grid *grid = new Grid(width, height);
    grid->environmentSeeder(percentage);
    grid->termiteSeeder(coloniesCount, coloniesSize);
    grid->setTemperatureCelsius(temp);

    for (int i = 0; i < time; i++)
    {
        grid->addWeek();

        if (temp < 10) {
            grid->simulateStep();
        } else if (temp >= 10 && temp < 17) {
            for (int i = 0; i < 2; i++)
                grid->simulateStep();
        } else if (temp >= 17 && temp < 23) {
            for (int i = 0; i < 3; i++)
                grid->simulateStep();
        } else if (temp >= 23 && temp < 28) {
            for (int i = 0; i < 4; i++)
                grid->simulateStep();
        } else {
            for (int i = 0; i < 5; i++)
                grid->simulateStep();
        }

        // VIEW STATE AFTER 1 WEEK  
        if (outStats.is_open()) {  
            grid->getStats(&outStats);
        }  else {
            grid->getStats(&std::cout);
        }
        
        
    }

    // std::ofstream outCsv("out.csv", std::ios::out | std::ios::app);
    // grid->getStats(&outCsv);
    // outCsv.close();
    

    if (outStats.is_open()) {
        outStats.close();
    }

    delete grid;
    exit(EXIT_SUCCESS);
}