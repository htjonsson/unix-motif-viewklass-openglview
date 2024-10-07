// OpenGL
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>

#include "OpenGLViewDelegate.h"
#include "OpenGLView.h"

OpenGLViewDelegate::OpenGLViewDelegate()
{}

OpenGLViewDelegate::~OpenGLViewDelegate()
{}

// ---------------------------------------------------------------------------------------------------------  

void 
OpenGLViewDelegate::setOpenGLView(OpenGLView* openGLView)
{
    _openGLView = openGLView;
}

XVisualInfo*    
OpenGLViewDelegate::visualInfo()
{
    return _visualInfo;
}

GLXContext      
OpenGLViewDelegate::context()
{
    return _glxContext;
}

GLboolean       
OpenGLViewDelegate::doubleBuffer()
{
    return _doubleBuffer;
}

// --------------------------------------------------------------------------------------------------------- 

bool
OpenGLViewDelegate::createContext(Widget widget)
{
    static int snglBuf[] = {GLX_RGBA, GLX_DEPTH_SIZE, 16, None};
    static int dblBuf[] = {GLX_RGBA, GLX_DEPTH_SIZE, 16, GLX_DOUBLEBUFFER, None};

    /* find an OpenGL-capable RGB visual with depth buffer */
    _visualInfo = glXChooseVisual(XtDisplay(widget), DefaultScreen(XtDisplay(widget)), dblBuf);
    if (_visualInfo == NULL) 
    {
        _visualInfo = glXChooseVisual(XtDisplay(widget), DefaultScreen(XtDisplay(widget)), snglBuf);
    
        if (_visualInfo == NULL) 
        {
            XtWarning("no RGB visual with depth buffer");
            return false;
        }         
        _doubleBuffer = GL_FALSE;
    }

    /* create an OpenGL rendering context */
    _glxContext = glXCreateContext(XtDisplay(widget), _visualInfo, /* no display list sharing */ None, /* favor direct */ GL_TRUE);
    if (_glxContext == NULL) 
    {
        XtWarning("could not create rendering context");
        return false;
    }
    return true;
}

void
OpenGLViewDelegate::makeCurrent(Widget widget)
{
    /* Once widget is realized (ie, associated with a created X window), we
     * can bind the OpenGL rendering context to the window.
     */
    glXMakeCurrent(XtDisplay(widget), XtWindow(widget), _glxContext);
}

// ---------------------------------------------------------------------------------------------------------  

void
OpenGLViewDelegate::handleUpdateViewport(Dimension width, Dimension height)
{

}

void 
OpenGLViewDelegate::handleKeyRelease(KeySym keysym)
{
    switch (keysym) 
    {
        case XK_Up:
            glRotatef(10.0, 0.0, 0.0, 1.0); 
            _openGLView->update();
            break;

        case XK_Down:
            glRotatef(-10.0, 0.0, 0.0, 1.0);
            _openGLView->update();
            break;

        case XK_Left:
            glRotatef(-10.0, 0.0, 1.0, 0.0);
            _openGLView->update();
            break;

        case XK_Right:
            glRotatef(10.0, 0.0, 1.0, 0.0);
            _openGLView->update();
            break;

        default: 
            break;
    }    
}

// ---------------------------------------------------------------------------------------------------------  

void 
OpenGLViewDelegate::initalizeGL()
{
    /* setup OpenGL state */
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL); 
    glClearDepth(1.0);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glLoadIdentity();
    gluPerspective(40.0, 1.0, 10.0, 200.0);
    glTranslatef(0.0, 0.0, -50.0); 
    glRotatef(-58.0, 0.0, 1.0, 0.0);
}

void 
OpenGLViewDelegate::drawGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.0); glVertex3f(-10.0, -10.0, 0.0);
    glColor3f(0.7, 0.7, 0.7); glVertex3f(10.0, -10.0, 0.0);
    glColor3f(1.0, 1.0, 1.0); glVertex3f(-10.0, 10.0, 0.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 0.0); glVertex3f(0.0, -10.0, -10.0);
    glColor3f(0.0, 1.0, 0.7); glVertex3f(0.0, -10.0, 10.0);
    glColor3f(0.0, 0.0, 1.0); glVertex3f(0.0, 5.0, -10.0);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(1.0, 1.0, 0.0); glVertex3f(-10.0, 6.0, 4.0);
    glColor3f(1.0, 0.0, 1.0); glVertex3f(-10.0, 3.0, 4.0);
    glColor3f(0.0, 0.0, 1.0); glVertex3f(4.0, -9.0, -10.0);
    glColor3f(1.0, 0.0, 1.0); glVertex3f(4.0, -6.0, -10.0);
    glEnd();  
}