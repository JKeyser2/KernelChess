#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/slab.h> // for kmalloc, kfree
#include <linux/time.h> // for kernel time functions
#include <linux/random.h>



/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jakcson Keyser");
MODULE_DESCRIPTION("Chess in the kernel!!!");


/* Buffer for data */
static char buffer[255];
static int buffer_pointer = 0;

static char theBoardArray[8][8][4];

static bool hasGameStarted = false;
static bool userIsWhite = false;
static bool whitesTurn = true;


/* Variables for device and device class */
static dev_t my_device_nr;
static struct class *my_class;
static struct cdev my_device;


#define DRIVER_NAME "chessdriver"
#define DRIVER_CLASS "MyModuleClass"


void CreateBoard(char theBoardArray[8][8][4]);
void PrintBoard(char theBoardArray[8][8][4]);


int FindCheckAndCheckmateOnWhiteKing(char theBoardArray[8][8][4]);
int FindCheckAndCheckmateOnBlackKing(char theBoardArray[8][8][4]);


void ConvertLocationToIndex(char* theLocation, int pieceLocation[1][2]);


int LookForWhiteKing(char theBoardArray[8][8][4]);
int LookForBlackKing(char theBoardArray[8][8][4]);


int WhiteCpuPickMove(char theBoardArray[8][8][4]);
int BlackCpuPickMove(char theBoardArray[8][8][4]);


int WhitePawnAllMovesUser(int whitePawnAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece, char* upgradedPiece);
int WhiteKingAllMovesUser(int whiteKingAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece);
int WhiteKnightAllMovesUser(int whiteKnightAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece);
int WhiteRookAllMovesUser(int whiteRookAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece);
int WhiteBishopAllMovesUser(int whiteBishopAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece);
int WhiteQueenAllMovesUser(int whiteQueenAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece);


int BlackPawnAllMovesUser(int blackPawnAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece, char* upgradedPiece);
int BlackKingAllMovesUser(int blackKingAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece);
int BlackKnightAllMovesUser(int blackKnightAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece);
int BlackRookAllMovesUser(int blackRookAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece);
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


void ClearBuffer(char buffer[]);
void CopyToBuffer(char buffer[], char string[]);

/**
 * @brief 2. (We receive) Read data out of the buffer
 */
static ssize_t driver_read(struct file *File, char *user_buffer, size_t count, loff_t *offs) {
    printk("Driver read from!\n");
    
    int not_copied, delta;
    size_t to_copy;

    loff_t pos = *offs;

    if (pos >= buffer_pointer) {
        return 0;
    }

    /* Get amount of data to copy (using buffer length) */
    to_copy = min(count, strlen(buffer) - pos);

    /* Copy data to user */
    not_copied = copy_to_user(user_buffer, buffer + pos, to_copy);

    *offs += to_copy;

    /* Calculate data */
    delta = to_copy - not_copied;

    /* Log the string to the kernel log */
    printk(KERN_INFO "Read string: %.*s\n", (int)to_copy, buffer + pos);

    /* Clear the buffer after reading */
    memset(buffer, 0, sizeof(buffer));

    return delta;
}


/**
 * @brief 1. We write data to buffer and it handles it
 */
