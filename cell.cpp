/********************************* cell.cpp ***********************************
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

#include "cell.h"

/** 
 * Cell constructor
 * 
 * @param CellType type
 * @throws InvalidCellType
 */
Cell::Cell(CellType type)
{
    this->type = type;
    if (type == CellType::ENVIRONMENT) {
        this->state = CellEnvironmentState::BLANK;
    } else if (type == CellType::TERMITE) {
        this->state = CellTermiteState::EMTPY;
    } else {
        throw InvalidCellType();
    }
}

/** 
 * Type of cell getter.
 * 
 * @return int
 */
int Cell::getType()
{
    return this->type;
}

/** 
 * State of cell getter.
 * 
 * @return int
 */
int Cell::getState()
{
    return this->state;
}

/** 
 * Setter of cell state.
 * 
 * @param int state
 * @throws InvalidCellType
 * @throws InvalidCellState
 */
void Cell::setState(int state)
{
    if (this->type == CellType::ENVIRONMENT) {
        if (state >= CellEnvironmentState::BLANK && state <= CellEnvironmentState::TREE_DECAY) {
            this->state = state;
        } else {
            throw InvalidCellState();
        }
    } else if (type == CellType::TERMITE) {
        if (
            state == CellTermiteState::EMTPY 
            || state <= CellTermiteState::LOW
            || state == CellTermiteState::MEDIUM
            || state == CellTermiteState::HIGH
        ) {
            this->state = state;
        } else {
            throw InvalidCellState();
        }
    } else {
        throw InvalidCellType();
    }
    
}

/** 
 * Setter of cell type.
 * 
 * @param int type
 * @throws InvalidCellType
 */
void Cell::setType(CellType type)
{
    if (type == CellType::ENVIRONMENT) {
        this->type = type;
        this->state = CellEnvironmentState::BLANK;
    } else if (type == CellType::TERMITE) {
        this->type = type;
        this->state = CellTermiteState::EMTPY;
    } else {
        throw InvalidCellType();
    }
    
}