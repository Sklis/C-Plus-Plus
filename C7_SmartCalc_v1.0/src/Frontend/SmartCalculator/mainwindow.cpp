#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  start_settings();
  connect_signals();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::start_settings() {
  setFixedSize(624, 533);
  makePlot();
  set_validators();
  ui->tabWidget->setCurrentIndex(0);
  QDate date_today = QDate::currentDate();
  ui->date_credit_start->setDate(date_today);
  ui->date_credit_finish->setDate(date_today);
  ui->deposit_start_term->setDate(date_today);
  ui->deposit_date_replanishment->setDate(date_today);
  ui->deposit_date_withdraw->setDate(date_today);
  ui->date_deposit_finish->setDate(date_today);
}

void MainWindow::set_validators() {
  credit_calc_validator();
  deposit_calc_validator();
}

void MainWindow::on_tabWidget_currentChanged(int index) {
  if (index == 0) {
    if (ui->checkBox->isChecked()) {
      setFixedSize(1126, 533);
    } else {
      setFixedSize(624, 533);
    }
  } else if (index == 1) {
    setFixedSize(825, 290);
  } else if (index == 2) {
    setFixedSize(1120, 450);
  }
}

void MainWindow::on_checkBox_clicked(bool checked) {
  if (checked) {
    setFixedSize(1126, 533);
  } else {
    setFixedSize(624, 533);
  }
}

void MainWindow::connect_signals() {
  connect(ui->button_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_00, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->button_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->button_sum, SIGNAL(released()), this, SLOT(math_operations()));
  connect(ui->button_sub, SIGNAL(released()), this, SLOT(math_operations()));
  connect(ui->button_div, SIGNAL(released()), this, SLOT(math_operations()));
  connect(ui->button_mul, SIGNAL(released()), this, SLOT(math_operations()));

  connect(ui->button_pow, SIGNAL(released()), this,
          SLOT(on_button_mod_or_pow_clicked()));
  connect(ui->button_mod, SIGNAL(released()), this,
          SLOT(on_button_mod_or_pow_clicked()));

  connect(ui->button_sign, SIGNAL(released()), this, SLOT(operations()));

  connect(ui->button_acos, SIGNAL(released()), this, SLOT(functions()));
  connect(ui->button_asin, SIGNAL(released()), this, SLOT(functions()));
  connect(ui->button_atan, SIGNAL(released()), this, SLOT(functions()));
  connect(ui->button_cos, SIGNAL(released()), this, SLOT(functions()));
  connect(ui->button_sin, SIGNAL(released()), this, SLOT(functions()));
  connect(ui->button_tan, SIGNAL(released()), this, SLOT(functions()));
  connect(ui->button_sqrt, SIGNAL(released()), this, SLOT(functions()));
  connect(ui->button_log, SIGNAL(released()), this, SLOT(functions()));
  connect(ui->button_ln, SIGNAL(released()), this, SLOT(functions()));

  connect(ui->button_x, SIGNAL(released()), this,
          SLOT(on_button_pi_or_x_clicked()));
  connect(ui->button_pi, SIGNAL(released()), this,
          SLOT(on_button_pi_or_x_clicked()));
}

void MainWindow::digits_numbers() {
  START;
  INP;
  LEN_I;
  if (len_i > 0) {
    LAST_I;
    if (ui->tmp_line->text().isEmpty() && lastChar.isDigit()) {
      FIN;
      fin.chop(1);
      ui->finish_line->setText(fin + button->text() + "|");
      ui->input_line->setText(ui->input_line->text() + button->text());
    } else if (lastChar.isDigit() || lastChar == 'd' || lastChar == '+' ||
               lastChar == '-' || lastChar == '*' || lastChar == '/' ||
               lastChar == '(' || ui->input_line->text().endsWith("^")) {
      ui->tmp_line->setText(ui->tmp_line->text() + button->text());
      ui->input_line->setText(ui->input_line->text() + button->text());
    } else if (lastChar == ')' || lastChar == 'x' || lastChar == 'i') {
      ui->tab_result_mistakes->setText("Синтаксическая ошибка (Syntax Error)!");
    } else {
      ui->tmp_line->setText(ui->tmp_line->text() + button->text());
      ui->input_line->setText(ui->input_line->text() + button->text());
    }
  } else {
    ui->tmp_line->setText(ui->tmp_line->text() + button->text());
    ui->input_line->setText(ui->input_line->text() + button->text());
  }
}

