
#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include "GameObject.h"
#include "Collision.h"
#include "Shader.h"
#include "Physics.h"
#include "Utility.h"
#include "Light.h"
#include "VertexArray.h"
#include "Camera.h"
#include "VertexBuffer.h"
#include "Input.h"
#include "Scene.h"
#define SHAPE(type) _obj->getShape() == type
#define OUTPUT(vec) std::cout << vec.x << " " << vec.y << " " << vec.z <<std::endl;
#define TAG(tag) obj[i]->getTag() == tag


namespace utility
{
	void onEveryFrame(Scene* _scene, float _dT) // This function runs every frame. Add various 'per frame' interactions here.
	{
		GameObject* hand = nullptr;
		GameObject* hand2 = nullptr;
		GameObject* cat = new GameObject();
		Input* input = _scene->getInput();
		Camera* camera = _scene->getCam();

		std::vector<GameObject*> obj = _scene->getObjects();

		for (int i = 0; i < obj.size(); i++) // Cycles through every object. You can access individual objects from its tag.
		{
			if (TAG("hand"))
			{
				hand = obj[i];
				hand->setPosition(camera->getPos()   + (camera->getFwd() * 2.0f) + (camera->getRight() * 1.0f));
				float turn;
				if (camera->getYaw() > 0.0f)
				{
					turn = 540.0f - camera->getYaw();
				}
				else
				{
					turn = 180.0f + -camera->getYaw();
				}
				glm::vec3 rot = hand->m_shapeComp->getRot();
				hand->m_shapeComp->setRotation(glm::vec3(rot.x, turn, rot.z));				
			}

			else if (TAG("bulb"))
			{
				obj[i]->setPosition(_scene->getpLight()[0]->m_pos);
			}

			else if (TAG("ball2"))
			{
				
			}


			else if (TAG("hand2"))
			{
				hand2 = obj[i];
				hand2->setPosition((camera->getPos() - glm::vec3(0.0f, 1.7f, 0.0f)) + (camera->getFwd() * 2.0f) - (camera->getRight() * 1.1f));
				float turn;
				if (camera->getYaw() > 0.0f)
				{
					turn = 540.0f - camera->getYaw();
				}
				else
				{
					turn = 180.0f + -camera->getYaw();
				}
				hand2->m_shapeComp->setRotation(glm::vec3(0.0f, turn + 180.0f, 0.0f));
			}

			else if (TAG("cat"))
			{
				cat = obj[i];
				OUTPUT(cat->m_rb->getVelocity());

				glm::vec3 direction = glm::vec3(0, 0, 0);

				if (input->m_left)
				{
					direction.x -= 1;
				}
				if (input->m_right)
				{
					direction.x += 1;
				}
				if (input->m_up)
				{
					direction.z += 1;
				}
				if (input->m_down)
				{
					direction.z -= 1;
				}
				float vely = cat->m_rb->getVelocity().y;
				

				glm::vec3 force = cat->m_rb->getForce();
				if(input->m_asc && cat->m_rb->isFloored() && force.y < 0.1f)
				{
					
				}

				glm::mat4 temp(1.0f);
				temp = glm::rotate(temp, glm::radians(-camera->getYaw()), glm::vec3(0, 1, 0));
				glm::vec3 directionFix;
				directionFix.z = direction.x;
				directionFix.x = direction.z;
				directionFix.y = direction.y;
				temp = glm::translate(temp, directionFix);
				glm::vec3 dir = temp * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
				if (dir != glm::vec3(0, 0, 0))
				{
					dir = glm::normalize(dir);
				}
				dir.y = 0.0f;
				cat->m_rb->setVelocity(dir * 10.0f);
				cat->m_rb->addVelocity(glm::vec3(0.0f, vely, 0.0f));
			}
			camera->setPos(cat->getPosition() + glm::vec3(0.0f, 5.0f, 0.0f)); //+(camera->getFwd() * glm::vec3(0.0f, 0.0f, -5.0f)));
		}
	}


	void update(GameObject* _obj, Shader* _shader, std::vector<GameObject*> _allObj, float _dT)
	{
		glm::mat4 modelMat(1.0f); // Model Matrix
		modelMat = glm::translate(modelMat, _obj->getPosition()); // Translate by game object's position
		if (_obj->isAdvancedPhysics())
		{
			glm::mat4 rotationMat = glm::mat4(_obj->m_Phy->getRotMat()); //Reference whoever Alex got this from
			glm::quat rotate = glm::normalize(glm::quat_cast(rotationMat));
			_obj->m_Phy->setRotMat(glm::mat3_cast(rotate));

			modelMat *= glm::mat4_cast(rotate);
		}
		
		else
		{
			glm::vec3 rotation = glm::radians(_obj->m_shapeComp->getRot());
			float rotSum = rotation.x + rotation.y + rotation.z;
			{
				modelMat = glm::rotate(modelMat, rotation.x, glm::vec3(1, 0, 0)); //Rotate by the shape component's rotation
				modelMat = glm::rotate(modelMat, rotation.y, glm::vec3(0, 1, 0));
				modelMat = glm::rotate(modelMat, rotation.z, glm::vec3(0, 0, 1));
			}
		}
		modelMat = glm::scale(modelMat, _obj->m_shapeComp->getScale()); // Scale by shape object's scale

		_obj->m_shapeComp->setModel(modelMat); // Send the model matrix back to the shape component to be drawn	
		
		_shader->setUniform("in_Model", _obj->m_shapeComp->getModel()); // Translate the model matrix by camera position and stuff
		_shader->setUniform("in_Texture", _obj->m_shapeComp->m_tex);

		if (_obj->isPhysics()) 
		{
			Physics::update(_obj, _allObj, _dT); // Also update the shape's rigidbody if it has one. Checks for collisions and adjusts position
		}

	}

