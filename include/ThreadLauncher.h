#ifndef THREAD_LAUNCHER_H_
#define THREAD_LAUNCHER_H_

#include <string>
#include <initializer_list>

// �����߳������еĺ�������
typedef void* (*thread_func)(void*);

namespace ThreadLauncher {
	/*
 * �����߳�
 * params:
 * title������
 * funcs���̺߳�����ʼ���б�
 * date:2024/9/28
 */
	void StartThread(const std::string& title, std::initializer_list<thread_func> funcs);

	void StartThread(const std::string& title, std::initializer_list<Thread*> threads);

	class Thread {

	public:
		Thread(const char* thread_name, thread_func func) :name(thread_name), run(func) { }

		Thread(const Thread&) = delete;
		Thread& operator=(const Thread&) = delete;

	private:
		// �߳���
		const char* name;
		// �߳����к���
		thread_func run;

	};

}

#endif // !THREAD_LAUNCHER_H_

