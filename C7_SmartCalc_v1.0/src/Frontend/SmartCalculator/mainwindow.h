#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDate>
#include <QLineEdit>
#include <QMainWindow>
#include <QString>
#include <QVector>
#include <cctype>

extern "C" {
#include "../../Backend/smartCalc.h"
}

#define START                       \
  ui->tab_result_mistakes->clear(); \
  QPushButton *button = (QPushButton *)sender()
#define INP QString inp = ui->input_line->text()
#define FIN QString fin = ui->finish_line->text()
#define TMP QString tmp = ui->tmp_line->text()
#define LAST_I QChar lastChar = inp.at(inp.length() - 1)
#define LAST_I_2 QChar lastLastChar = inp.at(inp.length() - 2)
#define LEN_F std::size_t len_f = ui->finish_line->text().length()
#define LEN_I std::size_t len_i = ui->input_line->text().length()
#define LEN_T std::size_t len_t = ui->tmp_line->text().length()
#define FINISH \
  ui->finish_line->setText(ui->finish_line->text() + button->text() + "|");
#define CHECK_BRACKET                                                          \
  if (!ui->tmp_line->text().isEmpty()) {                                       \
    ui->finish_line->setText(ui->finish_line->text() + ui->tmp_line->text() +  \
                             "|");                                             \
    ui->tmp_line->setText("");                                                 \
  }                                                                            \
  LAST_I;                                                                      \
  if (lastChar.isDigit() || lastChar == ')' || lastChar == 'x' ||              \
      lastChar == 'i') {                                                       \
    ui->input_line->setText(ui->input_line->text() + button->text());          \
    FINISH;                                                                    \
  } else if (lastChar == '(') {                                                \
    ui->tab_result_mistakes->setText("Пропущено выражение.");                  \
  } else {                                                                     \
    ui->tab_result_mistakes->setText("Синтаксическая ошибка (Syntax Error)!"); \
  }

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/// @brief Класс отображения приложения
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:

  /// @brief Устанавливает начальные данные для работы
  void start_settings();

  /// @brief Устанавливает какие символы можно вводить
  void set_validators();

  /// @brief Переключает калькуляторы и маняет размер окна
  void on_tabWidget_currentChanged(int index);

  /// @brief Открывает дополнительное окно для графика
  void on_checkBox_clicked(bool checked);

  /// @brief Назначает выполнение функций при нажатии на кнопки
  void connect_signals();
  /// @brief Добавляет цифры во входную строку
  void digits_numbers();

  /// @brief Добавляет математический оператор
  void math_operations();

  /// @brief Проверяет корректность и устанавливает степень и mod
  void on_button_mod_or_pow_clicked();

  /// @brief Меняет знак
  void operations();

  /// @brief Вставляет функции во входную строку
  void functions();

  /// @brief Стирает все данные
  void on_button_AC_clicked();

  /// @brief Устанавливает точку
  void on_button_dot_clicked();

  /// @brief Удаляет один символ с конца строки
  void on_button_del_clicked();

  /// @brief Устанавливает левую кнопку
  void on_button_left_bracket_clicked();

  /// @brief Устанавливает правую кнопку
  void on_button_right_bracket_clicked();

  /// @brief Проверяет корректность и устаналивает pi и х
  void on_button_pi_or_x_clicked();

  /// @brief Выполняет математические расчеты и выводи результат
  void on_button_equal_clicked();

  /// @brief Строит график
  void on_pushButton_graf_clicked();

  /// @brief Задает размеры поля графика и все привязки для него
  void makePlot();

  /// @brief Очищает поле графика
  void on_pushButton_graf_3_clicked();

  /// @brief Валидные символы для кредитного калькулятора
  void credit_calc_validator();

  /// @brief Валидные символы для депозитного калькулятора
  void deposit_calc_validator();

  /// @brief Принимает все данные для расчета и вызывает необходимую функцию для
  /// расчета
  void on_push_credit_cal_clicked();

  /// @brief Очищает кредитный калькулятор
  void on_credit_clean_clicked();

  /// @brief Производит вычисление кредита для аннуитетного платежа
  void annuitet_calc(double credit_sum, int credit_term, double procent);

  /// @brief Производит вычисление кредита для дифференцированного платежа
  void difference_calc(double credit_sum, int credit_term, double procent);

  /// @brief Выводи результат вычислений
  void annuitet_result(double payment, double overpayment,
                       double payment_total);

  /// @brief Выводи результат вычислений
  void difference_result(double start_payment, double end_payment,
                         double overpayment, double payment_total);

  /// @brief Принимает данные для расчета в депозитном калькуляторе
  void on_deposit_calculation_clicked();

  /// @brief Очищает депозитный калькулятор
  void clear_deposit_line();

  /// @brief Первоначальная обработка даных в депозитном калькуляторе
  void deposit_calculation();

  /// @brief Вычисляет последнюю дату вклада
  QDate get_end_date_term_deposit();

  /// @brief Определяет переодичность выплат
  QDate get_next_date_payment(QDate date_payment);

  /// @brief Определяет периодичность пополнения и частичного снятия
  void get_next_date_replanishment_or_withdraw(QDate *date, const int type);

  /// @brief Определяет необходимость пополнения вклада
  void add_replanishment(double *deposit_sum, QDate *date_replanishment);

  /// @brief Определяет необходимость частичного снятия
  void sub_withdraw(double *deposit_sum, QDate *date_withdraw);

  /// @brief Расчитывает дневные проценты в году
  void procent_calculation(const double deposit_sum, const QDate date,
                           double *sum_procent_of_period,
                           double *total_sum_procent);

  /// @brief Вычисляет процент налога
  void add_sum_tax(double *sum_tax, double *sum_procent_of_year);

  /// @brief Вычисление годовых процентов
  void add_sum_procent_of_year(double *sum_procent_of_year,
                               double *sum_procent_of_period);

  /// @brief Проверяет дату пополнения или частичного снятия
  void check_date_replanishment_or_withdraw(
      const QDate date_start_term, const double sum, const int period,
      QDate *date_replanishment_or_withdraw);

  /// @brief Выводит результаты расчета
  void set_deposit_result(const double total_sum_procent, const double sum_tax,
                          const double deposit_sum);

  /// @brief Удаляет произведенные расчеты
  void on_pushButton_clicked();

 private:
  Ui::MainWindow *ui;
};
#endif  // MAINWINDOW_H
