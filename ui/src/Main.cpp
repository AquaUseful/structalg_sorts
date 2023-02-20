#include "Main.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <qmainwindow.h>
#include <qnamespace.h>
#include <qobjectdefs.h>
#include <qwidget.h>
#include <vector>

#include "SortStats.hpp"
#include "Timer.hpp"
#include "counting_sort.hpp"
#include "insertion_sort.hpp"
#include "internal_sort.hpp"
#include "quick_sort.hpp"
#include "selection_sort.hpp"
#include "shell_sort.hpp"
#include "swap_sort.hpp"

ui::Main::Main(QWidget *parent)
    : QMainWindow(parent), m_ui{std::make_unique<ui_t>()}, m_rdev{} {
  m_ui->setupUi(this);
  m_ui->retranslateUi(this);
  m_rgen.seed(m_rdev());
  config_slots();
}

void ui::Main::config_slots() {
  connect(m_ui->exitBtn, SIGNAL(clicked()), this, SLOT(close()));
  connect(m_ui->sortBtn, SIGNAL(clicked()), this, SLOT(update_sort_info()));
  connect(m_ui->arrSize, SIGNAL(valueChanged(int)), this,
          SLOT(update_arr_size()));
}

void ui::Main::update_sort_info() {
  update_arr_size();
  update_array();

  if (m_ui->resultsTable->item(0, 0)->checkState()) {
    update_swap_sort();
  } else {
    clear_sort_info(0);
  }

  if (m_ui->resultsTable->item(1, 0)->checkState()) {
    update_selection_sort();
  } else {
    clear_sort_info(1);
  }

  if (m_ui->resultsTable->item(2, 0)->checkState()) {
    update_insertion_sort();
  } else {
    clear_sort_info(2);
  }

  if (m_ui->resultsTable->item(3, 0)->checkState()) {
    update_shell_sort();
  } else {
    clear_sort_info(3);
  }

  if (m_ui->resultsTable->item(4, 0)->checkState()) {
    update_quick_sort();
  } else {
    clear_sort_info(4);
  }

  if (m_ui->resultsTable->item(5, 0)->checkState()) {
    update_internal_sort();
  } else {
    clear_sort_info(5);
  }

  if (m_ui->resultsTable->item(6, 0)->checkState()) {
    update_counting_sort();
  } else {
    clear_sort_info(6);
  }
}

void ui::Main::update_swap_sort() {
  auto arr = m_array;
  const auto result =
      Timer::measure(direct_swap_sort<typename decltype(arr)::iterator>,
                     arr.begin(), arr.end());
  display_sort_info(0, result.func_result, result.duration.count(),
                    std::is_sorted(arr.begin(), arr.end()));
}

void ui::Main::update_selection_sort() {
  auto arr = m_array;
  const auto result = Timer::measure(
      selection_sort<typename decltype(arr)::iterator>, arr.begin(), arr.end());
  display_sort_info(1, result.func_result, result.duration.count(),
                    std::is_sorted(arr.begin(), arr.end()));
}

void ui::Main::update_insertion_sort() {
  auto arr = m_array;
  const auto result = Timer::measure(
      insertion_sort<typename decltype(arr)::iterator>, arr.begin(), arr.end());
  display_sort_info(2, result.func_result, result.duration.count(),
                    std::is_sorted(arr.begin(), arr.end()));
}

void ui::Main::update_shell_sort() {
  auto arr = m_array;
  const auto result = Timer::measure(
      shell_sort<typename decltype(arr)::iterator>, arr.begin(), arr.end());
  display_sort_info(3, result.func_result, result.duration.count(),
                    std::is_sorted(arr.begin(), arr.end()));
}

void ui::Main::update_quick_sort() {
  auto arr = m_array;
  const auto result = Timer::measure(
      quick_sort<typename decltype(arr)::iterator>, arr.begin(), arr.end());
  display_sort_info(4, result.func_result, result.duration.count(),
                    std::is_sorted(arr.begin(), arr.end()));
}

void ui::Main::update_internal_sort() {
  auto arr = m_array;
  const auto result = Timer::measure(
      internal_sort<typename decltype(arr)::iterator>, arr.begin(), arr.end());
  display_sort_info(5, SortStats{0, 0}, result.duration.count(),
                    std::is_sorted(arr.begin(), arr.end()));
}

void ui::Main::update_arr_size() {
  m_arr_size = m_ui->arrSize->value();
  const std::size_t array_kbytes = (sizeof(value_t) * m_arr_size) / 1024;
  QString kbytes;
  if (array_kbytes == 0) {
    kbytes = "<1";
  } else {
    kbytes = QString::number(array_kbytes);
  }
  m_ui->arrKbytes->setText(kbytes);
}

void ui::Main::clear_sort_info(int row) {
  for (int col{1}; col <= 3; ++col) {
    m_ui->resultsTable->item(row, col)->setText("");
  }
  m_ui->resultsTable->item(row, 4)->setCheckState(Qt::CheckState::Unchecked);
}

void ui::Main::display_sort_info(int row, SortStats stats, long duration,
                                 bool is_sorted) {
  m_ui->resultsTable->item(row, 1)->setText(QString::number(stats.comparisons));
  m_ui->resultsTable->item(row, 2)->setText(QString::number(stats.swaps));
  m_ui->resultsTable->item(row, 3)->setText(QString::number(duration));

  const Qt::CheckState check_state =
      is_sorted ? Qt::CheckState::Checked : Qt::CheckState::Unchecked;
  m_ui->resultsTable->item(row, 4)->setCheckState(check_state);
}

void ui::Main::update_array() {
  m_array.resize(m_arr_size);
  randdist_t dist(m_min_value, m_max_value);
  std::generate(m_array.begin(), m_array.end(),
                [this, &dist]() { return dist(m_rgen); });
}

void ui::Main::update_counting_sort() {
  auto arr = m_array;
  const auto result = Timer::measure(
      counting_sort<typename decltype(arr)::iterator>, arr.begin(), arr.end());
  display_sort_info(6, result.func_result, result.duration.count(),
                    std::is_sorted(arr.begin(), arr.end()));
}
