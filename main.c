#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <stdio.h>
#include "cube.h"

#define CELL 50

SDL_Color colors[6]={
{255,255,255,255},
{255,0,0,255},
{0,255,0,255},
{0,0,255,255},
{255,165,0,255},
{255,255,0,255}
};

typedef enum {
    NONE, MOVE_U, MOVE_D, MOVE_L, MOVE_R, MOVE_F, MOVE_B
} Move;

Move selectedMove = NONE;

/* animation */
int animating = 0;
int animSteps = 0;
int animMax = 8;
Move animMove;
int animReverse;

/* draw letters */
void drawLetter(SDL_Renderer *r,char ch,int x,int y){

    SDL_SetRenderDrawColor(r,0,0,0,255);

    switch(ch){

        case 'U':
            SDL_RenderDrawLine(r,x,y,x,y+30);
            SDL_RenderDrawLine(r,x+30,y,x+30,y+30);
            SDL_RenderDrawLine(r,x,y+30,x+30,y+30);
            break;

        case 'D':
            SDL_RenderDrawLine(r,x,y,x,y+30);
            SDL_RenderDrawLine(r,x,y,x+20,y+5);
            SDL_RenderDrawLine(r,x+20,y+5,x+20,y+25);
            SDL_RenderDrawLine(r,x+20,y+25,x,y+30);
            break;

        case 'L':
            SDL_RenderDrawLine(r,x,y,x,y+30);
            SDL_RenderDrawLine(r,x,y+30,x+30,y+30);
            break;

        case 'R':
            SDL_RenderDrawLine(r,x,y,x,y+30);
            SDL_RenderDrawLine(r,x,y,x+20,y+5);
            SDL_RenderDrawLine(r,x+20,y+5,x,y+15);
            SDL_RenderDrawLine(r,x,y+15,x+20,y+30);
            break;

        case 'F':
            SDL_RenderDrawLine(r,x,y,x,y+30);
            SDL_RenderDrawLine(r,x,y,x+30,y);
            SDL_RenderDrawLine(r,x,y+15,x+20,y+15);
            break;

        case 'B':
            SDL_RenderDrawLine(r,x,y,x,y+30);
            SDL_RenderDrawLine(r,x,y,x+20,y+5);
            SDL_RenderDrawLine(r,x+20,y+5,x,y+15);
            SDL_RenderDrawLine(r,x,y+15,x+20,y+25);
            SDL_RenderDrawLine(r,x+20,y+25,x,y+30);
            break;
    }
}

/* draw cube */
void drawFace(SDL_Renderer *r,Cube *c,int f,int x,int y){
    for(int i=0;i<3;i++)
    for(int j=0;j<3;j++){
        SDL_Color col=colors[c->face[f][i][j]];
        SDL_SetRenderDrawColor(r,col.r,col.g,col.b,255);

        SDL_Rect rect={x+j*CELL,y+i*CELL,CELL,CELL};
        SDL_RenderFillRect(r,&rect);

        SDL_SetRenderDrawColor(r,0,0,0,255);
        SDL_RenderDrawRect(r,&rect);
    }
}

void renderCube(SDL_Renderer *r,Cube *c){
    int o=CELL*3;

    drawFace(r,c,0,o,0);
    drawFace(r,c,4,0,o);
    drawFace(r,c,2,o,o);
    drawFace(r,c,1,o*2,o);
    drawFace(r,c,3,o*3,o);
    drawFace(r,c,5,o,o*2);
}

