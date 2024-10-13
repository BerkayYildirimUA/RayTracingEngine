//
// Created by berka on 07/10/2024.
//

#include "Rendering/include/Camera.h"
#include "Core/include/Color3.h"

void Camera::raytrace(Scene &scn, int blocksize) {
    Ray theRay;
    theRay.setStart(eye);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, nColumns, 0, nRows, -1, 1);
    glDisable(GL_LIGHTING);

    for (int row = 0; row <= nRows; row++) {
        for (int col = 0; col <= nRows; col++) {
            //theRay.setDir(); //TODO set dir
            Color3 clr = scn.shade(theRay);
            glColor3f(clr.R, clr.B, clr.B);
            glRecti(col, row, col + blocksize, row + blocksize);
        }
    }
}
