#include "Errorable.h"

void Errorable::popError()
{
	m_errorStack.pop();
}

int Errorable::getLastError()
{
	return m_errorStack.top();
}

bool Errorable::hasError() const
{
	return m_errorStack.size();
}

void Errorable::clearErrors()
{
	m_errorStack = std::stack<int>();
}

void Errorable::pushError(int val)
{
	emit errorHappened(val);
	m_errorStack.push(val);
}

