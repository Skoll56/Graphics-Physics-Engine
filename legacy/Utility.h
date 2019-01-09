#ifndef _UTILITY_H_
#define _UTILITY_H_
#include <vector>
#include <string>

class GameObject;
class Shader;
class SpotLight;
class DirLight;
class PointLight;
class Camera;
class Scene;


namespace utility
{
	void onEveryFrame(Scene* _scene, float _dT);
	void update(GameObject* _obj, Shader* _shader, std::vector<GameObject*> _allObj, float _dT);
	void updateLighting(std::vector<SpotLight*> _sLight, std::vector<DirLight*> _dLight, std::vector<PointLight*> _pLight, Shader *lSh);
	GameObject* copy(GameObject* _obj);
	float lerp(float _a, float _b, float _f); //Reference Alex
}



#endif