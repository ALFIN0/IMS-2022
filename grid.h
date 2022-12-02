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
#include <exception>
#include <vector>
#include "cell.h"

class Grid {
    private:
        CellType cellsType;
        int width;
        int height;
        std::vector<std::vector<Cell*>*> *termiteField;
        std::vector<std::vector<Cell*>*> *environmentField;
    public:
        Grid(int width, int height);
        ~Grid();
        CellEnvironmentState getEnvironmentState(int x, int y);
        CellTermiteState getTermiteState(int x, int y);
        void setEnvironmentState(CellEnvironmentState state, int x, int y);
        void setTermiteState(CellTermiteState state, int x, int y);
        double getTermiteNeighborhood(int x, int y);
};