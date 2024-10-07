#ifndef OPENGL_VIEW_H
#define OPENGL_VIEW_H

#include <Vk/VkComponent.h>
#include <Xm/Xm.h>
// OpenGL
#include <GL/gl.h>
#include <GL/glx.h>

#include "OpenGLViewDelegate.h"

class OpenGLView : public VkComponent
{
public:
    OpenGLView(const char *name, Widget parent, OpenGLViewDelegate* delegate);
    ~OpenGLView();

private:
  void createWidget(const char *name, Widget parent);  

private:
    GLboolean _viewportUpdateNeeded = GL_TRUE;

private:
    OpenGLViewDelegate* _delegate = NULL;

private:
    void setDelegate(OpenGLViewDelegate* delegate);

private:
    void updateViewport();

public:
    void update();
    
private:
    void handleExpose(Widget widget);
    void handleResize(Widget widget); 
    void handleInput(Widget widget, XEvent* event);   
    void handleKeyRelease(Widget widget, KeySym keysym);

private:
    static void inputCallback(Widget widget, XtPointer clientData, XtPointer callData);
    static void exposeCallback(Widget widget, XtPointer clientData, XtPointer callData); 
    static void resizeCallback(Widget widget, XtPointer clientData, XtPointer callData);   
};

#endif // OPENGL_VIEW_H