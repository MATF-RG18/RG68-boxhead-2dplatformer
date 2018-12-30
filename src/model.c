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
 }

void drawPlayerModel(float x, float y)
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
			glTranslatef(x, y + (float)playerLength + 0.01, 0);
			glRotatef(90 + 30*playerStamina,0,1,0);
			glScalef(0.3,0.02,0.01);
			glutSolidSphere(1,30,30);
		glPopMatrix();

		glPushMatrix();
			glTranslatef(x, y + (float)playerLength + 0.02, 0);
			glRotatef (30*playerStamina,0,1,0);
			glScalef(0.3,0.02,0.01);
			glutSolidSphere(1,30,30);
		glPopMatrix();
	}
}


void drawGround2D()
{

  //Ispisujemo score
  writeScore("Score!", playerPosXLeft + playerLength/2, playerPosY + 1, 1);

  //Iscrtavamo red plane 
  drawRedPlane();
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
       visina =(float)rand()/(float)(RAND_MAX) * playerMaxJumpHeight * 1.7 + 0.1;
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
   
   if(i%2 == 0 || i%5 == 0)
      {
      	drawTree2D(groundXCor[i], groundHeight[i], i);
      	//Nakon iscrtavanja moramo opet da vratimo materijal na ground
      }

 if(groundXCor[i] > RedPlaneParam - 5)
  {
    drawHill(i, groundHeight[i]);
    drawMoon();
  }
   setMaterial("ground");
      
  if(i%25 == 0)
    setMaterial("special roof");
   glColor3f(0,1,1);
   glBegin(GL_POLYGON);
     glVertex3f(groundXCor[i], groundHeight[i], 0);
     glVertex3f(groundXCor[i], groundDepth, 0);
     glVertex3f(groundXCor[i] + groundLengthOfTile,  groundDepth, 0);
     glVertex3f(groundXCor[i] + groundLengthOfTile, groundHeight[i], 0);  
   glEnd();
   
   }

   // iscrtavamo jezera
   drawLakes();
}

   void drawGround3D(void)
    {


   //Ispisujemo score dosadasnji
   writeScore("SCORE!",playerPosXLeft,playerPosY+1,1); 

   //Iscrtavamo crvenu ravan
   drawRedPlane();  

   //Podesavamo prvobitnu plocu, i poziciju igraca u odnosu na nju 
   groundXCor[0] =  0;
   groundHeight[0] = 0.2;
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


   if(i % 25 == 0)
    setMaterial("special roof");
   else if(i % 2 == 0)
   	setMaterial("roof1");
   else if(i % 5 == 0)
   	setMaterial("roof2");
   else 
   	setMaterial("roof3");

   if(i == 0)
       groundXCor[0] = 0;
   else
       groundXCor[i] = groundXCor[i-1] + groundLengthOfTile;
   
   //Iscrtavamo zgrade
   glPushMatrix();
   glTranslatef((groundLengthOfTile/2 +  i * groundLengthOfTile),groundHeight[i]/2, 0);
   glScalef(groundLengthOfTile, groundHeight[i], 1);
   glutSolidCube(1);
   glPopMatrix();

   //Iscrtavamo teren ispod nasih ploca za kretanje
   glPushMatrix();
   glTranslatef((groundLengthOfTile/2 +  i * groundLengthOfTile),-0.75, 0);
   glScalef(groundLengthOfTile, 1, 1);
   glutSolidCube(1);
   glPopMatrix();

   glPushMatrix();
   glTranslatef((groundLengthOfTile/2 +  i * groundLengthOfTile),-2, 0);
   glScalef(groundLengthOfTile, 1, 1);
   glutSolidCube(1);
   glPopMatrix();

    //Ovde mi odgovara ova boja zato nju biram;
   setMaterial("neon");
   
      glPushMatrix();
   glTranslatef((groundLengthOfTile/2 +  i * groundLengthOfTile),-2.5, 0);
   glScalef(groundLengthOfTile, 5, 0.7);
   glutSolidCube(1);
   glPopMatrix();

   //Iscrtavamo pozadinu
   if(i != groundNumOfTiles - 5)
   {

   setMaterial("firstRowBackground");
   glPushMatrix();
	   glTranslatef((groundLengthOfTile/2 +  i * groundLengthOfTile),groundHeight[i+3]/2, -1);
	   glScalef(groundLengthOfTile, groundHeight[i+3]+ 2, 1);
	   glutSolidCube(1);
	   glPopMatrix(); 


   setMaterial("secondRowBackground");
   glPushMatrix();
	   glTranslatef((groundLengthOfTile/2 +  i * groundLengthOfTile),groundHeight[i+3]/2, -2);
	   glScalef(groundLengthOfTile, groundHeight[i+5] + 3, 1);
	   glutSolidCube(1);
	   glPopMatrix();           
   }

   glEnable(GL_CLIP_PLANE0);   
   //Iscrtavamo odzake
   if(i % 2 == 0)
   {
    if(i%10 == 0)
      drawChimney(i, groundHeight[i], 2);
    else if(i % 8 == 0)
      drawChimney(i, groundHeight[i], 1);
    else
      drawChimney(i, groundHeight[i], 3);
    glDisable(GL_CLIP_PLANE0);
   
    }

 }
}


    void drawTree2D(float x, float y, int poz)
    {
    	
    	 //promenljiva koja ce nam pomeriti malko iscrtavanje ispod y jer ne zelimo da vidimo prostor izmedju kada se renderuje
    	float eps = 0.01;
    	setMaterial("bark");
    	//Isrtavamo stabla i krosnje od drveca
    	glBegin(GL_QUADS);
    		glVertex3f(x - 0.05 + groundLengthOfTile/2, y - eps, -0.01);
    		glVertex3f(x - 0.05 + groundLengthOfTile/2, 0.4 + y - eps, -0.01);
    		glVertex3f(x + 0.05 + groundLengthOfTile/2, 0.4 + y - eps, -0.01);
    		glVertex3f(x + 0.05 + groundLengthOfTile/2, y - eps, -0.01);
    	glEnd();


    	setMaterial("leaf");
    	glBegin(GL_TRIANGLES);
		    glVertex3f(x - 0.2 + groundLengthOfTile/2, y + 0.4 - eps, -0.011);
    		glVertex3f(x + 0.2 + groundLengthOfTile/2, 0.4 + y - eps, -0.011);
    		glVertex3f(x + groundLengthOfTile/2, 0.8 + y - eps, -0.011);
    	glEnd();

    	glBegin(GL_TRIANGLES);
		    glVertex3f(x - 0.2 + groundLengthOfTile/2, y + 0.4 +0.3 - eps, -0.012);
    		glVertex3f(x + 0.2 + groundLengthOfTile/2, 0.4 + y +0.3 - eps, -0.012);
    		glVertex3f(x + groundLengthOfTile/2, 0.8 + y +0.3 - eps, -0.02);
    	glEnd();

    	if(poz % 6 == 0)
    	{
    	setMaterial("leaf");
    	glBegin(GL_TRIANGLES);
		    glVertex3f(x - 0.2 + groundLengthOfTile/2, y + 0.4 + 0.6 - eps, -0.013);
    		glVertex3f(x + 0.2 + groundLengthOfTile/2, 0.4 + y + 0.6 - eps, -0.013);
    		glVertex3f(x + groundLengthOfTile/2, 0.8 + y + 0.6 - eps, -0.013);
    	glEnd();
    	}
    }
 
