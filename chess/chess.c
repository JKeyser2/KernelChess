#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


void CreateBoard(char theBoardArray[8][8][4]);
void PrintBoard(char theBoardArray[8][8][4]);


int WhitePawnAllMovesUser(int whitePawnAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece, char* upgradedPiece);
int WhiteKingAllMovesUser(int whiteKingAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece);
int WhiteKnightAllMovesUser(int whiteKnightAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece);
int WhiteRookAllMovesUser(int whiteRookAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece);
int WhiteBishopAllMovesUser(int whiteBishopAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece);
int WhiteQueenAllMovesUser(int whiteQueenAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece);


int BlackPawnAllMovesUser(int blackPawnAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece, char* upgradedPiece);
int BlackKingAllMovesUser(int whiteKingAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece);
int BlackKnightAllMovesUser(int blackKnightAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece);
int BlackRookAllMovesUser(int whiteRookAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece);
int BlackBishopAllMovesUser(int blackBishopAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece);
int BlackQueenAllMovesUser(int blackQueenAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece);


int WhitePawnAllMovesCpu(int whitePawnAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]);
int WhiteKingAllMovesCpu(int whiteKingAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]);
int WhiteKnightAllMovesCpu(int whiteKnightAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]);
int WhiteRookAllMovesCpu(int whiteRookAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]);
int WhiteBishopAllMovesCpu(int whiteBishopAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]);
int WhiteQueenAllMovesCpu(int whiteQueenAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]);


int BlackPawnAllMovesCpu(int blackPawnAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]);
int BlackKingAllMovesCpu(int blackKingAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]);
int BlackKnightAllMovesCpu(int blackKnightAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]);
int BlackRookAllMovesCpu(int blackRookAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]);
int BlackBishopAllMovesCpu(int blackBishopAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]);
int BlackQueenAllMovesCpu(int blackQueenAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]);


int WhiteCpuPickMove(char theBoardArray[8][8][4]);
int BlackCpuPickMove(char theBoardArray[8][8][4]);


int FindCheckOnWhiteKing(char theBoardArray[8][8][4]);


void ConvertLocationToIndex(char* theLocation, int pieceLocation[1][2]);



int main(){
    char theBoardArray[8][8][4];

    CreateBoard(theBoardArray);

    PrintBoard(theBoardArray);

    int pieceStartLocation[1][2];
    int pieceEndLocation[1][2];

    char* startLocation = "";
    char* endLocation = "";
    char* takenPiece = "";
    char* upgradedPiece = "";

    ConvertLocationToIndex(startLocation, pieceStartLocation);
    ConvertLocationToIndex(endLocation, pieceEndLocation);

    int whitePawnAllMovesUser[100][2];
    //WhitePawnAllMovesUser(whitePawnAllMovesUser, theBoardArray, pieceStartLocation, pieceEndLocation, takenPiece, upgradedPiece);
    int whiteKingAllMovesUser[100][2];
    //WhiteKingAllMovesUser(whiteKingAllMovesUser, theBoardArray, pieceStartLocation, pieceEndLocation, takenPiece);
    int whiteKnightAllMovesUser[100][2];
    //WhiteKnightAllMovesUser(whiteKnightAllMovesUser, theBoardArray, pieceStartLocation, pieceEndLocation, takenPiece);
    int whiteRookAllMovesUser[100][2];
    //WhiteRookAllMovesUser(whiteRookAllMovesUser, theBoardArray, pieceStartLocation, pieceEndLocation, takenPiece);
    int whiteBishopAllMovesUser[100][2];
    //WhiteBishopAllMovesUser(whiteBishopAllMovesUser, theBoardArray, pieceStartLocation, pieceEndLocation, takenPiece);
    int whiteQueenAllMovesUser[100][2];
    //WhiteQueenAllMovesUser(whiteQueenAllMovesUser, theBoardArray, pieceStartLocation, pieceEndLocation, takenPiece);


    int blackPawnAllMovesUser[100][2];
    //BlackPawnAllMovesUser(blackPawnAllMovesUser, theBoardArray, pieceStartLocation, pieceEndLocation, takenPiece, upgradedPiece);
    int blackKingAllMovesUser[100][2];
    //BlackKingAllMovesUser(blackKingAllMovesUser, theBoardArray, pieceStartLocation, pieceEndLocation, takenPiece);
    int blackKnightAllMovesUser[100][2];
    //BlackKnightAllMovesUser(blackKnightAllMovesUser, theBoardArray, pieceStartLocation, pieceEndLocation, takenPiece);
    int blackRookAllMovesUser[100][2];
    //BlackRookAllMovesUser(blackRookAllMovesUser, theBoardArray, pieceStartLocation, pieceEndLocation, takenPiece);
    int blackBishopAllMovesUser[100][2];
    //BlackBishopAllMovesUser(blackBishopAllMovesUser, theBoardArray, pieceStartLocation, pieceEndLocation, takenPiece);
    int blackQueenAllMovesUser[100][2];
    //BlackQueenAllMovesUser(blackQueenAllMovesUser, theBoardArray, pieceStartLocation, pieceEndLocation, takenPiece);


    int whitePawnAllMovesCpu[100][2];
    //WhitePawnAllMovesCpu(whitePawnAllMovesCpu, theBoardArray, pieceStartLocation);
    int whiteKingAllMovesCpu[100][2];
    //WhiteKingAllMovesCpu(whiteKingAllMovesCpu, theBoardArray, pieceStartLocation);
    int whiteKnightAllMovesCpu[100][2];
    //WhiteKnightAllMovesCpu(whiteKnightAllMovesCpu, theBoardArray, pieceStartLocation);
    int whiteRookAllMovesCpu[100][2];
    //WhiteRookAllMovesCpu(whiteRookAllMovesCpu, theBoardArray, pieceStartLocation);
    int whiteBishopAllMovesCpu[100][2];
    //WhiteBishopAllMovesCpu(whiteBishopAllMovesCpu, theBoardArray, pieceStartLocation);
    int whiteQueenAllMovesCpu[100][2];
    //WhiteQueenAllMovesCpu(whiteQueenAllMovesCpu, theBoardArray, pieceStartLocation);


    int blackPawnAllMovesCpu[100][2];
    //BlackPawnAllMovesCpu(blackPawnAllMovesCpu, theBoardArray, pieceStartLocation);
    int blackKingAllMovesCpu[100][2];
    //BlackKingAllMovesCpu(blackKingAllMovesCpu, theBoardArray, pieceStartLocation);
    int blackKnightAllMovesCpu[100][2];
    //BlackKnightAllMovesCpu(blackKnightAllMovesCpu, theBoardArray, pieceStartLocation);
    int blackRookAllMovesCpu[100][2];
    //BlackRookAllMovesCpu(blackRookAllMovesCpu, theBoardArray, pieceStartLocation);
    int blackBishopAllMovesCpu[100][2];
    //BlackBishopAllMovesCpu(blackBishopAllMovesCpu, theBoardArray, pieceStartLocation);
    int blackQueenAllMovesCpu[100][2];
    //BlackQueenAllMovesCpu(blackQueenAllMovesCpu, theBoardArray, pieceStartLocation);


    for(int i = 0; i < 500; i++){
        printf("iteration: %d \n", i);
        WhiteCpuPickMove(theBoardArray);
        PrintBoard(theBoardArray);
        BlackCpuPickMove(theBoardArray); 
        PrintBoard(theBoardArray);
    }

    //FindCheckOnWhiteKing(theBoardArray);

    //for(int i = 0; i < 100; i++){
        //for(int j = 0; j < 2; j++){
            //printf("%d ", whiteRookAllMoves[i][j]);
        //}
    //}

    //PrintBoard(theBoardArray);



    return 0;
}




void CreateBoard(char theBoardArray[8][8][4]) {
    // Initialize the board with piece positions
    char initialBoard[8][8][4] = {
        {"**", "**", "WK", "WR", "**", "**", "WN", "WR"},
        {"WP", "**", "**", "WN", "**", "WP", "WP", "WP"},
        {"BB", "**", "WP", "**", "WP", "**", "**", "**"},
        {"**", "**", "**", "**", "**", "**", "**", "**"},
        {"**", "BP", "**", "BP", "**", "BB", "**", "**"},
        {"**", "**", "BN", "**", "**", "**", "**", "BP"},
        {"**", "BP", "BP", "BK", "**", "BP", "BP", "**"},
        {"**", "**", "**", "**", "**", "**", "**", "WQ"}
    };

    // Copy the initial board to the actual board
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            strcpy(theBoardArray[i][j], initialBoard[i][j]);
        }
    }
}




void PrintBoard(char theBoardArray[8][8][4]){
    printf("\n");
    for(int i = 0; i < 8; i++){
        printf("\n");
        for(int j = 0; j < 8; j++){
            printf("%s ", theBoardArray[i][j]);
        }
    }
    printf("\n");

}




int WhitePawnAllMovesUser(int whitePawnAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece, char* upgradedPiece){
    // Checks that the white pawn is where the user says it is
    if(strcmp(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WP") != 0){
        printf("There is no white pawn in that position\n");
        return -1;
    }

    if(pieceStartLocation[0][0] == -1){
        printf("User did not enter a real row for the starting piece location\n");
        return -1;
    }

    if(pieceStartLocation[0][1] == -1){
        printf("User did not enter a real column for the starting piece location\n");
        return -1;
    }

    if(pieceEndLocation[0][0] == -1){
        printf("User did not enter a real row for the ending piece location\n");
        return -1;
    }

    if(pieceEndLocation[0][1] == -1){
        printf("User did not enter a real column for the ending piece location\n");
        return -1;
    }

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 2; j++){
            whitePawnAllMovesUser[i][j] = -1;
        }
    }

    int currIndex = 0;


    // Checks if piece can move forward 2
    // 1. Checks piece is in starting spot
    // 2. Checks 1 spot in front is empty
    // 3. Checks 2 spots in front is empty
    if((pieceStartLocation[0][0] == 6) && (strcmp(theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1]], "**") == 0) && (strcmp(theBoardArray[pieceStartLocation[0][0] - 2][pieceStartLocation[0][1]], "**") == 0)){
        whitePawnAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - 2;
        whitePawnAllMovesUser[currIndex][1] = pieceStartLocation[0][1];
        currIndex++;
    }


    // Checks if piece can move forward 1
    // 1. Checks if 1 spot in front is empty
    if ((strcmp(theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1]], "**") == 0)){
        whitePawnAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - 1;
        whitePawnAllMovesUser[currIndex][1] = pieceStartLocation[0][1];
        currIndex++;
    }


    // Checks if piece can move diagonal left
    // 1. Checks that move is on the board
    // 2. Checks that enemy piece is on spot
    if((pieceStartLocation[0][1] - 1) != -1){
        if (theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1] - 1][0] == 'B'){
            whitePawnAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - 1;
            whitePawnAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - 1;
            currIndex++;
        }
    }


    // Checks if piece can move diagonal right
    // 1. Checks that move is on the board
    // 2. Checks that enemy piece is on spot
    if((pieceStartLocation[0][1] + 1) != 8){
        if (theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1] + 1][0] == 'B'){

            whitePawnAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - 1;
            whitePawnAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + 1;
            currIndex++;
        }
    }

    bool moveIsPossible = false;

    // Sees if the location the player wants to move to is possible
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 1; j++){
            if((whitePawnAllMovesUser[i][j] == pieceEndLocation[0][0]) && (whitePawnAllMovesUser[i][j+1] == pieceEndLocation[0][1])){
                moveIsPossible = true;
            }
        }
    }

    // If we are not taking a piece
    if(strcmp(takenPiece, "") == 0){
        // If move is possible
        if(moveIsPossible == true){

            // If pawn isn't at other end of the board and the player wants to upgrade it
            if(pieceEndLocation[0][0] != 0 && strcmp(upgradedPiece, "") != 0){
                printf("Piece cannot be upgraded\n");
                return -1;
            }

            // If at other end of board and user didn't set a piece to upgrade it to
            if(pieceEndLocation[0][0] == 0 && strcmp(upgradedPiece, "") == 0){
                printf("User didn't specify what to upgrade the piece to\n");
                return -1;
            }

            // Upgrade to Rook
            if(pieceEndLocation[0][0] == 0 && strcmp(upgradedPiece, "WR") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WR");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                printf("Move made\n");
                return 1;
            // Upgrade to Knight
            }else if(pieceEndLocation[0][0] == 0 && strcmp(upgradedPiece, "WN") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WN");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                printf("Move made\n");
                return 1;
            // Upgrade to Bishop 
            }else if(pieceEndLocation[0][0] == 0 && strcmp(upgradedPiece, "WB") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WB");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**"); 
                printf("Move made\n");
                return 1;
            // Upgrade to Queen 
            }else if(pieceEndLocation[0][0] == 0 && strcmp(upgradedPiece, "WQ") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WQ");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**"); 
                printf("Move made\n");
                return 1;
            }else{
                printf("User did not enter a valid piece to upgrade to\n");
                return -1;
            }

            // Move the piece
            strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WP");
            strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
            printf("Move made\n");
            return 1;
        }else{
            printf("That is not a possible move\n");
            return -1;
        }
    // If we are taking a piece
    }else{
         // If move is possible
        if(moveIsPossible == true){
            // Checks that the piece the user wants to take is actually there
            if(strcmp(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], takenPiece) == 0){
            // If pawn isn't at other end of the board and the player wants to upgrade it
            if(pieceEndLocation[0][0] != 0 && strcmp(upgradedPiece, "") != 0){
                printf("Piece cannot be upgraded\n");
                return -1;
            }

            // If at other end of board and user didn't set a piece to upgrade it to
            if(pieceEndLocation[0][0] == 0 && strcmp(upgradedPiece, "") == 0){
                printf("User didn't specify what to upgrade the piece to\n");
                return -1;
            }

            // Upgrade to Rook
            if(pieceEndLocation[0][0] == 0 && strcmp(upgradedPiece, "WR") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WR");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                printf("Move made\n");
                return 1;
            // Upgrade to Knight
            }else if(pieceEndLocation[0][0] == 0 && strcmp(upgradedPiece, "WN") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WN");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                printf("Move made\n");
                return 1;
            // Upgrade to Bishop 
            }else if(pieceEndLocation[0][0] == 0 && strcmp(upgradedPiece, "WB") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WB");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**"); 
                printf("Move made\n");
                return 1;
            // Upgrade to Queen 
            }else if(pieceEndLocation[0][0] == 0 && strcmp(upgradedPiece, "WQ") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WQ");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**"); 
                printf("Move made\n");
                return 1;
            }else{
                printf("User did not enter a valid piece to upgrade to\n");
                return -1;
            }

                // Take the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WP");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                printf("Move made\n");
                return 1;
            }else{
                printf("The piece you want to take is not there\n");
                return -1;
            }
        }else{
            printf("That is not a possible move\n");
            return -1;
        }

    }


}




