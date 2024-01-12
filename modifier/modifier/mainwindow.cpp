#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_action_triggered() { on_choice_clicked(); }

void MainWindow::on_action_2_triggered() { QApplication::quit(); }

void MainWindow::on_choice_clicked() {
  directori_file = QFileDialog::getExistingDirectory(
      nullptr, "Выберите директорию с исходными файлами", QDir::homePath());
  if (directori_file.isEmpty()) {
    QMessageBox::critical(this, "Предупреждение",
                          "Не указана дерикторию c исходными файлами.");
    on_choice_clicked();
  }
  ui->path_save_5->setText(directori_file);
}

void MainWindow::on_path_save_clicked() {
  directori_save = QFileDialog::getExistingDirectory(
      nullptr, "Выберите директорию для модифицырованных фалов",
      QDir::homePath());
  if (directori_save.isEmpty()) {
    QMessageBox::critical(this, "Предупреждение",
                          "Укажите дерикторию для сохранения.");
    on_path_save_clicked();
  }
  ui->path_save_3->setText(directori_save);
}

void MainWindow::on_modify_clicked() {
  if (directori_file.isEmpty()) {
    on_choice_clicked();
  } else if (directori_save.isEmpty()) {
    on_path_save_clicked();
  }

  mask = ui->mask_2->text();
  if (mask.isEmpty()) {
    int type = ui->mask->currentIndex();
    mask = (type == 0) ? ".txt" : ".bin";
  } else {
    if (mask[0] != '.') {
      mask = "." + mask;
    }
  }

  QDir dir(directori_file);

  QStringList filters;
  filters << "*" + mask;

  files = dir.entryList(filters, QDir::Files);

  if (ui->timer->isChecked()) {
    foreach (QString file, files) {
      processExistingFiles(file);
    }

    int checkInterval = ui->spinBox->value();
    checkInterval *= 1000;
    timer->start(checkInterval);
  } else {
    foreach (QString file, files) {
      processExistingFiles(file);
    }
  }
}

void MainWindow::processExistingFiles(const QString& file) {
  QDir dir(directori_file);
  QString filePath = dir.absoluteFilePath(file);
  QFileInfo fileInfo(file);
  QString fileName = fileInfo.baseName();

  if (!filePath.isNull() && !filePath.isEmpty()) {
    QFile file(filePath);

    if (file.open(QIODevice::ReadOnly)) {
      QByteArray fileData = file.readAll();
      file.close();
      xorByteArray(fileData);
      if (ui->checkBox->isChecked()) {
        QFile file(filePath);
        file.remove();
      }
      saveFile(fileData, fileName, mask);
    }
  }
}

void MainWindow::timerSlot() {
  QDir dir(directori_file);
  QStringList filters;
  filters << "*" + mask;
  QStringList newFiles = dir.entryList(filters, QDir::Files);
  QStringList addedItems;

  for (const QString& item : newFiles) {
    if (!files.contains(item)) {
      addedItems << item;
    }
  }

  foreach (QString file, addedItems) {
    processExistingFiles(file);
  }
}

void MainWindow::xorByteArray(QByteArray& fileData) {
  uint64_t xorValue = ui->variable->text().toULongLong();
  int size = fileData.size();
  int xorSize = sizeof(uint64_t);

  for (int i = 0; i < size; i += xorSize) {
    uint64_t block = 0;

    for (int j = 0; j < xorSize && (i + j) < size; ++j) {
      block = (block << 8) | static_cast<uint8_t>(fileData[i + j]);
    }

    block ^= xorValue;

    for (int j = xorSize - 1; j >= 0 && (i + j) < size; --j) {
      fileData[i + j] = static_cast<char>((block >> (8 * j)) & 0xFF);
    }
  }
}

void MainWindow::saveFile(const QByteArray fileData, const QString& fileName,
                          const QString& mask) {
  QString newFileName;

  chengeNameModifyFile(fileName, mask, newFileName);

  QDir dir(directori_save);
  QString fullFilePath = dir.absoluteFilePath(newFileName + mask);
  QFile file(fullFilePath);

  if (file.open(QIODevice::WriteOnly)) {
    qint64 bytesWritten = file.write(fileData);

    if (bytesWritten == -1) {
      qDebug() << "Error writing data to file: " << fullFilePath;
    } else {
      qDebug() << "Data successfully written to file: " << fullFilePath;
    }

    file.close();
  } else {
    qDebug() << "Error opening file for writing: " << fullFilePath;
  }
}

void MainWindow::chengeNameModifyFile(const QString& fileName,
                                      const QString& mask,
                                      QString& newFileName) {
  QDir dir(directori_save);
  QStringList filters;
  filters << "*" + mask;
  QStringList files = dir.entryList(filters, QDir::Files);

  if (ui->path_save_2->currentIndex() == 0) {
    QString str = fileName + mask;

    foreach (QString file, files) {
      if (str == file) {
        QDateTime dateTime = QDateTime::currentDateTime();
        QString currentDateTime = dateTime.toString("dd.MM.yy_HH.mm.ss");
        newFileName = fileName + "-" + currentDateTime;
        return;
      }
    }

    newFileName = fileName;
  } else {
    foreach (QString file, files) {
      QString filePath = dir.absoluteFilePath(file);
      if (fileName == file) {
        QFile fileToRemove(filePath);
        fileToRemove.remove();
        break;
      }
    }

    newFileName = fileName;
  }
}

void MainWindow::on_modify_2_clicked() { timer->stop(); }
