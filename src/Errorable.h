#pragma once

#include <stack>

#include <qobject.h>
#include <qdialog.h>

// Adds error class to derived class. Contains stack of errors of type Enum.
class Errorable : private QDialog
{
	Q_OBJECT

signals:

	// Emit when error happened.
	void errorHappened(int);

public:

	// Pop last error.
	void popError();

	// Return last error and pop it.
	int getLastError();

	// Returns if class has error.
	bool hasError()const;

	// Clears error stack.
	void clearErrors();

	// Returns last error.
	int topError() const;

protected:

	// Adds error.
	void pushError(int val);

private:

	// Error stack.
	std::stack<int> m_errorStack;
};


