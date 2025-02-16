#pragma once

#include <cstdint>
#include <optional>
#include <windows.h>

class safe_ptr {
protected:
	HANDLE m_h_proc;
	bool m_protect;
	PVOID m_addr;

public:
	template <typename T>
	__forceinline safe_ptr(T* addr, bool protect = false, HANDLE hProc = GetCurrentProcess()) : m_h_proc(hProc), m_protect(protect), m_addr((PVOID)addr) {
	}

	template <typename T>
	__forceinline std::optional<T> _(intptr_t i) const {
		DWORD oldProtect = 0;
		if (!m_protect || VirtualProtectEx(m_h_proc, (PVOID)((uintptr_t)m_addr + i), sizeof(T), PAGE_EXECUTE_READWRITE, &oldProtect)) {
			T result;
			SIZE_T readed = 0;
			bool success = ReadProcessMemory(m_h_proc, (PVOID)((uintptr_t)m_addr + i), &result, sizeof(T), &readed) && readed == sizeof(T);
			if (m_protect) {
				VirtualProtectEx(m_h_proc, (PVOID)((uintptr_t)m_addr + i), sizeof(T), oldProtect, &oldProtect);
			}
			if (success) {
				return result;
			}
		}
		return std::nullopt;
	}
};
