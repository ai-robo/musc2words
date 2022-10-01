#include "mainwindow.h"

#include <QDebug>
#include <QDialog>
#include <QScreen>

#include "comportdialog.h"
#include "receiverthread.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  move(QGuiApplication::screens().at(0)->geometry().center() -
       frameGeometry().center());
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionCOM_triggered() {
  // qDebug() << "on_actionCOM_triggered";
  ComPortDialog dialog;
  dialog.Init();
  if (dialog.exec() == QDialog::Accepted) {
    QString port_name = "/dev/" + dialog.getPortName();
    // qDebug() << port_name;

    connect(&m_thread, &ReceiverThread::request, this,
            &MainWindow::showRequest);
    connect(&m_thread, &ReceiverThread::error, this, &MainWindow::processError);
    connect(&m_thread, &ReceiverThread::timeout, this,
            &MainWindow::processTimeout);
    m_buttonsVector = {{ui->pushButton_A, "А"},   {ui->pushButton_B, "Б"},
                       {ui->pushButton_V, "В"},   {ui->pushButton_G, "Г"},
                       {ui->pushButton_D, "Д"},   {ui->pushButton_E, "Е"},
                       {ui->pushButton_YO, "Ё"},  {ui->pushButton_ZH, "Ж"},
                       {ui->pushButton_Z, "З"},   {ui->pushButton_I, "И"},
                       {ui->pushButton_Y, "Й"},   {ui->pushButton_K, "К"},
                       {ui->pushButton_L, "Л"},   {ui->pushButton_M, "М"},
                       {ui->pushButton_N, "Н"},   {ui->pushButton_O, "О"},
                       {ui->pushButton_P, "П"},   {ui->pushButton_R, "Р"},
                       {ui->pushButton_S, "С"},   {ui->pushButton_T, "Т"},
                       {ui->pushButton_U, "У"},   {ui->pushButton_F, "Ф"},
                       {ui->pushButton_H, "Х"},   {ui->pushButton_TS, "Ц"},
                       {ui->pushButton_CH, "Ч"},  {ui->pushButton_SH, "Ш"},
                       {ui->pushButton_SH2, "Щ"}, {ui->pushButton_TV, "Ъ"},
                       {ui->pushButton_IY, "Ы"},  {ui->pushButton_MZ, "Ь"},
                       {ui->pushButton_EE, "Э"},  {ui->pushButton_UU, "Ю"},
                       {ui->pushButton_YA, "Я"}};
    m_thread.startReceiver(port_name, 10000);
  }
}

void MainWindow::startReceiver() {}

void MainWindow::showRequest(const QString& s) {
  static int letter_num = 0;
  // qDebug() << s;
  if (s == "set") {
    qDebug() << letter_num;
    qDebug() << m_buttonsVector.at(letter_num).second;
    ui->lineEdit->setText(ui->lineEdit->text() +
                          m_buttonsVector.at(letter_num).second);
  } else {
    letter_num++;
    qDebug() << letter_num;
    if (letter_num > 32) {
      letter_num = 0;
      m_buttonsVector.at(letter_num).first->setEnabled(true);
      m_buttonsVector.at(32).first->setEnabled(false);
      m_buttonsVector.at(1).first->setEnabled(false);
    } else if (letter_num == 32) {
      m_buttonsVector.at(letter_num).first->setEnabled(true);
      m_buttonsVector.at(31).first->setEnabled(false);
    } else if (letter_num == 0) {
      m_buttonsVector.at(letter_num).first->setEnabled(true);
      m_buttonsVector.at(1).first->setEnabled(false);
      m_buttonsVector.at(32).first->setEnabled(false);
    } else {
      m_buttonsVector.at(letter_num).first->setEnabled(true);
      m_buttonsVector.at(letter_num - 1).first->setEnabled(false);
      m_buttonsVector.at(letter_num + 1).first->setEnabled(false);
    }
  }
}

void MainWindow::processError(const QString& s) { qDebug() << s; }

void MainWindow::processTimeout(const QString& s) { qDebug() << s; }

void MainWindow::ShowMessage(QString title, QString message,
                             QMessageBox::Icon icon) {
  QMessageBox box(title, message, icon, QMessageBox::Ok, QMessageBox::NoButton,
                  QMessageBox::NoButton);
  box.exec();
}

void MainWindow::ShowError(QString title, QString message) {
  ShowMessage(title, message, QMessageBox::Critical);
}
