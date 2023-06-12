#include "glshowcloud.h"
#include <QDebug>
#include <QMouseEvent>

const char *vertexShaderSource = "#version 330 core\n layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "   gl_PointSize = 10.0;\n"
                                 "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\0";

glShowCloud::glShowCloud(QWidget *parent):QOpenGLWidget(parent)
{
}

glShowCloud::~glShowCloud()
{

}

void glShowCloud::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.2,0.1,0.2,1.0);
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        qDebug("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        qDebug("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");
    }
    // link shaders
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        qDebug("ERROR::SHADER::PROGRAM::LINKING_FAILED\n");
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[] = {
        0.0f, 0.0f, 0.0f,
        0.5f, 0.9f, 0.0f,
        0.9f,  0.5f, 0.0f
    };
    glGenVertexArrays(1, &VAO[0]);
    glGenBuffers(1, &VBO[0]);
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    float vertices2[] = {
        0.0f, 0.0f, 0.0f,
        -0.5f, -0.9f, 0.0f,
        -0.9f, -0.5f, 0.0f
    };
    glGenVertexArrays(1, &VAO[1]);
    glGenBuffers(1, &VBO[1]);
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void glShowCloud::resizeGL(int w, int h)
{
    qDebug("resizeGL(int w, int h)");
}

void glShowCloud::paintGL()
{
    qDebug("paintGL()");

    glViewport(0,0,width()*devicePixelRatio(),height()*devicePixelRatio());
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);

    glBindVertexArray(VAO[0]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_TRIANGLES, 0, 3);

//    glUseProgram(shaderProgram);
    glBindVertexArray(VAO[1]); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glEnable(GL_PROGRAM_POINT_SIZE);
//    glPointSize(10);
    glDrawArrays(GL_POINTS, 0, 3);
}

void glShowCloud::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        m_isLeftPressing = true;
    }
    else if(event->button()==Qt::RightButton)
    {
        m_isRightPressing = true;
    }
}

void glShowCloud::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        m_isLeftPressing = false;
    }
    else if(event->button()==Qt::RightButton)
    {
        m_isRightPressing = false;
    }
}

void glShowCloud::mouseMoveEvent(QMouseEvent *event)
{
    m_mouseXNow = event->pos().x();
    m_mouseYNow = event->pos().y();
    qDebug("x:%d y:%d",m_mouseXNow,m_mouseYNow);
}
