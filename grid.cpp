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

/** 
 * Grid constructor
 * 
 * @param int width
 * @param int height
 */
Grid::Grid(int width, int height)
{
    int count = 0;
    this->width = width;
    this->height = height;
    this->termiteField = new std::vector<std::vector<Cell*>*>();
    this->environmentField = new std::vector<std::vector<Cell*>*>();
    this->week = 0;

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

/** 
 * Grid destructor.
 */
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

/** 
 * Get state of environment state of cell.
 * 
 * @param int x
 * @param int y
 * @return CellEnvironmentState
 */
CellEnvironmentState Grid::getEnvironmentState(int x, int y)
{
    if (
        x >= this->environmentField->size() 
        || x < 0
        || y >= this->environmentField->at(x)->size()
        || y < 0
    ) {
        return CellEnvironmentState::BLANK;
    }

    return (CellEnvironmentState) (this->environmentField->at(x)->at(y)->getState());
}

/** 
 * Get state of termite state of cell.
 * 
 * @param int x
 * @param int y
 * @return CellTermiteState
 */
CellTermiteState Grid::getTermiteState(int x, int y)
{
    if (
        x >= this->termiteField->size() 
        || x < 0 
        || y >= this->termiteField->at(x)->size()
        || y < 0
    ) {
        return CellTermiteState::EMTPY;
    }

    return (CellTermiteState) (this->termiteField->at(x)->at(y)->getState());
}

/** 
 * Set state of environment state of cell.
 * 
 * @param CellEnvironmentState state
 * @param int x
 * @param int y
 * @throws InvalidCellType
 * @throws InvalidCellState
 */
void Grid::setEnvironmentState(CellEnvironmentState state, int x, int y)
{
    if (
        x >= this->environmentField->size() 
        || x < 0
        || y >= this->environmentField->at(x)->size()
        || y < 0
    ) {
        return;
    }

    this->environmentField->at(x)->at(y)->setState(state);
}

/** 
 * Set state of termite state of cell.
 * 
 * @param CellTermiteState state
 * @param int x
 * @param int y
 * @throws InvalidCellType
 * @throws InvalidCellState
 */
void Grid::setTermiteState(CellTermiteState state, int x, int y)
{
    if (
        x >= this->termiteField->size() 
        || x < 0 
        || y >= this->termiteField->at(x)->size()
        || y < 0
    ) {
        return;
    }

    this->termiteField->at(x)->at(y)->setState(state);
}

/** 
 * Get width of field.
 * 
 * @return int
 */
int Grid::getWidth()
{
    return this->termiteField->size() > this->environmentField->size() 
        ? this->environmentField->size() 
        : this->termiteField->size();
}

/** 
 * Get height of field.
 * 
 * @return int
 */
int Grid::getHeight()
{
    return this->termiteField->at(0)->size() > this->environmentField->at(0)->size() 
        ? this->environmentField->at(0)->size() 
        : this->termiteField->at(0)->size();
}

/** 
 * Simulate termite movement in its neighborhood.
 * 
 * @param int x
 * @param int y
 */
void Grid::simulateTermiteNeighborhood(int x, int y)
{
    int idx = 0;
    int trees[9], sumTrees = 0;
    int termites[9], sumTermites = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            int treeState = this->getEnvironmentState(x + i, y + j);
            trees[idx] = (treeState == CellEnvironmentState::BLANK) ? 0 : 6 / treeState;
            sumTrees += trees[idx];
            termites[idx] = this->getTermiteState(x + i, y + j);
            if (idx != 4) {
                sumTermites += termites[idx];
            }
            idx++;
        }
    }

    if (sumTrees <= 0 && termites[4] <= CellTermiteState::LOW) {
        for (int i = 0; i < 9; i++) {
            if (i == 4) {
                continue;
            }
            if (termites[i] == CellTermiteState::MEDIUM) {
                this->setTermiteState(CellTermiteState::HIGH, x + (i/3) - 1, y + (i%3) - 1);
                break;
            }
        }
        this->setTermiteState(CellTermiteState::EMTPY, x, y);
    } else if (sumTrees <= 0) {
        bool moved = false;
        for (int i = 0; i < 9; i++) {
            if (i == 4) {
                continue;
            }
            if (sumTermites < 500 && termites[i] == CellTermiteState::EMTPY) {
                this->setTermiteState(CellTermiteState::HIGH, x + (i/3) - 1, y + (i%3) - 1);
                this->setTermiteState(CellTermiteState::EMTPY, x, y);
                moved = true;
                break;
            } else if (sumTermites > 500 && (termites[i] == CellTermiteState::LOW || termites[i] == CellTermiteState::MEDIUM)) {
                this->setTermiteState(CellTermiteState::HIGH, x + (i/3) - 1, y + (i%3) - 1);
                this->setTermiteState(CellTermiteState::EMTPY, x, y);
                moved = true;
                break;
            }
        }
        if (!moved) {
            this->setTermiteState((CellTermiteState)((termites[4]/10 >= 10) ? termites[4]/10 : 0), x, y);
        }
    } else {
        double priority[9] = {0,0,0,0,0,0,0,0,0};
        for (int i = 0; i < 9; i++) {
            if (i == 4) {
                continue;
            }
            int treeValue = trees[i] ? 180 * trees[i] : 0;
            priority[i] = treeValue * (termites[i] ? (termites[i] / 1000.0) : 1000.0);
        }
        double max = 0;
        std::set<int> indexes;
        for (int i = 0; i < 9; i++) {
            if (max < priority[i]) {
                indexes.clear();
                indexes.insert(i);
                max = priority[i];
            } else if (max == priority[i]) {
                indexes.insert(i);
            }
        }
        if (termites[4] == CellTermiteState::HIGH) {
            if (indexes.size() > 1) {
                int value1 = *next(indexes.begin(), 0);
                int value2 = *next(indexes.begin(), 1);
                this->setTermiteState(CellTermiteState::HIGH, x + (value1/3) - 1, y + (value1%3) - 1);
                if (termites[value2] >= CellTermiteState::MEDIUM) {
                    this->setTermiteState(CellTermiteState::HIGH, x + (value2/3) - 1, y + (value2%3) - 1);
                } else {
                    this->setTermiteState(CellTermiteState::MEDIUM, x + (value2/3) - 1, y + (value2%3) - 1);
                }
            } else if (indexes.size()) {
                int value1 = *next(indexes.begin(), 0);
                this->setTermiteState(CellTermiteState::HIGH, x + (value1/3) - 1, y + (value1%3) - 1);
                if (termites[value1] >= CellTermiteState::MEDIUM) {
                    this->setTermiteState(CellTermiteState::MEDIUM, x, y);
                } else {
                    this->setTermiteState(CellTermiteState::LOW, x, y);
                }
            }
        } else {
            if (indexes.size()) {
                int value1 = *next(indexes.begin(), 0);
                if ((termites[4]*termites[value1] > CellTermiteState::HIGH)) {
                    this->setTermiteState(CellTermiteState::HIGH, x + (value1/3) - 1, y + (value1%3) - 1);
                    this->setTermiteState((CellTermiteState)((termites[4]*termites[value1]) / CellTermiteState::HIGH), x, y);
                } else {
                    this->setTermiteState((CellTermiteState)(termites[value1] ? termites[4]*termites[value1] : termites[4]), x + (value1/3) - 1, y + (value1%3) - 1);
                    this->setTermiteState(CellTermiteState::LOW, x, y);
                }
            }
        }
    }
    
}

