#include "ShaderManager.h"

std::map<std::string, Shader> ShaderManager::Shaders;

Shader ShaderManager::LoadShader(const char* vShaderFile, const char* fShaderFile, std::string name)
{
    Shaders[name] = LoadShaderFromFile(vShaderFile, fShaderFile);
    return Shaders[name];
}

Shader ShaderManager::GetShader(std::string name)
{
    return Shaders[name];
}

void ShaderManager::Clear()
{
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
}

Shader ShaderManager::LoadShaderFromFile(const char* vShaderFile, const char* fShaderFile)
{
    std::string vertexCode;
    std::string fragmentCode;
    try
    {
        // Open Files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;

        // Read files buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

        // Close handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();

        // Conver stream to string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::exception e)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    Shader shader;
    shader.Compile(vShaderCode, fShaderCode);

    return shader;
}
