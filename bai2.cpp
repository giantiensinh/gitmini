#include iostream
using namespace std;

int main() {
    int tong = 0;
    for (int i=0; i < 5; i++) {
        int songuyen;
        cout << "Nhập số nguyên thứ " << i + 1 << ": ";
        cin >> songuyen;
        tong+= songuyen;
    }
    cout << "Tổng của 5 số nguyên là: " << tong << endl;

    return 0;
}