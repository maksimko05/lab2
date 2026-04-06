#include "Triangle.h"
#include <iostream>
#include <cmath>

#define IN 1
#define OUT 0
#define BORDER 2

using namespace std;

int sign(double n) {
    if(abs(n) < 1e-9) return 0;
    if (n > 0) return 1;
    return -1;
}

double determinant(Point A, Point B){
    return A.x * B.y - A.y * B.x;
}

double Triangle::area() const {
    return 0.5 * abs(determinant(A, B) + determinant(B, C) + determinant(C, A));
}

double distance(const Point &p1, const Point &p2){
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

int containsOnDegenerate(const Triangle &triangle, const Point &point){
    Point p1 = triangle.A;
        Point p2 = triangle.B;
        if(distance(p1, p2) < distance(triangle.A, triangle.C)){
            p2 = triangle.C;
        }

        if(distance(p1, p2) < distance(triangle.B, triangle.C)){
            p1 = triangle.B;
        }

        return distance(point, p1) + distance(point, p2) - distance(p1, p2) < 1e-9 ? BORDER : OUT;
}

int Triangle::containsByArea(const Point &point) const {
    if(area() == 0){
        return containsOnDegenerate(*this, point);
    }
    if(sign(area() - (Triangle{A, B, point}.area() + Triangle{B, C, point}.area() + Triangle{A, C, point}.area())) == 0){
        if(sign(Triangle{A, B, point}.area()) == 0 || sign(Triangle{B, C, point}.area()) == 0 || sign(Triangle{A, C, point}.area()) == 0){
            return BORDER;
        }
        return IN;
    }
    return OUT;
}

int Triangle::contains(const Point &point) const {
    const double sign1 = sign(determinant(point - A, B - A));
    const double sign2 = sign(determinant(point - B, C - B));
    const double sign3 = sign(determinant(point - C, A - C));

    if(area() == 0){
        return containsOnDegenerate(*this, point);
    }

    if(sign1 == sign2 && sign2 == sign3){
        return IN;
    }
    
    return (sign1 == 0 && sign2 == sign3) ||
        (sign2 == 0 && sign1 == sign3) || 
        (sign3 == 0 && sign1 == sign2) ||
        (sign1 == 0 && sign2 == 0) ||
        (sign1 == 0 && sign3 == 0) ||
        (sign2 == 0 && sign3 == 0) ? BORDER : OUT;
}

void handler(){
    Triangle triangle;
    cout << "Введіть координати точок трикутника в данному форматі: (A.x A.y B.x B.y C.x C.y)\n";
    cin >> triangle.A.x;
    cin >> triangle.A.y;
    cin >> triangle.B.x;
    cin >> triangle.B.y;
    cin >> triangle.C.x;
    cin >> triangle.C.y;

    cout << "Введіть кількість точок на яких буде здійснена перевірка приналежності до трикутника: ";
    int amountPoints;
    cin >> amountPoints;

    cout << "\nВведіть тепер послідовно координати усіх точок: ";
    Point temp;

    for(int i = 0; i < amountPoints; i++){
        cin >> temp.x;
        cin >> temp.y;
        int result = triangle.contains(temp);
        if(result == IN){
            cout << "За методом векторного добутку: Точка належить трикутнику\n";
        } else if(result == BORDER){
            cout << "За методом векторного добутку: Точка належить границі трикутника\n";
        } else {
            cout << "За методом векторного добутку: Точка не належить трикутнику\n";
        }
        result = triangle.containsByArea(temp);
        if(result == IN){
            cout << "За методом площ: Точка належить трикутнику\n";
        } else if(result == BORDER){
            cout << "За методом площ: Точка належить границі трикутника\n";
        } else {
            cout << "За методом площ: Точка не належить трикутнику\n";
        }
        cout << endl;
    }

    return;
}