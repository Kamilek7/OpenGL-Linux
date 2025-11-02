#include "camera.h"

Camera::Camera(glm::vec3 position)
{
    this->position = position;
}

void Camera::matrix(float FOVdeg, float nearPlane, float farPlane, Shaders& shader, const char* uniform, int width, int height)
{
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 proj = glm::mat4(1.0f);

    view = glm::lookAt(position, position+orientation, up);
    proj = glm::perspective(glm::radians(FOVdeg), (float)(width)/float(height), nearPlane, farPlane);

    glUniformMatrix4fv(glGetUniformLocation(shader.getID(), uniform), 1, GL_FALSE, glm::value_ptr(proj*view));

}

void Camera::inputs(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += speed*orientation;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= speed*glm::normalize(glm::cross(orientation, up));
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= speed*orientation;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += speed*glm::normalize(glm::cross(orientation, up));


    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        position += speed*up;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        position -= speed*up;



}