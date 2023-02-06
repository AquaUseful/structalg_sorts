#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>
#include <memory>
#include <qmainwindow.h>
#include <qobjectdefs.h>
#include <qwidget.h>
#include <random>

#include "ui_Main.h"

#include "Timer.hpp"

namespace ui {
class Main : public QMainWindow {
  Q_OBJECT
public:
  using ui_t = Ui::MainFormUi;
  using ui_ptr_t = std::unique_ptr<ui_t>;

  using value_t = std::uint16_t;
  using randdev_t = std::random_device;
  using randgen_t = std::mt19937_64;
  using randdist_t = std::uniform_int_distribution<value_t>;

public:
  explicit Main(QWidget * = nullptr);
  virtual ~Main() = default;

private:
  void config_slots();
  void update_swap_sort();
  void update_selection_sort();
  void update_insertion_sort();
  void update_quick_sort();
  void update_internal_sort();
  void get_arr_size();

private slots:
  void update_sort_info();

private:
  ui_ptr_t m_ui;
  randdev_t m_rdev;
  randgen_t m_rgen;

  std::size_t m_arr_size{0};

  const value_t m_min_value{std::numeric_limits<value_t>::min()};
  const value_t m_max_value{std::numeric_limits<value_t>::max()};
};
} // namespace ui