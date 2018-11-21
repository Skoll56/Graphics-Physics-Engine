#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <exception>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <time.h>
#include <iostream>
#include <fstream>
#include "Utility.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "stb_image.h"
#include "Texture.h"
#include "Camera.h"


#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

SDL_Window* initialise();
bool takeInput(SDL_Event &_event, Camera *_camera);

int main(int argc, char *argv[])
{
	SDL_Window *window = initialise();	

	Physics * physics = new Physics(-9.81f);
	Shader *shader = new Shader();
	Camera *camera = new Camera(glm::vec3(0, 0, 30), glm::vec3(0, 0, 0));

	std::vector<GameObject*> objects;
	//Spheres are size 1/1/1
	//Boxes are size 1/1/1
	//Planes are size 1/0/1
	//Meshes may vary. Mesh sizes are used to determine their hitbox (box collisions are always tested before the mesh collision for efficiency)


	GameObject *shape = new GameObject(glm::vec3(0.0f, 15.0f, 0.0f));
	shape->addSphereShape("image1.bmp", 5.0f);
	shape->addPhysics("testShape", 20.0f, 0.3f);

	GameObject *floor = new GameObject(glm::vec3(0.0f, 0.0f, 0.0f));
	floor->addPlaneShape("diffuse.bmp", glm::vec3(50.0f, 1.0f, 50.f), glm::vec3(0.0f, 1.0f, 0.0f ));	

	GameObject *sphere = new GameObject(glm::vec3(10.0f, 15.0f, 0.0f));
	sphere->addSphereShape("Image1.bmp", 2.0f);
	sphere->addPhysics("ball", 2.0f, 0.3f);

	//Curuthers has a size of (roughly) 2/4/2. 
	GameObject *cat = new GameObject(glm::vec3(0.0f, 5.0f, 5.0f));
	cat->addMeshShape("curuthers_diffuse.png", "curuthers.obj", glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(2.0f, 4.0f, 2.0f));

	GameObject *box = new GameObject(glm::vec3(-10.0f, 5.0f, 4.0f));
	box->addBoxShape("Image2.png", glm::vec3(2.0f, 2.0f, 2.0f));

	objects.push_back(shape);
	objects.push_back(floor);
	objects.push_back(sphere);
	objects.push_back(cat);
	objects.push_back(box);


	///VertexBuffer positions
	//shape->m_vBOp->add(glm::vec3(0.0f, 0.5f, 0.0f));
	//shape->m_vBOp->add(glm::vec3(-0.5f, -0.5f, 0.0f));
	//shape->m_vBOp->add(glm::vec3(0.5f, -0.5f, 0.0f));

	///VertexBuffer texCoords
	//shape->m_vBOt->add(glm::vec2(0.5f, 0.0f));
	//shape->m_vBOt->add(glm::vec2(0.0f, 1.0f));
	//shape->m_vBOt->add(glm::vec2(1.0f, 1.0f));	

	///VAO
	//shape->m_vAO->setBuffer("in_Position", shape->m_vBOp);
	//shape->m_vAO->setBuffer("in_TexCoord", shape->m_vBOt);


	int width, height;
	bool quit = false;
	long t1 = SDL_GetTicks();

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	
	
	while(!quit) // Game Loop
	{
		
		// Re-initialise per-frame variables
		float time = SDL_GetTicks();
		float dTime = (time - t1) / 1000.0f;
		t1 = time;
		SDL_Event event = {0};
	
		//Re-establish window-size to allow stretching and re-sizing
		SDL_GetWindowSize(window, &width, &height);
		glViewport(0, 0, width, height);

		//Set the clear-colour for the screen and clear it
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Set the active texture buffer
		glActiveTexture(GL_TEXTURE0 + 1);

		
		///Camera				
		shader->setUniform("in_Projection", glm::perspective(glm::radians(45.0f), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, 0.1f, 100.0f)); //Set the projection uniform
		glm::mat4 model(1.0f);		
		model = glm::translate(model, camera->getPos()); // Translate all objects based on the camera's position
		model = glm::rotate(model, glm::radians(camera->getRot()), glm::vec3(0, 1, 0)); //Translate by camera's rotation		
		shader->setUniform("in_View", glm::inverse(model)); // Establish the view matrix		
		
		///Objects
		for (int o = 0; o < objects.size(); o++) // Check every object
		{
			if (objects[o]->getShape() != "NO SHAPE") // Don't bother updating objects with no collider or mesh
			{
				utility::update(objects[o], shader, objects, physics, dTime); // Update the object's model matrix and appearance, and its physical location
				shader->draw(objects[o]->m_shapeComp->m_vAO); // Draw the object to the screen
			}
		}

		for (int o = 0; o < objects.size(); o++)
		{
			if (objects[o]->isPhysics())
			{
				if (objects[o]->m_rb->collided()) // Checks for any objects that collided during their update earlier
				{
					physics->handleCollisions(objects[o]); // Handles collision responses 
				}
			}
		}


		
		SDL_GL_SwapWindow(window);
		quit = takeInput(event, camera); //Handles the input, and returns a 'quit' value to see if the program should end
		
		
		camera->update(dTime); // Update camera based on the input
		

		float targetTime = 1.0f / 60.f;
		if (targetTime > dTime)
		{
			SDL_Delay((targetTime - dTime) * 1000.0f);
		}
	}

  SDL_DestroyWindow(window); // DESTROY THAT WINDOW. STRIKE IT DOWN. DEWIT.
  SDL_Quit();
  return 0;
}



