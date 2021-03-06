/*
** ThreadPool.cpp for cpp_plazza in /home/enguerrand/delivery/cpp_plazza/ThreadPool.cpp
**
** Made by Enguerrand Allamel
** Login   <enguerrand.allamel@epitech.eu>
**
** Started on  Wed Apr 19 10:36:03 2017 Enguerrand Allamel
** Last update Wed Apr 19 10:36:03 2017 Enguerrand Allamel
*/

#include "ThreadPool.hpp"

plazza::ThreadPool::ThreadPool(size_t nbWorker)
{
  this->_mutex = new Mutex();
  for (size_t i = 0 ; i < nbWorker ; i++)
    {
      this->_worker.push_back(new ThreadPoolWorker(&this->_orders, this->_mutex, this->_condVar));
    }
}

plazza::ThreadPool::~ThreadPool()
{
  for (auto it = this->_worker.begin() ; it != this->_worker.end() ; ++it)
    delete (*it);
  delete this->_mutex;
}

void plazza::ThreadPool::addOrder(Order order)
{
  this->_mutex->lock();
  this->_orders.push_back(order);
  this->_mutex->unlock();
}

bool plazza::ThreadPool::isEmpty() const
{
  bool res = true;
  for (auto it = this->_worker.begin() ; it != this->_worker.end() ; ++it)
    {
      if ((*it)->getStatus() == plazza::ThreadPoolWorker::STATUS::RUN ||
	  (*it)->getStatus() == plazza::ThreadPoolWorker::STATUS::NOT_START)
	res = false;
    }
  return (res);
}

bool plazza::ThreadPool::isFull() const
{
  this->_mutex->lock();
  size_t nb = this->_orders.size();
  this->_mutex->unlock();
  if (nb < this->_worker.size() * 2)
    return false;
  return true;
}