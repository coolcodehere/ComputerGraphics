#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

void drawEmptyDiamond() {
  glColor3f(0.01, 0.89, 0.988);
  // top frame
  glBegin(GL_LINE_LOOP);
    
    glVertex2f(-0.5f, 0.0f);
    glVertex2f(-0.375f, 0.2f);
    glVertex2f(0.375f, 0.2f);
    glVertex2f(0.5f, 0.0f);
  glEnd();

  // top inner triangles
  glBegin(GL_LINE_LOOP);
    glVertex2f(-0.5f, 0.0f);
    glVertex2f(-0.375f, 0.2f);
    glVertex2f(-0.25f, 0.0f);
    glVertex2f(-0.125f, 0.2f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.125f, 0.2f);
    glVertex2f(0.25f, 0.0f);
    glVertex2f(0.375f, 0.2f);
    glVertex2f(0.5f, 0.0f);
  glEnd();

  // bottom triangles
  glBegin(GL_LINE_LOOP);
    glVertex2f(-0.25f, 0.0f);
    glVertex2f(0.0f, -0.75f);
    glVertex2f(0.0f, 0.0f);
    glVertex2f(0.0f, -0.75f);
    glVertex2f(0.25f, 0.0f);
  glEnd();

  // Bottom Yellow triangle
  glColor3f(0.98, 0.73, 0.01);
  glBegin(GL_LINE_LOOP);
    glVertex2f(-0.5f, 0.0f);
    glVertex2f(0.5f, 0.0f);
    glVertex2f(0.0f, -0.75f);
  glEnd();
}

void drawFilledDiamond() {

  glBegin(GL_TRIANGLES);
    //bottom left
    glColor3f(0.0588, 0.988, 0.0118);
    glVertex2f(-0.5f, 0.0f);
    glColor3f(0.01f, 0.89f, 0.988);
    glVertex2f(-0.17f, 0.0f);
    glColor3f(0.988, 0.0118, 0.0118);
    glVertex2f(-0.015f, -0.75f);

    //bottom middle
    glColor3f(0.01f, 0.89f, 0.988);
    glVertex2f(-0.155f, 0.0f);
    glVertex2f(0.155f, 0.0f);
    glColor3f(0.988, 0.0118, 0.0118);
    glVertex2f(0.0f, -0.75f);

    //bottom right
    glColor3f(0.0118, 0.109, 0.988);
    glVertex2f(0.5f, 0.0f);
    glColor3f(0.01f, 0.89f, 0.988);
    glVertex2f(0.17f, 0.0f);
    glColor3f(0.988, 0.0118, 0.0118);
    glVertex2f(0.015f, -0.75f);

    //top 1 (left)
    glColor3f(0.0588, 0.988, 0.0118);
    glVertex2f(-0.5f, 0.015f);
    glColor3f(0.01f, 0.89f, 0.988);
    glVertex2f(-0.335f, 0.25f);
    glVertex2f(-0.179f, 0.015f);

    //top 2
    glVertex2f(-0.32f, 0.25f);
    glVertex2f(-0.161f, 0.015f);
    glVertex2f(-0.015f, 0.25f);

    //top 3 (mid)
    glVertex2f(-0.145f, 0.015f);
    glVertex2f(0.145f, 0.015f);
    glVertex2f(0.0f, 0.25f);

    //top 4
    glVertex2f(0.32f, 0.25f);
    glVertex2f(0.161f, 0.015f);
    glVertex2f(0.015f, 0.25f);

    //top 5 (right)
    glVertex2f(0.335f, 0.25f);
    glVertex2f(0.179f, 0.015f);
    glColor3f(0.0118, 0.109, 0.988);
    glVertex2f(0.5f, 0.015f);


  glEnd();
}

void myRender() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(0.0,0.0,0.0,0.0);
  glLineWidth(2);

  drawEmptyDiamond();
  // drawFilledDiamond();

  glFlush();
  glutSwapBuffers();
}

void main(int argc, char ** argv) {
  printf("hello world");
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

  glutInitWindowPosition(400,200);
  glutInitWindowSize(640, 480);
  #define windowName "Will Walter"
  glutCreateWindow(windowName);

  glutDisplayFunc(myRender);

  glutMainLoop();

  exit(0);
}

