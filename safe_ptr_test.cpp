#include "safe_ptr.hpp"
#include <cassert>
#include <cstdio>

int main() {
	safe_ptr xFFFFPtr((PVOID)0xFFFF);
	assert(!xFFFFPtr._<uint8_t>(0).has_value());

	safe_ptr mainPtr(&main);
	assert(mainPtr._<uint8_t>(0).has_value());

	safe_ptr modulePtr(GetModuleHandleW(NULL));
	assert(modulePtr._<uint16_t>(0) == IMAGE_DOS_SIGNATURE);

	auto imageDosHeaderOpt = modulePtr._<IMAGE_DOS_HEADER>(0);
	assert(imageDosHeaderOpt.has_value());
	
	auto imageNtHeaderOpt = modulePtr._<IMAGE_NT_HEADERS>(imageDosHeaderOpt->e_lfanew);
	assert(imageNtHeaderOpt.has_value());
	assert(imageNtHeaderOpt->Signature == IMAGE_NT_SIGNATURE);

	puts("PASS");
}