static ssize_t driver_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs) {
        //printk(KERN_INFO "Driver written to: %s\n", buffer);
        
	int to_copy, not_copied, delta;


	/* Get amount of data to copy */
	to_copy = min(count, sizeof(buffer));


	/* Copy data to user */
	not_copied = copy_from_user(buffer, user_buffer, to_copy);
	buffer[to_copy] = '\0';
	buffer_pointer = to_copy;
	
	delta = to_copy - not_copied;
	
	printk(KERN_INFO "Driver written to: %s\n", buffer);
	printk(KERN_INFO "Length of buffer: %zu", strlen(buffer)); 
	
	
	//CreateBoard(theBoardArray);


        // If user wants to start a new game as white
	if(strcmp(buffer, "00 W\n") == 0){
	    // Sets user to white
	    userIsWhite = true;
	    
	    hasGameStarted = true;
	    
	    
	    // Clear the buffer
	    ClearBuffer(buffer);
	       
	    // Create a new board
	    CreateBoard(theBoardArray);
	    
	    
	    strcpy(buffer, "OK\n\0");
	    
	    // Change buffer pointer to length of new string
	    buffer_pointer = strlen("OK\n");
	    
	    
	// If user wants to start a new game as black
	}else if(strcmp(buffer, "00 B\n") == 0){
	    // Sets user to black
	    userIsWhite = false;
	    
	    hasGameStarted = true;
	    
	    // Clear the buffer
	    ClearBuffer(buffer);
	       
	    // Create a new board
	    CreateBoard(theBoardArray);
	    
	    
	    strcpy(buffer, "OK\n");
	    
	    // Change buffer pointer to length of new string
	    buffer_pointer = strlen("OK\n");
	    
	    
	// If user wants current game state and game has started   
	}else if(strcmp(buffer, "01\n") == 0 && hasGameStarted == true){
	    // Clear the buffer
	    ClearBuffer(buffer);
	    
	    int i = 0;
	    int j = 0;
	    int k = 0;
	    int m = 0;
	    
	    // Copy the board over
	    for(i = 0; i < 8; i++){
	        for(j = 0; j < 8; j++){
		    for(k = 0; k < 2; k++){
		        buffer[m] = theBoardArray[i][j][k];
		        m++;
		    }
		    buffer[m] = ' ';
		    m++;
	        }
	        buffer[m] = '\n';
	        m++;
	        }
	    buffer[m] = '\0';	    
	    
	    // Change buffer pointer to length of new string
	    buffer_pointer = 200;
	}else if(strcmp(buffer, "1\n") == 0 && hasGameStarted == false){
	    // Clear the buffer
	    ClearBuffer(buffer);
	    
	    strcpy(buffer, "NOGAME\n");
	    
	    // Change buffer pointer to length of new string
	    buffer_pointer = strlen("NOGAME\n");
	    
	// User move    
	}else if(buffer[1] == '2' && hasGameStarted == true){
	    // If no game has been started
	    if(hasGameStarted == false){
	        strcpy(buffer, "NOGAME\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("NOGAME\n");	
	    
	    // If white moves when black's turn        
	    }else if(buffer[3] == 'W' && whitesTurn == false){
	        strcpy(buffer, "OOT\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("OOT\n");	
	    
	    // If black moves when white's turn	    
	    }else if(buffer[3] == 'B' && whitesTurn == true){
	        strcpy(buffer, "OOT\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("OOT\n");
	        
	    // Moving white pawn   	    
	    }else if(buffer[3] == 'W' && buffer[4] == 'P'){
	        
	        int whitePawnAllMovesUser[100][2];
	        
	        int pieceStartLocation[1][2];
	        int pieceEndLocation[1][2];
	        
	        char startLocation[3];
	        char endLocation[3];
	        char takenPiece[3];
	        char upgradedPiece[3];
	        
	        startLocation[0] = buffer[5];
	        startLocation[1] = buffer[6];
	        startLocation[2] = '\0';
	        
	        endLocation[0] = buffer[8];
	        endLocation[1] = buffer[9];
	        endLocation[2] = '\0';
	        
	        takenPiece[0] = '\0';
	        upgradedPiece[0] = '\0';
	        
	        ConvertLocationToIndex(startLocation, pieceStartLocation);
	        ConvertLocationToIndex(endLocation, pieceEndLocation);
	        
	        
	        int t = 0;
	        
	        for(t = 0; t < strlen(buffer); t++){
	            if(buffer[t] == 'x'){
	                takenPiece[0] = buffer[t+1];
	                takenPiece[1] = buffer[t+2];
	                takenPiece[2] = '\0';
	            }   
	        }
	        for(t = 0; t < strlen(buffer); t++){
	            if(buffer[t] == 'y'){
	                upgradedPiece[0] = buffer[t+1];
	                upgradedPiece[1] = buffer[t+2];
	                upgradedPiece[2] = '\0';
	            }   
	        }
	        
	        int returnValue = -2;
	        	        
	        returnValue = WhitePawnAllMovesUser(whitePawnAllMovesUser, theBoardArray, pieceStartLocation, pieceEndLocation, takenPiece, upgradedPiece);
	        
	        
	        if(returnValue == 1){
	        strcpy(buffer, "OK\n");
	        
	        whitesTurn = false;
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("OK\n");		        
	        }else if(returnValue == 2){
	        strcpy(buffer, "CHECK\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("CHECK\n");
	        
	        whitesTurn = false;	        
	        
	        }else if(returnValue == 3){
	        strcpy(buffer, "MATE\n");
	        
	        hasGameStarted = false;
	        whitesTurn = true;
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("MATE\n");		        
	        }else{
	        strcpy(buffer, "ILLMOVE\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("ILLMOVE\n");		        
	     
	       }
	       
	       
	       
	    }else if(buffer[3] == 'W' && buffer[4] == 'K'){
	        
	        int whiteKingAllMovesUser[100][2];
	        
	        int pieceStartLocation[1][2];
	        int pieceEndLocation[1][2];
	        
	        char startLocation[3];
	        char endLocation[3];
	        char takenPiece[3];
	        
	        startLocation[0] = buffer[5];
	        startLocation[1] = buffer[6];
	        startLocation[2] = '\0';
	        
	        endLocation[0] = buffer[8];
	        endLocation[1] = buffer[9];
	        endLocation[2] = '\0';
	        
	        takenPiece[0] = '\0';
	        
	        ConvertLocationToIndex(startLocation, pieceStartLocation);
	        ConvertLocationToIndex(endLocation, pieceEndLocation);
	        
	        
	        int t = 0;
	        
	        for(t = 0; t < strlen(buffer); t++){
	            if(buffer[t] == 'x'){
	                takenPiece[0] = buffer[t+1];
	                takenPiece[1] = buffer[t+2];
	                takenPiece[2] = '\0';
	            }   
	        }
	        
	        int returnValue = -2;
	        	        
	        returnValue = WhiteKingAllMovesUser(whiteKingAllMovesUser, theBoardArray, pieceStartLocation, pieceEndLocation, takenPiece);
	        
	        
	        if(returnValue == 1){
	        strcpy(buffer, "OK\n");
	        
	        whitesTurn = false;
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("OK\n");		        
	        }else if(returnValue == 2){
	        strcpy(buffer, "CHECK\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("CHECK\n");
	        
	        whitesTurn = false;	        
	        
	        }else if(returnValue == 3){
	        strcpy(buffer, "MATE\n");
	        
	        hasGameStarted = false;
	        whitesTurn = true;
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("MATE\n");		        
	        }else{
	        strcpy(buffer, "ILLMOVE\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("ILLMOVE\n");		        
	     
	       }
	       
	       
	       
	    }else if(buffer[3] == 'W' && buffer[4] == 'N'){
	        
	        int whiteKnightAllMovesUser[100][2];
	        
	        int pieceStartLocation[1][2];
	        int pieceEndLocation[1][2];
	        
	        char startLocation[3];
	        char endLocation[3];
	        char takenPiece[3];
	        
	        startLocation[0] = buffer[5];
	        startLocation[1] = buffer[6];
	        startLocation[2] = '\0';
	        
	        endLocation[0] = buffer[8];
	        endLocation[1] = buffer[9];
	        endLocation[2] = '\0';
	        
	        takenPiece[0] = '\0';
	        
	        ConvertLocationToIndex(startLocation, pieceStartLocation);
	        ConvertLocationToIndex(endLocation, pieceEndLocation);
	        
	        
	        int t = 0;
	        
	        for(t = 0; t < strlen(buffer); t++){
	            if(buffer[t] == 'x'){
	                takenPiece[0] = buffer[t+1];
	                takenPiece[1] = buffer[t+2];
	                takenPiece[2] = '\0';
	            }   
	        }
	        
	        int returnValue = -2;
	        	        
	        returnValue = WhiteKnightAllMovesUser(whiteKnightAllMovesUser, theBoardArray, pieceStartLocation, pieceEndLocation, takenPiece);
	        
	        
	        if(returnValue == 1){
	        strcpy(buffer, "OK\n");
	        
	        whitesTurn = false;
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("OK\n");		        
	        }else if(returnValue == 2){
	        strcpy(buffer, "CHECK\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("CHECK\n");
	        
	        whitesTurn = false;	        
	        
	        }else if(returnValue == 3){
	        strcpy(buffer, "MATE\n");
	        
	        hasGameStarted = false;
	        whitesTurn = true;
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("MATE\n");		        
	        }else{
	        strcpy(buffer, "ILLMOVE\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("ILLMOVE\n");		        
	     
	       }
	       
	       
	       
	    }else if(buffer[3] == 'W' && buffer[4] == 'R'){
	        
	        int whiteRookAllMovesUser[100][2];
	        
	        int pieceStartLocation[1][2];
	        int pieceEndLocation[1][2];
	        
	        char startLocation[3];
	        char endLocation[3];
	        char takenPiece[3];
	        
	        startLocation[0] = buffer[5];
	        startLocation[1] = buffer[6];
	        startLocation[2] = '\0';
	        
	        endLocation[0] = buffer[8];
	        endLocation[1] = buffer[9];
	        endLocation[2] = '\0';
	        
	        takenPiece[0] = '\0';
	        
	        ConvertLocationToIndex(startLocation, pieceStartLocation);
	        ConvertLocationToIndex(endLocation, pieceEndLocation);
	        
	        
	        int t = 0;
	        
	        for(t = 0; t < strlen(buffer); t++){
	            if(buffer[t] == 'x'){
	                takenPiece[0] = buffer[t+1];
	                takenPiece[1] = buffer[t+2];
	                takenPiece[2] = '\0';
	            }   
	        }
	        
	        int returnValue = -2;
	        	        
	        returnValue = WhiteRookAllMovesUser(whiteRookAllMovesUser, theBoardArray, pieceStartLocation, pieceEndLocation, takenPiece);
	        
	        
	        if(returnValue == 1){
	        strcpy(buffer, "OK\n");
	        
	        whitesTurn = false;
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("OK\n");		        
	        }else if(returnValue == 2){
	        strcpy(buffer, "CHECK\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("CHECK\n");
	        
	        whitesTurn = false;	        
	        
	        }else if(returnValue == 3){
	        strcpy(buffer, "MATE\n");
	        
	        hasGameStarted = false;
	        whitesTurn = true;
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("MATE\n");		        
	        }else{
	        strcpy(buffer, "ILLMOVE\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("ILLMOVE\n");		        
	     
	       }
	       
	       
	       
	    }else if(buffer[3] == 'W' && buffer[4] == 'B'){
	        
	        int whiteBishopAllMovesUser[100][2];
	        
	        int pieceStartLocation[1][2];
	        int pieceEndLocation[1][2];
	        
	        char startLocation[3];
	        char endLocation[3];
	        char takenPiece[3];
	        
	        startLocation[0] = buffer[5];
	        startLocation[1] = buffer[6];
	        startLocation[2] = '\0';
	        
	        endLocation[0] = buffer[8];
	        endLocation[1] = buffer[9];
	        endLocation[2] = '\0';
	        
	        takenPiece[0] = '\0';
	        
	        ConvertLocationToIndex(startLocation, pieceStartLocation);
	        ConvertLocationToIndex(endLocation, pieceEndLocation);
	        
	        
	        int t = 0;
	        
	        for(t = 0; t < strlen(buffer); t++){
	            if(buffer[t] == 'x'){
	                takenPiece[0] = buffer[t+1];
	                takenPiece[1] = buffer[t+2];
	                takenPiece[2] = '\0';
	            }   
	        }
	        
	        int returnValue = -2;
	        	        
	        returnValue = WhiteBishopAllMovesUser(whiteBishopAllMovesUser, theBoardArray, pieceStartLocation, pieceEndLocation, takenPiece);
	        
	        
	        if(returnValue == 1){
	        strcpy(buffer, "OK\n");
	        
	        whitesTurn = false;
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("OK\n");		        
	        }else if(returnValue == 2){
	        strcpy(buffer, "CHECK\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("CHECK\n");
	        
	        whitesTurn = false;	        
	        
	        }else if(returnValue == 3){
	        strcpy(buffer, "MATE\n");
	        
	        hasGameStarted = false;
	        whitesTurn = true;
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("MATE\n");		        
	        }else{
	        strcpy(buffer, "ILLMOVE\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("ILLMOVE\n");		        
	     
	       }
	       
	       
	       
	    }else if(buffer[3] == 'W' && buffer[4] == 'Q'){
	        
	        int whiteQueenAllMovesUser[100][2];
	        
	        int pieceStartLocation[1][2];
	        int pieceEndLocation[1][2];
	        
	        char startLocation[3];
	        char endLocation[3];
	        char takenPiece[3];
	        
	        startLocation[0] = buffer[5];
	        startLocation[1] = buffer[6];
	        startLocation[2] = '\0';
	        
	        endLocation[0] = buffer[8];
	        endLocation[1] = buffer[9];
	        endLocation[2] = '\0';
	        
	        takenPiece[0] = '\0';
	        
	        ConvertLocationToIndex(startLocation, pieceStartLocation);
	        ConvertLocationToIndex(endLocation, pieceEndLocation);
	        
	        
	        int t = 0;
	        
	        for(t = 0; t < strlen(buffer); t++){
	            if(buffer[t] == 'x'){
	                takenPiece[0] = buffer[t+1];
	                takenPiece[1] = buffer[t+2];
	                takenPiece[2] = '\0';
	            }   
	        }
	        
	        int returnValue = -2;
	        	        
	        returnValue = WhiteQueenAllMovesUser(whiteQueenAllMovesUser, theBoardArray, pieceStartLocation, pieceEndLocation, takenPiece);
	        
	        
	        if(returnValue == 1){
	        strcpy(buffer, "OK\n");
	        
	        whitesTurn = false;
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("OK\n");		        
	        }else if(returnValue == 2){
	        strcpy(buffer, "CHECK\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("CHECK\n");
	        
	        whitesTurn = false;	        
	        
	        }else if(returnValue == 3){
	        strcpy(buffer, "MATE\n");
	        
	        hasGameStarted = false;
	        whitesTurn = true;
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("MATE\n");		        
	        }else{
	        strcpy(buffer, "ILLMOVE\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("ILLMOVE\n");		        
	     
	       }
	       
	       
	       
	    }else if(buffer[3] == 'B' && buffer[4] == 'P'){
	        
	        int blackPawnAllMovesUser[100][2];
	        
	        int pieceStartLocation[1][2];
	        int pieceEndLocation[1][2];
	        
	        char startLocation[3];
	        char endLocation[3];
	        char takenPiece[3];
	        char upgradedPiece[3];
	        
	        startLocation[0] = buffer[5];
	        startLocation[1] = buffer[6];
	        startLocation[2] = '\0';
	        
	        endLocation[0] = buffer[8];
	        endLocation[1] = buffer[9];
	        endLocation[2] = '\0';
	        
	        takenPiece[0] = '\0';
	        upgradedPiece[0] = '\0';
	        
	        ConvertLocationToIndex(startLocation, pieceStartLocation);
	        ConvertLocationToIndex(endLocation, pieceEndLocation);
	        
	        
	        int t = 0;
	        
	        for(t = 0; t < strlen(buffer); t++){
	            if(buffer[t] == 'x'){
	                takenPiece[0] = buffer[t+1];
	                takenPiece[1] = buffer[t+2];
	                takenPiece[2] = '\0';
	            }   
	        }
	        for(t = 0; t < strlen(buffer); t++){
	            if(buffer[t] == 'y'){
	                upgradedPiece[0] = buffer[t+1];
	                upgradedPiece[1] = buffer[t+2];
	                upgradedPiece[2] = '\0';
	            }   
	        }
	        
	        int returnValue = -2;
	        	        
	        returnValue = BlackPawnAllMovesUser(blackPawnAllMovesUser, theBoardArray, pieceStartLocation, pieceEndLocation, takenPiece, upgradedPiece);
	        
	        
	        if(returnValue == 1){
	        strcpy(buffer, "OK\n");
	        
	        whitesTurn = true;
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("OK\n");		        
	        }else if(returnValue == 2){
	        strcpy(buffer, "CHECK\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("CHECK\n");
	        
	        whitesTurn = true;	        
	        
	        }else if(returnValue == 3){
	        strcpy(buffer, "MATE\n");
	        
	        hasGameStarted = false;
	        whitesTurn = true;
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("MATE\n");		        
	        }else{
	        strcpy(buffer, "ILLMOVE\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("ILLMOVE\n");		        
	     
	       }
	       
	       
	       
	    }else if(buffer[3] == 'B' && buffer[4] == 'K'){
	        
	        int blackKingAllMovesUser[100][2];
	        
	        int pieceStartLocation[1][2];
	        int pieceEndLocation[1][2];
	        
	        char startLocation[3];
	        char endLocation[3];
	        char takenPiece[3];
	        
	        startLocation[0] = buffer[5];
	        startLocation[1] = buffer[6];
	        startLocation[2] = '\0';
	        
	        endLocation[0] = buffer[8];
	        endLocation[1] = buffer[9];
	        endLocation[2] = '\0';
	        
	        takenPiece[0] = '\0';
	        
	        ConvertLocationToIndex(startLocation, pieceStartLocation);
	        ConvertLocationToIndex(endLocation, pieceEndLocation);
	        
	        
	        int t = 0;
	        
	        for(t = 0; t < strlen(buffer); t++){
	            if(buffer[t] == 'x'){
	                takenPiece[0] = buffer[t+1];
	                takenPiece[1] = buffer[t+2];
	                takenPiece[2] = '\0';
	            }   
	        }
	        
	        int returnValue = -2;
	        	        
	        returnValue = BlackKingAllMovesUser(blackKingAllMovesUser, theBoardArray, pieceStartLocation, pieceEndLocation, takenPiece);
	        
	        
	        if(returnValue == 1){
	        strcpy(buffer, "OK\n");
	        
	        whitesTurn = true;
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("OK\n");		        
	        }else if(returnValue == 2){
	        strcpy(buffer, "CHECK\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("CHECK\n");
	        
	        whitesTurn = true;	        
	        
	        }else if(returnValue == 3){
	        strcpy(buffer, "MATE\n");
	        
	        hasGameStarted = false;
	        whitesTurn = true;
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("MATE\n");		        
	        }else{
	        strcpy(buffer, "ILLMOVE\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("ILLMOVE\n");		        
	     
	       }
	       
	       
	       
	    }else if(buffer[3] == 'B' && buffer[4] == 'N'){
	        
	        int blackKnightAllMovesUser[100][2];
	        
	        int pieceStartLocation[1][2];
	        int pieceEndLocation[1][2];
	        
	        char startLocation[3];
	        char endLocation[3];
	        char takenPiece[3];
	        
	        startLocation[0] = buffer[5];
	        startLocation[1] = buffer[6];
	        startLocation[2] = '\0';
	        
	        endLocation[0] = buffer[8];
	        endLocation[1] = buffer[9];
	        endLocation[2] = '\0';
	        
	        takenPiece[0] = '\0';
	        
	        ConvertLocationToIndex(startLocation, pieceStartLocation);
	        ConvertLocationToIndex(endLocation, pieceEndLocation);
	        
	        
	        int t = 0;
	        
	        for(t = 0; t < strlen(buffer); t++){
	            if(buffer[t] == 'x'){
	                takenPiece[0] = buffer[t+1];
	                takenPiece[1] = buffer[t+2];
	                takenPiece[2] = '\0';
	            }   
	        }
	        
	        int returnValue = -2;
	        	        
	        returnValue = BlackKnightAllMovesUser(blackKnightAllMovesUser, theBoardArray, pieceStartLocation, pieceEndLocation, takenPiece);
	        
	        
	        if(returnValue == 1){
	        strcpy(buffer, "OK\n");
	        
	        whitesTurn = true;
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("OK\n");		        
	        }else if(returnValue == 2){
	        strcpy(buffer, "CHECK\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("CHECK\n");
	        
	        whitesTurn = true;	        
	        
	        }else if(returnValue == 3){
	        strcpy(buffer, "MATE\n");
	        
	        hasGameStarted = false;
	        whitesTurn = true;
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("MATE\n");		        
	        }else{
	        strcpy(buffer, "ILLMOVE\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("ILLMOVE\n");		        
	     
	       }
	       
	    }else if(buffer[3] == 'B' && buffer[4] == 'R'){
	        
	        int blackRookAllMovesUser[100][2];
	        
	        int pieceStartLocation[1][2];
	        int pieceEndLocation[1][2];
	        
	        char startLocation[3];
	        char endLocation[3];
	        char takenPiece[3];
	        
	        startLocation[0] = buffer[5];
	        startLocation[1] = buffer[6];
	        startLocation[2] = '\0';
	        
	        endLocation[0] = buffer[8];
	        endLocation[1] = buffer[9];
	        endLocation[2] = '\0';
	        
	        takenPiece[0] = '\0';
	        
	        ConvertLocationToIndex(startLocation, pieceStartLocation);
	        ConvertLocationToIndex(endLocation, pieceEndLocation);
	        
	        
	        int t = 0;
	        
	        for(t = 0; t < strlen(buffer); t++){
	            if(buffer[t] == 'x'){
	                takenPiece[0] = buffer[t+1];
	                takenPiece[1] = buffer[t+2];
	                takenPiece[2] = '\0';
	            }   
	        }
	        
	        int returnValue = -2;
	        	        
	        returnValue = BlackRookAllMovesUser(blackRookAllMovesUser, theBoardArray, pieceStartLocation, pieceEndLocation, takenPiece);
	        
	        
	        if(returnValue == 1){
	        strcpy(buffer, "OK\n");
	        
	        whitesTurn = true;
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("OK\n");		        
	        }else if(returnValue == 2){
	        strcpy(buffer, "CHECK\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("CHECK\n");
	        
	        whitesTurn = true;	        
	        
	        }else if(returnValue == 3){
	        strcpy(buffer, "MATE\n");
	        
	        hasGameStarted = false;
	        whitesTurn = true;
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("MATE\n");		        
	        }else{
	        strcpy(buffer, "ILLMOVE\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("ILLMOVE\n");		        
	        }
	        
	    }else if(buffer[3] == 'B' && buffer[4] == 'B'){
	        
	        int blackBishopAllMovesUser[100][2];
	        
	        int pieceStartLocation[1][2];
	        int pieceEndLocation[1][2];
	        
	        char startLocation[3];
	        char endLocation[3];
	        char takenPiece[3];
	        
	        startLocation[0] = buffer[5];
	        startLocation[1] = buffer[6];
	        startLocation[2] = '\0';
	        
	        endLocation[0] = buffer[8];
	        endLocation[1] = buffer[9];
	        endLocation[2] = '\0';
	        
	        takenPiece[0] = '\0';
	        
	        ConvertLocationToIndex(startLocation, pieceStartLocation);
	        ConvertLocationToIndex(endLocation, pieceEndLocation);
	        
	        
	        int t = 0;
	        
	        for(t = 0; t < strlen(buffer); t++){
	            if(buffer[t] == 'x'){
	                takenPiece[0] = buffer[t+1];
	                takenPiece[1] = buffer[t+2];
	                takenPiece[2] = '\0';
	            }   
	        }
	        
	        int returnValue = -2;
	        	        
	        returnValue = BlackBishopAllMovesUser(blackBishopAllMovesUser, theBoardArray, pieceStartLocation, pieceEndLocation, takenPiece);
	        
	        
	        if(returnValue == 1){
	        strcpy(buffer, "OK\n");
	        
	        whitesTurn = true;
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("OK\n");		        
	        }else if(returnValue == 2){
	        strcpy(buffer, "CHECK\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("CHECK\n");
	        
	        whitesTurn = true;	        
	        
	        }else if(returnValue == 3){
	        strcpy(buffer, "MATE\n");
	        
	        hasGameStarted = false;
	        whitesTurn = true;
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("MATE\n");		        
	        }else{
	        strcpy(buffer, "ILLMOVE\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("ILLMOVE\n");		        
	        }
	    
	    }else if(buffer[3] == 'B' && buffer[4] == 'Q'){
	        
	        int blackQueenAllMovesUser[100][2];
	        
	        int pieceStartLocation[1][2];
	        int pieceEndLocation[1][2];
	        
	        char startLocation[3];
	        char endLocation[3];
	        char takenPiece[3];
	        
	        startLocation[0] = buffer[5];
	        startLocation[1] = buffer[6];
	        startLocation[2] = '\0';
	        
	        endLocation[0] = buffer[8];
	        endLocation[1] = buffer[9];
	        endLocation[2] = '\0';
	        
	        takenPiece[0] = '\0';
	        
	        ConvertLocationToIndex(startLocation, pieceStartLocation);
	        ConvertLocationToIndex(endLocation, pieceEndLocation);
	        
	        
	        int t = 0;
	        
	        for(t = 0; t < strlen(buffer); t++){
	            if(buffer[t] == 'x'){
	                takenPiece[0] = buffer[t+1];
	                takenPiece[1] = buffer[t+2];
	                takenPiece[2] = '\0';
	            }   
	        }
	        
	        int returnValue = -2;
	        	        
	        returnValue = BlackQueenAllMovesUser(blackQueenAllMovesUser, theBoardArray, pieceStartLocation, pieceEndLocation, takenPiece);
	        
	        
	        if(returnValue == 1){
	        strcpy(buffer, "OK\n");
	        
	        whitesTurn = true;
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("OK\n");		        
	        }else if(returnValue == 2){
	        strcpy(buffer, "CHECK\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("CHECK\n");
	        
	        whitesTurn = true;	        
	        
	        }else if(returnValue == 3){
	        strcpy(buffer, "MATE\n");
	        
	        hasGameStarted = false;
	        whitesTurn = true;
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("MATE\n");		        
	        }else{
	        strcpy(buffer, "ILLMOVE\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("ILLMOVE\n");		        
	        }
	    
	    }else{
	        strcpy(buffer, "INVFMT\n");
	    
	        // Change buffer pointer to length of new string
	        buffer_pointer = strlen("INVFMT\n");			    
	    }
	// White trying to resign, not their turn   
	}else if(strcmp(buffer, "04\n") == 0 && hasGameStarted == true && userIsWhite == true && whitesTurn == false){
            strcpy(buffer, "OOT\n");	
	
	    // Change buffer pointer to length of new string
            buffer_pointer = strlen("OOT\n");		

        // Black trying to resign, not their turn
        }else if(strcmp(buffer, "04\n") == 0 && hasGameStarted == true && userIsWhite == false && whitesTurn == true){
            strcpy(buffer, "OOT\n");	
	
	    // Change buffer pointer to length of new string
            buffer_pointer = strlen("OOT\n");	       
        
        // Trying to resign no game
        }else if(strcmp(buffer, "04\n") == 0 && hasGameStarted == false){
            strcpy(buffer, "NOGAME\n");	
	
	    // Change buffer pointer to length of new string
            buffer_pointer = strlen("NOGAME\n");	         
            
	    
	// Resign game    
	}else if(strcmp(buffer, "04\n") == 0){
	    hasGameStarted = false;
	    whitesTurn = true;
	   
            strcpy(buffer, "OK\n");
    
            // Change buffer pointer to length of new string
            buffer_pointer = strlen("OK\n");	
        // CPU move (black)
        // Game has started
        // User is white
        // Not white's turn
	}else if(strcmp(buffer, "03\n") == 0 && hasGameStarted == true && userIsWhite == true && whitesTurn == false){
	
	    int returnValue = 0;
	
	    BlackCpuPickMove(theBoardArray);
	    
	    
            returnValue = FindCheckAndCheckmateOnWhiteKing(theBoardArray);
            
            whitesTurn = true;
	    
	    if(returnValue == 1){
            strcpy(buffer, "OK\n");	
	
	    // Change buffer pointer to length of new string
            buffer_pointer = strlen("OK\n");	        
	    }else if(returnValue == 2){
            strcpy(buffer, "CHECK\n");	
	
	    // Change buffer pointer to length of new string
            buffer_pointer = strlen("CHECK\n");		    
	    
	    }else{
            strcpy(buffer, "MATE\n");
            	
	    hasGameStarted = false;
	    whitesTurn = true;
	
	    // Change buffer pointer to length of new string
            buffer_pointer = strlen("MATE\n");		    
	    
	    }

	
        // CPU move (black)
        // User is white
        // White's turn
	}else if(strcmp(buffer, "03\n") == 0 && userIsWhite == true && whitesTurn == true){
            strcpy(buffer, "OOT\n");	
	
	    // Change buffer pointer to length of new string
            buffer_pointer = strlen("OOT\n");		
	
	
	
	
	}else if(strcmp(buffer, "03\n") == 0 && hasGameStarted == false){
            strcpy(buffer, "NOGAME\n");	
	
	    // Change buffer pointer to length of new string
            buffer_pointer = strlen("NOGAME\n");			
	
	
	
	// CPU move (white)
        // Game has started
        // User is black
        // Not black's turn
	}else if(strcmp(buffer, "03\n") == 0 && hasGameStarted == true && userIsWhite == false && whitesTurn == true){
	
	    int returnValue = 0;
	
	    WhiteCpuPickMove(theBoardArray);
	    
	    
            returnValue = FindCheckAndCheckmateOnBlackKing(theBoardArray);
            
            whitesTurn = false;
	    
	    if(returnValue == 1){
            strcpy(buffer, "OK\n");	
	
	    // Change buffer pointer to length of new string
            buffer_pointer = strlen("OK\n");	        
	    }else if(returnValue == 2){
            strcpy(buffer, "CHECK\n");	
	
	    // Change buffer pointer to length of new string
            buffer_pointer = strlen("CHECK\n");		    
	    
	    }else{
            strcpy(buffer, "MATE\n");
            
            hasGameStarted = false;
	    whitesTurn = true;
	
	    // Change buffer pointer to length of new string
            buffer_pointer = strlen("MATE\n");		    
	    
	    }

	
	
	
	
	// CPU move (white)
        // User is black
        // Black's turn
	}else if(strcmp(buffer, "03\n") == 0 && userIsWhite == false && whitesTurn == false){
            strcpy(buffer, "OOT\n");	
	
	    // Change buffer pointer to length of new string
            buffer_pointer = strlen("OOT\n");		
	

	// Invalid format
	}else if(buffer[1] == '2' && hasGameStarted == false){
            strcpy(buffer, "NOGAME\n");	
	
	    // Change buffer pointer to length of new string
            buffer_pointer = strlen("NOGAME\n");	
	}
	
	else{
            strcpy(buffer, "INVFMT\n");	
	
	    // Change buffer pointer to length of new string
            buffer_pointer = strlen("INVFMT\n");		
	}
	
	
	//02 WPf7-g8xBNyWB
	// 17 with newline included
	
	
	
	//PrintBoard(theBoardArray);
	
	// Clear the buffer
	//int n = 0;
	//for(n = 0; n < sizeof(buffer); n++){
	    //buffer[n] = '\0';
	//}
	
	//printk("BELOW\n");
	//CreateBoard(theBoardArray);
	//PrintBoard(theBoardArray);
	
	//int i = 0;
	//int j = 0;
	//int k = 0;
	//int m = 0;


	//for(i = 0; i < 8; i++){
	    //for(j = 0; j < 8; j++){
	        //for(k = 0; k < 2; k++){
		    //buffer[m] = theBoardArray[i][j][k];
		    //m++;
	        //}
	        //buffer[m] = ' ';
	        //m++;
	    //}
	    //buffer[m] = '\n';
	    //m++;
	    //}
	//buffer[m] = '\0';


	//printk("Buffer Board:%s", buffer);
        //printk(KERN_INFO "Length of buffer: %zu", strlen(buffer)); 
	
	//char* startLocation = "A2";
	//char* endLocation = "A3";
	
	//int pieceStartLocation[1][2];
	//int pieceEndLocation[1][2];
	
	//char* startLocation2 = "A1";
	//char* endLocation2 = "A2";
	
	//int pieceStartLocation2[1][2];
	//int pieceEndLocation2[1][2];
	
	//int greatcool = 0;
	
	//ConvertLocationToIndex(startLocation, pieceStartLocation);
	//ConvertLocationToIndex(endLocation, pieceEndLocation);
	
	//ConvertLocationToIndex(startLocation2, pieceStartLocation2);
	//ConvertLocationToIndex(endLocation2, pieceEndLocation2);
	
	//int whitePawnAllMovesUser[100][2];
	//int whiteRookAllMovesUser[100][2];
	
	//greatcool = WhitePawnAllMovesCpu(whitePawnAllMovesCpu, theBoardArray, pieceStartLocation);
	
	//greatcool = WhitePawnAllMovesUser(whitePawnAllMovesUser, theBoardArray, pieceStartLocation, pieceEndLocation, "", "");
	
	//greatcool = WhiteRookAllMovesUser(whiteRookAllMovesUser, theBoardArray, pieceStartLocation2, pieceEndLocation2, "");
	
	//PrintBoard(theBoardArray);


	return delta;
}


/**
 * @brief This function is called, when the device file is opened
 */
static int driver_open(struct inode *device_file, struct file *instance) {
	printk("dev_nr - open was called!\n");
	return 0;
}


/**
 * @brief This function is called, when the device file is opened
 */
static int driver_close(struct inode *device_file, struct file *instance) {
	printk("dev_nr - close was called!\n");
	return 0;
}


static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close,
	.read = driver_read,
	.write = driver_write
};


/**
 * @brief This function is called, when the module is loaded into the kernel
 */
static int __init ModuleInit(void) {
	int retval;
	printk("Hello, Kernel!\n");


	/* Allocate a device nr */
	if( alloc_chrdev_region(&my_device_nr, 0, 1, DRIVER_NAME) < 0) {
		printk("Device Nr. could not be allocated!\n");
		return -1;
	}
	printk("read_write - Device Nr. Major: %d, Minor: %d was registered!\n", my_device_nr >> 20, my_device_nr & 0xfffff);


	/* Create device class */
	if((my_class = class_create(THIS_MODULE, DRIVER_CLASS)) == NULL) {
		printk("Device class can not be created!\n");
		goto ClassError;
	}


	/* create device file */
	if(device_create(my_class, NULL, my_device_nr, NULL, DRIVER_NAME) == NULL) {
		printk("Can not create device file!\n");
		goto FileError;
	}


	/* Initialize device file */
	cdev_init(&my_device, &fops);


	/* Regisering device to kernel */
	if(cdev_add(&my_device, my_device_nr, 1) == -1) {
		printk("Registering of device to kernel failed!\n");
		goto AddError;
	}


	return 0;
AddError:
	device_destroy(my_class, my_device_nr);
FileError:
	class_destroy(my_class);
ClassError:
	unregister_chrdev_region(my_device_nr, 1);
	return -1;
}


/**
 * @brief This function is called, when the module is removed from the kernel
 */
static void __exit ModuleExit(void) {
	cdev_del(&my_device);
	device_destroy(my_class, my_device_nr);
	class_destroy(my_class);
	unregister_chrdev_region(my_device_nr, 1);
	printk("Goodbye, Kernel\n");
}


void CreateBoard(char theBoardArray[8][8][4]) {
    // Initialize the board with piece positions
    char initialBoard[8][8][4] = {
        {"BR", "BN", "BB", "BQ", "BK", "BB", "BN", "BR"},
        {"BP", "BP", "BP", "BP", "BP", "BP", "BP", "BP"},
        {"**", "**", "**", "**", "**", "**", "**", "**"},
        {"**", "**", "**", "**", "**", "**", "**", "**"},
        {"**", "**", "**", "**", "**", "**", "**", "**"},
        {"**", "**", "**", "**", "**", "**", "**", "**"},
        {"WP", "WP", "WP", "WP", "WP", "WP", "WP", "WP"},
        {"WR", "WN", "WB", "WQ", "WK", "WB", "WN", "WR"}
    };

    int i = 0;
    int j = 0;

    // Copy the initial board to the actual board
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            strcpy(theBoardArray[i][j], initialBoard[i][j]);
        }
    }
}

void PrintBoard(char theBoardArray[8][8][4]){
    char destinationString[200];
   

    int i = 0;
    int j = 0;
    int k = 0;
    int m = 0;


    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            for(k = 0; k < 2; k++){
                destinationString[m] = theBoardArray[i][j][k];
                m++;
            }
            destinationString[m] = ' ';
            m++;
        }
        destinationString[m] = '\n';
        m++;
    }
    destinationString[m] = '\0';


    printk("%s", destinationString);


}



int WhitePawnAllMovesUser(int whitePawnAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece, char* upgradedPiece){
    int returnValue = 0;
    int checkedSelf = 0;


    // Checks that the white pawn is where the user says it is
    if(strcmp(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WP") != 0){
        printk("There is no white pawn in that position\n");
        return -1;
    }


    if(pieceStartLocation[0][0] == -1){
        printk("User did not enter a real row for the starting piece location\n");
        return -1;
    }


    if(pieceStartLocation[0][1] == -1){
        printk("User did not enter a real column for the starting piece location\n");
        return -1;
    }


    if(pieceEndLocation[0][0] == -1){
        printk("User did not enter a real row for the ending piece location\n");
        return -1;
    }


    if(pieceEndLocation[0][1] == -1){
        printk("User did not enter a real column for the ending piece location\n");
        return -1;
    }

    int i = 0;
    int j = 0;

    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
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


    i = 0;
    j = 0;
    
    // Sees if the location the player wants to move to is possible
    for(i = 0; i < 100; i++){
        for(j = 0; j < 1; j++){
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
                printk("Piece cannot be upgraded\n");
                return -1;
            }


            // If at other end of board and user didn't set a piece to upgrade it to
            if(pieceEndLocation[0][0] == 0 && strcmp(upgradedPiece, "") == 0){
                printk("User didn't specify what to upgrade the piece to\n");
                return -1;
            }


            // Upgrade to Rook
            if(pieceEndLocation[0][0] == 0 && strcmp(upgradedPiece, "WR") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WR");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");


                checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WP"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnBlackKing(theBoardArray);
                    return returnValue;  
                }


            // Upgrade to Knight
            }else if(pieceEndLocation[0][0] == 0 && strcmp(upgradedPiece, "WN") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WN");
		strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                
                checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WP"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnBlackKing(theBoardArray);
                    return returnValue;  
                }


            // Upgrade to Bishop 
            }else if(pieceEndLocation[0][0] == 0 && strcmp(upgradedPiece, "WB") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WB");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**"); 
                
                checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WP"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnBlackKing(theBoardArray);
                    return returnValue;  
                }


            // Upgrade to Queen 
            }else if(pieceEndLocation[0][0] == 0 && strcmp(upgradedPiece, "WQ") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WQ");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**"); 
                
                checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WP"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnBlackKing(theBoardArray);
                    return returnValue;  
                }


            }else if(pieceEndLocation[0][0] == 0 && strcmp(upgradedPiece, "") == 0){
                printk("User did not enter a valid piece to upgrade to 1\n");
                return -1;
            }


            // Move the piece
            strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WP");
            strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
            
            checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);


            if(checkedSelf == 2 || checkedSelf == 3){
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WP"); 
                printk("Can't make that move, puts your king in check/checkmate\n");
                return -1;
            }else{
                printk("Move made\n");
                returnValue = FindCheckAndCheckmateOnBlackKing(theBoardArray);
                return returnValue;  
            }


        }else{
            printk("That is not a possible move\n");
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
                printk("Piece cannot be upgraded\n");
                return -1;
            }


            // If at other end of board and user didn't set a piece to upgrade it to
            if(pieceEndLocation[0][0] == 0 && strcmp(upgradedPiece, "") == 0){
                printk("User didn't specify what to upgrade the piece to\n");
                return -1;
            }


            // Upgrade to Rook
            if(pieceEndLocation[0][0] == 0 && strcmp(upgradedPiece, "WR") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WR");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                
                checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WP"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnBlackKing(theBoardArray);
                    return returnValue;  
                }


            // Upgrade to Knight
            }else if(pieceEndLocation[0][0] == 0 && strcmp(upgradedPiece, "WN") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WN");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                
                checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WP"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnBlackKing(theBoardArray);
                    return returnValue;  
                }


            // Upgrade to Bishop 
            }else if(pieceEndLocation[0][0] == 0 && strcmp(upgradedPiece, "WB") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WB");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**"); 
                
                checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WP"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnBlackKing(theBoardArray);
                    return returnValue;  
                }


            // Upgrade to Queen 
            }else if(pieceEndLocation[0][0] == 0 && strcmp(upgradedPiece, "WQ") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WQ");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**"); 
                
                checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WP"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnBlackKing(theBoardArray);
                    return returnValue;  
                }


            }else if(pieceEndLocation[0][0] == 0 && strcmp(upgradedPiece, "") == 0){
                printk("User did not enter a valid piece to upgrade to 2\n");
                return -1;
            }


                // Take the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "WP");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                
                checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WP"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnBlackKing(theBoardArray);
                    return returnValue;  
                }
                
            }else{
                printk("The piece you want to take is not there\n");
                return -1;
            }
        }else{
            printk("That is not a possible move\n");
            return -1;
        }


    }




}




int FindCheckAndCheckmateOnWhiteKing(char theBoardArray[8][8][4]){
    printk("100");
    //return -3;
    
    int kingCurrLocation[1][2];

    int i = 0;
    int j = 0;

    // Goes through the board, looking for the white king
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            // If we found the white king, store its location
            if(strcmp(theBoardArray[i][j], "WK") == 0){
                kingCurrLocation[0][0] = i;
                kingCurrLocation[0][1] = j;


               //printk("%d %d\n", kingCurrLocation[0][0], kingCurrLocation[0][1]);
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

    i = 0;
    j = 0;

    // Sets all values to -1
    for(i = 0; i < 500; i++){
        for(j = 0; j < 5; j++){
            blackCpuAllPossibleMoves[i][j] = -1;
        }
    }


    // For storing all moves of the individual piece
    int individualPieceAllMoves[100][2];


    // For storing starting location of individual piece
    int pieceLocation[1][2];


    bool stillLooping = true;

    i = 0;
    j = 0;

    // Loops through the board
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
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
    

    printk("101\n");
    //return -3;


    stillLooping = true;
    int k = 0;


    bool thereIsCheck = false;


    while(stillLooping == true){
        printk("110\n");
        //return -3;
        if(k == 500){
            stillLooping = false;
        }


        if(blackCpuAllPossibleMoves[k][0] == -1){
            stillLooping = false;
        }else{
            //printk("HERE: %d %d %d %d %d\n", blackCpuAllPossibleMoves[k][0], blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2], blackCpuAllPossibleMoves[k][3], blackCpuAllPossibleMoves[k][4]);
            // If we found a check
            if((blackCpuAllPossibleMoves[k][3] == kingCurrLocation[0][0]) &&  (blackCpuAllPossibleMoves[k][4] == kingCurrLocation[0][1])){
                printk("and we continue\n");
                //return -3;
                if(blackCpuAllPossibleMoves[k][0] == 0){
                    printk("Check from pawn at index %d %d\n", blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2]);
                    thereIsCheck = true;
                }
                if(blackCpuAllPossibleMoves[k][0] == 1){
                    printk("Check from knight at index %d %d\n", blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2]);
                    thereIsCheck = true;
                }
                if(blackCpuAllPossibleMoves[k][0] == 2){
                    printk("Check from rook at index %d %d\n", blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2]);
                    thereIsCheck = true;
                }
                if(blackCpuAllPossibleMoves[k][0] == 3){
                    printk("Check from bishop at index %d %d\n", blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2]);
                    thereIsCheck = true;
                }
                if(blackCpuAllPossibleMoves[k][0] == 4){
                    printk("Check from queen at index %d %d\n", blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2]);
                    thereIsCheck = true;
                }
                if(blackCpuAllPossibleMoves[k][0] == 5){
                    printk("Check from king at index %d %d\n", blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2]);
                    thereIsCheck = true;
                }
            }else{
                //printk("good god\n");
                //return -3;
            }


            


            k++;
        }
    }


    if(thereIsCheck == false){
        return 1;
    }
    
    printk("102\n");
    //return -3;


    // Now we are going to look for checkmate


    int currIndex2 = 0;


    // For storing all moves of the white king
    int whiteKingAllMoves[100][2];
    WhiteKingAllMovesCpu(whiteKingAllMoves, theBoardArray, kingCurrLocation);


    i = 0;
    j = 0;
    
    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
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
                //printk("HERE: %d %d %d %d %d\n", blackCpuAllPossibleMoves[k][0], blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2], blackCpuAllPossibleMoves[k][3], blackCpuAllPossibleMoves[k][4]);
                // If we found a check
                if((blackCpuAllPossibleMoves[k][3] == kingCurrLocation[0][0]) &&  (blackCpuAllPossibleMoves[k][4] == kingCurrLocation[0][1])){
                    if(blackCpuAllPossibleMoves[k][0] == 0){
                        printk("Future check from pawn at index %d %d\n", blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2]);
                        kingsNextMoveIsChecked = true;
                    }
                    if(blackCpuAllPossibleMoves[k][0] == 1){
                        printk("Future check from knight at index %d %d\n", blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2]);
                        kingsNextMoveIsChecked = true;
                    }
                    if(blackCpuAllPossibleMoves[k][0] == 2){
                        printk("Future check from rook at index %d %d\n", blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2]);
                        kingsNextMoveIsChecked = true;
                    }
                    if(blackCpuAllPossibleMoves[k][0] == 3){
                        printk("Future check from bishop at index %d %d\n", blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2]);
                        kingsNextMoveIsChecked = true;
                    }
                    if(blackCpuAllPossibleMoves[k][0] == 4){
                        printk("Future check from queen at index %d %d\n", blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2]);
                        kingsNextMoveIsChecked = true;
                    }
                    if(blackCpuAllPossibleMoves[k][0] == 5){
                        printk("Future check from king at index %d %d\n", blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2]);
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
        printk("Checkmate\n");
        return 3;
    }else{
        return 2;
    }


   


}



