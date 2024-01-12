#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QDebug>
#include <QFileDialog>
#include <QFileInfo>
#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <QWidget>

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

 private slots:
  void on_action_triggered();

  void on_action_2_triggered();

  void on_choice_clicked();

  void on_modify_clicked();

  void processExistingFiles(const QString& file);

  // void watchDirectory();

  void timerSlot();

  void on_path_save_clicked();

  void xorByteArray(QByteArray& fileData);

  void saveFile(const QByteArray fileData, const QString& fileName,
                const QString& mask);

  void chengeNameModifyFile(const QString& fileName, const QString& mask,
                            QString& newFileName);

  void on_modify_2_clicked();

 private:
  Ui::MainWindow* ui;

  QTimer* timer;
  QString mask, directori_file, directori_save;
  QStringList files;
};
#endif  // MAINWINDOW_H
