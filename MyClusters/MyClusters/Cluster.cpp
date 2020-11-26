#include "Cluster.h"
#include <iostream>
#include <ctime>

Cluster::Cluster() : processor(1), count_tact(0), count_task(0), free_tact(0)
{
	time_task_completion.resize(0);
}

Cluster::Cluster(int proc) : processor(proc), count_tact(0), count_task(0), free_tact(0)
{
	if ((proc > 64) || (proc < 1))
		throw - 1;
	time_task_completion.resize(0);
}

void Cluster::ClusterOn(TaskStream & task_stream)
{
	Queue<Task> queue(task_stream.GetCountTask());
	int tmp = 0;

	Task current_task;
	while (true)
	{
		count_tact++;
		//возвращаем освободившиеся процессоры
		if (time_task_completion.size() != 0)
		{
			for (int i = 0; i < time_task_completion.size(); i++)
			{
				if (time_task_completion[i].first == count_tact)
				{
					count_task++;
					processor += time_task_completion[i].second;
					time_task_completion.erase(time_task_completion.begin() + i);
					i--;
				}
			}
		}
		//проверяем очередь
		if (!queue.IsEmpty())
		{
			if (processor >= queue.ViewTheFirst().processor)
			{
				current_task = queue.Get();
				processor -= current_task.processor;
				time_task_completion.push_back(std::make_pair(count_tact + current_task.tact, current_task.processor));
			}
		}
		// поступила ли новая задача, требующая обработки?
		if (count_tact == task_stream.ViewTheTact())
		{
			tmp = task_stream.GetTact();
			current_task = task_stream.GetNewTask();
			if (processor >= current_task.processor)
			{
				processor -= current_task.processor;
				time_task_completion.push_back(std::make_pair(count_tact + current_task.tact, current_task.processor));
			}
			else
			{
				if (time_task_completion.size() == 0)
					throw "the current task cannot be completed";
				queue.Put(current_task);
			}	
		}
		//счётчик тактов простоя
		if (time_task_completion.size() == 0)
			free_tact++;

		if (count_task == task_stream.GetCountTask())
			break;
	}
}

void Cluster::Statistics()
{
	std::cout << " Количество процессоров в кластере: " << processor << std::endl;
	std::cout << " Количество тактов, потраченное на выполнение задач: " << count_tact << std::endl;
	std::cout << " Количество выполненых задач: " << count_task << std::endl;
	std::cout << " Среднее количество тактов выполнения задания: " << (float(count_tact - free_tact)) / float(count_task) << std::endl;
	std::cout << " Кличество тактов простоя кластера: " << free_tact << std::endl;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------

TaskStream::TaskStream(int count_task): count_task(count_task), tacts_new_task(count_task)
{
	srand(time(NULL));
	int t = 0;
	for (int i = 0; i < count_task; i++)
	{
		t += 1 + rand() % 5;
		tacts_new_task.Put(t);
	}
}

Task TaskStream::GetNewTask()
{
	srand(time(NULL)); 
	Task new_task;
	new_task.tact = 1 + rand() % 20;
	new_task.processor = 1 + rand() % 10;
	return new_task;
}

int TaskStream::ViewTheTact()
{
	if (tacts_new_task.Cardinality() == 0)
		return - 1;
	return tacts_new_task.ViewTheFirst();
}

int TaskStream::GetCountTask()
{
	return count_task;
}

int TaskStream::GetTact()
{
	return tacts_new_task.Get();
}




