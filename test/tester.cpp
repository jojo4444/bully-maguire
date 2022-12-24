#include "tester.hpp"

Tester::Tester() : pdata(nullptr) {}

Tester::~Tester() {
	delete pdata;
}