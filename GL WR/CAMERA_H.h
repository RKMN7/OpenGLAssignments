#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Cam_Dir
{
	Forward,
	Backward,
	Left,
	Right,
	Up,
	Down
};

const float YAW=-90.0f;
const float PITCH=0.0f;
const float SENSITIVITY=0.04f;
const float SPEED=0.1f;
const float ZOOM=100.0f;

class Camera
{
public:
	glm::vec3 pos, front, up, right, upW;
	float yaw, pitch, speed, sensitivity, zoom;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3 U = glm::vec3(0.0f, 1.0f, 0.0f), float Y = YAW, float P = PITCH) : front(glm::vec3(0.0f, 0.0f, -1.0f)), speed(SPEED), sensitivity(SENSITIVITY), zoom(ZOOM)
    {
        pos = position;
        upW = U;
        yaw = Y;
        pitch = P;
        updateCamV();
    }

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float Y, float P) : front(glm::vec3(0.0f, 0.0f, -1.0f)), speed(SPEED), sensitivity(SENSITIVITY), zoom(ZOOM)
    {
        pos = glm::vec3(posX, posY, posZ);
        upW = glm::vec3(upX, upY, upZ);
        yaw = Y;
        pitch = P;
        updateCamV();
    }

	glm::mat4 GetCam()
	{
		return glm::lookAt(pos, pos+front, up);
	}

	void Key(Cam_Dir way)
	{
		if(way==Forward)
			pos+=speed*front;
		if(way==Backward)
			pos-=speed*front;
		if(way==Left)
			pos-=speed*right;
		if(way==Right)
			pos+=speed*right;
		if(way==Up)
			pos+=speed*upW;
		if(way==Down)
			pos-=speed*upW;
	}

	void Mouse(float xD, float yD)
	{
		xD*=sensitivity;
		yD*=sensitivity;

		yaw += xD;
		pitch += yD;
		if(pitch > 85.0f)
			pitch = 85.0f;
		if(pitch < -85.0f)
			pitch = -85.0f;

		updateCamV();
	}

	void Scroll(float yoffset)
	{
		if (zoom >= 1.0f && zoom <= 120.f)
            zoom -= yoffset;
        if (zoom <= 1.0f)
            zoom = 1.0f;
        if (zoom >= 120.f)
            zoom = 120.f;
	}

private:
	void updateCamV()
	{
		glm::vec3 see;
		see.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		see.y = sin(glm::radians(pitch));
		see.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(see);

		right=glm::normalize(glm::cross(front, upW));
		up=glm::normalize(glm::cross(right, front));
	}
};
#endif