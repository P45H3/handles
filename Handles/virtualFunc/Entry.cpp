#include <Windows.h>
#include <iostream>
#include <memory>

using namespace std;

class CHandle {
private:
	HANDLE m_Handle;
public:
	
	CHandle(HANDLE _H) : m_Handle(_H) {}
	CHandle(HMODULE _H) : m_Handle((HANDLE)_H) {}
	CHandle() { m_Handle = INVALID_HANDLE_VALUE; }

	void operator=(HANDLE _Inp) {
		if (_Inp != INVALID_HANDLE_VALUE)
			m_Handle = _Inp;
	}


	void Release() {
		if (m_Handle != INVALID_HANDLE_VALUE) {
			CloseHandle(m_Handle);
			m_Handle = INVALID_HANDLE_VALUE;
		}
	}

	HANDLE& Get() { return m_Handle; }

	~CHandle() { Release(); }
};

int main() { 
	SetConsoleTitle(" ");
	
	DWORD hSim = 123456;
	
	unique_ptr<CHandle> g_hFst(new CHandle((HANDLE)hSim));
	unique_ptr<CHandle> g_hSec(new CHandle()); 
	
	*g_hSec = (HANDLE)hSim;

	printf_s("FST - %d | SC - %d\n", g_hFst->Get(), g_hSec->Get());

	g_hFst->Release();
	g_hSec->Release();

	printf_s("FST - %d | SC - %d\n", g_hFst->Get(), g_hSec->Get());

	return 0;
}