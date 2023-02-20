#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>
#include <memory>
#include <qmainwindow.h>
#include <qobjectdefs.h>
#include <qwidget.h>
#include <random>
#include <vector>

#include "SortStats.hpp"
#include "ui_Main.h"

#include "Timer.hpp"

namespace ui {
class Main : public QMainWindow {
  Q_OBJECT
public:
  using ui_t = Ui::MainFormUi;
  using ui_ptr_t = std::unique_ptr<ui_t>;

  using value_t = std::int16_t;
  using randdev_t = std::random_device;
  using randgen_t = std::mt19937_64;
  using randdist_t = std::uniform_int_distribution<value_t>;
  using array_t = std::vector<value_t>;

public:
  explicit Main(QWidget * = nullptr);
  virtual ~Main() = default;

private:
  void config_slots();
  void update_shell_sort();
  void update_swap_sort();
  void update_selection_sort();
  void update_insertion_sort();
  void update_quick_sort();
  void update_internal_sort();
  void update_counting_sort();
  void clear_sort_info(int);
  void update_array();
  void display_sort_info(int, SortStats, long, bool);

private slots:
  void update_sort_info();
  void update_arr_size();

private:
  ui_ptr_t m_ui;
  randdev_t m_rdev;
  randgen_t m_rgen;
  array_t m_array;

  std::size_t m_arr_size{0};

  const value_t m_min_value{std::numeric_limits<value_t>::min() / 10};
  const value_t m_max_value{std::numeric_limits<value_t>::max() / 10};
};
} // namespace ui