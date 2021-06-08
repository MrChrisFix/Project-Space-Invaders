#pragma once

template<typename First, typename Second>
struct Para
{
private:
	First fir;
	Second sec;
	Para<First, Second>* pNext;

public:
	void add(First f, Second s) { this->fir = f; this->sec = s; this->pNext = nullptr; }
	void addFirst(First f) { this->fir = f; }
	void addSecond(Second s) { this->sec = s; }
	void setNext(Para* p) { this->pNext = p; }

	Para* getNext() { return this->pNext; }
	First getFirst() { return this->fir; }
	Second getSecond() { return this->sec; }
};
