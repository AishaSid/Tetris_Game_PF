/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * This header contains the global/common variables of the project.
 * You don't really need to change anything.
 * TIP: After completing your project, you can make changes for aesthetics.
 * */

//AISHA SIDDIQA 22I-1281 CS-F

//---Title: PF-Project, Fall-2022 for BS(CS)---//
const char title[] = "PF-Project, Fall-2022";

//---Height and Width of the Actual Interactive Game---//
const int M = 20;   //Number of rows for a piece to cover on the screen (not the entire screen) = 20
const int N = 10;   //Number of columns for a piece to cover on the screen (not the entire screen) = 10

//---The Actual Interactive Game Grid - Built Over (MxN)---//
int gameGrid[M][N] = {0};

//---To Hold the Coordinates of the Piece---//
int point_1[4][2], point_2[4][2], point_3[4][2], b_shadow[4][2];
int bombs_1[4][2], bloc_1[4][2],bloc_2[4][2];
//---CheckUncertain Conditions---//
bool anamoly()
{
    for (int i=0;i<4;i++)
    
        if (point_1[i][0]<0 || point_1[i][0]>=N || point_1[i][1]>=M)      //defines the starting point
            return 0;
            
        else if (gameGrid[point_1[i][1]][point_1[i][0]])
            return 0;							//avoids overwriting of blocks
    return 1;
};



