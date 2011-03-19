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
    void createBulletPivotA();
    void createBulletPivotB();
    void createBulletSol();
    void gererPhysique();
    void reset();
    void syncBulletToOgre(btRigidBody *rigidBody, const Ogre::String nodeName);
private:
    btDiscreteDynamicsWorld *myWorld; // monde physique
    btBroadphaseInterface *myBroadphase; // détection de chevauchement AABB d'objets
    btCollisionDispatcher *myDispatcher; // algorithmes de gestion de collisions
    btDefaultCollisionConfiguration *myCollisionConfiguration; // configuration des allocataires de mémoires
    btSequentialImpulseConstraintSolver *mySequentialImpulseConstraintSolver; // implémentation SIMD rapide de la méthode Projected Gauss Seidel (iterative LCP)
    btTransform myTransform; // position ou orientation
    btDefaultMotionState *myMotionState_Box; // synchronisation des transformations
    btDefaultMotionState *myMotionState_Sol;
    btDefaultMotionState *myMotionState_PivotA;
    btDefaultMotionState *myMotionState_PivotB;
    btRigidBody *body_box; // boîte en chute libre
    btRigidBody *body_sol; // sol
    btRigidBody *body_pivotA; // partie fixe du pivot
    btRigidBody *body_pivotB; // partie mobile du pivot
    btHingeConstraint *pivotAB; // liaison pivot entr A et B
};

#endif