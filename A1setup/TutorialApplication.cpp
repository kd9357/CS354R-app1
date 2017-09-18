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
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0, 0, 0));
    mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    //Set camera
    mCamera->setPosition(0, 47, 222);   //Pull camera up and back
    // Light sources
    Ogre::Light * light = mSceneMgr->createLight("MainLight");
    light->setPosition(20, 80, 50);

    //Plane
    // Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    // Ogre::MeshManager::getSingleton().createPlane(
    //     "ground",
    //     Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
    //     plane, 1500, 1500, 20, 20, true, 1, 5, 5, Ogre::Vector3::UNIT_Z);
    // Ogre::Entity* groundEntity = mSceneMgr->createEntity("ground");
    // groundEntity->setCastShadows(false);
    // groundEntity->setMaterialName("Examples/Rockwall"); //may break
    // mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);

    //Entity
    // Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
    // ogreHead->setCastShadows(true);
    // mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ogreHead);

    Ogre::Entity* ogreHead2 = mSceneMgr->createEntity("Head2", "ogrehead.mesh");
    Ogre::SceneNode* headNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode(
        Ogre::Vector3(84, 48, 0));  //Setting position ourselves
    headNode2->attachObject(ogreHead2);

    //Normals? Texture? something not right
    Ogre::Entity* ball = mSceneMgr->createEntity("Ball", "sphere.mesh");
    ball->setCastShadows(true);
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(ball);
    ball->setMaterialName("droplet.png");

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
