/****************************************************************************
** Meta object code from reading C++ file 'controlwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "controlwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controlwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyText_t {
    QByteArrayData data[3];
    char stringdata0[18];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyText_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyText_t qt_meta_stringdata_MyText = {
    {
QT_MOC_LITERAL(0, 0, 6), // "MyText"
QT_MOC_LITERAL(1, 7, 9), // "loseFocus"
QT_MOC_LITERAL(2, 17, 0) // ""

    },
    "MyText\0loseFocus\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyText[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void MyText::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyText *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loseFocus(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyText::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyText::loseFocus)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject MyText::staticMetaObject = { {
    QMetaObject::SuperData::link<QTextEdit::staticMetaObject>(),
    qt_meta_stringdata_MyText.data,
    qt_meta_data_MyText,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyText::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyText::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyText.stringdata0))
        return static_cast<void*>(this);
    return QTextEdit::qt_metacast(_clname);
}

int MyText::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void MyText::loseFocus()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_AppSettings_t {
    QByteArrayData data[6];
    char stringdata0[49];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AppSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AppSettings_t qt_meta_stringdata_AppSettings = {
    {
QT_MOC_LITERAL(0, 0, 11), // "AppSettings"
QT_MOC_LITERAL(1, 12, 8), // "OpenFile"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 5), // "Apply"
QT_MOC_LITERAL(4, 28, 6), // "Cancel"
QT_MOC_LITERAL(5, 35, 13) // "OpenSourceDir"

    },
    "AppSettings\0OpenFile\0\0Apply\0Cancel\0"
    "OpenSourceDir"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AppSettings[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    0,   36,    2, 0x08 /* Private */,
       5,    0,   37,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AppSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AppSettings *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OpenFile(); break;
        case 1: _t->Apply(); break;
        case 2: _t->Cancel(); break;
        case 3: _t->OpenSourceDir(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject AppSettings::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_AppSettings.data,
    qt_meta_data_AppSettings,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AppSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AppSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AppSettings.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int AppSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
struct qt_meta_stringdata_ModelSettings_t {
    QByteArrayData data[18];
    char stringdata0[178];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ModelSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ModelSettings_t qt_meta_stringdata_ModelSettings = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ModelSettings"
QT_MOC_LITERAL(1, 14, 6), // "Cancel"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 5), // "Apply"
QT_MOC_LITERAL(4, 28, 9), // "AddMotion"
QT_MOC_LITERAL(5, 38, 12), // "DeleteMotion"
QT_MOC_LITERAL(6, 51, 14), // "ShowMotionInfo"
QT_MOC_LITERAL(7, 66, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(8, 83, 1), // "w"
QT_MOC_LITERAL(9, 85, 11), // "StartMotion"
QT_MOC_LITERAL(10, 97, 9), // "BindSound"
QT_MOC_LITERAL(11, 107, 1), // "x"
QT_MOC_LITERAL(12, 109, 10), // "BindMotion"
QT_MOC_LITERAL(13, 120, 8), // "BindText"
QT_MOC_LITERAL(14, 129, 11), // "UpdateModel"
QT_MOC_LITERAL(15, 141, 8), // "AddGroup"
QT_MOC_LITERAL(16, 150, 11), // "DeleteGroup"
QT_MOC_LITERAL(17, 162, 15) // "UpdateGroupName"

    },
    "ModelSettings\0Cancel\0\0Apply\0AddMotion\0"
    "DeleteMotion\0ShowMotionInfo\0"
    "QTreeWidgetItem*\0w\0StartMotion\0BindSound\0"
    "x\0BindMotion\0BindText\0UpdateModel\0"
    "AddGroup\0DeleteGroup\0UpdateGroupName"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModelSettings[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    2,   83,    2, 0x08 /* Private */,
       9,    2,   88,    2, 0x08 /* Private */,
      10,    1,   93,    2, 0x08 /* Private */,
      12,    1,   96,    2, 0x08 /* Private */,
      13,    0,   99,    2, 0x08 /* Private */,
      14,    0,  100,    2, 0x08 /* Private */,
      15,    0,  101,    2, 0x08 /* Private */,
      16,    0,  102,    2, 0x08 /* Private */,
      17,    0,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Int,    8,    2,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Int,    8,    2,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ModelSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ModelSettings *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Cancel(); break;
        case 1: _t->Apply(); break;
        case 2: _t->AddMotion(); break;
        case 3: _t->DeleteMotion(); break;
        case 4: _t->ShowMotionInfo((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->StartMotion((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->BindSound((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->BindMotion((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->BindText(); break;
        case 9: _t->UpdateModel(); break;
        case 10: _t->AddGroup(); break;
        case 11: _t->DeleteGroup(); break;
        case 12: _t->UpdateGroupName(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ModelSettings::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ModelSettings.data,
    qt_meta_data_ModelSettings,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ModelSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModelSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ModelSettings.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ModelSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
