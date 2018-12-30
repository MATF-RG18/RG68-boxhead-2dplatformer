#include "callback.h"
#include "sharedVars.h"
#include "model.h"

#define FULL 100;

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
    

    //koordinatni sistem, ako je false ne iscrtava se ako je true iscrtava se
    drawAxis(false);

    //stamina bar
    drawStaminaBar();
    
    // Skaliramo sve za koeficijent, po svim osama, u ovom slucaju ne skaliramo, ali ipak cu ostaviti da mi bude lakse kasnije da ne razmisjljam
    glScalef(1, 1, 1);




    //Racunamo koordinatu desne ivice naseg igraca. Korisno kasnije u kolizijama
   	playerPosXRight = playerPosXLeft + playerLength; // cuvamo srazmeru igraca 

   	
   	//Iscrtavamo igraca
   	drawPlayerModel((float)((playerPosXLeft + playerPosXRight) / 2), playerPosY);

	if(active3D)
    	//Iscrtavamo u 3D ground
    	drawGround3D();
    
    else
    	//Iscrtavamo u 2D ground
    	drawGround2D();
   



   //Iscrtavamo igraca
   playerPosXRight = playerPosXLeft + playerLength; // cuvamo srazmeru igraca 

   //drawPlayerModel2D();
    

   glutSwapBuffers();
}




void on_timer(int value)
{  



  //Racunamo trenutne dozvole igraca
    playerCurrentTile = getPlayerCurrentTile();


  // Otklanja bag koji se nekada pojavi gde se igrac stvori unutar kocke.
  if(just_started)
  {
    playerPosY = groundHeight[playerCurrentTile];
    just_started = false;
  }

  if(playerCurrentTile - 2 > score)
    score = playerCurrentTile-2; 


  int pomocnaX = floor(playerPosXRight/ groundLengthOfTile);
  if((playerCurrentTile != pomocnaX) && (groundHeight[pomocnaX] > (groundHeight[playerCurrentTile] + playerLength/3)))
    playerPosXLeft = groundXCor[playerCurrentTile] + groundLengthOfTile - playerLength;        


  if(has_been_restarted)
  {
    //Samo pokrecemo opet animaciju ako smo restartovali igru
    animation_ongoing = true;
  }
  

  if(playerCurrentTile % 25 == 0 && playerPosY <= groundHeight[playerCurrentTile])
    playerStamina = FULL;


  if(animation_ongoing)
  {

  //Prekida se igra
  if(playerPosXRight <= RedPlaneParam)
  {
    animation_ongoing = false;
  }

  if(playerCurrentTile >= 3)
  {
      if(playerCurrentTile < 30)
        RedPlaneParam+=0.008;
      else if(playerCurrentTile < 60)
        RedPlaneParam+= 0.01;
  }

	if(!wingsActive)
	{
		if(playerStamina < 100)
		{
			if(playerStamina < 30)
			{
		    	staminaIncrement += 0.2;
			}
			else if(playerStamina > 70)
			{
				staminaIncrement += 0.3;
			}
			else
				staminaIncrement += 0.25;

		    if(staminaIncrement >= 1)
		    {
				playerStamina += 1;
				staminaIncrement = 0;
			}	
		}
	}
	else
	{
		//Deaktiviramo krila ukoliko je stamina = 0;
		if(playerStamina <= 0)
			wingsActive = false;

		staminaIncrement -= 0.3;
		if(staminaIncrement <= 0)
		{
			playerStamina -= 1;
			staminaIncrement = 1;
		}
	}	


    
  	 if(playerCurrentTile > (groundNumOfTiles / 2))
        generateMoreGround();
    
     if(groundXCor[playerCurrentTile] + groundLengthOfTile < playerPosXRight 
     		&& playerPosY < groundHeight[playerCurrentTile+1]
     			&& abs(groundXCor[playerCurrentTile+1] - groundXCor[playerCurrentTile]) > playerLength/2)
     {
     	playerPosXRight = groundXCor[playerCurrentTile] + groundLengthOfTile;
     	playerPosXLeft = playerPosXRight - playerLength;
     }

    if(groundIsSet[playerCurrentTile] == true)
      groundLevel = groundHeight[playerCurrentTile];
    
    //ovo se menja pritiskom na dugme c
    if(cameraTilt)
    {
    	if(!active3D)
    		active3D = true;

        if(cameraOffsetY < 1)
            cameraOffsetY += 0.02;
    }
    else
    {
    	if(active3D)
   			if(cameraOffsetY <=0 )
	   			active3D = false;

        if(cameraOffsetX > 0)
            cameraOffsetX -= 0.02;
        if(cameraOffsetY > 0)
            cameraOffsetY -= 0.02;
        if(cameraOffsetY < 0)
        	cameraOffsetY = 0;
    }   
   
    //proveravamo da li je igrac trenutno u skoku
    
    if(!wingsActive)
    {
		    if(playerPosY > groundHeight[getPlayerCurrentTile()])
		        if(indFalling == false)
		           indFalling = true;
		       
		  

		    if (indJump == true)
		    {

            if(pressed_a)
            {
               //Ako drzimo i 'w' i 'a' zelimo da nam se krece dijagonalno
             if(canMoveThisWay('a')) 
                  playerPosXLeft += playerStepBackwards;
            }
            else if(pressed_d)
            {
               //Ako drzimo i 'w' i 'd' zelimo da nam se krece dijagonalno
              if(canMoveThisWay('d'))
                  playerPosXLeft += playerStepForward;
                //za sada koristim ovo ali svejedno je ime promenljive bitno je da je okej velicina :TODO   
            }

		        if (playerPosY  < playerJumpHeight)
		        {
		            playerPosY += 0.02;
		            cameraOffsetY += 0.02;
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
            if(pressed_a)
            {
               //Ako drzimo i 'w' i 'a' zelimo da nam se krece dijagonalno
             if(canMoveThisWay('a')) 
                  playerPosXLeft += playerStepBackwards;
            }
            else if(pressed_d)
            {
               //Ako drzimo i 'w' i 'd' zelimo da nam se krece dijagonalno
              if(canMoveThisWay('d'))
                  playerPosXLeft += playerStepForward;
                //za sada koristim ovo ali svejedno je ime promenljive bitno je da je okej velicina :TODO   
            }
		        cameraOffsetY -= 0.02;
		        playerPosY -= 0.02;
		    }
		    if(playerPosY <= groundHeight[playerCurrentTile] && indJump == false)
		    {
		        playerPosY = groundLevel;
		        indFalling  = false;
		    }
	}
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




