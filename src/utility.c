#include "utility.h"
#include "sharedVars.h"
#include <stdio.h>
#include "model.h"


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
	//pribavimo trenutnu podlogu
	playerCurrentTile = getPlayerCurrentTile();
    
    //update-ujemo visinu skoka
   	playerJumpHeight = playerMaxJumpHeight + groundHeight[playerCurrentTile];
}

//vraca trenutnu podlogu igraca
int getPlayerCurrentTile()
{
    int possibleLeft = floor(playerPosXLeft/ groundLengthOfTile);
    int possibleRight = floor(playerPosXRight/ groundLengthOfTile);

    //stvarno ne znam zasto sam dobio ovu ideju ali ovo radi
    if(groundHeight[possibleLeft] > playerPosY && groundHeight[possibleRight] <= playerPosY)
      return possibleRight;
    //same here
    if(groundHeight[possibleLeft] <= playerPosY && groundHeight[possibleRight] > playerPosY)
      return possibleLeft;

    //E ovo dole skroz ima smisla, ali ne radi bez ovoga gore
    if(possibleRight == possibleLeft)
      return possibleLeft;

    else // possibleRight > possibleLeft
    {
      if(groundHeight[possibleLeft] < playerPosY && groundHeight[possibleRight] < playerPosY)
        return groundHeight[possibleLeft] > groundHeight[possibleRight] ? possibleLeft : possibleRight;
      
      else if(groundHeight[possibleLeft] >= playerPosY && groundHeight[possibleRight] < playerPosY)
        return possibleLeft;
      
      else
        return possibleRight;
    }

    // return floor(playerPosXLeft/ groundLengthOfTile);  
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

   for(i=1; i< groundNumOfTiles; i++)
       if(groundIsSet[i] != true)
            groundIsSet[i] = false;

   srand(time(NULL));
   for(i= 1; i < groundNumOfTiles; i++)
   {
       if(groundIsSet[i] == false)
      {
       float visina;
       visina = (float)rand() / (float)RAND_MAX + 0.2 ;
       
       //Cisto ogranicenje za visinu
       if (visina > 3)
       	 visina = 3;
       if (visina < 0.6)
       	 visina = 0.6;

       groundHeight[i] = visina; //Dodatno skracivanje
       
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
    if(key == 'a') //u switch statement sam stavio da podrzava i za veliko slovo tako da nije problem
    {    

        //Obezbedimo se kada smo na prvoj ploci da ne mozemo da odemo levo, imace smisla u daljoj implementaciji
        if(playerCurrentTile == 0)
          if(groundXCor[playerCurrentTile] >= playerPosXLeft)
            return false;

        //Ukoliko je visina na koju treba da skocimo manja od nekog dela visine naseg igraca onda necemo da skacemo, samo da predjemo preko toga
        if(groundHeight[playerCurrentTile - 1] - playerPosY > 0 && 
              groundHeight[playerCurrentTile - 1] - playerPosY < (playerLength / 2))
          return true;

        //Ako guramo zid kada se krecemo na levo
        if((groundXCor[playerCurrentTile - 1] + groundLengthOfTile >= playerPosXLeft - 0.005) &&
           (groundHeight[playerCurrentTile - 1] > playerPosY))
            return false;
    }
    if(key == 'd')  //u switch statement sam stavio da podrzava i za veliko slovo tako da nije problem
    {

      
        //Ukoliko je visina na koju treba da skocimo manja od nekog dela visine naseg igraca onda necemo da skacemo, samo da predjemo preko toga
        if(groundHeight[playerCurrentTile + 1] - playerPosY > 0 && 
              groundHeight[playerCurrentTile + 1] - playerPosY < (playerLength / 2))
          return true;

       //Ako guramo zid kada se krecemo na desno
       if((groundXCor[playerCurrentTile] + groundLengthOfTile <= playerPosXLeft + 0.105) && //0.105 sam stavio da ne bi izlazilo malko preko granice
             groundHeight[playerCurrentTile + 1] >= playerPosY) //0.1 je magicna konstanta koja nam predstavlja sirinu nase kockice/igraca
       {
        return false;
       }
    }

    // //Ako ni jedan uslov nije ispunjen mi mozemo da se krecemo u tom pravcu pa vracamo true
    return true;
}



void setLighting()
{	
	//Podesavamo vektore
	GLfloat position [] = {10,10,10,1};
	GLfloat ambient  [] = {0.4,0.4,0.4,1};
	GLfloat diffuse  [] = {1,1,1,1};
	GLfloat specular [] = {1,1,1,1};

	//Inicijalizujemo osobine svetlosti koje zelimo i poziciju osvetljenja
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);



}


void setMaterial(char * option)
{
	

    if(strcmp("ground", option) == 0)
    {
    	//Podesavamo vektore
		GLfloat specular [] = {0,0,0,0};
		GLfloat ambient  [] = {0.105, 0.176, 0.086,1};
		GLfloat diffuse  [] = {0.105, 0.176, 0.1,1};
    	int shininess   = 100;

		//Inicijalizujemo osobine materijala
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	}
	else if(strcmp("moon", option)==0)
	{
		//Podesavamo vektore
		GLfloat specular [] = {0,0,0,0};
		GLfloat ambient  [] = {0.909, 0.870, 0.552,1};
		GLfloat diffuse  [] = {0.909, 0.870, 0.552,1};
    	int shininess   = 100;

		//Inicijalizujemo osobine materijala
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	}

	else if(strcmp("water", option)==0)
	{
		//Podesavamo vektore
		GLfloat specular [] = {0,0,0,0};
		GLfloat ambient  [] = {0.011, 0.207, 0.2,1};
		GLfloat diffuse  [] = {0.011, 0.207, 0.2,1};
    	int shininess   = 100;

		//Inicijalizujemo osobine materijala
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	}

	else if(strcmp("Clipping plane", option) == 0)
	{
			//Podesavamo vektore
		GLfloat specular [] = {1,1,1,0};
		GLfloat ambient  [] = {0.890, 0.168, 0.168,0.3};
		GLfloat diffuse  [] = {0.890, 0.168, 0.168,0.3};
    	int shininess   = 1;

		//Inicijalizujemo osobine materijala
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	}

	else if(strcmp("neon", option)==0)
	{
		//Podesavamo vektore
		GLfloat specular [] = {0,0,0,0};
		GLfloat ambient  [] = {0.039, 1, 0.968,1};
		GLfloat diffuse  [] = {0.039, 1, 0.968,1};
    	int shininess   = 100;

		//Inicijalizujemo osobine materijala
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	}


	else if(strcmp("roof1", option)==0)
	{
		//Podesavamo vektore
		GLfloat specular [] = {0,0,0,0};
		GLfloat ambient  [] = {0.305, 0.431, 0.411,1};
		GLfloat diffuse  [] = {0.301, 0.301, 0.301,1};
    	int shininess   = 100;

		//Inicijalizujemo osobine materijala
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	}

	else if(strcmp("roof2", option)==0)
	{
		//Podesavamo vektore
		GLfloat specular [] = {0,0,0,0};
		GLfloat ambient  [] = {0.205, 0.231, 0.211,1};
		GLfloat diffuse  [] = {0.201, 0.201, 0.201,1};
    	int shininess   = 100;

		//Inicijalizujemo osobine materijala
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	}

	else if(strcmp("roof3", option)==0)
	{
		//Podesavamo vektore
		GLfloat specular [] = {0,0,0,0};
		GLfloat ambient  [] = {0.105, 0.131, 0.111,1};
		GLfloat diffuse  [] = {0.101, 0.101, 0.201,1};
    	int shininess   = 100;

		//Inicijalizujemo osobine materijala
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	}

	else if(strcmp("special roof", option)==0)
	{
		//Podesavamo vektore
		GLfloat specular [] = {0,0,0,0};
		GLfloat ambient  [] = {0.933, 0.847, 0.325,1};
		GLfloat diffuse  [] = {0.933, 0.847, 0.325,1};
    	int shininess   = 100;

		//Inicijalizujemo osobine materijala
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	}

	else if(strcmp("player", option)==0)
	{
		//Podesavamo vektore
		GLfloat specular [] = {0,0,1,0};
		GLfloat ambient  [] = {0,0,1,1};
		GLfloat diffuse  [] = {0.4,0.4,1,1};
	    int shininess   = 100;
		
		//Inicijalizujemo osobine materijala
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);	
	}

	else if(strcmp("firstRowBackground", option) ==0)
	{
		GLfloat specular [] = {0,0,0,0};
		GLfloat ambient  [] = {0.1, 0.1, 0.1,1};
		GLfloat diffuse  [] = {0.160, 0.160, 0.166,1};
	    int shininess   = 100;
		
		//Inicijalizujemo osobine materijala
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	}

	else if(strcmp("firstRowBackground", option) ==0)
	{
		GLfloat specular [] = {0.1,0.1,0.1,0};
		GLfloat ambient  [] = {0.117, 0.121, 0.121,1};
		GLfloat diffuse  [] = {0.117, 0.121, 0.121,1};
	    int shininess   = 100;
		
		//Inicijalizujemo osobine materijala
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	}

	else if(strcmp("stamina", option)==0)
	{
			//Podesavamo vektore
		GLfloat specular [] = {0.3,0.3,0.3,0};
		GLfloat ambient  [] = {0.3, 0.3,0,1};
		GLfloat diffuse  [] = {0.2,0.2,0.2,1};
	    int shininess   = 3;
		
		//Inicijalizujemo osobine materijala
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);	
	}

	else if(strcmp("leaf", option)==0)
	{
		//Podesavamo vektore
		GLfloat specular [] = {0,1,1,1};
		GLfloat ambient  [] = {0.3,1,0.3,1};
		GLfloat diffuse  [] = {0.4,0.1,0.4,1};
	    int shininess   = 100;
		
		//Inicijalizujemo osobine materijala
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);

	}

	else if(strcmp("bark", option)==0)
	{
		//Podesavamo vektore
		GLfloat specular [] = {0,0,0,1};
		GLfloat ambient  [] = {0.588, 0.349, 0.211,1};
		GLfloat diffuse  [] = {0.588, 0.349, 0.211,1};
	    int shininess   = 100;
		
		//Inicijalizujemo osobine materijala
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	}
}




void drawAxis(bool do_it)
{
	if(do_it)
	{
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
    }

}