int WhiteKingAllMovesUser(int whiteKingAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece){
    // Checks that the white king is where the user says it is
    if(strcmp(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WK") != 0){
        printf("There is no white king in that position\n");
        return -1;
    }

    if(pieceStartLocation[0][0] == -1){
        printf("User did not enter a real row for the starting piece location\n");
        return -1;
    }

    if(pieceStartLocation[0][1] == -1){
        printf("User did not enter a real column for the starting piece location\n");
        return -1;
    }

    if(pieceEndLocation[0][0] == -1){
        printf("User did not enter a real row for the ending piece location\n");
        return -1;
    }

    if(pieceEndLocation[0][1] == -1){
        printf("User did not enter a real column for the ending piece location\n");
        return -1;
    }

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 2; j++){
            whiteKingAllMovesUser[i][j] = -1;
        }
    }

    int currIndex = 0;


    // Checks if piece can move forward 1
    // 1. Checks moving up 1 is still on board
    // 2. Checks if 1 spot forward doesn't have a white piece
    if(pieceStartLocation[0][0] != 0){
        if (theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1]][0] != 'W'){
        whiteKingAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - 1;
        whiteKingAllMovesUser[currIndex][1] = pieceStartLocation[0][1];
        currIndex++;
        }  
    }

    // 1. Checks moving right 1 is still on board
    // 2. Checks if 1 spot right doesn't have a white piece
    if(pieceStartLocation[0][1] != 7){
        if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] + 1][0] != 'W'){
        whiteKingAllMovesUser[currIndex][0] = pieceStartLocation[0][0];
        whiteKingAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + 1;
        currIndex++;
        }  
    }

    // 1. Checks moving down 1 is still on board
    // 2. Checks if 1 spot down doesn't have a white piece
    if(pieceStartLocation[0][0] != 7){
        if (theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1]][0] != 'W'){
        whiteKingAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + 1;
        whiteKingAllMovesUser[currIndex][1] = pieceStartLocation[0][1];
        currIndex++;
        }  
    }
    
    // 1. Checks moving left 1 is still on board
    // 2. Checks if 1 spot down doesn't have a white piece
    if(pieceStartLocation[0][1] != 0){
        if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] -1][0] != 'W'){
        whiteKingAllMovesUser[currIndex][0] = pieceStartLocation[0][0];
        whiteKingAllMovesUser[currIndex][1] = pieceStartLocation[0][1] -1;
        currIndex++;
        }  
    }

    // 1. Checks moving up and left 1 is still on board
    // 2. Checks if 1 up and left doesn't have a white piece
    if(pieceStartLocation[0][0] != 0 && pieceStartLocation[0][1] != 0){
        if (theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1] - 1][0] != 'W'){
        whiteKingAllMovesUser[currIndex][0] = pieceStartLocation[0][0] -1;
        whiteKingAllMovesUser[currIndex][1] = pieceStartLocation[0][1] -1;
        currIndex++;
        }  
    }

    // 1. Checks moving up and right 1 is still on board
    // 2. Checks if 1 up and right doesn't have a white piece
    if(pieceStartLocation[0][0] != 0 && pieceStartLocation[0][1] != 7){
        if (theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1] + 1][0] != 'W'){
        whiteKingAllMovesUser[currIndex][0] = pieceStartLocation[0][0] -1;
        whiteKingAllMovesUser[currIndex][1] = pieceStartLocation[0][1] +1;
        currIndex++;
        }  
    }

    // 1. Checks moving down and right 1 is still on board
    // 2. Checks if 1 down and right doesn't have a white piece
    if(pieceStartLocation[0][0] != 7 && pieceStartLocation[0][1] != 7){
        if (theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1] + 1][0] != 'W'){
        whiteKingAllMovesUser[currIndex][0] = pieceStartLocation[0][0] +1;
        whiteKingAllMovesUser[currIndex][1] = pieceStartLocation[0][1] +1;
        currIndex++;
        }  
    }

    // 1. Checks moving down and left 1 is still on board
    // 2. Checks if 1 down and left doesn't have a white piece
    if(pieceStartLocation[0][0] != 7 && pieceStartLocation[0][1] != 0){
        if (theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1] - 1][0] != 'W'){
        whiteKingAllMovesUser[currIndex][0] = pieceStartLocation[0][0] +1;
        whiteKingAllMovesUser[currIndex][1] = pieceStartLocation[0][1] -1;
        currIndex++;
        }  
    }


    bool moveIsPossible = false;

    // Sees if the location the player wants to move to is possible
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 1; j++){
            if((whiteKingAllMovesUser[i][j] == pieceEndLocation[0][0]) && (whiteKingAllMovesUser[i][j+1] == pieceEndLocation[0][1])){
                moveIsPossible = true;
            }
        }
    }

    // If we are not taking a piece
    if(strcmp(takenPiece, "") == 0){
        // If move is possible
        if(moveIsPossible == true){
            // Move the piece
            strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WK");
            strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
            printf("Move made\n");
            return 1;
        }else{
            printf("That is not a possible move\n");
            return -1;
        }
    // If we are taking a piece
    }else{
         // If move is possible
        if(moveIsPossible == true){
            // Checks that the piece the user wants to take is actually there
            if(strcmp(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], takenPiece) == 0){
                // Take the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WK");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                printf("Move made\n");
                return 1;
            }else{
                printf("The piece you want to take is not there\n");
                return -1;
            }
        }else{
            printf("That is not a possible move\n");
            return -1;
        }

    }

}





int WhiteKnightAllMovesUser(int whiteKnightAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece){
    // Checks that the white knight is where the user says it is
    if(strcmp(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WN") != 0){
        printf("There is no white knight in that position\n");
        return -1;
    }

    if(pieceStartLocation[0][0] == -1){
        printf("User did not enter a real row for the starting piece location\n");
        return -1;
    }

    if(pieceStartLocation[0][1] == -1){
        printf("User did not enter a real column for the starting piece location\n");
        return -1;
    }

    if(pieceEndLocation[0][0] == -1){
        printf("User did not enter a real row for the ending piece location\n");
        return -1;
    }

    if(pieceEndLocation[0][1] == -1){
        printf("User did not enter a real column for the ending piece location\n");
        return -1;
    }

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 2; j++){
            whiteKnightAllMovesUser[i][j] = -1;
        }
    }

    int currIndex = 0;


    // Checks if piece can up 1, right 2
    // 1. Checks moving up 1, right 2 is still on board
    // 2. Checks if up 1, right 2 doesn't have a white piece
    if(pieceStartLocation[0][0] != 0 && pieceStartLocation[0][1] < 6){
        if (theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1] + 2][0] != 'W'){
            whiteKnightAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - 1;
            whiteKnightAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + 2;
            currIndex++;
        }  
    }


    // Checks if piece can up 2, right 1
    // 1. Checks moving up 2, right 1 is still on board
    // 2. Checks if up 2, right 1 doesn't have a white piece
    if(pieceStartLocation[0][0] > 1 && pieceStartLocation[0][1] != 7){
        if (theBoardArray[pieceStartLocation[0][0] - 2][pieceStartLocation[0][1] + 1][0] != 'W'){
            whiteKnightAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - 2;
            whiteKnightAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + 1;
            currIndex++;
        }  
    }


    // Checks if piece can down 1, right 2
    // 1. Checks moving down 1, right 2 is still on board
    // 2. Checks if down 1, right 2 doesn't have a white piece
    if(pieceStartLocation[0][0] != 7 && pieceStartLocation[0][1] < 6){
        if (theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1] + 2][0] != 'W'){
            whiteKnightAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + 1;
            whiteKnightAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + 2;
            currIndex++;
        }  
    }
    

    // Checks if piece can down 2, right 1
    // 1. Checks moving down 2, right 1 is still on board
    // 2. Checks if down 2, right 1 doesn't have a white piece
    if(pieceStartLocation[0][0] < 6 && pieceStartLocation[0][1] != 7){
        if (theBoardArray[pieceStartLocation[0][0] + 2][pieceStartLocation[0][1] + 1][0] != 'W'){
            whiteKnightAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + 2;
            whiteKnightAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + 1;
            currIndex++;
        }  
    }
    

    // Checks if piece can up 1, left 2
    // 1. Checks moving up 1, left 2 is still on board
    // 2. Checks if up 1, left 2 doesn't have a white piece
    if(pieceStartLocation[0][0] != 0 && pieceStartLocation[0][1] > 1){
        if (theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1] - 2][0] != 'W'){
            whiteKnightAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - 1;
            whiteKnightAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - 2;
            currIndex++;
        }  
    }


    // Checks if piece can up 2, left 1
    // 1. Checks moving up 2, left 1 is still on board
    // 2. Checks if up 2, left 1 doesn't have a white piece
    if(pieceStartLocation[0][0] > 1 && pieceStartLocation[0][1] != 0){
        if (theBoardArray[pieceStartLocation[0][0] - 2 ][pieceStartLocation[0][1] - 1][0] != 'W'){
            whiteKnightAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - 2;
            whiteKnightAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - 1;
            currIndex++;
        }  
    }


    // Checks if piece can down 1, left 2
    // 1. Checks moving down 1, left 2 is still on board
    // 2. Checks if down 1, left 2 doesn't have a white piece
    if(pieceStartLocation[0][0] != 7 && pieceStartLocation[0][1] > 1){
        if (theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1] - 2][0] != 'W'){
            whiteKnightAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + 1;
            whiteKnightAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - 2;
            currIndex++;
        }  
    }


    // Checks if piece can down 2, left 1
    // 1. Checks moving down 2, left 1 is still on board
    // 2. Checks if down 2, left 1 doesn't have a white piece
    if(pieceStartLocation[0][0] < 6 && pieceStartLocation[0][1] != 0){
        if (theBoardArray[pieceStartLocation[0][0] + 2][pieceStartLocation[0][1] - 1][0] != 'W'){
            whiteKnightAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + 2;
            whiteKnightAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - 1;
            currIndex++;
        }  
    }

    
    bool moveIsPossible = false;

    // Sees if the location the player wants to move to is possible
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 1; j++){
            if((whiteKnightAllMovesUser[i][j] == pieceEndLocation[0][0]) && (whiteKnightAllMovesUser[i][j+1] == pieceEndLocation[0][1])){
                moveIsPossible = true;
            }
        }
    }

    // If we are not taking a piece
    if(strcmp(takenPiece, "") == 0){
        // If move is possible
        if(moveIsPossible == true){
            // Move the piece
            strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WN");
            strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
            printf("Move made\n");
            return 1;
        }else{
            printf("That is not a possible move\n");
            return -1;
        }
    // If we are taking a piece
    }else{
         // If move is possible
        if(moveIsPossible == true){
            // Checks that the piece the user wants to take is actually there
            if(strcmp(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], takenPiece) == 0){
                // Take the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WN");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                printf("Move made\n");
                return 1;
            }else{
                printf("The piece you want to take is not there\n");
                return -1;
            }
        }else{
            printf("That is not a possible move\n");
            return -1;
        }

    }
    
}





int WhiteRookAllMovesUser(int whiteRookAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece){
    // Checks that the white rook is where the user says it is
    if(strcmp(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WR") != 0){
        printf("There is no white rook in that position\n");
        return -1;
    }

    if(pieceStartLocation[0][0] == -1){
        printf("User did not enter a real row for the starting piece location\n");
        return -1;
    }

    if(pieceStartLocation[0][1] == -1){
        printf("User did not enter a real column for the starting piece location\n");
        return -1;
    }

    if(pieceEndLocation[0][0] == -1){
        printf("User did not enter a real row for the ending piece location\n");
        return -1;
    }

    if(pieceEndLocation[0][1] == -1){
        printf("User did not enter a real column for the ending piece location\n");
        return -1;
    }

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 2; j++){
            whiteRookAllMovesUser[i][j] = -1;
        }
    }

    int currIndex = 0;
    int currIndex2 = 1;

    bool endOfRoad = false;


    // Checks how far piece can go up
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1]][0] == '*'){
            whiteRookAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            whiteRookAllMovesUser[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1]][0] == 'B'){
            whiteRookAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            whiteRookAllMovesUser[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1]][0] == 'W'){
            endOfRoad = true;
        }
    }

    
    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go left
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][1] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] -currIndex2][0] == '*'){
            whiteRookAllMovesUser[currIndex][0] = pieceStartLocation[0][0];
            whiteRookAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] -currIndex2][0] == 'B'){
            whiteRookAllMovesUser[currIndex][0] = pieceStartLocation[0][0];
            whiteRookAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] - currIndex2][0] == 'W'){
            endOfRoad = true;
        }
    }



    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go right
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][1] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] +currIndex2][0] == '*'){
            whiteRookAllMovesUser[currIndex][0] = pieceStartLocation[0][0];
            whiteRookAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] +currIndex2][0] == 'B'){
            whiteRookAllMovesUser[currIndex][0] = pieceStartLocation[0][0];
            whiteRookAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] + currIndex2][0] == 'W'){
            endOfRoad = true;
        }
    }



    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go down
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1]][0] == '*'){
            whiteRookAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            whiteRookAllMovesUser[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1]][0] == 'B'){
            whiteRookAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            whiteRookAllMovesUser[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]  + currIndex2][pieceStartLocation[0][1]][0] == 'W'){
            endOfRoad = true;
        }
    }
    
   

    
    bool moveIsPossible = false;

    // Sees if the location the player wants to move to is possible
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 1; j++){
            if((whiteRookAllMovesUser[i][j] == pieceEndLocation[0][0]) && (whiteRookAllMovesUser[i][j+1] == pieceEndLocation[0][1])){
                moveIsPossible = true;
            }
        }
    }

    // If we are not taking a piece
    if(strcmp(takenPiece, "") == 0){
        // If move is possible
        if(moveIsPossible == true){
            // Move the piece
            strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WR");
            strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
            printf("Move made\n");
            return 1;
        }else{
            printf("That is not a possible move\n");
            return -1;
        }
    // If we are taking a piece
    }else{
         // If move is possible
        if(moveIsPossible == true){
            // Checks that the piece the user wants to take is actually there
            if(strcmp(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], takenPiece) == 0){
                // Take the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WR");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                printf("Move made\n");
                return 1;
            }else{
                printf("The piece you want to take is not there\n");
                return -1;
            }
        }else{
            printf("That is not a possible move\n");
            return -1;
        }

    }
}




int WhiteBishopAllMovesUser(int whiteBishopAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece){
    // Checks that the white bishop is where the user says it is
    if(strcmp(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WB") != 0){
        printf("There is no white bishop in that position\n");
        return -1;
    }

    if(pieceStartLocation[0][0] == -1){
        printf("User did not enter a real row for the starting piece location\n");
        return -1;
    }

    if(pieceStartLocation[0][1] == -1){
        printf("User did not enter a real column for the starting piece location\n");
        return -1;
    }

    if(pieceEndLocation[0][0] == -1){
        printf("User did not enter a real row for the ending piece location\n");
        return -1;
    }

    if(pieceEndLocation[0][1] == -1){
        printf("User did not enter a real column for the ending piece location\n");
        return -1;
    }

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 2; j++){
            whiteBishopAllMovesUser[i][j] = -1;
        }
    }

    int currIndex = 0;
    int currIndex2 = 1;

    bool endOfRoad = false;


    // Checks how far piece can go up and right
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] - currIndex2) == -1 || (pieceStartLocation[0][1] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] + currIndex2][0] == '*'){
            whiteBishopAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            whiteBishopAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'B'){
            whiteBishopAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            whiteBishopAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'W'){
            endOfRoad = true;
        }
    }


    
    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go down and right
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] + currIndex2) == 8 || (pieceStartLocation[0][1] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] + currIndex2][0] == '*'){
            whiteBishopAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            whiteBishopAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'B'){
            whiteBishopAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            whiteBishopAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'W'){
            endOfRoad = true;
        }
    }
    
    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go down and left
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] + currIndex2) == 8 || (pieceStartLocation[0][1] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] - currIndex2][0] == '*'){
            whiteBishopAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            whiteBishopAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'B'){
            whiteBishopAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            whiteBishopAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'W'){
            endOfRoad = true;
        }
    }


    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go up and left
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] - currIndex2) == -1 || (pieceStartLocation[0][1] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] - currIndex2][0] == '*'){
            whiteBishopAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            whiteBishopAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'B'){
            whiteBishopAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            whiteBishopAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'W'){
            endOfRoad = true;
        }
    }

    
    bool moveIsPossible = false;

    // Sees if the location the player wants to move to is possible
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 1; j++){
            if((whiteBishopAllMovesUser[i][j] == pieceEndLocation[0][0]) && (whiteBishopAllMovesUser[i][j+1] == pieceEndLocation[0][1])){
                moveIsPossible = true;
            }
        }
    }

    // If we are not taking a piece
    if(strcmp(takenPiece, "") == 0){
        // If move is possible
        if(moveIsPossible == true){
            // Move the piece
            strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WB");
            strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
            printf("Move made\n");
            return 1;
        }else{
            printf("That is not a possible move\n");
            return -1;
        }
    // If we are taking a piece
    }else{
         // If move is possible
        if(moveIsPossible == true){
            // Checks that the piece the user wants to take is actually there
            if(strcmp(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], takenPiece) == 0){
                // Take the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WB");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                printf("Move made\n");
                return 1;
            }else{
                printf("The piece you want to take is not there\n");
                return -1;
            }
        }else{
            printf("That is not a possible move\n");
            return -1;
        }

    }
}