/** 
 * Tree seeder in environment field.
 * 
 * @param treeDensity <0 - no trees, 100< - all trees
 */
void Grid::environmentSeeder(int treeDensity)
{
    if (treeDensity <= 0) 
        return;

    if (treeDensity >= 100) {
        for (int i = 0; i < this->environmentField->size(); i++)
        {
            for (int j = 0; j < this->environmentField->at(i)->size(); j++)
            {
                this->environmentField->at(i)->at(j)->setState(CellEnvironmentState::TREE_HEALTHY);
            }     
        }
    } else {
        double variances[5] = {(double)treeDensity, treeDensity - treeDensity * 0.15, treeDensity + treeDensity * 0.2, treeDensity - treeDensity * 0.3, treeDensity + treeDensity * 0.4};
        std::srand(std::time(nullptr));
    
        for (int i = 0; i < this->environmentField->size(); i += 4) {
            for (int j = 0; j < this->environmentField->at(i)->size(); j += 4) {
                int trees = round(variances[std::rand() % 5] * 16.0 / 100.0);
                std::set<int> healthyTrees;
                
                if (trees > 15) {
                    for (int idx = 0; idx < 16; idx++) {
                        healthyTrees.insert(idx);
                    }
                    
                } else {
                    while(healthyTrees.size() < trees || healthyTrees.size() > 15) {
                        healthyTrees.insert(std::rand() % 16);
                    }
                }
                
                for(auto& treeIdx: healthyTrees) {
                    int xIndex = i + (int)(treeIdx / 4);
                    int yIndex = j + (treeIdx % 4);
                    
                    if (
                        xIndex < this->environmentField->size()
                        && yIndex < this->environmentField->at(i)->size()
                    ) {
                        this->environmentField->at(xIndex)->at(yIndex)->setState(CellEnvironmentState::TREE_HEALTHY);
                    }
                }
            }     
            
        }
    }
}