int FindCheckAndCheckmateOnBlackKing(char theBoardArray[8][8][4]){
    int kingCurrLocation[1][2];

    int i = 0;
    int j = 0;
    
    // Goes through the board, looking for the black king
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            // If we found the black king, store its location
            if(strcmp(theBoardArray[i][j], "BK") == 0){
                kingCurrLocation[0][0] = i;
                kingCurrLocation[0][1] = j;


               //printk("%d %d\n", kingCurrLocation[0][0], kingCurrLocation[0][1]);
            }
        }
    }




    // For storing all possible moves
    // 1. Piece type
    // 2. Starting x 
    // 3. Starting y
    // 4. Ending x
    // 5. Ending y
    int whiteCpuAllPossibleMoves[500][5];


    // For storing current index in the above list
    int currIndex = 0;

    i = 0;
    j = 0;

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

    i = 0;
    j = 0;

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
            // If we found a black queen
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


    stillLooping = true;
    int k = 0;


    bool thereIsCheck = false;


    while(stillLooping == true){
        if(k == 500){
            stillLooping = false;
        }


        if(whiteCpuAllPossibleMoves[k][0] == -1){
            stillLooping = false;
        }else{
            //printk("HERE: %d %d %d %d %d\n", blackCpuAllPossibleMoves[k][0], blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2], blackCpuAllPossibleMoves[k][3], blackCpuAllPossibleMoves[k][4]);
            // If we found a check
            if((whiteCpuAllPossibleMoves[k][3] == kingCurrLocation[0][0]) &&  (whiteCpuAllPossibleMoves[k][4] == kingCurrLocation[0][1])){
                if(whiteCpuAllPossibleMoves[k][0] == 0){
                    printk("Check from pawn at index %d %d\n", whiteCpuAllPossibleMoves[k][1], whiteCpuAllPossibleMoves[k][2]);
                    thereIsCheck = true;
                }
                if(whiteCpuAllPossibleMoves[k][0] == 1){
                    printk("Check from knight at index %d %d\n", whiteCpuAllPossibleMoves[k][1], whiteCpuAllPossibleMoves[k][2]);
                    thereIsCheck = true;
                }
                if(whiteCpuAllPossibleMoves[k][0] == 2){
                    printk("Check from rook at index %d %d\n", whiteCpuAllPossibleMoves[k][1], whiteCpuAllPossibleMoves[k][2]);
                    thereIsCheck = true;
                }
                if(whiteCpuAllPossibleMoves[k][0] == 3){
                    printk("Check from bishop at index %d %d\n", whiteCpuAllPossibleMoves[k][1], whiteCpuAllPossibleMoves[k][2]);
                    thereIsCheck = true;
                }
                if(whiteCpuAllPossibleMoves[k][0] == 4){
                    printk("Check from queen at index %d %d\n", whiteCpuAllPossibleMoves[k][1], whiteCpuAllPossibleMoves[k][2]);
                    thereIsCheck = true;
                }
                if(whiteCpuAllPossibleMoves[k][0] == 5){
                    printk("Check from king at index %d %d\n", whiteCpuAllPossibleMoves[k][1], whiteCpuAllPossibleMoves[k][2]);
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

    i = 0;
    j = 0;

    // For storing all moves of the black king
    int blackKingAllMoves[100][2];
    BlackKingAllMovesCpu(blackKingAllMoves, theBoardArray, kingCurrLocation);


    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
            if(blackKingAllMoves[i][0] != -1){
                currIndex2++;
                j++;
            }
        }
    }




    bool weLoveLooping = true;


    int currIndex3 = -1;


    while(weLoveLooping == true && currIndex3 < currIndex2-1){
        currIndex3++;


        
        kingCurrLocation[0][0] = blackKingAllMoves[currIndex3][0];
        kingCurrLocation[0][1] = blackKingAllMoves[currIndex3][1];




        bool kingsNextMoveIsChecked = false;


        stillLooping = true;
        int k = 0;




        while(stillLooping == true){
            if(k == 500){
                stillLooping = false;
            }


            if(whiteCpuAllPossibleMoves[k][0] == -1){
                stillLooping = false;
            }else{
                //printk("HERE: %d %d %d %d %d\n", blackCpuAllPossibleMoves[k][0], blackCpuAllPossibleMoves[k][1], blackCpuAllPossibleMoves[k][2], blackCpuAllPossibleMoves[k][3], blackCpuAllPossibleMoves[k][4]);
                // If we found a check
                if((whiteCpuAllPossibleMoves[k][3] == kingCurrLocation[0][0]) &&  (whiteCpuAllPossibleMoves[k][4] == kingCurrLocation[0][1])){
                    if(whiteCpuAllPossibleMoves[k][0] == 0){
                        printk("Future check from pawn at index %d %d\n", whiteCpuAllPossibleMoves[k][1], whiteCpuAllPossibleMoves[k][2]);
                        kingsNextMoveIsChecked = true;
                    }
                    if(whiteCpuAllPossibleMoves[k][0] == 1){
                        printk("Future check from knight at index %d %d\n", whiteCpuAllPossibleMoves[k][1], whiteCpuAllPossibleMoves[k][2]);
                        kingsNextMoveIsChecked = true;
                    }
                    if(whiteCpuAllPossibleMoves[k][0] == 2){
                        printk("Future check from rook at index %d %d\n", whiteCpuAllPossibleMoves[k][1], whiteCpuAllPossibleMoves[k][2]);
                        kingsNextMoveIsChecked = true;
                    }
                    if(whiteCpuAllPossibleMoves[k][0] == 3){
                        printk("Future check from bishop at index %d %d\n", whiteCpuAllPossibleMoves[k][1], whiteCpuAllPossibleMoves[k][2]);
                        kingsNextMoveIsChecked = true;
                    }
                    if(whiteCpuAllPossibleMoves[k][0] == 4){
                        printk("Future check from queen at index %d %d\n", whiteCpuAllPossibleMoves[k][1], whiteCpuAllPossibleMoves[k][2]);
                        kingsNextMoveIsChecked = true;
                    }
                    if(whiteCpuAllPossibleMoves[k][0] == 5){
                        printk("Future check from king at index %d %d\n", whiteCpuAllPossibleMoves[k][1], whiteCpuAllPossibleMoves[k][2]);
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
        printk("Checkmate\n");
        return 3;
    }else{
        return 2;
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


    
    if(theLocation[0] == 'a'){
        pieceLocation[0][1] = 0;
    }else if(theLocation[0] == 'b'){
        pieceLocation[0][1] = 1;
    }else if(theLocation[0] == 'c'){
        pieceLocation[0][1] = 2;
    }else if(theLocation[0] == 'd'){
        pieceLocation[0][1] = 3;
    }else if(theLocation[0] == 'e'){
        pieceLocation[0][1] = 4;
    }else if(theLocation[0] == 'f'){
        pieceLocation[0][1] = 5;
    }else if(theLocation[0] == 'g'){
        pieceLocation[0][1] = 6;
    }else if(theLocation[0] == 'h'){
        pieceLocation[0][1] = 7;
    }else{
        pieceLocation[0][1] = -1;
    }


    //printk("%d ", pieceLocation[0][0]);
    //printk("%d ", pieceLocation[0][1]);


}


int LookForWhiteKing(char theBoardArray[8][8][4]){
    int i = 0;
    int j = 0;
    
    printk("\n");
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            if(strcmp(theBoardArray[i][j], "WK") == 0){
                return 1;
            }
        }
    }
    return -1;


}


int LookForBlackKing(char theBoardArray[8][8][4]){
    int i = 0;
    int j = 0;
    
    printk("\n");
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
            if(strcmp(theBoardArray[i][j], "BK") == 0){
                return 1;
            }
        }
    }
    return -1;


}



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
                //return -3;
                // Move the piece
                strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][1]][whiteCpuAllPossibleMoves[randomNumber][2]], "**");
                strcpy(theBoardArray[whiteCpuAllPossibleMoves[randomNumber][3]][whiteCpuAllPossibleMoves[randomNumber][4]], "WQ");
                
                return 1;


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
                
                return 1;
                
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
            
            return 1;


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
            
            return 1;


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
            
            return 1;


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
            
            return 1;


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
            
            return 1;


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




