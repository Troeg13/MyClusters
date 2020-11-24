#pragma once
#include "Turn.h"
#include <vector>
#include <utility>

struct Task
{
	int tact;// число тактов для выполнения
	int processor;//кол-во процессоров для выполнения
};

class TaskStream
{
private:
	Turn<int> tacts_new_task;
	int count_task;// количество задач
public:
	TaskStream(int count_task);
	Task GetNewTask();
	int ViewTheTact(); //метод возвращающий значение такта на котором, должна сгенирироваться следующая задача
	int GetTact();
	int GetCountTask();
};

class Cluster
{
private:
	int processor;
	std::vector<std::pair<int, int>> time_task_completion;//first - такт к которому задача будет выполнена, secont - кол-во освободившихся процессоров
	int count_task;
	int count_tact;
	int free_tact;//такт простоя
public:
	Cluster();
	Cluster(int proc);
	void ClusterOn(TaskStream & task_stream);
	void Statistics();
};