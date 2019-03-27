#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

class Camera
{
public:

	glm::vec3 camPos;
	glm::vec3 camTarget;
	glm::vec3 upDir;
	glm::vec3 camRight;
	glm::vec3 camFront;
	glm::vec3 camUp;
	float camSpeed;

	Camera(glm::vec3 _camPos, glm::vec3 _targPos, glm::vec3 _upDir );
	void keyPress(std::string direction, float deltetime);
	glm::mat4 getView();

	~Camera();
};

