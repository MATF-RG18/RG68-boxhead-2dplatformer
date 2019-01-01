#include "sharedVars.h"
#include <stdio.h>
#include <stdbool.h>

//Moje promenljive

//Promenljive koje cuvaju velicinu prozora
float window_height; //visina
float window_width; //sirina

//Da li smo aktivirali super skok
bool wingsActive= false;


//Energija naseg igraca, 100 je maksimalna vrednost
int playerStamina = 100;
float staminaIncrement = 0;

bool just_started = true;


//promenljive koje cuvaju poziciju igraca
 float playerPosXLeft = 1.25;
 float playerLength = 0.1; //sirina kockice, kasnije modela
 float playerPosXRight;
 float playerPosY = 0; 
 int playerCurrentTile;
 float playerStepBackwards = -0.020;
 float playerStepForward = 0.020;

 //Parametar za x osu crvene ravni
 float RedPlaneParam = 0;

 //animation parametar
 bool animation_ongoing = true;

 //promenljiva koja ce mi reci da li sam u 3D prikazu ili 2D prikazu
 bool active3D = true;

 //kamera 
 bool cameraTilt = true; //Da li je ili nije kamera malko nagnuta po x osi
                         //pritiskom na 'c' resavamo da li hocemo ili necemo ovo. 
 float cameraOffsetX = 0.2;
 float cameraOffsetY = 1;

 float groundLevel = 0; //nivo terena, za sada je to 0 odnosno x osa

 float dnFPS = 1000; //koristimo ga u on_timer pozivu za kontrolu frejmova po sekundi

 bool indJump = false; //indikator da li je igrac trenutno u skoku
 bool indFalling = false;

 float playerJumpHeight; //Visina koju igrac moze da dosegne prilikom trenutnog skoka po y osi
 float playerMaxJumpHeight = 0.5; //Maksimalna visina skoka koju igrac moze da dosegne sa x ose (prirodna visina skoka)

//Nizovi za kontrolu zemlje po kojoj ce igrac hodati
 float* groundXCor; //X koordinate svake od ploca koje se nadovezuju
 float* groundHeight; //visina svake od ploca koje nadovezujemo
 bool*  groundIsSet; //indikator da li smo ili ne vec postavili visinu i x koordinatu ovog terena
 float  groundLengthOfTile = 0.5; // "duzina" ploce
 float  groundDepth = - 3;


 int groundNumOfTiles = 20; //Ove dve velicine koristimo za kontrolu realloc funkcije
 int groundReallocStep = 5; 
 

 //bool promenljive za kretanje
 bool pressed_a = false;
 bool pressed_d = false;

 //fullscreen
 bool fullscreen = true;


//Da li je igra restartovana
bool has_been_restarted = true;

 //Score
 int score = 0;
