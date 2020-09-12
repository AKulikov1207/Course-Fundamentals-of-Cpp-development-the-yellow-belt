#include <iostream>
#include <map>
#include <tuple>
#include <string>
#include <vector>

using namespace std;

class TeamTasks {
public:
	// Получить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const std::string& person) const {
		return PersonTasks.at(person);
	}

	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const std::string& person) {
		auto& tasks_info = PersonTasks[person];
		++tasks_info[TaskStatus::NEW];
	}

	// Обновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(
		const std::string& person, int task_count) {
		TasksInfo upgrade;
		TasksInfo updated;
		TasksInfo untouched;
		auto& tasks_info = PersonTasks[person];
		for (auto& item : tasks_info) {
			if (item.first == TaskStatus::NEW) {
				if (item.second > 0) {
					int new_status_count = item.second;
					while (new_status_count > 0 && task_count > 0) {
						++updated[TaskStatus::IN_PROGRESS];
						++upgrade[TaskStatus::IN_PROGRESS];
						--new_status_count;
						--task_count;
					}
					if (new_status_count > 0) {
						untouched[TaskStatus::NEW] += new_status_count;
						upgrade[TaskStatus::NEW] += new_status_count;
					}
				}
			}
			if (item.first == TaskStatus::IN_PROGRESS) {
				if (item.second > 0) {
					int in_progress_status_count = item.second;
					while (in_progress_status_count > 0 && task_count > 0) {
						++updated[TaskStatus::TESTING];
						++upgrade[TaskStatus::TESTING];
						--in_progress_status_count;
						--task_count;
					}
					if (in_progress_status_count > 0) {
						untouched[TaskStatus::IN_PROGRESS] += in_progress_status_count;
						upgrade[TaskStatus::IN_PROGRESS] += in_progress_status_count;
					}
				}
			}
			if (item.first == TaskStatus::TESTING) {
				if (item.second > 0) {
					int testing_status_count = item.second;
					while (testing_status_count > 0 && task_count > 0) {
						++updated[TaskStatus::DONE];
						++upgrade[TaskStatus::DONE];
						--testing_status_count;
						--task_count;
					}
					if (testing_status_count > 0) {
						untouched[TaskStatus::TESTING] += testing_status_count;
						upgrade[TaskStatus::TESTING] += testing_status_count;
					}
				}
			}
			if (item.first == TaskStatus::DONE) {
				if (item.second > 0) {
					upgrade[TaskStatus::DONE] += item.second;
				}
			}
		}
		PersonTasks[person] = upgrade;
		return std::make_tuple(updated, untouched);
	};

private:
	std::map<std::string, TasksInfo> PersonTasks;
};