/********************************* grid.cpp ***********************************
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

#include "grid.h"

Grid::Grid(int width, int height)
{
    int count = 0;
    this->width = width;
    this->height = height;
    this->termiteField = new std::vector<std::vector<Cell*>*>();
    this->environmentField = new std::vector<std::vector<Cell*>*>();

    for (int i = 0; i < width; i++)
    {
        this->termiteField->push_back(new std::vector<Cell*>());
        this->environmentField->push_back(new std::vector<Cell*>());
        
        for (int j = 0; j < height; j++)
        {
            this->termiteField->at(i)->push_back(new Cell(CellType::TERMITE));
            this->environmentField->at(i)->push_back(new Cell(CellType::ENVIRONMENT));
        }
    }

}

Grid::~Grid()
{
    for (int i = 0; i < this->environmentField->size(); i++)
    {
        for (int j = 0; j < this->environmentField->at(i)->size(); j++)
        {
            delete this->environmentField->at(i)->at(j); 
        }
        delete this->environmentField->at(i);        
    }
    delete this->environmentField;

    for (int i = 0; i < this->termiteField->size(); i++)
    {
        for (int j = 0; j < this->termiteField->at(i)->size(); j++)
        {
            delete this->termiteField->at(i)->at(j); 
        }
        delete this->termiteField->at(i);        
    }
    delete this->termiteField;
}

CellEnvironmentState Grid::getEnvironmentState(int x, int y)
{
    return (CellEnvironmentState) (this->environmentField->at(x)->at(y)->getState());
}

CellTermiteState Grid::getTermiteState(int x, int y)
{
    return (CellTermiteState) (this->termiteField->at(x)->at(y)->getState());
}

void Grid::setEnvironmentState(CellEnvironmentState state, int x, int y)
{
    this->environmentField->at(x)->at(y)->setState(state);
}

void Grid::setTermiteState(CellTermiteState state, int x, int y)
{
    this->termiteField->at(x)->at(y)->setState(state);
}

double Grid::getTermiteNeighborhood(int x, int y)
{
    // zlozity vypocet okolia
    return 45 * 0.1 + 17;
}