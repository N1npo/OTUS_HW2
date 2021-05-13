#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <chrono>

using string_buffer_t = std::vector<std::string>;
class ITask 
{
public:
	virtual std::string run(const string_buffer_t &buff) = 0;
	virtual const char* name() const = 0;
};

class Tester
{
public:
	static void run_tests(ITask& task, const char* path)
	{
		std::cout << "==== Start test " << task.name() << " ====" << std::endl;
		try
		{
			size_t n = 0;
			std::ifstream input_file, output_file;
			__open_test(input_file, output_file, path, n);
			while (input_file.is_open() && output_file.is_open())
			{
				std::cout << "Test " << n;
				auto start_time = std::chrono::high_resolution_clock::now();
				bool result = __run_test(input_file, output_file, task);
				auto end_time = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
				std::cout << " (duratuin: " << duration << " msec)" << std::endl;
				input_file.close();
				output_file.close();
				n++;
				__open_test(input_file, output_file, path, n);
			}
			input_file.close();
			output_file.close();
		}
		catch (const std::exception& e)
		{
			std::cout << "Got exception: " << e.what() << std::endl;
		}
		std::cout << "==== Test done ====" << std::endl;
	}
private:
	static bool __run_test(std::ifstream &input, std::ifstream &output, ITask &task)
	{
		std::string line;
		string_buffer_t buff;
		
		while (std::getline(input, line))
		{
			buff.emplace_back(__trim(line));
		}
		std::string expect((std::istreambuf_iterator<char>(output)), std::istreambuf_iterator<char>());
		expect = __trim(expect);
		std::string got = task.run(buff);
		bool result = expect == got;
		std::cout << ": " << (result ? "Passed" : "Failed");
		if (!result)
		{
			std::cout << " got: " << got << ", expected: " << expect;
		}
		return result;
	}

	static void __open_test(std::ifstream &input, std::ifstream &output, const char *path, size_t n)
	{
		std::string in = std::string(path) + "/test." + std::to_string(n) + ".in";
		std::string out = std::string(path) + "/test." + std::to_string(n) + ".out";
		input.open(in);
		output.open(out);
	}

	static std::string __ltrim(const std::string& s, const char* ws = " \r\n")
	{
		size_t start = s.find_first_not_of(ws);
		return (start == std::string::npos) ? "" : s.substr(start);
	}

	static std::string __rtrim(const std::string& s, const char* ws = " \r\n")
	{
		size_t end = s.find_last_not_of(ws);
		return (end == std::string::npos) ? "" : s.substr(0, end + 1);
	}

	static std::string __trim(const std::string& s) {
		return __rtrim(__ltrim(s));
	}
};