void drawChimney(int poz, float height, int option)
{
	GLUquadric * cylinder1 = gluNewQuadric();
	GLUquadric * cylinder2 = gluNewQuadric();
  if(option == 1)
  {
  	glPushMatrix();
  		glTranslatef(poz * groundLengthOfTile + groundLengthOfTile/2, height + 0.46, 0.4);
  		glRotatef(90, 1, 0, 0);
  		gluCylinder(cylinder1, 0.05, 0.05, poz%6* 3, 30, 30);
  	glPopMatrix();
  }
	if(option == 2)
	{
  glPushMatrix();
      glTranslatef(poz * groundLengthOfTile + groundLengthOfTile/2, height + 0.46, -0.4);
      glRotatef(90, 1, 0, 0);
      gluCylinder(cylinder1, 0.05, 0.05, poz%6* 3, 30, 30);
  glPopMatrix();
  
	glPushMatrix();
		glTranslatef(poz * groundLengthOfTile + groundLengthOfTile/2, height + 0.46, 0.4);
		glRotatef(90, 1, 0, 0);
		gluCylinder(cylinder2, 0.05, 0.05, poz%6* 3, 30, 30);
	glPopMatrix();
	}

  if(option == 3)
  {
  glPushMatrix();
    glTranslatef(poz * groundLengthOfTile + groundLengthOfTile/2, height + 0.46, -0.4);
    glRotatef(90, 1, 0, 0);
    gluCylinder(cylinder1, 0.05, 0.05, poz%6* 3, 30, 30);
  glPopMatrix();
  }

}
void drawMoon(void)
{
  setMaterial("moon");
   glPushMatrix();
      glScalef(2,2,1);
      glTranslatef(playerPosXLeft/2 ,1,-2);
      glutSolidSphere(0.15, 30,30);
   glPopMatrix();
   setMaterial("ground");
  
}

