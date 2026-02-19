#ifndef NODO_HPP
#define NODO_HPP

template <typename T>
class Nodo {
private:
    T info;
    Nodo<T>* next;

public:
    Nodo(const T& value, Nodo<T>* nextNode = nullptr) : info(value), next(nextNode) {}

    const T& getInfo() const { return info; }
    void setInfo(const T& value) { info = value; }

    Nodo<T>* getNext() const { return next; }
    void setNext(Nodo<T>* nextNode) { next = nextNode; }
};

#endif
