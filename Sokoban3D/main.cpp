#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include <GL/glut.h> 
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdint.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <sstream>
#include "SOIL.h"
#include "fmod.hpp"
#include "main.h"
#include <fstream>
#include <windows.h>

void exit_game()
{
	systemFMOD->release();
	exit(0);
}
void text(GLfloat x, GLfloat y, GLfloat scale, char* texto, ...) 
{ // x,y position, scale factor, text
	va_list args; 
	char buffer[255], *p; 
	GLfloat font_scale = 119.05 + 33; //Maximo + minimo
	va_start(args, texto); 
	vsprintf(buffer, texto, args); 
	va_end(args); 
	glMatrixMode(GL_MODELVIEW); 
	glPushMatrix(); 
	glLoadIdentity(); 
	glPushAttrib(GL_ENABLE_BIT); 
	glDisable(GL_LIGHTING); 
	glDisable(GL_TEXTURE_2D); 
	glDisable(GL_DEPTH_TEST); 
	glTranslatef(x, y, 0.0); 
	glScalef(scale/font_scale, scale/font_scale, scale/font_scale); 
	for(p = buffer; *p; p++) 
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *p); //fonte + texto (ver glut-3.spec.pdf) 
	glPopAttrib(); 
	glPopMatrix(); 
} 
void showRotationLast()
{
	if(scale<=30)
	{

		scale+=1.0f;
	}
	else{ win=false;
		game_state=GAME_SCORE;}
}
void showRotation()
{
	if(rotationx!=0)
	{
		rotationx-=5;
		rotationy-=5;
		rotationz-=5;
		scale+=0.01945;
	}
}
int LoadGLTextures() // Load Bitmaps And Convert To Textures
{
	//----------------WALL TEXTURE --------------------
	texture[1] = SOIL_load_OGL_texture
		(
		"gfx/wall.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	if(texture[1] == 0)
		return false;


	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	//----------------FLOOR TEXTURE --------------------
	texture[2] = SOIL_load_OGL_texture
		(
		"gfx/floor.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	if(texture[2] == 0)
		return false;


	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	//----------------FLOOR_x TEXTURE --------------------
	texture[3] = SOIL_load_OGL_texture
		(
		"gfx/floor_x.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	if(texture[3] == 0)
		return false;


	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	//--------------- Box TEXTURE --------------------
	texture[4] = SOIL_load_OGL_texture
		(
		"gfx/box.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	if(texture[4] == 0)
		return false;


	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	//----------------Box_ok TEXTURE --------------------
	texture[5] = SOIL_load_OGL_texture
		(
		"gfx/box_ok.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	if(texture[5] == 0)
		return false;


	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	//----------------Player TEXTURE --------------------
	texture[6] = SOIL_load_OGL_texture
		(
		"gfx/player.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	if(texture[6] == 0)
		return false;


	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	//----------------LOGO TEXTURE --------------------
	texture[7] = SOIL_load_OGL_texture
		(
		"gfx/sokoban_logo.bmp",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y
		);

	if(texture[7] == 0)
		return false;


	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

	//----------------Splash End TEXTURE --------------------
	
	return true;										// Return Success
}
void displayString()
{
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glColor3f( 1.0, 1.0, 1.0 );

	glRasterPos3f( -50.0, -5.0, 0.0 );
	int i;
	for( i=0; i<(int)strlen( lvl.c_str() ); i++ )
		glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, lvl[i] );
	std::stringstream s;
	s << current_level;
	std::string tr = s.str();
	for( i=0; i<(int)strlen( tr.c_str() ); i++ )
		glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, tr[i] );

	glRasterPos3f( -20.0, -5.0, 0.0 );
	for( i=0; i<(int)strlen( moves.c_str() ); i++ )
		glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, moves[i] );

	
	std::stringstream ss;
	ss << MOVES;
	std::string str = ss.str();
	
	for( i=0; i<(int)strlen( str.c_str() ); i++ )
		glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, str[i] );

	glRasterPos3f( 10.0, -5.0, 0.0 );
	for( i=0; i<(int)strlen( pushes.c_str() ); i++ )
		glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, pushes[i] );
	std::stringstream sss;
	sss << PUSHES;
	std::string sstr = sss.str();

	for( i=0; i<(int)strlen( sstr.c_str() ); i++ )
		glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, sstr[i] );

	glPopMatrix();
}
void displayMenu()
{
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f); 
	glTranslatef(0,0,0);

	glViewport(WIDTH/20, HEIGHT-(HEIGHT/3), WIDTH-(WIDTH/8),HEIGHT/3 );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_DEPTH);
	glColor3ub(255,255,255);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f,  0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f,  0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	glViewport(0, 0, WIDTH,HEIGHT );
	glPushMatrix();
	

	if (menu_chose1==CHOOSE)
		glColor3f(255,0,0);
	else glColor3f(0,0,0);

	text(-0.5,0.15,0.1,"CHOOSE LEVEL",0);

	if (menu_chose1==START)
		glColor3f(255,0,0);
	else glColor3f(0,0,0);
	
	text(-0.5,0.0,0.1,"NEW GAME",0);
	if (menu_chose1==OPTIONS)
		glColor3f(255,0,0);
	else glColor3f(0,0,0);
	text(-0.5,-0.15,0.1,"OPTIONS",0);
	if (menu_chose1==CREDITS)
		glColor3f(255,0,0);
	else glColor3f(0,0,0);
	text(-0.5,-0.3,0.1,"CREDITS",0);
	if (menu_chose1==EXIT)
		glColor3f(255,0,0);
	else glColor3f(0,0,0);
	text(-0.5,-0.45,0.1,"EXIT",0);

	

	glPopMatrix();
}
void displayMenuOptions()
{
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f); 
	glTranslatef(0,0,0);

	glViewport(0, 0, WIDTH,HEIGHT );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glPushMatrix();
	glLoadIdentity();
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	if (menu_chose_options==MCO_FULL)
		glColor3f(255,0,0);
	else glColor3f(0,0,0);
	text(-0.5,0.0,0.1,"FULLSCREEN",0);
	if (menu_chose_options==MCO_WINDOWED)
		glColor3f(255,0,0);
	else glColor3f(0,0,0);
	text(-0.5,-0.15,0.1,"WINDOWED",0);
	if (menu_chose_options==MCO_EXIT)
		glColor3f(255,0,0);
	else glColor3f(0,0,0);
	text(-0.5,-0.7,0.1,"BACK",0);

	glPopMatrix();
}
void displayMenuCredits()
{
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f); 
	glTranslatef(0,0,0);

	glViewport(0, 0, WIDTH,HEIGHT );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glPushMatrix();
	glLoadIdentity();
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	std::string authors="Made by Lukasz Swiderski ";
	std::string help ="with support of Piotr Palkiewicz";
	glRasterPos3f( -0.95, -0.6, 0.0 );
	int i;
	for( i=0; i<(int)strlen( authors.c_str() ); i++ )
		glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, authors[i] );
	glRasterPos3f( -0.8, -0.7, 0.0 );
	for( i=0; i<(int)strlen( help.c_str() ); i++ )
		glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, help[i] );
	std::string maps="Inspiration of maps was Rick Sladkey <rick.sladkey@gmail.com>";
	glRasterPos3f( -0.95, -0.8, 0.0 );
	for( i=0; i<(int)strlen( maps.c_str() ); i++ )
		glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, maps[i] );
	std::string strony="www.LukaszSwiderski.com ... www.neufrin.com";
	glRasterPos3f( -0.8, -0.9, 0.0 );
	for( i=0; i<(int)strlen( strony.c_str() ); i++ )
		glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, strony[i] );



	glPopMatrix();
}
void saveLoad()
{
	//std::cout<<levels_avaible<<" "<<current_level<<std::endl;
	if (levels_avaible<current_level)
	{
		levels_avaible = current_level;
	}
	//std::cout<<levels_avaible<<" "<<current_level<<std::endl;
	int tmp_level[1];
	tmp_level[0] =0;
	FILE *fp;
	fp = fopen("save.dat","rb");


	if (fp!=NULL)
	{
		fread((tmp_level),sizeof(int),1,fp);
		//std::cout<<"ODCZYTALO"<<std::endl;
		fclose(fp);
	}
	else 
	{
		//std::cout<<"UTWORZYLO NOWY"<<std::endl;
		fp = fopen("save.dat","w+b");
		fwrite(&tmp_level,sizeof(int),1,fp);
		fclose(fp);
		
	}
	fp = fopen("save.dat","r+b");
	//std::cout<<std::endl<<tmp_level[0]<<" "<<levels_avaible<<std::endl;
	if (tmp_level[0]>levels_avaible)
	{
		levels_avaible=tmp_level[0];

	}
	//std::cout<<tmp_level[0]<<" "<<levels_avaible<<std::endl;

	fwrite(&levels_avaible,sizeof(int),1,fp);
	fclose(fp);
}
void displayChooseLevel()
{
	
	

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f); 
	glTranslatef(0,0,0);

	glViewport(0, 0, WIDTH,HEIGHT );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	glPushMatrix();
	glLoadIdentity();
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

	glColor3f(0,0,0);


	//levels_avaible =100;
	float text_level=0.4;
	float text_column= -0.7;
		
	std::string level_text = "Level: ";
	for (int i=1; i<=levels_avaible;i++, text_level-=0.05)
	{

		if (i==21)
		{
			text_column= -0.4;
			 text_level=0.4;
		}
		else if (i==41)
		{
			text_column= -0.1;
			text_level=0.4;
		}
		else if (i==61)
		{
			text_column= 0.2;
			text_level=0.4;
		}
		else if (i==81)
		{
			text_column= 0.5;
			text_level=0.4;
		}
		if (i == choosed_level)
		{
			glColor3f(1,0,0);
		}
		else glColor3f(0,0,0);
		glRasterPos3f( text_column, text_level, 0.0 );
		for( int j=0; j<level_text.size(); j++ )
			glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, level_text[j] );

		std::stringstream ss;
		ss << i;
		std::string str = ss.str();
		ss.clear();

		for( int j=0; j<(int)strlen( str.c_str() ); j++ )
			glutBitmapCharacter( GLUT_BITMAP_HELVETICA_12, str[j] );
		str.clear();



	
		
	
	}


	glPopMatrix();
}
void displayGame()
{
	showRotation();
	glEnable(GL_DEPTH);
	if (win)
	{
		showRotationLast();
	}
	
	
	//scene

	if(HEIGHT == 0) //nie dzielimy przez 0
		HEIGHT  = 1;
	glViewport(0, 20, WIDTH,HEIGHT-20 );

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat nRange = 16.0f;
	GLfloat hudRange= 50.0f;
	if (WIDTH <= HEIGHT)
		glOrtho (-nRange, nRange, -nRange*HEIGHT /WIDTH, nRange*HEIGHT /WIDTH, -nRange*2,nRange*2);
	else
		glOrtho (-nRange*WIDTH/HEIGHT , nRange*WIDTH/HEIGHT , -nRange, nRange, -nRange*2, nRange*2);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();



	gluLookAt (ex,ey,ez,cx,cy,cz,ux,uy,uz);

	glScalef(scale,scale,scale);
	glRotatef(rotationx,1,0,0);
	glRotatef(rotationx,0,1,0);
	glRotatef(rotationx,0,0,1);
	drawMap();
	drawPlayer();
	drawBoxes();

	//hud

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f); 
	glTranslatef(0,0,0);

	glViewport(0, 0, WIDTH,20 );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	
	glOrtho (-hudRange, hudRange, -20, 20, -1,1);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBegin(GL_QUADS);
	glVertex3f(-hudRange, -20.0f, 0.0f);
	glVertex3f(hudRange, -20.0f, 0.0f);
	glVertex3f(hudRange, 20.0f,  0.0f);
	glVertex3f(-hudRange, 20.0f,  0.0f);
	glEnd();
	displayString();
	glPopMatrix();
	//logo

	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f); 
	glTranslatef(0,0,0);

	glViewport(0, HEIGHT-(HEIGHT/6), WIDTH/3,HEIGHT/6 );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_DEPTH);
	glColor3ub(255,255,255);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f,  0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f,  0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	
	glPopMatrix();
}
void displayScore()
{
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f); 
	glTranslatef(0,0,0);

	glViewport(0, 0, WIDTH,HEIGHT );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	glLoadIdentity();
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	glColor3f( 0.0, 0.0, 0.0 );
	std::stringstream ss;
	std::stringstream ss1;
	std::stringstream ss2;

	std::string level = "Level: ";
	ss<<current_level;
	level+=ss.str();
	ss.clear();
	char *cstr = new char[level.length() + 1];
	strcpy(cstr, level.c_str());
	text(-0.5,0.0,0.1,cstr,0);
	delete [] cstr;

	std::string moves="Moves: ";
		
	ss1 << MOVES;
	moves+=ss1.str();
	ss1.clear();
	cstr = new char[moves.length() + 1];
	strcpy(cstr, moves.c_str());
	text(-0.5,-0.15,0.1,cstr,0);
	delete [] cstr;

	std::string pushes="Pushes: ";
	ss2 << PUSHES;
	pushes+=ss2.str();
	ss2.clear();
	cstr = new char[pushes.length() + 1];
	strcpy(cstr, pushes.c_str());
	text(-0.5,-0.3,0.1,cstr,0);
	delete [] cstr;
	
	text(-0.5,-0.45,0.1,"Press any Key to continue",0);
	glPopMatrix();
}
void displayEnd()
{
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f); 
	glTranslatef(0,0,0);

	glViewport(WIDTH/20, HEIGHT-(HEIGHT/3), WIDTH-(WIDTH/8),HEIGHT/3 );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_DEPTH);

	glPopMatrix();
	glViewport(0, 0, WIDTH,HEIGHT );
	glPushMatrix();
	glColor3f(0,0,0);

	text(-0.5,0.0,0.1,"Congratulations",0);
	text(-0.5,-0.15,0.1,"You passed All Levels",0);


	glPopMatrix();
}
void display (void) {  
	if (WIDTH<640)
	{

		glutReshapeWindow(640,HEIGHT);
	}
	if (HEIGHT<480)
	{

		glutReshapeWindow(WIDTH,480);
	}
	
	
	glClearColor(0.95f, 0.95f, 0.95f, 1.0f);   
	glLoadIdentity();  
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	
	
	switch(game_state)
	{
		case GAME_MENU:
			displayMenu();
		break;
		case GAME_MENU_OPTIONS:
			displayMenuOptions();
			break;
		case GAME_MENU_CREDITS:
			displayMenuCredits();
			break;
	case GAME_RUNNING:
		displayGame();
		break;
	case GAME_SCORE:
			displayScore();
		break;
	case  GAME_END:
		displayEnd();
		break;
	case  GAME_SELECT_LEVEL:
		displayChooseLevel();
		break;
	default:std::cout<<"Error"<<std::endl;
		break;
	}

	
	
	glutSwapBuffers();
} 
void makeQuad() //make quad
{
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, 0.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f,  1.0f);
	glEnd();
}
void makeCube()
{
	glBegin(GL_QUADS);
	// Front Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, 0.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f,  1.0f,  1.0f);
	// Back Face
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f,  1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, 0.0f, -0.0f);
	// Top Face
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f,  1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, 0.0f);
	// Bottom Face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, 0.0f,  1.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f,  1.0f);
	// Right face
	glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, 0.0f,  1.0f);
	// Left Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f,  1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f,  1.0f,  1.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f,  1.0f, 0.0f);
	glEnd();
}
void drawCube(int x, int y, int z, BLOCK_TYPE bl)
{
	if (directionFlag)
	{
		colorPower-=0.05f;
		if (colorPower<200)
		{
			directionFlag=false;
		}
	}
	else
	{
		colorPower+=0.05f;
		if (colorPower>254)
		{
			directionFlag=true;
		}
	}
	

	glEnable(GL_TEXTURE_2D);
	glPushMatrix();
	glTranslatef(x,y,z);
	glColor3ub(255,255,255);

	switch (bl)
	{
	case WALL:
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		makeCube();
		break;
	case FLOOR:		
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		makeQuad();
		break;
	case FLOOR_X:
		glBindTexture(GL_TEXTURE_2D, texture[3]);
		makeQuad();
		break;
	case BOX:
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		makeCube();
		break;
	case BOX_OK:
		glColor3ub(colorPower,colorPower,colorPower);
		glBindTexture(GL_TEXTURE_2D, texture[5]);
		makeCube();
		
		break;
	case PLAYER:
		glColor3ub(colorPower,colorPower,colorPower);
		glBindTexture(GL_TEXTURE_2D, texture[6]);
		makeCube();
		break;
	default:
		break;
	}
	
	
	
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}
void drawMap()
{
	glTranslatef(-MAP_SIZE/2,0.f,-MAP_SIZE/2);
	for(int j = 0; j < MAP_SIZE; j++) {
		for(int i = 0; i < MAP_SIZE; i++) {
			if(map[j][i] != -1) //j=y i=x
				drawCube(i,0,j,(BLOCK_TYPE)map[j][i]); //x,y,z, x=i, y=0, z=j;
			
		}
	}
}
void drawPlayer()
{
	drawCube(player.x,0,player.y,PLAYER);
}
void drawBoxes()
{
	size_t s = boxes.size();
	for(size_t i = 0; i < s; i++)
	{
		if(boxes[i].state)
		drawCube(boxes[i].x,0,boxes[i].y,BOX_OK);
		else
		drawCube(boxes[i].x,0,boxes[i].y,BOX);
	}
		
	
}
static bool LevelCompleteCond() {
		size_t s = boxes.size();
		for(size_t i = 0; i < s; i++) {
			if(!boxes[i].state)
				return false;
		}

		return true; 
}
static bool LoadNextLevel(bool next) {
	if (next)
	{
		
		current_level++;
		MOVES=0;
		PUSHES=0;
		scale=0.0f;
		rotationx=360;
		rotationy=360;
		rotationz=360;
		
	}

		char file_name[256] = {0};
		_snprintf(file_name, sizeof(file_name) - 1, 
			"maps/%u.txt", current_level);

		boxes.clear();
		Konami.clear();
		return LoadMap(file_name);
}
bool LoadMap(const char *filename) {
		// -1 == 0xffffffff -> 0xff
		memset(map, 0xff, sizeof(map));

		FILE *f = fopen(filename, "r");
		if(!f) {
			fprintf(stderr, "error: could not open map file \"%s\"\n",
				filename);
			return false;
		}

		for(int j = 0; j < MAP_SIZE; j++) {
			char line[MAP_SIZE*2];
			fgets(line, sizeof(line), f);
			if(feof(f)) {
				fprintf(stderr, "error: unexpected end of file \"%s\"\n",
					filename);
				fclose(f);
				return false;
			}

			for(int i = 0; i < MAP_SIZE; i++) {
				switch(line[i]) {
				case ' ': map[j][i] = -1; break;
				case '#': map[j][i] = WALL; break;
				case '.': map[j][i] = FLOOR; break;
				case 'x': map[j][i] = FLOOR_X; break;
				case 'p': map[j][i] = FLOOR;
						  player.x=i;
						  player.y=j;
						  break;
				case 'o': boxes.push_back(Box::mk(i, j));
						  map[j][i] = FLOOR; break;
				default: map[j][i] = -1; break;
					
					fclose(f);
					return false;
				}
			}
		}

		printf("info: loaded map \"%s\"\n", filename);
		saveLoad();
		fclose(f);
		return true;
}
int getBox(int x, int y) {
	size_t s = boxes.size();
for(size_t i = 0; i < s; i++) 
{
	if(boxes[i].x == x && boxes[i].y == y)
		return i;
}

	return -1;
}

