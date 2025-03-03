#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;
const double MIN = 1e-6;
int n, m, x, y;
void assemble(vector<vector<double>> &coefficient, vector<vector<double>> &a, int &digit) {
    /*for(int i = 0; i < m; i++)
        for(int j = 0; j <= m; j++)
            coefficient[i][j] = 0.0;*/
    int n_temp = m - 2;
    coefficient[0][0] = 2.0 / 3.0;
    coefficient[0][1] = -1.0 / 3.0;
    coefficient[m - 1][m - 2] = -1.0 / 3.0;
    coefficient[m - 1][m - 1] = 2.0 / 3.0;
    if(m > 2) {
        for (int i = 1; i <= n_temp; i++) {
            coefficient[i][i - 1] = -1.0 / 4.0;
            coefficient[i][i] = 3.0 / 4.0;
            coefficient[i][i + 1] = -1.0 / 4.0;
        }
    }
    coefficient[0][m] = a[digit + 1][0] / 3.0  + 1.0;
    coefficient[m - 1][m] = a[digit + 1][m - 1] / 3.0  + 1.0;
    if(m > 2)
        for (int i = 1; i <= n_temp; i++)
            coefficient[i][m] = a[digit + 1][i] / 4.0 + 1.0;
    /*cout << "---coefficient matrix" << endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j <= m; j++)
            cout << coefficient[i][j] << " ";
        cout << endl;
    }
    cout << "---coefficient matrix end" << endl;*/
}
void elimination(vector<vector<double>> &coefficient) {
    int col = 0, pivot = 0;
    for (; col < m; col++)
    {
        int max_row = pivot;
        /*for (int i = pivot + 1; i < m; i++)
            if(fabs(coefficient[max_row][col]) < fabs(coefficient[i][col]))
                max_row = i;
        if(fabs(coefficient[max_row][col]) < MIN)
            continue;
        if(pivot != max_row)
            for(int i = 0; i <= m; i++)
                swap(coefficient[max_row][i], coefficient[pivot][i]);*/
        double factor_pivot = coefficient[pivot][col];
        for (int i = col; i <= min(m - 1, col + 1); i++)
            coefficient[pivot][i] = coefficient[pivot][i] / factor_pivot;
        coefficient[pivot][m] /= factor_pivot;
        //for (int i = 0; i < m; i++) {
        //    if(i != pivot){
        if(pivot < m - 1){
            double factor = coefficient[pivot + 1][col];
            for (int j = col; j <= min(m - 1, col + 1); j++) {
                coefficient[pivot + 1][j] = coefficient[pivot + 1][j] - factor * coefficient[pivot][j];
            }
            coefficient[pivot + 1][m] = coefficient[pivot + 1][m] - factor * coefficient[pivot][m];
        }
        //    }
        //}
        pivot++;
    }
}
void recurse(const vector<vector<double>> &coefficient, vector<vector<double>> &a, int& digit) {
    for (int i = m - 1; i >= 0; --i) {
        a[digit][i] = coefficient[i][m];
        if (i + 1 < m) {
            a[digit][i] -= coefficient[i][i + 1] * a[digit][i + 1];
        }
        a[digit][i] /= coefficient[i][i];
    }
}
int main() {
    cin >> n >> m >> x >> y;
    if(n == 1) {
        cout << fixed << setprecision(5) << 0.0 << endl;
    }else if(m == 1) {
        double temp = 2 * (n - x);
        cout << fixed << setprecision(5) << temp << endl;
    }else {
        // cout << "sl3" << endl;
        vector<vector<double>> a(n, vector<double>(m, 0.0));
        vector<vector<double>> coefficient(m, vector<double>(m + 1, 0.0));
        for (int digit = n - 2; digit >= x - 1; digit--) {
            assemble(coefficient, a, digit);
            elimination(coefficient);
            recurse(coefficient, a, digit);
            bool converged = true;
            for (int i = 0; i < m; i++) {
                if (fabs(a[digit][i] - a[digit + 1][i]) >= 0.00001) {
                    converged = false;
                    break;
                }
            }
            if (converged) {
                cout << fixed << setprecision(5) << a[digit][y - 1] << endl;
                return 0;
            }
        }
        cout << fixed << setprecision(5) << a[x - 1][y - 1] << endl;
    }
    return 0;
}