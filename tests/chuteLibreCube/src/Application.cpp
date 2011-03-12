#include "Application.h"
#include "InputListener.h"

void Application::createScene()
{
	createBulletWorld();

	SceneNode *node= mSceneMgr->getRootSceneNode()->createChildSceneNode("nodeTete", Vector3::ZERO, Quaternion::IDENTITY);

	// tête
	//Entity *head= mSceneMgr->createEntity("Tete", "ogrehead.mesh");
	//node->attachObject(head);

	// sol
	Plane plan(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane("sol", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plan, 500, 500, 100, 100, true, 1, 1, 1, Vector3::UNIT_Z);
	Entity *ent= mSceneMgr->createEntity("EntiteSol", "sol");
	node->attachObject(ent);
	ent->setMaterialName("Examples/GrassFloor");

	// boîte en chute libre
	Entity *box= mSceneMgr->createEntity("Box", "cube.mesh"); // 100x100x100 cube
	SceneNode *nodeBox= mSceneMgr->getRootSceneNode()->createChildSceneNode("nodeBox");
	nodeBox->attachObject(box);

	// lumière directionnelle
	mSceneMgr->setAmbientLight(ColourValue(0.0, 0.0, 0.0));
	Light *light = mSceneMgr->createLight("lumiere1");
	light->setDiffuseColour(1.0, 0.7, 1.0);
	light->setSpecularColour(1.0, 0.7, 1.0);
	light->setPosition(-100, 200, 100);
	light->setPowerScale(3.0);
	light->setType(Light::LT_DIRECTIONAL);
	light->setDirection(10.0, -20.0, -5);

	// ombres
	light->setCastShadows(true);
	//head->setCastShadows(true);
	ent->setCastShadows(false);
	box->setCastShadows(true);

	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
}

void Application::createCamera() // appelée automatiquement
{
	mCamera = mSceneMgr->createCamera("Ma Camera");
	mCamera->setPosition(Vector3(-350.0, 500.0, 500.0));
	mCamera->lookAt(Vector3(100.0, 0.0, -200.0));
	mCamera->setNearClipDistance(1);
	mCamera->setFarClipDistance(10000);
	if (mRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE))
		mCamera->setFarClipDistance(0);
}

void Application::createViewports() // appelée automatiquement
{
	Viewport *vue = mWindow->addViewport(mCamera);
	mCamera->setAspectRatio(Real(vue->getActualWidth()) / Real(vue->getActualHeight()));
	vue->setBackgroundColour(ColourValue(0.8, 0.8, 0.8));
}

void Application::createFrameListener() // appelée automatiquement
{
	mFrameListener= new InputListener(this, mWindow, mCamera, mSceneMgr, true, true, false);
    mRoot->addFrameListener(mFrameListener);
}

void Application::createBulletWorld()
{
	// configuration par défaut pour la mémoire, la collision
	myCollisionConfiguration = new btDefaultCollisionConfiguration(); 

	// collision dispatcher par défaut (parallèle : cf. Extras/BulletMultiThreaded)
	myDispatcher = new btCollisionDispatcher(myCollisionConfiguration); 

	// initialisation du broadphase (détecteur des objets où leurs AABB se chevauchent) 
	myBroadphase = new btDbvtBroadphase();

	// constraint solver par défaut (parallèle : cf. Extras/BulletMultiThreaded)
	mySequentialImpulseConstraintSolver = new btSequentialImpulseConstraintSolver; 

	// initialisation du monde physique Bullet
	myWorld = new btDiscreteDynamicsWorld(myDispatcher,myBroadphase,mySequentialImpulseConstraintSolver,myCollisionConfiguration);

	// définition de la gravité
	myWorld->setGravity( btVector3(0,-10,0) ); 

	// création des éléments physiques
	createBulletBox();
	createBulletSol();
}

void Application::createBulletBox()
{
	// On déclare une forme et on l'initialise en tant que boite de la taille 1,1,1 
	btCollisionShape* shape = new btBoxShape( btVector3(50,50,50) );

	// On initialise notre btTransform et on lui dit une position (la position de la boite) 
	myTransform.setIdentity();
	myTransform.setOrigin( btVector3(0,300,0) );
	myTransform.setRotation(btQuaternion(btVector3(0.0, 0.0, 0.1), 40));

	// L'inertie de la boite 
	btVector3 localInertia(0,0,0);

	// Le poids de la boite 
	btScalar mass = 0.5f;

	// On calcule l'inertie suivant le poids.
	if ( mass )
		shape->calculateLocalInertia( mass, localInertia );

	// Il est conseillé d'utiliser motionState car il fournit des capacités d'interpolation et synchronise seulement les objets "actifs". 
	myMotionState_Box = new btDefaultMotionState(myTransform);

	// On regroupe les informations de la boite à partir de la masse, l'inertie, etc ...
	btRigidBody::btRigidBodyConstructionInfo myBoxRigidBodyConstructionInfo( mass, myMotionState_Box, shape, localInertia );

	// On construit le corps de la boite à partir de l'information regroupée 
	body_box = new btRigidBody(myBoxRigidBodyConstructionInfo);

	// On ajoute notre boite dans le monde Bullet 
	myWorld->addRigidBody(body_box);
}

void Application::createBulletSol()
{
	// Forme en tant que boite
	btCollisionShape* shape_sol = new btBoxShape( btVector3(250,1,250) );  // ou btStaticPlaneShape 

	// Position du sol
	myTransform.setIdentity();
	myTransform.setOrigin( btVector3(0,-1,0) );
	btVector3 localInertiaSol(0,0,0);

	btScalar mass = 0; // Le fait que le poids de cet objet soit zéro le rend statique

	myMotionState_Sol = new btDefaultMotionState(myTransform);

	btRigidBody::btRigidBodyConstructionInfo sol_info( mass, myMotionState_Sol, shape_sol, localInertiaSol );

	body_sol = new btRigidBody(sol_info);

	// On ajoute le sol dans le monde Bullet
	myWorld->addRigidBody(body_sol); 
}

void Application::gererPhysique()
{
	if ( myWorld )
		myWorld->stepSimulation( 1.0 / 60.0 );
	//  myWorld->stepSimulation( Ogre::ControllerManager::getElapsedTime() );

	// application des changements du monde physique au monde graphique
	btVector3 position = body_box->getCenterOfMassPosition();
	mSceneMgr->getSceneNode("nodeBox")->setOrientation((Ogre::Quaternion)body_box->getOrientation());
	mSceneMgr->getSceneNode("nodeBox")->setPosition(position.getX(), position.getY(), position.getZ());
}

void Application::reset()
{
	myTransform.setIdentity();
	myTransform.setOrigin( btVector3(0,300,0) );
	myTransform.setRotation(btQuaternion(btVector3(0.0, 0.0, 0.1), 40));

	body_box->setCenterOfMassTransform(myTransform);
	body_box->setLinearVelocity(btVector3(0.0, 0.0, 0.0));
	body_box->setAngularVelocity(btVector3(0.0, 0.0, 0.0));
	body_box->activate(true);
}