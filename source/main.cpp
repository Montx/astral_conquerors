#include <Ogre.h>
#include <Bites/OgreApplicationContext.h>
#include <iostream>

class COgreTest : public OgreBites::ApplicationContext, public OgreBites::InputListener
{
public:
    COgreTest() : OgreBites::ApplicationContext("OgreTest"){}
    virtual ~COgreTest() {}

    bool keyPressed(const OgreBites::KeyboardEvent& evt)
    {
        if (evt.keysym.sym == OgreBites::SDLK_ESCAPE) 
        {
            getRoot()->queueEndRendering();
        }

        return true;
    }

    void setup()
    {
        OgreBites::ApplicationContext::setup();

        addInputListener(this);

        Ogre::Root* root = getRoot();
        Ogre::SceneManager* scnMgr = root->createSceneManager();

        Ogre::RTShader::ShaderGenerator* shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
        shadergen->addSceneManager(scnMgr);

        Ogre::Light* light = scnMgr->createLight("MainLight");
        Ogre::SceneNode* lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        lightNode->setPosition(0, 10, 15);
        lightNode->attachObject(light);

        Ogre::SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
        camNode->setPosition(0, 0, 15);
        camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);

        Ogre::Camera* cam = scnMgr->createCamera("myCam");
        cam->setNearClipDistance(5);
        cam->setAutoAspectRatio(true);
        camNode->attachObject(cam);

        getRenderWindow()->addViewport(cam);

        Ogre::Entity* ent = scnMgr->createEntity("Sinbad.mesh");
        Ogre::SceneNode* node = scnMgr->getRootSceneNode()->createChildSceneNode();
        node->attachObject(ent);
    }
};

int main(int argc, char* argv[])
{
    COgreTest test;
    test.initApp();
    test.getRoot()->startRendering();
    test.closeApp();
    
    return 0;
}