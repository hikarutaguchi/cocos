#pragma once

#ifdef _DEBUG

#include <Windows.h>
#include <memory>

#define TRACE(fmt, ...) printf(fmt, __VA_ARGS__)	// √ﬁ ﬁØ∏ﬁï∂éöóÒèoóÕ

class _DebugConOut
{
public:

	static _DebugConOut &GetInstace()
	{
		return (*s_Instance);
	}

private:

	struct _DebugConOutDeleter
	{
		void operator()(_DebugConOut* _debugconout) const
		{
			delete _debugconout;
		}
	};

	_DebugConOut();
	~_DebugConOut();
	static std::unique_ptr<_DebugConOut, _DebugConOutDeleter> s_Instance;

	FILE* _debugFp = nullptr;	// Ãß≤ŸŒﬂ≤›¿
};
#else
#define TRACE(fmt, ...)
#endif // _DEBUG
