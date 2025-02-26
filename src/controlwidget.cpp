#include "LAppModel.hpp"
#include "controlwidget.h"
#include "LApp.h"
#include <fstream>
#include <vector>
#include <io.h>
#include <QtWidgets/qtabbar.h>
#include <QtCore/qregexp.h>
#include <QtGui/qpainter.h>
#include <QtGui/qvalidator.h>
#include <QtWidgets/qfiledialog.h>
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qtreewidget.h>
#include <QtWidgets/qheaderview.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qlistview.h>
#include "LAppLive2DManager.hpp"

using namespace LAppConfig;

class Tip : public QWidget
{
public:
	Tip();
	void Pop(QWidget* p, const char* text);
	static Tip* GetInstance();
protected:
	void paintEvent(QPaintEvent* e);
	const char* text = NULL;
	QPropertyAnimation* anime;
};

namespace {
	Tip* _tip = NULL;
}

Tip::Tip()
{
	resize(100, 40);
	setAttribute(Qt::WA_TransparentForMouseEvents);
	setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
	anime = new QPropertyAnimation(this, "windowOpacity");
	anime->setStartValue(1);
	anime->setEndValue(0);
	anime->setDuration(2000);
}
void Tip::paintEvent(QPaintEvent* e)
{
	resize(strlen(text) * 7 + 30, 40);
	QPainter painter(this);
	painter.fillRect(0, 0, width(), 40, QColor(0, 0, 0, 180));
	painter.setPen(Qt::white);
	painter.drawText(15, 25, QString::fromLocal8Bit(text).toStdString().c_str());
}
void Tip::Pop(QWidget* p, const char* text)
{
	close();
	this->text = text;
	anime->stop();
	move(p->x() + p->width() / 2 - width()/2, p->y() + 20);
	show();
	anime->start();
}
Tip* Tip::GetInstance()
{
	if (_tip == NULL) _tip = new Tip();
	return _tip;
}


void getDirNames(string path, vector<string>& files)
{
	//文件句柄
#ifdef WIN64_FLAG
	__int64   hFile = 0;
#else
	long	hFile = 0;
#endif // WIN64_FLAG

	//文件信息
#ifdef WIN64_FLAG
	struct __finddata64_t fileinfo;
#else
	struct _finddata_t fileinfo;
#endif // WIN64_FLAG

	string p;
	if (
#ifdef WIN64_FLAG
	(hFile = _findfirst64(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1L
#else
	(hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1
#endif // WIN64_FLAG
		)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				string x = fileinfo.name;
				if (strcmp(x.c_str(), ".") != 0 && strcmp(x.c_str(), "..") != 0)
				{
					files.push_back(string(fileinfo.name));
				}
			}
		} while (
#ifdef WIN64_FLAG
			_findnext64(hFile, &fileinfo) == 0
#else
			_findnext(hFile, &fileinfo) == 0
#endif // WIN64_FLAG

			);
		_findclose(hFile);
	}
}




