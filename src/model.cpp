#include <boost/describe.hpp>
#include <boost/json.hpp>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "model.h"

Todo::Model::Model()
{
  load_file();
}

void Todo::Model::load_file()
{
  dir_init();

  std::ifstream infile{TODO_DIR / TODO_FILE};
  if (infile.is_open() == false)
  {
    std::cerr << "error: file not opened\n";
    std::exit(EXIT_FAILURE);
  }

  size_t size = std::filesystem::file_size(TODO_DIR / TODO_FILE);
  std::string buf(size, ' ');
  infile.read(&buf[0], size);

  infile.close();

  try
  {
    boost::json::value jv = boost::json::parse(buf);
    if (jv.is_array() == false)
    {
      std::cerr << "json parsing error: json was not an array\n";
      std::exit(EXIT_FAILURE);
    }

    todo_list_ = boost::json::value_to<std::vector<Todo::Task>>(jv);
  }
  catch (const std::exception &e)
  {
    std::cerr << "json parsing error: " << e.what() << '\n';
    std::exit(EXIT_FAILURE);
  }
}

void Todo::Model::save_file()
{
  std::ofstream outfile{TODO_DIR / TODO_FILE};
  boost::json::value jv = boost::json::value_from(todo_list_);
  outfile << jv;
  outfile.close();
}

void Todo::Model::dir_init()
{
  try
  {
    if (std::filesystem::exists(TODO_DIR) == false)
    {
      std::filesystem::create_directory(TODO_DIR);
    }

    if (std::filesystem::exists(TODO_DIR / TODO_FILE) == false)
    {
      std::ofstream outfile{TODO_DIR / TODO_FILE};
      outfile << "[]";

      if (outfile.is_open() == false)
      {
        std::cerr << "file could not be initialized\n";
      }
      outfile.close();
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
  }
}

void Todo::Model::add(const std::string &task_desc, size_t index)
{
  if (index != 0)
  {
    if (index > todo_list_.size())
    {
      throw std::out_of_range("Parent task ID is out of range");
    }
    todo_list_[index - 1].child_tasks.emplace_back(Task{task_desc, {}, false});
  }
  else
  {
    todo_list_.emplace_back(Task{task_desc, {}, false});
  }
}

void Todo::Model::remove(size_t index)
{
  if (index == 0 || index > todo_list_.size())
  {
    throw std::out_of_range("Task ID out of range");
  }
  todo_list_.erase(todo_list_.begin() + index - 1);
}

void Todo::Model::change_task_status(size_t index)
{
  if (index == 0 || index > todo_list_.size())
  {
    throw std::out_of_range("Task ID out of range");
  }
  todo_list_[index - 1].completion = not todo_list_[index - 1].completion;
}

const std::vector<Todo::Task> &Todo::Model::get_list()
{
  return todo_list_;
}
