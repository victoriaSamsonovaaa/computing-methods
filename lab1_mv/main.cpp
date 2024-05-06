#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <algorithm>
using namespace std;

// Функция разложения Холецкого
void solvingSLAE(vector<vector<double>>& A, vector<double>& b, vector<double>& x) {
    int n = A.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            double sum = 0.0;
            if (j == i) {
                for (int k = 0; k < j; k++) {
                    sum += pow(A[j][k], 2);
                }
                A[j][j] = sqrt(A[j][j] - sum);
            }
            else {
                for (int k = 0; k < j; k++) {
                    sum += A[j][k] * A[i][k];
                }
                A[i][j] = (A[i][j] - sum) / A[j][j];
            }
        }
    }

    // Решение системы L*y = b
    vector<double> y(n);
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for(int j = 0; j < i; j++) {
            sum += A[i][j] * y[j];
        }
        y[i] = (b[i] - sum) / A[i][i];
    }
    // Решение системы L^T*x = y
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0.0;
        for (int j = i + 1; j < n; j++) {
            sum += A[j][i] * x[j];
        }
        x[i] = (y[i] - sum) / A[i][i];
    }
}

void error(vector<double>& xEx, vector<double>& x, int n) {
    vector<double> diff(n);
    for (int i = 0; i < n; i++) {
        diff[i] = abs(xEx[i] - x[i]);
    }
    sort(diff.begin(), diff.end());
    cout << fixed << setprecision(2) << diff[n - 1];
}


int main() {
    int n = 5;
    vector<vector<double>> arr(n, vector<double> (n));
    arr[0][0] = 4.0;
    arr[0][1] = 0.0;
    arr[0][2] = -1.0;
    arr[0][3] = 0.0;
    arr[0][4] = -1.0;

    arr[1][0] = 0.0;
    arr[1][1] = 5.0;
    arr[1][2] = -2.0;
    arr[1][3] = -1.0;
    arr[1][4] = 0.0;

    arr[2][0] = -1.0;
    arr[2][1] = -2.0;
    arr[2][2] = 6.0;
    arr[2][3] = 0.0;
    arr[2][4] = -1.0;

    arr[3][0] = 0.0;
    arr[3][1] = -1.0;
    arr[3][2] = 0.0;
    arr[3][3] = 7.0;
    arr[3][4] = 0.0;

    arr[4][0] = -1.0;
    arr[4][1] = 0.0;
    arr[4][2] = -1.0;
    arr[4][3] = 0.0;
    arr[4][4] = 8.0;

    vector<double> b = {16.0, 12.0, 4.0, 10.0, 0.0};
    vector<double> x(n);
    vector<double> expAns = {5.00, 4.00, 3.00, 2.00, 1.00};

    cout << "INITIAL MATRIX:" << '\n';
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << fixed << setprecision(2) <<arr[i][j] << " ";
        }
        cout << '\n';
    }
    cout << '\n';

    cout << "VECTOR b: " << '\n';
    for (int j = 0; j < n; j++) {
        cout << fixed << setprecision(2) << "b[" << j << "] = " << b[j] << '\n';
    }
    cout << '\n';

    solvingSLAE(arr, b, x);

    cout << "THE OBTAINED x-VECTOR (OBTAINED ANSWER):" << '\n';
    for (int i = 0; i < n; i++) {
        cout.setf(ios::fixed);
        cout.precision(2);
        cout << fixed << setprecision(2) << "x[" << i << "] = " << x[i] << '\n';
    }
    cout << '\n';


    cout << "THE EXPECTED x-VECTOR (EXPECTED ANSWER):" << '\n';
    for (int i = 0; i < n; i++) {
        cout << fixed << setprecision(2) << "x[" << i << "] = " << expAns[i] << '\n';
    }
    cout << '\n';

    cout << "THE ERROR IS: ";
    error(expAns, x, n);
    cout << '\n' << '\n';
    vector<vector<double>> arr1(n, vector<double> (n));

    arr1[0][0] = 4.0;
    arr1[0][1] = 0.0;
    arr1[0][2] = -1.0;
    arr1[0][3] = 0.0;
    arr1[0][4] = -1.0;

    arr1[1][0] = 0.0;
    arr1[1][1] = 5.0;
    arr1[1][2] = -2.0;
    arr1[1][3] = -1.0;
    arr1[1][4] = 0.0;

    arr1[2][0] = -1.0;
    arr1[2][1] = -2.0;
    arr1[2][2] = 6.0;
    arr1[2][3] = 0.0;
    arr1[2][4] = -1.0;

    arr1[3][0] = 0.0;
    arr1[3][1] = -1.0;
    arr1[3][2] = 0.0;
    arr1[3][3] = 7.0;
    arr1[3][4] = 0.0;

    arr1[4][0] = -1.0;
    arr1[4][1] = 0.0;
    arr1[4][2] = -1.0;
    arr1[4][3] = 0.0;
    arr1[4][4] = 8.0;

    cout << "THE VECTOR OF ERRORS IS: " << '\n';
    vector<double> r1(n);
    vector<double> r(n);
    for (int i = 0; i < n; i++) {
        r1[i] = 0.0;
        for (int j = 0; j < n; j++) {
            r1[i] += arr1[i][j] * x[j];
        }
    }
    for (int i = 0; i < n; i++) {
        r[i] = b[i] - r1[i];
        cout << fixed << setprecision(2) << "r[" << i << "] = " << r[i] << '\n';
    }
    cout << '\n';

    return 0;
}
