#ifndef CBUILTINDLG_H
#define CBUILTINDLG_H

#include <QDialog>
#include <QPushButton>
#include <QTextEdit>

class QErrorMessage;
class QPrinter;

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
    QErrorMessage *errorMessageDlg;
    QPrinter      *printer;

    void appendLog(const QString &message);
    void appendLogRich(const QString &message);
};
#endif // CBUILTINDLG_H
