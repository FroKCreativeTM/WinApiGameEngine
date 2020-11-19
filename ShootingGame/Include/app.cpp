#include "CCore.h"

INT APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	// ½Ì±ÛÅæ °´Ã¼ ÃÊ±âÈ­
	if (!CCore::GetInst()->Init(hInstance))
	{
		CCore::DestroyInst();
		return 0;
	}

	// return value
	int nRev = CCore::GetInst()->Run();
	CCore::DestroyInst();

	return nRev;
}