#include <SDL2/SDL.h>

struct Input
{
	Input();
	bool takeInput(SDL_Event &_event);

	bool m_left, m_right, m_up, m_down, m_asc, m_desc, m_r1, m_r2, m_r, m_f;

};
