#include <iostream>
#include <cmath>
#include <Eigen/Core>

using namespace std;
using namespace Eigen;

double poly(const VectorXd& w, double x) {

  //
  // 多項式f(x) = w_0 + w_1 x^1 + ... を計算
  //
  // forループでt=1に繰り返しxをかけてべき乗の計算をする
  // 対応するw(i)とtをかけてfに足していく
  double f = 0;
  double t = 1;
  for(int i=0; i<w.size(); i++) {
      f += w(i) * t;
      t *= x;
  }

  return f;
}

bool solvPolyBinarySearch(const VectorXd& w, double& a, double& b) {

  int max_iter = 100;
  double tol = 1e-8; // tolerance 許容誤差

  cout << "Binary search for polynomial function" << endl;

  for(int i = 0; i < max_iter; ++i) {

    //
    // f(a)とf(b)を計算する
    //
    double fa = poly(w, a);
    double fb = poly(w, b);

    cout << "-------------------------" << endl;
    cout << "Iteration = " << i << endl;
    cout << "a = " << a << ", b = " << b << endl;
    cout << "f(a) = " << fa << ", f(b) = " << fb << endl;
    cout << "|a - b| = " << abs(a-b) << endl;

    //
    // f(a)とf(b)の符号が同じ場合は異常終了
    //
    // falseを返却
    if(fa*fb > 0) {
      cout << "error: f(a) * f(b) > 0" << endl;
      return false;
    }

    // --------------------------------------------------
    // aとbの中点cでの関数値を調べて[a,b]を更新するコードを作成
    // --------------------------------------------------
    // 中点cとf(c)を計算し，fa*fcの符号によってbまたはaを新しくcに更新
    double c = (a + b) / 2;
    double fc = poly(w, c);
    if(fa*fc<0)
        b = c;
    else
        a = c;



    //
    // aとbの差が十分小さくなれば終了
    //
    // trueを返却
    if(abs(a-b) < tol) {
      cout << "Binary search successfully terminated" << endl;
      return true;
    }
  }

  // forループが回りきってしまった場合falseを返却して終了
  cout << "Binary search iteration reached the maximum." << endl;

  return false;
}

int main() {

  VectorXd w = VectorXd::Zero(10);

  //
  // 多項式の係数
  //
  w(5) = 0.1;
  w(4) = 0.5;
  w(3) = -2;
  w(2) = -2;
  w(0) = -20;

  //
  // 初期値
  //
  double a = 5;
  double b = -1;

  cout << "w = " << w.transpose() << endl;

  solvPolyBinarySearch(w,a,b);

  cout << "Approximated solution of f(x) = 0 is " << (a + b)/2 << endl;
  cout << "====================================================" << endl;

    //2回目
    //
    // 多項式の係数
    //
    w(5) = 0.2;
    w(4) = 0.3;
    w(3) = -5;
    w(2) = -7;
    w(0) = -30;

    //
    // 初期値
    //
     a = 10;
     b = -10;

    cout << "w = " << w.transpose() << endl;

    solvPolyBinarySearch(w,a,b);

    cout << "Approximated solution of f(x) = 0 is " << (a + b)/2 << endl;


  return 0;
}
