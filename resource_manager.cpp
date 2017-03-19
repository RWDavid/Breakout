#include "resource_manager.h"

#include <SOIL.h>
#include <iostream>
#include <fstream>
#include <sstream>

// Instantiate static variables
std::map<std::string, Texture2D>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;

// Generate a shader
Shader ResourceManager::LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name)
{
	Shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return Shaders[name];
}

// Retrieves a shader
Shader ResourceManager::GetShader(std::string name)
{
	return Shaders[name];
}

// Generates a texture
Texture2D ResourceManager::LoadTexture(const GLchar *file, GLboolean alpha, std::string name)
{
	Textures[name] = loadTextureFromFile(file, alpha);
	return Textures[name];
}

// Retrieves a texture
Texture2D ResourceManager::GetTexture(std::string name)
{
	return Textures[name];
}

// De-allocates all loaded resources
void ResourceManager::Clear()
{
	for (auto iter : Shaders)
	{
		glDeleteProgram(iter.second.ID);
	}
	for (auto iter : Textures)
	{
		glDeleteTextures(1, &iter.second.ID);
	}
}

// Loads and generates a shader from a file
Shader ResourceManager::loadShaderFromFile(const GLchar *vShaderFile, const GLchar* fShaderFile, const GLchar* gShaderFile)
{
	std::string vertexCode, fragmentCode, geometryCode;

	try
	{
		std::ifstream vertexShaderFile(vShaderFile), fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;

		// Buffer file data into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();

		// Close files
		vertexShaderFile.close();
		fragmentShaderFile.close();

		// Convert stream data into strings
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

		// Also read geometry shader file if geometry path is not a nullptr
		if (gShaderFile != nullptr)
		{
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}

	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}

	const GLchar *vShaderCode = vertexCode.c_str();
	const GLchar *fShaderCode = fragmentCode.c_str();
	const GLchar *gShaderCode = geometryCode.c_str();

	// Create and return a shader with file data
	Shader shader;
	shader.Compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);
	return shader;
}

// Loads a single texture from file
Texture2D ResourceManager::loadTextureFromFile(const GLchar *file, GLboolean alpha)
{
	// Create Texture object
	Texture2D texture;
	if (alpha)
	{
		texture.Internal_Format = GL_RGBA;
		texture.Image_Format = GL_RGBA;
	}
	// Load image
	int width, height;
	unsigned char* image = SOIL_load_image(file, &width, &height, 0, texture.Image_Format == GL_RGBA ? SOIL_LOAD_RGBA : SOIL_LOAD_RGB);

	// Generate texture
	texture.Generate(width, height, image);

	// Free image data
	SOIL_free_image_data(image);
	return texture;
}