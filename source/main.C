// Motif 
#include <Xm/Xm.h>
// ViewKlass
#include <Vk/VkApp.h>
#include <Vk/VkSimpleWindow.h>
// Standard C/C++
#include <stdio.h>
#include <iostream>
#include <vector>

#include "DefaultResources.h"
#include "OpenGLView.h"
#include "OpenGLViewDelegate.h"

using namespace std;

// Application-specific setup
int main ( int argc, char **argv )
{
    VkApp* app = new VkApp("OpenGLViewApp", &argc, argv);
    // Application-specific code
    app->setDefaultResources(app->baseWidget(), _defaultResources);

    VkSimpleWindow* win = new VkSimpleWindow("OpenGLView");

    OpenGLViewDelegate delegate;

    OpenGLView view("opengl_view", win->mainWindowWidget(), &delegate);
    win->addView(view);

    // Set a default size of window as 800x600
    XtVaSetValues(win->mainWindowWidget(), XmNwidth, 800, XmNheight, 600, NULL);

    win->show();

    // Run the application
    app->run();  

    return 0;
}

