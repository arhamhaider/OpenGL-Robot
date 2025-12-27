#include "InitShader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

std::string ReadFile(const char* path)
{
    std::ifstream in(path);
    if (!in.is_open()) {
        std::cerr << "Cannot open shader file: " << path << "\n";
        std::exit(EXIT_FAILURE);
    }
    std::stringstream ss;
    ss << in.rdbuf();
    return ss.str();
}

static GLuint CompileOne(GLenum type, const char* src, const char* label)
{
    GLuint sh = glCreateShader(type);
    glShaderSource(sh, 1, &src, nullptr);
    glCompileShader(sh);

    GLint ok;
    glGetShaderiv(sh, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[1024];
        glGetShaderInfoLog(sh, 1024, nullptr, log);
        std::cerr << "Shader compile error in " << label << ":\n" << log << "\n";
        std::exit(EXIT_FAILURE);
    }
    return sh;
}

GLuint InitShader(const char* vShaderFile, const char* fShaderFile)
{
    std::string vsrc = ReadFile(vShaderFile);
    std::string fsrc = ReadFile(fShaderFile);

    GLuint vs = CompileOne(GL_VERTEX_SHADER,   vsrc.c_str(), vShaderFile);
    GLuint fs = CompileOne(GL_FRAGMENT_SHADER, fsrc.c_str(), fShaderFile);

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);

    GLint linked;
    glGetProgramiv(prog, GL_LINK_STATUS, &linked);
    if (!linked) {
        char log[1024];
        glGetProgramInfoLog(prog, 1024, nullptr, log);
        std::cerr << "Program link error:\n" << log << "\n";
        std::exit(EXIT_FAILURE);
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
    return prog;
}
