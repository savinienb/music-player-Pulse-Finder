/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Tue Jul 5 02:13:23 2016
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      33,   11,   11,   11, 0x05,
      45,   11,   11,   11, 0x05,
      72,   58,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
     103,   98,   11,   11, 0x0a,
     179,  173,   11,   11, 0x08,
     197,   11,   11,   11, 0x08,
     216,   11,   11,   11, 0x08,
     240,   11,   11,   11, 0x08,
     248,   11,   11,   11, 0x08,
     277,   11,   11,   11, 0x08,
     305,   11,   11,   11, 0x08,
     323,   11,   11,   11, 0x08,
     353,   11,   11,   11, 0x08,
     375,  371,   11,   11, 0x08,
     424,  399,   11,   11, 0x08,
     448,   11,   11,   11, 0x08,
     461,   11,   11,   11, 0x08,
     479,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0changemusic(QString)\0"
    "playmusic()\0pausemusic()\0mean,variance\0"
    "setrythmvariable(int,int)\0data\0"
    "dataReceived(QMap<Phonon::AudioDataOutput::Channel,QVector<qint16> >)\0"
    "value\0Loadingvalue(int)\0on_Pulse_clicked()\0"
    "on_Metrostate_clicked()\0clock()\0"
    "on_ModifyMetronome_clicked()\0"
    "on_setaudiosource_clicked()\0"
    "on_Play_clicked()\0on_setryhtmvariable_clicked()\0"
    "on_Stop_clicked()\0pos\0ShowContextMenu(QPoint)\0"
    "is_filepathgood,filename\0"
    "musicpath(bool,QString)\0timedomain()\0"
    "frequencydomain()\0on_pushButton_clicked()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->changemusic((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->playmusic(); break;
        case 2: _t->pausemusic(); break;
        case 3: _t->setrythmvariable((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->dataReceived((*reinterpret_cast< const QMap<Phonon::AudioDataOutput::Channel,QVector<qint16> >(*)>(_a[1]))); break;
        case 5: _t->Loadingvalue((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 6: _t->on_Pulse_clicked(); break;
        case 7: _t->on_Metrostate_clicked(); break;
        case 8: _t->clock(); break;
        case 9: _t->on_ModifyMetronome_clicked(); break;
        case 10: _t->on_setaudiosource_clicked(); break;
        case 11: _t->on_Play_clicked(); break;
        case 12: _t->on_setryhtmvariable_clicked(); break;
        case 13: _t->on_Stop_clicked(); break;
        case 14: _t->ShowContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 15: _t->musicpath((*reinterpret_cast< const bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 16: _t->timedomain(); break;
        case 17: _t->frequencydomain(); break;
        case 18: _t->on_pushButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::changemusic(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::playmusic()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void MainWindow::pausemusic()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void MainWindow::setrythmvariable(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
