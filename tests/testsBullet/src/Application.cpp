#include "Application.h"
#include "InputListener.h"

void Application::createScene()
{
    createBulletWorld();

    SceneNode *node= mSceneMgr->getRootSceneNode()->createChildSceneNode("nodeTete", Vector3::ZERO, Quaternion::IDENTITY);

    // sol
    Entity *sol = mSceneMgr->createEntity("Sol", "cube.mesh"); // 100x100x100 cube
    SceneNode *nodeSol= mSceneMgr->getRootSceneNode()->createChildSceneNode("nodeSol");
    nodeSol->scale(5, 1.0/50.0, 5); // 500x2x500 cube
    nodeSol->attachObject(sol);

    // boîte en chute libre
    Entity *box = mSceneMgr->createEntity("Box", "cube.mesh"); // 100x100x100 cube
    SceneNode *nodeBox= mSceneMgr->getRootSceneNode()->createChildSceneNode("nodeBox");
    nodeBox->attachObject(box);

    // partie fixe du pivot (A)
    Entity *pivotA = mSceneMgr->createEntity("PivotA", "cube.mesh"); // 100x100x100 cube
    SceneNode *nodePivotA= mSceneMgr->getRootSceneNode()->createChildSceneNode("nodePivotA");
    nodePivotA->scale(1.0, 0.5, 0.5); // 100x50x50 cube
    nodePivotA->attachObject(pivotA);

    // partie mobile du pivot (B)
    Entity *pivotB = mSceneMgr->createEntity("PivotB", "cube.mesh"); // 100x100x100 cube
    SceneNode *nodePivotB= mSceneMgr->getRootSceneNode()->createChildSceneNode("nodePivotB");
    nodePivotB->scale(1.0, 0.5, 0.5); // 100x50x50 cube
    nodePivotB->attachObject(pivotB);

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
    sol->setCastShadows(true);
    box->setCastShadows(true);
    pivotA->setCastShadows(true);
    pivotB->setCastShadows(true);

    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_ADDITIVE); // SHADOWTYPE_STENCIL_MODULATIVE
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
    createBulletPivotA();
    createBulletPivotB();

    // liaison pivot entre A et B
    pivotAB = new btHingeConstraint(*body_pivotA,          *body_pivotB, 
                                    btVector3(50, -25, 0), btVector3(-50, -25, 0),
                                    btVector3(0, 0, 1),    btVector3(0, 0, 1));
	pivotAB->enableAngularMotor	(	true, 20, 40);	
    myWorld->addConstraint(pivotAB, true);
    
                                    
}

void Application::createBulletBox()
{
    // On déclare une forme et on l'initialise en tant que boite  
    btCollisionShape* shape = new btBoxShape( btVector3(50,50,50) ); // 100x100x100 box

    // On initialise notre btTransform et on lui dit une position (la position de la boite) 
    myTransform.setIdentity();
    myTransform.setOrigin( btVector3(260,300,0) );
    myTransform.setRotation(btQuaternion(btVector3(1, 0, 0), 40)); // rotation de 40°
    
    // L'inertie de la boite 
    btVector3 localInertia(0,0,0);

    // Le poids de la boite 
    btScalar mass = 10.0f;

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

void Application::createBulletPivotA()
{
    btCollisionShape* shape_pivotA = new btBoxShape( btVector3(50,25,25) );  // 100x50x50 box

    myTransform.setIdentity();
    myTransform.setOrigin( btVector3(-50,225,-175) );
    btVector3 localInertiaPivotA(0,0,0);

    btScalar mass = 0; // statique

    myMotionState_PivotA = new btDefaultMotionState(myTransform);
    btRigidBody::btRigidBodyConstructionInfo pivotA_info( mass, myMotionState_PivotA, shape_pivotA, localInertiaPivotA );
    body_pivotA = new btRigidBody(pivotA_info);
    myWorld->addRigidBody(body_pivotA); 
}

void Application::createBulletPivotB()
{
    btCollisionShape* shape_pivotB = new btBoxShape( btVector3(50,25,25) ); // 100x50x50 box

    myTransform.setIdentity();
    myTransform.setOrigin( btVector3(50,225,-175) );
    btVector3 localInertiaPivotB(0,0,0);

    btScalar mass = 10.0f;

    if ( mass )
        shape_pivotB->calculateLocalInertia( mass, localInertiaPivotB );

    myMotionState_PivotB = new btDefaultMotionState(myTransform);
    btRigidBody::btRigidBodyConstructionInfo pivotB_info( mass, myMotionState_PivotB, shape_pivotB, localInertiaPivotB );
    body_pivotB = new btRigidBody(pivotB_info);
    myWorld->addRigidBody(body_pivotB);
}

void Application::createBulletSol()
{
    // Forme en tant que boite
    btCollisionShape* shape_sol = new btBoxShape( btVector3(250,1,250) );  // 500x2x500 box

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

    syncBulletToOgre(body_box, "nodeBox");
    syncBulletToOgre(body_sol, "nodeSol");
    syncBulletToOgre(body_pivotA, "nodePivotA");
    syncBulletToOgre(body_pivotB, "nodePivotB");
}

void Application::reset()
{
    myTransform.setIdentity();
    myTransform.setOrigin( btVector3(260,300,0) );
    myTransform.setRotation(btQuaternion(btVector3(1, 0, 0), 40));
    body_box->setCenterOfMassTransform(myTransform);
    body_box->setLinearVelocity(btVector3(0.0, 0.0, 0.0));
    body_box->setAngularVelocity(btVector3(0.0, 0.0, 0.0));
    body_box->activate(true);

    myTransform.setIdentity();
    myTransform.setOrigin( btVector3(50,225,-175) );
    body_pivotB->setCenterOfMassTransform(myTransform);
    body_pivotB->setLinearVelocity(btVector3(0.0, 0.0, 0.0));
    body_pivotB->setAngularVelocity(btVector3(0.0, 0.0, 0.0));
    body_pivotB->activate(true);
}

void Application::syncBulletToOgre(btRigidBody *rigidBody, const Ogre::String nodeName)
{
    mSceneMgr->getSceneNode(nodeName)->setPosition(rigidBody->getCenterOfMassTransform().getOrigin().getX(),
                                                   rigidBody->getCenterOfMassTransform().getOrigin().getY(),
                                                   rigidBody->getCenterOfMassTransform().getOrigin().getZ());    

    mSceneMgr->getSceneNode(nodeName)->setOrientation(rigidBody->getCenterOfMassTransform().getRotation().normalize().getW(),
                                                      rigidBody->getCenterOfMassTransform().getRotation().normalize().getX(),
                                                      rigidBody->getCenterOfMassTransform().getRotation().normalize().getY(),
                                                      rigidBody->getCenterOfMassTransform().getRotation().normalize().getZ());
}
