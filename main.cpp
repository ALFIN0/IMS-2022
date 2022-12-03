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

#include <GL/glut.h>

#define PIXEL_SIZE 0.02

void render()
{
    float x = 0.5;
    float y = 0.5;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.0, 204.0,0.0);
    glBegin(GL_QUADS);
    glVertex2f(x,y);
    glVertex2f(x+PIXEL_SIZE, y);
    glVertex2f(x+PIXEL_SIZE,y-PIXEL_SIZE);
    glVertex2f(x,y-PIXEL_SIZE);
    glEnd();

    glutSwapBuffers();
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

    Grid *grid = new Grid(45, 45);

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