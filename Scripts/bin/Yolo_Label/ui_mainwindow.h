/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <label_img.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    label_img *label_image;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QSlider *horizontalSlider_contrast;
    QLabel *label_contrast;
    QHBoxLayout *horizontalLayout;
    QSlider *horizontalSlider_images;
    QLabel *label_progress;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_open_files;
    QTextEdit *textEdit_log;
    QTableWidget *tableWidget_label;
    QHBoxLayout *horizontalLayout_6;
    QCheckBox *checkBox_visualize_class_name;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1180, 693);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1180, 640));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        MainWindow->setFocusPolicy(Qt::StrongFocus);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color : rgb(0, 0, 17);"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        centralWidget->setMinimumSize(QSize(1180, 610));
        centralWidget->setMaximumSize(QSize(165555, 165555));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_image = new label_img(centralWidget);
        label_image->setObjectName(QString::fromUtf8("label_image"));
        sizePolicy.setHeightForWidth(label_image->sizePolicy().hasHeightForWidth());
        label_image->setSizePolicy(sizePolicy);
        label_image->setMinimumSize(QSize(540, 360));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(18);
        font.setBold(true);
        font.setWeight(75);
        label_image->setFont(font);
        label_image->setCursor(QCursor(Qt::CrossCursor));
        label_image->setMouseTracking(true);
        label_image->setStyleSheet(QString::fromUtf8("QLabel { background-color : rgb(0, 0, 17); color : rgb(187, 255, 254);\n"
"border-style: outset;\n"
"border-width: 2px;\n"
"border-color: rgb(0, 255, 255);}\n"
"\n"
""));
        label_image->setFrameShape(QFrame::StyledPanel);
        label_image->setFrameShadow(QFrame::Plain);
        label_image->setLineWidth(3);
        label_image->setScaledContents(true);
        label_image->setAlignment(Qt::AlignCenter);
        label_image->setMargin(-1);

        verticalLayout->addWidget(label_image);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));

        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSlider_contrast = new QSlider(centralWidget);
        horizontalSlider_contrast->setObjectName(QString::fromUtf8("horizontalSlider_contrast"));
        horizontalSlider_contrast->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(horizontalSlider_contrast->sizePolicy().hasHeightForWidth());
        horizontalSlider_contrast->setSizePolicy(sizePolicy2);
        horizontalSlider_contrast->setMinimumSize(QSize(560, 22));
        horizontalSlider_contrast->setMaximumSize(QSize(16777215, 42));
        horizontalSlider_contrast->setFocusPolicy(Qt::NoFocus);
        horizontalSlider_contrast->setStyleSheet(QString::fromUtf8("\n"
"QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 8px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"    background: rgb(0, 255, 255);\n"
"    margin: 2px 0;\n"
"}\n"
"\n"
"\n"
"QSlider::handle:horizontal {\n"
"   background: rgb(255, 187, 0);\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 18px;\n"
"    margin: -10px 0; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"    border-radius: 3px;\n"
"}\n"
""));
        horizontalSlider_contrast->setMaximum(0);
        horizontalSlider_contrast->setPageStep(0);
        horizontalSlider_contrast->setTracking(true);
        horizontalSlider_contrast->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider_contrast);

        label_contrast = new QLabel(centralWidget);
        label_contrast->setObjectName(QString::fromUtf8("label_contrast"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_contrast->sizePolicy().hasHeightForWidth());
        label_contrast->setSizePolicy(sizePolicy3);
        label_contrast->setMinimumSize(QSize(160, 23));
        label_contrast->setMaximumSize(QSize(16777215, 42));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        label_contrast->setFont(font1);
        label_contrast->setStyleSheet(QString::fromUtf8("background-color : rgb(0, 0, 17);color : rgb(0, 255, 255);\n"
"border-style: outset;\n"
"border-width: 2px;\n"
"border-color: rgb(0, 255, 255);"));
        label_contrast->setFrameShape(QFrame::StyledPanel);
        label_contrast->setLineWidth(2);
        label_contrast->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_contrast);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSlider_images = new QSlider(centralWidget);
        horizontalSlider_images->setObjectName(QString::fromUtf8("horizontalSlider_images"));
        horizontalSlider_images->setEnabled(false);
        sizePolicy2.setHeightForWidth(horizontalSlider_images->sizePolicy().hasHeightForWidth());
        horizontalSlider_images->setSizePolicy(sizePolicy2);
        horizontalSlider_images->setMinimumSize(QSize(560, 22));
        horizontalSlider_images->setMaximumSize(QSize(16777215, 42));
        horizontalSlider_images->setFocusPolicy(Qt::NoFocus);
        horizontalSlider_images->setStyleSheet(QString::fromUtf8("\n"
"QSlider::groove:horizontal {\n"
"    border: 1px solid #999999;\n"
"    height: 8px; /* the groove expands to the size of the slider by default. by giving it a height, it has a fixed size */\n"
"    background: rgb(0, 255, 255);\n"
"    margin: 2px 0;\n"
"}\n"
"\n"
"\n"
"QSlider::handle:horizontal {\n"
"   background: rgb(255, 187, 0);\n"
"    border: 1px solid #5c5c5c;\n"
"    width: 18px;\n"
"    margin: -10px 0; /* handle is placed by default on the contents rect of the groove. Expand outside the groove */\n"
"    border-radius: 3px;\n"
"}\n"
""));
        horizontalSlider_images->setMaximum(0);
        horizontalSlider_images->setPageStep(0);
        horizontalSlider_images->setTracking(true);
        horizontalSlider_images->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSlider_images);

        label_progress = new QLabel(centralWidget);
        label_progress->setObjectName(QString::fromUtf8("label_progress"));
        sizePolicy3.setHeightForWidth(label_progress->sizePolicy().hasHeightForWidth());
        label_progress->setSizePolicy(sizePolicy3);
        label_progress->setMinimumSize(QSize(160, 23));
        label_progress->setMaximumSize(QSize(16777215, 42));
        label_progress->setFont(font1);
        label_progress->setStyleSheet(QString::fromUtf8("background-color : rgb(0, 0, 17);color : rgb(0, 255, 255);\n"
"border-style: outset;\n"
"border-width: 2px;\n"
"border-color: rgb(0, 255, 255);"));
        label_progress->setFrameShape(QFrame::StyledPanel);
        label_progress->setLineWidth(2);
        label_progress->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_progress);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButton_open_files = new QPushButton(centralWidget);
        pushButton_open_files->setObjectName(QString::fromUtf8("pushButton_open_files"));
        sizePolicy1.setHeightForWidth(pushButton_open_files->sizePolicy().hasHeightForWidth());
        pushButton_open_files->setSizePolicy(sizePolicy1);
        pushButton_open_files->setMinimumSize(QSize(160, 25));
        pushButton_open_files->setMaximumSize(QSize(200, 60));
        pushButton_open_files->setBaseSize(QSize(0, 0));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        font2.setKerning(true);
        pushButton_open_files->setFont(font2);
        pushButton_open_files->setFocusPolicy(Qt::NoFocus);
        pushButton_open_files->setStyleSheet(QString::fromUtf8("background-color : rgb(0, 0, 17);color : rgb(0, 255, 255);\n"
"border-style: outset;\n"
"border-width: 2px;\n"
"border-color: rgb(0, 255, 255);"));
        pushButton_open_files->setAutoDefault(false);

        horizontalLayout_4->addWidget(pushButton_open_files);

        textEdit_log = new QTextEdit(centralWidget);
        textEdit_log->setObjectName(QString::fromUtf8("textEdit_log"));
        sizePolicy1.setHeightForWidth(textEdit_log->sizePolicy().hasHeightForWidth());
        textEdit_log->setSizePolicy(sizePolicy1);
        textEdit_log->setMinimumSize(QSize(560, 25));
        textEdit_log->setMaximumSize(QSize(16777215, 60));
        textEdit_log->setFont(font1);
        textEdit_log->setFocusPolicy(Qt::NoFocus);
        textEdit_log->setStyleSheet(QString::fromUtf8("background-color : rgb(0, 0, 17);color : rgb(0, 255, 255);\n"
"border-style: outset;\n"
"border-width: 2px;\n"
"border-color: rgb(0, 255, 255);"));
        textEdit_log->setTabChangesFocus(false);
        textEdit_log->setReadOnly(true);

        horizontalLayout_4->addWidget(textEdit_log);


        verticalLayout->addLayout(horizontalLayout_4);


        horizontalLayout_5->addLayout(verticalLayout);

        tableWidget_label = new QTableWidget(centralWidget);
        if (tableWidget_label->columnCount() < 2)
            tableWidget_label->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_label->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_label->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget_label->setObjectName(QString::fromUtf8("tableWidget_label"));
        sizePolicy.setHeightForWidth(tableWidget_label->sizePolicy().hasHeightForWidth());
        tableWidget_label->setSizePolicy(sizePolicy);
        tableWidget_label->setMinimumSize(QSize(220, 360));
        tableWidget_label->setMaximumSize(QSize(330, 16777215));
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(true);
        font3.setWeight(75);
        tableWidget_label->setFont(font3);
        tableWidget_label->setFocusPolicy(Qt::NoFocus);
        tableWidget_label->setStyleSheet(QString::fromUtf8("QHeaderView::section {\n"
"    background-color: rgb(0, 0, 17);\n"
"    color: rgb(255, 187, 0);\n"
"    padding-left: 4px;\n"
"    border: 2px solid rgb(0, 255, 255);\n"
"	font-weight: bold;\n"
"}\n"
"QTableWidget\n"
"{\n"
"border-style: outset;\n"
"border-width: 2px;\n"
"border-color: rgb(0, 255, 255);\n"
"color:rgb(187, 255, 254);\n"
"gridline-width:2px;\n"
"gridline-color: rgb(0, 255, 255);\n"
"}\n"
"\n"
"QTableView {\n"
"    selection-background-color: qlineargradient(x1: 0, y1: 0, x2: 1.0, y2: 1.0, stop: 0 rgb(34, 0, 85), stop: 1 white);\n"
"	selection-color: rgb(0, 255, 0);\n"
"}"));
        tableWidget_label->setFrameShape(QFrame::WinPanel);
        tableWidget_label->setFrameShadow(QFrame::Plain);
        tableWidget_label->setLineWidth(5);
        tableWidget_label->setShowGrid(true);
        tableWidget_label->setSortingEnabled(false);
        tableWidget_label->setWordWrap(true);
        tableWidget_label->setCornerButtonEnabled(true);
        tableWidget_label->setColumnCount(2);
        tableWidget_label->horizontalHeader()->setVisible(false);
        tableWidget_label->horizontalHeader()->setMinimumSectionSize(40);
        tableWidget_label->horizontalHeader()->setHighlightSections(false);
        tableWidget_label->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tableWidget_label->horizontalHeader()->setStretchLastSection(true);
        tableWidget_label->verticalHeader()->setVisible(false);
        tableWidget_label->verticalHeader()->setHighlightSections(false);
        tableWidget_label->verticalHeader()->setProperty("showSortIndicator", QVariant(false));

        horizontalLayout_5->addWidget(tableWidget_label);


        gridLayout->addLayout(horizontalLayout_5, 3, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        checkBox_visualize_class_name = new QCheckBox(centralWidget);
        checkBox_visualize_class_name->setObjectName(QString::fromUtf8("checkBox_visualize_class_name"));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Arial"));
        font4.setPointSize(12);
        font4.setUnderline(false);
        font4.setStrikeOut(false);
        checkBox_visualize_class_name->setFont(font4);
        checkBox_visualize_class_name->setStyleSheet(QString::fromUtf8("background-color : rgb(0, 0, 17);color : rgb(0, 255, 255);\n"
""));

        horizontalLayout_6->addWidget(checkBox_visualize_class_name);


        gridLayout->addLayout(horizontalLayout_6, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1180, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setEnabled(true);
        mainToolBar->setMovable(false);
        mainToolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
#if QT_CONFIG(shortcut)
        label_image->setBuddy(label_image);
#endif // QT_CONFIG(shortcut)

        mainToolBar->addSeparator();

        retranslateUi(MainWindow);

        pushButton_open_files->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "YoloLabel", nullptr));
        label_image->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Open a Dataset Directory...</p><p>D: Next Image</p><p>A: Prev Image</p><p>S: Next Class</p><p>W: Prev Class</p><p>V: Visualize Class Name</p><p>O: Open Files<br/>Ctrl + S: Save</p><p>Ctrl + D: Delete an Image<br/></p></body></html>", nullptr));
        label_contrast->setText(QCoreApplication::translate("MainWindow", "Contrast", nullptr));
        label_progress->setText(QCoreApplication::translate("MainWindow", "0 / 0", nullptr));
        pushButton_open_files->setText(QCoreApplication::translate("MainWindow", "Open Files", nullptr));
#if QT_CONFIG(shortcut)
        pushButton_open_files->setShortcut(QCoreApplication::translate("MainWindow", "O", nullptr));
#endif // QT_CONFIG(shortcut)
        textEdit_log->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Arial'; font-size:12pt; font-weight:600; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Gulim'; font-size:9pt;\">Last Labeled Image:<br />Current Image:</span></p></body></html>", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_label->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_label->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Color", nullptr));
        checkBox_visualize_class_name->setText(QCoreApplication::translate("MainWindow", "Visualize Class Name", nullptr));
#if QT_CONFIG(shortcut)
        checkBox_visualize_class_name->setShortcut(QCoreApplication::translate("MainWindow", "V", nullptr));
#endif // QT_CONFIG(shortcut)
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
