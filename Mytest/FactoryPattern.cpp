#include <iostream>
using namespace std;

enum ProductType {
    TypeA,
    TypeB,
    TypeC
};


class Product { //抽象接口
public:
    virtual void show() = 0;
    virtual ~Product() {
        cout << "~Product\n";
    };
};

class ProductA : public Product{
public:
    ProductA() {
        cout << "ProductA create 1.\n";
    }
    void show () {
        cout << "This is ProductA\n";
    }
    ~ProductA() {cout << "~ProductA()\n";}
};
class ProductB : public Product{
public:
    ProductB() {
        cout << "ProductB create 1.\n";
    }
    void show () {
        cout << "This is ProductB\n";
    }
    ~ProductB() {cout << "~ProductB()\n";}
};
class ProductC : public Product{
public:
    ProductC() {
        cout << "ProductC create 1.\n";
    }
    void show () {
        cout << "This is ProductC\n";
    }
    ~ProductC() {cout << "~ProductC()\n";}
};

class Factory {
public:
    Product* create(ProductType type) {
        switch (type) {
            case TypeA:
                return new ProductA();
            case TypeB:
                return new ProductB();
            case TypeC:
                return new ProductC();
            default:
                return nullptr;
        }
    }
};

int main() {
    Factory factory1;
    Product* a1 = factory1.create(TypeA);
    Product* b1 = factory1.create(TypeB);
    Product* c1 = factory1.create(TypeC);
    delete a1;
    return 0;
}