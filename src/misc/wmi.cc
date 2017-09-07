#define _WIN32_DCOM
#include <iostream>
using namespace std;
#include <comdef.h>
#include <Wbemidl.h>
#include "wmi.h"

#pragma comment(lib, "wbemuuid.lib")



std::map<string,string> OS_WMI_Information()
{
	std::map<string, string> osnamevalues;
    HRESULT hres;


    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres))
    {
	    cout << "Failed to initialize COM library. Error code = 0x"	<< hex << hres << endl;
		goto CLEANUP;
    }


   hres = CoInitializeSecurity(
	NULL,
	-1,                          // COM authentication
	NULL,                        // Authentication services
	NULL,                        // Reserved
	RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
	RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
	NULL,                        // Authentication info
	EOAC_NONE,                   // Additional capabilities 
	NULL                         // Reserved
   );


   if (FAILED(hres))
   {
	   cout << "Failed to initialize security. Error code = 0x"
		<< hex << hres << endl;
	   goto CLEANUP;                    // Program has failed.
   }

// Step 3: ---------------------------------------------------
// Obtain the initial locator to WMI -------------------------

IWbemLocator *pLoc = NULL;

hres = CoCreateInstance(
	CLSID_WbemLocator,
	0,
	CLSCTX_INPROC_SERVER,
	IID_IWbemLocator, (LPVOID *)&pLoc);

if (FAILED(hres))
{
	cout << "Failed to create IWbemLocator object."
		<< " Err code = 0x"
		<< hex << hres << endl;
	goto CLEANUP;
}


// Connect to WMI through the IWbemLocator::ConnectServer method

IWbemServices *pSvc = NULL;

// Connect to the root\cimv2 namespace with
// the current user and obtain pointer pSvc
// to make IWbemServices calls.
hres = pLoc->ConnectServer(
	_bstr_t(L"ROOT\\CIMV2"), // Object path of WMI namespace
	NULL,                    // User name. NULL = current user
	NULL,                    // User password. NULL = current
	0,                       // Locale. NULL indicates current
	NULL,                    // Security flags.
	0,                       // Authority (for example, Kerberos)
	0,                       // Context object 
	&pSvc                    // pointer to IWbemServices proxy
);

if (FAILED(hres))
{
	cout << "Could not connect. Error code = 0x"
		<< hex << hres << endl;
	pLoc->Release();
	goto CLEANUP;
}

cout << "Connected to ROOT\\CIMV2 WMI namespace" << endl;


// Step 5: --------------------------------------------------
// Set security levels on the proxy -------------------------

hres = CoSetProxyBlanket(
	pSvc,                        // Indicates the proxy to set
	RPC_C_AUTHN_WINNT,           // RPC_C_AUTHN_xxx
	RPC_C_AUTHZ_NONE,            // RPC_C_AUTHZ_xxx
	NULL,                        // Server principal name 
	RPC_C_AUTHN_LEVEL_CALL,      // RPC_C_AUTHN_LEVEL_xxx 
	RPC_C_IMP_LEVEL_IMPERSONATE, // RPC_C_IMP_LEVEL_xxx
	NULL,                        // client identity
	EOAC_NONE                    // proxy capabilities 
);

if (FAILED(hres))
{
	cout << "Could not set proxy blanket. Error code = 0x"
		<< hex << hres << endl;
	pSvc->Release();
	pLoc->Release();
	goto CLEANUP;
}

// Step 6: --------------------------------------------------
// Use the IWbemServices pointer to make requests of WMI ----

// For example, get the name of the operating system
IEnumWbemClassObject* pEnumerator = NULL;
hres = pSvc->ExecQuery(
	bstr_t("WQL"),
	bstr_t("SELECT * FROM Win32_OperatingSystem"),
	WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
	NULL,
	&pEnumerator);

