#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ttt.h"


State createstate(int move, int status) {
    State s;
    s.move = move;
    s.status = status;
    return s;
}

// Checks if the board is filled
int boardfull(int b[9]) {
    for(int i = 0; i < 9; i++){
        if (b[i] == 0){
            return 0;
        }
    }
    return 1;
}

// Returns who the current player is
int whoplays(int b[9]) {
    int exes = 0;
    int os = 0; 
    for(int i = 0; i < 9; i++){
        if(b[i] == 1){
            exes++;
        } else if(b[i] == 2){
            os++;
        }
    }
    if(exes + os == 9){
        return 0;
    } else if (exes == os){
        return 1;
    } 
    return 2;
}

// Returns the other player
int otherplayer(int x) {
    return 3-x;
}

// Makes a copy of the board
int* copyboard(int b[9]) {
    int* a = malloc(sizeof(int)*9); 
    for(int i = 0; i < 9; i++){
        a[i] = b[i];
    }
    return a; 
}

// Returns the better state.
State betterstate(State s1, State s2, int player) {
    // TODO: If there are several equally good choices,
    // take a random one
    if(s1.status == player) {
        return s1;
    }
    if(s2.status == player) {
        return s2;
    }
    if(s1.status == 0) {
        return s1;
    }
    return s2;
}

// Given a board, play a winning move if there is one
// otherwise, play a drawing move if there is one,
// otherwise, play any move
State bestmove(int b[9]) {
    //fprintf(stderr, "Begin bestmove\n");
    //printboard(b);
    if(boardfull(b)) {
        int winner = checkwin(b);
        return createstate(-1, winner);
    } else if(checkwin(b)) {
        int winner = checkwin(b);
        return createstate(-1, winner);
    } else {
        int p = whoplays(b);

        State best = {-1, otherplayer(p)};

        for(int i = 1; i <= 9; i++) {
            if(b[i-1] == 0) {
                int* newb = copyboard(b);
                newb[i-1] = p;
                State s;
                s.move = i;
                s.status = bestmove(newb).status;
                best = betterstate(best, s, p);
            }
        }
        return best;
    }
}

void printboard(int b[9]){
    for(int i = 0; i < 9; i++){
        if (i % 3 == 0 && i != 0){ printf("\n");}
        if (b[i] == 1){ printf("X");} 
        else if (b[i] == 2) { printf("O");} 
        else {printf("%d", i+1);}
    }
    printf("\n");
}
void initboard(int a[9]){
    for(int i = 0; i < 9; i++){
        a[i] = 0;
    }
}
int checkmove(){
    char s[256];
    int len = scanf("%s", s);
    assert(len >= 0);

    int ok = 1;
    ok &= strlen(s) == 1;
    ok &= '1' <= s[0] && s[0] <= '9';
    if(!ok) {
        printf("PLAY A VALID MOVE\n");
        return -1;
    }
    return s[0] - '0';
}
void playmove(int b[9], int move){
    while(1){
        int num = checkmove();
        if(num == -1) continue;
        num--;
        if(b[num] == 0){
            b[num] = move==0?1:2;
            break;
        } else { 
            printf("PLAY SOMEWHERE ELSE\n");
        }
    }
}
int checkwin(int b[9]){
    //check rows
    for(int i = 0; i < 9; i+=3){
        if(b[i] == b[1 + i] &&
            b[i] == b[2 + i] && 
            b[i] != 0){
            return b[i];
        }
    }

    //check cols
    if(b[0] == b[3] && b[0] == b[6] && b[0] != 0){
        return b[0];
    }
    if(b[1] == b[4] && b[1] == b[7] && b[1] != 0){
        return b[1];
    }
    if(b[2] == b[5] && b[2] == b[8] && b[2] != 0){
        return b[2];
    }
    /*for(int i = 0; i < 3; i++){
        if(b[i] == b[3 + i] && 
            b[i] == b[6 + i]){
            return b[i];
        }
    }*/
    //check diags
    if(b[0] == b[4] && b[0] == b[8] && b[0] != 0){
        return b[0];
    } else if (b[2] == b[4] && b[2] == b[6] && b[4] != 0){ 
        return b[4];
    }
    return 0;
}

int main(int argc, char *argv[]){
    int b[9];
    initboard(b);
    for(int i = 0; i < 9; i++){
        printf("\n=====================\nplease enter a number 1-9\n");
        printboard(b);
        if(i % 2 == 0){ // human plays
            playmove(b, i % 2); 
        } else { //computer plays
            State st = bestmove(b);
            b[st.move - 1] = 2;
        }
        if (checkwin(b) == 1){
            printf("X Wins!\n");
            break;
        } else if (checkwin(b) == 2) { 
            printf("O Wins!\n");
            break;
        }
    }
    printboard(b);

    return 0;
}
