#include "GameObject.h"




class Physics
{
public:
	Physics(float _gravity) { m_gravity = _gravity; }

	void update(GameObject* _my, std::vector<GameObject*> _other, float _dT);
	bool collide(float _dT, std::vector<GameObject*> _other, GameObject * _my, glm::vec3 _c1);
	void handleCollisions(GameObject* _object);
	
	
	

private:
	float m_gravity;
	
};

