#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"

class SpriteRenderer
{
public:
	// Constructor - takes a shader
	SpriteRenderer(Shader &shader);

	// Destructor
	~SpriteRenderer();

	/* Renders a defined quadrilateral textured with given sprite:
	 * texture - Texture object containing the image for the sprite
	 * position - a size 2 vector in the form of (x, y) (x increases to the right; y increases downward; (0, 0) = top left corner of window)
	 * size - a size 2 vector in the form of (x, y) used in component-wise scaling (x is the scale amount for the width; y is for the height)
	 * rotate - a GLfloat value used to rotate the sprite clockwise by a certain number of degrees
	 * color - a size 3 vector (RGB) (leave to default if no color modification is wanted)
	 */
	void DrawSprite(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

private:
	// Render state
	Shader shader;
	GLuint quadVAO;

	// Initializes and configures the quad's buffer and vertex attributes
	void initRenderData();
};

#endif