/** 
 * Seeds termites in field.
 * 
 * @param int numberOfColonies = 1
 * @param CellTermiteState sizeOfColonies = CellTermiteState::MEDIUM
 */
void Grid::termiteSeeder(int numberOfColonies /*=1*/, CellTermiteState sizeOfColonies /*=CellTermiteState::MEDIUM*/)
{
    if (numberOfColonies <= 0) {
        return;
    }

    std::set<int> termiteCells;
    if (numberOfColonies > this->getWidth() * this->getHeight()) {
        for (int x = 0; x < this->getWidth(); x++) {
            for (int y = 0; y < this->getHeight(); y++)
            {
                this->setTermiteState(sizeOfColonies, x, y);
            }
        }
        
    } else {
        while(termiteCells.size() < numberOfColonies) {
            termiteCells.insert(std::rand() % (this->getWidth() * this->getHeight()));
        }

        for (auto& termiteIdx: termiteCells) {
            this->setTermiteState(sizeOfColonies, (int)(termiteIdx / this->getHeight()), termiteIdx % this->getHeight());
        }
    }
}

/** 
 * 
 */
void Grid::setTemperatureCelsius(double temp)
{
    this->tempCelsius = temp;
}

/** 
 * 
 */
double Grid::getTemperatureCelsius()
{
    return this->tempCelsius;
}

/** 
 * Simulate one step of simulation.
 */
void Grid::simulateStep()
{
    for (int i = 0; i < this->termiteField->size(); i++)
    {
        for (int j = 0; j < this->termiteField->at(i)->size(); j++)
        {
            int currentTermiteState = this->getTermiteState(i, j);
            if (currentTermiteState != CellTermiteState::EMTPY) {

                CellEnvironmentState currentEnviroState = this->getEnvironmentState(i,j);
                if (currentEnviroState == CellEnvironmentState::TREE_HEALTHY && currentTermiteState < CellTermiteState::HIGH) {
                    this->setTermiteState((CellTermiteState)(currentTermiteState*10),i,j);
                } else if (currentEnviroState == CellEnvironmentState::TREE_HEALTHY && currentTermiteState >= CellTermiteState::HIGH) {
                    this->setEnvironmentState(CellEnvironmentState::TREE_ATTACKED,i,j);
                } else if (currentEnviroState == CellEnvironmentState::TREE_ATTACKED) {
                    this->setEnvironmentState(CellEnvironmentState::TREE_DECAY,i,j);
                } else {
                    this->simulateTermiteNeighborhood(i, j);
                }
            }

        }   
    }
}

