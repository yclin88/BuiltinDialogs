#ifndef CBUILTINDLG_H
#define CBUILTINDLG_H

#include <QDialog>
#include <QPushButton>
#include <QTextEdit>

class CBuiltinDlg : public QDialog
{
    Q_OBJECT

public:
    CBuiltinDlg(QWidget *parent = nullptr);
    ~CBuiltinDlg();
private:
    QTextEdit     *displayTextEdit;
    QPushButton   *colorPushBtn;
    QPushButton   *errorPushBtn;
    QPushButton   *filePushBtn;
    QPushButton   *fontPushBtn;
    QPushButton   *inputPushBtn;
    QPushButton   *pagePushBtn;
    QPushButton   *progressPushBtn;
    QPushButton   *printPushBtn;
private slots: //槽函數(slot)宣告
    void doPushBtn();
};
#endif // CBUILTINDLG_H
