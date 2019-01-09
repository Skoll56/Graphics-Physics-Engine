#include <vector>
#include <glm/glm.hpp>
#include "GameObject.h"
#include "Room.h"
class GameObject;
class SpotLight;
class DirLight;
class PointLight;
class Camera;
class Shader;
class Input;
//class Room;

class Scene
{
public:
	Scene();
	std::vector<GameObject*> getObjects() { return m_object; }
	Camera* getCam() { return m_mainCam; }
	Input* getInput() { return m_input; }

	void addSpotLight(SpotLight* _light) { m_sLight.push_back(_light); }
	void adDirLight(DirLight* _light) { m_dLight.push_back(_light); }
	void addPointLight(PointLight* _light) { m_pLight.push_back(_light); }
	void addCamera(Camera* _cam) { m_camera.push_back(_cam); }
	std::vector<PointLight*> getpLight() { return m_pLight; }
	Room* createRoom(float _x, float _y, float _z, glm::vec3 _pos);
	Room* createRoom(float _x, float _y, float _z, int _NESW, Room* _prev);
	void createStartScene();
	void update(float _dT);


	Shader* m_simpleSh;
	Shader* m_lightingSh;
	Shader* m_uiSh;
	Room* m_room1;
	

private:
	std::vector<GameObject*> m_object;
	std::vector<Camera*> m_camera;
	std::vector<SpotLight*> m_sLight;
	std::vector<DirLight*> m_dLight;
	std::vector<PointLight*> m_pLight;
	GameObject* m_templateWall;
	Camera* m_mainCam;
	Input* m_input;
};
