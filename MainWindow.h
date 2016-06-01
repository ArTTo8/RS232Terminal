#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "rs232terminalprotocol.h"
#include "ComPort.h"
#include "MacroWindow.h"
#include "Macros.h"
#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QTimer>
#include <QSerialPort>
#include <QCheckBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QSignalMapper>
#include <QSettings>
#include <QAbstractButton>
#include <QFileDialog>
#include <QGroupBox>
#include <QSpacerItem>
#include <QListWidget>

//class MyPlainTextEdit : public QPlainTextEdit
//{
//    Q_OBJECT
//public:
//    MyPlainTextEdit(QWidget *parent = 0) : QPlainTextEdit(parent) {}
//    void delLine(int lineNumber)
//    {
//        QStringList list = this->toPlainText().split("\n");
//        list.removeAt(lineNumber);
//        this->clear();
//        this->insertPlainText(list.join("\n"));
//    }
//};

class MiniMacros : public QWidget
{
    Q_OBJECT
signals:
    bPress(int index);
    cbCheck(int index, bool check);

public:
    int index;
    QHBoxLayout *layout;
    QCheckBox *cbMiniMacros;
    QPushButton *bMiniMacros;

    MiniMacros(int i, QString title, QWidget *parent = 0) : QWidget(parent)
    {
        index = i;
        cbMiniMacros = new QCheckBox;
        bMiniMacros = new QPushButton;
        layout = new QHBoxLayout;
        bMiniMacros->setText(title);

        layout->setSpacing(2);
        layout->setMargin(2);

        layout->addWidget(cbMiniMacros);
        layout->addWidget(bMiniMacros);
        setLayout(layout);

        connect(bMiniMacros, SIGNAL(clicked(bool)), this, SLOT(click()));
        connect(cbMiniMacros, SIGNAL(toggled(bool)), this, SLOT(ckeck(bool)));
    }

public slots:
    void click() { emit bPress(index); }
    void ckeck(bool check) { emit cbCheck(index, check); }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QWidget *widget;
    QComboBox *m_cbPort;
    QComboBox *m_cbBaud;
    QComboBox *m_cbBits;
    QComboBox *m_cbParity;
    QComboBox *m_cbStopBits;
    QPushButton *m_bStart;
    QPushButton *m_bStop;
    QPushButton *m_bWriteLogClear;
    QPushButton *m_bReadLogClear;
    QPushButton *m_bOffsetLeft;
    QPushButton *m_bShowMacroForm;
    QPushButton *m_bSaveWriteLog;
    QPushButton *m_bSaveReadLog;
    QLabel *m_lTx;
    QLabel *m_lRx;
    QSpinBox *m_sbBytesCount;
    QListWidget *m_eLogRead;
    QListWidget *m_eLogWrite;
    QSpinBox *m_sbRepeatSendInterval;
    QLineEdit *m_leSendPackage;
    QAbstractButton *m_abSendPackage;
    QCheckBox *m_cbEchoMode;
    QCheckBox *m_cbSelectAllMiniMacroses;
    QSpinBox *m_sbEchoInterval;
    QCheckBox *m_cbReadScroll;
    QCheckBox *m_cbWriteScroll;
    QCheckBox *m_cbSaveWriteLog;
    QCheckBox *m_cbSaveReadLog;

    QTimer *m_BlinkTimeTxNone;
    QTimer *m_BlinkTimeRxNone;
    QTimer *m_BlinkTimeTxColor;
    QTimer *m_BlinkTimeRxColor;

    QTimer *m_tSend;
    QTimer *m_tEcho;

    QTimer *m_tWriteLog;
    QTimer *m_tReadLog;

    QSerialPort *m_Port;
    ComPort *m_ComPort;
    RS232TerminalProtocol *m_Protocol;
    QSettings *settings;
    MacroWindow *macroWindow;
    QFileDialog *fileDialog;
    QPushButton *m_bHiddenGroup;
    QGroupBox *m_gbHiddenGroup;
    QVBoxLayout *hiddenLayout;
    QSpacerItem *spacer;

    QFile writeLog;
    QFile readLog;
    int maxWriteLogRows;
    int maxReadLogRows;
    int logReadRowsCount;
    int logWriteRowsCount;
    QStringList listOfBytes;
    int readBytesDisplayed;
    QStringList echoData;
    bool logWrite;
    bool logRead;
    QString writeLogBuffer;
    QString readLogBuffer;
    QString buffer;

    void view();
    void saveSession();
    void loadSession();
    void connections();

protected:
    virtual void closeEvent(QCloseEvent *e);

private slots:
    void setAllMini(bool check);
    void hiddenClick();
    void start();
    void stop();
    void echo();
    void saveWrite();
    void saveRead();
    void doOffset();
    void writeLogTimeout();
    void readLogTimeout();
    void startWriteLog(bool check);
    void startReadLog(bool check);
    void textChanged(QString text);
    void cleanEchoBuffer(bool check);
    void macrosRecieved(const QString &str);
    void showMacroWindow();
    void clearReadLog();
    void clearWriteLog();
    void received(bool isReceived);
    void sendSingle();
    void colorIsRx();
    void colorRxNone();
    void colorIsTx();
    void colorTxNone();
    void startSending(bool checked);
    void addToHidden(int index, const QString &str);
    void delFromHidden(int index);
    void miniMacrosTextChanged(QString str, int index) { MiniMacrosList[index]->bMiniMacros->setText(str); }

public:
    QMap<int, MiniMacros *> MiniMacrosList;
    void displayReadData(QString string);
    void displayWriteData(QString string);
    void sendPackage(QString string);
    explicit MainWindow(QString title, QWidget *parent = 0);
};

#endif
