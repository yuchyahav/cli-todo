#pragma once

#include <string>
#include <vector>

#include "model.h"

namespace Todo
{
enum class MenuOptions
{
  EXIT = 0,
  ADD,
  REMOVE,
  DISPLAY,
  CHANGE_STATUS,
  INVALID
};

class View
{
public:
  View() = default;

  MenuOptions get_menu_opt();

  std::string get_task_desc(const std::string &msg);

  size_t get_index(const std::string &msg);

  void display_list(const std::vector<Todo::Task> &todo_list, size_t level = 0);

  void display_msg(const std::string &msg);
};
}  // namespace Todo