void drawHill(int poz, float height)
{
  if(poz%2 == 0)
  {
    glPushMatrix();
      glScalef(6,4,1);
      glTranslatef(poz/10,-height + 0.25,-1);
      glutSolidSphere(height, 30,30);
    glPopMatrix();
  }


}


void drawLakes(void)
{
  int i;
 for(i = 2; i < groundNumOfTiles-1; i++) 
 {
    if(i%2 != 0 && i%5 != 0)
    {
      if(groundHeight[i]<groundHeight[i-1] && groundHeight[i] < groundHeight[i+1])
      {
        float min_height = groundHeight[i-1]<groundHeight[i+1] ? groundHeight[i-1] : groundHeight[i+1];
        setMaterial("water");
            glBegin(GL_QUADS);
              glVertex3f(groundXCor[i]-0.01, groundHeight[i] - 0.03, 0);
              glVertex3f(groundXCor[i]-0.01, min_height - 0.05, 0 );
              glVertex3f(groundXCor[i+1]+0.01, min_height - 0.05, 0);
              glVertex3f(groundXCor[i+1]+0.01, groundHeight[i] - 0.03, 0);
            glEnd();
        
      }
    }
  }
}


void drawRedPlane(void)
{

  //Sada iscrtavam ravan koja nas "juri"
    glPushMatrix();

      //Iscrtavamo vidnu kliping ravan
      setMaterial("Clipping plane");
      glPushMatrix();
       glScalef(1, 1, 1);
       glTranslatef(RedPlaneParam - 1.5, playerPosY, 0);
       glutSolidCube(3);

      glPopMatrix();
}


void writeScore(char *string,float x,float y,float z) 
{  
    char *c;

    glLineWidth(3);
    // sprintf(string, "%d!", score);
    asprintf (&string, "%i!", score);

    glPushMatrix();
    

    if(score < 10)
      glTranslatef(playerPosXLeft - 0.5 + playerLength + 0.4, 1.3 + playerPosY,0.2);
    else if(score < 100) 
      glTranslatef(playerPosXLeft - 0.5 + playerLength + 0.3, 1.3 + playerPosY,0.2);
    else  
      glTranslatef(playerPosXLeft - 0.5 + playerLength + 0.3, 1.3 + playerPosY,0.2);


    glScalef(0.0015,0.0015,0.001);
    
    glLineWidth(2);

    for (c=string; *c != '!'; c++)
      {
          //ovde mi bas odgovara ovaj materijal pa ga opet koristim
          setMaterial("special roof");
          glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN , *c);
      }
  glPopMatrix();
}