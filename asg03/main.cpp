#include <iostream>
#include <cmath>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

//
// 多変量非線形方程式のためのニュートン法
// 引数1
// VectorXd (*func)(const VectorXd& x, MatrixXd& J)
//   返り値にベクトルf(x)，第二引数にヤコビ行列を設定する「関数」型引数
//   引数に渡す関数を変えることで色々なfを扱える
// 引数2
// VectorXd& x
//   初期解ベクトル
//
bool multiVariateNewton(VectorXd (*func)(const VectorXd& x, MatrixXd& J), VectorXd& x) {

  int n = x.size();
  double tol = 1e-8;
  VectorXd f(n);
  MatrixXd J(n,n);

  cout << "-------------------------" << endl;
  cout << "Newton iteration setting" << endl;
  cout << "Problem dimension: " << n << ", Stopping tolerance: " << tol << endl;

  int max_iter = 100;
  for(int iter = 0; iter < max_iter; ++iter) {

    f = func(x,J);

    //
    // ニュートン法の更新式を作成
    //
    // ヤコビ行列にfをかけたものを引いて解を更新
      x = x - J.inverse() * f;

    //
    // fのノルムがtol以下で終了
    //
    // ノルムの計算
    // fの各要素の2乗したものをnormに足していき，その後sqrtで平方根をとる
    double norm = 0;
    for(int i=0; i<f.size(); i++)
        norm += f(i) * f(i);
    norm = sqrt(norm);
    // norm<tol ならtrueを返却して正常終了
    if(norm<tol) {
        cout << "Newton successfully terminated" << endl;
        return true;
    }

  }

  // forループが回りきってしまったら，falseを返却して終了
  cout << "Newton iteration reached the maximum." << endl;

  return false;
}

//
// 問題設定１
//
VectorXd objective_func(const VectorXd& x, MatrixXd& J) {

  VectorXd f(x.size());

  //
  // ここに問題設定１の関数値f(x)の計算とヤコビ行列の計算を作成
  //
  f(0) = exp(-exp(-x(0) - x(1))) - x(1)*(1 + x(0)*x(0));
  f(1) = x(0)*cos(x(1)) + x(1)*sin(x(0)) - 1/2.0;
  J(0, 0) = exp(-exp(-x(0) - x(1)))*exp(-x(0) - x(1)) - 2*x(1)*x(0);
  J(0, 1) = exp(-exp(-x(0) - x(1)))*exp(-x(0) - x(1)) - (1 + x(0)*x(0));
  J(1, 0) = cos(x(1)) + x(1)*cos(x(0));
  J(1, 1) = -x(0)*sin(x(1)) + sin(x(0));

  return f;
}

//
// 問題設定２
//
VectorXd objective_func2(const VectorXd& x, MatrixXd& J) {

  VectorXd f(x.size());

  //
  // ここに問題設定２の関数値f(x)の計算とヤコビ行列の計算を作成
  //
  f(0) = x(0)*x(0) + x(1)*x(1) + x(0)*x(2) - x(0) - x(1) - 1;
  f(1) = x(0)*x(0)*x(0) + x(2)*x(2)*x(2) + 3*x(0)*x(0) - x(2)*x(2) + 2*x(1)*x(2) - 2*x(2) - 4;
  f(2) = 3*x(0)*x(1) + 2*x(0)*x(2) + 4*x(1)*x(2) - 3*x(1) - 4*x(2) - 2*x(0);
  J <<
    2*x(0)+x(2)-1,      2*x(1)-1,        x(0),
    3*x(0)*x(0)+6*x(0), 2*x(2),          3*x(2)*x(2)-2*x(2)+2*x(1)-2,
    3*x(1)+2*x(2)-2,    3*x(0)+4*x(2)-3, 2*x(0)+4*x(1)-4;

  return f;
}

int main() {

  cout << "-------------------Problem 1-------------------" << endl;

  VectorXd x1(2);

  //
  // 問題設定１の初期値
  //
  x1(0) = 0.8;
  x1(1) = 0.9;

  cout << "x1 = " << x1.transpose() << endl;

  multiVariateNewton(objective_func,x1);

  cout << "=========================" << endl;
  cout << "Solution for the problem 1: " << endl;
  cout << x1.transpose() << endl;

  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

  // 2回目
  x1(0) = 10000;
  x1(1) = 10000;

  cout << "x1 = " << x1.transpose() << endl;

  multiVariateNewton(objective_func,x1);

  cout << "=========================" << endl;
  cout << "Solution for the problem 1: " << endl;
  cout << x1.transpose() << endl;


  cout << "-------------------Problem 2-------------------" << endl;

  //
  // 問題設定２の実行用コード
  //
  VectorXd x2(3);

  //
  // 問題設定２の初期値
  //
  x2(0) = 1.2;
  x2(1) = 1.2;
  x2(2) = 1.2;

  cout << "x2 = " << x2.transpose() << endl;

  multiVariateNewton(objective_func2,x2);

  cout << "=========================" << endl;
  cout << "Solution for the problem 2: " << endl;
  cout << x2.transpose() << endl;

  cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

  // 2回目
  x2(0) = 5.3;
  x2(1) = 1.7;
  x2(2) = 2.6;

  cout << "x2 = " << x2.transpose() << endl;

  multiVariateNewton(objective_func2,x2);

  cout << "=========================" << endl;
  cout << "Solution for the problem 2: " << endl;
  cout << x2.transpose() << endl;



  return 0;
}