	void updateLighting(std::vector<SpotLight*> _sLight, std::vector<DirLight*> _dLight, std::vector<PointLight*> _pLight, Shader *_lSh)
	{
		std::string uniform;
		for (int i = 0; i < _pLight.size(); i++)
		{
			std::string itr = std::to_string(i);
			 uniform = "in_pLight[" + itr + "].m_specIntens";
			_lSh->setUniform(uniform, _pLight[i]->getSpec());

			uniform = "in_pLight[" + itr + "].m_diffuse";
			_lSh->setUniform(uniform, _pLight[i]->getDif());

			uniform = "in_pLight[" + itr + "].m_pos";
			_lSh->setUniform(uniform, _pLight[i]->getPos());

			uniform = "in_pLight[" + itr + "].m_radius";
			_lSh->setUniform(uniform, _pLight[i]->getRadius());

			uniform = "in_pLight[" + itr + "].m_quadratic";
			_lSh->setUniform(uniform, _pLight[i]->getQuad());

		}	
		
		for (int i = 0; i < _dLight.size(); i++)
		{				
			std::string itr = std::to_string(i);
			uniform = "in_dLight[" + itr + "].m_specIntens";
			float t = _dLight[i]->getSpec();
			_lSh->setUniform(uniform, _dLight[i]->getSpec());

			uniform = "in_dLight[" + itr + "].m_diffuse";
			_lSh->setUniform(uniform, _dLight[i]->getDif());
			
			uniform = "in_dLight[" + itr + "].m_ambient";
			_lSh->setUniform(uniform, _dLight[i]->getAmb());

			uniform = "in_dLight[" + itr + "].m_direction";
			_lSh->setUniform(uniform, _dLight[i]->getDirection());
		}	
			
		for (int i = 0; i < _sLight.size(); i++)
		{	
			std::string itr = std::to_string(i);
			uniform = "in_sLight[" + itr + "].m_specIntens";
			_lSh->setUniform(uniform, _sLight[i]->getSpec());

			uniform = "in_sLight[" + itr + "].m_diffuse";
			_lSh->setUniform(uniform, _sLight[i]->getDif());

			uniform = "in_sLight[" + itr + "].m_pos";
			_lSh->setUniform(uniform, _sLight[i]->getPos());

			uniform = "in_sLight[" + itr + "].m_radius";
			_lSh->setUniform(uniform, _sLight[i]->getRadius());

			uniform = "in_sLight[" + itr + "].m_quadratic";
			_lSh->setUniform(uniform, _sLight[i]->getQuad());
			
			uniform = "in_sLight[" + itr + "].m_angle";
			_lSh->setUniform(uniform, glm::cos(glm::radians(_sLight[i]->getAngle())));

			uniform = "in_sLight[" + itr + "].m_fadeAngle";
			_lSh->setUniform(uniform, glm::cos(glm::radians(_sLight[i]->getFangle())));

			uniform = "in_sLight[" + itr + "].m_direction";
			_lSh->setUniform(uniform, _sLight[i]->getDirection());

			uniform = "in_sLight[" + itr + "].m_antiLight";
			_lSh->setUniform(uniform, _sLight[i]->m_antiLight);		
		}
	}

	
	GameObject * copy(GameObject * _obj)
	{
		GameObject* t = new GameObject();
		
		if (_obj->getShape() != "NO SHAPE")
		{			
			t->m_shapeComp = new Shape();
			*t->m_shapeComp = *_obj->m_shapeComp;
					
			if (SHAPE("sphere"))
			{
				t->m_sphere = new Sphere();
				*t->m_sphere = *_obj->m_sphere;
			}
			else if (SHAPE("plane"))
			{
				t->m_plane = new Plane();
				*t->m_plane = *_obj->m_plane;
			}
			else if (SHAPE("mesh"))
			{
				t->m_mesh = new Mesh();
				*t->m_mesh = *_obj->m_mesh;
			}
			else if (SHAPE("box"))
			{
				t->m_box = new Box();
				*t->m_box = *_obj->m_box;
			}
			if (_obj->isPhysics())
			{
				t->m_rb = new PhysicsObj();
				*t->m_rb = *_obj->m_rb;
			}
			if (_obj->isAdvancedPhysics())
			{
				t->m_Phy = new AdvancedPhysics();
				*t->m_Phy = *_obj->m_Phy;
			}
		}
		t->setShader(_obj->getShader());
		t->setPosition(_obj->getPosition());
		t->setTag(_obj->getTag() + "[copy]");
		t->setActive(_obj->isActive());
		t->setShapeString(_obj->getShape());
		t->setPhysBool(_obj->isPhysics());
		t->setAdPhysBool(_obj->isAdvancedPhysics());
		return t;
	}

	float lerp(float _a, float _b, float _f)
	{
		return _a + _f * (_b - _a);
	}
}