void MainWindow::math_operations() {
  START;
  INP;
  FIN;
  LEN_I;
  if (!ui->tmp_line->text().isEmpty()) {
    ui->finish_line->setText(ui->finish_line->text() + ui->tmp_line->text() +
                             "|");
    ui->tmp_line->setText("");
  }
  if (len_i > 0) {
    LAST_I;
    if (lastChar == '(') {
      ui->tab_result_mistakes->setText("Синтаксическая ошибка (Syntax Error)!");
    } else if ((lastChar == '-' || lastChar == '+') || lastChar == '*' ||
               lastChar == '/' || lastChar == '^') {
      inp.chop(1);
      fin.chop(2);
      ui->input_line->setText(inp + button->text());
      FINISH;
    } else if (lastChar == 'd') {
      inp.chop(3);
      fin.chop(4);
      ui->input_line->setText(inp + button->text());
      FINISH;
    } else {
      ui->input_line->setText(ui->input_line->text() + button->text());
      FINISH;
    }
  } else {
    ui->tab_result_mistakes->setText("Синтаксическая ошибка (Syntax Error)!");
  }
}

void MainWindow::on_button_mod_or_pow_clicked() {
  START;
  INP;
  LEN_I;
  if (!ui->tmp_line->text().isEmpty()) {
    ui->finish_line->setText(ui->finish_line->text() + ui->tmp_line->text() +
                             "|");
    ui->tmp_line->clear();
  }
  if (len_i > 0) {
    LAST_I;
    if (lastChar == '^' && button->text() == '^') {
      ui->input_line->setText(ui->input_line->text() + button->text());
      FINISH;
    } else if (lastChar.isDigit() || lastChar == ')') {
      ui->input_line->setText(ui->input_line->text() + button->text());
      FINISH;
    } else {
      ui->tab_result_mistakes->setText("Синтаксическая ошибка (Syntax Error)!");
    }
  } else {
    ui->tab_result_mistakes->setText("Введите сначала данные.");
  }
}

void MainWindow::operations() {
  ui->tab_result_mistakes->clear();
  INP;
  FIN;
  LEN_I;
  LEN_T;
  if (!ui->tmp_line->text().isEmpty()) {
    inp.chop(len_t);
    if (ui->tmp_line->text().contains('-')) {
      ui->tmp_line->setText(ui->tmp_line->text().replace("-", ""));
    } else {
      ui->tmp_line->setText(ui->tmp_line->text().insert(0, "-"));
    }
    ui->input_line->setText(inp + ui->tmp_line->text());
  }
  if (len_i > 1) {
    if (ui->input_line->text().endsWith("(pi)") &&
        ui->finish_line->text().endsWith("pi|")) {
      inp.chop(3);
      fin.chop(3);
      ui->input_line->setText(inp + "-pi)");
      ui->finish_line->setText(fin + "-pi|");
    } else if (ui->input_line->text().endsWith("(-pi)") &&
               ui->finish_line->text().endsWith("-pi|")) {
      inp.chop(4);
      fin.chop(4);
      ui->input_line->setText(inp + "pi)");
      ui->finish_line->setText(fin + "pi|");
    } else if (ui->input_line->text().endsWith("(x)") &&
               ui->finish_line->text().endsWith("x|")) {
      inp.chop(2);
      fin.chop(2);
      ui->input_line->setText(inp + "-x)");
      ui->finish_line->setText(fin + "-x|");
    } else if (ui->input_line->text().endsWith("(-x)") &&
               ui->finish_line->text().endsWith("-x|")) {
      inp.chop(3);
      fin.chop(3);
      ui->input_line->setText(inp + "x)");
      ui->finish_line->setText(fin + "x|");
    }
  }
}

void MainWindow::functions() {
  START;
  INP;
  LEN_I;
  if (len_i > 1) {
    if (!ui->tmp_line->text().isEmpty()) {
      ui->finish_line->setText(ui->finish_line->text() + ui->tmp_line->text() +
                               "|");
      ui->tmp_line->setText("");
    }
    LAST_I;
    if (lastChar == ')' || lastChar == 'd' || lastChar.isDigit()) {
      ui->tab_result_mistakes->setText("Синтаксическая ошибка (Syntax Error)!");
    } else if (!ui->tmp_line->text().isEmpty()) {
      ui->finish_line->setText(ui->finish_line->text() + ui->tmp_line->text() +
                               "|" + button->text() + "|(|");
      ui->input_line->setText(ui->input_line->text() + button->text() + "(");
    } else {
      ui->finish_line->setText(ui->finish_line->text() + button->text() + "|(|");
      ui->input_line->setText(ui->input_line->text() + button->text() + "(");
    }
  } else if (len_i == 1) {
    LAST_I;
    if (lastChar == '-' || lastChar == '(') {
      //            ui->input_line->setText("/*-");
      ui->finish_line->setText(ui->finish_line->text() + button->text() +
                               "|(|");
      ui->input_line->setText(ui->input_line->text() + button->text() + "(");
    } else {
      ui->tab_result_mistakes->setText("Синтаксическая ошибка (Syntax Error)!");
    }
  } else {
    ui->finish_line->setText(ui->finish_line->text() + button->text() + "|(|");
    ui->input_line->setText(ui->input_line->text() + button->text() + "(");
  }
}

