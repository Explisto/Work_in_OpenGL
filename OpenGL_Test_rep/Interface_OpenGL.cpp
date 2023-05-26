// Подключение заголовочного файла
#include "Function_OpenGL.h"

/*
int draw_text_1() 
{
	FTGLPixmapFont font("arial.ttf");
	font.FaceSize(72);
	font.Render("Hello World!");
}
*/

int draw_text_1()
{
	FT_Library ft;
	FT_Error err = FT_Init_FreeType(&ft);
	if (err != 0)
	{
		printf("Failed to initialize FreeType\n");
		exit(EXIT_FAILURE);
	}
	FT_Int major, minor, patch;
	FT_Library_Version(ft, &major, &minor, &patch);
	//printf("FreeType's version is %d.%d.%d\n", major, minor, patch);
	return 0;
}





//FTGLPolygonFont* fonts[6];
//#define TEXT_SC_M 0.0366
//
//int draw_text_1()
//{
//	FTGLPixmapFont fonts("arial.ttf");
//	//FTGLPolygonFont fonts("arial.ttf");
//	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//	glEnable(GL_POLYGON_SMOOTH);
//	glPushMatrix();
//	glTranslated(1, 1, 0);
//	glScaled(TEXT_SC_M, TEXT_SC_M, TEXT_SC_M);
//	//glScaled(mash, mash / 2, mash);
//	fonts.Render("Hello world!");
//	glPopMatrix();
//	glDisable(GL_POLYGON_SMOOTH);
//}