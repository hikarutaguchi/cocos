#ifdef _DEBUG

#include <Windows.h>
#include "_DebugConOut.h"

//static _DebugConOut * /*_DebugConOut::*/s_Instance = nullptr;
std::unique_ptr<_DebugConOut, _DebugConOut::_DebugConOutDeleter>_DebugConOut::s_Instance(new _DebugConOut());	//���̂���������ڽ�������Ƃ��ēn���Ă�����

_DebugConOut::_DebugConOut()
{
	// ��ʕ\������
	// �O�ɂ���E�B���h�E�̃n���h�����擾
	// HWND hWnd = GetForegroundWindow();
	// �R���\�[���̕\������
	AllocConsole();

	// ����
	freopen_s(&_debugFp, "CONIN$", "r", stdin);

	// �R���\�[���ɕ����𑗂��悤�ɂ���(�o��)
	freopen_s(&_debugFp,"CONOUT$","w",stdout);

	// �R���\�[�����J������Ɏ擾�����n���h�����J��
	//SetForegroundWindow(hWnd);
}


_DebugConOut::~_DebugConOut()
{
	// �R���\�[�������
	FreeConsole();
}

#endif // _DEBUG