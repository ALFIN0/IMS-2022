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

/** 
 * InvalidCellState exception class
 */
class InvalidCellState : public std::exception {
    public:
   const char * what () const throw () {
      return "Invalid cell state.";
   }
};

/** 
 * InvalidCellType exception class
 */
class InvalidCellType : public std::exception {
    public:
   const char * what () const throw () {
      return "Invalid cell type.";
   }
};

/// Enum for environment field cell state.
enum CellEnvironmentState {
    BLANK, ///< blank state - 0
    TREE_HEALTHY, ///< tree is healthy - 1
    TREE_ATTACKED, ///< tree is attacked - 2
    TREE_DECAY ///< tree is in decay - 3
};
/// Enum for termite field cell state
enum CellTermiteState {
    EMTPY, ///< empty cell - 0
    LOW = 10, ///< low amount of termites - 10
    MEDIUM = 100, ///< medium amount of termites - 100 
    HIGH = 1000 ///< high amount of termites - 1000
};
/// Enum for cell field type
enum CellType {
    ENVIRONMENT, ///< environment type field
    TERMITE ///< termite type field
};

/** 
 * Class Cell.
 */
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