#ifndef SHADER_HPP
#define SHADER_HPP

class Shader{
    public:
    GLuint Program;

    Shader(const char* vertexPath, const char* fragmentPath) {
        string vertexCode;
        string fragmentCode;
        ifstream vShaderFile;
        ifstream fShaderFile;
        vShaderFile.exceptions(ifstream::failbit);
        fShaderFile.exceptions(ifstream::failbit);
        try {
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            stringstream vShaderStream, fShaderStream;

            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf();

            vShaderFile.close();
            fShaderFile.close();

            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str();
        }
        catch(ifstream::failure e) {
            cout << e.what();
        }
        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();


        GLuint vertex, fragment;
        GLint success;
        GLchar infoLog[512];

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            cout << infoLog;
        }

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            cout << infoLog;
        }
        this->Program = glCreateProgram();
        glAttachShader(this->Program, vertex);
        glAttachShader(this->Program, fragment);
        glLinkProgram(this->Program);
        glGetProgramiv(this->Program, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(this->Program, 512, NULL, infoLog);
            cout << infoLog;
        }

        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    void use() {
        glUseProgram(this->Program);
    }
};

#endif