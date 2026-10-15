#ifndef CUBE_H
#define CUBE_H

typedef enum{
    WHITE,
    RED,
    GREEN,
    BLUE,
    ORANGE,
    YELLOW
} Color;

typedef struct{
    Color face[6][3][3];
} Cube;

void initCube(Cube *c);

void setSticker(Cube *c,int face,int row,int col,Color color);

void rotateU(Cube *c);
void rotateD(Cube *c);
void rotateL(Cube *c);
void rotateR(Cube *c);
void rotateF(Cube *c);
void rotateB(Cube *c);

void scrambleCube(Cube *c);
void solveCube(Cube *c);

#endif