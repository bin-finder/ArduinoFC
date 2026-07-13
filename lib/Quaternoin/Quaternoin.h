#pragma once
#include <math.h>

template<typename T>
struct Quaternoin{
public:
  T w, x, y, z;

  Quaternoin() : w(T(1)), x(T(0)), y(T(0)), z(T(0)) {}
  /*
  This is the initiliser.
  @param data Pointer to an array of 4 elements corrosponding to {w,x,y,z}
  */
  Quaternoin(T w, T x, T y, T z) : w(w),x(x),y(y),z(z) {}

  double norm(){
    return sqrt(x*x+y*y+z*z);
  }

  void normalize(){
    double magnitude = norm();
    w /= magnitude;
    x /= magnitude;
    y /= magnitude;
    z /= magnitude;
  }

  /*
  The Hamilton Product for Quaternoins
  https://en.wikipedia.org/wiki/Quaternion#Hamilton_product
  @param pointer to other Quaternoin object to be multlipied.
  */
  Quaternoin<T> operator*(const Quaternoin<T>& q) const {
    return Quaternoin(
      w*q.w - x*q.x - y*q.y - z*q.z,
      w*q.x + x*q.w + y*q.z - z*q.y,
      w*q.y - x*q.z + y*q.w + z*q.x,
      w*q.z + x*q.y - y*q.x + z*q.w
    );
  }

  Quaternoin<T> operator+(const Quaternoin<T>& q) const {
    return Quaternoin(w+q.w,x+q.x,y+q.y,z+q.z);
  }

  void operator+=(const Quaternoin<T>& q) const {
    w+q.w;
    x+q.x;
    y+q.y;
    z+q.z;
  }

  Quaternoin<T> operator-(const Quaternoin<T>& q) const {
    return Quaternoin(w-q.w,x-q.x,y-q.y,z-q.z);
  }

  Quaternoin<T> operator*(const float num) const {
    return Quaternoin(w*num,x*num,y*num,z*num);
  }

  Quaternoin<T> operator/(const float num) const {
    return Quaternoin(w/num,x/num,y/num,z/num);
  }

  bool operator==(const Quaternoin<T>& quat) const{
    if(quat.w == w && quat.x == x && quat.y == y && quat.z == z){
      return true;
    }
    else{
      return false;
    }
  }
};

template<typename T>
Quaternoin<T> operator*(float num, const Quaternoin<T>& quat){
  return Quaternoin<T>(quat.w*num, quat.x*num, quat.y*num, quat.z*num);
}