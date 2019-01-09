#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Scene.h"
#include "Input.h"
#include "Shader.h"
#include "Camera.h"
#include "Light.h"
#include "Utility.h"
#include "Physics.h"
#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

Scene::Scene()
{
	m_simpleSh = new Shader("../shaders/simpleVert.txt", "../shaders/simpleFrag.txt");
	m_lightingSh = new Shader("../shaders/lightVert.txt", "../shaders/lightFrag.txt");
	m_uiSh = new Shader("../shaders/UI Vert.txt", "../shaders/UI Frag.txt");
	m_mainCam = new Camera(glm::vec3(-0, 5, -30));
	m_input = new Input();

	m_templateWall = new GameObject(glm::vec3(5000.0f, 0.0f, 0.0f));
	m_templateWall->addBoxShape("diffuse.bmp", glm::vec3(1.0f));
	m_templateWall->setTag("wall");
	m_templateWall->setShader(m_lightingSh);

}

Room* Scene::createRoom(float _x, float _y, float _z, glm::vec3 _pos)
{
	Room* room = new Room;
	std::vector<GameObject*> wall;
	wall.resize(6);
	for (int i = 0; i < 6; i++)
	{
		wall[i] = utility::copy(m_templateWall);
		wall[i]->setTag("w");
	}
	wall[0]->setTag("floor");
	wall[1]->setTag("roof");
	glm::vec3 pos;

	// Roof and floor	
	pos.x = _pos.x;	
	pos.y = _pos.y + (_y / 2.0f);
	pos.z = _pos.z;
	wall[0]->setPosition(pos);
	wall[0]->m_shapeComp->setScale(_x + 2.0f, 0.001f, _z + 2.0f);
	


	pos.y = _pos.y - (_y/2.0f);
	wall[1]->setPosition(pos);
	wall[1]->m_shapeComp->setScale(_x + 2.0f, 0.001f, _z + 2.0f);
	

	//X pair
	pos.x = _pos.x + (_x / 2.0f);
	pos.y = _pos.y;
	pos.z = _pos.z;	
	wall[2]->setPosition(pos);
	wall[2]->m_shapeComp->setScale(0.001f, _y + 2.0f, _z + 2.0f);
	


	pos.x = _pos.x - (_x / 2.0f);
	wall[3]->setPosition(pos);
	wall[3]->m_shapeComp->setScale(0.001f, _y + 2.0f, _z + 2.0f);
	

	//Z pair
	
	pos.x = _pos.x;
	pos.y = _pos.y;	
	pos.z = (_pos.z) + _z /2.0f;	
	wall[4]->setPosition(pos);
	wall[4]->m_shapeComp->setScale(_x + 2.0f, _y + 2.0f, 0.001f);
	

	pos.z = _pos.z - (_z / 2.0f);
	wall[5]->setPosition(pos);
	wall[5]->m_shapeComp->setScale(_x + 2.0f, _y + 2.0f, 0.001f);
	room->m_walls = wall;
	for (int i = 0; i < wall.size(); i++)
	{
		m_object.push_back(wall[i]);
	}
	return room;
}

Room* Scene::createRoom(float _x, float _y, float _z, int _NESW, Room * _prev)
{
	return new Room();
}

