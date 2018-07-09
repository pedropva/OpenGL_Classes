#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GLFW/glfw3.h>
extern GLFWwindow* window;
extern GLuint WIDTH, HEIGHT;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

// Initial position : on +Z
glm::vec3 position = glm::vec3(0, 0, 10);
//initial direction
glm::vec3 direction = glm::vec3(0, 0, 0);
//up vector
glm::vec3 up = glm::vec3(0, 1, 0);
//right vector
glm::vec3 rightVector = glm::vec3(1, 0, 0);
//object position which we will be orbiting around
glm::vec3 objectPosition = glm::vec3(0, 0, 0);
// Initial Field of View
float initialFoV = 45.0f;

//speed which we do each rotation
float zoomSpeed = 1.0f;
float rollSpeed = 0.5f;
float yawSpeed= 2.0f;
float pitchSpeed = 2.0f;
float keySpeed = 5.0f; 


GLfloat aspectRatio = (GLfloat)WIDTH / (GLfloat)HEIGHT;

mat4 ViewMatrix;
mat4 ProjectionMatrix;

mat4 getViewMatrix() {
	return ViewMatrix;
}

mat4 getProjectionMatrix() {
	return ProjectionMatrix;
}

glm::vec3 getUpVector() {
	return up;
}


void keyboardEventsCameraMove(float deltaTime) {
	// Roll Left
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		rightVector += up * deltaTime * keySpeed * rollSpeed;
	}
	// Roll Right
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		rightVector -= up * deltaTime * keySpeed * rollSpeed;
	}
	// Zoom in
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
		position += direction * deltaTime * keySpeed *zoomSpeed;
	}
	// Zoom out
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		position -= direction * deltaTime * keySpeed * zoomSpeed;
	}
	// Pitch UP
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position += up * deltaTime * keySpeed * pitchSpeed;
	}
	// Pitch Down	
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position -= up * deltaTime * keySpeed * pitchSpeed;
	}
	// Yaw right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position += rightVector * deltaTime * keySpeed * yawSpeed;
	}
	// Yaw left
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		position -= rightVector * deltaTime * keySpeed  * yawSpeed;
	}
}
void rotateCameraTransform(float angle, vec3 axis)
{
	//Concatenating operations;
	mat4 translate1 = translate(mat4(1.f), -position);
	mat4 rotateMat = rotate(translate1, radians(angle), axis);
	mat4 translate2 = translate(rotateMat, position);
	vec4 transformVec = translate2 * vec4(position, 1);

	//Defining the new camera position;
	position = vec3(transformVec);

	//If in target view mode, look at the origin, else look at the direction defined previously;
	ViewMatrix = lookAt(position,objectPosition, up);// position + direction
													 //model = mat4(1.0f);
													 //mvp = projection * view * model;

}

void computeMatricesFromInputs() {

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// View direction vector
	direction = normalize(position + objectPosition); //vec3(cos(verticalAngle) * sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle) * cos(horizontalAngle));
	//cout << "direction: " << direction.x << " and " << direction.y << " and " << direction.z << endl;

	// Rotate right
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		// Right vector
		rightVector = normalize(cross(up, direction));//vec3(-1, 0, 0);// vec3(sin(horizontalAngle - 3.14f / 2.0f), 0, cos(horizontalAngle - 3.14f / 2.0f));
	}
	// Up vector
	up = normalize(cross(-rightVector, direction));
	
	keyboardEventsCameraMove(deltaTime);

	float FoV = initialFoV;

	ProjectionMatrix = perspective(radians(FoV), aspectRatio, 0.1f, 100.0f);
	
	ViewMatrix = lookAt(position, objectPosition, up);// position + direction
	lastTime = currentTime;
}



#endif