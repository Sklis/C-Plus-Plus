#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::credit_calc_validator() {
  QRegularExpression rx("[0-9]*");
  QValidator *validator1 = new QRegularExpressionValidator(rx, this);
  ui->term_credit->setValidator(validator1);
  rx.setPattern("[0-9]*[.]?[0-9]*");
  QValidator *validator2 = new QRegularExpressionValidator(rx, this);
  ui->sum_credit->setValidator(validator2);
  ui->credit_procent->setValidator(validator2);
}

void MainWindow::on_push_credit_cal_clicked() {
  on_credit_clean_clicked();
  double credit_sum = ui->sum_credit->text().toDouble();
  int credit_term = ui->term_credit->text().toInt();
  double procent = ui->credit_procent->text().toDouble();
  if (credit_sum != 0 && credit_term != 0 && procent != 0) {
    ui->error->clear();
    if (ui->comboBox_term->currentIndex() == 0) {
      credit_term *= 12;
    }

    procent /= 100;
    if (ui->comboBox_type->currentIndex() == 0) {
      annuitet_calc(credit_sum, credit_term, procent);
    } else {
      difference_calc(credit_sum, credit_term, procent);
    }
    setFixedSize(825, 540);
  } else {
    ui->error->setText("Заполнены не все поля!");
  }
}

void MainWindow::on_credit_clean_clicked() {
  ui->payment->setText("");
  ui->total->setText("");
  ui->overpayment->setText("");
  ui->date_credit_finish->clear();
  setFixedSize(825, 290);
}

void add_table(double d, QStandardItemModel *model, int i, int j) {
  QStandardItem *item = new QStandardItem(QString::number(d, 'f', 2));
  model->setItem(i, j, item);
}

void add_table_s(const QString &str, QStandardItemModel *model, int i, int j) {
  QStandardItem *item = new QStandardItem(str);
  model->setItem(i, j, item);
}

void MainWindow::annuitet_calc(double credit_sum, int credit_term,
                               double procent) {
  procent /= 12;
  QDate date_start = ui->date_credit_start->date();
  QDate date_tmp = date_start;
  QDate date_finish = date_start.addMonths(credit_term);
  ui->date_credit_finish->setDate(date_finish);

  QStandardItemModel *model = new QStandardItemModel();
  QStringList labels =
      QObject::tr(
          "Дата платежа;Сумма платежа;Платеж по основному долгу;Платеж "
          "по процентам;Остаток долга")
          .simplified()
          .split(";");
  model->setHorizontalHeaderLabels(labels);

  double payment = credit_sum * procent * (pow((1 + procent), credit_term)) /
                   (pow((1 + procent), credit_term) - 1);
  double payment_total = payment * credit_term;
  double overpayment = 0.0;
  double debt_balance = credit_sum;
  int i = 0;
  for (; date_tmp < date_finish; date_tmp = date_tmp.addMonths(1)) {
    double overpay = debt_balance * procent;
    double pay = payment - overpay;
    debt_balance -= pay;
    QDate date = date_tmp.addMonths(1);
    add_table_s(date.toString("dd-MM-yyyy"), model, i, 0);
    add_table(payment, model, i, 1);
    add_table(pay, model, i, 2);
    add_table(overpay, model, i, 3);
    add_table(debt_balance, model, i, 4);
    i++;
    overpayment += overpay;
  }
  ui->table_result->setModel(model);
  ui->table_result->resizeColumnsToContents();
  ui->table_result->show();
  annuitet_result(payment, overpayment, payment_total);
}

void MainWindow::difference_calc(double credit_sum, const int credit_term,
                                 double procent) {
  //    QDate date_start_term = QDate::currentDate();
  procent /= 12;
  QDate date_start = ui->date_credit_start->date();
  QDate date_finish = date_start.addMonths(credit_term);
  ui->date_credit_finish->setDate(date_finish);
  QDate date_tmp = date_start;
  double start_payment = 0.0;
  double end_payment = 0.0;
  double debt_balance = credit_sum;
  double month_credit = credit_sum / credit_term;
  double total_payment = 0.0;
  double overpayment = 0.0;
  QStandardItemModel *model = new QStandardItemModel();
  QStringList labels =
      QObject::tr(
          "Дата платежа;Сумма платежа;Платеж по основному долгу;Платеж "
          "по процентам;Остаток долга")
          .simplified()
          .split(";");
  model->setHorizontalHeaderLabels(labels);
  int i = 0;
  for (int j = 1; date_tmp < date_finish;
       date_tmp = date_tmp.addMonths(1), j++) {
    double payment =
        month_credit + (credit_sum - (j - 1) * month_credit) * procent;
    if (i == 0) {
      start_payment = payment;
    } else if (i != 0 && i == credit_term - 1) {
      end_payment = payment;
    }
    total_payment += payment;

    double overpay = debt_balance * procent;
    double pay = payment - overpay;
    debt_balance -= pay;
    overpayment += overpay;
    QDate date = date_tmp.addMonths(1);
    add_table_s(date.toString("dd-MM-yyyy"), model, i, 0);
    add_table(payment, model, i, 1);
    add_table(pay, model, i, 2);
    add_table(overpay, model, i, 3);
    add_table(debt_balance, model, i, 4);
    i++;
  }

  if (credit_term == 1) {
    annuitet_result(start_payment, overpayment, total_payment);
  } else {
    difference_result(start_payment, end_payment, overpayment, total_payment);
  }
  ui->table_result->setModel(model);
  ui->table_result->resizeColumnsToContents();
  ui->table_result->show();
}

void MainWindow::annuitet_result(const double payment, const double overpayment,
                                 const double payment_total) {
  char result_str[255] = {'\0'};
  setlocale(LC_NUMERIC, "C");
  sprintf(result_str, "%.2f", payment);
  ui->payment->setText(result_str);
  memset(result_str, '\0', 255);
  sprintf(result_str, "%.2f", overpayment);
  ui->overpayment->setText(result_str);
  memset(result_str, '\0', 255);
  sprintf(result_str, "%.2f", payment_total);
  ui->total->setText(result_str);
}

void MainWindow::difference_result(const double start_payment,
                                   const double end_payment,
                                   const double overpayment,
                                   const double payment_total) {
  char result_str[255] = {'\0'};
  setlocale(LC_NUMERIC, "C");
  sprintf(result_str, "%.2f", start_payment);
  strcat(result_str, "...");
  char str[255] = {'\0'};
  sprintf(str, "%.2f", end_payment);
  strcat(result_str, str);
  ui->payment->setText(result_str);
  memset(result_str, '\0', 255);
  sprintf(result_str, "%.2f", overpayment);
  ui->overpayment->setText(result_str);
  memset(result_str, '\0', 255);
  sprintf(result_str, "%.2f", payment_total);
  ui->total->setText(result_str);
}
