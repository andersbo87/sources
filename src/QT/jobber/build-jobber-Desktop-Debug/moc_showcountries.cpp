/****************************************************************************
** Meta object code from reading C++ file 'showcountries.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../jobb/QT/jobber/jobber/showcountries.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'showcountries.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ShowCountries_t {
    QByteArrayData data[11];
    char stringdata0[189];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ShowCountries_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ShowCountries_t qt_meta_stringdata_ShowCountries = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ShowCountries"
QT_MOC_LITERAL(1, 14, 18), // "buttonFirstClicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 17), // "buttonLastClicked"
QT_MOC_LITERAL(4, 52, 17), // "buttonNextClicked"
QT_MOC_LITERAL(5, 70, 21), // "buttonPreviousClicked"
QT_MOC_LITERAL(6, 92, 24), // "comboboxCountryIDChanged"
QT_MOC_LITERAL(7, 117, 26), // "lineEditCountrynameChanged"
QT_MOC_LITERAL(8, 144, 14), // "btnSaveClicked"
QT_MOC_LITERAL(9, 159, 16), // "btnDeleteClicked"
QT_MOC_LITERAL(10, 176, 12) // "windowLoaded"

    },
    "ShowCountries\0buttonFirstClicked\0\0"
    "buttonLastClicked\0buttonNextClicked\0"
    "buttonPreviousClicked\0comboboxCountryIDChanged\0"
    "lineEditCountrynameChanged\0btnSaveClicked\0"
    "btnDeleteClicked\0windowLoaded"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ShowCountries[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ShowCountries::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ShowCountries *_t = static_cast<ShowCountries *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->buttonFirstClicked(); break;
        case 1: _t->buttonLastClicked(); break;
        case 2: _t->buttonNextClicked(); break;
        case 3: _t->buttonPreviousClicked(); break;
        case 4: _t->comboboxCountryIDChanged(); break;
        case 5: _t->lineEditCountrynameChanged(); break;
        case 6: _t->btnSaveClicked(); break;
        case 7: _t->btnDeleteClicked(); break;
        case 8: _t->windowLoaded(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ShowCountries::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ShowCountries.data,
      qt_meta_data_ShowCountries,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ShowCountries::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ShowCountries::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ShowCountries.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ShowCountries::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
