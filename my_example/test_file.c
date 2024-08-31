int WhiteCpuPickMove(char theBoardArray[8][8][4]){
    int returnValue = 0;


    // For storing all possible moves
    // 1. Piece type
    // 2. Starting x 
    // 3. Starting y
    // 4. Ending x
    // 5. Ending y
    int whiteCpuAllPossibleMoves[500][5];


    // For storing current index in the above list
    int currIndex = 0;
    
    int i = 0;
    int j = 0;


    // Sets all values to -1
    for(i = 0; i < 500; i++){
        for(j = 0; j < 5; j++){
            whiteCpuAllPossibleMoves[i][j] = -1;
        }
    }




    // For storing all moves of the individual piece
    int individualPieceAllMoves[100][2];


    // For storing starting location of individual piece
    int pieceLocation[1][2];


    bool stillLooping = true;

    //return -3;

    // Loops through the board
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
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

    //return -3;


    //for(int i = 0; i < 500; i++){
        //if(whiteCpuAllPossibleMoves[i][0] != -1){
          //for(int j = 0; j < 5; j++){
            //printk("%d ", whiteCpuAllPossibleMoves[i][j]);
        //}
        //printk("\n");  
        //}
    //}
    //printk("%d\n", currIndex);




    // Seed the random number generator
    //srand(time(NULL));




    // Print the random number
    //printk("Random number: %d\n", randomNumber);


    //printk("White:\n");
    //printk("%d ", whiteCpuAllPossibleMoves[randomNumber][0]);
    //printk("%d ", whiteCpuAllPossibleMoves[randomNumber][1]);
    //printk("%d ", whiteCpuAllPossibleMoves[randomNumber][2]);
    //printk("%d ", whiteCpuAllPossibleMoves[randomNumber][3]);
    //printk("%d ", whiteCpuAllPossibleMoves[randomNumber][4]);
    //printk("\n");


    int checkedSelf = 0;


    int coolCounter = 0;


    bool weLoveLooping = true;


    while(weLoveLooping == true){
         // Generate a random number to randomly pick the move
        //int randomNumber = (rand() % currIndex);
        
        unsigned int randomNumber;
        get_random_bytes(&randomNumber, sizeof(randomNumber));
        randomNumber %= currIndex;
        
        printk("randomNumber: %d", randomNumber); //4
        printk("currIndex: %d", currIndex);     //20
        
        //return -3;


        if(coolCounter == 50){
            weLoveLooping = false;
            printk("cool\n");
            return 3;
        }


        // If the piece to be moved is a pawn
        if(whiteCpuAllPossibleMoves[randomNumber][0] == 0){
            printk("at pawn\n");
            //return -3;
            // If the pawn is ready for promotion, make it a queen
            if(whiteCpuAllPossibleMoves[randomNumber][3] == 0){
                printk("at pawn 2.5\n");
                return -3;
                // Move the piece
                strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][1]][whiteCpuAllPossibleMoves[randomNumber][2]], "**");
                strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][3]][whiteCpuAllPossibleMoves[randomNumber][4]], "WQ");


                checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);
                


                if(checkedSelf == 2 || checkedSelf == 3){
                    // Move the piece
                    strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][1]][whiteCpuAllPossibleMoves[randomNumber][2]], "WP");
                    strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][3]][whiteCpuAllPossibleMoves[randomNumber][4]], "**");
                    coolCounter++;  
                }else{
                    weLoveLooping = false;
                }
                
            }else{
                printk("at pawn 2\n");
                //return -3;
                // Move the piece
                strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][1]][whiteCpuAllPossibleMoves[randomNumber][2]], "**");
                strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][3]][whiteCpuAllPossibleMoves[randomNumber][4]], "WP");
                
                printk("at pawn 3.8\n");
                //return -3;  
                
                //int car = 0; //checkedSelf 
                
                checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);
                
                //return -100;

		//printk("car %d", car);
		//printk("at pawn 4\n");
                //return -3;
                
                weLoveLooping = false;

                //if(checkedSelf == 2 || checkedSelf == 3){
                    // Move the piece
                    //strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][1]][whiteCpuAllPossibleMoves[randomNumber][2]], "WP");
                    //strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][3]][whiteCpuAllPossibleMoves[randomNumber][4]], "**");  
                    //coolCounter++;  
                //}else{
                    //weLoveLooping = false;
                //}
            }
        }
        // If the piece to be moved is a knight
        else if(whiteCpuAllPossibleMoves[randomNumber][0] == 1){
            // Move the piece
            strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][1]][whiteCpuAllPossibleMoves[randomNumber][2]], "**");
            strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][3]][whiteCpuAllPossibleMoves[randomNumber][4]], "WN");


            checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);


            if(checkedSelf == 2 || checkedSelf == 3){
                // Move the piece
                strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][1]][whiteCpuAllPossibleMoves[randomNumber][2]], "WN");
                strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][3]][whiteCpuAllPossibleMoves[randomNumber][4]], "**");  
                coolCounter++;  
            }else{
                weLoveLooping = false;
            }


        }
        // If the piece to be moved is a rook
        else if(whiteCpuAllPossibleMoves[randomNumber][0] == 2){
            // Move the piece
            strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][1]][whiteCpuAllPossibleMoves[randomNumber][2]], "**");
            strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][3]][whiteCpuAllPossibleMoves[randomNumber][4]], "WR"); 


            checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);


            if(checkedSelf == 2 || checkedSelf == 3){
                // Move the piece
                strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][1]][whiteCpuAllPossibleMoves[randomNumber][2]], "WR");
                strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][3]][whiteCpuAllPossibleMoves[randomNumber][4]], "**"); 
                coolCounter++;  
            }else{
                weLoveLooping = false;
            }
            
        }
        // If the piece to be moved is a bishop
        else if(whiteCpuAllPossibleMoves[randomNumber][0] == 3){
            // Move the piece
            strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][1]][whiteCpuAllPossibleMoves[randomNumber][2]], "**");
            strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][3]][whiteCpuAllPossibleMoves[randomNumber][4]], "WB");


            checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);


            if(checkedSelf == 2 || checkedSelf == 3){
                // Move the piece
                strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][1]][whiteCpuAllPossibleMoves[randomNumber][2]], "WB");
                strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][3]][whiteCpuAllPossibleMoves[randomNumber][4]], "**");
                coolCounter++;   
            }else{
                weLoveLooping = false;
            }


        }
        // If the piece to be moved is a queen
        else if(whiteCpuAllPossibleMoves[randomNumber][0] == 4){
            // Move the piece
            strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][1]][whiteCpuAllPossibleMoves[randomNumber][2]], "**");
            strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][3]][whiteCpuAllPossibleMoves[randomNumber][4]], "WQ");


            checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);


            if(checkedSelf == 2 || checkedSelf == 3){
                // Move the piece
                strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][1]][whiteCpuAllPossibleMoves[randomNumber][2]], "WQ");
                strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][3]][whiteCpuAllPossibleMoves[randomNumber][4]], "**");  
                coolCounter++;  
            }else{
                weLoveLooping = false;
            }
            
        }
        // If the piece to be moved is a king
        else if(whiteCpuAllPossibleMoves[randomNumber][0] == 5){
            // Move the piece
            strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][1]][whiteCpuAllPossibleMoves[randomNumber][2]], "**");
            strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][3]][whiteCpuAllPossibleMoves[randomNumber][4]], "WK");


            checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);


            if(checkedSelf == 2 || checkedSelf == 3){
                // Move the piece
                strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][1]][whiteCpuAllPossibleMoves[randomNumber][2]], "WK");
                strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][3]][whiteCpuAllPossibleMoves[randomNumber][4]], "**"); 
                coolCounter++;   
            }else{
                weLoveLooping = false;
            }


        }








    }
    


        
   


    returnValue = FindCheckAndCheckmateOnBlackKing(theBoardArray);
    return returnValue;


}

