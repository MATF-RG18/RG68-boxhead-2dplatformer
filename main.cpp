#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

using namespace std;




//promenljive koje pocinju sa 'dn' su user defined promenljive.  
//Cuvamo dimenzije prozora kao width i height
static int window_width, window_height; 

// Deklaracije callback funkcija. 
static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void on_timer(int value);

//Moje funkcije
void updatePlayerJumpHeight();
int getPlayerCurrentTile();
void generateMoreGround();
bool canMoveThisWay(unsigned char key);

//promenljive koje cuvaju poziciju igraca
float playerPosX = 0;
float playerPosY = 0; 
int playerCurrentTile;

//kamera 
float cameraTilt = true; //Da li je ili nije kamera malko nagnuta po x osi
                         //pritiskom na 'c' resavamo da li hocemo ili necemo ovo. 
float cameraOffsetX = 0.2;
float cameraOffsetY = 1;

float groundLevel = 0; //nivo terena, za sada je to 0 odnosno x osa

float dnFPS = 90; //koristimo ga u on_timer pozivu za kontrolu frejmova po sekundi

bool indJump = false; //indikator da li je igrac trenutno u skoku
bool indFalling = false;

float playerJumpHeight; //Visina koju igrac moze da dosegne prilikom trenutnog skoka po y osi
float playerMaxJumpHeight = 0.5; //Maksimalna visina skoka koju igrac moze da dosegne sa x ose (prirodna visina skoka)

//Nizovi za kontrolu zemlje po kojoj ce igrac hodati
float* groundXCor; //X koordinate svake od ploca koje se nadovezuju
float* groundHeight; //visina svake od ploca koje nadovezujemo
bool*  groundIsSet; //indikator da li smo ili ne vec postavili visinu i x koordinatu ovog terena
float  groundLengthOfTile = 0.5; // "duzina" ploce
float  groundDepth = - 0.2;


int groundNumOfTiles = 10; //Ove dve velicine koristimo za kontrolu realloc funkcije
int groundReallocStep = 5; 



int main(int argc, char **argv)
{
    // Inicijalizujemo GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

    // Kreiramo prozor
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);

    // Postavljamo funkcije za registrovanje callback funkcija 
    glutKeyboardFunc(on_keyboard);
    glutReshapeFunc(on_reshape);
    glutDisplayFunc(on_display);
    glutTimerFunc(1000/dnFPS, on_timer, 0);

    // Inicijalizujemo boju prozora i gl inicijalizacija
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    


    //Inicijalizujemo niz za ground
    groundXCor = (float*)malloc( sizeof(float) * groundNumOfTiles);
    groundHeight = (float*)malloc( sizeof(float) * groundNumOfTiles);
    groundIsSet = (bool*)malloc( sizeof(bool) * groundNumOfTiles);
    if(groundXCor == NULL || groundHeight == NULL || groundIsSet == NULL){
        printf("greska pri alociranju memorije");
        fflush(stdin);
        exit(EXIT_FAILURE);
    }


        

    int j;
    for(j =0; j< groundNumOfTiles; j++)
        groundIsSet[j] = false;



    //Glavna petlja
    glutMainLoop();

    return 0;
}


static void on_keyboard(unsigned char key, int x, int y)
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

static void on_reshape(int width, int height)
{
     // Pamte se sirina i visina prozora.
    window_width = width;
    window_height = height;

}

static void on_display(void)
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

static void on_timer(int value)
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

//Skok moram da namestim, i da namestim realloc da mi ne pravi samo 10 ploca, i plus ogranicenja, da ne mogu da ide kroz zid i tako to


//definicije mojih funkcija
void updatePlayerJumpHeight()
{
    //Nadjemo trenutnu podlogu po kojoj se igrac krece
    playerCurrentTile = floor(playerPosX / groundLengthOfTile);
    playerJumpHeight = playerMaxJumpHeight + groundHeight[playerCurrentTile];
}

//vraca trenutnu podlogu igraca
int getPlayerCurrentTile()
{
    return floor(playerPosX / groundLengthOfTile);  
}



//Funkcija za generisanje terena
void generateMoreGround()
{
   groundNumOfTiles += groundReallocStep;
   groundIsSet = (bool*) realloc(groundIsSet, sizeof(bool) *  groundNumOfTiles);
  //Niz sa koordinatam x naseg niza koji cuva podloge i niz koji cuva visine tih podloga
   groundXCor = (float*) realloc(groundXCor, sizeof(float) * groundNumOfTiles);
   groundHeight = (float*)  realloc(groundHeight, sizeof(float) * groundNumOfTiles);

   if(groundIsSet == NULL || groundXCor == NULL || groundHeight == NULL)
   {
       fprintf(stderr, "losa realokacija u funkciji generateMoreGround");
       exit(EXIT_FAILURE);
   }

   int i;

   for(i=0; i< groundNumOfTiles; i++)
       if(groundIsSet[i] != true)
            groundIsSet[i] = false;

   srand(time(NULL));
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
}


//Funkcija kojom cemo proveravati da li mozemo da se krecemo u nekom pravcu ili ne
bool canMoveThisWay(unsigned char key)
{
    
    fflush(stdin);
    playerCurrentTile = getPlayerCurrentTile();
    //Mogao sam da stavim i if else konstrukciju ali je svejedno jer ce se svakako pozivati za jedno od ova dva i nije bitan redosled provere
    if(key == 'a' || key == 'A')
    {
        printf("jeste");
        //Ako guramo zid kada se krecemo na levo
        if(groundXCor[playerCurrentTile - 1] + groundLengthOfTile == playerPosX)
            return false;
    }
    if(key == 'd'|| key == 'D')
    {
       printf("oke");
        //Ako guramo zid kada se krecemo na desno
       if(groundXCor[playerCurrentTile] + groundLengthOfTile <= playerPosX + 0.1) //0.1 je magicna konstanta koja nam predstavlja sirinu nase kockice/igraca
       {
        printf("I didnt alow him to move this way!");
        return false;
       }
    }

    //Ako ni jedan uslov nije ispunjen mi mozemo da se krecemo u tom pravcu pa vracamo true
    return true;
}
