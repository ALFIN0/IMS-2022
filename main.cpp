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
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <GL/glut.h>

// constants
#define PIXEL_SIZE 0.02
#define SPACE_BETWEEN 0.03
#define WIDTH 45
#define HEIGHT 45

// global varibles
Grid *grid = nullptr;
int Time;


void render()
{
    float x = -0.7;
    float y = 0.7;
    //unsigned char text[128];
    for(int t = 0; t < Time; t++) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        /*snprintf((char *)(text), 128, "%ith month", t);
        int w = glutBitmapLength(GLUT_BITMAP_8_BY_13, text);
        int len = strlen((char *)text);
        float textPosition = 0.0 - (float)(w/len)/100.0;
        glRasterPos2f(textPosition, 0.75);
        glColor3f(0.0,0.0,0.0);
        for (int i = 0; i < len; i++) {
            glutBitmapCharacter(GLUT_BITMAP_8_BY_13, text[i]);
        }*/
        for (int i = 0; i < WIDTH; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                if (grid->getEnvironmentState(i, j) == TREE_HEALTHY)
                    glColor3f(0.0, 204.0, 0.0);
                else if (grid->getTermiteState(i, j) == LOW)
                    glColor3f(236.0, 118.0, 0.0);
                else if (grid->getTermiteState(i, j) == MEDIUM)
                    glColor3f(153.0, 76.0, 0.0);
                else if (grid->getTermiteState(i, j) == HIGH)
                    glColor3f(51.0, 25.0, 0.0);

                glBegin(GL_QUADS);
                glVertex2f(x + i * SPACE_BETWEEN, y - j * SPACE_BETWEEN);
                glVertex2f(x + PIXEL_SIZE + i * SPACE_BETWEEN, y - j * SPACE_BETWEEN);
                glVertex2f(x + PIXEL_SIZE + i * SPACE_BETWEEN, y - PIXEL_SIZE - j * SPACE_BETWEEN);
                glVertex2f(x + i * SPACE_BETWEEN, y - PIXEL_SIZE - j * SPACE_BETWEEN);
                glEnd();
            }
        }

        glutSwapBuffers();
        sleep(5);
    }

}

void setup()
{
    grid = new Grid(WIDTH,HEIGHT);
    grid->environmentSeeder(150);
    Time = 2;

}

void printHelp()
{
    std::cout << "IMS project - Model of cellular automaton\n";
    std::cout << "  Theme - Spread of termites is forested areas with impact temperature\n\n";
    std::cout << "Parameters:\n";
    std::cout << "  Required:\n";
    std::cout << "    -x X: width of field\n";
    std::cout << "    -t X: time of simulation\n";
    std::cout << "  Optional:\n";
    std::cout << "    -y X: height of field\n";
    std::cout << "    -T X: temperature of simulation in Celsius\n";
    std::cout << "    -h: print help\n";
}

int main(int argc, char** argv)
{
    int c;
    while((c = getopt(argc, argv, "x:t:y:T:h")) != -1)
    {
        switch(c)
        {
            case 'x':
                std::cerr << "\nwidth: " << optarg;
                break;
            case 't':
                std::cerr << "\ntime: " << optarg;
                break;
            case 'y':
                std::cerr << "\nheight: " << optarg;
                break;
            case 'T':
                std::cerr << "\ntemp: " << optarg;
                break;
            case 'h':
                printHelp();
                return EXIT_SUCCESS;
            default:
                break;
        }
    }

    // Grid *grid = new Grid(45, 45);
    setup();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(640,640);
    glutCreateWindow("Spread of termites is forested areas with impact temperature");

    glutDisplayFunc(render);
    glutMainLoop();

    delete grid;
    return 0;
}