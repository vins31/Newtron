#ifndef DEF_InputListener
#define DEF_InputListener

#include <OIS/OIS.h>
#include <ExampleFrameListener.h>
#include "Application.h"

class InputListener : public ExampleFrameListener, OIS::KeyListener, OIS::MouseListener // FrameTimeControllerValue
{
public:
    InputListener(Application* app, RenderWindow* win, Camera* cam, SceneManager *sceneMgr, bool bufferedKeys = false, 
		bool bufferedMouse = false, bool bufferedJoy = false);
    bool frameRenderingQueued(const FrameEvent& evt);
	bool frameEnded(const FrameEvent &evt);
	bool mouseMoved(const OIS::MouseEvent &e);
	bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool keyPressed(const OIS::KeyEvent &e);
	bool keyReleased(const OIS::KeyEvent &e);

private:
    Ogre::SceneManager *mSceneMgr;
    bool mContinuer;

    Ogre::Vector3 mMouvement;
    Ogre::Real mVitesse;
    Ogre::Real mVitesseRotation;

	Application *application;
};

#endif
