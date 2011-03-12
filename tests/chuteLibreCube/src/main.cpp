/**
 *  Test d'intégration Bullet-Ogre-OIS
 *  ----------------------------------
 *
 *	compilation :
 *		dépendances : OGRE (OIS, boost), bullet
 *	
 *	utilisation :
 *		Q,S,D,Z : déplacement caméra
 *		souris : orientation caméra
 *		espace : reset cube		 
 */

#include <Ogre.h>
#include <btBulletDynamicsCommon.h>
#include "Application.h"

#if OGRE_PLATFORM == PLATFORM_WIN32 || OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
int main(int argc, char **argv)
#endif
{
	Application app;

	try 
	{
		app.go();
	} 
	catch(Ogre::Exception& e) 
	{
		#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
				MessageBoxA(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
		#else
				fprintf(stderr, "An exception has occurred: %s\n", e.getFullDescription().c_str());
		#endif
    }

    return 0;
}