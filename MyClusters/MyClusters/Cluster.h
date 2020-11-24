#pragma once
#include "Turn.h"
#include <vector>
#include <utility>

struct Task
{
	int tact;// ����� ������ ��� ����������
	int processor;//���-�� ����������� ��� ����������
};

class TaskStream
{
private:
	Turn<int> tacts_new_task;
	int count_task;// ���������� �����
public:
	TaskStream(int count_task);
	Task GetNewTask();
	int ViewTheTact(); //����� ������������ �������� ����� �� �������, ������ ��������������� ��������� ������
	int GetTact();
	int GetCountTask();
};

class Cluster
{
private:
	int processor;
	std::vector<std::pair<int, int>> time_task_completion;//first - ���� � �������� ������ ����� ���������, secont - ���-�� �������������� �����������
	int count_task;
	int count_tact;
	int free_tact;//���� �������
public:
	Cluster();
	Cluster(int proc);
	void ClusterOn(TaskStream & task_stream);
	void Statistics();
};