bool takeInput(SDL_Event &_event, Camera *_camera) // The input handler / controller
{
	bool quit = false;
	while (SDL_PollEvent(&_event))
	{
		
		if (_event.type == SDL_QUIT)
		{
			quit = true;
		}

		else if (_event.type == SDL_KEYDOWN)
		{
			if (_event.key.keysym.sym == SDLK_a)
			{
				_camera->m_left = true;
			}
			if (_event.key.keysym.sym == SDLK_d)
			{
				_camera->m_right = true;
			}
			if (_event.key.keysym.sym == SDLK_w)
			{
				_camera->m_up = true;
			}
			if (_event.key.keysym.sym == SDLK_s)
			{
				_camera->m_down = true;
			}

			if (_event.key.keysym.sym == SDLK_SPACE)
			{
				_camera->m_asc = true;
			}

			if (_event.key.keysym.sym == SDLK_LSHIFT)
			{
				_camera->m_desc = true;
			}

			if (_event.key.keysym.sym == SDLK_q)
			{
				_camera->m_r1 = true;
			}
			if (_event.key.keysym.sym == SDLK_e)
			{
				_camera->m_r2 = true;
			}
		}

		else if (_event.type == SDL_KEYUP)
		{
			if (_event.key.keysym.sym == SDLK_a)
			{
				_camera->m_left = false;
			}
			if (_event.key.keysym.sym == SDLK_d)
			{
				_camera->m_right = false;
			}
			if (_event.key.keysym.sym == SDLK_w)
			{
				_camera->m_up = false;
			}
			if (_event.key.keysym.sym == SDLK_s)
			{
				_camera->m_down = false;
			}

			if (_event.key.keysym.sym == SDLK_SPACE)
			{
				_camera->m_asc = false;
			}

			if (_event.key.keysym.sym == SDLK_LSHIFT)
			{
				_camera->m_desc = false;
			}
			if (_event.key.keysym.sym == SDLK_q)
			{
				_camera->m_r1 = false;
			}
			if (_event.key.keysym.sym == SDLK_e)
			{
				_camera->m_r2 = false;
			}
		}

	}

	return quit;
}

SDL_Window* initialise() // Starts the window and initialises a lot of the SDL/GLEW stuff
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw std::exception();
	}

	SDL_Window *window = SDL_CreateWindow("Physics/Graphics Engine",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);

	if (!SDL_GL_CreateContext(window))
	{
		throw std::exception();
	}

	if (glewInit() != GLEW_OK)
	{
		throw std::exception();
	}
	

	return window;
}