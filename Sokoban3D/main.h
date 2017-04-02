enum BLOCK_TYPE
{
	WALL=1,FLOOR=2,FLOOR_X=3,BOX=4,BOX_OK=5,PLAYER=6
};
enum GAME_STATE
{
	GAME_MENU,GAME_RUNNING,GAME_SCORE,GAME_END,GAME_MENU_CREDITS,GAME_MENU_OPTIONS,GAME_SELECT_LEVEL
};
GAME_STATE game_state=GAME_MENU;
struct Player
{
	int x;
	int y;
}; 
Player player;
struct Box
{
	int x;
	int y;
	bool state;
	static struct Box mk(int x, int y) {
		Box s = { x, y, false };
		return s;
	}
};
void drawCube(int x, int y, int z, BLOCK_TYPE bl);
void drawMap();
void drawPlayer();
void drawBoxes();
bool LoadMap(const char *filename);
void showScore();
void showRotation();
int LoadGLTextures();
void displayString();
void display (void);
void makeQuad();
void makeCube();
static bool LevelCompleteCond();
static bool LoadNextLevel(bool next);
int getBox(int x, int y);
void movePlayer(int key,int x,int y);
void reshape (int w, int h);
void keyPressed (unsigned char key, int x, int y);
void timer(int extra);
void drawLogo();
#define MAP_SIZE 16
int map[MAP_SIZE][MAP_SIZE];
bool music_push=false;
enum MENU_CHOSE1 {
	CHOOSE=0,START=1,OPTIONS=2,CREDITS=3,EXIT=4

};
MENU_CHOSE1 menu_chose1 = CHOOSE;
enum MENU_CHOSE_OPTIONS{
	MCO_FULL=0,MCO_WINDOWED=1,MCO_EXIT=2
};
MENU_CHOSE_OPTIONS menu_chose_options=MCO_FULL;
std::string Konami="";
int levels_avaible=1;
int choosed_level=1;
float logoz=0;
float logox=0;
float logoy=0;
float counterx=0;
float countery=0;
float logoscale=2;
bool win=false;
FMOD::System *systemFMOD;

FMOD::Channel *channel_move;
FMOD::Sound *sound_move;
FMOD::ChannelGroup *channelEffects_move;

FMOD::Channel *channel_background;
FMOD::Sound *music_background;
FMOD::ChannelGroup *channelEffects_bg;

FMOD::Channel *channel_push;
FMOD::Sound *sound_push;
FMOD::ChannelGroup *channelEffects_push;

GLuint	texture[8];
unsigned int current_level = 0;
bool End=false;
float ex=4,ey=15,ez=8,cx=0.5,cy=0.5,cz=0.5,ux=0,uy=1,uz=0;
int WIDTH=0,HEIGHT=0;
std::vector<Box> boxes;
std::string lvl ="level: ";
std::string moves ="moves: ";
std::string pushes ="pushes: ";
int MOVES=0;
int PUSHES=0;
float scale=0.0f;
float rotationx=360;
float rotationy=360;
float rotationz=360;
bool show_score=false;
float colorPower=255.0f;
bool directionFlag=true;
float rotation_last_x=0;
float rotation_last_y=0;
float rotation_last_z=0;
