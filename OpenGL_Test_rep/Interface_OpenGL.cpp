// Подключение заголовочного файла
#include "Function_OpenGL.h"

FTGLPolygonFont* fonts[6];
#define TEXT_SC_M 0.0366 

enum
{
    FONT_ARIAL,
    FONT_COMIC,
    FONT_TIMES,
    FONT_SYMBL,
    FONT_COURI,
    FONT_ARIAL_SM,
};

//fonts[FONT_ARIAL] = new FTGLPolygonFont("../Libs/FONTS/arialbd.ttf");
//fonts[FONT_COMIC] = new FTGLPolygonFont("C:/Users/Даниил/source/repos/OpenGL_Test_rep/Libs/FONTS/comic.ttf");
/*
* 
fonts[FONT_TIMES] = new FTGLPolygonFont("../Libs/FONTS/times.ttf");
fonts[FONT_SYMBL] = new FTGLPolygonFont("../Libs/FONTS/symbol.ttf");
fonts[FONT_COURI] = new FTGLPolygonFont("../Libs/FONTS/cour.ttf");
fonts[FONT_ARIAL_SM] = new FTGLPolygonFont("../Libs/FONTS/Arial.ttf");
*/

int draw_text_1(const char* inp, double x, double y, double mash, bool cx, bool cy, double angl)
{

    // Create a pixmap font from a TrueType file.

    //FTGLPixmapFont font("C:/Users/Даниил/source/repos/OpenGL_Test_rep/Libs/FONTS/comic.ttf");
    FTGLPixmapFont font("../Libs/FONTS/times.ttf");

    // If something went wrong, bail out.
    if (font.Error())
    {
        return -1;
        cout << "ERROR" << endl;
    }


    // Set the font size and render a small text.
    //font.FaceSize(72);
    //font.Render("Hello World!");
}