void getFileNames(string path, vector<string>& files)
{
	//文件句柄
#ifdef WIN64_FLAG
	__int64   hFile = 0;
	struct __finddata64_t fileinfo;
#else
	long   hFile = 0;
	struct _finddata_t fileinfo;
#endif // WIN64_FLAG

	//文件信息
	string p;
	if (
#ifdef WIN64_FLAG
	(hFile = _findfirst64(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1L
#else
	(hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1
#endif // WIN64_FLAG
		)
	{
		do
		{
			if (!(fileinfo.attrib & _A_SUBDIR))
			{
				files.push_back(string(fileinfo.name));
			}
		} while (
#ifdef WIN64_FLAG
			_findnext64(hFile, &fileinfo) == 0
#else
			_findnext(hFile, &fileinfo) == 0
#endif // WIN64_FLAG
			);
		_findclose(hFile);
	}
}


AppSettings::AppSettings(QWidget* p)
{
	_parent = p;
	lbl_appName = new QLabel(QString::fromLocal8Bit("应用名称"));
	lbl_username = new QLabel(QString::fromLocal8Bit("用户名称"));
	lbl_iconPath = new QLabel(QString::fromLocal8Bit("托盘图标"));
	lbl_FPS = new QLabel("FPS");
	lbl_appKey = new QLabel(QString::fromLocal8Bit("Key"));
	lbl_appSecret = new QLabel(QString::fromLocal8Bit("Secret"));
	lbl_windowWidth = new QLabel(QString::fromLocal8Bit("窗口宽度"));
	lbl_windowHeight = new QLabel(QString::fromLocal8Bit("窗口高度"));
	lbl_modelDir = new QLabel(QString::fromLocal8Bit("模型路径"));
	appName = new QLineEdit();
	username = new QLineEdit();
	iconPath = new QLineEdit();
	appKey = new QLineEdit();
	appSecret = new QLineEdit();
	fps = new QLineEdit();
	windowWidth = new QLineEdit();
	windowHeight = new QLineEdit();
	modelDir = new QLineEdit();

	lbl_lipsync = new QLabel(QString::fromLocal8Bit("口型同步"));
	lipSync = new QLineEdit();
	QRegExpValidator* v3 = new QRegExpValidator(QRegExp("^[0-9]{1,2}\\.[0-9]{1}$"));
	lipSync->setValidator(v3);

	lbl_motioninterval = new QLabel(QString::fromLocal8Bit("动作频率"));
	motionInterval = new QLineEdit();
	motionInterval->setValidator(v3);

	/*appName->setFixedHeight(30);
	username->setFixedHeight(30);
	iconPath->setFixedHeight(30);
	appKey->setFixedHeight(30);
	appSecret->setFixedHeight(30);
	fps->setFixedHeight(30);
	windowWidth->setFixedHeight(30);
	windowHeight->setFixedHeight(30);
	modelDir->setFixedHeight(30);*/

	windowWidth->setFixedWidth(50);
	windowHeight->setFixedWidth(50);
	lipSync->setFixedWidth(50);
	motionInterval->setFixedWidth(50);


	const QValidator* v = new QRegExpValidator(QRegExp("[0-9]{1,2}"));
	fps->setValidator(v);
	const QValidator* v2 = new QRegExpValidator(QRegExp("[0-9]{1,4}"));
	windowWidth->setValidator(v2);
	windowHeight->setValidator(v2);

	openFile = new QPushButton(QString::fromLocal8Bit("打开"));
	chooseDir = new QPushButton(QString::fromLocal8Bit("打开"));
	apply = new QPushButton(QString::fromLocal8Bit("应用"));
	cancel = new QPushButton(QString::fromLocal8Bit("重置"));

	grid = new QGridLayout();

	grid->addWidget(lbl_appName, 0, 0, 0);
	grid->addWidget(appName, 0, 1, 1, 4, 0);
	grid->addWidget(lbl_username, 0, 5, 0);
	grid->addWidget(username, 0, 6, 1, 4, 0);
	grid->addWidget(lbl_iconPath, 2, 0, 0);
	grid->addWidget(iconPath, 2, 1, 1, 8, 0);
	grid->addWidget(openFile, 2, 9, 0);
	grid->addWidget(lbl_modelDir, 3, 0, 1, 1, 0);
	grid->addWidget(modelDir, 3, 1, 1, 8, 0);
	grid->addWidget(chooseDir, 3, 9, 1, 1, 0);
	grid->addWidget(lbl_lipsync, 4, 0, 1, 1, 0);
	grid->addWidget(lipSync, 4, 1, 1, 1, 0);
	grid->addWidget(lbl_motioninterval, 4, 2, 1, 1, 0);
	grid->addWidget(motionInterval, 4, 3, 1, 1, 0);
	grid->addWidget(lbl_FPS, 4, 4, 0);
	grid->addWidget(fps, 4, 5, 1, 1, 0);
	grid->addWidget(lbl_windowWidth, 4, 6, 1, 1, 0);
	grid->addWidget(windowWidth, 4, 7, 1, 1, 0);
	grid->addWidget(lbl_windowHeight, 4, 8, 1, 1, 0);
	grid->addWidget(windowHeight, 4, 9, 1, 1, 0);
	grid->addWidget(lbl_appKey, 5, 0, 0);
	grid->addWidget(appKey, 5, 1, 1, 4, 0);
	grid->addWidget(lbl_appSecret, 6, 0, 0);
	grid->addWidget(appSecret, 6, 1, 1, 4, 0);
	grid->addWidget(apply, 7, 6, 1, 2, 0);
	grid->addWidget(cancel, 7, 8, 1, 2, 0);
	setLayout(grid);
	
	connect(openFile, SIGNAL(clicked()), SLOT(OpenFile()));
	connect(chooseDir, SIGNAL(clicked()), SLOT(OpenSourceDir()));

	connect(apply, SIGNAL(clicked()), SLOT(Apply()));
	connect(cancel, SIGNAL(clicked()), SLOT(Cancel()));
}

void AppSettings::OpenFile()
{
	QString path = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择图标路径"), iconPath->text(), "Image File(*.jpg *.png);;");
	if (!path.isEmpty())
	iconPath->setText(path);
}

void AppSettings::OpenSourceDir()
{
	QString path = QFileDialog::getExistingDirectory(this, QString::fromLocal8Bit("选择资源文件夹"), modelDir->text());
	if (!path.isEmpty())
		modelDir->setText(path);
}

void AppSettings::Apply()
{
	_AppName = appName->text().toUtf8().toStdString();
	_UserName = username->text().toUtf8().toStdString();
	_IconPath = iconPath->text().toUtf8().toStdString();
	_ApiKey = appKey->text().toUtf8().toStdString();
	_ApiSecret = appSecret->text().toUtf8().toStdString();
	_FPS = fps->text().toInt() == 0? _FPS : fps->text().toInt();
	_WindowWidth = windowWidth->text().toInt() == 0 ? _WindowWidth : windowWidth->text().toInt();
	_WindowHeight = windowHeight->text().toInt() == 0 ? _WindowHeight : windowHeight->text().toInt();
	_ModelDir = modelDir->text().isEmpty() ? _ModelDir : modelDir->text().toUtf8().toStdString();
	_MotionInterval = motionInterval->text().isEmpty() ? _MotionInterval : motionInterval->text().toFloat();
	_LipSyncMagnification = lipSync->text().isEmpty() ? _LipSyncMagnification : lipSync->text().toFloat();
	LApp::GetInstance()->GetWindow()->LoadConfig();
	_parent->setWindowTitle(QString::fromUtf8(_AppName.c_str()));
	LoadConfig();
	ControlWidget* p = static_cast<ControlWidget*>(_parent);
	try {
		if (p) {			
			p->_modelSettings->LoadConfig();
			Log("ModelDir changed", modelDir->text().toLocal8Bit());
		}
		else Log("AppSettings", "cast failed");
		LApp::GetInstance()->SaveConfig();
		Tip::GetInstance()->Pop(_parent, "保存成功!");
	}
	catch (exception e)
	{
		Tip::GetInstance()->Pop(_parent, "资源路径有误!");
		LApp::GetInstance()->LoadConfig();
		LoadConfig();
		p->_modelSettings->LoadConfig();
	}
}
void AppSettings::Cancel()
{
	LoadConfig();
}
void AppSettings::LoadConfig()
{
	appName->setText(QString::fromUtf8(_AppName.c_str()));
	username->setText(QString::fromUtf8(_UserName.c_str()));
	iconPath->setText(QString::fromUtf8(_IconPath.c_str()));
	fps->setText(to_string(_FPS).c_str());
	appKey->setText(QString::fromUtf8(_ApiKey.c_str()));
	appSecret->setText(QString::fromUtf8(_ApiSecret.c_str()));
	windowWidth->setText(to_string(_WindowWidth).c_str());
	windowHeight->setText(to_string(_WindowHeight).c_str());
	modelDir->setText(QString::fromUtf8(_ModelDir.c_str()));
	stringstream ss1;
	ss1 << _MotionInterval;
	motionInterval->setText(ss1.str().c_str());
	stringstream ss2;
	ss2 << _LipSyncMagnification;
	lipSync->setText(ss2.str().c_str());
}

ModelSettings::ModelSettings(QWidget* p)
{
	_parent = p;
	model = new QComboBox();
	lbl_model = new QLabel(QString::fromLocal8Bit("选择模型"));
	_motionGroups = new QTreeWidget();

	_motionGroups->setHeaderLabel(QString::fromLocal8Bit("动作组"));
	apply = new QPushButton(QString::fromLocal8Bit("保存"));
	cancel = new QPushButton(QString::fromLocal8Bit("重置"));

	motionJsonPath = new QComboBox();
	motionSoundPath = new QComboBox();
	motionText = new MyText();

	lbl_motionJsonPath = new QLabel(QString::fromLocal8Bit("动作路径"));
	lbl_motionJsonPath->setAlignment(Qt::AlignRight|Qt::AlignCenter);
	lbl_motionSoundPath = new QLabel(QString::fromLocal8Bit("语音"));
	lbl_motionSoundPath->setAlignment(Qt::AlignRight|Qt::AlignCenter);
	lbl_motionText = new QLabel(QString::fromLocal8Bit("文本"));
	lbl_motionText->setAlignment(Qt::AlignTop|Qt::AlignRight);
	motionGroup = new QLineEdit();
	addGroup = new QPushButton(QString::fromLocal8Bit("新建动作组"));
	deleteGroup = new QPushButton(QString::fromLocal8Bit("删除动作组"));
	lbl_motionGroup = new QLabel(QString::fromLocal8Bit("当前动作组"));
	addMotion = new QPushButton(QString::fromLocal8Bit("添加动作"));
	deleteMotion = new QPushButton(QString::fromLocal8Bit("删除动作"));
	changeModel = new QPushButton(QString::fromLocal8Bit("更新模型"));
	updateGroupName = new QPushButton(QString::fromLocal8Bit("修改动作组名称"));
	
	connect(apply, SIGNAL(clicked()), SLOT(Apply()));
	connect(cancel, SIGNAL(clicked()), SLOT(Cancel()));
	grid = new QGridLayout();
	grid->addWidget(lbl_model, 0, 0, 0);
	grid->addWidget(model, 0, 1, 0);
	grid->addWidget(changeModel, 0, 2, 0);
	grid->addWidget(lbl_motionGroup, 1, 0, 0);
	grid->addWidget(motionGroup, 1, 1, 0);
	grid->addWidget(addGroup, 1, 2, 0);
	grid->addWidget(deleteGroup, 1, 3, 0);
	grid->addWidget(updateGroupName, 1, 4, 0);
	grid->addWidget(_motionGroups, 2, 0, 3, 2, 0);
	grid->addWidget(motionJsonPath, 2, 3, 1, 2, 0);
	grid->addWidget(motionSoundPath, 3, 3, 1, 2, 0);
	grid->addWidget(motionText, 4, 3, 1, 2, 0);
	grid->addWidget(lbl_motionJsonPath, 2, 2, 0);
	grid->addWidget(lbl_motionSoundPath, 3, 2, 0);
	grid->addWidget(lbl_motionText, 4, 2, 0);
	grid->addWidget(addMotion, 5, 0, 0);
	grid->addWidget(deleteMotion, 5, 1, 0);
	grid->addWidget(apply, 5, 3, 0);
	grid->addWidget(cancel, 5, 4, 0);
	setLayout(grid);

	connect(_motionGroups, SIGNAL(itemClicked(QTreeWidgetItem*, int)), SLOT(ShowMotionInfo(QTreeWidgetItem*, int)));
	connect(_motionGroups, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), SLOT(StartMotion(QTreeWidgetItem*, int)));
	connect(addMotion, SIGNAL(clicked()), SLOT(AddMotion()));
	connect(deleteMotion, SIGNAL(clicked()), SLOT(DeleteMotion()));
	connect(motionJsonPath, SIGNAL(currentTextChanged(const QString&)), SLOT(BindMotion(const QString&)));
	connect(motionSoundPath, SIGNAL(currentTextChanged(const QString&)), SLOT(BindSound(const QString&)));
	connect(motionText, SIGNAL(loseFocus()), SLOT(BindText()));
	
	connect(addGroup, SIGNAL(clicked()), SLOT(AddGroup()));
	connect(deleteGroup, SIGNAL(clicked()), SLOT(DeleteGroup()));
	connect(updateGroupName, SIGNAL(clicked()), SLOT(UpdateGroupName()));

	connect(changeModel, SIGNAL(clicked()), SLOT(UpdateModel()));

	_motionGroups->setStyleSheet(
		QString("QScrollBar:vertical{width: 8px;background: #DDD;border: none}"
			"QTreeWidget::branch::open:has-children{border-image: url(").append(_ModelDir.c_str()).append("/open.png); }"
			"QScrollBar::handle:vertical{background: #AAA;}"
			"QScrollBar::handle:vertical:hover{background: #888;}"
			"QHeaderView::section{background-color: rgb(50, 50, 50); color: rgba(255, 255, 255, 210); height: 30px; font-family: 微软雅黑; border: none; padding-left: 10px}")
		);
	const char* styleSheet = ("QComboBox QAbstractItemView {color: rgba(255, 255, 255, 210); outline: none; background: rgb(100, 100, 100)}"
		"QComboBox{selection-background-color: rgb(50, 50, 50); padding-left: 5px}"
		"QScrollBar::vertical{width: 10px; background: #d0d2d4}"
		"QScrollBar::handle:vertical{background: rgb(160, 160, 160)}"
		);
	model->setStyleSheet(styleSheet);
	motionJsonPath->setStyleSheet(styleSheet);
	motionSoundPath->setStyleSheet(styleSheet);
	model->setView(new QListView());
	motionJsonPath->setView(new QListView());
	motionSoundPath->setView(new QListView());

}

void ModelSettings::Apply()
{
	if (QMessageBox::question(_parent, QString::fromLocal8Bit("保存配置"), QString::fromLocal8Bit("是否保存配置?"), QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
	{
		//中文支持
		const char* path = QString::fromUtf8(string(_ModelDir).append("/").append(_ModelName).append("/").append(_ModelName).append(".model3.json").c_str()).toLocal8Bit();

		Log("Save ModelJson", path);
		ofstream ofs(path);
		ofs << _modelJson;
		ofs.close();
		LoadConfig();
		LAppLive2DManager::GetInstance()->ChangeModel(_ModelDir.c_str(), _ModelName.c_str());
		Tip::GetInstance()->Pop(_parent, "操作成功!");
	}
	
}

void ModelSettings::Cancel()
{
	LoadConfig();
}

void ModelSettings::LoadConfig()
{
	_motionGroups->clear();
	motionJsonPath->clear();
	motionSoundPath->clear();
	motionText->clear();
	motionGroup->clear();
	int i;
	int size;
	const char* path;
	vector<std::string> _files;
	bool flag = false;
	path = QString::fromUtf8(_ModelDir.c_str()).toLocal8Bit().constData();
	Log("Load ModelDir", path);
	getDirNames(path, _files);
	size = _files.size();
	model->clear();
	for (i = 0; i < size; i++)
	{
		if (strcmp(_ModelName.c_str(), QString::fromLocal8Bit(_files[i].c_str()).toStdString().c_str()) == 0) flag = true;
		model->addItem(QString::fromLocal8Bit(_files[i].c_str()));
	}
	_ModelName = flag ? _ModelName : model->itemText(0).toUtf8().constData();
	model->setCurrentText(_ModelName.c_str());
	motionJsonPath->clear();
	_files.clear();

	path = QString::fromUtf8(string(_ModelDir).append("/").append(_ModelName).append("/").append("motions").c_str()).toLocal8Bit().constData();
	Log("Load MotionJsonDir", path);

	getFileNames(path, _files);
	size = _files.size();
	for (i = 0; i < size; i++)
	{
		motionJsonPath->addItem(QString::fromLocal8Bit(string("motions/").append(_files[i]).c_str()));
	}
	motionSoundPath->clear();
	motionJsonPath->addItem("");
	motionJsonPath->setCurrentText("");
	_files.clear();

	path = QString::fromUtf8(string(_ModelDir).append("/").append(_ModelName).append("/").append("sounds").c_str()).toLocal8Bit().constData();
	Log("Load motionSoundDir", path);
	getFileNames(path, _files);
	size = _files.size();
	for (i = 0; i < size; i++)
	{
		motionSoundPath->addItem(QString::fromLocal8Bit(string("sounds/").append(_files[i]).c_str()));
	}
	motionSoundPath->addItem("");
	motionSoundPath->setCurrentText("");


	path = QString::fromUtf8(string(_ModelDir).append("/").append(_ModelName).append("/").append(_ModelName).append(".model3.json").c_str()).toLocal8Bit();
	Log("Load ModelJson", path);

	ifstream ifs(path);
	ifs >> _modelJson;
	ifs.close();
	Json::Value motions = _modelJson["FileReferences"]["Motions"];
	Json::Value::Members groupnames = motions.getMemberNames();
	size = groupnames.size();
	QTreeWidgetItem* item;
	QTreeWidgetItem* subItem;
	int j;
	int size2;
	for (i = 0; i < size; i++)
	{
		item = new QTreeWidgetItem();
		_motionGroups->addTopLevelItem(item);
		Json::Value motionGroups = motions[groupnames[i]];
		item->setText(0, QString::fromUtf8(groupnames[i].c_str()));
		size2 = motionGroups.size();

		for (j = 0; j < size2; j++)
		{
			subItem = new QTreeWidgetItem();
			subItem->setText(0, QString::fromUtf8(groupnames[i].c_str()).append("_").append(to_string(j).c_str()));
			subItem->setData(1, 0, j);
			item->addChild(subItem);
		}
	}
	
}

void ModelSettings::BindMotion(const QString& x)
{
	QTreeWidgetItem* cur = _motionGroups->currentItem();
	if (cur != NULL && cur->parent() != NULL)
	{
		const char* path = QString::fromUtf8(string(_ModelDir).append("/").append(_ModelName).append("/").append(motionJsonPath->currentText().toStdString()).c_str()).toLocal8Bit();
		if (_access(path, 0) != -1)
		{
			_modelJson["FileReferences"]["Motions"][cur->parent()->text(0).toStdString()][cur->parent()->indexOfChild(cur)]["File"] = motionJsonPath->currentText().toStdString();
			if (!motionJsonPath->currentText().isEmpty())
			{
				Tip::GetInstance()->Pop(_parent, "动作已更换!");
			}
			else {
				Tip::GetInstance()->Pop(_parent, "动作已清空!");
			}
		}
		else Tip::GetInstance()->Pop(_parent, "动作文件不存在!");
	}
}

void ModelSettings::BindSound(const QString& x)
{
	QTreeWidgetItem* cur = _motionGroups->currentItem();
	if (cur != NULL && cur->parent() != NULL)
	{
		const char* path = QString::fromUtf8(string(_ModelDir).append("/").append(_ModelName).append("/").append(motionSoundPath->currentText().toLocal8Bit().constData()).c_str()).toLocal8Bit();
		if (_access(path, 0) != -1)
		{
			_modelJson["FileReferences"]["Motions"][cur->parent()->text(0).toStdString()][cur->parent()->indexOfChild(cur)]["Sound"] = motionSoundPath->currentText().toStdString();
			if (!motionSoundPath->currentText().isEmpty())
			{
				Tip::GetInstance()->Pop(_parent, "语音已更换!");
			}
			else {
				Tip::GetInstance()->Pop(_parent, "语音已清空!");
			}
		}
		else {
			Tip::GetInstance()->Pop(_parent, "音频文件不存在!");
		}
	}
		
}

void ModelSettings::BindText()
{
	QTreeWidgetItem* cur = _motionGroups->currentItem();
	if (cur != NULL && cur->parent() != NULL)
	{
		_modelJson["FileReferences"]["Motions"][cur->parent()->text(0).toStdString()][cur->parent()->indexOfChild(cur)]["Text"] = motionText->toPlainText().toStdString();
		if (!motionText->toPlainText().isEmpty())
		{
			Tip::GetInstance()->Pop(_parent, "文本已修改!");
		}
		else {
			Tip::GetInstance()->Pop(_parent, "文本已清空!");
		}
	}
}

void ModelSettings::AddMotion()
{
	if (_motionGroups->currentItem() == NULL)  //无选中
	{
		Tip::GetInstance()->Pop(_parent, "未选择动作组!");
	}
	else if (_motionGroups->currentItem()->parent() == NULL)  //选中整个动作组
	{
		Json::Value motion;
		motion["File"] = "";
		motion["Sound"] = "";
		motion["Text"] = "";
		_modelJson["FileReferences"]["Motions"][_motionGroups->currentItem()->text(0).toStdString()].append(motion);

		int idx = _motionGroups->currentItem()->childCount();
		QTreeWidgetItem* subItem = new QTreeWidgetItem();
		subItem->setText(0, QString(_motionGroups->currentItem()->text(0)).append("_").append(to_string(idx).c_str()));
		subItem->setData(1, 0, idx);
		_motionGroups->currentItem()->addChild(subItem);
		Tip::GetInstance()->Pop(_parent, "动作已添加!");
	}
	else  //选中子动作 
	{
		QTreeWidgetItem* p = _motionGroups->currentItem()->parent();

		Json::Value motion;
		motion["File"] = "";
		motion["Sound"] = "";
		motion["Text"] = "";
		_modelJson["FileReferences"]["Motions"][p->text(0).toStdString()].append(motion);

		int idx = p->childCount();
		QTreeWidgetItem* subItem = new QTreeWidgetItem();
		subItem->setText(0, QString(p->text(0)).append("_").append(to_string(idx).c_str()));
		subItem->setData(1, 0, idx);
		p->addChild(subItem);
		Tip::GetInstance()->Pop(_parent, "动作已添加!");
	}
}

void ModelSettings::DeleteMotion()
{
	if (_motionGroups->currentItem() == NULL)  //无选中
	{
		Tip::GetInstance()->Pop(_parent, "未选择动作!");
	}
	else if (_motionGroups->currentItem()->parent() == NULL)  //选中整个动作组
	{
		Tip::GetInstance()->Pop(_parent, "未选择动作!");
	}
	else  //选中子动作 
	{
		QTreeWidgetItem* p = _motionGroups->currentItem()->parent();
		_modelJson["FileReferences"]["Motions"][p->text(0).toStdString()].removeIndex(p->indexOfChild(_motionGroups->currentItem()), NULL);
		p->removeChild(_motionGroups->currentItem());
		int i;
		int size = p->childCount();
		for (i = 0; i < size; i++)
		{
			p->child(i)->setData(1, 0, i);
			p->child(i)->setText(0, QString(p->text(0)).append("_").append(to_string(i).c_str()));
		}
		motionJsonPath->setCurrentText("");
		motionSoundPath->setCurrentText("");
		motionText->clear();
		Tip::GetInstance()->Pop(_parent, "动作已删除!");
	}
}

void ModelSettings::ShowMotionInfo(QTreeWidgetItem* w, int idx)
{
	if (w->parent() != NULL)
	{
		motionGroup->setText(w->parent()->text(0));
		string groupname = w->parent()->text(0).toUtf8();
		int idx = w->data(1, 0).toInt();
		Json::Value motion = _modelJson["FileReferences"]["Motions"][groupname][idx];

		motionJsonPath->setCurrentText(QString::fromUtf8(motion["File"].isNull() ? "" : motion["File"].asCString()));
		motionSoundPath->setCurrentText(QString::fromUtf8(motion["Sound"].isNull() ? "" : motion["Sound"].asCString()));
		motionText->setText(QString::fromStdString(motion["Text"].isNull() ? "" : motion["Text"].asCString()));
	}
	else{
		if (w->parent() == NULL) motionGroup->setText(w->text(0));
		motionJsonPath->setCurrentText("");
		motionSoundPath->setCurrentText("");
		motionText->clear();
	}
}

void ModelSettings::AddGroup()
{
	if (motionGroup->text().isEmpty()) {
		Tip::GetInstance()->Pop(_parent, "动作组名称不能为空!");
		return;
	}
	QList<QTreeWidgetItem*> x = _motionGroups->findItems(motionGroup->text(), Qt::MatchExactly, 0);
	if (x.count() == 0)
	{
		QTreeWidgetItem* topItem = new QTreeWidgetItem();
		topItem->setText(0, motionGroup->text());
		_motionGroups->addTopLevelItem(topItem);
		_modelJson["FileReferences"]["Motions"][motionGroup->text().toUtf8().toStdString()] = Json::Value(Json::arrayValue);
		Tip::GetInstance()->Pop(_parent, "动作组添加成功!");
	}
	else {
		Tip::GetInstance()->Pop(_parent, "动作组已存在!");
	}
}

void ModelSettings::DeleteGroup()
{
	if (motionGroup->text().isEmpty()) {
		Tip::GetInstance()->Pop(_parent, "未选中动作组!");
		return;
	}
	QList<QTreeWidgetItem*> x = _motionGroups->findItems(motionGroup->text(), Qt::MatchExactly, 0);
	if (x.count() == 1)
	{
		if (QMessageBox::question(_parent, QString::fromLocal8Bit("模型设置"), QString::fromLocal8Bit("是否删除动作组<br>").append("<b>").append(motionGroup->text()).append("</b>"),
			QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
		{
			_modelJson["FileReferences"]["Motions"].removeMember(motionGroup->text().toUtf8().toStdString());
			x.at(0)->takeChildren();
			_motionGroups->takeTopLevelItem(_motionGroups->indexOfTopLevelItem(x.at(0)));
			Tip::GetInstance()->Pop(_parent, "动作组已删除!");
			_motionGroups->clearFocus();
			motionGroup->clear();
		}
	}
	else if (x.count() == 0)
	{
		Tip::GetInstance()->Pop(_parent, "动作组不存在!");
	}
	else {
		Tip::GetInstance()->Pop(_parent, "出现未知错误!");
	}
}

void ModelSettings::UpdateGroupName()
{
	if (motionGroup->text().isEmpty()) 
	{
		Tip::GetInstance()->Pop(_parent, "动作组名称不能为空!");
	}
	else if (_motionGroups->currentItem() == NULL)  //无选中
	{
		Tip::GetInstance()->Pop(_parent, "未选中动作组!");
	}
	else if (_motionGroups->findItems(motionGroup->text(), Qt::MatchExactly, 0).count() > 0)
	{
		Tip::GetInstance()->Pop(_parent, "动作组名称已存在!");
	}
	else if (_motionGroups->currentItem()->parent() == NULL)  //选中整个动作组
	{
		Json::Value group = _modelJson["FileReferences"]["Motions"][_motionGroups->currentItem()->text(0).toStdString()];
		_modelJson["FileReferences"]["Motions"].removeMember(_motionGroups->currentItem()->text(0).toStdString());
		_modelJson["FileReferences"]["Motions"][motionGroup->text().toStdString()] = group;
		_motionGroups->currentItem()->setText(0, motionGroup->text());
		Tip::GetInstance()->Pop(_parent, "动作组名称已修改!");
	}
	else  //选中子动作 
	{
		QTreeWidgetItem* p = _motionGroups->currentItem()->parent();
		Json::Value group = _modelJson["FileReferences"]["Motions"][p->text(0).toStdString()];
		_modelJson["FileReferences"]["Motions"].removeMember(p->text(0).toStdString());
		_modelJson["FileReferences"]["Motions"][motionGroup->text().toStdString()] = group;
		p->setText(0, motionGroup->text());
		Tip::GetInstance()->Pop(_parent, "动作组名称已修改!");
	}
}

void ModelSettings::StartMotion(QTreeWidgetItem* w, int idx)
{
	if (w->parent() != NULL)
	{
		string groupname = w->parent()->text(0).toUtf8();
		int idx = w->data(1, 0).toInt();
		LAppLive2DManager::GetInstance()->GetModel(0)->StartMotion(groupname.c_str(), idx, PriorityForce);
	}
	else {
		motionJsonPath->setCurrentText("");
		motionSoundPath->setCurrentText("");
		motionText->clear();
	}
}

void ModelSettings::UpdateModel()
{
	_ModelName = model->currentText().toUtf8();
	LAppLive2DManager::GetInstance()->ChangeModel(_ModelDir.c_str(), _ModelName.c_str());
	LApp::GetInstance()->SaveConfig();
	LoadConfig();
	Tip::GetInstance()->Pop(_parent, "模型已更换");
}

ControlWidget::ControlWidget()
{
	setFixedSize(620, 450);
	setWindowFlags(Qt::Tool);
	setWindowTitle(QString::fromUtf8(_AppName.c_str()));
	_appSettings = new AppSettings(this);
	_modelSettings = new ModelSettings(this);
	addTab(_appSettings, QString::fromLocal8Bit("用户设置"));
	addTab(_modelSettings, QString::fromLocal8Bit("模型设置"));
	setStyleSheet("QTabBar::tab{font-family: 微软雅黑; width: 120px; height: 30px; background-color: rgb(50, 50, 50); color: rgba(180, 180, 180, 180); padding: 0; margin: 0} "
		"QTabBar::tab:selected{background-color: rgb(30, 30, 30); color: rgba(255, 255, 255, 180); }"
		"QTabBar{background-color: rgb(37, 37, 38);}"
		"QTabWidget::pane{border: none; background-color: rgb(30, 30, 30); color: white}"
		"QTabWidget{background-color: rgb(37, 37, 38)}"
	);
	_appSettings->setStyleSheet("QWidget{color: rgba(255, 255, 255, 180);background-color: rgb(50, 50, 50); font-family: 微软雅黑;}"
		"QLabel{background: transparent; color: rgba(255, 255, 255, 200); font: 15px}"
		"QLineEdit{padding: 5px; color: rgb(191, 191, 191); font: 15px; border: 1px solid rgb(80, 80, 80); background-color: rgb(60, 60, 60);}"
		"QLineEdit::focus{border: 1px solid rgb(50, 120, 200)}"
		"QPushButton{width: 100px; font: 13.5px; border-radius: 10px; font-family: 微软雅黑; color: rgba(255, 255, 255, 200); background-color: rgba(50, 150, 235, 190); border: none; padding-left: 10px; padding-right: 10px; padding-top: 7px; padding-bottom: 7px}"
		"QPushButton:pressed{color: rgba(255, 255, 255, 100); background-color: rgba(50, 150, 235, 150); border: none; padding-left: 10px; padding-right: 10px; padding-top: 7px; padding-bottom: 7px}"
	);
	_modelSettings->setStyleSheet("QWidget{color: rgba(255, 255, 255, 180); background-color: rgb(50, 50, 50); font-family: 微软雅黑}"
		"QLabel{background: transparent; color: rgba(255 ,255, 255, 200); font: 15px}"
		"QTreeWidget::item{height: 30px; color: rgba(255, 255, 255, 200)}"
		"QTreeWidget{outline: none; border: none; color: rgba(255, 255, 255, 245); background-color: rgb(50, 50, 50); font-family: 微软雅黑}"
		"QTreeWidget::item:selected:active{background-color: rgba(50, 120, 170, 180); color: rgba(255, 255, 255, 245); border: 1px solid rgb(50, 120, 240)}"
		"QTreeWidget::item:selected:!active{background-color: rgba(50, 120, 170, 90); color: rgba(255, 255, 255, 245); border: 1px solid rgb(50, 120, 240)}"
		"QTreeWidget::item:hover{background-color: rgb(50, 50, 50); border: none}"
		"QTextEdit{padding: 5px; border: 1px solid rgb(80, 80, 80); color: rgba(255, 255, 255, 245); font: 17px}"
		"QTextEdit::focus{border: 1px solid rgb(50, 120, 200)}"
		"QLineEdit{padding: 5px; color: rgb(191, 191, 191); font: 15px; border: 1px solid rgb(80, 80, 80); background-color: rgb(60, 60, 60);}"
		"QLineEdit::focus{border: 1px solid rgb(50, 120, 200)}"
		"QPushButton{width: 100px;font: 13.5px; border-radius: 10px; font-family: 微软雅黑; color: rgba(255, 255, 255, 200); background-color: rgba(50, 150, 235, 190); border: none; padding-left: 10px; padding-right: 10px; padding-top: 7px; padding-bottom: 7px}"
		"QPushButton:pressed{color: rgba(255, 255, 255, 100); background-color: rgba(50, 150, 235, 150); border: none; padding-left: 10px; padding-right: 10px; padding-top: 7px; padding-bottom: 7px}"
		"QComboBox{height: 30px; padding: 1px 18px 1px 3px;}"
		
	);
}


void ControlWidget::Pop()
{
	_appSettings->LoadConfig();
	_modelSettings->LoadConfig();
	show();
	raise();
}

