#pragma once
#include "Queue.h"
#include <vector>
#include <utility>

struct Task
{
	int tact;
	int processor;
};

class TaskStream
{
private:
	Queue<int> tacts_new_task;//очерёдность тактов на которых будут генерироваться новые задачи
	int count_task;
public:
	TaskStream(int count_task);
	Task GetNewTask();//генирация новой задачи
	int ViewTheTact(); 
	int GetTact();
	int GetCountTask();
};

class Cluster
{
private:
	int processor;
	std::vector<std::pair<int, int>> time_task_completion;//first- такт на котором завершится выполнение задачи, second - кол-во процессоров, которые освободятся
	int count_task;
	int count_tact;
	int free_tact;//такты простоя
public:
	Cluster();
	Cluster(int proc);
	void ClusterOn(TaskStream & task_stream);
	void Statistics();
};