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
#include <stdio.h>
#include <unistd.h>

#include <GL/glut.h>
#include <GL/gl.h>

// constants
#define PIXEL_SIZE 0.02
#define SPACE_BETWEEN 0.03
#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000
#define SCREEN_POSITION_X 100
#define SCREEN_POSITION_Y 100
#define MIN_SCREEN_PADDING 0.05

// global varibles
Grid *grid = nullptr;
int Time;
int temp = 20;
std::ofstream outWeekStats;

void makeStepInSimulation()
{
    grid->addWeek();

    if (temp < 10) {
        grid->simulateStep();
    } else if (temp >= 10 && temp < 15) {
        for (int i = 0; i < 2; i++)
            grid->simulateStep();
    } else if (temp >= 15 && temp < 20) {
        for (int i = 0; i < 3; i++)
            grid->simulateStep();
    } else if (temp >= 20 && temp < 24) {
        for (int i = 0; i < 4; i++)
            grid->simulateStep();
    } else if (temp >= 24 && temp < 28) {
        for (int i = 0; i < 5; i++)
            grid->simulateStep();
    } else {
        for (int i = 0; i < 6; i++)
            grid->simulateStep();
    }

    // VIEW STATE AFTER 1 WEEK
    if (outWeekStats.is_open()) {
        grid->writeWeekStats(&outWeekStats);
    }  else {
        grid->writeWeekStats(&std::cout);
    }


}




float getInitX(float size)
{
    float res = (float)(grid->getWidth()) * size / (-2.0);
    return res;
}

float getInitY(float size)
{
    float res = (float)(grid->getHeight()) * size / (2.0);
    return res;
}

float getTextPositionX(int w, int len)
{
    float res = 0.0 - (float)(w / len) / 100.0;
    return res;
}

float getTextPositionY(float posY)
{
    float res = (1.0 - posY) / 2.0;
    res += posY;
    return res;
}
float getSizeOfCell()
{
    float size = PIXEL_SIZE;
    float x = getInitX(SPACE_BETWEEN);
    float y = getInitY(SPACE_BETWEEN);
    if((1.0-abs(x)) < MIN_SCREEN_PADDING)
    {
        //resize
        size = 0.95/((float)(grid->getWidth()));
        //printf("%f size\n", size);
    }
    if((1.0-abs(y)) < MIN_SCREEN_PADDING + 0.1)
    {
        float tmp_y = 0.85/((float)(grid->getHeight()));
        size = tmp_y < size ? tmp_y : size;
        //printf("%f size\n", size);
    }
    return size;
}

void render()
{
    float size = getSizeOfCell();
    float space = size + 0.01;
    float x = getInitX(space);
    float y = getInitY(space);
    unsigned char text[128];
    for(int t = 0; t < Time +1; t++) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glColor3f(1.0,1.0,1.0);
        snprintf((char *)(text), 128, "%ith week", t);
        int w = glutBitmapLength(GLUT_BITMAP_8_BY_13, text);
        int len = strlen((char *)text);
        float textPositionX = getTextPositionX(w, len);
        float textPositionY = getTextPositionY(y);

        glRasterPos2f(textPositionX, textPositionY);
        for (int i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
        }
        for (int i = 0; i < grid->getWidth(); i++) {
            for (int j = 0; j < grid->getHeight(); j++) {

                //printf("Cell %i and %i adn state %i\n", i, j, grid->getEnvironmentState(i, j));
                if (grid->getEnvironmentState(i, j) == TREE_HEALTHY)
                    glColor3f(0.0, 0.8, 0.0);
                else if (grid->getTermiteState(i, j) == LOW) {
                   // printf("Low\n");
                    glColor3f(1.0, 0.5, 0.0);
                }
                else if (grid->getTermiteState(i, j) == MEDIUM) {
                    //printf("MEdium\n");
                    glColor3f(0.6, 0.3, 0.0); }
                else if (grid->getTermiteState(i, j) == HIGH) {
                    //printf("High\n");
                    glColor3f(0.2, 0.1, 0.0); }
                else if(grid->getEnvironmentState(i, j) == BLANK)
                    continue;

                glBegin(GL_QUADS);
                glVertex2f(x + i * space, y - j * space);
                glVertex2f(x + size + i * space, y - j * space);
                glVertex2f(x + size + i * space, y - size - j * space);
                glVertex2f(x + i * space, y - size - j * space);
                glEnd();

            }
        }

        glutSwapBuffers();
        sleep(2);   //TODO change timing
        makeStepInSimulation();
    }

}



void setup(int width, int height, int percentage, int coloniesCount, CellTermiteState coloniesSize, int temp)
{

    grid = new Grid(width, height);
    grid->environmentSeeder(percentage);
    grid->termiteSeeder(coloniesCount, coloniesSize);
    grid->setTemperatureCelsius(temp);

    /*grid = new Grid(WIDTH,HEIGHT);
    test setting up for
    grid->environmentSeeder(150);
    grid->setEnvironmentState(BLANK, 10,10);
    grid->setTermiteState(LOW, 11,10);
    grid->setEnvironmentState(TREE_DECAY, 11,10);
    grid->setTermiteState(MEDIUM, 12,10);
    grid->setEnvironmentState(TREE_DECAY, 12,10);
    grid->setTermiteState(HIGH, 13,10);
    grid->setEnvironmentState(TREE_DECAY, 13,10);
    Time = 2;
*/
}

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
    std::cout << "    -S X: statistics mode, when using this parameter graphical window will be disabled and result statistics will be appended to given file\n";
    std::cout << "    -h: print help\n";
}

int main(int argc, char** argv)
{
    int c;
    int height = 400;
    int width = 400;
    int percentage = 50;
    int coloniesCount = 2;
    CellTermiteState coloniesSize = CellTermiteState::MEDIUM;
    std::ofstream outProgramStats;

    while((c = getopt(argc, argv, "x:t:y:T:p:n:s:f:S:h")) != -1)
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
                Time = atoi(optarg);
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
                outWeekStats.open(optarg, std::ios::out);
                break;
            case 'S':
                outProgramStats.open(optarg, std::ios::out | std::ios::app);
                if (!outProgramStats.is_open()) {
                    std::cerr << "ERR: Cannot open file \"" << optarg << "\", for parameter -S\n";
                    exit(EXIT_FAILURE);
                }
                break;
            case 'h':
                printHelp();
                return EXIT_SUCCESS;
            default:
                break;
        }
    }
    if (!Time) {
        std::cerr << "ERR: Missing parameter time -t\n";
        exit(EXIT_FAILURE);
    }

    setup(width, height, percentage, coloniesCount, coloniesSize, temp);
    if (outProgramStats.is_open()) {
        for (int i = 0; i < Time; i++) {
            makeStepInSimulation();   
        }

        grid->writeProgramStats(&outProgramStats);
        outProgramStats.close();
    } else {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowPosition(SCREEN_POSITION_X,SCREEN_POSITION_Y);
        glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
        glutCreateWindow("Spread of termites in forested areas with impact temperature");


        glutDisplayFunc(render);

        glutMainLoop();
    }
    

    if (outWeekStats.is_open()) {
        outWeekStats.close();
    }

    delete grid;
    exit(EXIT_SUCCESS);
}