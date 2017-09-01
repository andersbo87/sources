/****************************************************************************
** Meta object code from reading C++ file 'skriv.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Skriv/skriv.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'skriv.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Skriv_t {
    QByteArrayData data[18];
    char stringdata0[367];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Skriv_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Skriv_t qt_meta_stringdata_Skriv = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Skriv"
QT_MOC_LITERAL(1, 6, 11), // "windowShown"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 22), // "handleSelectionChanged"
QT_MOC_LITERAL(4, 42, 5), // "index"
QT_MOC_LITERAL(5, 48, 26), // "fontHandleSelectionChanged"
QT_MOC_LITERAL(6, 75, 4), // "name"
QT_MOC_LITERAL(7, 80, 26), // "on_actionAvslutt_triggered"
QT_MOC_LITERAL(8, 107, 23), // "on_action_pne_triggered"
QT_MOC_LITERAL(9, 131, 28), // "on_actionLagre_som_triggered"
QT_MOC_LITERAL(10, 160, 24), // "on_actionLagre_triggered"
QT_MOC_LITERAL(11, 185, 24), // "on_actionAngre_triggered"
QT_MOC_LITERAL(12, 210, 26), // "on_actionGj_r_om_triggered"
QT_MOC_LITERAL(13, 237, 22), // "on_actionFet_triggered"
QT_MOC_LITERAL(14, 260, 27), // "on_actionKlipp_ut_triggered"
QT_MOC_LITERAL(15, 288, 25), // "on_actionKopier_triggered"
QT_MOC_LITERAL(16, 314, 26), // "on_actionLim_inn_triggered"
QT_MOC_LITERAL(17, 341, 25) // "on_actionKursiv_triggered"

    },
    "Skriv\0windowShown\0\0handleSelectionChanged\0"
    "index\0fontHandleSelectionChanged\0name\0"
    "on_actionAvslutt_triggered\0"
    "on_action_pne_triggered\0"
    "on_actionLagre_som_triggered\0"
    "on_actionLagre_triggered\0"
    "on_actionAngre_triggered\0"
    "on_actionGj_r_om_triggered\0"
    "on_actionFet_triggered\0"
    "on_actionKlipp_ut_triggered\0"
    "on_actionKopier_triggered\0"
    "on_actionLim_inn_triggered\0"
    "on_actionKursiv_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Skriv[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   85,    2, 0x08 /* Private */,
       5,    1,   88,    2, 0x08 /* Private */,
       7,    0,   91,    2, 0x08 /* Private */,
       8,    0,   92,    2, 0x08 /* Private */,
       9,    0,   93,    2, 0x08 /* Private */,
      10,    0,   94,    2, 0x08 /* Private */,
      11,    0,   95,    2, 0x08 /* Private */,
      12,    0,   96,    2, 0x08 /* Private */,
      13,    0,   97,    2, 0x08 /* Private */,
      14,    0,   98,    2, 0x08 /* Private */,
      15,    0,   99,    2, 0x08 /* Private */,
      16,    0,  100,    2, 0x08 /* Private */,
      17,    0,  101,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::QFont,    6,
    QMetaType::Void,
    QMetaType::Void,
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

void Skriv::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Skriv *_t = static_cast<Skriv *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->windowShown(); break;
        case 1: _t->handleSelectionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->fontHandleSelectionChanged((*reinterpret_cast< QFont(*)>(_a[1]))); break;
        case 3: _t->on_actionAvslutt_triggered(); break;
        case 4: _t->on_action_pne_triggered(); break;
        case 5: _t->on_actionLagre_som_triggered(); break;
        case 6: _t->on_actionLagre_triggered(); break;
        case 7: _t->on_actionAngre_triggered(); break;
        case 8: _t->on_actionGj_r_om_triggered(); break;
        case 9: _t->on_actionFet_triggered(); break;
        case 10: _t->on_actionKlipp_ut_triggered(); break;
        case 11: _t->on_actionKopier_triggered(); break;
        case 12: _t->on_actionLim_inn_triggered(); break;
        case 13: _t->on_actionKursiv_triggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Skriv::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Skriv::windowShown)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject Skriv::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Skriv.data,
      qt_meta_data_Skriv,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Skriv::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Skriv::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Skriv.stringdata0))
        return static_cast<void*>(const_cast< Skriv*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Skriv::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void Skriv::windowShown()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
