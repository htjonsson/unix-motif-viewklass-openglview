#ifndef OPENGL_VIEW_DELEGATE_H
#define OPENGL_VIEW_DELEGATE_H

// Motif
#include <Xm/Xm.h>
// OpenGL
#include <GL/gl.h>
#include <GL/glx.h>

class OpenGLView;

class OpenGLViewDelegate 
{
public:
    OpenGLViewDelegate();
    ~OpenGLViewDelegate();

private:
    XVisualInfo*    _visualInfo;
    GLXContext      _glxContext;    
    GLboolean       _doubleBuffer = GL_TRUE;
    OpenGLView*     _openGLView;

public:
    XVisualInfo*    visualInfo();
    GLXContext      context();
    GLboolean       doubleBuffer(); 

public:
    void setOpenGLView(OpenGLView* openGLView);

public:
    virtual bool createContext(Widget widget);
    virtual void makeCurrent(Widget widget);

public:
    virtual void handleUpdateViewport(Dimension width, Dimension height);

public:
    virtual void handleKeyRelease(KeySym keysym);

public:
    virtual void initalizeGL();
    virtual void drawGL();
};

#endif // OPENGL_VIEW_DELEGATE_H