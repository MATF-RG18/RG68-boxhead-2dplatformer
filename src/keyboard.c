#include "keyboard.h"
#include "utility.h"
#include "sharedVars.h"

//predefinisane promenljive za dirke na tastaturi
#define ESCAPE 27
#define SPACE 32

// definisemo promenljivu koja ce nam cuvati energiju naseg igraca
#define FULL 100


void setKeyboardFunc(void)
{
    glutKeyboardFunc(on_keyboard);
}


void on_keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case ESCAPE:
        // Zavrsava se program.
        free(groundXCor);
        free(groundHeight);
        exit(EXIT_SUCCESS);
        break;
    case 'd':
    case 'D':
        //krecemo se na desnu stranu
        if(canMoveThisWay('d'))
        playerPosXLeft += playerStepForward;
        break;
    case 'a':
    case 'A':
        //krecemo se na levu stranu ako mozemo
        if(canMoveThisWay('a'))
            playerPosXLeft += playerStepBackwards;
        break;
    case 'w':
    case 'W':  
        //pokrecemo skok ako vec nije pokrenut
        if(!wingsActive)
       {
	        if( indJump == false && indFalling == false)
	        {
		        	if(playerStamina >= 30)
		        {
		        	playerStamina -= 30;
		            updatePlayerJumpHeight();
		            indJump = true;
		        }
		    }
	    }
        
        else
        {
        	playerPosY += playerStepForward; //za sada koristim ovo ali svejedno je ime promenljive bitno je da je okej velicina :TODO
        }
        break;
    

    case 's':
    case 'S':
    	if(wingsActive)
    	{
    		if(playerPosY - playerStepForward >= groundHeight[getPlayerCurrentTile()])
    		playerPosY -= playerStepForward;
    	}
    	break;
    // case 'c':
    // case 'C':
    //       //biramo da li zelimo kamera da nam bude tilt ili ne.
    //       if( cameraTilt == true){
    //           cameraTilt = false;}
    //       else
    //           cameraTilt = true;
    //       break; 
    case 'r':
    case 'R':
    	  //biramo da li zelimo 3D ili 2D
          if( cameraTilt == true)
          {
              cameraTilt = false;
    	  }
    	  else
    	  {
            cameraTilt = true;
          }
          break; 
     
     case SPACE:
     	   if(!wingsActive &&(playerStamina >= 30))
     	   {	
     	   		playerStamina -= 20;
     	    	wingsActive = true;
    	   }
    	   else if(wingsActive)
    	   {
    	   	 indFalling = true;
    	   	 wingsActive = false;
    	   }
    }
}

