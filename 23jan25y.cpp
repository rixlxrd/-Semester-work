#include <iostream>
#include <math.h>
using namespace std;

double F(double x, double y, double z, double a) {
    return fabs(cos(x + a)) / (2 + sin(y + z));
}

double T(double u) {
    int scale = 1024;
    int binary = (int)(u * scale);
    int reversed = 0;
    for (int i = 0; i < 10; ++i) {
        reversed <<= 1;
        reversed |= (binary & 1);
        binary >>= 1;
    }
    return (double)reversed / scale;
}

void interval(int R, double z, int xi[]) {
    int k = (int)(z * R);
    if (k >= 0 && k < R) {
        xi[k]++;
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    double x_minus2, x_minus1, x0;
    const int N = 100, R = 10;
    cout << "Введите x(-2), x(-1), x0 через пробел: ";
    cin >> x_minus2 >> x_minus1 >> x0;
    cout << "----------------------\n";

    for (int a = 0; a <= 1; ++a) {
        double x[N];
        x[0] = x_minus2;
        x[1] = x_minus1;
        x[2] = x0;

        int xi[R] = { 0 };

        for (int i = 3; i < N; ++i) {
            x[i] = T(F(x[i - 1], x[i - 2], x[i - 3], a));
            interval(R, x[i], xi);
        }

        double M_xi = 0;
        for (int k = 0; k < R; ++k) {
            M_xi += ((2.0 * k + 1) / (2.0 * R)) * (xi[k] / (double)N);
        }

        double D_xi = 0;
        for (int k = 0; k < R; ++k) {
            D_xi += pow((2.0 * k + 1) / (2.0 * R) - M_xi, 2) * (xi[k] / (double)N);
        }
        cout << "Результаты для a = " << a << ":" << endl;
        cout << "Массив eps: ";
        for (int k = 0; k < R; ++k) {
            cout << xi[k] << " ";
        }
        cout << endl;
        cout << "Математическое ожидание M(eps): " << M_xi << endl;
        cout << "Дисперсия D(eps): " << D_xi << endl;
        cout << "----------------------\n";
    }

    return 0;
}
