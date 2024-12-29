/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

//---Piece Starts to Fall When Game Starts---//

//AISHA SIDDIQA 22I-1281 CS-F
// 1
void nextpiece(int n1, int n2)
{
  for (int i = 0; i < 4; i++)
  {
    bloc_1[i][0] = BLOCKS[n1][i] % 2;
    bloc_1[i][1] = BLOCKS[n1][i] / 2;
  }
  for (int i = 0; i < 4; i++)
  {
    bloc_2[i][0] = BLOCKS[n2][i] % 2;
    bloc_2[i][1] = BLOCKS[n2][i] / 2;
  }
}
// 2
void fallingPiece(float &timer, float &delay, int &colorNum, int &delta_x, int &n1, int &n2)
{
  if (timer > delay)
  {

    for (int i = 0; i < 4; i++)
    {
      point_2[i][0] = point_1[i][0];
      point_2[i][1] = point_1[i][1];
      point_1[i][1] += 1;
      // How much units downward
    }

    if (!anamoly())
    {
      int n3 = rand() % 7 + 1;
      n2 = n3;
      n1 = n2;
      int n = n1;

      if (n != 7)
        for (int i = 0; i < 4; i++)
          gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
      else
        for (int i = 0; i < 4; i++)
          gameGrid[point_2[i][1]][point_2[i][0]] = 0;

      colorNum = rand() % 7 + 1;

      for (int i = 0; i < 4; i++)
      {
        point_1[i][0] = BLOCKS[n][i] % 2;
        point_1[i][1] = BLOCKS[n][i] / 2;
        point_3[i][0] = BLOCKS[n][i] % 2;
        point_3[i][1] = BLOCKS[n][i] / 2;
      }
    }
    nextpiece(n1, n2);
    timer = 0;
  }
}

/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///

// 3	//MOVEMENTS
void move_x(int &delta_x, int &n)
{
  if (n != 7)
  {
    if (delta_x == 1 || delta_x == -1)
    { // movement loop
      for (int i = 0; i < 4; i++)
      {
        point_2[i][0] = point_1[i][0];
        point_1[i][0] += delta_x;
      } // add delta x to only the x axis for left right movements.
      if (!anamoly())
      {
        for (int i = 0; i < 4; i++)
          point_1[i][0] = point_2[i][0]; // stores previous value of grid if we try to go out of grid  (opposite )
      }
    }
  }
  delta_x = 0; // restoring value
}

// 4	//ROTATION
void rotation(bool &rotate, int &n)
{
  if (n != 7)
  {
    int x, y;

    if (rotate)
    {
      for (int i = 0; i < 4; i++)
      {
        point_2[i][0] = point_1[i][0]; // storing values of last movement to dummy array
        point_2[i][1] = point_1[i][1];
      }
      for (int i = 0; i < 4; i++)
      {
        x = point_1[i][0] - point_1[1][0]; // to get x and y axis of block (all four parts)
        y = point_1[i][1] - point_1[1][1];
        point_1[i][0] -= (x + y);
        point_1[i][1] += (x - y); //  rotating the block in x-y plane by switching its values.
      }
    }
    if (!anamoly())
    {
      for (int i = 0; i < 4; i++)
      {
        point_1[i][0] = point_2[i][0]; // restoring the last movements to remove anamoly
        point_1[i][1] = point_2[i][1];
      }
    }
  }
  rotate = false;
}

// 5	//GAMEOVER
void GameOver(bool &gameover)
{ // the function is chosen to get a true boolian.
  for (int i = 0; i < N; i++)
  {
    if (gameGrid[0][i] != 0)
      gameover = true; // if any of the first row block is filled, bool will be true
  }                    // return bool tre
}

// 6	//RESET
void Restart(bool &reset, int &score)
{
  if (reset) // if bool = true
  {
    for (int i = 0; i < M; i++)
    {
      for (int j = 0; j < N; j++)
      {
        gameGrid[i][j] = 0;
        score = 0; // empty all the spaces in grid.
      }            // new game will start
    }
  }
  reset = false; // restore value back to false
}

// 7
bool s_anamoly()
{
  for (int i = 0; i < 4; i++)

    if (point_3[i][0] < 0 || point_3[i][0] >= N || point_3[i][1] >= M) // defines the starting point
      return 0;

    else if (gameGrid[point_3[i][1]][point_3[i][0]])
      return 0; // avoids overwriting of blocks
  return 1;
};

