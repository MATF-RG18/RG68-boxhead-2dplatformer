#include "callback.h"

//!!!!!!! SVE PROMENLJIVE SU DEKLARISANE U UTILITY.C !!!!!


//promenljive koje pocinju sa 'dn' su user defined promenljive.  
//Cuvamo dimenzije prozora kao width i height
static int window_width, window_height; 


//promenljive koje cuvaju poziciju igraca
extern float playerPosX;
extern float playerPosY; 
extern int playerCurrentTile;

 //kamera 
extern bool cameraTilt; //Da li je ili nije kamera malko nagnuta po x osi
                         //pritiskom na 'c' resavamo da li hocemo ili necemo ovo. 
extern float cameraOffsetX;
extern float cameraOffsetY;

extern float groundLevel; //nivo terena, za sada je to 0 odnosno x osa

extern float dnFPS; //koristimo ga u on_timer pozivu za kontrolu frejmova po sekundi

extern bool indJump; //indikator da li je igrac trenutno u skoku
extern bool indFalling;

extern float playerJumpHeight; //Visina koju igrac moze da dosegne prilikom trenutnog skoka po y osi
extern float playerMaxJumpHeight; //Maksimalna visina skoka koju igrac moze da dosegne sa x ose (prirodna visina skoka)

//Nizovi za kontrolu zemlje po kojoj ce igrac hodati
extern float* groundXCor; //X koordinate svake od ploca koje se nadovezuju
extern float* groundHeight; //visina svake od ploca koje nadovezujemo
extern bool*  groundIsSet; //indikator da li smo ili ne vec postavili visinu i x koordinatu ovog terena
extern float  groundLengthOfTile; // "duzina" ploce
extern float  groundDepth;


extern int groundNumOfTiles; //Ove dve velicine koristimo za kontrolu realloc funkcije
extern int groundReallocStep; 






void set_callback(void)
{
    glutKeyboardFunc(on_keyboard);
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
    gluPerspective(45,1,1,-1.5); 
    
    // Podesava se vidna tacka
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();   
    //podesavamo gde ce nam kamera gledati, ondnosno iz koje pespektive
    gluLookAt(playerPosX  + cameraOffsetX, playerPosY + cameraOffsetY, 3,playerPosX , playerPosY, 0, 0, 1, 0);
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
       visina = (float)rand()/(float)(RAND_MAX) * (groundIsSet[i-1] + 0.1);
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
    
   glColor3f(1,0.5,1);
   glBegin(GL_POLYGON);
      glVertex3f(playerPosX, playerPosY, 0);
      glVertex3f(playerPosX + 0.1, playerPosY, 0);
      glVertex3f(playerPosX + 0.1, playerPosY + 0.1, 0);
      glVertex3f(playerPosX, playerPosY + 0.1, 0);
      glEnd();

   glutSwapBuffers();
}





void on_timer(int value)
{  
    if(getPlayerCurrentTile() > (groundNumOfTiles / 2))
        generateMoreGround();

    //Racunamo trenutne dozvole igraca
    playerCurrentTile = floor(playerPosX / groundLengthOfTile);
  
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
            printf("Falling! \n");
       }    
    }
    
    if(playerPosY > groundHeight[playerCurrentTile] && indJump == false)
    {
        cameraOffsetY -= 0.01;
        playerPosY -= 0.01;
    }
    if(playerPosY <= groundLevel && indJump == false)
    {
        playerPosY = groundLevel;
        indFalling  = false;
    }
    glutPostRedisplay(); //nanovo ucitavamo prozor u odredjenim intervalima
    glutTimerFunc(1000/dnFPS, on_timer, 0); //podesili smo funkciju on_timer da sama sebe poziva  

}





void on_reshape(int width, int height)
{
     // Pamte se sirina i visina prozora.
    window_width = width;
    window_height = height;

}



void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 27:
        // Zavrsava se program.
        free(groundXCor);
        free(groundHeight);
        exit(EXIT_SUCCESS);
        break;
    case 'd':
        //krecemo se na desnu stranu
        if(canMoveThisWay('d'))
        playerPosX += 0.02;
        break;
    case 'a':
        //krecemo se na levu stranu ako mozemo
        if(canMoveThisWay('a'))
        playerPosX -= 0.02;
        break;
    case 'w':
       
        //pokrecemo skok ako vec nije pokrenut
        if( indJump == false && indFalling == false)
        {
            updatePlayerJumpHeight();
            printf("Podesena visina: %f\n", playerJumpHeight);
            indJump = true;
        }
            break;
    case 'c':
          //biramo da li zelimo kamera da nam bude tilt ili ne.
          if( cameraTilt == true){
              cameraTilt = false;}
          else
              cameraTilt = true;
          break; 
    }
}


