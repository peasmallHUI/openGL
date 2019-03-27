#include "Camera.h"



Camera::Camera(glm::vec3 _camPos, glm::vec3 _targPos, glm::vec3 _upDir):
	camPos (_camPos),camTarget(_targPos),upDir(_upDir),camSpeed(1.0f)
{
	camFront = glm::normalize(camPos - camTarget);
	camRight = glm::normalize(glm::cross(upDir, camFront));
	camUp = glm::normalize(glm::cross(camFront, camRight));
}

void Camera::keyPress(std::string direction, float deltatime)
{
	if (direction == "FORWARD")
		camPos += camSpeed * deltatime * camFront;
	if (direction == "BACKWARD")
		camPos -= camSpeed * deltatime * camFront;
	if (direction == "RIGHT")
		camPos -= camSpeed * deltatime * camRight;
	if (direction == "LEFT")
		camPos += camSpeed * deltatime * camRight;
}

glm::mat4 Camera::getView()
{
	return glm::lookAt(camPos, camPos + camFront, upDir);
}



Camera::~Camera()
{
}
