//MS Copilot AI generated this c code as an example of how to
//communicate with bluetooth devices in Win32API on Windows.
//
//Twilight Wizard                                 2/9/2025
//	- Windows 11
//	- Win32API


// AI said, "To interact with a real Bluetooth device on Windows using the Win32 API, you'll need to use the BluetoothAPIs.h 
//           functions for device discovery, opening a connection, reading data, and closing the connection. Here's an example
//           program that demonstrates these steps:"

#include <windows.h>
#include <stdio.h>
#include <bluetoothapis.h>
#include <bthsdpdef.h>
#include <bthdef.h>
#include <ws2bth.h>

#pragma comment(lib, "Bthprops.lib")
#pragma comment(lib, "Ws2_32.lib")

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

HANDLE OpenBluetoothDevice(BLUETOOTH_DEVICE_INFO *deviceInfo) {
    SOCKADDR_BTH sa = { 0 };
    int sa_len = sizeof(sa);
    SOCKET s = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);

    if (s == INVALID_SOCKET) {
        printf("Failed to create socket.\n");
        return INVALID_HANDLE_VALUE;
    }

    sa.addressFamily = AF_BTH;
    sa.btAddr = deviceInfo->Address.ullLong;
    sa.serviceClassId = RFCOMM_PROTOCOL_UUID;
    sa.port = BT_PORT_ANY;

    if (connect(s, (struct sockaddr *)&sa, sa_len) == SOCKET_ERROR) {
        printf("Failed to connect to device.\n");
        closesocket(s);
        return INVALID_HANDLE_VALUE;
    }

    printf("Connected to Bluetooth device: %ls\n", deviceInfo->szName);
    return (HANDLE)s;
}

void ReadFromBluetoothDevice(HANDLE hDevice) {
    char buffer[1024];
    int bytesRead;

    if (hDevice == INVALID_HANDLE_VALUE) {
        printf("Invalid device handle.\n");
        return;
    }

    bytesRead = recv((SOCKET)hDevice, buffer, sizeof(buffer), 0);
    if (bytesRead == SOCKET_ERROR) {
        printf("Failed to read from device.\n");
    } else {
        buffer[bytesRead] = '\0';
        printf("Data read from device: %s\n", buffer);
    }
}

void CloseBluetoothDevice(HANDLE hDevice) {
    if (hDevice != INVALID_HANDLE_VALUE) {
        closesocket((SOCKET)hDevice);
        printf("Closed Bluetooth device.\n");
    } else {
        printf("Invalid device handle.\n");
    }
}

int main() {
    BLUETOOTH_DEVICE_INFO deviceInfo;
    HANDLE hDevice;

    ListBluetoothDevices();

    // Simulate device info for demonstration purposes
    ZeroMemory(&deviceInfo, sizeof(deviceInfo));
    deviceInfo.dwSize = sizeof(deviceInfo);
    wcscpy_s(deviceInfo.szName, L"Sample Bluetooth Device");
    deviceInfo.Address.ullLong = 0x001122334455; // Example address

    hDevice = OpenBluetoothDevice(&deviceInfo);
    ReadFromBluetoothDevice(hDevice);
    CloseBluetoothDevice(hDevice);

    return 0;
}