int WhiteQueenAllMovesUser(int whiteQueenAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece){
    // Checks that the white rook is where the user says it is
    if(strcmp(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WQ") != 0){
        printf("There is no white queen in that position\n");
        return -1;
    }

    if(pieceStartLocation[0][0] == -1){
        printf("User did not enter a real row for the starting piece location\n");
        return -1;
    }

    if(pieceStartLocation[0][1] == -1){
        printf("User did not enter a real column for the starting piece location\n");
        return -1;
    }

    if(pieceEndLocation[0][0] == -1){
        printf("User did not enter a real row for the ending piece location\n");
        return -1;
    }

    if(pieceEndLocation[0][1] == -1){
        printf("User did not enter a real column for the ending piece location\n");
        return -1;
    }

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 2; j++){
            whiteQueenAllMovesUser[i][j] = -1;
        }
    }

    int currIndex = 0;
    int currIndex2 = 1;

    bool endOfRoad = false;


    // Checks how far piece can go up
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1]][0] == '*'){
            whiteQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            whiteQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1]][0] == 'B'){
            whiteQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            whiteQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1]][0] == 'W'){
            endOfRoad = true;
        }
    }

    
    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go left
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][1] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] -currIndex2][0] == '*'){
            whiteQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0];
            whiteQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] -currIndex2][0] == 'B'){
            whiteQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0];
            whiteQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] - currIndex2][0] == 'W'){
            endOfRoad = true;
        }
    }



    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go right
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][1] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] +currIndex2][0] == '*'){
            whiteQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0];
            whiteQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] +currIndex2][0] == 'B'){
            whiteQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0];
            whiteQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] + currIndex2][0] == 'W'){
            endOfRoad = true;
        }
    }



    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go down
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1]][0] == '*'){
            whiteQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            whiteQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1]][0] == 'B'){
            whiteQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            whiteQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]  + currIndex2][pieceStartLocation[0][1]][0] == 'W'){
            endOfRoad = true;
        }
    }



    currIndex2 = 1;

    endOfRoad = false;



    // Checks how far piece can go up and right
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] - currIndex2) == -1 || (pieceStartLocation[0][1] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] + currIndex2][0] == '*'){
            whiteQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            whiteQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'B'){
            whiteQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            whiteQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'W'){
            endOfRoad = true;
        }
    }


    
    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go down and right
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] + currIndex2) == 8 || (pieceStartLocation[0][1] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] + currIndex2][0] == '*'){
            whiteQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            whiteQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'B'){
            whiteQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            whiteQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'W'){
            endOfRoad = true;
        }
    }
    
    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go down and left
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] + currIndex2) == 8 || (pieceStartLocation[0][1] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] - currIndex2][0] == '*'){
            whiteQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            whiteQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'B'){
            whiteQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            whiteQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'W'){
            endOfRoad = true;
        }
    }


    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go up and left
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] - currIndex2) == -1 || (pieceStartLocation[0][1] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] - currIndex2][0] == '*'){
            whiteQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            whiteQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'B'){
            whiteQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            whiteQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'W'){
            endOfRoad = true;
        }
    }
    
   

    
    bool moveIsPossible = false;

    // Sees if the location the player wants to move to is possible
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 1; j++){
            if((whiteQueenAllMovesUser[i][j] == pieceEndLocation[0][0]) && (whiteQueenAllMovesUser[i][j+1] == pieceEndLocation[0][1])){
                moveIsPossible = true;
            }
        }
    }

    // If we are not taking a piece
    if(strcmp(takenPiece, "") == 0){
        // If move is possible
        if(moveIsPossible == true){
            // Move the piece
            strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WQ");
            strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
            printf("Move made\n");
            return 1;
        }else{
            printf("That is not a possible move\n");
            return -1;
        }
    // If we are taking a piece
    }else{
         // If move is possible
        if(moveIsPossible == true){
            // Checks that the piece the user wants to take is actually there
            if(strcmp(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], takenPiece) == 0){
                // Take the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WQ");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                printf("Move made\n");
                return 1;
            }else{
                printf("The piece you want to take is not there\n");
                return -1;
            }
        }else{
            printf("That is not a possible move\n");
            return -1;
        }

    }
}









void ConvertLocationToIndex(char* theLocation, int pieceLocation[1][2]){
    pieceLocation[0][0] = -1;
    pieceLocation[0][1] = -1;

    if(theLocation[1] == '8'){
        pieceLocation[0][0] = 0;
    }else if(theLocation[1] == '7'){
        pieceLocation[0][0] = 1;
    }else if(theLocation[1] == '6'){
        pieceLocation[0][0] = 2;
    }else if(theLocation[1] == '5'){
        pieceLocation[0][0] = 3;
    }else if(theLocation[1] == '4'){
        pieceLocation[0][0] = 4;
    }else if(theLocation[1] == '3'){
        pieceLocation[0][0] = 5;
    }else if(theLocation[1] == '2'){
        pieceLocation[0][0] = 6;
    }else if(theLocation[1] == '1'){
        pieceLocation[0][0] = 7;
    }else{
        pieceLocation[0][0] = -1; 
    }

    
    if(theLocation[0] == 'A'){
        pieceLocation[0][1] = 0;
    }else if(theLocation[0] == 'B'){
        pieceLocation[0][1] = 1;
    }else if(theLocation[0] == 'C'){
        pieceLocation[0][1] = 2;
    }else if(theLocation[0] == 'D'){
        pieceLocation[0][1] = 3;
    }else if(theLocation[0] == 'E'){
        pieceLocation[0][1] = 4;
    }else if(theLocation[0] == 'F'){
        pieceLocation[0][1] = 5;
    }else if(theLocation[0] == 'G'){
        pieceLocation[0][1] = 6;
    }else if(theLocation[0] == 'H'){
        pieceLocation[0][1] = 7;
    }else{
        pieceLocation[0][1] = -1;
    }

    //printf("%d ", pieceLocation[0][0]);
    //printf("%d ", pieceLocation[0][1]);

}




int BlackPawnAllMovesUser(int blackPawnAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece, char* upgradedPiece){
    // Checks that the black pawn is where the user says it is
    if(strcmp(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BP") != 0){
        printf("There is no black pawn in that position\n");
        return -1;
    }

    if(pieceStartLocation[0][0] == -1){
        printf("User did not enter a real row for the starting piece location\n");
        return -1;
    }

    if(pieceStartLocation[0][1] == -1){
        printf("User did not enter a real column for the starting piece location\n");
        return -1;
    }

    if(pieceEndLocation[0][0] == -1){
        printf("User did not enter a real row for the ending piece location\n");
        return -1;
    }

    if(pieceEndLocation[0][1] == -1){
        printf("User did not enter a real column for the ending piece location\n");
        return -1;
    }

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 2; j++){
            blackPawnAllMovesUser[i][j] = -1;
        }
    }

    int currIndex = 0;


    // Checks if piece can move forward 2
    // 1. Checks piece is in starting spot
    // 2. Checks 1 spot in front is empty
    // 3. Checks 2 spots in front is empty
    if((pieceStartLocation[0][0] == 1) && (strcmp(theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1]], "**") == 0) && (strcmp(theBoardArray[pieceStartLocation[0][0] + 2][pieceStartLocation[0][1]], "**") == 0)){
        blackPawnAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + 2;
        blackPawnAllMovesUser[currIndex][1] = pieceStartLocation[0][1];
        currIndex++;
    }


    // Checks if piece can move forward 1
    // 1. Checks if 1 spot in front is empty
    if ((strcmp(theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1]], "**") == 0)){
        blackPawnAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + 1;
        blackPawnAllMovesUser[currIndex][1] = pieceStartLocation[0][1];
        currIndex++;
    }


    // Checks if piece can move diagonal left
    // 1. Checks that move is on the board
    // 2. Checks that enemy piece is on spot
    if((pieceStartLocation[0][1] - 1) != -1){
        if (theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1] - 1][0] == 'W'){
            blackPawnAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + 1;
            blackPawnAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - 1;
            currIndex++;
        }
    }


    // Checks if piece can move diagonal right
    // 1. Checks that move is on the board
    // 2. Checks that enemy piece is on spot
    if((pieceStartLocation[0][1] + 1) != 8){
        if (theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1] + 1][0] == 'W'){

            blackPawnAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + 1;
            blackPawnAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + 1;
            currIndex++;
        }
    }

    bool moveIsPossible = false;

    // Sees if the location the player wants to move to is possible
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 1; j++){
            if((blackPawnAllMovesUser[i][j] == pieceEndLocation[0][0]) && (blackPawnAllMovesUser[i][j+1] == pieceEndLocation[0][1])){
                moveIsPossible = true;
            }
        }
    }

    // If we are not taking a piece
    if(strcmp(takenPiece, "") == 0){
        // If move is possible
        if(moveIsPossible == true){

            // If pawn isn't at other end of the board and the player wants to upgrade it
            if(pieceEndLocation[0][0] != 7 && strcmp(upgradedPiece, "") != 0){
                printf("Piece cannot be upgraded\n");
                return -1;
            }

            // If at other end of board and user didn't set a piece to upgrade it to
            if(pieceEndLocation[0][0] == 7 && strcmp(upgradedPiece, "") == 0){
                printf("User didn't specify what to upgrade the piece to\n");
                return -1;
            }

            // Upgrade to Rook
            if(pieceEndLocation[0][0] == 7 && strcmp(upgradedPiece, "BR") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BR");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                printf("Move made\n");
                return 1;
            // Upgrade to Knight
            }else if(pieceEndLocation[0][0] == 7 && strcmp(upgradedPiece, "BN") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BN");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                printf("Move made\n");
                return 1;
            // Upgrade to Bishop 
            }else if(pieceEndLocation[0][0] == 7 && strcmp(upgradedPiece, "BB") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BB");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**"); 
                printf("Move made\n");
                return 1;
            // Upgrade to Queen 
            }else if(pieceEndLocation[0][0] == 7 && strcmp(upgradedPiece, "BQ") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BQ");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**"); 
                printf("Move made\n");
                return 1;
            }else{
                printf("User did not enter a valid piece to upgrade to\n");
                return -1;
            }

            // Move the piece
            strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BP");
            strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
            printf("Move made\n");
            return 1;
        }else{
            printf("That is not a possible move\n");
            return -1;
        }
    // If we are taking a piece
    }else{
         // If move is possible
        if(moveIsPossible == true){
            // Checks that the piece the user wants to take is actually there
            if(strcmp(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], takenPiece) == 0){
            // If pawn isn't at other end of the board and the player wants to upgrade it
            if(pieceEndLocation[0][0] != 7 && strcmp(upgradedPiece, "") != 0){
                printf("Piece cannot be upgraded\n");
                return -1;
            }

            // If at other end of board and user didn't set a piece to upgrade it to
            if(pieceEndLocation[0][0] == 7 && strcmp(upgradedPiece, "") == 0){
                printf("User didn't specify what to upgrade the piece to\n");
                return -1;
            }

            // Upgrade to Rook
            if(pieceEndLocation[0][0] == 7 && strcmp(upgradedPiece, "BR") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BR");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                printf("Move made\n");
                return 1;
            // Upgrade to Knight
            }else if(pieceEndLocation[0][0] == 7 && strcmp(upgradedPiece, "BN") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BN");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                printf("Move made\n");
                return 1;
            // Upgrade to Bishop 
            }else if(pieceEndLocation[0][0] == 7 && strcmp(upgradedPiece, "BB") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BB");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**"); 
                printf("Move made\n");
                return 1;
            // Upgrade to Queen 
            }else if(pieceEndLocation[0][0] == 7 && strcmp(upgradedPiece, "BQ") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BQ");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**"); 
                printf("Move made\n");
                return 1;
            }else{
                printf("User did not enter a valid piece to upgrade to\n");
                return -1;
            }

                // Take the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BP");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                printf("Move made\n");
                return 1;
            }else{
                printf("The piece you want to take is not there\n");
                return -1;
            }
        }else{
            printf("That is not a possible move\n");
            return -1;
        }

    }


}




int BlackKingAllMovesUser(int blackKingAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece){
    // Checks that the black king is where the user says it is
    if(strcmp(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WK") != 0){
        printf("There is no black king in that position\n");
        return -1;
    }

    if(pieceStartLocation[0][0] == -1){
        printf("User did not enter a real row for the starting piece location\n");
        return -1;
    }

    if(pieceStartLocation[0][1] == -1){
        printf("User did not enter a real column for the starting piece location\n");
        return -1;
    }

    if(pieceEndLocation[0][0] == -1){
        printf("User did not enter a real row for the ending piece location\n");
        return -1;
    }

    if(pieceEndLocation[0][1] == -1){
        printf("User did not enter a real column for the ending piece location\n");
        return -1;
    }

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 2; j++){
            blackKingAllMovesUser[i][j] = -1;
        }
    }

    int currIndex = 0;


    // Checks if piece can move forward 1
    // 1. Checks moving up 1 is still on board
    // 2. Checks if 1 spot forward doesn't have a black piece
    if(pieceStartLocation[0][0] != 0){
        if (theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1]][0] != 'B'){
        blackKingAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - 1;
        blackKingAllMovesUser[currIndex][1] = pieceStartLocation[0][1];
        currIndex++;
        }  
    }

    // 1. Checks moving right 1 is still on board
    // 2. Checks if 1 spot right doesn't have a black piece
    if(pieceStartLocation[0][1] != 7){
        if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] + 1][0] != 'B'){
        blackKingAllMovesUser[currIndex][0] = pieceStartLocation[0][0];
        blackKingAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + 1;
        currIndex++;
        }  
    }

    // 1. Checks moving down 1 is still on board
    // 2. Checks if 1 spot down doesn't have a black piece
    if(pieceStartLocation[0][0] != 7){
        if (theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1]][0] != 'B'){
        blackKingAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + 1;
        blackKingAllMovesUser[currIndex][1] = pieceStartLocation[0][1];
        currIndex++;
        }  
    }
    
    // 1. Checks moving left 1 is still on board
    // 2. Checks if 1 spot down doesn't have a black piece
    if(pieceStartLocation[0][1] != 0){
        if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] -1][0] != 'B'){
        blackKingAllMovesUser[currIndex][0] = pieceStartLocation[0][0];
        blackKingAllMovesUser[currIndex][1] = pieceStartLocation[0][1] -1;
        currIndex++;
        }  
    }

    // 1. Checks moving up and left 1 is still on board
    // 2. Checks if 1 up and left doesn't have a black piece
    if(pieceStartLocation[0][0] != 0 && pieceStartLocation[0][1] != 0){
        if (theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1] - 1][0] != 'B'){
        blackKingAllMovesUser[currIndex][0] = pieceStartLocation[0][0] -1;
        blackKingAllMovesUser[currIndex][1] = pieceStartLocation[0][1] -1;
        currIndex++;
        }  
    }

    // 1. Checks moving up and right 1 is still on board
    // 2. Checks if 1 up and right doesn't have a black piece
    if(pieceStartLocation[0][0] != 0 && pieceStartLocation[0][1] != 7){
        if (theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1] + 1][0] != 'B'){
        blackKingAllMovesUser[currIndex][0] = pieceStartLocation[0][0] -1;
        blackKingAllMovesUser[currIndex][1] = pieceStartLocation[0][1] +1;
        currIndex++;
        }  
    }

    // 1. Checks moving down and right 1 is still on board
    // 2. Checks if 1 down and right doesn't have a black piece
    if(pieceStartLocation[0][0] != 7 && pieceStartLocation[0][1] != 7){
        if (theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1] + 1][0] != 'B'){
        blackKingAllMovesUser[currIndex][0] = pieceStartLocation[0][0] +1;
        blackKingAllMovesUser[currIndex][1] = pieceStartLocation[0][1] +1;
        currIndex++;
        }  
    }

    // 1. Checks moving down and left 1 is still on board
    // 2. Checks if 1 down and left doesn't have a black piece
    if(pieceStartLocation[0][0] != 7 && pieceStartLocation[0][1] != 0){
        if (theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1] - 1][0] != 'B'){
        blackKingAllMovesUser[currIndex][0] = pieceStartLocation[0][0] +1;
        blackKingAllMovesUser[currIndex][1] = pieceStartLocation[0][1] -1;
        currIndex++;
        }  
    }


    bool moveIsPossible = false;

    // Sees if the location the player wants to move to is possible
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 1; j++){
            if((blackKingAllMovesUser[i][j] == pieceEndLocation[0][0]) && (blackKingAllMovesUser[i][j+1] == pieceEndLocation[0][1])){
                moveIsPossible = true;
            }
        }
    }

    // If we are not taking a piece
    if(strcmp(takenPiece, "") == 0){
        // If move is possible
        if(moveIsPossible == true){
            // Move the piece
            strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BK");
            strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
            printf("Move made\n");
            return 1;
        }else{
            printf("That is not a possible move\n");
            return -1;
        }
    // If we are taking a piece
    }else{
         // If move is possible
        if(moveIsPossible == true){
            // Checks that the piece the user wants to take is actually there
            if(strcmp(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], takenPiece) == 0){
                // Take the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BK");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                printf("Move made\n");
                return 1;
            }else{
                printf("The piece you want to take is not there\n");
                return -1;
            }
        }else{
            printf("That is not a possible move\n");
            return -1;
        }

    }

}



