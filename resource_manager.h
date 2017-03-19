#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#define GLEW_STATIC
#include <GL/glew.h>
#include <map>
#include <string>

#include "shader.h"
#include "texture.h"

// ResourceManager is a static class in which its functions / members can be accessed from outside the class

class ResourceManager
{
public:
	// Shader resource storage: Each member of the storage has a name and a shader (which can be accessed by the name)
	static std::map<std::string, Shader> Shaders;

	// Texture resource storage: Each member of the storage has a name and a texture (which can be accessed by the name)
	static std::map<std::string, Texture2D> Textures;

	/* Generates a shader:
	 * vShaderFile - vertex shader data (provide a file directory)
	 * fShaderFile - fragment shader data
	 * gShaderFile - geometry shader data (if gShaderFile is not a null pointer, it will also create a geometry shader)
	 * name - string to be stored as the name; used to access the shader
	 */
	static Shader LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);

	// Retrieves a stored shader through its name
	static Shader GetShader(std::string name);

	/* Generates a texture:
	 * file - image directory / filename
	 * alpha - determines if internal format & image format should include alpha value (RGBA)
	 * name - string to be stored as the name; used to access the texture
	 */
	static Texture2D LoadTexture(const GLchar *file, GLboolean alpha, std::string name);

	// Retrieves a stored texture through its name
	static Texture2D GetTexture(std::string name);

	// De-allocates all loaded resources
	static void Clear();

private:
	// Private constructor; constructor should not be called within the class nor externally
	// Its members and functions are available publicly
	ResourceManager() { }

	// Loads and generates a shader from a file
	static Shader    loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);

	// Loads a single texture from file
	static Texture2D loadTextureFromFile(const GLchar *file, GLboolean alpha);
};
#endif