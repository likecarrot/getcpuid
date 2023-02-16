#include <winsock2.h>
#include <windows.h>
#include    <intrin.h>
#include    <stdio.h>
#include <iphlpapi.h>
#include	<string>
#include <iostream>
#pragma comment(lib, "IPHLPAPI.lib")
using namespace std;
int main()
{
    int i[4] = { 0 };
    __cpuid(i, 1);
    printf("cpuid-----%X %08X ", i[3], i[0]);

	bool ret = false;
	ULONG outBufLen = sizeof(IP_ADAPTER_ADDRESSES);
	PIP_ADAPTER_ADDRESSES pAddresses = (IP_ADAPTER_ADDRESSES*)malloc(outBufLen);
	if (pAddresses == NULL)
		return false;
	if (GetAdaptersAddresses(AF_UNSPEC, 0, NULL, pAddresses, &outBufLen) == ERROR_BUFFER_OVERFLOW)
	{
		free(pAddresses);
		pAddresses = (IP_ADAPTER_ADDRESSES*)malloc(outBufLen);
		if (pAddresses == NULL)
			return false;
	}

	if (GetAdaptersAddresses(AF_UNSPEC, 0, NULL, pAddresses, &outBufLen) == NO_ERROR)
	{
		for (PIP_ADAPTER_ADDRESSES pCurrAddresses = pAddresses; pCurrAddresses != NULL; pCurrAddresses = pCurrAddresses->Next)
		{
			if (pCurrAddresses->PhysicalAddressLength != 6)
				continue;
			char acMAC[32];
			sprintf(acMAC, "%02X-%02X-%02X-%02X-%02X-%02X",
				int(pCurrAddresses->PhysicalAddress[0]),
				int(pCurrAddresses->PhysicalAddress[1]),
				int(pCurrAddresses->PhysicalAddress[2]),
				int(pCurrAddresses->PhysicalAddress[3]),
				int(pCurrAddresses->PhysicalAddress[4]),
				int(pCurrAddresses->PhysicalAddress[5]));
			string macOUT = acMAC;
			cout << endl <<"MAC------" << macOUT << endl;
			ret = true;
			break;
		}
	}

	free(pAddresses);

    system("pause");
    return 0;
}