int BlackCpuPickMove(char theBoardArray[8][8][4]){
    int returnValue = 0;
    // For storing all possible moves
    // 1. Piece type
    // 2. Starting x 
    // 3. Starting y
    // 4. Ending x
    // 5. Ending y
    int blackCpuAllPossibleMoves[500][5];


    // For storing current index in the above list
    int currIndex = 0;
    
    int i = 0;
    int j = 0;


    // Sets all values to -1
    for(i = 0; i < 500; i++){
        for(j = 0; j < 5; j++){
            blackCpuAllPossibleMoves[i][j] = -1;
        }
    }


    // For storing all moves of the individual piece
    int individualPieceAllMoves[100][2];


    // For storing starting location of individual piece
    int pieceLocation[1][2];


    bool stillLooping = true;
    
    i = 0;
    j = 0;


    // Loops through the board
    for(i = 0; i < 8; i++){
        for(j = 0; j < 8; j++){
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
           // printk("%d ", blackCpuAllPossibleMoves[i][j]);
        //}
        //printk("\n");  
        //}
    //}
    //printk("%d\n", currIndex);




    // Seed the random number generator
    //srand(time(NULL));


    // Generate a random number to randomly pick the move
    //int randomNumber = (rand() % currIndex);


    // Print the random number
    //printk("Random number: %d\n", randomNumber);


    //printk("Black:\n");
    //printk("%d ", blackCpuAllPossibleMoves[randomNumber][0]);
    //printk("%d ", blackCpuAllPossibleMoves[randomNumber][1]);
    //printk("%d ", blackCpuAllPossibleMoves[randomNumber][2]);
    //printk("%d ", blackCpuAllPossibleMoves[randomNumber][3]);
    //printk("%d ", blackCpuAllPossibleMoves[randomNumber][4]);
    //printk("\n");


    int checkedSelf = 0;


    bool weLoveLooping = true;


    int coolCounter = 0;


    while(weLoveLooping == true){
        //int randomNumber = (rand() % currIndex);
        
        unsigned int randomNumber;
        get_random_bytes(&randomNumber, sizeof(randomNumber));
        randomNumber %= currIndex;


        if(coolCounter == 50){
            weLoveLooping = false;
            printk("cool\n");
            return 3;
        }
        // If the pieced to be moved is a pawn
        if(blackCpuAllPossibleMoves[randomNumber][0] == 0){
            // If the pawn is ready for promotion, make it a queen
            if(blackCpuAllPossibleMoves[randomNumber][3] == 7){
                // Move the piece
                strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][1]][blackCpuAllPossibleMoves[randomNumber][2]], "**");
                strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][3]][blackCpuAllPossibleMoves[randomNumber][4]], "BQ"); 

		return 1;

                checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    // Move the piece
                    strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][1]][blackCpuAllPossibleMoves[randomNumber][2]], "BP");
                    strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][3]][blackCpuAllPossibleMoves[randomNumber][4]], "**");  


                    coolCounter++;  
                }else{
                    weLoveLooping = false;
                }
                
            }else{
                // Move the piece
                strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][1]][blackCpuAllPossibleMoves[randomNumber][2]], "**");
                strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][3]][blackCpuAllPossibleMoves[randomNumber][4]], "BP");   
                
                return 1;


                checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    // Move the piece
                    strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][1]][blackCpuAllPossibleMoves[randomNumber][2]], "BP");
                    strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][3]][blackCpuAllPossibleMoves[randomNumber][4]], "**");  


                    coolCounter++;  
                }else{
                    weLoveLooping = false;
                } 
                
            }
        }
        // If the piece to be moved is a knight
        else if(blackCpuAllPossibleMoves[randomNumber][0] == 1){
            // Move the piece
            strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][1]][blackCpuAllPossibleMoves[randomNumber][2]], "**");
            strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][3]][blackCpuAllPossibleMoves[randomNumber][4]], "BN");
            
            return 1;


            checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


            if(checkedSelf == 2 || checkedSelf == 3){
                // Move the piece
                strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][1]][blackCpuAllPossibleMoves[randomNumber][2]], "BN");
                strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][3]][blackCpuAllPossibleMoves[randomNumber][4]], "**");  


                coolCounter++;  
            }else{
                weLoveLooping = false;
            }


        }
        // If the piece to be moved is a rook
        else if(blackCpuAllPossibleMoves[randomNumber][0] == 2){
            // Move the piece
            strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][1]][blackCpuAllPossibleMoves[randomNumber][2]], "**");
            strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][3]][blackCpuAllPossibleMoves[randomNumber][4]], "BR"); 
            
            return 1;


            checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


            if(checkedSelf == 2 || checkedSelf == 3){
                // Move the piece
                strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][1]][blackCpuAllPossibleMoves[randomNumber][2]], "BR");
                strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][3]][blackCpuAllPossibleMoves[randomNumber][4]], "**");  


                coolCounter++;  
            }else{
                weLoveLooping = false;
            }
            
        }
        // If the piece to be moved is a bishop
        else if(blackCpuAllPossibleMoves[randomNumber][0] == 3){
            // Move the piece
            strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][1]][blackCpuAllPossibleMoves[randomNumber][2]], "**");
            strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][3]][blackCpuAllPossibleMoves[randomNumber][4]], "BB");
            
            return 1;


            checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


            if(checkedSelf == 2 || checkedSelf == 3){
                // Move the piece
                strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][1]][blackCpuAllPossibleMoves[randomNumber][2]], "BB");
                strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][3]][blackCpuAllPossibleMoves[randomNumber][4]], "**");  


                coolCounter++;  
            }else{
                weLoveLooping = false;
            }


        }
        // If the piece to be moved is a queen
        else if(blackCpuAllPossibleMoves[randomNumber][0] == 4){
            // Move the piece
            strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][1]][blackCpuAllPossibleMoves[randomNumber][2]], "**");
            strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][3]][blackCpuAllPossibleMoves[randomNumber][4]], "BQ");
            
            return 1;


            checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


            if(checkedSelf == 2 || checkedSelf == 3){
                // Move the piece
                strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][1]][blackCpuAllPossibleMoves[randomNumber][2]], "BQ");
                strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][3]][blackCpuAllPossibleMoves[randomNumber][4]], "**");  


                coolCounter++;  
            }else{
                weLoveLooping = false;
            }
            
        }
        // If the piece to be moved is a king
        else if(blackCpuAllPossibleMoves[randomNumber][0] == 5){
            // Move the piece
            strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][1]][blackCpuAllPossibleMoves[randomNumber][2]], "**");
            strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][3]][blackCpuAllPossibleMoves[randomNumber][4]], "BK");
            
            return 1;


            checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


            if(checkedSelf == 2 || checkedSelf == 3){
                // Move the piece
                strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][1]][blackCpuAllPossibleMoves[randomNumber][2]], "BK");
                strcpy(theBoardArray[blackCpuAllPossibleMoves[randomNumber][3]][blackCpuAllPossibleMoves[randomNumber][4]], "**");  


                coolCounter++;  
            }else{
                weLoveLooping = false;
            }


        }


    }
    


        


    returnValue = FindCheckAndCheckmateOnWhiteKing(theBoardArray);
    return returnValue;


}


