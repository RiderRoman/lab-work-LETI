#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#include <cctype>
#include <cmath>

#include "DynamicArr.h"
#include "DoublyLinkedList.h"
#include "Stack.h"

using namespace std;

bool is_digit(const string& value) {
	char numbers[10] = { '0','1','2','3','4','5','6','7','8','9' };
	int j = 0;
	for (int i = 0; i < value.length(); i++) {
		for (j = 0; j < 10; j++) {
			if (value[i] == numbers[j]) break;
		}
		if (j == 10) return false;
	}
	return true;
}

bool is_operation(const string& value) {
	if (value.length() != 1) return false;
	return string("+-*/^()").find(value[0]) != string::npos;
}

bool is_pure_operation(const string& value) {
	if (value.length() != 1) return false;
	return string("+-*/^").find(value[0]) != string::npos;
}

int get_priority(string op) {
	if (op == "+" || op == "-") return 1;
	if (op == "*" || op == "/") return 2;
	if (op == "^") return 3;
	if (op == "(" || op == ")") return 0;
	return 0;
}

double solve_rpn(DynamicArr<string> &rpn) {
	Stack<double> numbers;

	for (int i = 0; i < rpn.get_size(); i++) {
		if (is_digit(rpn[i])) {
			numbers.push_back(stod(rpn[i]));
			continue;
		}
		if (string("+-*/^").find(rpn[i]) != string::npos) {
			double b = numbers.top(); numbers.pop_back();
			double a = numbers.top(); numbers.pop_back();
			if (rpn[i] == "+") numbers.push_back(a + b);
			if (rpn[i] == "-") numbers.push_back(a - b);
			if (rpn[i] == "*") numbers.push_back(a * b);
			if (rpn[i] == "/") numbers.push_back(a / b);
			if (rpn[i] == "^") numbers.push_back(pow(a, b));
			continue;
		}
		else {
			double x = numbers.top(); numbers.pop_back();
			if (rpn[i] == "cos") numbers.push_back(cos(x * (3.14159265 / 180)));
			if (rpn[i] == "sin") numbers.push_back(sin(x * (3.14159265 / 180)));
		}
	}
	return numbers.front();
}

void shunting_yard_(DynamicArr<string> &input) {
	Stack<string> stack;
	DynamicArr<string> rpn;

	size_t size = input.get_size();

	for (int i = 0; i < size; i++) {
		if (is_digit(input[i])) {
			rpn.push_back(input[i]);
			continue;
		}

		if (input[i] == "(") {
			stack.push_back(input[i]);
			continue;
		}

		if (input[i] == ")") {
			while (stack.get_size() != 0 && stack.top() != "(") {
				rpn.push_back(stack.top()); 
				stack.pop_back();
			}

			if (stack.get_size() != 0) stack.pop_back();

			if (stack.get_size() != 0 && !is_digit(stack.top()) && !is_operation(stack.top())) { // if cos or sin after delete "("
				rpn.push_back(stack.top()); 
				stack.pop_back();
			}

			continue;
		}

		if (is_operation(input[i])) {
			while (stack.get_size() != 0 && ((get_priority(stack.top()) > get_priority(input[i])) || (get_priority(stack.top()) >= get_priority(input[i]) && input[i] != "^"))) {
				rpn.push_back(stack.top());
				stack.pop_back();
			}

			stack.push_back(input[i]);
			continue;
		}
		else {
			stack.push_back(input[i]);
			continue;
		}
	}

	while (stack.get_size() != 0) {
		rpn.push_back(stack.top()); 
		stack.pop_back();
	}
	rpn.print_array();
	cout << "результат: " << solve_rpn(rpn);
	return;
}



bool check_problem(DynamicArr<string> &problem) {
	if (problem.get_size() == 0) return false;
	size_t last_token = problem.get_size() - 1;

	if (is_pure_operation(problem[0])) {
		cerr << "Выраженние введено некорректно.\n";
		return false;
	}
	
	if (is_pure_operation(problem[last_token]) || problem[last_token] == "sin" || problem[last_token] == "cos" || problem[last_token] == "(") {
		cerr << "Выраженние введено некорректно.\n";
		return false;
	}

	if (problem.get_size() <= 1) return false;

	for (size_t i = 0; i < problem.get_size() - 1; i++) {
		if (is_digit(problem[i]) && is_digit(problem[i + 1])) {
			cerr << "Выраженние введено некорректно.\n";
			return false;
		}

		if (is_pure_operation(problem[i]) && is_pure_operation(problem[i + 1])) {
			cerr << "Выраженние введено некорректно.\n";
			return false;
		}

		if (is_pure_operation(problem[i]) && problem[i + 1] == ")") {
			cerr << "Выраженние введено некорректно.\n";
			return false;
		}

		if (problem[i] == "sin" || problem[i] == "cos") {
			if (problem[i + 1] != "(") {
				cerr << "Выраженние введено некорректно.\n";
				return false;
			}
		}
	}
	
	return true;
}

int main() {
	setlocale(LC_ALL, "RU");
	string input;
	cout << "Введите выражение: ";
	getline(cin >> ws, input);

	DynamicArr<string> tokens;
	Stack<string> rpn;
	size_t i = 0;

	while (i < input.length()) {
		if (isspace(input[i])) {
			i++;
			continue;
		}

		if (string("+-*/^()").find(input[i]) != string::npos) {
			tokens.push_back(string(1, input[i]));
			i++;
			continue;
		}

		if (input[i] >= '0' && input[i] <= '9') {
			string number = "";
			while (i < input.length() && input[i] >= '0' && input[i] <= '9') {
				number += input[i];
				i++;
			}
			tokens.push_back(number);
			continue;
		}

		if (isalpha(input[i])) {
			string function = "";
			while (i < input.length() && isalpha(input[i])) {
				function += input[i];
				i++;
			}
			tokens.push_back(function);
			continue;
		}

		i++;
	}
	if (!check_problem(tokens)) return 0;

	//tokens.print_array();

	shunting_yard_(tokens);


	return 0;
}