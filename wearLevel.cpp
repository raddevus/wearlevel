#include <windows.h>
#include <iostream>
#include <locale>
#include <sysinfoapi.h>

std::string displayValue(LONGLONG);
void getOsUptime();

int main(int argc, char *argv[]) { 
    std::string targetDrive = "\\\\.\\";
    if (argc >1){
        targetDrive.append(argv[1]);
        targetDrive.append(":");
        std::cout << targetDrive << std::endl;
    }
    else{
        targetDrive += "C:";
    }
    HANDLE dev = CreateFile(targetDrive.c_str(), 
        FILE_READ_ATTRIBUTES, 
        FILE_SHARE_READ | FILE_SHARE_WRITE, 
        NULL, 
        OPEN_EXISTING, 
        0, 
        NULL);

    DISK_PERFORMANCE disk_info { };
    DWORD bytes;

    if (dev == INVALID_HANDLE_VALUE) {
        std::cerr << "Error opening disk\n";
        return 1;
    }

    if (!DeviceIoControl(dev, 
            IOCTL_DISK_PERFORMANCE, 
            NULL, 
            0, 
            &disk_info, 
            sizeof(disk_info), 
            &bytes, 
            NULL))
    {
        std::cerr << "Failure in DeviceIoControl\n";
        return 1;
    }
    //std::cout << (disk_info.BytesRead.QuadPart).Type() << std::endl;
    //displayValue(disk_info.BytesRead.QuadPart );
    //std::cout.imbue(std::locale(""));
    //std::cout.imbue(std::locale::global(std::locale("")));
    std::cout << "Bytes read: " << displayValue(disk_info.BytesRead.QuadPart) << "\n";
    std::cout << "Bytes written: " << displayValue(disk_info.BytesWritten.QuadPart) << "\n";
    getOsUptime();
}

std::string displayValue(LONGLONG byteCount){
   auto s = std::to_string(byteCount);
   int n = s.length() - 3;
   while (n > 0) {
      s.insert(n, ",");
      n -= 3;
   }
   return s;
}

void getOsUptime(){
    ULONGLONG milli = GetTickCount64();
    //3600000 milliseconds in an hour
    long days = milli / (3600000 *24);
    milli = milli - (3600000 *24) * days;
    long hr = milli / 3600000;
    milli = milli - 3600000 * hr;
    //60000 milliseconds in a minute
    long min = milli / 60000;
    milli = milli - 60000 * min;

    //1000 milliseconds in a second
    long sec = milli / 1000;
    milli = milli - 1000 * sec;
    std::cout << "OS has been running " << days << " days " << hr << " hours " << min << " minutes " << sec << " seconds " << milli << " ms." << std::endl;
}