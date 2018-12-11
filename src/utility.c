#include "utility.h"
#include <stdio.h>


//EKSTERNE PROMENLJIVE


//promenljive koje cuvaju poziciju igraca
 float playerPosX = 0;
 float playerPosY = 0; 
 int playerCurrentTile;

 //kamera 
 bool cameraTilt = true; //Da li je ili nije kamera malko nagnuta po x osi
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



//FUNKCIJE

bool initGround()
{
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
    return true;
  }



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