void Scene::createStartScene()
{
	//Spheres are size 1/1/1
	//Boxes are size 1/1/1
	//Planes are size 1/0/1 
	//Meshes may vary. Mesh sizes are used to determine their hitbox (box collisions are always tested before the mesh collision for efficiency)

	GameObject *shape = new GameObject(glm::vec3(-10.0f, 15.0f, 0.0f));
	shape->addSphereShape("red.png", 5.0f);
	shape->addPhysics("testShape", 20.0f, 1.0f);
	shape->setShader(m_lightingSh);
	shape->m_shapeComp->setShine(3);

	GameObject *lightBulb = new GameObject(glm::vec3(-10, 20, 5));
	lightBulb->addSphereShape("red.png", 1.0f);
	lightBulb->setTag("bulb");
	lightBulb->setShader(m_simpleSh);

	GameObject *floor = new GameObject(glm::vec3(0.0f, 0.0f, 0.0f));
	floor->addPlaneShape("diffuse.bmp", glm::vec3(100.0f, 0.001f, 100.f), glm::vec3(0.0f, 1.0f, 0.0f));
	floor->setShader(m_lightingSh);
	floor->setTag("floor");
	floor->m_shapeComp->setRotation(1.0f, 0.0f, 0.0f);
	floor->m_shapeComp->setShine(5);

	GameObject *sphere = new GameObject(glm::vec3(8.0f, 5.0f, 0.0f));
	sphere->addSphereShape("Image1.bmp", 2.0f);
	sphere->addPhysics("ball", 2.0f, 0.9f);
	sphere->setShader(m_lightingSh);

	GameObject *sphere2 = new GameObject(glm::vec3(-10.0f, 30.0f, 1.0f));
	sphere2->addSphereShape("Image1.bmp", 2.0f);
	sphere2->addPhysics("ball2", 2.0f, 0.2f);
	sphere2->addAdvancedPhysics("sphere", sphere2->m_shapeComp->getScale(), sphere2->m_rb->getMass());
	sphere2->setShader(m_lightingSh);

	m_room1 = createRoom(100.0f, 100.0f, 100.0f, glm::vec3(100.0f, 50.0f, 100.0f));

	//Curuthers has a size of (roughly) 2.8/5/2.5. 
	GameObject *cat = new GameObject(glm::vec3(20.0f, 20.0f, 10.0f));
	cat->addMeshShape("curuthers_diffuse.png", "curuthers.obj", glm::vec3(1.0f, 0.5f, 1.0f), glm::vec3(2.8f, 5.0f, 2.5f), "cat");
	cat->addPhysics("cat", 1.0f, 0.1f);
	cat->setShader(m_lightingSh);

	GameObject *hand = new GameObject(glm::vec3(0.0f, 0.0f, 0.0f));
	hand->addMeshShape("HAND_C.jpg", "fist.obj", glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(2.0f, 1.0f, 1.0f), "hand");
	hand->setShader(m_simpleSh);
	hand->m_shapeComp->setSolid(false);

	GameObject *box = new GameObject(glm::vec3(5.0f, 10.0f, 15.0f));
	box->addBoxShape("red.png", glm::vec3(10.0f, 5.0f, 10.0f));
	box->setTag("box");
	box->addPhysics("boxio", 2.0f, 0.1f);
	box->setShader(m_lightingSh);

	GameObject *box2 = new GameObject(glm::vec3(7.0f, 30.0f, 12.0f));
	box2->addBoxShape("Image1.bmp", glm::vec3(10.0f, 5.0f, 10.0f));
	box2->addPhysics("boxio2", 2.0f, 0.4f);
	box2->setShader(m_lightingSh);

	GameObject *hand2 = new GameObject(glm::vec3(0.0f, 0.0f, 0.0f));
	hand2->addMeshShape("gun.png", "gun.obj", glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(2.0f, 1.0f, 1.0f), "hand2");
	hand2->setShader(m_simpleSh);
	hand2->m_shapeComp->setSolid(false);


	
	m_object.push_back(shape);

	//objects.push_back(sphere);
	m_object.push_back(sphere2);
	m_object.push_back(cat);
	m_object.push_back(box);
	m_object.push_back(lightBulb);
	m_object.push_back(hand);
	m_object.push_back(hand2);
	m_object.push_back(box2);
	m_object.push_back(floor);

	//Lights
	PointLight *bulb = new PointLight(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.6f, 50.0f, 0.032f);
	DirLight *sun = new DirLight(glm::vec3(0.0f, 0.0f, 0.0f), 0.4f, glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0.2f, -1.0f, 0.0f));
	SpotLight *lamp = new SpotLight(glm::vec3(-25.0f, 20.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), 0.8f, 20.0f, 40.0f, 100.0f, 0.0075f, glm::vec3(0.0f, -1.0f, 0.0f));
	SpotLight *lamp2 = new SpotLight(glm::vec3(25.0f, 20.0f, 0.0f), glm::vec3(1.0f, 0.0f, 1.0f), 0.8f, 20.0f, 40.0f, 100.0f, 0.0075f, glm::vec3(0.0f, -1.0f, 0.0f));
	SpotLight *blotch = new SpotLight(glm::vec3(25.0f, 20.0f, 0.0f), glm::vec3(-1.0f, -1.0f, -1.0f), 0.8f, 10.0f, 20.0f, 100.0f, 0.0075f, glm::vec3(0.0f, -1.0f, 0.0f));
	blotch->m_antiLight = 1;

	m_pLight.push_back(bulb);

	m_dLight.push_back(sun);

	m_sLight.push_back(lamp);
	m_sLight.push_back(lamp2);
	m_sLight.push_back(blotch);
}

