#include "Main.hpp"

#include <algorithm>
#include <iostream>
#include <memory>
#include <qmainwindow.h>
#include <qobjectdefs.h>
#include <qwidget.h>
#include <vector>

#include "Timer.hpp"
#include "direct_insertion_sort.hpp"
#include "direct_selection_sort.hpp"
#include "direct_swap_sort.hpp"
#include "internal_sort.hpp"
#include "quick_sort.hpp"

ui::Main::Main(QWidget *parent)
    : QMainWindow(parent), m_ui{std::make_unique<ui_t>()}, m_rdev{} {
  m_ui->setupUi(this);
  m_ui->retranslateUi(this);
  m_rgen.seed(m_rgen());
  config_slots();
}

void ui::Main::config_slots() {
  connect(m_ui->exitBtn, SIGNAL(clicked()), this, SLOT(close()));
  connect(m_ui->sortBtn, SIGNAL(clicked()), this, SLOT(update_sort_info()));
}

void ui::Main::update_sort_info() {
  get_arr_size();
  update_swap_sort();
  update_insertion_sort();
  update_selection_sort();
  update_quick_sort();
  update_internal_sort();
}

void ui::Main::update_swap_sort() {
  randdist_t dist(m_min_value, m_max_value);
  std::vector<value_t> arr(m_arr_size);
  std::generate(arr.begin(), arr.end(),
                [this, &dist]() { return dist(m_rgen); });
  const auto result =
      Timer::measure(direct_swap_sort<typename decltype(arr)::iterator>,
                     arr.begin(), arr.end());

  m_ui->resultsTable->item(0, 1)->setText(
      QString::number(result.func_result.comparisons));
  m_ui->resultsTable->item(0, 2)->setText(
      QString::number(result.func_result.swaps));
  m_ui->resultsTable->item(0, 3)->setText(
      QString::number(result.duration.count()));
}

void ui::Main::update_selection_sort() {
  randdist_t dist(m_min_value, m_max_value);
  std::vector<value_t> arr(m_arr_size);
  std::generate(arr.begin(), arr.end(),
                [this, &dist]() { return dist(m_rgen); });
  const auto result =
      Timer::measure(direct_selection_sort<typename decltype(arr)::iterator>,
                     arr.begin(), arr.end());

  m_ui->resultsTable->item(1, 1)->setText(
      QString::number(result.func_result.comparisons));
  m_ui->resultsTable->item(1, 2)->setText(
      QString::number(result.func_result.swaps));
  m_ui->resultsTable->item(1, 3)->setText(
      QString::number(result.duration.count()));
}

void ui::Main::update_insertion_sort() {
  randdist_t dist(m_min_value, m_max_value);
  std::vector<value_t> arr(m_arr_size);
  std::generate(arr.begin(), arr.end(),
                [this, &dist]() { return dist(m_rgen); });
  const auto result =
      Timer::measure(direct_insertion_sort<typename decltype(arr)::iterator>,
                     arr.begin(), arr.end());

  m_ui->resultsTable->item(2, 1)->setText(
      QString::number(result.func_result.comparisons));
  m_ui->resultsTable->item(2, 2)->setText(
      QString::number(result.func_result.swaps));
  m_ui->resultsTable->item(2, 3)->setText(
      QString::number(result.duration.count()));
}

void ui::Main::update_quick_sort() {
  randdist_t dist(m_min_value, m_max_value);
  std::vector<value_t> arr(m_arr_size);
  std::generate(arr.begin(), arr.end(),
                [this, &dist]() { return dist(m_rgen); });
  const auto result = Timer::measure(
      quick_sort<typename decltype(arr)::iterator>, arr.begin(), arr.end());

  m_ui->resultsTable->item(4, 1)->setText(
      QString::number(result.func_result.comparisons));
  m_ui->resultsTable->item(4, 2)->setText(
      QString::number(result.func_result.swaps));
  m_ui->resultsTable->item(4, 3)->setText(
      QString::number(result.duration.count()));
}

void ui::Main::update_internal_sort() {
  randdist_t dist(m_min_value, m_max_value);
  std::vector<value_t> arr(m_arr_size);
  std::generate(arr.begin(), arr.end(),
                [this, &dist]() { return dist(m_rgen); });
  const auto result = Timer::measure(
      internal_sort<typename decltype(arr)::iterator>, arr.begin(), arr.end());

  m_ui->resultsTable->item(5, 1)->setText(
      QString::number(result.func_result.comparisons));
  m_ui->resultsTable->item(5, 2)->setText(
      QString::number(result.func_result.swaps));
  m_ui->resultsTable->item(5, 3)->setText(
      QString::number(result.duration.count()));
}

void ui::Main::get_arr_size() { m_arr_size = m_ui->arrSize->value(); }