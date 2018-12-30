#ifndef SHARED_VARS_H
#define SHARED_VARS_H

#include <stdio.h>
#include <stdbool.h> 

//Moje promenljive

//Promenljive koje cuvaju velicinu prozora
extern float window_height; //visina
extern float window_width; //sirina

//Promenljiva koja ce mi govoriti da li sam u 3D prikazu ili 2D prikazu
extern bool active3D;

//promenljive koje cuvaju poziciju igraca
extern float playerPosXLeft;
extern float playerLength; //sirina kockice, kasnije modela
extern float playerPosXRight;
extern float playerPosY; 
extern int playerCurrentTile;
extern float playerStepForward;
extern float playerStepBackwards;

//animation parametar
extern bool animation_ongoing;

//da li smo aktivirali super skok
extern bool wingsActive;
	
//Parametar za x osu crvene ravni
extern float RedPlaneParam;

//Energija naseg igraca
extern int playerStamina;
extern float staminaIncrement;
 
 //kamera 
extern bool cameraTilt; //Da li je ili nije kamera malko nagnuta po x osi
                         //pritiskom na 'c' resavamo da li hocemo ili necemo ovo. 
extern float cameraOffsetX;
extern float cameraOffsetY;

//Kada tek krecemo koristimo ovo
extern bool just_started;

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

//bool promenljive za kretanje
extern bool pressed_a;
extern bool pressed_d;

//fullscreen
extern bool fullscreen;

//Da li je igra restartovana
extern bool has_been_restarted;

//Score
extern int score;

#endif