#include "cube.h"
#include <stdlib.h>
#include <time.h>


void initCube(Cube *c){

    for(int f=0;f<6;f++)
        for(int r=0;r<3;r++)
            for(int col=0;col<3;col++)
                c->face[f][r][col] = f;
}

void setSticker(Cube *c,int face,int row,int col,Color color){
    c->face[face][row][col] = color;
}



void rotateFaceCW(Cube *c,int f){

    Color temp[3][3];

    for(int r=0;r<3;r++)
        for(int col=0;col<3;col++)
            temp[col][2-r] = c->face[f][r][col];

    for(int r=0;r<3;r++)
        for(int col=0;col<3;col++)
            c->face[f][r][col] = temp[r][col];
}

/* U */

void rotateU(Cube *c){

    rotateFaceCW(c,0);

    Color temp[3];

    for(int i=0;i<3;i++)
        temp[i] = c->face[2][0][i];

    for(int i=0;i<3;i++)
        c->face[2][0][i] = c->face[1][0][i];

    for(int i=0;i<3;i++)
        c->face[1][0][i] = c->face[3][0][i];

    for(int i=0;i<3;i++)
        c->face[3][0][i] = c->face[4][0][i];

    for(int i=0;i<3;i++)
        c->face[4][0][i] = temp[i];
}

/* D */

void rotateD(Cube *c){

    rotateFaceCW(c,5);

    Color temp[3];

    for(int i=0;i<3;i++)
        temp[i] = c->face[2][2][i];

    for(int i=0;i<3;i++)
        c->face[2][2][i] = c->face[4][2][i];

    for(int i=0;i<3;i++)
        c->face[4][2][i] = c->face[3][2][i];

    for(int i=0;i<3;i++)
        c->face[3][2][i] = c->face[1][2][i];

    for(int i=0;i<3;i++)
        c->face[1][2][i] = temp[i];
}

/* L */

void rotateL(Cube *c){

    rotateFaceCW(c,4);

    Color temp[3];

    for(int i=0;i<3;i++)
        temp[i] = c->face[0][i][0];

    for(int i=0;i<3;i++)
        c->face[0][i][0] = c->face[3][2-i][2];

    for(int i=0;i<3;i++)
        c->face[3][2-i][2] = c->face[5][i][0];

    for(int i=0;i<3;i++)
        c->face[5][i][0] = c->face[2][i][0];

    for(int i=0;i<3;i++)
        c->face[2][i][0] = temp[i];
}

/* R */

void rotateR(Cube *c){

    rotateFaceCW(c,1);

    Color temp[3];

    for(int i=0;i<3;i++)
        temp[i] = c->face[0][i][2];

    for(int i=0;i<3;i++)
        c->face[0][i][2] = c->face[2][i][2];

    for(int i=0;i<3;i++)
        c->face[2][i][2] = c->face[5][i][2];

    for(int i=0;i<3;i++)
        c->face[5][i][2] = c->face[3][2-i][0];

    for(int i=0;i<3;i++)
        c->face[3][2-i][0] = temp[i];
}

/* F */

void rotateF(Cube *c){

    rotateFaceCW(c,2);

    Color temp[3];

    for(int i=0;i<3;i++)
        temp[i] = c->face[0][2][i];

    for(int i=0;i<3;i++)
        c->face[0][2][i] = c->face[4][2-i][2];

    for(int i=0;i<3;i++)
        c->face[4][2-i][2] = c->face[5][0][2-i];

    for(int i=0;i<3;i++)
        c->face[5][0][2-i] = c->face[1][i][0];

    for(int i=0;i<3;i++)
        c->face[1][i][0] = temp[i];
}

/* B */

void rotateB(Cube *c){

    rotateFaceCW(c,3);

    Color temp[3];

    for(int i=0;i<3;i++)
        temp[i] = c->face[0][0][i];

    for(int i=0;i<3;i++)
        c->face[0][0][i] = c->face[1][i][2];

    for(int i=0;i<3;i++)
        c->face[1][i][2] = c->face[5][2][2-i];

    for(int i=0;i<3;i++)
        c->face[5][2][2-i] = c->face[4][2-i][0];

    for(int i=0;i<3;i++)
        c->face[4][2-i][0] = temp[i];
}

void scrambleCube(Cube *c){

    srand(time(NULL));

    for(int i=0;i<25;i++){

        int m = rand()%6;

        switch(m){

            case 0: rotateU(c); break;
            case 1: rotateR(c); break;
            case 2: rotateF(c); break;
            case 3: rotateB(c); break;
            case 4: rotateL(c); break;
            case 5: rotateD(c); break;
        }
    }
}

void solveCube(Cube *c){
    initCube(c);
}