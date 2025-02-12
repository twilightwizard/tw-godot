//MS Copilot AI generated this c code as an example of how to
//communicate with bluetooth devices in Win32API on Windows.
//
//Twilight Wizard                                 2/9/2025
//	- Windows 11
//	- Win32API

#include <windows.h>
#include <stdio.h>
#include <bluetoothapis.h>

//Link to this bluetooth library
//#pragma comment(lib, "Bthprops.lib")

void ListBluetoothDevices() {
    BLUETOOTH_DEVICE_SEARCH_PARAMS searchParams;
    BLUETOOTH_DEVICE_INFO deviceInfo;
    HANDLE hFind;

    ZeroMemory(&searchParams, sizeof(searchParams));
    searchParams.dwSize = sizeof(searchParams);
    searchParams.fReturnAuthenticated = TRUE;
    searchParams.fReturnRemembered = TRUE;
    searchParams.fReturnUnknown = TRUE;
    searchParams.fReturnConnected = TRUE;
    searchParams.hRadio = NULL;

    deviceInfo.dwSize = sizeof(deviceInfo);

    hFind = BluetoothFindFirstDevice(&searchParams, &deviceInfo);
    if (hFind == NULL) {
        printf("No Bluetooth devices found.\n");
        return;
    }

    do {
        wprintf(L"Device found: %s\n", deviceInfo.szName);
    } while (BluetoothFindNextDevice(hFind, &deviceInfo));

    BluetoothFindDeviceClose(hFind);
}

int main() {
    ListBluetoothDevices();
    return 0;
}
