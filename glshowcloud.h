#ifndef GLSHOWCLOUD_H
#define GLSHOWCLOUD_H

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>


class glShowCloud : public QOpenGLWidget,public QOpenGLExtraFunctions
{
public:
    glShowCloud(QWidget *parent);
    ~glShowCloud();

private:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    unsigned int VAO[2];
    unsigned int VBO[2];

    unsigned int shaderProgram;

    bool m_isLeftPressing = false;
    bool m_isRightPressing = false;
    int m_mouseXNow = 0;
    int m_mouseYNow = 0;
    int m_mouseXPre = 0;
    int m_mouseYPre = 0;

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
//    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
//    virtual void keyPressEvent(QKeyEvent *event);
//    virtual void keyReleaseEvent(QKeyEvent *event);
//    virtual void focusInEvent(QFocusEvent *event);
//    virtual void focusOutEvent(QFocusEvent *event);
//    virtual void enterEvent(QEnterEvent *event);
//    virtual void leaveEvent(QEvent *event);
//    virtual void paintEvent(QPaintEvent *event);
//    virtual void moveEvent(QMoveEvent *event);
//    virtual void resizeEvent(QResizeEvent *event);
//    virtual void closeEvent(QCloseEvent *event);

};

#endif // GLSHOWCLOUD_H
