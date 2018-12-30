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
    glutKeyboardUpFunc(on_release);
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
       if(animation_ongoing)
       { 
         pressed_d = true;
         //Zelimo da se ogranicimo od mogucnosti da se ubrzano krece.
         if((!indJump && !indFalling)|| wingsActive)
           if(canMoveThisWay('d'))
              playerPosXLeft += playerStepForward;
       }
       break;
    case 'a':
    case 'A':
       if(animation_ongoing)
       {        
        pressed_a = true;
        //krecemo se na levu stranu ako mozemo
       
       //Zelimo da se ogranicimo od mogucnosti da se ubrzano krece.
       if((!indJump && !indFalling) || wingsActive)
         if(canMoveThisWay('a'))
             playerPosXLeft += playerStepBackwards;
      }
       break;
    case 'w':
    case 'W':  
       
      if(animation_ongoing)
      { //pokrecemo skok ako vec nije pokrenut
          if(!wingsActive)
         {
  	        if(indJump == false && indFalling == false)
  	        {
  		        	if(playerStamina >= 20)
  		        {
  		        	playerStamina -= 20;
  		            updatePlayerJumpHeight();
  		            indJump = true;
  		        }
  		    }
  	    }
      
        
        else
        {
            if( indJump == false && indFalling == false)
                indJump = true;
            
               //Ako je pritisnuto dugme samo dugme 'w' onda idemo horizontalno
               playerPosY += playerStepForward; //za sada koristim ovo ali svejedno je ime promenljive bitno je da je okej velicina :TODO
        }
      }
        break;
    

    case 's':
    case 'S':
      if(animation_ongoing)
      {
      	if(wingsActive)
      	{
      		if(playerPosY - playerStepForward >= groundHeight[getPlayerCurrentTile()])
      		playerPosY -= playerStepForward;
      	}
        else
        {
          pressed_a = pressed_d = false;
          indJump = false;
          indFalling = true;
        }
      }
      break;
      
    case 'f':
    case 'F':
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
     case 'r':
     case 'R':
           has_been_restarted = true;
           animation_ongoing = true;
           playerPosXLeft = groundXCor[2] + groundLengthOfTile/2;
           playerPosY = groundHeight[2];
           pressed_d = pressed_a = false;
           score = 0;
           playerStamina = FULL;
           RedPlaneParam = 0;
           indJump = false;
           indFalling = false;
           wingsActive = false;
           playerPosY = groundHeight[getPlayerCurrentTile()];
          break;
     case SPACE:
        if(animation_ongoing)
        {
     	   if(!wingsActive &&(playerStamina >= 30))
     	   {
                //deaktiviramo skok jer ne zelimo da nam se nastavi kada iskljucimo krila
            indJump = false;	
     	   		playerStamina -= 20;
     	    	wingsActive = true;
    	   }
    	   else if(wingsActive)
    	   {
           pressed_a = false;
           pressed_d = false;
           indJump = false;
    	   	 indFalling = true;
    	   	 wingsActive = false;
    	   }
       }
         break;
      case 'e':
      case 'E':
          {
            if (!fullscreen)
            {
                //Fullscreen
               glutFullScreen();
               fullscreen = true;
            }
            else
            {
                //Windowed
               glutReshapeWindow(1200, 900);
               glutPositionWindow(0,0);
               fullscreen = false;
            }
          }
          break;
    }

}

void on_release(unsigned char key, int x, int y)
{
    //Radimo switch za nasu dugmad
    switch (key)
    {
        case 'a':
        case 'A':   
              pressed_d = false;
              break;
        case 'd':
        case 'D':
              pressed_a = false;
              break;
    }
}
