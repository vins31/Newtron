#ifndef DEF_Application
#define DEF_Application

#include <ExampleApplication.h>
#include <btBulletDynamicsCommon.h>

class Application : public ExampleApplication
{
public:
    void createScene();
	void createCamera();
	void createViewports();
	void createFrameListener();
	void createBulletWorld();
	void createBulletBox();
	void createBulletSol();
	void gererPhysique();
	void reset();
private:
	btDiscreteDynamicsWorld *myWorld; // monde physique
	btBroadphaseInterface *myBroadphase; // d�tection de chevauchement AABB d'objets
	btCollisionDispatcher *myDispatcher; // algorithmes de gestion de collisions
	btDefaultCollisionConfiguration *myCollisionConfiguration; // configuration des allocataires de m�moires
	btSequentialImpulseConstraintSolver *mySequentialImpulseConstraintSolver; // impl�mentation SIMD rapide de la m�thode Projected Gauss Seidel (iterative LCP)
	btTransform myTransform; // position ou orientation
	btDefaultMotionState *myMotionState_Box; // synchronisation des transformations
	btDefaultMotionState *myMotionState_Sol; // synchronisation des transformations 
	btRigidBody *body_box; // bo�te en chute libre
	btRigidBody	*body_sol; // sol
};

#endif