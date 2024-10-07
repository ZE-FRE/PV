#ifndef THREAD_LAUNCHER_H_
#define THREAD_LAUNCHER_H_

#include <string>
#include <initializer_list>

// 定义线程所运行的函数类型
typedef void* (*thread_func)(void*);

namespace ThreadLauncher {
	/*
 * 启动线程
 * params:
 * title：标题
 * funcs：线程函数初始化列表
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
		// 线程名
		const char* name;
		// 线程运行函数
		thread_func run;

	};

}

#endif // !THREAD_LAUNCHER_H_

