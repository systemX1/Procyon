#include "FShader.h"

PrRendering::Resources::FShader::FShader(const char* p_vertexShaderPath, const char* p_fragmentShaderPath) {
    // prepare shader data
    // open files
    std::string vertexShaderCode;
    std::string fragmentShaderCode;
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;
    vertexShaderFile.open(p_vertexShaderPath);
    fragmentShaderFile.open(p_fragmentShaderPath);
    // assert open files
    assert(vertexShaderFile.is_open() && "CANNOT OPEN vertexShaderFile");
    assert(fragmentShaderFile.is_open() && "CANNOT OPEN fragmentShaderFile");
    // read file's buffer contents into streams
    std::stringstream vShaderStream, fShaderStream;
    vShaderStream << vertexShaderFile.rdbuf();
    fShaderStream << fragmentShaderFile.rdbuf();
    // close file handlers
    vertexShaderFile.close();
    fragmentShaderFile.close();
    // convert stream into string
    vertexShaderCode = vShaderStream.str();
    fragmentShaderCode = fShaderStream.str();
    // convert to const char*
    const char* vertexShaderCodeCStr = vertexShaderCode.c_str();
    const char* fragmentShaderCodeCStr = fragmentShaderCode.c_str();

    // compile shaders
    GLuint vertexShader, fragmentShader;
    // vertex shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCodeCStr, nullptr);
    glCompileShader(vertexShader);
    CheckCompileErrors(vertexShader, "VERTEX");
    // fragment FShader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCodeCStr, nullptr);
    glCompileShader(fragmentShader);
    CheckCompileErrors(fragmentShader, "FRAGMENT");
    // shader Program
    m_id = glCreateProgram();
    glAttachShader(m_id, vertexShader); 
    glAttachShader(m_id, fragmentShader);
    glLinkProgram(m_id);
    CheckCompileErrors(m_id, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    logi("FShader created with vs:{} fs:{}", p_vertexShaderPath, p_fragmentShaderPath);
}

void PrRendering::Resources::FShader::UseProgram() const {
    glUseProgram(m_id);
}

void PrRendering::Resources::FShader::SetBool(const std::string& p_name, const bool p_value) const {
    glUniform1i(glGetUniformLocation(m_id, p_name.c_str()), static_cast<int>(p_value));
}

void PrRendering::Resources::FShader::SetInt(const std::string& p_name, const int p_value) const {
    glUniform1i(glGetUniformLocation(m_id, p_name.c_str()), p_value);
}

void PrRendering::Resources::FShader::SetFloat(const std::string& p_name, const float p_value) const {
    glUniform1f(glGetUniformLocation(m_id, p_name.c_str()), p_value);
}

void PrRendering::Resources::FShader::CheckCompileErrors(const unsigned int p_shader, const std::string& p_type) {
    int success;
    char infoLog[1024];
    if (p_type != "PROGRAM" ) {
        glGetShaderiv(p_shader, GL_COMPILE_STATUS, &success);
        if ( !success ) {
            glGetShaderInfoLog(p_shader, 1024, nullptr, infoLog);
            loge("ERROR::SHADER_COMPILATION_ERROR of type {}: {}", p_type, infoLog);
            //std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    } else {
        glGetProgramiv(p_shader, GL_LINK_STATUS, &success);
        if ( !success ) {
            glGetProgramInfoLog(p_shader, 1024, nullptr, infoLog);
            loge("ERROR::PROGRAM_LINKING_ERROR of type {}: {}", p_type, infoLog);
            //std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
