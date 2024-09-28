#ifndef THREAD_LAUNCHER_H_
#define THREAD_LAUNCHER_H_

#include <string>
#include <initializer_list>

// �����߳������еĺ�������
typedef void* (*thread_func)(void*);

/*
 * �����߳�
 * params:
 * title������
 * funcs���̺߳�����ʼ���б�
 */
void StartThread(const std::string& title, std::initializer_list<thread_func> funcs);

#endif // !THREAD_LAUNCHER_H_

