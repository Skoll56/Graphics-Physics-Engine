#include <vector>

class PointLight;
class GameObject;


struct Corridor
{
	std::vector<GameObject*> m_walls;
	std::vector<GameObject*> m_lamp;
	std::vector<PointLight*> m_light;
};

struct Room
{
	glm::vec3 m_pos;
	int m_id;
	std::vector<GameObject*> m_walls;
	GameObject* m_inDoor;
	GameObject* m_outDoor;
	std::vector<GameObject*> m_lamp;
	std::vector<PointLight*> m_light;
	Corridor* m_exit;
};


