// ViewKit/ViewKlass
#include <Vk/VkComponent.h>
// Motif
#include <Xm/Xm.h>
#include <Xm/DrawingA.h>
// OpenGL
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
// Standard C/C++
#include <string>
#include <iostream>

#include "OpenGLView.h"

OpenGLView::OpenGLView(const char *name, Widget parent, OpenGLViewDelegate* delegate) 
    : VkComponent(name)
{
    setDelegate(delegate);
    createWidget(name, parent);
}

OpenGLView::~OpenGLView()
{}

void 
OpenGLView::createWidget(const char *name, Widget parent)
{
    _baseWidget = XtCreateManagedWidget(name, xmDrawingAreaWidgetClass, parent, NULL, 0);

    // installDestroyHandler();

    XtAddCallback(_baseWidget, XmNexposeCallback, exposeCallback, this);
    XtAddCallback(_baseWidget, XmNresizeCallback, resizeCallback, this);
    XtAddCallback(_baseWidget, XmNinputCallback, inputCallback, this);


    if (_delegate != NULL &&(true == _delegate->createContext(_baseWidget)))
    {
        _delegate->makeCurrent(_baseWidget);
        _delegate->initalizeGL(); 
    }
}

// ---------------------------------------------------------------------------------------------------------  

void
OpenGLView::setDelegate(OpenGLViewDelegate* delegate)
{
    this->_delegate = delegate;
}

// ---------------------------------------------------------------------------------------------------------  

void
OpenGLView::updateViewport()
{
    Dimension width, height;

    XtVaGetValues(_baseWidget, XmNwidth, &width, XmNheight, &height, NULL);
    glViewport(0, 0, (GLint) width, (GLint) height);

    _viewportUpdateNeeded = GL_FALSE;

    if (_delegate != NULL)
        _delegate->handleUpdateViewport(width, height);
}

void
OpenGLView::update()
{
    if (_delegate != NULL)
    {
        _delegate->makeCurrent(_baseWidget);

        if (_viewportUpdateNeeded) 
            updateViewport();

        _delegate->drawGL();

        if (_delegate->doubleBuffer()) 
            glXSwapBuffers(XtDisplay(_baseWidget), XtWindow(_baseWidget));
    
        glFlush();
    }    
}

// ---------------------------------------------------------------------------------------------------------  

void
OpenGLView::handleExpose(Widget widget)
{   
    update();
}

void
OpenGLView::handleResize(Widget widget)
{   
    /* don't try OpenGL until window is realized! */
    if (XtIsRealized(_baseWidget)) 
    { 
        updateViewport();
    }
    else 
    {
        _viewportUpdateNeeded = GL_TRUE;
    }       
}


void 
OpenGLView::handleKeyRelease(Widget widget, KeySym keysym)
{
    switch (keysym) 
    {
        case XK_Up:
            glRotatef(10.0, 0.0, 0.0, 1.0); 
            update();
            break;

        case XK_Down:
            glRotatef(-10.0, 0.0, 0.0, 1.0);
            update();
            break;

        case XK_Left:
            glRotatef(-10.0, 0.0, 1.0, 0.0);
            update();
            break;

        case XK_Right:
            glRotatef(10.0, 0.0, 1.0, 0.0);
            update();
            break;

        default: 
            break;
    }    
}

void
OpenGLView::handleInput(Widget widget, XEvent* event)
{
    switch (event->type) 
    {
        case KeyRelease:
        {
            /*
             * It is necessary to convert the keycode to a keysym before it is
             * possible to check if it is an escape
             */
            char    buffer[1];
            KeySym  keysym;

            int rc = XLookupString((XKeyEvent *)event, buffer, 1, &keysym, NULL);

            handleKeyRelease(widget, keysym);

            break;
        }
        default:
            break;
    }
}

// ---------------------------------------------------------------------------------------------------------  

void
OpenGLView::exposeCallback(Widget widget, XtPointer clientData, XtPointer callData)
{
    OpenGLView *view = (OpenGLView*) clientData;
    view->handleExpose(widget);
}

void
OpenGLView::resizeCallback(Widget widget, XtPointer clientData, XtPointer callData)
{
    OpenGLView *view = (OpenGLView*) clientData;
    view->handleResize(widget);
}

void
OpenGLView::inputCallback(Widget widget, XtPointer clientData, XtPointer callData)
{
    XmDrawingAreaCallbackStruct *cd = (XmDrawingAreaCallbackStruct*) callData;

    OpenGLView *view = (OpenGLView*) clientData;
    view->handleInput(widget, cd->event);    
}