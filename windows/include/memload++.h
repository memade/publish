﻿#if !defined(INC_H___B00DFB21_3AEA_4AA8_A0CC_10E106D8FE6D__HEAD__)
#define INC_H___B00DFB21_3AEA_4AA8_A0CC_10E106D8FE6D__HEAD__

namespace shared {

	using HMEMORYMODULE = void*;
	using HMEMORYRSRC = void*;
	using HCUSTOMMODULE = void*;
	using CustomAllocFunc = LPVOID(*)(LPVOID, SIZE_T, DWORD, DWORD, void*);
	using CustomFreeFunc = BOOL(*)(LPVOID, SIZE_T, DWORD, void*);
	using CustomLoadLibraryFunc = HCUSTOMMODULE(LPCSTR, void*);
	using CustomGetProcAddressFunc = FARPROC(*)(HCUSTOMMODULE, LPCSTR, void*);
	using CustomFreeLibraryFunc = void (*)(HCUSTOMMODULE, void*);

	class Memload final {
	public:
		Memload(const std::string&);
		~Memload();
	public:
		/**
			* Load EXE/DLL from memory location with the given size.
			*
			* All dependencies are resolved using default LoadLibrary/GetProcAddress
			* calls through the Windows API.
			*/
		HMEMORYMODULE MemoryLoadLibrary(const void*, size_t);
		/**
			* Load EXE/DLL from memory location with the given size using custom dependency
			* resolvers.
			*
			* Dependencies will be resolved using passed callback methods.
			*/
		HMEMORYMODULE MemoryLoadLibraryEx(const void*, size_t,
			CustomAllocFunc,
			CustomFreeFunc,
			CustomLoadLibraryFunc,
			CustomGetProcAddressFunc,
			CustomFreeLibraryFunc,
			void*);
		/**
			* Get address of exported method. Supports loading both by name and by
			* ordinal value.
			*/
		FARPROC MemoryGetProcAddress(HMEMORYMODULE, LPCSTR);
		/**
			* Free previously loaded EXE/DLL.
			*/
		void MemoryFreeLibrary(HMEMORYMODULE);
		/**
			* Execute entry point (EXE only). The entry point can only be executed
			* if the EXE has been loaded to the correct base address or it could
			* be relocated (i.e. relocation information have not been stripped by
			* the linker).
			*
			* Important: calling this function will not return, i.e. once the loaded
			* EXE finished running, the process will terminate.
			*
			* Returns a negative value if the entry point could not be executed.
			*/
		int MemoryCallEntryPoint(HMEMORYMODULE);
		/**
			* Find the location of a resource with the specified type and name.
			*/
		HMEMORYRSRC MemoryFindResource(HMEMORYMODULE, LPCTSTR, LPCTSTR);
		/**
			* Find the location of a resource with the specified type, name and language.
			*/
		HMEMORYRSRC MemoryFindResourceEx(HMEMORYMODULE, LPCTSTR, LPCTSTR, WORD);
		/**
			* Get the size of the resource in bytes.
			*/
		DWORD MemorySizeofResource(HMEMORYMODULE, HMEMORYRSRC);
		/**
			* Get a pointer to the contents of the resource.
			*/
		LPVOID MemoryLoadResource(HMEMORYMODULE, HMEMORYRSRC);
		/**
			* Load a string resource.
			*/
		int MemoryLoadString(HMEMORYMODULE, UINT, LPTSTR, int);
		/**
			* Load a string resource with a given language.
			*/
		int MemoryLoadStringEx(HMEMORYMODULE, UINT, LPTSTR, int, WORD);
		/**
		* Default implementation of CustomAllocFunc that calls VirtualAlloc
		* internally to allocate memory for a library
		*
		* This is the default as used by MemoryLoadLibrary.
		*/
		static LPVOID MemoryDefaultAlloc(LPVOID, SIZE_T, DWORD, DWORD, void*);
		/**
		* Default implementation of CustomFreeFunc that calls VirtualFree
		* internally to free the memory used by a library
		*
		* This is the default as used by MemoryLoadLibrary.
		*/
		static BOOL MemoryDefaultFree(LPVOID, SIZE_T, DWORD, void*);
		/**
			* Default implementation of CustomLoadLibraryFunc that calls LoadLibraryA
			* internally to load an additional libary.
			*
			* This is the default as used by MemoryLoadLibrary.
			*/
		static HCUSTOMMODULE MemoryDefaultLoadLibrary(const char*, void*);
		/**
			* Default implementation of CustomGetProcAddressFunc that calls GetProcAddress
			* internally to get the address of an exported function.
			*
			* This is the default as used by MemoryLoadLibrary.
			*/
		static FARPROC MemoryDefaultGetProcAddress(HCUSTOMMODULE, const char*, void*);
		/**
			* Default implementation of CustomFreeLibraryFunc that calls FreeLibrary
			* internally to release an additional libary.
			*
			* This is the default as used by MemoryLoadLibrary.
			*/
		static void MemoryDefaultFreeLibrary(HCUSTOMMODULE, void*);
	};


}///namespace shared

#pragma comment(lib,"memload++")
/// /*新生®（上海）**/
/// /*2022_02_21T07:44:53.7673172Z**/
/// /*_ _ _ _ _ _ _ www.skstu.com _ _ _ _ _ _ _**/
#endif ///INC_H___B00DFB21_3AEA_4AA8_A0CC_10E106D8FE6D__HEAD__