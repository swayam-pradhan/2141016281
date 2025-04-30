#include <iostream>
#include <sys/sysinfo.h>
using namespace std;

void displayMemoryInfo() {
    struct sysinfo info;
    if (sysinfo(&info) == 0) {
        cout << "Total RAM: " << info.totalram / (1024 * 1024) << " MB\n";
        cout << "Total RAM: " << info.totalram / (1024 * 1024 * 1024) << " GB\n";
        cout << "Free RAM : " << info.freeram / (1024 * 1024) << " MB\n";
        cout << "Free RAM : " << info.freeram / (1024 * 1024 * 1024) << " GB\n";
    } else {
        cout << "Failed to get system info.\n";
    }
}

int main() {
    displayMemoryInfo();
    return 0;
}