void Scene::update(float _dT)
{
	///Camera				
	m_mainCam->update(_dT, m_input); // Update camera based on the input
	m_simpleSh->setUniform("in_Projection", glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f)); //Set the projection uniform
	m_lightingSh->setUniform("in_Projection", glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f)); //Set the projection uniform
	m_uiSh->setUniform("in_Orthographic", glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT, 0.0f, 1.0f)); //Set the Orthographic uniform
	glm::mat4 model(1.0f);
	model = glm::lookAt(m_mainCam->getPos(), m_mainCam->getPos() + m_mainCam->getFwd(), m_mainCam->getUp());

	m_simpleSh->setUniform("in_View", model); // Establish the view matrix		
	m_lightingSh->setUniform("in_View", model); // Establish the view matrix

	//Make various per-frame changes
	

	//Lighting Shaders
	m_lightingSh->setUniform("in_Emissive", glm::vec3(0.0f, 0.0f, 0.0f));

	m_lightingSh->setUniform("in_CamPos", m_mainCam->getPos());

	utility::updateLighting(m_sLight, m_dLight, m_pLight, m_lightingSh);

	

	///Objects				
	for (int o = 0; o < m_object.size(); o++) // Check every object
	{
		if (m_object[o]->getShape() != "NO SHAPE") // Don't bother updating objects with no collider or mesh
		{
			if (m_object[o]->isPhysics())
			{
				if (m_object[o]->m_rb->collided()) // Checks for any objects that collided during their update earlier
				{
					// Always handle collisions BEFORE updating physics positions because this function adjusts velocity due to response
					Physics::handleCollisions(m_object[o]);
				}
			}

			//lightingSh->setUniform("in_Mod", objects[o]->m_shapeComp->getModel());
			m_lightingSh->setUniform("in_Shininess", (int)pow(2, m_object[o]->m_shapeComp->getShine()));
			utility::update(m_object[o], m_object[o]->getShader(), m_object, _dT); // Update the object's model matrix and appearance, and its physical location				
			m_object[o]->getShader()->draw(m_object[o]->m_shapeComp->m_vAO); // Draw the object to the screen using its own shader
		}
	}

	//for (int o = 0; o < m_room1->m_walls.size(); o++) // Check every object in the room
	//{
	//	m_lightingSh->setUniform("in_Shininess", (int)pow(2, m_room1->m_walls[o]->m_shapeComp->getShine()));
	//	utility::update(m_room1->m_walls[o], m_room1->m_walls[o]->getShader(), m_room1->m_walls, _dT); // Update the object's model matrix and appearance, and its physical location				
	//	m_room1->m_walls[o]->getShader()->draw(m_room1->m_walls[o]->m_shapeComp->m_vAO); // Draw the object to the screen using its own shader
	//}
	
}




//https://sketchfab.com/models/ed37306f40c547c1a179587665b54286?cursor=cD0yMDE3LTA3LTI3KzIyJTNBMDAlM0E1Mi44MDkxNDM%3D // Wyrm model
	//https://sketchfab.com/models/ab12bf5debaf482db6456326e2799969?ref=related // Snake Man
		// https://sketchfab.com/models/f2b2894395864d49b12ca0065f30ade2?ref=related#download // Cthulhu Statue
		// https://free3d.com/3d-model/hand-v2--144793.html // Hand(s)
		// https://free3d.com/3d-model/rigged-hands-28855.html Hand texture
		// https://www.turbosquid.com/FullPreview/Index.cfm/ID/1082345//  Gun