// 8	//LINE CLEAR
void lineclear(int &score)
{
  int c = 0, row = 0, temp = 0;
  for (int i = 0; i < M; i++)
  {
    temp = 0;

    for (int j = 0; j < N; j++) // nested for loop to cover both x and y axis
    {
      if (gameGrid[i][j] != 0) // check if all columns of any row are filled
      {
        c++;
      }

      if (c == N)
      {
        for (int k = 0; k < N; k++)
        {
          gameGrid[i][k] = 0;
        } // remove that line which is filled
        row = i;
        temp++; // store value of that line
      }
      for (int m = row - 1; m > 0; m--) // shift the upper lines and block downwards.
      {
        for (int l = 0; l < N; l++) // nested for loop (for all)
        {

          {
            gameGrid[m + 1][l] = gameGrid[m][l];
          } // stores value of previous to bottom one
        }
      }
      row = 0; // reassign value to avoid errors

      switch (temp)
      {
      case 0:
        break;
      case 1:
        score += 10;
        break;
      case 2:
        score += 30;
        break;
      case 3:
        score += 60;
        break;
      case 4:
        score += 100;
        break;
      }
    }
    c = 0;
  } // re assign value inside nested loop
}

// SPACE BAR
// 9
void spacebar(int &n)
{
  // if(n!=7)
  {
    while (anamoly()) // adds one to the y-axis untill we get to anamoly of bottom.
    {
      for (int i = 0; i < 4; i++)
      {
        point_1[i][1] += 1;
      } // moves the block directly to the end
    }
    for (int i = 0; i < 4; i++)
    {
      point_1[i][1] -= 1; // subtract one from the block to place it perfectly on the grid
    }
  }
}

// 10  //SHADOWS
void shadows(int &n)
{

  for (int i = 0; i < 4; i++)
  {
    point_3[i][0] = point_1[i][0];
    point_3[i][1] = point_1[i][1];
    // How much units downward
  }

  while (s_anamoly())
  { // adds one to the y-axis untill we get to anamoly of bottom.

    for (int i = 0; i < 4; i++)
    {
      point_3[i][1] += 1;
    } // moves the block directly to the end
  }
  for (int i = 0; i < 4; i++)
  {
    point_3[i][1] -= 1; // subtract one from the block to place it perfectly on the grid
  }
}

// 9
void bombs_(int &n)
{
  if (n == 7)
  {
    for (int i = 0; i < 4; i++)
    {
      // point_1[i][0]= rand()%10;
    }
  }
}
// 8		//BOMBdisappearence

// 11
void bombvacant(int &n) // to remove the bomb from the gamegrid
{
  int a, b;
  if (n == 7)
  { // for (int i=0;i<4;i++)
    //{
    //    bombs_1[i][0]=point_1[i][0];
    //    bombs_1[i][1]=point_1[i][1];
    // }

    // for (int i=0; i<4; i++)
    //  { gameGrid[point_2[i][1]][point_2[i][0]] = 0; }    		//at the point where bomb will fall, it will not store value of bomb.

    if (!anamoly())
    {
      for (int i = 0; i < 4; i++)
      {
        a = point_1[i][0] - point_1[1][0]; // to get x and y axis of block (all four parts)
        b = point_1[i][1] - point_1[1][1];
        gameGrid[point_1[i][0]][point_1[i][1]] = 0;
      }
    }
    // at the point where bomb will fall, it will not store value of bomb.
  }
}

// 12   LEVEL UP
void levelup(int &score, int &lev, float &delay)
{
  if (!(score % 100 || score == 0)) // WITH EVERY 100 POINTS, THE LEVEL WILL INCREASE
  {
    lev += 1;
    delay -= 0.2; // THE DELAY IN TIME WILL DECREASE, MEANS THE GAME WILL SPEED UP
  }
}

// 10

/*
void bombdestruction(int &n)
{
 if(n==7)
   {
   if(!anamoly())
   {for (int i=0;i<4;i++)
        {
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
        }

     for (int i=0; i<4; i++)
   {
     gameGrid[point_2[i][1]][point_2[i][0]] = 0;
   }
   for (int i=0;i<4;i++)

     point_2[i][1] += 1;
    for (int i=0; i<4; i++)
   {
     gameGrid[point_2[i][1]][point_2[i][0]] = 0;
    }
    for (int i=0;i<4;i++)
     point_2[i][0] += 1;
     for (int i=0; i<4; i++)
   {
     gameGrid[point_2[i][1]][point_2[i][0]] = 0;
    }
    for (int i=0;i<4;i++)
     point_2[i][1] -= 1;
    for (int i=0; i<4; i++)
   {
     gameGrid[point_2[i][1]][point_2[i][0]] = 0;
    }
   }
   }
}
  */
///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
