#include "model.h"


//Funkcija za iscrtavanje 2d modela igraca 
void drawPlayerModel2D(void)
{
   //Iscrtavamo igraca
   playerPosXRight = playerPosXLeft + playerLength; // cuvamo srazmeru igraca 

   glColor3f(1, 0.5, 1);
   glBegin(GL_POLYGON);
      glVertex3f(playerPosXLeft, playerPosY, 0);
      glVertex3f(playerPosXRight, playerPosY, 0);
      glVertex3f(playerPosXRight, playerPosY + 0.1, 0);
      glVertex3f(playerPosXLeft, playerPosY + 0.1, 0);
      glEnd();
}



//Funkcija za iscrtavanje 3d modela igraca
void drawPlayerModel3D(void)
{
	glBegin(GL_QUADS);
       glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f( playerPosXLeft, 0.1, -0.1);
      glVertex3f(playerPosXRight, 0.1, -0.1);
      glVertex3f(playerPosXRight, 0.1,  0.1);
      glVertex3f( playerPosXLeft, 0.1,  0.1);
 
      // Bottom face (y = -1.0f)
       glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f( playerPosXLeft, playerPosY, -0.1);
      glVertex3f(playerPosXRight, playerPosY, -0.1);
      glVertex3f(playerPosXRight, playerPosY,  0.1);
      glVertex3f( playerPosXLeft, playerPosY,  0.1);
 
      // Front face  (z = 1.0f)
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( playerPosXLeft,  playerPosY, 0.1);
      glVertex3f(playerPosXLeft,  playerPosY + 0.1, 0.1);
      glVertex3f(playerPosXRight, playerPosY + 0.1, 0.1);
      glVertex3f(playerPosXRight, playerPosY , 0.1); 
 
      // Back face (z = -1.0f)
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( playerPosXLeft, playerPosY, 0);
      glVertex3f(playerPosXLeft,  playerPosY + 0.1, 0);
      glVertex3f(playerPosXRight, playerPosY + 0.1, 0);
      glVertex3f(playerPosXRight, playerPosY, 0);
 
      // Left face (x = -1.0f)
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(playerPosXLeft,  playerPosY,  0);
      glVertex3f(playerPosXLeft,  playerPosY + 0.1,  0);
      glVertex3f(playerPosXLeft,  playerPosY + 0.1, -0.1);
      glVertex3f(playerPosXLeft,  playerPosY, -0.1);
 
      // Right face (x = 1.0f)
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(playerPosXRight,  playerPosY,  0);
      glVertex3f(playerPosXRight,  playerPosY + 0.1,  0);
      glVertex3f(playerPosXRight,  playerPosY + 0.1, -0.1);
      glVertex3f(playerPosXRight,  playerPosY, -0.1);
}


void drawGround2D()
{
   //Podesavamo prvobitnu plocu, i poziciju igraca u odnosu na nju 
   groundXCor[0] =  0;
   groundHeight[0] = 0;
   playerCurrentTile = 0;
   groundIsSet[0] = true;   

   srand(time(NULL));
   int i;
   for(i= 1; i < groundNumOfTiles; i++)
   {
       if(groundIsSet[i] == false)
      {
       float visina;
       visina =(float)rand()/(float)(RAND_MAX) * playerMaxJumpHeight * 1.7;
       groundHeight[i] = visina;
       groundIsSet[i] = true;
      }
   }    
   for(i = 0; i < groundNumOfTiles; i++) 
   {

   if(i == 0)
       groundXCor[0] = 0;
   else
       groundXCor[i] = groundXCor[i-1] + groundLengthOfTile;
   
   glColor3f(0,1,1);
   glBegin(GL_POLYGON);
     glVertex3f(groundXCor[i], groundHeight[i], 0);
     glVertex3f(groundXCor[i], groundDepth, 0);
     glVertex3f(groundXCor[i] + groundLengthOfTile,  groundDepth, 0);
     glVertex3f(groundXCor[i] + groundLengthOfTile, groundHeight[i], 0);  
   glEnd();
   }
}

//    void drawGround3d(void)
//    {
//    	//za sada nista (obrisah pet puta komentar da bi mi ostao pristojan... life is Matf... i mean life is hard...)
//    }
 



