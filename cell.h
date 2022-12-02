/********************************** cell.h ************************************
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

#ifndef __CELL_H__
#define __CELL_H__

#include <cstdlib>
#include <exception>

class InvalidCellState : public std::exception {
    public:
   const char * what () const throw () {
      return "Invalid cell state.";
   }
};

class InvalidCellType : public std::exception {
    public:
   const char * what () const throw () {
      return "Invalid cell type.";
   }
};

enum CellEnvironmentState{BLANK, TREE_HEALTHY, TREE_DECAY};
enum CellTermiteState{EMTPY, LOW = 10, MEDIUM = 100, HIGH = 1000};
enum CellType{ENVIRONMENT, TERMITE};

class Cell {
    protected:
        int state;
        CellType type;
    public:
        Cell(CellType type);
        int getType();
        int getState();
        void setType(CellType type);
        void setState(int state);
};

#endif