void movePlayer(int key,int x,int y)
{		int p_dx = 0; // player delta x,y
		int p_dy = 0;
	switch (game_state)
	{
	case GAME_MENU:
		switch (key)
		{

		case GLUT_KEY_UP:
			menu_chose1=(MENU_CHOSE1)(menu_chose1-1);
			if(systemFMOD->playSound(sound_push,channelEffects_move,false, &channel_move)!=FMOD_OK)
				fprintf(stderr, "error: FMOD Channel");
			break;
		case GLUT_KEY_DOWN:
			menu_chose1=(MENU_CHOSE1)(menu_chose1+1);
			if(systemFMOD->playSound(sound_push,channelEffects_move,false, &channel_move)!=FMOD_OK)
				fprintf(stderr, "error: FMOD Channel");
			break;
		default:
			break;
		}
		if (menu_chose1<0)
		{
			menu_chose1 = EXIT;
		}
		else if (menu_chose1>4)
		{
			menu_chose1 = CHOOSE;
		}
		break;
	case GAME_RUNNING:
		

		switch (key)
		{

		case GLUT_KEY_UP:
			p_dy-=1;
			Konami+="0";
			break;
		case GLUT_KEY_DOWN:
			p_dy+=1;
			Konami+="1";
			break;
		case GLUT_KEY_LEFT:
			p_dx-=1;
			Konami+="2";
			break;
		case GLUT_KEY_RIGHT:
			p_dx+=1;
			Konami+="3";
			break;
		default:
			break;
		}


		if(p_dx || p_dy) {

			int player_new_x = player.x + p_dx; // player new x,y
			int player_new_y = player.y + p_dy;

			bool player_move_ok = true;

			if(map[player_new_y][player_new_x] == WALL ||
				map[player_new_y][player_new_x] == -1) {
					player_move_ok = false;
			} else {
				int box_id = getBox(player_new_x, player_new_y);
				if(box_id != -1) {
					int box_new_x = player_new_x + p_dx; 
					int box_new_y = player_new_y + p_dy;

					bool box_move_ok = true;

					if(map[box_new_y][box_new_x] == WALL ||
						map[box_new_y][box_new_x] == -1) {
							box_move_ok = false;
					} else if(getBox(box_new_x, box_new_y) != -1) {
						box_move_ok = false;
					}

					if(!box_move_ok) {
						player_move_ok = false;
					} else {
						boxes[box_id].x = box_new_x;
						boxes[box_id].y = box_new_y;
						PUSHES++;
						if(systemFMOD->playSound(sound_push,channelEffects_push,false, &channel_push)!=FMOD_OK)
							fprintf(stderr, "error: FMOD Channel");
						music_push=true;
						boxes[box_id].state = (map[box_new_y][box_new_x] == FLOOR_X);

						if(boxes[box_id].state) {
							// Is level complete?
							if(LevelCompleteCond()) {
								win=true;

								return;

							}
						}
					}
				}
			}

			if(player_move_ok) {

				if (!music_push)
				{
					if(systemFMOD->playSound(sound_move,channelEffects_move,false, &channel_move)!=FMOD_OK)
						fprintf(stderr, "error: FMOD Channel");
				}
															   music_push=false;
				player.x = player_new_x;
				player.y = player_new_y;
				MOVES++;
			}
		}

		glutPostRedisplay();
		break;
	case GAME_SCORE:
		break;
	case GAME_END:
		break;
	case GAME_MENU_CREDITS:
		break;
	case GAME_MENU_OPTIONS:
		switch (key)
		{

		case GLUT_KEY_UP:
			menu_chose_options=(MENU_CHOSE_OPTIONS)(menu_chose_options-1);
			if(systemFMOD->playSound(sound_push,channelEffects_move,false, &channel_move)!=FMOD_OK)
				fprintf(stderr, "error: FMOD Channel");
			break;
		case GLUT_KEY_DOWN:
			menu_chose_options=(MENU_CHOSE_OPTIONS)(menu_chose_options+1);
			if(systemFMOD->playSound(sound_push,channelEffects_move,false, &channel_move)!=FMOD_OK)
				fprintf(stderr, "error: FMOD Channel");
			break;
		default:
			break;
		}
		if (menu_chose_options<0)
		{
			menu_chose_options = MCO_EXIT;
		}
		else if (menu_chose_options>2)
		{
			menu_chose_options = MCO_FULL;
		}
		break;
	case GAME_SELECT_LEVEL:
		switch (key)
		{

		case GLUT_KEY_UP:
			choosed_level--;
			if(systemFMOD->playSound(sound_push,channelEffects_move,false, &channel_move)!=FMOD_OK)
				fprintf(stderr, "error: FMOD Channel");
			break;
		case GLUT_KEY_DOWN:
			choosed_level++;
			if(systemFMOD->playSound(sound_push,channelEffects_move,false, &channel_move)!=FMOD_OK)
				fprintf(stderr, "error: FMOD Channel");
			break;
			
		default:
			break;
		}
		if (choosed_level<1)
		{
			choosed_level = 1;
		}
		else if (choosed_level>levels_avaible)
		{
			choosed_level = levels_avaible;
		}
		break;
	default:
		break;
	}
	
}
void reshape (int w, int h) { 
	
	WIDTH=w;
	HEIGHT=h;
}  
void keyPressed (unsigned char key, int x, int y) {
	

	
	switch (game_state)
	{
	case GAME_MENU:
		switch (key)
		{
		case 13: 
			switch (menu_chose1)
			{
			case CHOOSE:
				choosed_level=levels_avaible;
				game_state=GAME_SELECT_LEVEL;
				break;
			case START:	 current_level=1;
				MOVES=0;
				PUSHES=0;
				scale=0.0f;
				rotationx=360;
				rotationy=360;
				rotationz=360;
				LoadNextLevel(false);
				game_state = GAME_RUNNING;
				break;
			case OPTIONS:  game_state=GAME_MENU_OPTIONS;
				break;
			case CREDITS: game_state=GAME_MENU_CREDITS;
				break;
			case EXIT:	exit_game();
				break;
			default:
				break;
			}
			
			break;
		case 'o': game_state=GAME_MENU_OPTIONS;
			break;
		case 'c': game_state=GAME_MENU_CREDITS;
			break;
	
		case 27:

			exit_game();
			break;
		default:
			break;
		}
		break;
	case GAME_MENU_OPTIONS:
		switch (key)
		{
		
		case 27:
			game_state=GAME_MENU;
			break;
		case 'f': glutFullScreen();
			break;
		case 'w': glutReshapeWindow(800,600);
		case 13:
			switch (menu_chose_options)
			{
			case MCO_FULL:	 glutFullScreen();
				break;
			case MCO_WINDOWED:  glutReshapeWindow(800,600);
				break;
			case MCO_EXIT:	game_state=GAME_MENU;
				break;
			default:
				break;
			}
			
		default:
			break;
		}
		break;
		case GAME_SELECT_LEVEL:
			switch (key)
			{

			case 27:
				game_state=GAME_MENU;
				break;
			case 13:
				current_level=choosed_level;
				MOVES=0;
				PUSHES=0;
				scale=0.0f;
				rotationx=360;
				rotationy=360;
				rotationz=360;
				LoadNextLevel(false);
				game_state = GAME_RUNNING;
				break;
		default:
			break;
		}
		
		break;
	case GAME_MENU_CREDITS:
		switch (key)
		{

		case 27:
			game_state=GAME_MENU;
			break;
		default:
			break;
		}
	case GAME_RUNNING:
		switch (key)
		{
		case ' ':LoadNextLevel(false);
			break;
		case 'A':Konami+="5";
			break;
		case 'B':Konami+="4";
			break;
		case 'a':Konami+="5";
			break;
		case 'b':Konami+="4";
			break;
		case 27: game_state=GAME_MENU;
		default:
			break;
		}
		break;
	case GAME_SCORE:
		game_state=GAME_RUNNING;
		if (!LoadNextLevel(true))
		{
			game_state = GAME_END;
		} 
		break;
	case GAME_END:
		exit_game();
		break;
	}

	glutPostRedisplay();


}  
void timer(int extra)
{
	if (Konami=="0011232345")
	{
		
		if (!LoadNextLevel(true))
		{
			game_state = GAME_END;
		} 
	}
	else if(Konami.size()>10)
		Konami.clear(); 

	   
	glutPostRedisplay();
	glutTimerFunc(33, timer, 0);
}
void sound_init()
{
	if(FMOD::System_Create(&systemFMOD)!= FMOD_OK )
		fprintf(stderr, "error: FMOD not loaded");

	if(systemFMOD->init(10, FMOD_INIT_NORMAL,NULL)!=FMOD_OK)
		fprintf(stderr, "error: FMOD init");

	if(systemFMOD->createSound("sounds/powerup5.wav", FMOD_DEFAULT, 0, &sound_move)!=FMOD_OK)
		fprintf(stderr, "error: FMOD Sound");

	systemFMOD->createChannelGroup(NULL, &channelEffects_move);
	systemFMOD->createChannelGroup(NULL, &channelEffects_push);

	if(systemFMOD->createSound("sounds/jump3.wav", FMOD_DEFAULT, 0, &sound_push)!=FMOD_OK)
		fprintf(stderr, "error: FMOD Sound");

								   
	if(systemFMOD->createSound("sounds/background.wav", FMOD_DEFAULT, 0, &music_background)!=FMOD_OK)
		fprintf(stderr, "error: FMOD Sound");
	systemFMOD->createChannelGroup(NULL, &channelEffects_bg);
	  music_background->setMode(FMOD_LOOP_NORMAL);
									
	if(systemFMOD->playSound(music_background,channelEffects_bg,false, &channel_background)!=FMOD_OK)
		fprintf(stderr, "error: FMOD Channel");
	
}

//int main(int argc, char **argv) 
int main(int argc, char **argv)
{//int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
	//{
		//int argc = 0;
		//QApplication app( argc, 0 );
	FreeConsole();
	sound_init();
	
	
	
	glutInit(&argc, argv);
	
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); 
	
	glutInitWindowSize (800, 600); 
	glutCreateWindow ("Sokoban3D");  
	
	if (!LoadGLTextures())
	{
		exit(1);									
	}
	if (!LoadNextLevel(true))
	{
		exit(1);
	}	
	glClearDepth(1.0f);		
	glShadeModel(GL_SMOOTH);	
	glEnable(GL_DEPTH_TEST);							
	glDepthFunc(GL_LEQUAL);	
	glEnable(GL_POLYGON_SMOOTH);
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape); 
	glutSpecialFunc(movePlayer);
	glutKeyboardFunc(keyPressed);

	glutTimerFunc(0, timer, 0);
	glutMainLoop();
	
}  