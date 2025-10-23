#include "cbuiltindlg.h"

#include <QColor>
#include <QColorDialog>
#include <QCoreApplication>
#include <QErrorMessage>
#include <QFileDialog>
#include <QFontDialog>
#include <QGridLayout>
#include <QInputDialog>
#include <QLineEdit>
#include <QPageSetupDialog>
#include <QPrintDialog>
#include <QProgressDialog>
#include <QTextCursor>

#include <QElapsedTimer>
#include <QEventLoop>
#include <QPrinter>

CBuiltinDlg::CBuiltinDlg(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Qt標準通用對話盒"));

    QGridLayout *gridLayout = new QGridLayout(this);
    displayTextEdit         = new QTextEdit;
    displayTextEdit->setReadOnly(true);
    displayTextEdit->setPlainText(tr("Qt標準通用對話盒"));

    colorPushBtn    = new QPushButton(tr("顏色對話盒"));
    errorPushBtn    = new QPushButton(tr("錯誤訊息盒"));
    filePushBtn     = new QPushButton(tr("檔案對話盒"));
    fontPushBtn     = new QPushButton(tr("字體對話盒"));
    inputPushBtn    = new QPushButton(tr("輸入對話盒"));
    pagePushBtn     = new QPushButton(tr("頁面設定對話盒"));
    progressPushBtn = new QPushButton(tr("進度對話盒"));
    printPushBtn    = new QPushButton(tr("列印對話盒"));

    errorMessageDlg = new QErrorMessage(this);
    printer         = new QPrinter(QPrinter::HighResolution);

    gridLayout->addWidget(displayTextEdit, 0, 0, 8, 1);
    gridLayout->addWidget(colorPushBtn, 0, 1);
    gridLayout->addWidget(errorPushBtn, 1, 1);
    gridLayout->addWidget(filePushBtn, 2, 1);
    gridLayout->addWidget(fontPushBtn, 3, 1);
    gridLayout->addWidget(inputPushBtn, 4, 1);
    gridLayout->addWidget(pagePushBtn, 5, 1);
    gridLayout->addWidget(progressPushBtn, 6, 1);
    gridLayout->addWidget(printPushBtn, 7, 1);

    gridLayout->setColumnStretch(0, 3);
    gridLayout->setColumnStretch(1, 1);

    connect(colorPushBtn, &QPushButton::clicked, this, [this]() {
        const QColor color = QColorDialog::getColor(Qt::black, this, tr("選擇顏色"));
        if (color.isValid()) {
            appendLogRich(tr("選擇顏色：<span style=\"color:%1\">%1</span>")
                              .arg(color.name(QColor::HexRgb)));
        } else {
            appendLog(tr("顏色對話盒已取消"));
        }
    });

    connect(errorPushBtn, &QPushButton::clicked, this, [this]() {
        errorMessageDlg->showMessage(tr("這是一個錯誤訊息盒的範例。"));
        appendLog(tr("已顯示錯誤訊息盒"));
    });

    connect(filePushBtn, &QPushButton::clicked, this, [this]() {
        const QString fileName = QFileDialog::getOpenFileName(this, tr("選擇檔案"));
        if (!fileName.isEmpty()) {
            appendLog(tr("選擇檔案：%1").arg(fileName));
        } else {
            appendLog(tr("檔案對話盒已取消"));
        }
    });

    connect(fontPushBtn, &QPushButton::clicked, this, [this]() {
        bool ok = false;
        const QFont font = QFontDialog::getFont(&ok, displayTextEdit->font(), this, tr("選擇字體"));
        if (ok) {
            displayTextEdit->setFont(font);
            appendLog(tr("選擇字體：%1，大小：%2pt").arg(font.family()).arg(font.pointSize()));
        } else {
            appendLog(tr("字體對話盒已取消"));
        }
    });

    connect(inputPushBtn, &QPushButton::clicked, this, [this]() {
        bool ok = false;
        const QString text = QInputDialog::getText(this, tr("輸入對話盒"), tr("請輸入一些文字："),
                                                  QLineEdit::Normal, QString(), &ok);
        if (ok) {
            if (text.isEmpty()) {
                appendLog(tr("輸入了空字串"));
            } else {
                appendLog(tr("輸入內容：%1").arg(text));
            }
        } else {
            appendLog(tr("輸入對話盒已取消"));
        }
    });

    connect(pagePushBtn, &QPushButton::clicked, this, [this]() {
        QPageSetupDialog pageSetupDialog(printer, this);
        if (pageSetupDialog.exec() == QDialog::Accepted) {
            const QString orientation = printer->orientation() == QPrinter::Portrait ? tr("直向") : tr("橫向");
            appendLog(tr("頁面設定已更新，方向：%1").arg(orientation));
        } else {
            appendLog(tr("頁面設定對話盒已取消"));
        }
    });

    connect(progressPushBtn, &QPushButton::clicked, this, [this]() {
        QProgressDialog progress(tr("正在模擬長時間的工作..."), tr("取消"), 0, 100, this);
        progress.setWindowModality(Qt::WindowModal);
        progress.setMinimumDuration(0);

        for (int value = 0; value <= 100; ++value) {
            progress.setValue(value);
            QCoreApplication::processEvents();
            if (progress.wasCanceled()) {
                appendLog(tr("進度對話盒被使用者取消"));
                return;
            }

            QElapsedTimer delayTimer;
            delayTimer.start();
            while (delayTimer.elapsed() < 15) {
                QCoreApplication::processEvents(QEventLoop::AllEvents, 5);
            }
        }

        appendLog(tr("進度對話盒已完成"));
    });

    connect(printPushBtn, &QPushButton::clicked, this, [this]() {
        QPrintDialog printDialog(printer, this);
        if (printDialog.exec() == QDialog::Accepted) {
            displayTextEdit->print(printer);
            appendLog(tr("列印工作已送出"));
        } else {
            appendLog(tr("列印對話盒已取消"));
        }
    });
}

CBuiltinDlg::~CBuiltinDlg()
{
    delete printer;
}

void CBuiltinDlg::appendLog(const QString &message)
{
    QTextCursor cursor = displayTextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    cursor.insertText(message);
    cursor.insertBlock();
    displayTextEdit->setTextCursor(cursor);
}

void CBuiltinDlg::appendLogRich(const QString &message)
{
    QTextCursor cursor = displayTextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    cursor.insertHtml(message);
    cursor.insertBlock();
    displayTextEdit->setTextCursor(cursor);
}