int BlackKnightAllMovesUser(int blackKnightAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece){
    // Checks that the black knight is where the user says it is
    if(strcmp(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BN") != 0){
        printf("There is no black knight in that position\n");
        return -1;
    }

    if(pieceStartLocation[0][0] == -1){
        printf("User did not enter a real row for the starting piece location\n");
        return -1;
    }

    if(pieceStartLocation[0][1] == -1){
        printf("User did not enter a real column for the starting piece location\n");
        return -1;
    }

    if(pieceEndLocation[0][0] == -1){
        printf("User did not enter a real row for the ending piece location\n");
        return -1;
    }

    if(pieceEndLocation[0][1] == -1){
        printf("User did not enter a real column for the ending piece location\n");
        return -1;
    }

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 2; j++){
            blackKnightAllMovesUser[i][j] = -1;
        }
    }

    int currIndex = 0;


    // Checks if piece can up 1, right 2
    // 1. Checks moving up 1, right 2 is still on board
    // 2. Checks if up 1, right 2 doesn't have a black piece
    if(pieceStartLocation[0][0] != 0 && pieceStartLocation[0][1] < 6){
        if (theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1] + 2][0] != 'B'){
            blackKnightAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - 1;
            blackKnightAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + 2;
            currIndex++;
        }  
    }


    // Checks if piece can up 2, right 1
    // 1. Checks moving up 2, right 1 is still on board
    // 2. Checks if up 2, right 1 doesn't have a black piece
    if(pieceStartLocation[0][0] > 1 && pieceStartLocation[0][1] != 7){
        if (theBoardArray[pieceStartLocation[0][0] - 2][pieceStartLocation[0][1] + 1][0] != 'B'){
            blackKnightAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - 2;
            blackKnightAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + 1;
            currIndex++;
        }  
    }


    // Checks if piece can down 1, right 2
    // 1. Checks moving down 1, right 2 is still on board
    // 2. Checks if down 1, right 2 doesn't have a black piece
    if(pieceStartLocation[0][0] != 7 && pieceStartLocation[0][1] < 6){
        if (theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1] + 2][0] != 'B'){
            blackKnightAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + 1;
            blackKnightAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + 2;
            currIndex++;
        }  
    }
    

    // Checks if piece can down 2, right 1
    // 1. Checks moving down 2, right 1 is still on board
    // 2. Checks if down 2, right 1 doesn't have a black piece
    if(pieceStartLocation[0][0] < 6 && pieceStartLocation[0][1] != 7){
        if (theBoardArray[pieceStartLocation[0][0] + 2][pieceStartLocation[0][1] + 1][0] != 'B'){
            blackKnightAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + 2;
            blackKnightAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + 1;
            currIndex++;
        }  
    }
    

    // Checks if piece can up 1, left 2
    // 1. Checks moving up 1, left 2 is still on board
    // 2. Checks if up 1, left 2 doesn't have a black piece
    if(pieceStartLocation[0][0] != 0 && pieceStartLocation[0][1] > 1){
        if (theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1] - 2][0] != 'B'){
            blackKnightAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - 1;
            blackKnightAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - 2;
            currIndex++;
        }  
    }


    // Checks if piece can up 2, left 1
    // 1. Checks moving up 2, left 1 is still on board
    // 2. Checks if up 2, left 1 doesn't have a black piece
    if(pieceStartLocation[0][0] > 1 && pieceStartLocation[0][1] != 0){
        if (theBoardArray[pieceStartLocation[0][0] - 2 ][pieceStartLocation[0][1] - 1][0] != 'B'){
            blackKnightAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - 2;
            blackKnightAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - 1;
            currIndex++;
        }  
    }


    // Checks if piece can down 1, left 2
    // 1. Checks moving down 1, left 2 is still on board
    // 2. Checks if down 1, left 2 doesn't have a black piece
    if(pieceStartLocation[0][0] != 7 && pieceStartLocation[0][1] > 1){
        if (theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1] - 2][0] != 'B'){
            blackKnightAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + 1;
            blackKnightAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - 2;
            currIndex++;
        }  
    }


    // Checks if piece can down 2, left 1
    // 1. Checks moving down 2, left 1 is still on board
    // 2. Checks if down 2, left 1 doesn't have a black piece
    if(pieceStartLocation[0][0] < 6 && pieceStartLocation[0][1] != 0){
        if (theBoardArray[pieceStartLocation[0][0] + 2][pieceStartLocation[0][1] - 1][0] != 'B'){
            blackKnightAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + 2;
            blackKnightAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - 1;
            currIndex++;
        }  
    }

    
    bool moveIsPossible = false;

    // Sees if the location the player wants to move to is possible
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 1; j++){
            if((blackKnightAllMovesUser[i][j] == pieceEndLocation[0][0]) && (blackKnightAllMovesUser[i][j+1] == pieceEndLocation[0][1])){
                moveIsPossible = true;
            }
        }
    }

    // If we are not taking a piece
    if(strcmp(takenPiece, "") == 0){
        // If move is possible
        if(moveIsPossible == true){
            // Move the piece
            strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BN");
            strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
            printf("Move made\n");
            return 1;
        }else{
            printf("That is not a possible move\n");
            return -1;
        }
    // If we are taking a piece
    }else{
         // If move is possible
        if(moveIsPossible == true){
            // Checks that the piece the user wants to take is actually there
            if(strcmp(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], takenPiece) == 0){
                // Take the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BN");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                printf("Move made\n");
                return 1;
            }else{
                printf("The piece you want to take is not there\n");
                return -1;
            }
        }else{
            printf("That is not a possible move\n");
            return -1;
        }

    }
    
}




int BlackRookAllMovesUser(int blackRookAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece){
    // Checks that the black rook is where the user says it is
    if(strcmp(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BR") != 0){
        printf("There is no white rook in that position\n");
        return -1;
    }

    if(pieceStartLocation[0][0] == -1){
        printf("User did not enter a real row for the starting piece location\n");
        return -1;
    }

    if(pieceStartLocation[0][1] == -1){
        printf("User did not enter a real column for the starting piece location\n");
        return -1;
    }

    if(pieceEndLocation[0][0] == -1){
        printf("User did not enter a real row for the ending piece location\n");
        return -1;
    }

    if(pieceEndLocation[0][1] == -1){
        printf("User did not enter a real column for the ending piece location\n");
        return -1;
    }

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 2; j++){
            blackRookAllMovesUser[i][j] = -1;
        }
    }

    int currIndex = 0;
    int currIndex2 = 1;

    bool endOfRoad = false;


    // Checks how far piece can go up
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1]][0] == '*'){
            blackRookAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            blackRookAllMovesUser[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1]][0] == 'W'){
            blackRookAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            blackRookAllMovesUser[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1]][0] == 'B'){
            endOfRoad = true;
        }
    }

    
    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go left
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][1] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] -currIndex2][0] == '*'){
            blackRookAllMovesUser[currIndex][0] = pieceStartLocation[0][0];
            blackRookAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] -currIndex2][0] == 'W'){
            blackRookAllMovesUser[currIndex][0] = pieceStartLocation[0][0];
            blackRookAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] - currIndex2][0] == 'B'){
            endOfRoad = true;
        }
    }



    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go right
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][1] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] +currIndex2][0] == '*'){
            blackRookAllMovesUser[currIndex][0] = pieceStartLocation[0][0];
            blackRookAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] +currIndex2][0] == 'W'){
            blackRookAllMovesUser[currIndex][0] = pieceStartLocation[0][0];
            blackRookAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] + currIndex2][0] == 'B'){
            endOfRoad = true;
        }
    }



    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go down
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1]][0] == '*'){
            blackRookAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            blackRookAllMovesUser[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1]][0] == 'W'){
            blackRookAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            blackRookAllMovesUser[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]  + currIndex2][pieceStartLocation[0][1]][0] == 'B'){
            endOfRoad = true;
        }
    }
    
   

    
    bool moveIsPossible = false;

    // Sees if the location the player wants to move to is possible
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 1; j++){
            if((blackRookAllMovesUser[i][j] == pieceEndLocation[0][0]) && (blackRookAllMovesUser[i][j+1] == pieceEndLocation[0][1])){
                moveIsPossible = true;
            }
        }
    }

    // If we are not taking a piece
    if(strcmp(takenPiece, "") == 0){
        // If move is possible
        if(moveIsPossible == true){
            // Move the piece
            strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BR");
            strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
            printf("Move made\n");
            return 1;
        }else{
            printf("That is not a possible move\n");
            return -1;
        }
    // If we are taking a piece
    }else{
         // If move is possible
        if(moveIsPossible == true){
            // Checks that the piece the user wants to take is actually there
            if(strcmp(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], takenPiece) == 0){
                // Take the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BR");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                printf("Move made\n");
                return 1;
            }else{
                printf("The piece you want to take is not there\n");
                return -1;
            }
        }else{
            printf("That is not a possible move\n");
            return -1;
        }

    }
}






int BlackBishopAllMovesUser(int blackBishopAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece){
    // Checks that the black bishop is where the user says it is
    if(strcmp(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BB") != 0){
        printf("There is no black bishop in that position\n");
        return -1;
    }

    if(pieceStartLocation[0][0] == -1){
        printf("User did not enter a real row for the starting piece location\n");
        return -1;
    }

    if(pieceStartLocation[0][1] == -1){
        printf("User did not enter a real column for the starting piece location\n");
        return -1;
    }

    if(pieceEndLocation[0][0] == -1){
        printf("User did not enter a real row for the ending piece location\n");
        return -1;
    }

    if(pieceEndLocation[0][1] == -1){
        printf("User did not enter a real column for the ending piece location\n");
        return -1;
    }

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 2; j++){
            blackBishopAllMovesUser[i][j] = -1;
        }
    }

    int currIndex = 0;
    int currIndex2 = 1;

    bool endOfRoad = false;


    // Checks how far piece can go up and right
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] - currIndex2) == -1 || (pieceStartLocation[0][1] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] + currIndex2][0] == '*'){
            blackBishopAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            blackBishopAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'W'){
            blackBishopAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            blackBishopAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'B'){
            endOfRoad = true;
        }
    }


    
    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go down and right
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] + currIndex2) == 8 || (pieceStartLocation[0][1] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] + currIndex2][0] == '*'){
            blackBishopAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            blackBishopAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'W'){
            blackBishopAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            blackBishopAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'B'){
            endOfRoad = true;
        }
    }
    
    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go down and left
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] + currIndex2) == 8 || (pieceStartLocation[0][1] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] - currIndex2][0] == '*'){
            blackBishopAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            blackBishopAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'W'){
            blackBishopAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            blackBishopAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'B'){
            endOfRoad = true;
        }
    }


    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go up and left
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] - currIndex2) == -1 || (pieceStartLocation[0][1] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] - currIndex2][0] == '*'){
            blackBishopAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            blackBishopAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'W'){
            blackBishopAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            blackBishopAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'B'){
            endOfRoad = true;
        }
    }

    
    bool moveIsPossible = false;

    // Sees if the location the player wants to move to is possible
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 1; j++){
            if((blackBishopAllMovesUser[i][j] == pieceEndLocation[0][0]) && (blackBishopAllMovesUser[i][j+1] == pieceEndLocation[0][1])){
                moveIsPossible = true;
            }
        }
    }

    // If we are not taking a piece
    if(strcmp(takenPiece, "") == 0){
        // If move is possible
        if(moveIsPossible == true){
            // Move the piece
            strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BB");
            strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
            printf("Move made\n");
            return 1;
        }else{
            printf("That is not a possible move\n");
            return -1;
        }
    // If we are taking a piece
    }else{
         // If move is possible
        if(moveIsPossible == true){
            // Checks that the piece the user wants to take is actually there
            if(strcmp(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], takenPiece) == 0){
                // Take the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BB");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                printf("Move made\n");
                return 1;
            }else{
                printf("The piece you want to take is not there\n");
                return -1;
            }
        }else{
            printf("That is not a possible move\n");
            return -1;
        }

    }
}





