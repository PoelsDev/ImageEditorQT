/****************************************************************************
** Meta object code from reading C++ file 'MyMainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../MyMainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyMainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyMainWindow_t {
    QByteArrayData data[15];
    char stringdata0[213];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyMainWindow_t qt_meta_stringdata_MyMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 12), // "MyMainWindow"
QT_MOC_LITERAL(1, 13, 13), // "clickOpenFile"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 15), // "clickButtonGrey"
QT_MOC_LITERAL(4, 44, 15), // "clickButtonBlur"
QT_MOC_LITERAL(5, 60, 15), // "clickButtonEdge"
QT_MOC_LITERAL(6, 76, 16), // "setValueContrast"
QT_MOC_LITERAL(7, 93, 8), // "contrast"
QT_MOC_LITERAL(8, 102, 18), // "setValueBrightness"
QT_MOC_LITERAL(9, 121, 1), // "b"
QT_MOC_LITERAL(10, 123, 17), // "applyCustomKernel"
QT_MOC_LITERAL(11, 141, 16), // "saveCustomKernel"
QT_MOC_LITERAL(12, 158, 15), // "runCustomKernel"
QT_MOC_LITERAL(13, 174, 16), // "runCustomProgram"
QT_MOC_LITERAL(14, 191, 21) // "resetSavedOutputImage"

    },
    "MyMainWindow\0clickOpenFile\0\0clickButtonGrey\0"
    "clickButtonBlur\0clickButtonEdge\0"
    "setValueContrast\0contrast\0setValueBrightness\0"
    "b\0applyCustomKernel\0saveCustomKernel\0"
    "runCustomKernel\0runCustomProgram\0"
    "resetSavedOutputImage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyMainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    1,   73,    2, 0x08 /* Private */,
       8,    1,   76,    2, 0x08 /* Private */,
      10,    0,   79,    2, 0x08 /* Private */,
      11,    0,   80,    2, 0x08 /* Private */,
      12,    0,   81,    2, 0x08 /* Private */,
      13,    0,   82,    2, 0x08 /* Private */,
      14,    0,   83,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MyMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MyMainWindow *_t = static_cast<MyMainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clickOpenFile(); break;
        case 1: _t->clickButtonGrey(); break;
        case 2: _t->clickButtonBlur(); break;
        case 3: _t->clickButtonEdge(); break;
        case 4: _t->setValueContrast((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->setValueBrightness((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->applyCustomKernel(); break;
        case 7: _t->saveCustomKernel(); break;
        case 8: _t->runCustomKernel(); break;
        case 9: _t->runCustomProgram(); break;
        case 10: _t->resetSavedOutputImage(); break;
        default: ;
        }
    }
}

const QMetaObject MyMainWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MyMainWindow.data,
      qt_meta_data_MyMainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MyMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyMainWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MyMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
