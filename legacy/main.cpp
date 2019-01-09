#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <exception>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "stb_image.h"
#include "Input.h"
#include "Scene.h"
#include "Utility.h"

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 600

SDL_Window* initialise();


int main(int argc, char *argv[])
{
	SDL_Window *window = initialise();
	Scene* scene = new Scene;
	scene->createStartScene();
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
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Set the active texture buffer
		glActiveTexture(GL_TEXTURE0 + 1);
		
		scene->update(dTime);
		utility::onEveryFrame(scene, dTime);
		
		SDL_GL_SwapWindow(window);
		quit = scene->getInput()->takeInput(event); //Handles the input, and returns a 'quit' value to see if the program should end

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