int BlackQueenAllMovesUser(int blackQueenAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece){
    // Checks that the black queen is where the user says it is
    if(strcmp(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BQ") != 0){
        printf("There is no black queen in that position\n");
        return -1;
    }

    if(pieceStartLocation[0][0] == -1){
        printf("User did not enter a real row for the starting piece location\n");
        return -1;
    }

    if(pieceStartLocation[0][1] == -1){
        printf("User did not enter a real column for the starting piece location\n");
        return -1;
    }

    if(pieceEndLocation[0][0] == -1){
        printf("User did not enter a real row for the ending piece location\n");
        return -1;
    }

    if(pieceEndLocation[0][1] == -1){
        printf("User did not enter a real column for the ending piece location\n");
        return -1;
    }

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 2; j++){
            blackQueenAllMovesUser[i][j] = -1;
        }
    }

    int currIndex = 0;
    int currIndex2 = 1;

    bool endOfRoad = false;


    // Checks how far piece can go up
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1]][0] == '*'){
            blackQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            blackQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1]][0] == 'W'){
            blackQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            blackQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1]][0] == 'B'){
            endOfRoad = true;
        }
    }

    
    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go left
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][1] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] -currIndex2][0] == '*'){
            blackQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0];
            blackQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] -currIndex2][0] == 'W'){
            blackQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0];
            blackQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] - currIndex2][0] == 'B'){
            endOfRoad = true;
        }
    }



    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go right
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][1] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] +currIndex2][0] == '*'){
            blackQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0];
            blackQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] +currIndex2][0] == 'W'){
            blackQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0];
            blackQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] + currIndex2][0] == 'B'){
            endOfRoad = true;
        }
    }



    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go down
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1]][0] == '*'){
            blackQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            blackQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1]][0] == 'W'){
            blackQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            blackQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]  + currIndex2][pieceStartLocation[0][1]][0] == 'B'){
            endOfRoad = true;
        }
    }



    currIndex2 = 1;

    endOfRoad = false;



    // Checks how far piece can go up and right
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] - currIndex2) == -1 || (pieceStartLocation[0][1] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] + currIndex2][0] == '*'){
            blackQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            blackQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'W'){
            blackQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            blackQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'B'){
            endOfRoad = true;
        }
    }


    
    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go down and right
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] + currIndex2) == 8 || (pieceStartLocation[0][1] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] + currIndex2][0] == '*'){
            blackQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            blackQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'W'){
            blackQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            blackQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'B'){
            endOfRoad = true;
        }
    }
    
    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go down and left
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] + currIndex2) == 8 || (pieceStartLocation[0][1] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] - currIndex2][0] == '*'){
            blackQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            blackQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'W'){
            blackQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            blackQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'B'){
            endOfRoad = true;
        }
    }


    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go up and left
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] - currIndex2) == -1 || (pieceStartLocation[0][1] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] - currIndex2][0] == '*'){
            blackQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            blackQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'W'){
            blackQueenAllMovesUser[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            blackQueenAllMovesUser[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'B'){
            endOfRoad = true;
        }
    }
    
   

    
    bool moveIsPossible = false;

    // Sees if the location the player wants to move to is possible
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 1; j++){
            if((blackQueenAllMovesUser[i][j] == pieceEndLocation[0][0]) && (blackQueenAllMovesUser[i][j+1] == pieceEndLocation[0][1])){
                moveIsPossible = true;
            }
        }
    }

    // If we are not taking a piece
    if(strcmp(takenPiece, "") == 0){
        // If move is possible
        if(moveIsPossible == true){
            // Move the piece
            strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BQ");
            strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
            printf("Move made\n");
            return 1;
        }else{
            printf("That is not a possible move\n");
            return -1;
        }
    // If we are taking a piece
    }else{
         // If move is possible
        if(moveIsPossible == true){
            // Checks that the piece the user wants to take is actually there
            if(strcmp(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], takenPiece) == 0){
                // Take the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BQ");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                printf("Move made\n");
                return 1;
            }else{
                printf("The piece you want to take is not there\n");
                return -1;
            }
        }else{
            printf("That is not a possible move\n");
            return -1;
        }

    }
}



int WhitePawnAllMovesCpu(int whitePawnAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]){

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 2; j++){
            whitePawnAllMovesCpu[i][j] = -1;
        }
    }

    int currIndex = 0;


    // Checks if piece can move forward 2
    // 1. Checks piece is in starting spot
    // 2. Checks 1 spot in front is empty
    // 3. Checks 2 spots in front is empty
    if((pieceStartLocation[0][0] == 6) && (strcmp(theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1]], "**") == 0) && (strcmp(theBoardArray[pieceStartLocation[0][0] - 2][pieceStartLocation[0][1]], "**") == 0)){
        whitePawnAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - 2;
        whitePawnAllMovesCpu[currIndex][1] = pieceStartLocation[0][1];
        currIndex++;
    }


    // Checks if piece can move forward 1
    // 1. Checks if 1 spot in front is empty
    if ((strcmp(theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1]], "**") == 0)){
        whitePawnAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - 1;
        whitePawnAllMovesCpu[currIndex][1] = pieceStartLocation[0][1];
        currIndex++;
    }


    // Checks if piece can move diagonal left
    // 1. Checks that move is on the board
    // 2. Checks that enemy piece is on spot
    if((pieceStartLocation[0][1] - 1) != -1){
        if (theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1] - 1][0] == 'B'){
            whitePawnAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - 1;
            whitePawnAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - 1;
            currIndex++;
        }
    }


    // Checks if piece can move diagonal right
    // 1. Checks that move is on the board
    // 2. Checks that enemy piece is on spot
    if((pieceStartLocation[0][1] + 1) != 8){
        if (theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1] + 1][0] == 'B'){

            whitePawnAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - 1;
            whitePawnAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + 1;
            currIndex++;
        }
    }

}




int WhiteKingAllMovesCpu(int whiteKingAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]){

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 2; j++){
            whiteKingAllMovesCpu[i][j] = -1;
        }
    }


    int currIndex = 0;


    // Checks if piece can move forward 1
    // 1. Checks moving up 1 is still on board
    // 2. Checks if 1 spot forward doesn't have a white piece
    if(pieceStartLocation[0][0] != 0){
        if (theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1]][0] != 'W'){
        whiteKingAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - 1;
        whiteKingAllMovesCpu[currIndex][1] = pieceStartLocation[0][1];
        currIndex++;
        }  
    }

    // 1. Checks moving right 1 is still on board
    // 2. Checks if 1 spot right doesn't have a white piece
    if(pieceStartLocation[0][1] != 7){
        if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] + 1][0] != 'W'){
        whiteKingAllMovesCpu[currIndex][0] = pieceStartLocation[0][0];
        whiteKingAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + 1;
        currIndex++;
        }  
    }

    // 1. Checks moving down 1 is still on board
    // 2. Checks if 1 spot down doesn't have a white piece
    if(pieceStartLocation[0][0] != 7){
        if (theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1]][0] != 'W'){
        whiteKingAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + 1;
        whiteKingAllMovesCpu[currIndex][1] = pieceStartLocation[0][1];
        currIndex++;
        }  
    }
    
    // 1. Checks moving left 1 is still on board
    // 2. Checks if 1 spot down doesn't have a white piece
    if(pieceStartLocation[0][1] != 0){
        if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] -1][0] != 'W'){
        whiteKingAllMovesCpu[currIndex][0] = pieceStartLocation[0][0];
        whiteKingAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] -1;
        currIndex++;
        }  
    }

    // 1. Checks moving up and left 1 is still on board
    // 2. Checks if 1 up and left doesn't have a white piece
    if(pieceStartLocation[0][0] != 0 && pieceStartLocation[0][1] != 0){
        if (theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1] - 1][0] != 'W'){
        whiteKingAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] -1;
        whiteKingAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] -1;
        currIndex++;
        }  
    }

    // 1. Checks moving up and right 1 is still on board
    // 2. Checks if 1 up and right doesn't have a white piece
    if(pieceStartLocation[0][0] != 0 && pieceStartLocation[0][1] != 7){
        if (theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1] + 1][0] != 'W'){
        whiteKingAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] -1;
        whiteKingAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] +1;
        currIndex++;
        }  
    }

    // 1. Checks moving down and right 1 is still on board
    // 2. Checks if 1 down and right doesn't have a white piece
    if(pieceStartLocation[0][0] != 7 && pieceStartLocation[0][1] != 7){
        if (theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1] + 1][0] != 'W'){
        whiteKingAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] +1;
        whiteKingAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] +1;
        currIndex++;
        }  
    }

    // 1. Checks moving down and left 1 is still on board
    // 2. Checks if 1 down and left doesn't have a white piece
    if(pieceStartLocation[0][0] != 7 && pieceStartLocation[0][1] != 0){
        if (theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1] - 1][0] != 'W'){
        whiteKingAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] +1;
        whiteKingAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] -1;
        currIndex++;
        }  
    }


}





int WhiteKnightAllMovesCpu(int whiteKnightAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]){

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 2; j++){
            whiteKnightAllMovesCpu[i][j] = -1;
        }
    }

    int currIndex = 0;


    // Checks if piece can up 1, right 2
    // 1. Checks moving up 1, right 2 is still on board
    // 2. Checks if up 1, right 2 doesn't have a white piece
    if(pieceStartLocation[0][0] != 0 && pieceStartLocation[0][1] < 6){
        if (theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1] + 2][0] != 'W'){
            whiteKnightAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - 1;
            whiteKnightAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + 2;
            currIndex++;
        }  
    }


    // Checks if piece can up 2, right 1
    // 1. Checks moving up 2, right 1 is still on board
    // 2. Checks if up 2, right 1 doesn't have a white piece
    if(pieceStartLocation[0][0] > 1 && pieceStartLocation[0][1] != 7){
        if (theBoardArray[pieceStartLocation[0][0] - 2][pieceStartLocation[0][1] + 1][0] != 'W'){
            whiteKnightAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - 2;
            whiteKnightAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + 1;
            currIndex++;
        }  
    }


    // Checks if piece can down 1, right 2
    // 1. Checks moving down 1, right 2 is still on board
    // 2. Checks if down 1, right 2 doesn't have a white piece
    if(pieceStartLocation[0][0] != 7 && pieceStartLocation[0][1] < 6){
        if (theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1] + 2][0] != 'W'){
            whiteKnightAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + 1;
            whiteKnightAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + 2;
            currIndex++;
        }  
    }
    

    // Checks if piece can down 2, right 1
    // 1. Checks moving down 2, right 1 is still on board
    // 2. Checks if down 2, right 1 doesn't have a white piece
    if(pieceStartLocation[0][0] < 6 && pieceStartLocation[0][1] != 7){
        if (theBoardArray[pieceStartLocation[0][0] + 2][pieceStartLocation[0][1] + 1][0] != 'W'){
            whiteKnightAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + 2;
            whiteKnightAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + 1;
            currIndex++;
        }  
    }
    

    // Checks if piece can up 1, left 2
    // 1. Checks moving up 1, left 2 is still on board
    // 2. Checks if up 1, left 2 doesn't have a white piece
    if(pieceStartLocation[0][0] != 0 && pieceStartLocation[0][1] > 1){
        if (theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1] - 2][0] != 'W'){
            whiteKnightAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - 1;
            whiteKnightAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - 2;
            currIndex++;
        }  
    }


    // Checks if piece can up 2, left 1
    // 1. Checks moving up 2, left 1 is still on board
    // 2. Checks if up 2, left 1 doesn't have a white piece
    if(pieceStartLocation[0][0] > 1 && pieceStartLocation[0][1] != 0){
        if (theBoardArray[pieceStartLocation[0][0] - 2 ][pieceStartLocation[0][1] - 1][0] != 'W'){
            whiteKnightAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - 2;
            whiteKnightAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - 1;
            currIndex++;
        }  
    }


    // Checks if piece can down 1, left 2
    // 1. Checks moving down 1, left 2 is still on board
    // 2. Checks if down 1, left 2 doesn't have a white piece
    if(pieceStartLocation[0][0] != 7 && pieceStartLocation[0][1] > 1){
        if (theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1] - 2][0] != 'W'){
            whiteKnightAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + 1;
            whiteKnightAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - 2;
            currIndex++;
        }  
    }


    // Checks if piece can down 2, left 1
    // 1. Checks moving down 2, left 1 is still on board
    // 2. Checks if down 2, left 1 doesn't have a white piece
    if(pieceStartLocation[0][0] < 6 && pieceStartLocation[0][1] != 0){
        if (theBoardArray[pieceStartLocation[0][0] + 2][pieceStartLocation[0][1] - 1][0] != 'W'){
            whiteKnightAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + 2;
            whiteKnightAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - 1;
            currIndex++;
        }  
    }


    
}








int WhiteRookAllMovesCpu(int whiteRookAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]){

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 2; j++){
            whiteRookAllMovesCpu[i][j] = -1;
        }
    }

    int currIndex = 0;
    int currIndex2 = 1;

    bool endOfRoad = false;


    // Checks how far piece can go up
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1]][0] == '*'){
            whiteRookAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            whiteRookAllMovesCpu[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1]][0] == 'B'){
            whiteRookAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            whiteRookAllMovesCpu[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1]][0] == 'W'){
            endOfRoad = true;
        }
    }

    
    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go left
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][1] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] -currIndex2][0] == '*'){
            whiteRookAllMovesCpu[currIndex][0] = pieceStartLocation[0][0];
            whiteRookAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] -currIndex2][0] == 'B'){
            whiteRookAllMovesCpu[currIndex][0] = pieceStartLocation[0][0];
            whiteRookAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] - currIndex2][0] == 'W'){
            endOfRoad = true;
        }
    }



    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go right
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][1] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] +currIndex2][0] == '*'){
            whiteRookAllMovesCpu[currIndex][0] = pieceStartLocation[0][0];
            whiteRookAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] +currIndex2][0] == 'B'){
            whiteRookAllMovesCpu[currIndex][0] = pieceStartLocation[0][0];
            whiteRookAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] + currIndex2][0] == 'W'){
            endOfRoad = true;
        }
    }



    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go down
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1]][0] == '*'){
            whiteRookAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            whiteRookAllMovesCpu[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1]][0] == 'B'){
            whiteRookAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            whiteRookAllMovesCpu[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]  + currIndex2][pieceStartLocation[0][1]][0] == 'W'){
            endOfRoad = true;
        }
    }

}




int WhiteBishopAllMovesCpu(int whiteBishopAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]){

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 2; j++){
            whiteBishopAllMovesCpu[i][j] = -1;
        }
    }

    int currIndex = 0;
    int currIndex2 = 1;

    bool endOfRoad = false;


    // Checks how far piece can go up and right
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] - currIndex2) == -1 || (pieceStartLocation[0][1] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] + currIndex2][0] == '*'){
            whiteBishopAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            whiteBishopAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'B'){
            whiteBishopAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            whiteBishopAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'W'){
            endOfRoad = true;
        }
    }


    
    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go down and right
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] + currIndex2) == 8 || (pieceStartLocation[0][1] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] + currIndex2][0] == '*'){
            whiteBishopAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            whiteBishopAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'B'){
            whiteBishopAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            whiteBishopAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'W'){
            endOfRoad = true;
        }
    }
    
    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go down and left
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] + currIndex2) == 8 || (pieceStartLocation[0][1] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] - currIndex2][0] == '*'){
            whiteBishopAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            whiteBishopAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'B'){
            whiteBishopAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            whiteBishopAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'W'){
            endOfRoad = true;
        }
    }


    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go up and left
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] - currIndex2) == -1 || (pieceStartLocation[0][1] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] - currIndex2][0] == '*'){
            whiteBishopAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            whiteBishopAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'B'){
            whiteBishopAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            whiteBishopAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'W'){
            endOfRoad = true;
        }
    }

}




int WhiteQueenAllMovesCpu(int whiteQueenAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]){

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 2; j++){
            whiteQueenAllMovesCpu[i][j] = -1;
        }
    }

    int currIndex = 0;
    int currIndex2 = 1;

    bool endOfRoad = false;


    // Checks how far piece can go up
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1]][0] == '*'){
            whiteQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            whiteQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1]][0] == 'B'){
            whiteQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            whiteQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1]][0] == 'W'){
            endOfRoad = true;
        }
    }

    
    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go left
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][1] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] -currIndex2][0] == '*'){
            whiteQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0];
            whiteQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] -currIndex2][0] == 'B'){
            whiteQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0];
            whiteQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] - currIndex2][0] == 'W'){
            endOfRoad = true;
        }
    }



    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go right
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][1] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] +currIndex2][0] == '*'){
            whiteQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0];
            whiteQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] +currIndex2][0] == 'B'){
            whiteQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0];
            whiteQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] + currIndex2][0] == 'W'){
            endOfRoad = true;
        }
    }



    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go down
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1]][0] == '*'){
            whiteQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            whiteQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1]][0] == 'B'){
            whiteQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            whiteQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]  + currIndex2][pieceStartLocation[0][1]][0] == 'W'){
            endOfRoad = true;
        }
    }



    currIndex2 = 1;

    endOfRoad = false;



    // Checks how far piece can go up and right
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] - currIndex2) == -1 || (pieceStartLocation[0][1] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] + currIndex2][0] == '*'){
            whiteQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            whiteQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'B'){
            whiteQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            whiteQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'W'){
            endOfRoad = true;
        }
    }


    
    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go down and right
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] + currIndex2) == 8 || (pieceStartLocation[0][1] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] + currIndex2][0] == '*'){
            whiteQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            whiteQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'B'){
            whiteQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            whiteQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'W'){
            endOfRoad = true;
        }
    }
    
    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go down and left
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] + currIndex2) == 8 || (pieceStartLocation[0][1] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] - currIndex2][0] == '*'){
            whiteQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            whiteQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'B'){
            whiteQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            whiteQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'W'){
            endOfRoad = true;
        }
    }


    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go up and left
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] - currIndex2) == -1 || (pieceStartLocation[0][1] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] - currIndex2][0] == '*'){
            whiteQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            whiteQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'B'){
            whiteQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            whiteQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'W'){
            endOfRoad = true;
        }
    }
    

}