int WhiteKingAllMovesUser(int whiteKingAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece){
    int returnValue = 0;
    int checkedSelf = 0;


    // Checks that the white king is where the user says it is
    if(strcmp(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WK") != 0){
        printk("There is no white king in that position\n");
        return -1;
    }


    if(pieceStartLocation[0][0] == -1){
        printk("User did not enter a real row for the starting piece location\n");
        return -1;
    }


    if(pieceStartLocation[0][1] == -1){
        printk("User did not enter a real column for the starting piece location\n");
        return -1;
    }


    if(pieceEndLocation[0][0] == -1){
        printk("User did not enter a real row for the ending piece location\n");
        return -1;
    }


    if(pieceEndLocation[0][1] == -1){
        printk("User did not enter a real column for the ending piece location\n");
        return -1;
    }
    
    int i = 0;
    int j = 0;


    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
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

    i = 0;
    j = 0;

    // Sees if the location the player wants to move to is possible
    for(i = 0; i < 100; i++){
        for(j = 0; j < 1; j++){
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
            
            checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);


            if(checkedSelf == 2 || checkedSelf == 3){
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WK"); 
                printk("Can't make that move, puts your king in check/checkmate\n");
                return -1;
            }else{
                printk("Move made\n");
                returnValue = FindCheckAndCheckmateOnBlackKing(theBoardArray);
                return returnValue;  
            }
        }else{
            printk("That is not a possible move\n");
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
                
                checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WK"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnBlackKing(theBoardArray);
                    return returnValue;  
                }
            }else{
                printk("The piece you want to take is not there\n");
                return -1;
            }
        }else{
            printk("That is not a possible move\n");
            return -1;
        }


    }


}





