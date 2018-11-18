#include <glm/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "Shapes.h"
#include "Shader.h"
#include "Physics.h"

namespace utility
{
	float distanceToPlane(glm::vec3 &n, glm::vec3 &p, glm::vec3 &q);

	
	float* CrossProduct(float *a, float *b);

	bool sphereToPlane(Sphere *_my, Plane *_plane, glm::vec3 _c1);
	bool sphereToSphere(Sphere *_my, Sphere *_sphere, glm::vec3 _c1);
	
	bool boxToSphere(Box *_my, Sphere *_sphere, glm::vec3 _c1);

	bool boxToBox(Box *_my, Box* _box, glm::vec3 _c1);
	bool boxToPlane(Box *_my, Plane * _plane, glm::vec3 _c1);
	

	void update(GameObject* _obj, Shader* _shader, std::vector<GameObject*> _allObj, Physics *_physics, float _dT);


	int coplanar_tri_tri(float N[3], float V0[3], float V1[3], float V2[3],
		float U0[3], float U1[3], float U2[3]);

	int NoDivTriTriIsect(float V0[3], float V1[3], float V2[3],
		float U0[3], float U1[3], float U2[3]);

	int triBoxOverlap(float boxcenter[3], 
		       float boxhalfsize[3],float triverts[3][3]);

	int planeBoxOverlap(float normal[3], float d, float maxbox[3]);
}