int BlackPawnAllMovesCpu(int blackPawnAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]){


    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 2; j++){
	    blackPawnAllMovesCpu[i][j] = -1;
        }
    }

    int currIndex = 0;


    // Checks if piece can move forward 2
    // 1. Checks piece is in starting spot
    // 2. Checks 1 spot in front is empty
    // 3. Checks 2 spots in front is empty
    if((pieceStartLocation[0][0] == 1) && (strcmp(theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1]], "**") == 0) && (strcmp(theBoardArray[pieceStartLocation[0][0] + 2][pieceStartLocation[0][1]], "**") == 0)){
        blackPawnAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + 2;
        blackPawnAllMovesCpu[currIndex][1] = pieceStartLocation[0][1];
        currIndex++;
    }


    // Checks if piece can move forward 1
    // 1. Checks if 1 spot in front is empty
    if ((strcmp(theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1]], "**") == 0)){
        blackPawnAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + 1;
        blackPawnAllMovesCpu[currIndex][1] = pieceStartLocation[0][1];
        currIndex++;
    }


    // Checks if piece can move diagonal left
    // 1. Checks that move is on the board
    // 2. Checks that enemy piece is on spot
    if((pieceStartLocation[0][1] - 1) != -1){
        if (theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1] - 1][0] == 'W'){
            blackPawnAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + 1;
            blackPawnAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - 1;
            currIndex++;
        }
    }


    // Checks if piece can move diagonal right
    // 1. Checks that move is on the board
    // 2. Checks that enemy piece is on spot
    if((pieceStartLocation[0][1] + 1) != 8){
        if (theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1] + 1][0] == 'W'){

            blackPawnAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + 1;
            blackPawnAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + 1;
            currIndex++;
        }
    }


}





int BlackKingAllMovesCpu(int blackKingAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]){

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 2; j++){
            blackKingAllMovesCpu[i][j] = -1;
        }
    }

    int currIndex = 0;


    // Checks if piece can move forward 1
    // 1. Checks moving up 1 is still on board
    // 2. Checks if 1 spot forward doesn't have a black piece
    if(pieceStartLocation[0][0] != 0){
        if (theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1]][0] != 'B'){
        blackKingAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - 1;
        blackKingAllMovesCpu[currIndex][1] = pieceStartLocation[0][1];
        currIndex++;
        }  
    }

    // 1. Checks moving right 1 is still on board
    // 2. Checks if 1 spot right doesn't have a black piece
    if(pieceStartLocation[0][1] != 7){
        if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] + 1][0] != 'B'){
        blackKingAllMovesCpu[currIndex][0] = pieceStartLocation[0][0];
        blackKingAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + 1;
        currIndex++;
        }  
    }

    // 1. Checks moving down 1 is still on board
    // 2. Checks if 1 spot down doesn't have a black piece
    if(pieceStartLocation[0][0] != 7){
        if (theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1]][0] != 'B'){
        blackKingAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + 1;
        blackKingAllMovesCpu[currIndex][1] = pieceStartLocation[0][1];
        currIndex++;
        }  
    }
    
    // 1. Checks moving left 1 is still on board
    // 2. Checks if 1 spot down doesn't have a black piece
    if(pieceStartLocation[0][1] != 0){
        if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] -1][0] != 'B'){
        blackKingAllMovesCpu[currIndex][0] = pieceStartLocation[0][0];
        blackKingAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] -1;
        currIndex++;
        }  
    }

    // 1. Checks moving up and left 1 is still on board
    // 2. Checks if 1 up and left doesn't have a black piece
    if(pieceStartLocation[0][0] != 0 && pieceStartLocation[0][1] != 0){
        if (theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1] - 1][0] != 'B'){
        blackKingAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] -1;
        blackKingAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] -1;
        currIndex++;
        }  
    }

    // 1. Checks moving up and right 1 is still on board
    // 2. Checks if 1 up and right doesn't have a black piece
    if(pieceStartLocation[0][0] != 0 && pieceStartLocation[0][1] != 7){
        if (theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1] + 1][0] != 'B'){
        blackKingAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] -1;
        blackKingAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] +1;
        currIndex++;
        }  
    }

    // 1. Checks moving down and right 1 is still on board
    // 2. Checks if 1 down and right doesn't have a black piece
    if(pieceStartLocation[0][0] != 7 && pieceStartLocation[0][1] != 7){
        if (theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1] + 1][0] != 'B'){
        blackKingAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] +1;
        blackKingAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] +1;
        currIndex++;
        }  
    }

    // 1. Checks moving down and left 1 is still on board
    // 2. Checks if 1 down and left doesn't have a black piece
    if(pieceStartLocation[0][0] != 7 && pieceStartLocation[0][1] != 0){
        if (theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1] - 1][0] != 'B'){
        blackKingAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] +1;
        blackKingAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] -1;
        currIndex++;
        }  
    }

}




int BlackKnightAllMovesCpu(int blackKnightAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]){


    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 2; j++){
            blackKnightAllMovesCpu[i][j] = -1;
        }
    }

    int currIndex = 0;


    // Checks if piece can up 1, right 2
    // 1. Checks moving up 1, right 2 is still on board
    // 2. Checks if up 1, right 2 doesn't have a black piece
    if(pieceStartLocation[0][0] != 0 && pieceStartLocation[0][1] < 6){
        if (theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1] + 2][0] != 'B'){
            blackKnightAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - 1;
            blackKnightAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + 2;
            currIndex++;
        }  
    }


    // Checks if piece can up 2, right 1
    // 1. Checks moving up 2, right 1 is still on board
    // 2. Checks if up 2, right 1 doesn't have a black piece
    if(pieceStartLocation[0][0] > 1 && pieceStartLocation[0][1] != 7){
        if (theBoardArray[pieceStartLocation[0][0] - 2][pieceStartLocation[0][1] + 1][0] != 'B'){
            blackKnightAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - 2;
            blackKnightAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + 1;
            currIndex++;
        }  
    }


    // Checks if piece can down 1, right 2
    // 1. Checks moving down 1, right 2 is still on board
    // 2. Checks if down 1, right 2 doesn't have a black piece
    if(pieceStartLocation[0][0] != 7 && pieceStartLocation[0][1] < 6){
        if (theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1] + 2][0] != 'B'){
            blackKnightAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + 1;
            blackKnightAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + 2;
            currIndex++;
        }  
    }
    

    // Checks if piece can down 2, right 1
    // 1. Checks moving down 2, right 1 is still on board
    // 2. Checks if down 2, right 1 doesn't have a black piece
    if(pieceStartLocation[0][0] < 6 && pieceStartLocation[0][1] != 7){
        if (theBoardArray[pieceStartLocation[0][0] + 2][pieceStartLocation[0][1] + 1][0] != 'B'){
            blackKnightAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + 2;
            blackKnightAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + 1;
            currIndex++;
        }  
    }
    

    // Checks if piece can up 1, left 2
    // 1. Checks moving up 1, left 2 is still on board
    // 2. Checks if up 1, left 2 doesn't have a black piece
    if(pieceStartLocation[0][0] != 0 && pieceStartLocation[0][1] > 1){
        if (theBoardArray[pieceStartLocation[0][0] - 1][pieceStartLocation[0][1] - 2][0] != 'B'){
            blackKnightAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - 1;
            blackKnightAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - 2;
            currIndex++;
        }  
    }


    // Checks if piece can up 2, left 1
    // 1. Checks moving up 2, left 1 is still on board
    // 2. Checks if up 2, left 1 doesn't have a black piece
    if(pieceStartLocation[0][0] > 1 && pieceStartLocation[0][1] != 0){
        if (theBoardArray[pieceStartLocation[0][0] - 2 ][pieceStartLocation[0][1] - 1][0] != 'B'){
            blackKnightAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - 2;
            blackKnightAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - 1;
            currIndex++;
        }  
    }


    // Checks if piece can down 1, left 2
    // 1. Checks moving down 1, left 2 is still on board
    // 2. Checks if down 1, left 2 doesn't have a black piece
    if(pieceStartLocation[0][0] != 7 && pieceStartLocation[0][1] > 1){
        if (theBoardArray[pieceStartLocation[0][0] + 1][pieceStartLocation[0][1] - 2][0] != 'B'){
            blackKnightAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + 1;
            blackKnightAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - 2;
            currIndex++;
        }  
    }


    // Checks if piece can down 2, left 1
    // 1. Checks moving down 2, left 1 is still on board
    // 2. Checks if down 2, left 1 doesn't have a black piece
    if(pieceStartLocation[0][0] < 6 && pieceStartLocation[0][1] != 0){
        if (theBoardArray[pieceStartLocation[0][0] + 2][pieceStartLocation[0][1] - 1][0] != 'B'){
            blackKnightAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + 2;
            blackKnightAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - 1;
            currIndex++;
        }  
    }

    
}




int BlackRookAllMovesCpu(int blackRookAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]){

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 2; j++){
            blackRookAllMovesCpu[i][j] = -1;
        }
    }

    int currIndex = 0;
    int currIndex2 = 1;

    bool endOfRoad = false;


    // Checks how far piece can go up
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1]][0] == '*'){
            blackRookAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            blackRookAllMovesCpu[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1]][0] == 'W'){
            blackRookAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            blackRookAllMovesCpu[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1]][0] == 'B'){
            endOfRoad = true;
        }
    }

    
    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go left
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][1] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] -currIndex2][0] == '*'){
            blackRookAllMovesCpu[currIndex][0] = pieceStartLocation[0][0];
            blackRookAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] -currIndex2][0] == 'W'){
            blackRookAllMovesCpu[currIndex][0] = pieceStartLocation[0][0];
            blackRookAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] - currIndex2][0] == 'B'){
            endOfRoad = true;
        }
    }



    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go right
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][1] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] +currIndex2][0] == '*'){
            blackRookAllMovesCpu[currIndex][0] = pieceStartLocation[0][0];
            blackRookAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] +currIndex2][0] == 'W'){
            blackRookAllMovesCpu[currIndex][0] = pieceStartLocation[0][0];
            blackRookAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] + currIndex2][0] == 'B'){
            endOfRoad = true;
        }
    }



    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go down
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1]][0] == '*'){
            blackRookAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            blackRookAllMovesCpu[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1]][0] == 'W'){
            blackRookAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            blackRookAllMovesCpu[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]  + currIndex2][pieceStartLocation[0][1]][0] == 'B'){
            endOfRoad = true;
        }
    }

}



int BlackBishopAllMovesCpu(int blackBishopAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]){

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 2; j++){
            blackBishopAllMovesCpu[i][j] = -1;
        }
    }

    int currIndex = 0;
    int currIndex2 = 1;

    bool endOfRoad = false;


    // Checks how far piece can go up and right
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] - currIndex2) == -1 || (pieceStartLocation[0][1] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] + currIndex2][0] == '*'){
            blackBishopAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            blackBishopAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'W'){
            blackBishopAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            blackBishopAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'B'){
            endOfRoad = true;
        }
    }


    
    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go down and right
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] + currIndex2) == 8 || (pieceStartLocation[0][1] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] + currIndex2][0] == '*'){
            blackBishopAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            blackBishopAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'W'){
            blackBishopAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            blackBishopAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'B'){
            endOfRoad = true;
        }
    }
    
    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go down and left
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] + currIndex2) == 8 || (pieceStartLocation[0][1] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] - currIndex2][0] == '*'){
            blackBishopAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            blackBishopAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'W'){
            blackBishopAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            blackBishopAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'B'){
            endOfRoad = true;
        }
    }


    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go up and left
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] - currIndex2) == -1 || (pieceStartLocation[0][1] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] - currIndex2][0] == '*'){
            blackBishopAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            blackBishopAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'W'){
            blackBishopAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            blackBishopAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'B'){
            endOfRoad = true;
        }
    }

}




int BlackQueenAllMovesCpu(int blackQueenAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]){
    

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 2; j++){
            blackQueenAllMovesCpu[i][j] = -1;
        }
    }

    int currIndex = 0;
    int currIndex2 = 1;

    bool endOfRoad = false;


    // Checks how far piece can go up
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1]][0] == '*'){
            blackQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            blackQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1]][0] == 'W'){
            blackQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            blackQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1]][0] == 'B'){
            endOfRoad = true;
        }
    }

    
    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go left
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][1] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] -currIndex2][0] == '*'){
            blackQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0];
            blackQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] -currIndex2][0] == 'W'){
            blackQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0];
            blackQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] - currIndex2][0] == 'B'){
            endOfRoad = true;
        }
    }



    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go right
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][1] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] +currIndex2][0] == '*'){
            blackQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0];
            blackQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] +currIndex2][0] == 'W'){
            blackQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0];
            blackQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] + currIndex2][0] == 'B'){
            endOfRoad = true;
        }
    }



    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go down
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1]][0] == '*'){
            blackQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            blackQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1]][0] == 'W'){
            blackQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            blackQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1];
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0]  + currIndex2][pieceStartLocation[0][1]][0] == 'B'){
            endOfRoad = true;
        }
    }



    currIndex2 = 1;

    endOfRoad = false;



    // Checks how far piece can go up and right
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] - currIndex2) == -1 || (pieceStartLocation[0][1] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] + currIndex2][0] == '*'){
            blackQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            blackQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'W'){
            blackQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            blackQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'B'){
            endOfRoad = true;
        }
    }


    
    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go down and right
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] + currIndex2) == 8 || (pieceStartLocation[0][1] + currIndex2) == 8){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] + currIndex2][0] == '*'){
            blackQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            blackQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'W'){
            blackQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            blackQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] + currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] + currIndex2][0] == 'B'){
            endOfRoad = true;
        }
    }
    
    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go down and left
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] + currIndex2) == 8 || (pieceStartLocation[0][1] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] - currIndex2][0] == '*'){
            blackQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            blackQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'W'){
            blackQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] + currIndex2;
            blackQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] + currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'B'){
            endOfRoad = true;
        }
    }


    currIndex2 = 1;

    endOfRoad = false;


    // Checks how far piece can go up and left
    while(endOfRoad == false){
        // Makes sure we don't go off the board
        if((pieceStartLocation[0][0] - currIndex2) == -1 || (pieceStartLocation[0][1] - currIndex2) == -1){
            endOfRoad = true;
        }
        // If there is no blocking piece
        else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] - currIndex2][0] == '*'){
            blackQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            blackQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            currIndex2++;
        // If there is a white piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'W'){
            blackQueenAllMovesCpu[currIndex][0] = pieceStartLocation[0][0] - currIndex2;
            blackQueenAllMovesCpu[currIndex][1] = pieceStartLocation[0][1] - currIndex2;
            currIndex++;
            endOfRoad = true;
        // If there is a black piece in the way
        }else if (theBoardArray[pieceStartLocation[0][0] - currIndex2][pieceStartLocation[0][1] - currIndex2][0] == 'B'){
            endOfRoad = true;
        }
    }

}




