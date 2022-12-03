/********************************** grid.h ************************************
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

#include <iostream>
#include <fstream>
#include <exception>
#include <vector>
#include <ctime>
#include <math.h>
#include <set>
#include "cell.h"

/** 
 * Class Grid.
 */
class Grid {
    private:
        CellType cellsType;
        int width;
        int height;
        int week;
        double tempCelsius;
        std::vector<std::vector<Cell*>*> *termiteField;
        std::vector<std::vector<Cell*>*> *environmentField;
    public:
        Grid(int width, int height);
        ~Grid();
        CellEnvironmentState getEnvironmentState(int x, int y);
        CellTermiteState getTermiteState(int x, int y);
        void setEnvironmentState(CellEnvironmentState state, int x, int y);
        void setTermiteState(CellTermiteState state, int x, int y);
        int getWidth();
        int getHeight();
        void simulateTermiteNeighborhood(int x, int y);
        void environmentSeeder(int treeDensity);
        void termiteSeeder(int numberOfColonies = 1, CellTermiteState sizeOfColonies = CellTermiteState::MEDIUM);
        void setTemperatureCelsius(double temp);
        double getTemperatureCelsius();
        void simulateStep();
        void printConsoleTrees();
        void printConsoleTermites();
        void getStats(std::ostream *stream);
        void addWeek();
};