#include <iostream>
#include <cmath>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

//
// 返り値に多項式f(x)の関数値，第３引数にdf(x)/dxの値を設定する関数
//
double poly(const VectorXd& w, double x, double& g) {

  double f = 0;

  // fに関数値，gに微分値を設定
  double t = 1;
  g = 0;
  // forループでt=1に繰り返しxをかけてべき乗の計算をする
  // 対応するw(i)とtをかけてfに足していく
  // tをxで割って字数を下げ，iとw(i)をかけて微分値をgに足していく
  for(int i=0; i<w.size(); i++) {
      f += w(i) * t;
      g += i * w(i) * t/x;
      t *= x;
  }

  return f;
}

bool solvPolyNewton(const VectorXd& w, double& x) {

  int max_iter = 100;
  double tol = 1e-8;

  double g;
  for(int i = 0; i < max_iter; ++i) {

    double f = poly(w, x, g);
    cout << "-------------------------" << endl;
    cout << "Iteration = " << i << endl;
    cout << "x = " << x << endl;
    cout << "f(x) = " << f << endl;

    //
    // ニュートン法の繰り返しを作成
    //
    x = x - f / g;

    //
    // |f(x)| < tol が成立したら終了
    //
    // trueを返却
    if(abs(f)<tol) {
        cout << "Newton successfully terminated" << endl;
        return true;
    }

  }
  // forループが回りきってしまった場合falseを返却して終了
  cout << "Newton iteration reached the maximum." << endl;

  return false;
}

int main() {

  VectorXd w = VectorXd::Zero(10);

  w(5) = 0.1;
  w(4) = 0.5;
  w(3) = -2;
  w(2) = -2;
  w(0) = -20;

  double x = -3;

  cout << "w = " << w.transpose() << endl;
  solvPolyNewton(w,x);
  cout << "Approximated solution of f(x) = 0 is " << x << endl;
  cout << "==============================================" << endl;

  // 2回目
    w(5) = 0.2;
    w(4) = 0.3;
    w(3) = -5;
    w(2) = -7;
    w(0) = -30;

    x = 5;

    cout << "w = " << w.transpose() << endl;
    solvPolyNewton(w,x);
    cout << "Approximated solution of f(x) = 0 is " << x << endl;

  return 0;
}