int WhiteCpuPickMove(char theBoardArray[8][8][4]){
    // For storing all possible moves
    // 1. Piece type
    // 2. Starting x 
    // 3. Starting y
    // 4. Ending x
    // 5. Ending y
    int whiteCpuAllPossibleMoves[500][5];

    // For storing current index in the above list
    int currIndex = 0;

    // Sets all values to -1
    for(int i = 0; i < 500; i++){
        for(int j = 0; j < 5; j++){
            whiteCpuAllPossibleMoves[i][j] = -1;
        }
    }


    // For storing all moves of the individual piece
    int individualPieceAllMoves[100][2];

    // For storing starting location of individual piece
    int pieceLocation[1][2];

    bool stillLooping = true;

    // Loops through the board
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            // If we found a white pawn
            if(strcmp(theBoardArray[i][j], "WP") == 0){

                pieceLocation[0][0] = i;
                pieceLocation[0][1] = j;


                WhitePawnAllMovesCpu(individualPieceAllMoves, theBoardArray, pieceLocation);

                int k = 0;

                while(stillLooping == true){
                    if(k == 100){
                        stillLooping = false;
                    }

                    if(individualPieceAllMoves[k][0] == -1){
                        stillLooping = false;
                    }else{
                        whiteCpuAllPossibleMoves[currIndex][0] = 0;
                        whiteCpuAllPossibleMoves[currIndex][1] = i;
                        whiteCpuAllPossibleMoves[currIndex][2] = j;
                        whiteCpuAllPossibleMoves[currIndex][3] = individualPieceAllMoves[k][0];
                        whiteCpuAllPossibleMoves[currIndex][4] = individualPieceAllMoves[k][1];

                        currIndex++; 

                        k++;
                    }
                }
                stillLooping = true;

            // If we found a white knight
            }else if(strcmp(theBoardArray[i][j], "WN") == 0){

                pieceLocation[0][0] = i;
                pieceLocation[0][1] = j;


                WhiteKnightAllMovesCpu(individualPieceAllMoves, theBoardArray, pieceLocation);

                int k = 0;

                while(stillLooping == true){
                    if(k == 100){
                        stillLooping = false;
                    }

                    if(individualPieceAllMoves[k][0] == -1){
                        stillLooping = false;
                    }else{
                        whiteCpuAllPossibleMoves[currIndex][0] = 1;
                        whiteCpuAllPossibleMoves[currIndex][1] = i;
                        whiteCpuAllPossibleMoves[currIndex][2] = j;
                        whiteCpuAllPossibleMoves[currIndex][3] = individualPieceAllMoves[k][0];
                        whiteCpuAllPossibleMoves[currIndex][4] = individualPieceAllMoves[k][1];

                        currIndex++; 

                        k++;
                    }
                }

                stillLooping = true;
            // If we found a white rook
            }else if(strcmp(theBoardArray[i][j], "WR") == 0){

                pieceLocation[0][0] = i;
                pieceLocation[0][1] = j;


                WhiteRookAllMovesCpu(individualPieceAllMoves, theBoardArray, pieceLocation);

                int k = 0;

                while(stillLooping == true){
                    if(k == 100){
                        stillLooping = false;
                    }

                    if(individualPieceAllMoves[k][0] == -1){
                        stillLooping = false;
                    }else{
                        whiteCpuAllPossibleMoves[currIndex][0] = 2;
                        whiteCpuAllPossibleMoves[currIndex][1] = i;
                        whiteCpuAllPossibleMoves[currIndex][2] = j;
                        whiteCpuAllPossibleMoves[currIndex][3] = individualPieceAllMoves[k][0];
                        whiteCpuAllPossibleMoves[currIndex][4] = individualPieceAllMoves[k][1];

                        currIndex++; 

                        k++;
                    }
                }

                stillLooping = true;
            // If we found a white bishop
            }else if(strcmp(theBoardArray[i][j], "WB") == 0){

                pieceLocation[0][0] = i;
                pieceLocation[0][1] = j;


                WhiteBishopAllMovesCpu(individualPieceAllMoves, theBoardArray, pieceLocation);


                int k = 0;

                while(stillLooping == true){
                    if(k == 100){
                        stillLooping = false;
                    }

                    if(individualPieceAllMoves[k][0] == -1){
                        stillLooping = false;
                    }else{
                        whiteCpuAllPossibleMoves[currIndex][0] = 3;
                        whiteCpuAllPossibleMoves[currIndex][1] = i;
                        whiteCpuAllPossibleMoves[currIndex][2] = j;
                        whiteCpuAllPossibleMoves[currIndex][3] = individualPieceAllMoves[k][0];
                        whiteCpuAllPossibleMoves[currIndex][4] = individualPieceAllMoves[k][1];

                        currIndex++; 

                        k++;
                    }
                }

                stillLooping = true;
            // If we found a white queen
            }else if(strcmp(theBoardArray[i][j], "WQ") == 0){

                pieceLocation[0][0] = i;
                pieceLocation[0][1] = j;


                WhiteQueenAllMovesCpu(individualPieceAllMoves, theBoardArray, pieceLocation);

                int k = 0;

                while(stillLooping == true){
                    if(k == 100){
                        stillLooping = false;
                    }

                    if(individualPieceAllMoves[k][0] == -1){
                        stillLooping = false;
                    }else{
                        whiteCpuAllPossibleMoves[currIndex][0] = 4;
                        whiteCpuAllPossibleMoves[currIndex][1] = i;
                        whiteCpuAllPossibleMoves[currIndex][2] = j;
                        whiteCpuAllPossibleMoves[currIndex][3] = individualPieceAllMoves[k][0];
                        whiteCpuAllPossibleMoves[currIndex][4] = individualPieceAllMoves[k][1];

                        currIndex++; 

                        k++;
                    }
                }

                stillLooping = true;
            // If we found a white king
            }else if(strcmp(theBoardArray[i][j], "WK") == 0){

                pieceLocation[0][0] = i;
                pieceLocation[0][1] = j;


                WhiteKingAllMovesCpu(individualPieceAllMoves, theBoardArray, pieceLocation);

                int k = 0;

                while(stillLooping == true){
                    if(k == 100){
                        stillLooping = false;
                    }

                    if(individualPieceAllMoves[k][0] == -1){
                        stillLooping = false;
                    }else{
                        whiteCpuAllPossibleMoves[currIndex][0] = 5;
                        whiteCpuAllPossibleMoves[currIndex][1] = i;
                        whiteCpuAllPossibleMoves[currIndex][2] = j;
                        whiteCpuAllPossibleMoves[currIndex][3] = individualPieceAllMoves[k][0];
                        whiteCpuAllPossibleMoves[currIndex][4] = individualPieceAllMoves[k][1];

                        currIndex++; 

                        k++;
                    }
                }

                stillLooping = true;
            }
        }
    }


    //for(int i = 0; i < 500; i++){
        //if(whiteCpuAllPossibleMoves[i][0] != -1){
          //for(int j = 0; j < 5; j++){
            //printf("%d ", whiteCpuAllPossibleMoves[i][j]);
        //}
        //printf("\n");  
        //}
    //}
    printf("%d\n", currIndex);


    // Seed the random number generator
    srand(time(NULL));

    // Generate a random number to randomly pick the move
    int randomNumber = (rand() % currIndex);

    // Print the random number
    printf("Random number: %d\n", randomNumber);

    printf("White:\n");
    printf("%d ", whiteCpuAllPossibleMoves[randomNumber][0]);
    printf("%d ", whiteCpuAllPossibleMoves[randomNumber][1]);
    printf("%d ", whiteCpuAllPossibleMoves[randomNumber][2]);
    printf("%d ", whiteCpuAllPossibleMoves[randomNumber][3]);
    printf("%d ", whiteCpuAllPossibleMoves[randomNumber][4]);
    printf("\n");


    // If the pieced to be moved is a pawn
    if(whiteCpuAllPossibleMoves[randomNumber][0] == 0){
        // If the pawn is ready for promotion, make it a queen
        if(whiteCpuAllPossibleMoves[randomNumber][3] == 0){
            // Move the piece
            strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][1]][whiteCpuAllPossibleMoves[randomNumber][2]], "**");
            strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][3]][whiteCpuAllPossibleMoves[randomNumber][4]], "WQ");   
        }else{
            // Move the piece
            strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][1]][whiteCpuAllPossibleMoves[randomNumber][2]], "**");
            strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][3]][whiteCpuAllPossibleMoves[randomNumber][4]], "WP");    
        }
    }
    // If the piece to be moved is a knight
    else if(whiteCpuAllPossibleMoves[randomNumber][0] == 1){
        // Move the piece
        strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][1]][whiteCpuAllPossibleMoves[randomNumber][2]], "**");
        strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][3]][whiteCpuAllPossibleMoves[randomNumber][4]], "WN"); 
    }
    // If the piece to be moved is a rook
    else if(whiteCpuAllPossibleMoves[randomNumber][0] == 2){
        // Move the piece
        strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][1]][whiteCpuAllPossibleMoves[randomNumber][2]], "**");
        strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][3]][whiteCpuAllPossibleMoves[randomNumber][4]], "WR"); 
    }
    // If the piece to be moved is a bishop
    else if(whiteCpuAllPossibleMoves[randomNumber][0] == 3){
        // Move the piece
        strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][1]][whiteCpuAllPossibleMoves[randomNumber][2]], "**");
        strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][3]][whiteCpuAllPossibleMoves[randomNumber][4]], "WB"); 
    }
    // If the piece to be moved is a queen
    else if(whiteCpuAllPossibleMoves[randomNumber][0] == 4){
        // Move the piece
        strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][1]][whiteCpuAllPossibleMoves[randomNumber][2]], "**");
        strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][3]][whiteCpuAllPossibleMoves[randomNumber][4]], "WQ"); 
    }
    // If the piece to be moved is a king
    else if(whiteCpuAllPossibleMoves[randomNumber][0] == 5){
        // Move the piece
        strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][1]][whiteCpuAllPossibleMoves[randomNumber][2]], "**");
        strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][3]][whiteCpuAllPossibleMoves[randomNumber][4]], "WK"); 
    }

    return 1;

}




int BlackCpuPickMove(char theBoardArray[8][8][4]){
    // For storing all possible moves
    // 1. Piece type
    // 2. Starting x 
    // 3. Starting y
    // 4. Ending x
    // 5. Ending y
    int blackCpuAllPossibleMoves[500][5];

    // For storing current index in the above list
    int currIndex = 0;

    // Sets all values to -1
    for(int i = 0; i < 500; i++){
        for(int j = 0; j < 5; j++){
            blackCpuAllPossibleMoves[i][j] = -1;
        }
    }

    // For storing all moves of the individual piece
    int individualPieceAllMoves[100][2];

    // For storing starting location of individual piece
    int pieceLocation[1][2];

    bool stillLooping = true;

    // Loops through the board
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            // If we found a black pawn
            if(strcmp(theBoardArray[i][j], "BP") == 0){

                pieceLocation[0][0] = i;
                pieceLocation[0][1] = j;


                BlackPawnAllMovesCpu(individualPieceAllMoves, theBoardArray, pieceLocation);

                int k = 0;

                while(stillLooping == true){
                    if(k == 100){
                        stillLooping = false;
                    }

                    if(individualPieceAllMoves[k][0] == -1){
                        stillLooping = false;
                    }else{
                        blackCpuAllPossibleMoves[currIndex][0] = 0;
                        blackCpuAllPossibleMoves[currIndex][1] = i;
                        blackCpuAllPossibleMoves[currIndex][2] = j;
                        blackCpuAllPossibleMoves[currIndex][3] = individualPieceAllMoves[k][0];
                        blackCpuAllPossibleMoves[currIndex][4] = individualPieceAllMoves[k][1];

                        currIndex++; 

                        k++;
                    }
                }
                stillLooping = true;

            // If we found a black knight
            }else if(strcmp(theBoardArray[i][j], "BN") == 0){


                pieceLocation[0][0] = i;
                pieceLocation[0][1] = j;


                BlackKnightAllMovesCpu(individualPieceAllMoves, theBoardArray, pieceLocation);

                int k = 0;

                while(stillLooping == true){
                    if(k == 100){
                        stillLooping = false;
                    }

                    if(individualPieceAllMoves[k][0] == -1){
                        stillLooping = false;
                    }else{
                        blackCpuAllPossibleMoves[currIndex][0] = 1;
                        blackCpuAllPossibleMoves[currIndex][1] = i;
                        blackCpuAllPossibleMoves[currIndex][2] = j;
                        blackCpuAllPossibleMoves[currIndex][3] = individualPieceAllMoves[k][0];
                        blackCpuAllPossibleMoves[currIndex][4] = individualPieceAllMoves[k][1];

                        currIndex++; 

                        k++;
                    }
                }

                stillLooping = true;
            // If we found a black rook
            }else if(strcmp(theBoardArray[i][j], "BR") == 0){


                pieceLocation[0][0] = i;
                pieceLocation[0][1] = j;


                BlackRookAllMovesCpu(individualPieceAllMoves, theBoardArray, pieceLocation);

                int k = 0;

                while(stillLooping == true){
                    if(k == 100){
                        stillLooping = false;
                    }

                    if(individualPieceAllMoves[k][0] == -1){
                        stillLooping = false;
                    }else{
                        blackCpuAllPossibleMoves[currIndex][0] = 2;
                        blackCpuAllPossibleMoves[currIndex][1] = i;
                        blackCpuAllPossibleMoves[currIndex][2] = j;
                        blackCpuAllPossibleMoves[currIndex][3] = individualPieceAllMoves[k][0];
                        blackCpuAllPossibleMoves[currIndex][4] = individualPieceAllMoves[k][1];

                        currIndex++; 

                        k++;
                    }
                }

                stillLooping = true;
            // If we found a black bishop
            }else if(strcmp(theBoardArray[i][j], "BB") == 0){


                pieceLocation[0][0] = i;
                pieceLocation[0][1] = j;


                BlackBishopAllMovesCpu(individualPieceAllMoves, theBoardArray, pieceLocation);

                int k = 0;

                while(stillLooping == true){
                    if(k == 100){
                        stillLooping = false;
                    }

                    if(individualPieceAllMoves[k][0] == -1){
                        stillLooping = false;
                    }else{
                        blackCpuAllPossibleMoves[currIndex][0] = 3;
                        blackCpuAllPossibleMoves[currIndex][1] = i;
                        blackCpuAllPossibleMoves[currIndex][2] = j;
                        blackCpuAllPossibleMoves[currIndex][3] = individualPieceAllMoves[k][0];
                        blackCpuAllPossibleMoves[currIndex][4] = individualPieceAllMoves[k][1];

                        currIndex++; 

                        k++;
                    }
                }

                stillLooping = true;
            // If we found a black queen
            }else if(strcmp(theBoardArray[i][j], "BQ") == 0){

                pieceLocation[0][0] = i;
                pieceLocation[0][1] = j;


                BlackQueenAllMovesCpu(individualPieceAllMoves, theBoardArray, pieceLocation);

                int k = 0;

                while(stillLooping == true){
                    if(k == 100){
                        stillLooping = false;
                    }

                    if(individualPieceAllMoves[k][0] == -1){
                        stillLooping = false;
                    }else{
                        blackCpuAllPossibleMoves[currIndex][0] = 4;
                        blackCpuAllPossibleMoves[currIndex][1] = i;
                        blackCpuAllPossibleMoves[currIndex][2] = j;
                        blackCpuAllPossibleMoves[currIndex][3] = individualPieceAllMoves[k][0];
                        blackCpuAllPossibleMoves[currIndex][4] = individualPieceAllMoves[k][1];

                        currIndex++; 

                        k++;
                    }
                }

                stillLooping = true;
            // If we found a black king
            }else if(strcmp(theBoardArray[i][j], "BK") == 0){

                pieceLocation[0][0] = i;
                pieceLocation[0][1] = j;


                BlackKingAllMovesCpu(individualPieceAllMoves, theBoardArray, pieceLocation);

                int k = 0;

                while(stillLooping == true){
                    if(k == 100){
                        stillLooping = false;
                    }

                    if(individualPieceAllMoves[k][0] == -1){
                        stillLooping = false;
                    }else{
                        blackCpuAllPossibleMoves[currIndex][0] = 5;
                        blackCpuAllPossibleMoves[currIndex][1] = i;
                        blackCpuAllPossibleMoves[currIndex][2] = j;
                        blackCpuAllPossibleMoves[currIndex][3] = individualPieceAllMoves[k][0];
                        blackCpuAllPossibleMoves[currIndex][4] = individualPieceAllMoves[k][1];

                        currIndex++; 

                        k++;
                    }
                }

                stillLooping = true;
            }
        }
    }


    //for(int i = 0; i < 500; i++){
        //if(blackCpuAllPossibleMoves[i][0] != -1){
          //for(int j = 0; j < 5; j++){
           // printf("%d ", blackCpuAllPossibleMoves[i][j]);
        //}
        //printf("\n");  
        //}
    //}
    printf("%d\n", currIndex);


    // Seed the random number generator
    srand(time(NULL));

    // Generate a random number to randomly pick the move
    int randomNumber = (rand() % currIndex);

    // Print the random number
    printf("Random number: %d\n", randomNumber);

    printf("Black:\n");
    printf("%d ", blackCpuAllPossibleMoves[randomNumber][0]);
    printf("%d ", blackCpuAllPossibleMoves[randomNumber][1]);
    printf("%d ", blackCpuAllPossibleMoves[randomNumber][2]);
    printf("%d ", blackCpuAllPossibleMoves[randomNumber][3]);
    printf("%d ", blackCpuAllPossibleMoves[randomNumber][4]);
    printf("\n");

    // If the pieced to be moved is a pawn
    if(blackCpuAllPossibleMoves[randomNumber][0] == 0){
        // If the pawn is ready for promotion, make it a queen
        if(blackCpuAllPossibleMoves[randomNumber][3] == 7){
            // Move the piece
            strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][1]][blackCpuAllPossibleMoves[randomNumber][2]], "**");
            strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][3]][blackCpuAllPossibleMoves[randomNumber][4]], "BQ");   
        }else{
            // Move the piece
            strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][1]][blackCpuAllPossibleMoves[randomNumber][2]], "**");
            strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][3]][blackCpuAllPossibleMoves[randomNumber][4]], "BP");    
        }
    }
    // If the piece to be moved is a knight
    else if(blackCpuAllPossibleMoves[randomNumber][0] == 1){
        // Move the piece
        strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][1]][blackCpuAllPossibleMoves[randomNumber][2]], "**");
        strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][3]][blackCpuAllPossibleMoves[randomNumber][4]], "BN"); 
    }
    // If the piece to be moved is a rook
    else if(blackCpuAllPossibleMoves[randomNumber][0] == 2){
        // Move the piece
        strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][1]][blackCpuAllPossibleMoves[randomNumber][2]], "**");
        strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][3]][blackCpuAllPossibleMoves[randomNumber][4]], "BR"); 
    }
    // If the piece to be moved is a bishop
    else if(blackCpuAllPossibleMoves[randomNumber][0] == 3){
        // Move the piece
        strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][1]][blackCpuAllPossibleMoves[randomNumber][2]], "**");
        strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][3]][blackCpuAllPossibleMoves[randomNumber][4]], "BB"); 
    }
    // If the piece to be moved is a queen
    else if(blackCpuAllPossibleMoves[randomNumber][0] == 4){
        // Move the piece
        strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][1]][blackCpuAllPossibleMoves[randomNumber][2]], "**");
        strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][3]][blackCpuAllPossibleMoves[randomNumber][4]], "BQ"); 
    }
    // If the piece to be moved is a king
    else if(blackCpuAllPossibleMoves[randomNumber][0] == 5){
        // Move the piece
        strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][1]][blackCpuAllPossibleMoves[randomNumber][2]], "**");
        strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][3]][blackCpuAllPossibleMoves[randomNumber][4]], "BK"); 
    }

    return 1;

}


