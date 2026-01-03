#pragma once

#include <boost/describe.hpp>
#include <string>
#include <vector>

namespace Todo {
struct Task {
  std::string desc;               ///< Description of the task.
  std::vector<Task> child_tasks;  ///< Child tasks.
  uint16_t priority;              ///< Priority of the task.

  enum class Status : char {
    NOT_STARTED = 1,
    IN_PROGRESS = 2,
    COMPLETED = 3
  } status;  ///< Completion status of the task.

  bool operator==(const Task &other) const
  {
    if (desc != other.desc) {
      return false;
    }

    if (priority != other.priority) {
      return false;
    }

    if (status != other.status) {
      return false;
    }

    if (child_tasks != other.child_tasks) {
      return false;
    }

    return true;
  }

  bool operator!=(const Task &other) const
  {
    return not(*this == other);
  }
};

BOOST_DESCRIBE_ENUM(Task::Status, NOT_STARTED, IN_PROGRESS, COMPLETED);
BOOST_DESCRIBE_STRUCT(Task, (), (desc, child_tasks, priority, status));
}  // namespace Todo