int WhiteRookAllMovesUser(int whiteRookAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece){
    int returnValue = 0;
    int checkedSelf = 0;
    
    //printk("GREAT!\n");


    // Checks that the white rook is where the user says it is
    if(strcmp(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WR") != 0){
        printk("There is no white rook in that position\n");
        return -1;
    }


    if(pieceStartLocation[0][0] == -1){
        printk("User did not enter a real row for the starting piece location\n");
        return -1;
    }


    if(pieceStartLocation[0][1] == -1){
        printk("User did not enter a real column for the starting piece location\n");
        return -1;
    }


    if(pieceEndLocation[0][0] == -1){
        printk("User did not enter a real row for the ending piece location\n");
        return -1;
    }


    if(pieceEndLocation[0][1] == -1){
        printk("User did not enter a real column for the ending piece location\n");
        return -1;
    }

    int i = 0;
    int j = 0;

    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
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

    i = 0;
    j = 0;

    // Sees if the location the player wants to move to is possible
    for(i = 0; i < 100; i++){
        for(j = 0; j < 1; j++){
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
    	    checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);


            if(checkedSelf == 2 || checkedSelf == 3){
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WR"); 
                printk("Can't make that move, puts your king in check/checkmate\n");
                return -1;
            }else{
                printk("Move made\n");
                returnValue = FindCheckAndCheckmateOnBlackKing(theBoardArray);
                return returnValue;  
            }
        }else{
            printk("That is not a possible move\n");
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
                
                checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WR"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnBlackKing(theBoardArray);
                    return returnValue;  
                }
            }else{
                printk("The piece you want to take is not there\n");
                return -1;
            }
        }else{
            printk("That is not a possible move\n");
            return -1;
        }


    }
}