int FindCheckOnWhiteKing(char theBoardArray[8][8][4]){
    int kingCurrLocation[1][2];

    // Goes through the board, looking for the white king
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // If we found the white king, store its location
            if(strcmp(theBoardArray[i][j], "WK") == 0){
                kingCurrLocation[0][0] = i;
                kingCurrLocation[0][1] = j;

               //printf("%d %d\n", kingCurrLocation[0][0], kingCurrLocation[0][1]);
            }
        }
    }


    // For storing all possible moves
    // 1. Piece type
    // 2. Starting x 
    // 3. Starting y
    // 4. Ending x
    // 5. Ending y
    int blackCpuAllPossibleMoves[500][5];

    // For storing current index in the above list
    int currIndex = 0;

    // Sets all values to -1
    for(int i = 0; i < 500; i++){
        for(int j = 0; j < 5; j++){
            blackCpuAllPossibleMoves[i][j] = -1;
        }
    }

    // For storing all moves of the individual piece
    int individualPieceAllMoves[100][2];

    // For storing starting location of individual piece
    int pieceLocation[1][2];

    bool stillLooping = true;

    // Loops through the board
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            // If we found a black pawn
            if(strcmp(theBoardArray[i][j], "BP") == 0){

                pieceLocation[0][0] = i;
                pieceLocation[0][1] = j;


                BlackPawnAllMovesCpu(individualPieceAllMoves, theBoardArray, pieceLocation);

                int k = 0;

                while(stillLooping == true){
                    if(k == 100){
                        stillLooping = false;
                    }

                    if(individualPieceAllMoves[k][0] == -1){
                        stillLooping = false;
                    }else{
                        blackCpuAllPossibleMoves[currIndex][0] = 0;
                        blackCpuAllPossibleMoves[currIndex][1] = i;
                        blackCpuAllPossibleMoves[currIndex][2] = j;
                        blackCpuAllPossibleMoves[currIndex][3] = individualPieceAllMoves[k][0];
                        blackCpuAllPossibleMoves[currIndex][4] = individualPieceAllMoves[k][1];

                        currIndex++; 

                        k++;
                    }
                }
                stillLooping = true;

            // If we found a black knight
            }else if(strcmp(theBoardArray[i][j], "BN") == 0){


                pieceLocation[0][0] = i;
                pieceLocation[0][1] = j;


                BlackKnightAllMovesCpu(individualPieceAllMoves, theBoardArray, pieceLocation);

                int k = 0;

                while(stillLooping == true){
                    if(k == 100){
                        stillLooping = false;
                    }

                    if(individualPieceAllMoves[k][0] == -1){
                        stillLooping = false;
                    }else{
                        blackCpuAllPossibleMoves[currIndex][0] = 1;
                        blackCpuAllPossibleMoves[currIndex][1] = i;
                        blackCpuAllPossibleMoves[currIndex][2] = j;
                        blackCpuAllPossibleMoves[currIndex][3] = individualPieceAllMoves[k][0];
                        blackCpuAllPossibleMoves[currIndex][4] = individualPieceAllMoves[k][1];

                        currIndex++; 

                        k++;
                    }
                }

                stillLooping = true;
            // If we found a black rook
            }else if(strcmp(theBoardArray[i][j], "BR") == 0){


                pieceLocation[0][0] = i;
                pieceLocation[0][1] = j;


                BlackRookAllMovesCpu(individualPieceAllMoves, theBoardArray, pieceLocation);

                int k = 0;

                while(stillLooping == true){
                    if(k == 100){
                        stillLooping = false;
                    }

                    if(individualPieceAllMoves[k][0] == -1){
                        stillLooping = false;
                    }else{
                        blackCpuAllPossibleMoves[currIndex][0] = 2;
                        blackCpuAllPossibleMoves[currIndex][1] = i;
                        blackCpuAllPossibleMoves[currIndex][2] = j;
                        blackCpuAllPossibleMoves[currIndex][3] = individualPieceAllMoves[k][0];
                        blackCpuAllPossibleMoves[currIndex][4] = individualPieceAllMoves[k][1];

                        currIndex++; 

                        k++;
                    }
                }

                stillLooping = true;
            // If we found a black bishop
            }else if(strcmp(theBoardArray[i][j], "BB") == 0){


                pieceLocation[0][0] = i;
                pieceLocation[0][1] = j;


                BlackBishopAllMovesCpu(individualPieceAllMoves, theBoardArray, pieceLocation);

                int k = 0;

                while(stillLooping == true){
                    if(k == 100){
                        stillLooping = false;
                    }

                    if(individualPieceAllMoves[k][0] == -1){
                        stillLooping = false;
                    }else{
                        blackCpuAllPossibleMoves[currIndex][0] = 3;
                        blackCpuAllPossibleMoves[currIndex][1] = i;
                        blackCpuAllPossibleMoves[currIndex][2] = j;
                        blackCpuAllPossibleMoves[currIndex][3] = individualPieceAllMoves[k][0];
                        blackCpuAllPossibleMoves[currIndex][4] = individualPieceAllMoves[k][1];

                        currIndex++; 

                        k++;
                    }
                }

                stillLooping = true;
            // If we found a black queen
            }else if(strcmp(theBoardArray[i][j], "BQ") == 0){

                pieceLocation[0][0] = i;
                pieceLocation[0][1] = j;


                BlackQueenAllMovesCpu(individualPieceAllMoves, theBoardArray, pieceLocation);

                int k = 0;

                while(stillLooping == true){
                    if(k == 100){
                        stillLooping = false;
                    }

                    if(individualPieceAllMoves[k][0] == -1){
                        stillLooping = false;
                    }else{
                        blackCpuAllPossibleMoves[currIndex][0] = 4;
                        blackCpuAllPossibleMoves[currIndex][1] = i;
                        blackCpuAllPossibleMoves[currIndex][2] = j;
                        blackCpuAllPossibleMoves[currIndex][3] = individualPieceAllMoves[k][0];
                        blackCpuAllPossibleMoves[currIndex][4] = individualPieceAllMoves[k][1];

                        currIndex++; 

                        k++;
                    }
                }

                stillLooping = true;
            // If we found a black king
            }else if(strcmp(theBoardArray[i][j], "BK") == 0){

                pieceLocation[0][0] = i;
                pieceLocation[0][1] = j;


                BlackKingAllMovesCpu(individualPieceAllMoves, theBoardArray, pieceLocation);

                int k = 0;

                while(stillLooping == true){
                    if(k == 100){
                        stillLooping = false;
                    }

                    if(individualPieceAllMoves[k][0] == -1){
                        stillLooping = false;
                    }else{
                        blackCpuAllPossibleMoves[currIndex][0] = 5;
                        blackCpuAllPossibleMoves[currIndex][1] = i;
                        blackCpuAllPossibleMoves[currIndex][2] = j;
                        blackCpuAllPossibleMoves[currIndex][3] = individualPieceAllMoves[k][0];
                        blackCpuAllPossibleMoves[currIndex][4] = individualPieceAllMoves[k][1];

                        currIndex++; 

                        k++;
                    }
                }

                stillLooping = true;
            }
        }
    }

    stillLooping = true;
    int k = 0;

    bool thereIsCheck = false;

    while(stillLooping == true){
        if(k == 500){
            stillLooping = false;
        }

        if(blackCpuAllPossibleMoves[k][0] == -1){
            stillLooping = false;
        }else{
            //printf("HERE: %d %d %d %d %d\n", blackCpuAllPossibleMoves[k][0], blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2], blackCpuAllPossibleMoves[k][3], blackCpuAllPossibleMoves[k][4]);
            // If we found a check
            if((blackCpuAllPossibleMoves[k][3] == kingCurrLocation[0][0]) &&  (blackCpuAllPossibleMoves[k][4] == kingCurrLocation[0][1])){
                if(blackCpuAllPossibleMoves[k][0] == 0){
                    printf("Check from pawn at index %d %d\n", blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2]);
                    thereIsCheck = true;
                }
                if(blackCpuAllPossibleMoves[k][0] == 1){
                    printf("Check from knight at index %d %d\n", blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2]);
                    thereIsCheck = true;
                }
                if(blackCpuAllPossibleMoves[k][0] == 2){
                    printf("Check from rook at index %d %d\n", blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2]);
                    thereIsCheck = true;
                }
                if(blackCpuAllPossibleMoves[k][0] == 3){
                    printf("Check from bishop at index %d %d\n", blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2]);
                    thereIsCheck = true;
                }
                if(blackCpuAllPossibleMoves[k][0] == 4){
                    printf("Check from queen at index %d %d\n", blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2]);
                    thereIsCheck = true;
                }
                if(blackCpuAllPossibleMoves[k][0] == 5){
                    printf("Check from king at index %d %d\n", blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2]);
                    thereIsCheck = true;
                }
            }

            

            k++;
        }
    }

    if(thereIsCheck == false){
        return 1;
    }

    // Now we are going to look for checkmate

    int currIndex2 = 0;

    // For storing all moves of the white king
    int whiteKingAllMoves[100][2];
    WhiteKingAllMovesCpu(whiteKingAllMoves, theBoardArray, kingCurrLocation);

    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 2; j++){
            if(whiteKingAllMoves[i][0] != -1){
                currIndex2++;
                j++;
            }
        }
    }


    bool weLoveLooping = true;

    int currIndex3 = -1;

    while(weLoveLooping == true && currIndex3 < currIndex2-1){
        currIndex3++;

        
        kingCurrLocation[0][0] = whiteKingAllMoves[currIndex3][0];
        kingCurrLocation[0][1] = whiteKingAllMoves[currIndex3][1];


        bool kingsNextMoveIsChecked = false;

        stillLooping = true;
        int k = 0;


        while(stillLooping == true){
            if(k == 500){
                stillLooping = false;
            }

            if(blackCpuAllPossibleMoves[k][0] == -1){
                stillLooping = false;
            }else{
                //printf("HERE: %d %d %d %d %d\n", blackCpuAllPossibleMoves[k][0], blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2], blackCpuAllPossibleMoves[k][3], blackCpuAllPossibleMoves[k][4]);
                // If we found a check
                if((blackCpuAllPossibleMoves[k][3] == kingCurrLocation[0][0]) &&  (blackCpuAllPossibleMoves[k][4] == kingCurrLocation[0][1])){
                    if(blackCpuAllPossibleMoves[k][0] == 0){
                        printf("Future check from pawn at index %d %d\n", blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2]);
                        kingsNextMoveIsChecked = true;
                    }
                    if(blackCpuAllPossibleMoves[k][0] == 1){
                        printf("Future check from knight at index %d %d\n", blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2]);
                        kingsNextMoveIsChecked = true;
                    }
                    if(blackCpuAllPossibleMoves[k][0] == 2){
                        printf("Future check from rook at index %d %d\n", blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2]);
                        kingsNextMoveIsChecked = true;
                    }
                    if(blackCpuAllPossibleMoves[k][0] == 3){
                        printf("Future check from bishop at index %d %d\n", blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2]);
                        kingsNextMoveIsChecked = true;
                    }
                    if(blackCpuAllPossibleMoves[k][0] == 4){
                        printf("Future check from queen at index %d %d\n", blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2]);
                        kingsNextMoveIsChecked = true;
                    }
                    if(blackCpuAllPossibleMoves[k][0] == 5){
                        printf("Future check from king at index %d %d\n", blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2]);
                        kingsNextMoveIsChecked = true;
                    }
                }

                

                k++;
            }
        }

        if(kingsNextMoveIsChecked == false){
            weLoveLooping = false;
        }
        

    }

    if(weLoveLooping == true){
        printf("Checkmate\n");
        return 3;
    }else{
        return 2;
    }

   

    return 1;
}