if (FAILED(hres))
{
	cout << "Query for operating system name failed."
		<< " Error code = 0x"
		<< hex << hres << endl;
	pSvc->Release();
	pLoc->Release();
	goto CLEANUP;
}

// Step 7: -------------------------------------------------
// Get the data from the query in step 6 -------------------

IWbemClassObject *pclsObj = NULL;
ULONG uReturn = 0;

while (pEnumerator)
{
	HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
		&pclsObj, &uReturn);

	if (0 == uReturn)
	{
		break;
	}

	VARIANT vtProp;

	// Get the value of the Name property
	hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
	wcout << " OS Name : " << vtProp.bstrVal << endl;
	VariantClear(&vtProp);

	pclsObj->Release();
}

// Cleanup
// ========
CLEANUP:

pSvc->Release();
pLoc->Release();
pEnumerator->Release();
CoUninitialize();

return osnamevalues;   // Program successfully completed.

}




std::map<string, string> GetprocessPerformance()
{
	// To add error checking,
	// check returned HRESULT below where collected.
	HRESULT                 hr = S_OK;
	IWbemRefresher          *pRefresher = NULL;
	IWbemConfigureRefresher *pConfig = NULL;
	IWbemHiPerfEnum         *pEnum = NULL;
	IWbemServices           *pNameSpace = NULL;
	IWbemLocator            *pWbemLocator = NULL;
	IWbemObjectAccess       **apEnumAccess = NULL;
	BSTR                    bstrNameSpace = NULL;
	long                    lID = 0;
	long                    lVirtualBytesHandle = 0;
	long                    lIDProcessHandle = 0;
	DWORD                   dwVirtualBytes = 0;
	DWORD                   dwProcessId = 0;
	DWORD                   dwNumObjects = 0;
	DWORD                   dwNumReturned = 0;
	DWORD                   dwIDProcess = 0;
	DWORD                   i = 0;
	int                     x = 0;
	map<string, string> procperf;
	if (FAILED(hr = CoInitializeEx(NULL, COINIT_MULTITHREADED)))
	{
		goto CLEANUP;
	}

	if (FAILED(hr = CoInitializeSecurity(
		NULL,
		-1,
		NULL,
		NULL,
		RPC_C_AUTHN_LEVEL_NONE,
		RPC_C_IMP_LEVEL_IMPERSONATE,
		NULL, EOAC_NONE, 0)))
	{
		goto CLEANUP;
	}

	if (FAILED(hr = CoCreateInstance(
		CLSID_WbemLocator,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWbemLocator,
		(void**)&pWbemLocator)))
	{
		goto CLEANUP;
	}

	// Connect to the desired namespace.
	bstrNameSpace = SysAllocString(L"\\\\.\\root\\cimv2");
	if (NULL == bstrNameSpace)
	{
		hr = E_OUTOFMEMORY;
		goto CLEANUP;
	}
	if (FAILED(hr = pWbemLocator->ConnectServer(
		bstrNameSpace,
		NULL, // User name
		NULL, // Password
		NULL, // Locale
		0L,   // Security flags
		NULL, // Authority
		NULL, // Wbem context
		&pNameSpace)))
	{
		goto CLEANUP;
	}
	pWbemLocator->Release();
	pWbemLocator = NULL;
	SysFreeString(bstrNameSpace);
	bstrNameSpace = NULL;

	if (FAILED(hr = CoCreateInstance(
		CLSID_WbemRefresher,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWbemRefresher,
		(void**)&pRefresher)))
	{
		goto CLEANUP;
	}

	if (FAILED(hr = pRefresher->QueryInterface(
		IID_IWbemConfigureRefresher,
		(void **)&pConfig)))
	{
		goto CLEANUP;
	}

	// Add an enumerator to the refresher.
	if (FAILED(hr = pConfig->AddEnum(
		pNameSpace,
		L"Win32_PerfRawData_PerfProc_Process",
		0,
		NULL,
		&pEnum,
		&lID)))
	{
		goto CLEANUP;
	}
	pConfig->Release();
	pConfig = NULL;

	// Get a property handle for the VirtualBytes property.

	// Refresh the object ten times and retrieve the value.
	for (x = 0; x < 10; x++)
	{
		dwNumReturned = 0;
		dwIDProcess = 0;
		dwNumObjects = 0;

		if (FAILED(hr = pRefresher->Refresh(0L)))
		{
			goto CLEANUP;
		}

		hr = pEnum->GetObjects(0L,
			dwNumObjects,
			apEnumAccess,
			&dwNumReturned);
		// If the buffer was not big enough,
		// allocate a bigger buffer and retry.
		if (hr == WBEM_E_BUFFER_TOO_SMALL
			&& dwNumReturned > dwNumObjects)
		{
			apEnumAccess = new IWbemObjectAccess*[dwNumReturned];
			if (NULL == apEnumAccess)
			{
				hr = E_OUTOFMEMORY;
				goto CLEANUP;
			}
			SecureZeroMemory(apEnumAccess,
				dwNumReturned * sizeof(IWbemObjectAccess*));
			dwNumObjects = dwNumReturned;

			if (FAILED(hr = pEnum->GetObjects(0L,
				dwNumObjects,
				apEnumAccess,
				&dwNumReturned)))
			{
				goto CLEANUP;
			}
		}
		else
		{
			if (hr == WBEM_S_NO_ERROR)
			{
				hr = WBEM_E_NOT_FOUND;
				goto CLEANUP;
			}
		}

		// First time through, get the handles.
		if (0 == x)
		{
			CIMTYPE VirtualBytesType;
			CIMTYPE ProcessHandleType;
			if (FAILED(hr = apEnumAccess[0]->GetPropertyHandle(
				L"VirtualBytes",
				&VirtualBytesType,
				&lVirtualBytesHandle)))
			{
				goto CLEANUP;
			}
			if (FAILED(hr = apEnumAccess[0]->GetPropertyHandle(
				L"IDProcess",
				&ProcessHandleType,
				&lIDProcessHandle)))
			{
				goto CLEANUP;
			}
		}

		for (i = 0; i < dwNumReturned; i++)
		{
			if (FAILED(hr = apEnumAccess[i]->ReadDWORD(
				lVirtualBytesHandle,
				&dwVirtualBytes)))
			{
				goto CLEANUP;
			}
			if (FAILED(hr = apEnumAccess[i]->ReadDWORD(
				lIDProcessHandle,
				&dwIDProcess)))
			{
				goto CLEANUP;
			}

			wprintf(L"Process ID %lu is using %lu bytes\n",
				dwIDProcess, dwVirtualBytes);

			// Done with the object
			apEnumAccess[i]->Release();
			apEnumAccess[i] = NULL;
		}

		if (NULL != apEnumAccess)
		{
			delete[] apEnumAccess;
			apEnumAccess = NULL;
		}

		// Sleep for a second.
		Sleep(1000);
	}
	// exit loop here
CLEANUP:

	if (NULL != bstrNameSpace)
	{
		SysFreeString(bstrNameSpace);
	}

	if (NULL != apEnumAccess)
	{
		for (i = 0; i < dwNumReturned; i++)
		{
			if (apEnumAccess[i] != NULL)
			{
				apEnumAccess[i]->Release();
				apEnumAccess[i] = NULL;
			}
		}
		delete[] apEnumAccess;
	}
	if (NULL != pWbemLocator)
	{
		pWbemLocator->Release();
	}
	if (NULL != pNameSpace)
	{
		pNameSpace->Release();
	}
	if (NULL != pEnum)
	{
		pEnum->Release();
	}
	if (NULL != pConfig)
	{
		pConfig->Release();
	}
	if (NULL != pRefresher)
	{
		pRefresher->Release();
	}

	CoUninitialize();

	if (FAILED(hr))
	{
		cout << "Error status:"<< hr;
	}
	return procperf;
}