void MainWindow::on_button_AC_clicked() {
  ui->finish_line->clear();
  ui->input_line->clear();
  ui->tmp_line->clear();
  ui->tab_result_mistakes->clear();
}

void MainWindow::on_button_dot_clicked() {
  if (!(ui->tmp_line->text().contains('.')) &&
      !(ui->tmp_line->text().isEmpty())) {
    ui->tmp_line->setText(ui->tmp_line->text() + ".");
    ui->input_line->setText(ui->input_line->text() + ".");
  } else if (ui->tmp_line->text().isEmpty()) {
    ui->tab_result_mistakes->setText("Синтаксическая ошибка (Syntax Error)!");
  }
}

void MainWindow::on_button_del_clicked() {
  ui->tab_result_mistakes->clear();
  INP;
  LEN_I;
  FIN;
  if (len_i > 0) {
    LAST_I;

    if (!ui->tmp_line->text().isEmpty()) {
      TMP;
      tmp.chop(1);
      inp.chop(1);
      ui->tmp_line->setText(tmp);
      ui->input_line->setText(inp);
      return;
    }
    if (ui->finish_line->text().endsWith('|')) {
      fin.chop(1);
      ui->finish_line->setText(fin);
    }
    if (len_i > 1) {
      LAST_I_2;
      if (inp.endsWith("(pi)")) {
        inp.chop(4);
        fin.chop(3);
        ui->finish_line->setText(fin + "|");
        ui->input_line->setText(inp);
      } else if (inp.endsWith("(-pi)")) {
        inp.chop(5);
        fin.chop(4);
        ui->finish_line->setText(fin + "|");
        ui->input_line->setText(inp);
      } else if (inp.endsWith("(x)")) {
        inp.chop(3);
        fin.chop(2);
        ui->finish_line->setText(fin + "|");
        ui->input_line->setText(inp);
      } else if (inp.endsWith("(-x)")) {
        inp.chop(4);
        fin.chop(3);
        ui->finish_line->setText(fin + "|");
        ui->input_line->setText(inp);
      } else if (lastLastChar.isLetter() && lastChar == '(') {
        do {
          inp.chop(1);
          fin.chop(1);
          ui->finish_line->setText(fin);
          ui->input_line->setText(inp);
          std::size_t len = inp.length();
          if (len > 0) {
            QChar s = inp.at(inp.length() - 1);
            if (s.isLetter())
              continue;
            else
              break;
          } else {
            break;
          }
        } while (true);
      }
    }
    if (lastChar.isLetter()) {
      do {
        inp.chop(1);
        fin.chop(1);
        ui->finish_line->setText(fin);
        ui->input_line->setText(inp);
        std::size_t len = inp.length();
        ;
        if (len > 0) {
          QChar s = inp.at(inp.length() - 1);
          if (s.isLetter())
            continue;
          else
            break;
        } else {
          break;
        }
      } while (true);
    } else {
      inp.chop(1);
      fin.chop(1);
      ui->finish_line->setText(fin);
      ui->input_line->setText(inp);
    }
  } else {
    ui->tab_result_mistakes->setText("Вы все удалили! Удалять больше нечего.");
  }
}

void MainWindow::on_button_left_bracket_clicked() {
  START;
  INP;
  LEN_I;
  if (len_i > 0) {
    if (!ui->tmp_line->text().isEmpty()) {
      ui->finish_line->setText(ui->finish_line->text() + ui->tmp_line->text() +
                               "|");
      ui->tmp_line->setText("");
    }
    LAST_I;
    if (len_i == 1) {
      if (lastChar == '-' || lastChar == '+' || lastChar == '(') {
        ui->input_line->setText(inp + button->text());
        ui->finish_line->setText(ui->finish_line->text() + button->text() +
                                 "|");
      } else {
        ui->tab_result_mistakes->setText(
            "Синтаксическая ошибка (Syntax Error)!");
      }
    } else {
      if (lastChar == ')' || lastChar.isDigit() || lastChar == 'x' ||
          lastChar == 'i') {
        ui->tab_result_mistakes->setText(
            "Синтаксическая ошибка (Syntax Error)!");
      } else {
        ui->input_line->setText(inp + button->text());
        ui->finish_line->setText(ui->finish_line->text() + button->text() +
                                 "|");
      }
    }
  } else {
    ui->input_line->setText(ui->input_line->text() + button->text());
    ui->finish_line->setText(ui->finish_line->text() + button->text() + "|");
  }
}