void Grid::printConsoleTrees()
{
    int count = 0;
    int countErr = 0;
    int countAtt = 0;
    for (int i = 0; i < this->environmentField->size(); i++)
    {
        for (int j = 0; j < this->environmentField->at(i)->size(); j++)
        {
            if (this->environmentField->at(i)->at(j)->getState() == CellEnvironmentState::TREE_HEALTHY) {
                std::cerr << "X";
                count++;
            } else if (this->environmentField->at(i)->at(j)->getState() == CellEnvironmentState::TREE_ATTACKED) {
                std::cerr << "T";
                countAtt++;
            } 
            else if (this->environmentField->at(i)->at(j)->getState() == CellEnvironmentState::TREE_DECAY) {
                std::cerr << "*";
                countErr++;
            } else {
                std::cerr << " ";
            }
                
            
        }   
        std::cerr << "|\n";
    }
    std::cout << count/double(this->environmentField->size() * this->environmentField->at(0)->size()) * 100.0 
    << "\% DECAY: " << countErr/double(this->environmentField->size() * this->environmentField->at(0)->size()) * 100.0 <<"\%\n"
    << "\% ATTACK: " << countAtt/double(this->environmentField->size() * this->environmentField->at(0)->size()) * 100.0 <<"\%\n";
}

void Grid::printConsoleTermites()
{
    int count = 0;
    for (int i = 0; i < this->termiteField->size(); i++)
    {
        for (int j = 0; j < this->termiteField->at(i)->size(); j++)
        {
            if (this->termiteField->at(i)->at(j)->getState() == CellTermiteState::LOW) {
                std::cerr << "*";
                count+=10;
            } else if (this->termiteField->at(i)->at(j)->getState() == CellTermiteState::MEDIUM) {
                std::cerr << "+";
                count+=100;
            } else if (this->termiteField->at(i)->at(j)->getState() == CellTermiteState::HIGH) {
                std::cerr << "X";
                count+=1000;
            } else {
                std::cerr << " ";
            }
            
        }   
        std::cerr << "|\n";
    }
    std::cout << count << " " << this->getHeight() * this->getWidth() <<"\n";
}

void Grid::getStats(std::ostream *stream)
{
    int countLOW = 0;
    int countMED = 0;
    int countHIGH = 0;
    for (int i = 0; i < this->termiteField->size(); i++)
    {
        for (int j = 0; j < this->termiteField->at(i)->size(); j++)
        {
            if (this->termiteField->at(i)->at(j)->getState() == CellTermiteState::LOW) {
                countLOW++;
            } else if (this->termiteField->at(i)->at(j)->getState() == CellTermiteState::MEDIUM) {
                countMED++;
            } else if (this->termiteField->at(i)->at(j)->getState() == CellTermiteState::HIGH) {
                countHIGH++;
            }
            
        }   
    }

    int countHea = 0;
    int countDec = 0;
    int countAtt = 0;
    for (int i = 0; i < this->environmentField->size(); i++)
    {
        for (int j = 0; j < this->environmentField->at(i)->size(); j++)
        {
            if (this->environmentField->at(i)->at(j)->getState() == CellEnvironmentState::TREE_HEALTHY) {
                countHea++;
            } else if (this->environmentField->at(i)->at(j)->getState() == CellEnvironmentState::TREE_ATTACKED) {
                countAtt++;
            } 
            else if (this->environmentField->at(i)->at(j)->getState() == CellEnvironmentState::TREE_DECAY) {
                countDec++;
            }
                
            
        }   
    }

    *stream << "WEEK " << this->week << "\n";
    *stream << "Termite colonies :\n";
    *stream << "  Small populations : " << countLOW << "\n";
    *stream << "  Medium populations : " << countMED << "\n";
    *stream << "  Big populations : " << countHIGH << "\n";
    *stream << "Tree state:\n";
    *stream << "  Healthy : " << countHea << " -> " 
    << countHea/double(this->environmentField->size() * this->environmentField->at(0)->size()) * 100.0  << "%\n";
    *stream << "  Attacked : " << countAtt << " -> "
    << countAtt/double(this->environmentField->size() * this->environmentField->at(0)->size()) * 100.0  << "%\n";
    *stream << "  In decay : " << countDec << " -> " 
    << countDec/double(this->environmentField->size() * this->environmentField->at(0)->size()) * 100.0  << "%\n";

}

void Grid::addWeek()
{
    this->week++;
}