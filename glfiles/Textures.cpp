#include "Textures.h"
#include "../lib/stb_image.h"
#include <iostream>

Textures::Textures(const std::string &fname){
                /*width height and number of components of the image*/
    int iwidth, iheight, ncomp;
    /*load the data using std_image load*/
    unsigned char* imagedata = stbi_load(fname.c_str(), &iwidth, &iheight, &ncomp, 4);

    if( imagedata == NULL){
        std::cout << "Unable to load texture : " << std::endl;
    }



    /*allocate space for text and bind the texture to the allocated space*/
    glGenTextures(1, &texturehandle);
    glBindTexture(GL_TEXTURE_2D, texturehandle);

    /*sets texture parameters width and height to wrap*/
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    /*lets open gl handle caes of too big texture and too small*/
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /*      type of texture, vary texture depending on how far away*, store data as Red Green
     * Blue Alpha*, img width, img height,  format of data, how the data is stored , the actual data*/
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iwidth, iheight, 0, GL_RGBA, GL_UNSIGNED_BYTE,imagedata);

    stbi_image_free(imagedata);

}

Textures::~Textures(){

    glDeleteTextures(1, &texturehandle);
}

void Textures::Bind(unsigned int textnum){

    if ( textnum >=0 || textnum < 32 ){

        /*set the active texture and bind*/
        glActiveTexture(GL_TEXTURE0 + textnum);
        glBindTexture(GL_TEXTURE_2D, texturehandle);
    }

}



/**REFERENCES
 *
 * this class uses the stb_img to load images
 * lib located https://github.com/nothings/stb
 * code regarding library is based off test code from github
 * https://github.com/nothings/stb/tree/master/tests
 */