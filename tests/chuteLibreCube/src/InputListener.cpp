#include "InputListener.h"

InputListener::InputListener(Application* app, RenderWindow* win, Camera* cam, SceneManager *sceneMgr, 
								bool bufferedKeys, bool bufferedMouse, bool bufferedJoy) 
   : ExampleFrameListener(win, cam, bufferedKeys, bufferedMouse, bufferedJoy)
{
    mSceneMgr = sceneMgr;
    mContinuer = true;

    mMouvement = Ogre::Vector3::ZERO;
    mVitesse = 1000;
    mVitesseRotation = 0.2;

    mMouse->setEventCallback(this);
    mKeyboard->setEventCallback(this);

	application = app;
}

// Called after all render targets have had their rendering commands issued, 
// but before render windows have been asked to flip their buffers over
bool InputListener::frameRenderingQueued(const FrameEvent& evt)
{
	// gestion des entrées clavier et souris
    if(mMouse)
        mMouse->capture();
    if(mKeyboard)
        mKeyboard->capture();

    Ogre::Vector3 deplacement = Ogre::Vector3::ZERO;
    deplacement = mMouvement * mVitesse * evt.timeSinceLastFrame;
    mCamera->moveRelative(deplacement);

    return mContinuer;
}

// Called just after a frame has been rendered
bool InputListener::frameEnded(const FrameEvent &evt)
{
	// mise à jour du monde physique et répercution sur le monde graphique
	application->gererPhysique();

	return mContinuer;
}

bool InputListener::mouseMoved(const OIS::MouseEvent &e)
{
    mCamera->yaw(Ogre::Degree(-mVitesseRotation * e.state.X.rel));
    mCamera->pitch(Ogre::Degree(-mVitesseRotation * e.state.Y.rel));
    return true;
}

bool InputListener::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
    return true; 
}

bool InputListener::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
    return true;
}
 
bool InputListener::keyPressed(const OIS::KeyEvent &e)
{
    switch(e.key)
    {
    case OIS::KC_ESCAPE:
        mContinuer = false;
        break;
    case OIS::KC_W:
        mMouvement.z -= 1;
        break;
    case OIS::KC_S:
        mMouvement.z += 1;
        break;
    case OIS::KC_A:
        mMouvement.x -= 1;
        break;
    case OIS::KC_D:
        mMouvement.x += 1;
        break;
    case OIS::KC_LSHIFT:
        mVitesse *= 2;
        break;
	case OIS::KC_SPACE:
		application->reset();
		break;
    }

    return mContinuer;
}

bool InputListener::keyReleased(const OIS::KeyEvent &e)
{
    switch(e.key)
    {
    case OIS::KC_W:
        mMouvement.z += 1;
        break;
    case OIS::KC_S:
        mMouvement.z -= 1;
        break;
    case OIS::KC_A:
        mMouvement.x += 1;
        break;
    case OIS::KC_D:
        mMouvement.x -= 1;
        break;
    case OIS::KC_LSHIFT:
        mVitesse /= 2;
        break;
    }
    return true;
}
