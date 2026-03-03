#ifndef NODO_HPP
#define NODO_HPP

using namespace std;

template <typename T>
class Nodo {
private:
    T info;
    Nodo<T>* next;

public:
    Nodo(const T& value, Nodo<T>* nextNode = NULL) : info(value), next(nextNode) {}

    T& getInfo() { return info; }
    const T& getInfo() const { return info; }
    void setInfo(const T& value) { info = value; }

    Nodo<T>* getNext() const { return next; }
    void setNext(Nodo<T>* nextNode) { next = nextNode; }
};

#endif