/* highlight */
void highlight(SDL_Renderer *r){

    if(selectedMove == NONE) return;

    int o=CELL*3;

    SDL_SetRenderDrawBlendMode(r,SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(r,255,255,255,80);

    SDL_Rect rect;

    switch(selectedMove){
        case MOVE_U: rect=(SDL_Rect){o,0,3*CELL,CELL}; break;
        case MOVE_D: rect=(SDL_Rect){o,o*2+2*CELL,3*CELL,CELL}; break;
        case MOVE_L: rect=(SDL_Rect){0,o,CELL,3*CELL}; break;
        case MOVE_R: rect=(SDL_Rect){o*3+2*CELL,o,CELL,3*CELL}; break;
        case MOVE_F: rect=(SDL_Rect){o,o,3*CELL,3*CELL}; break;
        case MOVE_B: rect=(SDL_Rect){o*3,o,3*CELL,3*CELL}; break;
        default: return;
    }

    SDL_RenderFillRect(r,&rect);
    SDL_SetRenderDrawBlendMode(r,SDL_BLENDMODE_NONE);
}

/* apply move */
void applyMove(Cube *cube,Move m,int reverse){

    int times = reverse ? 3 : 1;

    for(int i=0;i<times;i++){
        switch(m){
            case MOVE_U: rotateU(cube); break;
            case MOVE_D: rotateD(cube); break;
            case MOVE_L: rotateL(cube); break;
            case MOVE_R: rotateR(cube); break;
            case MOVE_F: rotateF(cube); break;
            case MOVE_B: rotateB(cube); break;
            default: break;
        }
    }
}

/* animation */
void startAnimation(Move m,int reverse){
    if(m==NONE) return;
    animating=1;
    animSteps=0;
    animMove=m;
    animReverse=reverse;
}

int inside(SDL_Rect b,int x,int y){
    return x>=b.x && x<=b.x+b.w &&
           y>=b.y && y<=b.y+b.h;
}

int main(){

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *w=SDL_CreateWindow("Rubik Cube",
        SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
        800,600,0);

    SDL_Renderer *r=SDL_CreateRenderer(w,-1,SDL_RENDERER_ACCELERATED);

    Cube cube;
    initCube(&cube);

    SDL_Rect btnU={50,500,50,50};
    SDL_Rect btnD={110,500,50,50};
    SDL_Rect btnL={170,500,50,50};
    SDL_Rect btnR={230,500,50,50};
    SDL_Rect btnF={290,500,50,50};
    SDL_Rect btnB={350,500,50,50};

    SDL_Event e;
    int run=1;

    while(run){

        while(SDL_PollEvent(&e)){

            if(e.type==SDL_QUIT) run=0;

            if(e.type==SDL_MOUSEBUTTONDOWN && !animating){

                int mx=e.button.x;
                int my=e.button.y;

                int reverse = (e.button.button == SDL_BUTTON_RIGHT);

                if(inside(btnU,mx,my)) selectedMove=MOVE_U;
                else if(inside(btnD,mx,my)) selectedMove=MOVE_D;
                else if(inside(btnL,mx,my)) selectedMove=MOVE_L;
                else if(inside(btnR,mx,my)) selectedMove=MOVE_R;
                else if(inside(btnF,mx,my)) selectedMove=MOVE_F;
                else if(inside(btnB,mx,my)) selectedMove=MOVE_B;

                else{
                    startAnimation(selectedMove,reverse);
                }
            }
        }

        /* animation */
        if(animating){
            SDL_Delay(30);
            animSteps++;
            if(animSteps>=animMax){
                applyMove(&cube,animMove,animReverse);
                animating=0;
            }
        }

        SDL_SetRenderDrawColor(r,30,30,30,255);
        SDL_RenderClear(r);

        renderCube(r,&cube);
        highlight(r);

        /* buttons */
        SDL_SetRenderDrawColor(r,200,200,200,255);
        SDL_RenderFillRect(r,&btnU);
        SDL_RenderFillRect(r,&btnD);
        SDL_RenderFillRect(r,&btnL);
        SDL_RenderFillRect(r,&btnR);
        SDL_RenderFillRect(r,&btnF);
        SDL_RenderFillRect(r,&btnB);

        /* letters */
        drawLetter(r,'U',btnU.x+10,btnU.y+10);
        drawLetter(r,'D',btnD.x+10,btnD.y+10);
        drawLetter(r,'L',btnL.x+10,btnL.y+10);
        drawLetter(r,'R',btnR.x+10,btnR.y+10);
        drawLetter(r,'F',btnF.x+10,btnF.y+10);
        drawLetter(r,'B',btnB.x+10,btnB.y+10);

        SDL_RenderPresent(r);
    }

    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    SDL_Quit();

    return 0;
}