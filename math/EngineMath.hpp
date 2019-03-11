#ifndef ENGINE_MATH_HPP_
#define ENGINE_MATH_HPP_

#include <iostream>
using namespace std;
namespace Math{
    template <class T>
    class Vector2{
    public:
        // Default constructor, no arguments
        Vector2(){}

        // Constructor that allows for initializing X and Y.
        Vector2(T x1, T y1) : x(x1), y(y1) {}

        // Getters
        T getX(){return x;}
        T getY(){return y;}

        // Setters
        void setX(T x1){x = x1;}
        void setY(T y1){y = y1;}

        // Functions/Operations, these require that +, -, * are defined on type T

        // Element wise addition operator
        Vector2 operator+(Vector2& obj){
            Vector2<T> tmp = *this;
            tmp.x = this->x + obj.x;
            tmp.y = this->y + obj.y;
            return tmp;
        }

        // Element wise subtraction operator
        Vector2 operator-(Vector2& obj){
            Vector2<T> tmp = *this;
            tmp.x = this->x - obj.x;
            tmp.y = this->y - obj.y;
            return tmp;
        }

        // Dot product of two vectors
        T operator*(Vector2& obj){
            return (this->x * obj.x) + (this->y * obj.y);
        }
        // As to not overshadow the template class T (which really, K = T), we use a new template
        template <class K>
        friend ostream& operator<<(ostream& os, const Vector2<K> &g);

        template <class K>
        friend istream& operator>>(istream &is, Vector2<T> &c);
    protected:
        // Variables, hidden for data hiding purposes. The user should not get direct access.
        T x;
        T y;
    };

    template <class T>
    ostream& operator<<(ostream& os, const Vector2<T> &obj){
        os << "Vector2 {" << obj.x <<", "<< obj.y<<"}";
        return os;
    }

    template <class T>
    istream& operator>>(istream& is, Vector2<T> &obj){
        is >> obj.x >> obj.y;
        return is;
    }


    // A useful class of Vector2's that store only ints.
    class Vector2Int : public Vector2<int>{
    public:
        Vector2Int():Vector2<int>(){}
        Vector2Int(int x, int y):Vector2<int>(x,y){}

        Vector2Int(Vector2<int>& A){
            this->x = A.getX();
            this->y = A.getY();
        }
        Vector2Int(Vector2<int>&& A){
            this->x = A.getX();
            this->y = A.getY();
        }
    };
    class Vector2Float : public Vector2<float>{
    public:
        Vector2Float():Vector2<float>(){}
        Vector2Float(float x, float y):Vector2<float>(x,y){}

        Vector2Float(Vector2<float>& A){
            this->x = A.getX();
            this->y = A.getY();
        }
        Vector2Float(Vector2<int>& A){
            this->x = A.getX();
            this->y = A.getY();
        }
        Vector2Float(Vector2<float>&& A){
            this->x = A.getX();
            this->y = A.getY();
        }
        Vector2Float(Vector2<int>&& A){
            this->x = A.getX();
            this->y = A.getY();
        }
    };
}

#endif /* ENGINE_MATH_HPP_ */
