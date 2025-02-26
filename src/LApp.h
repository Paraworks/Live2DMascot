#pragma once
#include "glwidget.h"
#include <QtCore/qtextcodec.h>
#include <QtWidgets/qapplication.h>

void Log(const char* handler, const char* msg);

namespace LAppConfig {

	extern int _WindowWidth;
	extern int _WindowHeight;
	extern int _LastPosX;
	extern int _LastPosY;
	extern int _FPS;
	extern string _AppName;
	extern string _IconPath;
	extern string _ModelName;
	extern string _ModelDir;
	extern bool _KeepQuiet;
	extern bool _MouseTrack;
	extern bool _StayOnTop;
	extern bool _NoSound;
	extern bool _ShowText;
	extern bool _ShowBgmList;
	extern const char* _ConfigPath;
	extern int _DialogFontSize;
	extern string _DialogFontFamily;
	extern string _DialogFontColor;
	extern string _DialogBackgroundColor;
	extern int _TextFadeOutTime;
	extern int _BgmListLastPosX;
	extern int _BgmListLastPosY;
	extern float _LipSyncMagnification;
	extern string _NoteOutPath;
	extern string _ApiKey;
	extern string _ApiSecret;
	extern float _MotionInterval;
	extern string _UserName;
	extern bool _ShowBackground;
	extern bool _TransparentBackground;
	extern bool _MouseOn;
	extern bool _TransparentCharacter;
	extern int _DialogYOffset;
	extern int _DialogMaxWidth;
	extern int _DialogXPadding;
	extern int _DialogYPadding;
};

class LApp
{
private:
	QApplication* _app;
	GLWidget* _win;
public:
	LApp();
	~LApp();
	static LApp* GetInstance();
	void SaveConfig();
	static void Warning(const char* x);
	void Initialize(int argc, char* argv[]);
	void Run();
	void Release();
	void LoadConfig();
	QApplication* GetApp();
	GLWidget* GetWindow();
};