int WhiteBishopAllMovesUser(int whiteBishopAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece){
    int returnValue = 0;
    int checkedSelf = 0;


    // Checks that the white bishop is where the user says it is
    if(strcmp(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WB") != 0){
        printk("There is no white bishop in that position\n");
        return -1;
    }


    if(pieceStartLocation[0][0] == -1){
        printk("User did not enter a real row for the starting piece location\n");
        return -1;
    }


    if(pieceStartLocation[0][1] == -1){
        printk("User did not enter a real column for the starting piece location\n");
        return -1;
    }


    if(pieceEndLocation[0][0] == -1){
        printk("User did not enter a real row for the ending piece location\n");
        return -1;
    }


    if(pieceEndLocation[0][1] == -1){
        printk("User did not enter a real column for the ending piece location\n");
        return -1;
    }

    int i = 0;
    int j = 0;

    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
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

    i = 0;
    j = 0;

    // Sees if the location the player wants to move to is possible
    for(i = 0; i < 100; i++){
        for(j = 0; j < 1; j++){
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
            
            checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);


            if(checkedSelf == 2 || checkedSelf == 3){
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WB"); 
                printk("Can't make that move, puts your king in check/checkmate\n");
                return -1;
            }else{
                printk("Move made\n");
                returnValue = FindCheckAndCheckmateOnBlackKing(theBoardArray);
                return returnValue;  
            }
        }else{
            printk("That is not a possible move\n");
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
                
                checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WB"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnBlackKing(theBoardArray);
                    return returnValue;  
                }
            }else{
                printk("The piece you want to take is not there\n");
                return -1;
            }
        }else{
            printk("That is not a possible move\n");
            return -1;
        }


    }
}



int WhiteQueenAllMovesUser(int whiteQueenAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece){
    int returnValue = 0;
    int checkedSelf = 0;


    // Checks that the white queen is where the user says it is
    if(strcmp(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WQ") != 0){
        printk("There is no white queen in that position\n");
        return -1;
    }


    if(pieceStartLocation[0][0] == -1){
        printk("User did not enter a real row for the starting piece location\n");
        return -1;
    }


    if(pieceStartLocation[0][1] == -1){
        printk("User did not enter a real column for the starting piece location\n");
        return -1;
    }


    if(pieceEndLocation[0][0] == -1){
        printk("User did not enter a real row for the ending piece location\n");
        return -1;
    }


    if(pieceEndLocation[0][1] == -1){
        printk("User did not enter a real column for the ending piece location\n");
        return -1;
    }

    int i = 0;
    int j = 0;

    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
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
        else if (theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1] 
+currIndex2][0] == '*'){
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

    i = 0;
    j = 0;

    // Sees if the location the player wants to move to is possible
    for(i = 0; i < 100; i++){
        for(j = 0; j < 1; j++){
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
            
            checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);


            if(checkedSelf == 2 || checkedSelf == 3){
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WQ"); 
                printk("Can't make that move, puts your king in check/checkmate\n");
                return -1;
            }else{
                printk("Move made\n");
                returnValue = FindCheckAndCheckmateOnBlackKing(theBoardArray);
                return returnValue;  
            }
        }else{
            printk("That is not a possible move\n");
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
                
                checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WQ"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnBlackKing(theBoardArray);
                    return returnValue;  
                }
            }else{
                printk("The piece you want to take is not there\n");
                return -1;
            }
        }else{
            printk("That is not a possible move\n");
            return -1;
        }


    }
}



int BlackPawnAllMovesUser(int blackPawnAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece, char* upgradedPiece){
    int returnValue = 0;
    int checkedSelf = 0;


    // Checks that the black pawn is where the user says it is
    if(strcmp(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BP") != 0){
        printk("There is no black pawn in that position\n");
        return -1;
    }


    if(pieceStartLocation[0][0] == -1){
        printk("User did not enter a real row for the starting piece location\n");
        return -1;
    }


    if(pieceStartLocation[0][1] == -1){
        printk("User did not enter a real column for the starting piece location\n");
        return -1;
    }


    if(pieceEndLocation[0][0] == -1){
        printk("User did not enter a real row for the ending piece location\n");
        return -1;
    }


    if(pieceEndLocation[0][1] == -1){
        printk("User did not enter a real column for the ending piece location\n");
        return -1;
    }

    int i = 0;
    int j = 0;

    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
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

    i = 0;
    j = 0;

    // Sees if the location the player wants to move to is possible
    for(i = 0; i < 100; i++){
        for(j = 0; j < 1; j++){
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
                printk("Piece cannot be upgraded\n");
                return -1;
            }


            // If at other end of board and user didn't set a piece to upgrade it to
            if(pieceEndLocation[0][0] == 7 && strcmp(upgradedPiece, "") == 0){
                printk("User didn't specify what to upgrade the piece to\n");
                return -1;
            }


            // Upgrade to Rook
            if(pieceEndLocation[0][0] == 7 && strcmp(upgradedPiece, "BR") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BR");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                
                checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BP"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnWhiteKing(theBoardArray);
                    return returnValue;  
                }


            // Upgrade to Knight
            }else if(pieceEndLocation[0][0] == 7 && strcmp(upgradedPiece, "BN") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BN");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                
                checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BP"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnWhiteKing(theBoardArray);
                    return returnValue;  
                }
            // Upgrade to Bishop 
            }else if(pieceEndLocation[0][0] == 7 && strcmp(upgradedPiece, "BB") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BB");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**"); 
                
                checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BP"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnWhiteKing(theBoardArray);
                    return returnValue;  
                }
            // Upgrade to Queen 
            }else if(pieceEndLocation[0][0] == 7 && strcmp(upgradedPiece, "BQ") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BQ");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**"); 
                
                checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BP"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnWhiteKing(theBoardArray);
                    return returnValue;  
                }
            }else if(pieceEndLocation[0][0] == 7 && strcmp(upgradedPiece, "") == 0){
                printk("User did not enter a valid piece to upgrade to\n");
                return -1;
            }


            // Move the piece
            strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BP");
            strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
            
            checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


            if(checkedSelf == 2 || checkedSelf == 3){
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BP"); 
                printk("Can't make that move, puts your king in check/checkmate\n");
                return -1;
            }else{
                printk("Move made\n");
                returnValue = FindCheckAndCheckmateOnWhiteKing(theBoardArray);
                return returnValue;  
            }
        }else{
            printk("That is not a possible move\n");
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
                printk("Piece cannot be upgraded\n");
                return -1;
            }


            // If at other end of board and user didn't set a piece to upgrade it to
            if(pieceEndLocation[0][0] == 7 && strcmp(upgradedPiece, "") == 0){
                printk("User didn't specify what to upgrade the piece to\n");
                return -1;
            }


            // Upgrade to Rook
            if(pieceEndLocation[0][0] == 7 && strcmp(upgradedPiece, "BR") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BR");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                
                checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BP"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnWhiteKing(theBoardArray);
                    return returnValue;  
                }
            // Upgrade to Knight
            }else if(pieceEndLocation[0][0] == 7 && strcmp(upgradedPiece, "BN") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BN");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                
                checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BP"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnWhiteKing(theBoardArray);
                    return returnValue;  
                }
            // Upgrade to Bishop 
            }else if(pieceEndLocation[0][0] == 7 && strcmp(upgradedPiece, "BB") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BB");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**"); 
                
                checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BP"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnWhiteKing(theBoardArray);
                    return returnValue;  
                }
            // Upgrade to Queen 
            }else if(pieceEndLocation[0][0] == 7 && strcmp(upgradedPiece, "BQ") == 0){
                // Move the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BQ");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**"); 
                
                checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BP"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnWhiteKing(theBoardArray);
                    return returnValue;  
                }
            }else if(pieceEndLocation[0][0] == 7 && strcmp(upgradedPiece, "") == 0){
                printk("User did not enter a valid piece to upgrade to\n");
                return -1;
            }


                // Take the piece
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "BP");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "**");
                
                checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BP"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnWhiteKing(theBoardArray);
                    return returnValue;  
                }
            }else{
                printk("The piece you want to take is not there\n");
                return -1;
            }
        }else{
            printk("That is not a possible move\n");
            return -1;
        }


    }




}



int BlackKingAllMovesUser(int blackKingAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece){
    int returnValue = 0;
    int checkedSelf = 0;


    // Checks that the black king is where the user says it is
    if(strcmp(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BK") != 0){
        printk("There is no black king in that position\n");
        return -1;
    }


    if(pieceStartLocation[0][0] == -1){
        printk("User did not enter a real row for the starting piece location\n");
        return -1;
    }


    if(pieceStartLocation[0][1] == -1){
        printk("User did not enter a real column for the starting piece location\n");
        return -1;
    }


    if(pieceEndLocation[0][0] == -1){
        printk("User did not enter a real row for the ending piece location\n");
        return -1;
    }


    if(pieceEndLocation[0][1] == -1){
        printk("User did not enter a real column for the ending piece location\n");
        return -1;
    }

    int i = 0;
    int j = 0;

    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
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

    i = 0;
    j = 0;
    
    // Sees if the location the player wants to move to is possible
    for(i = 0; i < 100; i++){
        for(j = 0; j < 1; j++){
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
            
            checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


            if(checkedSelf == 2 || checkedSelf == 3){
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BK"); 
                printk("Can't make that move, puts your king in check/checkmate\n");
                return -1;
            }else{
                printk("Move made\n");
                returnValue = FindCheckAndCheckmateOnWhiteKing(theBoardArray);
                return returnValue;  
            }
        }else{
            printk("That is not a possible move\n");
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
                
                checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BK"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnWhiteKing(theBoardArray);
                    return returnValue;  
                }
            }else{
                printk("The piece you want to take is not there\n");
                return -1;
            }
        }else{
            printk("That is not a possible move\n");
            return -1;
        }


    }


}


