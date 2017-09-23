/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/
Tutorial Framework (for Ogre 1.9)
http://www.ogre3d.org/wiki/
-----------------------------------------------------------------------------
*/

#include "TutorialApplication.h"

//---------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{
}
//---------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

//---------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    // Ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    //Set camera
    mCamera->setPosition(-300, 300, 300);
    mCamera->lookAt(0, 0, 0);
    // Light sources
    Ogre::Light * light = mSceneMgr->createLight("MainLight");
    light->setPosition(20, 200, 50);

    //Plane
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingleton().createPlane(
        "ground",
        Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 
        400, 400, 20, 20, 
        true, 
        1, 5, 5, Ogre::Vector3::UNIT_Z);
    //Bottom Plane
    Ogre::Entity* groundEntity = mSceneMgr->createEntity("ground");
    groundEntity->setCastShadows(false);
    groundEntity->setMaterialName("Examples/Rockwall");
    Ogre::SceneNode * groundNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    groundNode->setPosition(0, -200, 0);
    groundNode->attachObject(groundEntity);
    //Top Plane
    Ogre::Entity* ceilingEntity = mSceneMgr->createEntity("ground");
    ceilingEntity->setCastShadows(false);
    ceilingEntity->setMaterialName("Examples/Rockwall");
    Ogre::SceneNode * ceilingNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    ceilingNode->setPosition(0, 200, 0);
    ceilingNode->roll(Ogre::Degree(180));
    ceilingNode->attachObject(ceilingEntity);
    //Walls
    //Left wall
    Ogre::Entity * wallEntity1 = mSceneMgr->createEntity("ground");
    wallEntity1->setMaterialName("Examples/Rockwall");
    Ogre::SceneNode * wallNode1 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    wallNode1->setPosition(-200, 0, 0);
    wallNode1->roll(Ogre::Degree(-90));
    wallNode1->yaw(Ogre::Degree(90));
    wallNode1->attachObject(wallEntity1);
    //Right wall
    Ogre::Entity * wallEntity2 = mSceneMgr->createEntity("ground");
    wallEntity2->setMaterialName("Examples/Rockwall");
    Ogre::SceneNode * wallNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    wallNode2->setPosition(200, 0, 0);
    wallNode2->roll(Ogre::Degree(90));
    wallNode2->yaw(Ogre::Degree(-90));
    wallNode2->attachObject(wallEntity2);
    //Near wall
    Ogre::Entity * wallEntity3 = mSceneMgr->createEntity("ground");
    wallEntity3->setMaterialName("Examples/Rockwall");
    Ogre::SceneNode * wallNode3 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    wallNode3->setPosition(0, 0, 200);
    wallNode3->pitch(Ogre::Degree(-90));
    wallNode3->attachObject(wallEntity3);
    //Far wall
    Ogre::Entity * wallEntity4 = mSceneMgr->createEntity("ground");
    wallEntity4->setMaterialName("Examples/Rockwall");
    Ogre::SceneNode * wallNode4 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    wallNode4->setPosition(0, 0, -200);
    wallNode4->pitch(Ogre::Degree(90));
    wallNode4->attachObject(wallEntity4);

    //Ball
    Ogre::Entity * ballEntity = mSceneMgr->createEntity("Ball", "sphere.mesh");
    ballEntity->setCastShadows(true);
    ballNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("ballNode");
    ballNode->setScale(0.3, 0.3, 0.3);
    ballNode->attachObject(ballEntity);

    radius = 30.6;  //Don't know where this number comes from
    currentDir = Ogre::Vector3(0, -200, 0);

}

//---------------------------------------------------------------------------
bool TutorialApplication::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
    bool ret = BaseApplication::frameRenderingQueued(fe);
    if(!processUnbufferedInput(fe))
        return false;

    //Setup collision
    Ogre::Entity * ballEntity = static_cast<Ogre::Entity*>(ballNode->getAttachedObject(0));
    Ogre::AxisAlignedBox box = ballEntity->getWorldBoundingBox();

    Ogre::Vector3 newDir = currentDir;
    //hit floor
    //TODO: Just determine which normal needs to be applied
    if(box.getCenter().y - radius <= -200)
    {
        newDir = currentDir - 2 * (currentDir.dotProduct(
                 Ogre::Vector3(0, 1, 0)) * Ogre::Vector3(0, 1, 0));
    }
    ballNode->translate(
        newDir * fe.timeSinceLastFrame,
        Ogre::Node::TS_LOCAL);
    currentDir = newDir;

    return ret;
}

//---------------------------------------------------------------------------
bool TutorialApplication::processUnbufferedInput(const Ogre::FrameEvent& fe)
{
    static bool mouseDownLastFrame = false;
    static Ogre::Real toggleTimer = 0.0f;
    static Ogre::Real rotate = 0.13;
    static Ogre::Real move = 250;

    bool leftMouseDown = mMouse->getMouseState().buttonDown(OIS::MB_Left);
    if(leftMouseDown && !mouseDownLastFrame)
    {
        Ogre::Light * light = mSceneMgr->getLight("MainLight");
        light->setVisible(!light->isVisible());
    }
    mouseDownLastFrame = leftMouseDown;
    return true;
}

//---------------------------------------------------------------------------

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;

        try {
            app.go();
        } catch(Ogre::Exception& e)  {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occurred: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------
