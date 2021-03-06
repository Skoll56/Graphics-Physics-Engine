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


class Scene
{
public:
	Scene();
	std::vector<GameObject*> getObjects() { return m_object; }
	Camera* getCam() { return m_mainCam; }
	Input* getInput() { return m_input; }
	void setCam(Camera* _cam) { m_mainCam = _cam; }
	void addSpotLight(SpotLight* _light) { m_sLight.push_back(_light); }
	void adDirLight(DirLight* _light) { m_dLight.push_back(_light); }
	void addPointLight(PointLight* _light) { m_pLight.push_back(_light); }
	std::vector<PointLight*> getpLight() { return m_pLight; }
	std::vector<SpotLight*> getsLight() { return m_sLight; }
	void createRoom(float _x, float _y, float _z, glm::vec3 _pos);
	void createRoom(float _x, float _y, float _z, int _NESW, Room* _prev);
	void createStartScene();
	void update(float _dT);
	void addToRoom(GameObject* _obj, int _room);
	void setDeny(bool _val) { m_deny = _val; }
	bool isDenied() { return m_deny; }
	void addObj(GameObject* _obj) { m_object.push_back(_obj); }
	GameObject* getZter() { return m_templateZter; }
	GameObject* getHornet() { return m_templateHornet; }

	Shader* m_simpleSh;
	Shader* m_lightingSh;
	Shader* m_uiSh;
	Shader* m_monsterSh;
	Shader* m_invSh;
	

private:
	int m_roomNum;
	std::vector<GameObject*> m_object;
	std::vector<SpotLight*> m_sLight;
	std::vector<DirLight*> m_dLight;
	std::vector<PointLight*> m_pLight;
	std::vector<Room*> m_room;
	GameObject* m_templateWall;
	GameObject* m_templateZter;
	GameObject* m_templateHornet;
	Camera* m_mainCam;
	Input* m_input;
	bool m_deny;
};