void MainWindow::on_button_right_bracket_clicked() {
  START;
  ui->input_line->setText(ui->input_line->text() + button->text());
  INP;
  QByteArray array = inp.toLocal8Bit();
  char *input_str = array.data();
  int num = 0;
  int flag = check_brackets_result(input_str, &num);
  inp.chop(1);
  ui->input_line->setText(inp);
  LEN_I;
  if (len_i > 0) {
    LAST_I;
    if (len_i == 1) {
      ui->tab_result_mistakes->setText("Так делать нельзя.");
    } else if (flag == OK) {
      if (len_i > 1) {
        if (!ui->tmp_line->text().isEmpty()) {
          ui->finish_line->setText(ui->finish_line->text() +
                                   ui->tmp_line->text() + "|" + button->text() +
                                   "|");
          ui->input_line->setText(ui->input_line->text() + button->text());
          ui->tmp_line->setText("");
        } else if (lastChar.isDigit() || lastChar == ')' || lastChar == 'x' ||
                   lastChar == 'i') {
          ui->input_line->setText(ui->input_line->text() + button->text());
          FINISH;
        } else if (lastChar == '(') {
          ui->tab_result_mistakes->setText("Пропущено выражение.");
        } else {
          ui->tab_result_mistakes->setText(
              "Синтаксическая ошибка (Syntax Error)!");
        }
      }
    } else if (flag == BRACKET_MISSING) {
      if (!ui->tmp_line->text().isEmpty()) {
        ui->finish_line->setText(ui->finish_line->text() +
                                 ui->tmp_line->text() + "|");
        ui->tmp_line->setText("");
      }
      if (lastChar.isDigit() || lastChar == ')' || lastChar == 'x' ||
          lastChar == 'i') {
        ui->input_line->setText(ui->input_line->text() + button->text());
        FINISH;
        ui->tab_result_mistakes->setText("Не закрыто еще " +
                                         QString::number(num) + " скобок.");
      } else if (lastChar == '(') {
        ui->tab_result_mistakes->setText("Пропущено выражение.");
      } else {
        ui->tab_result_mistakes->setText(
            "Синтаксическая ошибка (Syntax Error)!");
      }
    } else if (flag == EXTRA_BRACKET) {
      ui->tab_result_mistakes->setText("Много закрывающих скобок.");
    }
  }
}

void MainWindow::on_button_pi_or_x_clicked() {
  START;
  INP;
  LEN_I;
  if (len_i > 0) {
    if (!ui->tmp_line->text().isEmpty()) {
      ui->tab_result_mistakes->setText("Синтаксическая ошибка (Syntax Error)!");
    } else {
      LAST_I;
      if (lastChar == '+' || lastChar == '-' || lastChar == '*' ||
          lastChar == '^' || lastChar == 'd' || lastChar == '/' ||
          lastChar == '(') {
        ui->input_line->setText(ui->input_line->text() + "(" + button->text() +
                                ")");
        FINISH;
      } else {
        ui->tab_result_mistakes->setText(
            "Синтаксическая ошибка (Syntax Error)!");
      }
    }
  } else {
    ui->input_line->setText(ui->input_line->text() + "(" + button->text() +
                            ")");
    FINISH;
  }
}

