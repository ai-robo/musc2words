#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSerialPort>
#include <QVector>

#include "receiverthread.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow* ui;
  QSerialPort m_serial;
  ReceiverThread m_thread;
  QVector<std::pair<QPushButton*, QString>> m_buttonsVector;

  void ShowMessage(QString title, QString message, QMessageBox::Icon icon);
  void ShowError(QString title, QString message);

 private slots:
  void on_actionCOM_triggered();
  void startReceiver();
  void showRequest(const QString& s);
  void processError(const QString& s);
  void processTimeout(const QString& s);
};
#endif  // MAINWINDOW_H