int BlackKnightAllMovesUser(int blackKnightAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece){
    int returnValue = 0;
    int checkedSelf = 0;


    // Checks that the black knight is where the user says it is
    if(strcmp(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BN") != 0){
        printk("There is no black knight in that position\n");
        return -1;
    }


    if(pieceStartLocation[0][0] == -1){
        printk("User did not enter a real row for the starting piece location\n");
        return -1;
    }


    if(pieceStartLocation[0][1] == -1){
        printk("User did not enter a real column for the starting piece location\n");
        return -1;
    }


    if(pieceEndLocation[0][0] == -1){
        printk("User did not enter a real row for the ending piece location\n");
        return -1;
    }


    if(pieceEndLocation[0][1] == -1){
        printk("User did not enter a real column for the ending piece location\n");
        return -1;
    }

    int i = 0;
    int j = 0;
    
    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
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

    i = 0;
    j = 0;

    // Sees if the location the player wants to move to is possible
    for(i = 0; i < 100; i++){
        for(j = 0; j < 1; j++){
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
            
            checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


            if(checkedSelf == 2 || checkedSelf == 3){
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BN"); 
                printk("Can't make that move, puts your king in check/checkmate\n");
                return -1;
            }else{
                printk("Move made\n");
                returnValue = FindCheckAndCheckmateOnWhiteKing(theBoardArray);
                return returnValue;  
            }
        }else{
            printk("That is not a possible move\n");
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
                
                checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BN"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnWhiteKing(theBoardArray);
                    return returnValue;  
                }
            }else{
                printk("The piece you want to take is not there\n");
                return -1;
            }
        }else{
            printk("That is not a possible move\n");
            return -1;
        }


    }
    
}


int BlackRookAllMovesUser(int blackRookAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece){
    int returnValue = 0;
    int checkedSelf = 0;


    // Checks that the black rook is where the user says it is
    if(strcmp(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BR") != 0){
        printk("There is no white rook in that position\n");
        return -1;
    }


    if(pieceStartLocation[0][0] == -1){
        printk("User did not enter a real row for the starting piece location\n");
        return -1;
    }


    if(pieceStartLocation[0][1] == -1){
        printk("User did not enter a real column for the starting piece location\n");
        return -1;
    }


    if(pieceEndLocation[0][0] == -1){
        printk("User did not enter a real row for the ending piece location\n");
        return -1;
    }


    if(pieceEndLocation[0][1] == -1){
        printk("User did not enter a real column for the ending piece location\n");
        return -1;
    }

    int i = 0;
    int j = 0;

    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
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

    i = 0;
    j = 0;

    // Sees if the location the player wants to move to is possible
    for(i = 0; i < 100; i++){
        for(j = 0; j < 1; j++){
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
            
            checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


            if(checkedSelf == 2 || checkedSelf == 3){
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BR"); 
                printk("Can't make that move, puts your king in check/checkmate\n");
                return -1;
            }else{
                printk("Move made\n");
                returnValue = FindCheckAndCheckmateOnWhiteKing(theBoardArray);
                return returnValue;  
            }
        }else{
            printk("That is not a possible move\n");
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
                
                checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BR"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnWhiteKing(theBoardArray);
                    return returnValue;  
                }
            }else{
                printk("The piece you want to take is not there\n");
                return -1;
            }
        }else{
            printk("That is not a possible move\n");
            return -1;
        }


    }
}


int BlackBishopAllMovesUser(int blackBishopAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece){
    int returnValue = 0;
    int checkedSelf = 0;


    // Checks that the black bishop is where the user says it is
    if(strcmp(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BB") != 0){
        printk("There is no black bishop in that position\n");
        return -1;
    }


    if(pieceStartLocation[0][0] == -1){
        printk("User did not enter a real row for the starting piece location\n");
        return -1;
    }


    if(pieceStartLocation[0][1] == -1){
        printk("User did not enter a real column for the starting piece location\n");
        return -1;
    }


    if(pieceEndLocation[0][0] == -1){
        printk("User did not enter a real row for the ending piece location\n");
        return -1;
    }


    if(pieceEndLocation[0][1] == -1){
        printk("User did not enter a real column for the ending piece location\n");
        return -1;
    }

    int i = 0;
    int j = 0;

    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
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

    i = 0;
    j = 0;

    // Sees if the location the player wants to move to is possible
    for(i = 0; i < 100; i++){
        for(j = 0; j < 1; j++){
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
            
            checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


            if(checkedSelf == 2 || checkedSelf == 3){
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BB"); 
                printk("Can't make that move, puts your king in check/checkmate\n");
                return -1;
            }else{
                printk("Move made\n");
                returnValue = FindCheckAndCheckmateOnWhiteKing(theBoardArray);
                return returnValue;  
            }
        }else{
            printk("That is not a possible move\n");
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
                
                checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BB"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnWhiteKing(theBoardArray);
                    return returnValue;  
                }
            }else{
                printk("The piece you want to take is not there\n");
                return -1;
            }
        }else{
            printk("That is not a possible move\n");
            return -1;
        }


    }
}



int BlackQueenAllMovesUser(int blackQueenAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece){
    int returnValue = 0;
    int checkedSelf = 0;


    // Checks that the black queen is where the user says it is
    if(strcmp(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BQ") != 0){
        printk("There is no black queen in that position\n");
        return -1;
    }


    if(pieceStartLocation[0][0] == -1){
        printk("User did not enter a real row for the starting piece location\n");
        return -1;
    }


    if(pieceStartLocation[0][1] == -1){
        printk("User did not enter a real column for the starting piece location\n");
        return -1;
    }


    if(pieceEndLocation[0][0] == -1){
        printk("User did not enter a real row for the ending piece location\n");
        return -1;
    }


    if(pieceEndLocation[0][1] == -1){
        printk("User did not enter a real column for the ending piece location\n");
        return -1;
    }

    int i = 0;
    int j = 0;

    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
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
    for(i = 0; i < 100; i++){
        for(j = 0; j < 1; j++){
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
            
            checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


            if(checkedSelf == 2 || checkedSelf == 3){
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BQ"); 
                printk("Can't make that move, puts your king in check/checkmate\n");
                return -1;
            }else{
                printk("Move made\n");
                returnValue = FindCheckAndCheckmateOnWhiteKing(theBoardArray);
                return returnValue;  
            }
        }else{
            printk("That is not a possible move\n");
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
                
                checkedSelf = FindCheckAndCheckmateOnBlackKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "BQ"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnWhiteKing(theBoardArray);
                    return returnValue;  
                }
            }else{
                printk("The piece you want to take is not there\n");
                return -1;
            }
        }else{
            printk("That is not a possible move\n");
            return -1;
        }


    }
}


int WhitePawnAllMovesCpu(int whitePawnAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]){

    int i = 0;
    int j = 0;

    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
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


    return 1;

}


int WhiteKingAllMovesCpu(int whiteKingAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]){

    int i = 0;
    int j = 0;

    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
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



    return 1;
}


int WhiteKnightAllMovesCpu(int whiteKnightAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]){

    int i = 0;
    int j = 0;

    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
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


    return 1;
}



int WhiteRookAllMovesCpu(int whiteRookAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]){

    int i = 0;
    int j = 0;

    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
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


    return 1;

}


int WhiteBishopAllMovesCpu(int whiteBishopAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]){

    int i = 0;
    int j = 0;

    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
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


    return 1;

}


int WhiteQueenAllMovesCpu(int whiteQueenAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]){


    int i = 0;
    int j = 0;
    
    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
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
    return 1;

}


int BlackPawnAllMovesCpu(int blackPawnAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]){

    int i = 0;
    int j = 0;


    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
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


    return 1;

}










int BlackKingAllMovesCpu(int blackKingAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]){

    int i = 0;
    int j = 0;

    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
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


    return 1;

}








int BlackKnightAllMovesCpu(int blackKnightAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]){


    int i = 0;
    int j = 0;

    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
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



    return 1;
    
}






int BlackRookAllMovesCpu(int blackRookAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]){

    int i = 0;
    int j = 0;

    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
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

    return 1;
}


int BlackBishopAllMovesCpu(int blackBishopAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]){

    int i = 0;
    int j = 0;

    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
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

    return 1;
}

int BlackQueenAllMovesCpu(int blackQueenAllMovesCpu[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2]){
    
    int i = 0;
    int j = 0;

    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
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

    return 1;
}

void ClearBuffer(char buffer[]){
    int i = 0;
    for(i = 0; i < sizeof(buffer); i++){
        buffer[i] = '\0';
    }
}

void CopyToBuffer(char buffer[], char string[]){
    printk("CopyToBuffer Function:\n");
    int i = 0;
    for(i = 0; i < sizeof(string); i++){
        buffer[i] = string[i];
    }
}



int WhiteKnightAllMovesUser(int whiteKnightAllMovesUser[100][2], char theBoardArray[8][8][4], int pieceStartLocation[1][2], int pieceEndLocation[1][2], char* takenPiece){
    int returnValue = 0;
    int checkedSelf = 0;
    
    // Checks that the white knight is where the user says it is
    if(strcmp(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WN") != 0){
        printk("There is no white knight in that position\n");
        return -1;
    }


    if(pieceStartLocation[0][0] == -1){
        printk("User did not enter a real row for the starting piece location\n");
        return -1;
    }


    if(pieceStartLocation[0][1] == -1){
        printk("User did not enter a real column for the starting piece location\n");
        return -1;
    }


    if(pieceEndLocation[0][0] == -1){
        printk("User did not enter a real row for the ending piece location\n");
        return -1;
    }


    if(pieceEndLocation[0][1] == -1){
        printk("User did not enter a real column for the ending piece location\n");
        return -1;
    }

    int i = 0;
    int j = 0;

    for(i = 0; i < 100; i++){
        for(j = 0; j < 2; j++){
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

    i = 0;
    j = 0;

    // Sees if the location the player wants to move to is possible
    for(i = 0; i < 100; i++){
        for(j = 0; j < 1; j++){
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
            
            checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);


            if(checkedSelf == 2 || checkedSelf == 3){
                strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WN"); 
                printk("Can't make that move, puts your king in check/checkmate\n");
                return -1;
            }else{
                printk("Move made\n");
                returnValue = FindCheckAndCheckmateOnBlackKing(theBoardArray);
                return returnValue;  
            }
        }else{
            printk("That is not a possible move\n");
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
                
                checkedSelf = FindCheckAndCheckmateOnWhiteKing(theBoardArray);


                if(checkedSelf == 2 || checkedSelf == 3){
                    strcpy(theBoardArray[pieceEndLocation[0][0]][pieceEndLocation[0][1]], "**");
                    strcpy(theBoardArray[pieceStartLocation[0][0]][pieceStartLocation[0][1]], "WN"); 
                    printk("Can't make that move, puts your king in check/checkmate\n");
                    return -1;
                }else{
                    printk("Move made\n");
                    returnValue = FindCheckAndCheckmateOnBlackKing(theBoardArray);
                    return returnValue;  
                }
            }else{
                printk("The piece you want to take is not there\n");
                return -1;
            }
        }else{
            printk("That is not a possible move\n");
            return -1;
        }


    }
    
}







module_init(ModuleInit);
module_exit(ModuleExit);

