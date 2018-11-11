#include <glm/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "GameObject.h"

namespace utility
{
	float distanceToPlane(glm::vec3 &n, glm::vec3 &p, glm::vec3 &q);

	bool sphereToPlane(glm::vec3 &c0, glm::vec3 &c1, float r, glm::vec3 &ci, glm::vec3 &_permCP, GameObject *_plane);

	bool sphereToSphere(glm::vec3 &c0, glm::vec3 &c1, float r1, float r2, glm::vec3 &cp, glm::vec3 &sN);

	bool boxToBox(GameObject *_box, glm::vec3 _pos, glm::vec3 _scale);

	int coplanar_tri_tri(float N[3], float V0[3], float V1[3], float V2[3],
		float U0[3], float U1[3], float U2[3]);

	int NoDivTriTriIsect(float V0[3], float V1[3], float V2[3],
		float U0[3], float U1[3], float U2[3]);
}
