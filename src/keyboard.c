#include "keyboard.h"
#include "utility.h"
#include "sharedVars.h"


void setKeyboardFunc(void)
{
    glutKeyboardFunc(on_keyboard);
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
       
        //pokrecemo skok ako vec nije pokrenut
        if( indJump == false && indFalling == false)
        {
            updatePlayerJumpHeight();
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
    case 'p': //debag funkcija
          printf("Current tile: %d\n CurrentPosXLeft: %f\n Right x coordinate of previous tile: %f\n\n"
                        ,getPlayerCurrentTile(), playerPosXLeft, groundXCor[getPlayerCurrentTile()-1] + groundLengthOfTile);
          break;
    }
}

