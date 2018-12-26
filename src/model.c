#include "model.h"

void drawStaminaBar()
{
	
	setMaterial("stamina");

	/*
	Menjamo boju stamina bar u zavisnosti koliko stamine energije, 
	vec je podesena na crvenu na kojoj zelimo da bude ako je izmedju 70 i 30
	*/
	if(playerStamina >= 70)
	{	
		//zelena
		GLfloat mat[] = {0,1,0,1};
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat);	
	}
	else if(playerStamina >= 30 && playerStamina < 70)
	{
		//plava
		GLfloat mat[] = {1,1,0,1};
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
	}


	int i;
	for(i = 0; i < playerStamina; i++)
	{
		glPushMatrix();
			glTranslatef(0,0,0.2);
			glTranslatef((i*0.01 + playerPosXLeft - 0.5 + playerLength/2),1.5 + playerPosY  ,0);
			glutSolidSphere(0.01,15,15);
		glPopMatrix();
	}

	//Iscrtavamo pozadinu
	
	GLfloat diffuse[] = {0,0,0,1};
	GLfloat ambient[] = {0.4,0.4,0.4,1};
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse); 	
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);

	glPushMatrix();
		glTranslatef(0,0,0.2);
		glTranslatef((100 *0.01 + playerPosXLeft - 1 + playerLength/2),1.5 + playerPosY  ,-0.1);
		glScalef(5.5,0.4,0.003);
		glutSolidCube(0.2);
	glPopMatrix();
 }

//Funkcija za iscrtavanje 2d modela igraca 
void drawPlayerModel2D(void)
{
	setMaterial("player");
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
void drawPlayerModel3D(float x, float y)
{
	setMaterial("player");

	glPushMatrix();
	glTranslatef(x, y + (float)playerLength/2, 0);
	glutSolidCube(playerLength);
	glPopMatrix();

	//ako su krila ukljucena iscrtacemo elisu helikoptera
	if(wingsActive)
	{

		glPushMatrix();
			glTranslatef(x, y + (float)playerLength, 0);
			glRotatef(90 + 10*playerStamina,0,1,0);
			glScalef(0.3,0.02,0.01);
			glutSolidSphere(1,30,30);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(x, y + (float)playerLength, 0);
			glRotatef (10*playerStamina,0,1,0);
			glScalef(0.3,0.02,0.01);
			glutSolidSphere(1,30,30);
		glPopMatrix();
	}
}


void drawGround2D()
{
	setMaterial("ground");
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

   void drawGround3D(void)
    {


    //Postavljamo materijal za zemlju.
    setMaterial("ground");

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
   
   glPushMatrix();
   glTranslatef((groundLengthOfTile/2 +  i * groundLengthOfTile),groundHeight[i]/2, 0);
   glScalef(groundLengthOfTile, groundHeight[i], 1);
   glutSolidCube(1);
   glPopMatrix();   
   }


    }
 



