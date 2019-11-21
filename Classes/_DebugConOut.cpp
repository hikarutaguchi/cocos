#ifdef _DEBUG

#include <Windows.h>
#include "_DebugConOut.h"

//static _DebugConOut * /*_DebugConOut::*/s_Instance = nullptr;
std::unique_ptr<_DebugConOut, _DebugConOut::_DebugConOutDeleter>_DebugConOut::s_Instance(new _DebugConOut());	//実体を作ったｱﾄﾞﾚｽを引数として渡してあげる

_DebugConOut::_DebugConOut()
{
	// 画面表示順番
	// 前にあるウィンドウのハンドルを取得
	// HWND hWnd = GetForegroundWindow();
	// コンソールの表示命令
	AllocConsole();

	// 入力
	freopen_s(&_debugFp, "CONIN$", "r", stdin);

	// コンソールに文字を送れるようにする(出力)
	freopen_s(&_debugFp,"CONOUT$","w",stdout);

	// コンソールを開いた後に取得したハンドルを開く
	//SetForegroundWindow(hWnd);
}


_DebugConOut::~_DebugConOut()
{
	// コンソールを閉じる
	FreeConsole();
}

#endif // _DEBUG