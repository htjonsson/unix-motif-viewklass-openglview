// https://github.com/gamedev-net/nehe-opengl/blob/master/irix/lesson05/lesson5.c

glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); /* Clear The Screen And The Depth Buffer */

glLoadIdentity();                   /* make sure we're no longer rotated. */
glTranslatef(1.5f,0.0f,-7.0f);      /* Move Right 3 Units, and back into the screen 7 */
    
glRotatef(rquad,1.0f,1.0f,1.0f);    /* Rotate The Cube On X, Y, and Z */

/* draw a cube (6 quadrilaterals)*/
glBegin(GL_QUADS);                  /* start drawing the cube. */

/* top of cube*/
glColor3f(0.0f,1.0f,0.0f);          /* Set The Color To Blue */
glVertex3f( 1.0f, 1.0f,-1.0f);      /* Top Right Of The Quad (Top) */
glVertex3f(-1.0f, 1.0f,-1.0f);      /* Top Left Of The Quad (Top) */
glVertex3f(-1.0f, 1.0f, 1.0f);      /* Bottom Left Of The Quad (Top) */
glVertex3f( 1.0f, 1.0f, 1.0f);      /* Bottom Right Of The Quad (Top) */

/* bottom of cube*/
glColor3f(1.0f,0.5f,0.0f);          /* Set The Color To Orange */
glVertex3f( 1.0f,-1.0f, 1.0f);      /* Top Right Of The Quad (Bottom) */
glVertex3f(-1.0f,-1.0f, 1.0f);      /* Top Left Of The Quad (Bottom) */
glVertex3f(-1.0f,-1.0f,-1.0f);      /* Bottom Left Of The Quad (Bottom) */
glVertex3f( 1.0f,-1.0f,-1.0f);      /* Bottom Right Of The Quad (Bottom) */

/* front of cube*/
glColor3f(1.0f,0.0f,0.0f);          /* Set The Color To Red */
glVertex3f( 1.0f, 1.0f, 1.0f);      /* Top Right Of The Quad (Front) */
glVertex3f(-1.0f, 1.0f, 1.0f);      /* Top Left Of The Quad (Front) */
glVertex3f(-1.0f,-1.0f, 1.0f);      /* Bottom Left Of The Quad (Front) */
glVertex3f( 1.0f,-1.0f, 1.0f);      /* Bottom Right Of The Quad (Front) */

/* back of cube.*/
glColor3f(1.0f,1.0f,0.0f);          /* Set The Color To Yellow */
glVertex3f( 1.0f,-1.0f,-1.0f);      /* Top Right Of The Quad (Back) */
glVertex3f(-1.0f,-1.0f,-1.0f);      /* Top Left Of The Quad (Back) */
glVertex3f(-1.0f, 1.0f,-1.0f);      /* Bottom Left Of The Quad (Back) */
glVertex3f( 1.0f, 1.0f,-1.0f);      /* Bottom Right Of The Quad (Back) */

/* left of cube*/
glColor3f(0.0f,0.0f,1.0f);          /* Blue*/
glVertex3f(-1.0f, 1.0f, 1.0f);      /* Top Right Of The Quad (Left) */
glVertex3f(-1.0f, 1.0f,-1.0f);      /* Top Left Of The Quad (Left) */
glVertex3f(-1.0f,-1.0f,-1.0f);      /* Bottom Left Of The Quad (Left) */
glVertex3f(-1.0f,-1.0f, 1.0f);      /* Bottom Right Of The Quad (Left) */

/* Right of cube */
glColor3f(1.0f,0.0f,1.0f);          /* Set The Color To Violet */
glVertex3f( 1.0f, 1.0f,-1.0f);      /* Top Right Of The Quad (Right) */
glVertex3f( 1.0f, 1.0f, 1.0f);      /* Top Left Of The Quad (Right) */
glVertex3f( 1.0f,-1.0f, 1.0f);      /* Bottom Left Of The Quad (Right) */
glVertex3f( 1.0f,-1.0f,-1.0f);      /* Bottom Right Of The Quad (Right) */

glEnd();  

rquad-=15.0f;                       /* Decrease The Rotation Variable For The Cube*/

/* swap the buffers to display, since double buffering is used.*/
glutSwapBuffers();


void InitGL()          /* We call this right after our OpenGL window is created.*/
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);     /* This Will Clear The Background Color To Black*/
    glClearDepth(1.0);                /* Enables Clearing Of The Depth Buffer*/
    glDepthFunc(GL_LESS);                 /* The Type Of Depth Test To Do*/
    glEnable(GL_DEPTH_TEST);              /* Enables Depth Testing*/
    glShadeModel(GL_SMOOTH);          /* Enables Smooth Color Shading*/
}


    resize(width, height)


/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
    if (Height==0)                /* Prevent A Divide By Zero If The Window Is Too Small*/
        Height=1;

    glViewport(0, 0, Width, Height);      /* Reset The Current Viewport And Perspective Transformation*/

    resize();
}

void resize(int width, int width)

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f, (GLfloat)width/(GLfloat)width, 0.1f, 100.0f);
  
    glMatrixMode(GL_MODELVIEW);
}
