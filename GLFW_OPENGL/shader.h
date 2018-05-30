#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>

class Shader
{
public:
    GLuint Program;
    Shader( const GLchar *vertexPath, const GLchar *fragmentPath )
    {
        std::string vertexCode;
        std::string fragmentCode;
        std::ifstream vShaderFile;
        std::ifstream fShaderFile;
        vShaderFile.exceptions ( std::ifstream::badbit );
        fShaderFile.exceptions ( std::ifstream::badbit );
        try
        {
            // Opening files
            vShaderFile.open( vertexPath );
            fShaderFile.open( fragmentPath );
			if (!vShaderFile.is_open()) {
				std::cout << "Error,failed to open/find vertex shader file!\n" << std::endl;
			}
			if (!fShaderFile.is_open()) {
				std::cout << "Error,failed to open/find fragment shader file!\n" << std::endl;
			}
            std::stringstream vShaderStream, fShaderStream;
            // Read file's buffer contents into streams
            vShaderStream << vShaderFile.rdbuf( );
            fShaderStream << fShaderFile.rdbuf( );
            // close file handlers
            vShaderFile.close( );
            fShaderFile.close( );
            // Convert stream into string
            vertexCode = vShaderStream.str( );
            fragmentCode = fShaderStream.str( );
			//Print the shaders
			std::cout << "Vertex Shader file:" << std::endl << std::endl;
			std::cout << vertexCode << std::endl << std::endl;
			std::cout << "Fragment Shader file:" << std::endl << std::endl;;
			std::cout << fragmentCode << std::endl << std::endl;
        }
        catch ( std::ifstream::failure e )
        {
            std::cout << "Error,Shader file not successfully read!\n" << std::endl;
        }
        const GLchar *vShaderCode = vertexCode.c_str( );
        const GLchar *fShaderCode = fragmentCode.c_str( );
        //Compile shaders
        GLuint vertex, fragment;
        GLint success;
        GLchar infoLog[512];
        //Compile Vertex Shader
        vertex = glCreateShader( GL_VERTEX_SHADER );
        glShaderSource( vertex, 1, &vShaderCode, NULL );
        glCompileShader( vertex );
        // Print compile errors if any
        glGetShaderiv( vertex, GL_COMPILE_STATUS, &success );
        if ( !success )
        {
            glGetShaderInfoLog( vertex, 512, NULL, infoLog );
            std::cout << "Error,vertex shader compilation failed:\n" << infoLog << std::endl;
        }
        // Fragment Shader
        fragment = glCreateShader( GL_FRAGMENT_SHADER );
        glShaderSource( fragment, 1, &fShaderCode, NULL );
        glCompileShader( fragment );
        // Print compile errors if any
        glGetShaderiv( fragment, GL_COMPILE_STATUS, &success );
        if ( !success )
        {
            glGetShaderInfoLog( fragment, 512, NULL, infoLog );
            std::cout << "Error,fragment shader compilation failed:\n" << infoLog << std::endl;
        }
        // Shader Program
        this->Program = glCreateProgram( );
        glAttachShader( this->Program, vertex );
        glAttachShader( this->Program, fragment );
        glLinkProgram( this->Program );
        // Print linking errors if any
        glGetProgramiv( this->Program, GL_LINK_STATUS, &success );
        if (!success)
        {
            glGetProgramInfoLog( this->Program, 512, NULL, infoLog );
            std::cout << "Error,shader program linking failed:\n" << infoLog << std::endl;
        }
        // Delete the shaders as they're linked into our program now and no longer necessery
        glDeleteShader( vertex );
        glDeleteShader( fragment );
        
    }
    // Uses the current shader
    void Use( )
    {
        glUseProgram( this->Program );
    }
};

#endif
