/**
 *  Test d'intégration Bullet-Ogre-OIS
 *  ----------------------------------
 *
 *    compilation :
 *        includes :
 *            ../inc
 *            {BULLET}/src
 *            {BULLET}/Extras/Serialize/BulletWorldImporter
 *            {OGRE}/include
 *            {OGRE}/include/OGRE
 *            {OGRE}/boost_1_42
 *        libraries :
 *            bullet
 *            boost
 *            OGRE
 *            OIS
 *        dépendances : 
 *            OgreMain.lib
 *            OIS.lib
 *            BulletCollision.lib
 *            BulletDynamics.lib
 *            LinearMath.lib
 *            BulletWorldImporter.lib
 *    
 *    utilisation :
 *        Q,S,D,Z,A,E : déplacement caméra
 *        souris : orientation caméra
 *        espace : reset
 *
 *    fichiers :
 *        cube.mesh, wheel.mesh : accessibles par dossiers dans 
 *        wheel.bullet
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

    std::cout << "test" << std::endl;

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