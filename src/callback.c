#include "callback.h"
#include "sharedVars.h"
#include "model.h"



void set_callback(void)
{
    setKeyboardFunc(); //iz keyboard.h
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    glutTimerFunc(1000/dnFPS, on_timer, 0);
}



void on_display(void)
{
    //cistimo bafere
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Podesava se viewport
    glViewport(0, 0, window_width, window_height);

    // Podesava se projekcija. 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, window_width/(float)window_height,1,-1.5); 
    
    // Podesava se vidna tacka
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();   
    //podesavamo gde ce nam kamera gledati, ondnosno iz koje pespektive
    gluLookAt(playerPosXLeft + cameraOffsetX, playerPosY + cameraOffsetY, 3,playerPosXLeft, playerPosY, 0, 0, 1, 0);
       srand(time(NULL));
    glColor3f(1,0,0);
    

    
    
    //KOORDINATNI SISTEM
    glLineWidth(0.5);
    //x osa        
    glColor3f(1,0,0);
    glBegin(GL_LINES);
        glVertex3f(-100, 0, 0);
        glVertex3f(100, 0, 0);
    glEnd();    
    //y osa    
    glColor3f(0,1,0);
    glBegin(GL_LINES);
        glVertex3f(0, -1000, 0);
        glVertex3f(0, 1000, 0);
    glEnd();    
    //z osa    
    glColor3f(0,0,1);
    glBegin(GL_LINES);
        glVertex3f(0, 0, -1000);
        glVertex3f(0, 0, 1000);
    glEnd();
    
    // Skaliramo sve za koeficijent, po svim osama 
    glScalef(1, 1, 1);

    //Iscrtavamo teren u 2d
    drawGround2D();



   //Iscrtavamo igraca
   playerPosXRight = playerPosXLeft + playerLength; // cuvamo srazmeru igraca 

   drawPlayerModel2D();
   // drawPlayerModel3D();

   glutSwapBuffers();
}




void on_timer(int value)
{  
    
     if(getPlayerCurrentTile() > (groundNumOfTiles / 2))
        generateMoreGround();

    //Racunamo trenutne dozvole igraca
    playerCurrentTile = getPlayerCurrentTile(); 
  
    if(groundIsSet[playerCurrentTile] == true)
      groundLevel = groundHeight[playerCurrentTile];
    else
      {
      printf("\nGROUND LEVEL NOT SET TILE NO.: %d\t", playerCurrentTile);
      exit(EXIT_FAILURE);
      }
    
    //ovo se menja pritiskom na dugme c
    if(cameraTilt)
    {
        if(cameraOffsetX < 0.2)
            cameraOffsetX += 0.02;
        if(cameraOffsetY < 1)
            cameraOffsetY += 0.2;
    }
    else
    {
        if(cameraOffsetX > 0)
            cameraOffsetX -= 0.02;
        if(cameraOffsetY > 0)
            cameraOffsetY -= 0.02;
    }   
   
    //proveravamo da li je igrac trenutno u skoku
    
    if(playerPosY > groundHeight[getPlayerCurrentTile()])
        if(indFalling == false)
           indFalling = true;
       
  

    if (indJump == true)
    {
        if (playerPosY  < playerJumpHeight)
        {
            playerPosY += 0.01;
            cameraOffsetY += 0.01;
        }
        //Ako je igrac dostigao max visinu skoka, kazemo da vise nije u skoku, pada.
        else if(playerPosY >=  playerJumpHeight)
       {
            indJump = false;
            indFalling = true;
       }    
    }
    
    if(playerPosY > groundHeight[playerCurrentTile] && indJump == false)
    {
        cameraOffsetY -= 0.01;
        playerPosY -= 0.01;
    }
    if(playerPosY <= groundHeight[playerCurrentTile] && indJump == false)
    {
        playerPosY = groundLevel;
        indFalling  = false;
    }
    glutPostRedisplay(); //nanovo ucitavamo prozor u odredjenim intervalima
    glutTimerFunc(1000/dnFPS, on_timer, 0); //podesili smo funkciju on_timer da sama sebe poziva  

}





void on_reshape(int width, int height)
{
   //Postavlja se viewport. 
    glViewport(0, 0, width, height);

    /* Postavljaju se parametri projekcije. */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 1500);

  window_width = width;
  window_height = height;
}