void MainWindow::on_button_equal_clicked() {
  ui->tab_result_mistakes->setText("");
  if (!ui->tmp_line->text().isEmpty()) {
    ui->finish_line->setText(ui->finish_line->text() + ui->tmp_line->text());
    ui->tmp_line->clear();
  }
  QString fin = ui->finish_line->text();
  QByteArray array = fin.toLocal8Bit();
  char *input_str = array.data();
  int num;
  int flag = check_brackets_result(input_str, &num);
  if (flag == OK) {
    if (!ui->checkBox->isChecked()) {
      ui->finish_line->setText("");
      long double result;
      double x = ui->doubleSpinBox_x->value();
      char *lexems[255] = {0};
      char *RPN[255] = {0};
      char *tmp_out[255] = {0};
      int code = OK;
      to_lexems(input_str, lexems);
      if (lexems_to_RPN(lexems, tmp_out, RPN)) {
        ui->tab_result_mistakes->setText(
            "Не правильное выражение! Проверьте вводимые данные.");
      } else {
        result = answer(RPN, x, &code);

        if (code) {
          ui->tab_result_mistakes->setText("Error!");
        } else {
          QString final = QString::number(result, 'g', 7);
          ui->tab_result_mistakes->setText(final);
        }
      }

    } else {
      ui->tab_result_mistakes->setText(
          "Вы хотели построить график. Если нет, то снимите галочку ↓.");
    }
  } else if (flag == EXTRA_BRACKET) {
    ui->tab_result_mistakes->setText(
        "ЛИШНИЕ ЗАКРЫВАЮЩИЕ СКОБКИ. Проверте выражение.");
  } else if (flag == BRACKET_MISSING) {
    ui->tab_result_mistakes->setText("НЕХВАТАЕТ " + QString::number(num) +
                                     " СКОБОК. Проверьте выражение.");
  }
}

void MainWindow::on_pushButton_graf_clicked() {
  ui->tab_result_mistakes->setText("");
  if (!ui->tmp_line->text().isEmpty()) {
    ui->finish_line->setText(ui->finish_line->text() + ui->tmp_line->text());
    ui->tmp_line->clear();
  }
  QString fin = ui->finish_line->text();
  QByteArray array = fin.toLocal8Bit();
  char *input_str = array.data();
  int num;
  int flag = check_brackets_result(input_str, &num);
  if (flag == OK) {
    if (ui->checkBox->isChecked()) {
      long double result;
      char *lexems[255] = {0};
      char *RPN[255] = {0};
      char *tmp_out[255] = {0};
      int code = OK;
      to_lexems(input_str, lexems);
      if (lexems_to_RPN(lexems, tmp_out, RPN)) {
        ui->tab_result_mistakes->setText(
            "Не правильное выражение! Проверьте вводимые данные.");
      } else {
        if (ui->input_line->text().contains('x')) {
          QVector<double> x, y;
          ui->graph->clearGraphs();
          x.clear();
          y.clear();

          double xMax = ui->doubleSpinBox_x_right->value();
          double step = ui->doubleSpinBox_step->value();
          double X = ui->doubleSpinBox_x_left->value();
          for (; X <= xMax; X += step) {
            result = answer(RPN, X, &code);
            if (code) {
              ui->tab_result_mistakes->setText("Error!");
            } else {
              x.push_back(X);
              y.push_back(result);
            }
          }
          ui->graph->clearGraphs();
          ui->graph->addGraph();
          ui->graph->graph(0)->setData(x, y);
          ui->graph->xAxis->rescale();
          ui->graph->yAxis->rescale();
          if (ui->comboBox->currentIndex() == 0) {
          } else {
            ui->graph->graph(0)->setLineStyle(QCPGraph::lsNone);
            ui->graph->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
          }
          ui->graph->replot();
        } else {
          ui->tab_result_mistakes->setText(
              "Не возможно построить график. Отсутствует переменная!");
        }
      }
    }
  } else if (flag == EXTRA_BRACKET) {
    ui->tab_result_mistakes->setText(
        "ЛИШНИЕ ЗАКРЫВАЮЩИЕ СКОБКИ. Проверте выражение.");
  } else if (flag == BRACKET_MISSING) {
    ui->tab_result_mistakes->setText("НЕХВАТАЕТ " + QString::number(num) +
                                     " СКОБОК. Проверьте выражение.");
  }
}

void MainWindow::makePlot() {
  ui->graph->addGraph();
  ui->graph->xAxis->setLabel("x");
  ui->graph->yAxis->setLabel("y");
  ui->graph->xAxis2->setVisible(true);
  ui->graph->xAxis2->setTickLabels(false);
  ui->graph->yAxis2->setVisible(true);
  ui->graph->yAxis2->setTickLabels(false);
  connect(ui->graph->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->graph->xAxis2,
          SLOT(setRange(QCPRange)));
  connect(ui->graph->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->graph->yAxis2,
          SLOT(setRange(QCPRange)));
  ui->graph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
  ui->graph->xAxis->setRange(-10, 10);
  ui->graph->yAxis->setRange(-10, 10);
}

void MainWindow::on_pushButton_graf_3_clicked() {
  ui->graph->clearGraphs();
  ui->graph->replot();
}
