#ifndef LISTA_HPP
#define LISTA_HPP

#include <iostream>
#include <stdexcept>
#include <vector>
#include "Nodo.hpp"

template <typename T>
class Lista {
private:
    Nodo<T>* head;
    Nodo<T>* tail;
    int length;

public:
    Lista() : head(nullptr), tail(nullptr), length(0) {}

    Lista(const Lista<T>& other) : head(nullptr), tail(nullptr), length(0) {
        Nodo<T>* current = other.head;
        while (current) {
            insertar(current->getInfo(), length + 1);
            current = current->getNext();
        }
    }

    Lista<T>& operator=(const Lista<T>& other) {
        if (this == &other) {
            return *this;
        }
        vaciar();
        Nodo<T>* current = other.head;
        while (current) {
            insertar(current->getInfo(), length + 1);
            current = current->getNext();
        }
        return *this;
    }

    ~Lista() {
        vaciar();
    }

    int getLong() const {
        return length;
    }

    bool esVacia() const {
        return length == 0;
    }

    void insertar(const T& element, int pos) {
        if (pos < 1 || pos > length + 1) {
            throw std::out_of_range("Posicion invalida en insertar");
        }

        Nodo<T>* newNode = new Nodo<T>(element);

        if (length == 0) {
            head = newNode;
            tail = newNode;
            length = 1;
            return;
        }

        if (pos == 1) {
            newNode->setNext(head);
            head = newNode;
            ++length;
            return;
        }

        if (pos == length + 1) {
            tail->setNext(newNode);
            tail = newNode;
            ++length;
            return;
        }

        Nodo<T>* prev = head;
        for (int i = 1; i < pos - 1; ++i) {
            prev = prev->getNext();
        }

        newNode->setNext(prev->getNext());
        prev->setNext(newNode);
        ++length;
    }

    T consultar(int pos) const {
        if (pos < 1 || pos > length) {
            throw std::out_of_range("Posicion invalida en consultar");
        }

        if (pos == 1) {
            return head->getInfo();
        }

        if (pos == length) {
            return tail->getInfo();
        }

        Nodo<T>* current = head;
        for (int i = 1; i < pos; ++i) {
            current = current->getNext();
        }
        return current->getInfo();
    }

    void eliminar(int pos) {
        if (pos < 1 || pos > length) {
            throw std::out_of_range("Posicion invalida en eliminar");
        }

        if (length == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
            length = 0;
            return;
        }

        if (pos == 1) {
            Nodo<T>* toDelete = head;
            head = head->getNext();
            delete toDelete;
            --length;
            return;
        }

        if (pos == length) {
            Nodo<T>* prev = head;
            while (prev->getNext() != tail) {
                prev = prev->getNext();
            }
            delete tail;
            tail = prev;
            tail->setNext(nullptr);
            --length;
            return;
        }

        Nodo<T>* prev = head;
        for (int i = 1; i < pos - 1; ++i) {
            prev = prev->getNext();
        }

        Nodo<T>* toDelete = prev->getNext();
        prev->setNext(toDelete->getNext());
        delete toDelete;
        --length;
    }

    int buscar(const T& element) const {
        Nodo<T>* current = head;
        int pos = 1;
        while (current) {
            if (current->getInfo() == element) {
                return pos;
            }
            current = current->getNext();
            ++pos;
        }
        return -1;
    }

    void invertir() {
        Nodo<T>* prev = nullptr;
        Nodo<T>* current = head;
        tail = head;

        while (current) {
            Nodo<T>* nextNode = current->getNext();
            current->setNext(prev);
            prev = current;
            current = nextNode;
        }

        head = prev;
    }

    Lista<T> copiar() const {
        return Lista<T>(*this);
    }

    void vaciar() {
        Nodo<T>* current = head;
        while (current) {
            Nodo<T>* nextNode = current->getNext();
            delete current;
            current = nextNode;
        }
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    void intercambiar(int pos1, int pos2) {
        if (pos1 < 1 || pos1 > length || pos2 < 1 || pos2 > length) {
            throw std::out_of_range("Posicion invalida en intercambiar");
        }
        if (pos1 == pos2) {
            return;
        }

        T a = consultar(pos1);
        T b = consultar(pos2);
        modificar(pos1, b);
        modificar(pos2, a);
    }

    Lista<T> concatenar(const Lista<T>& target) const {
        Lista<T> result(*this);
        Nodo<T>* current = target.head;
        while (current) {
            result.insertar(current->getInfo(), result.getLong() + 1);
            current = current->getNext();
        }
        return result;
    }

    void destruir() {
        vaciar();
    }

    void modificar(int pos, const T& element) {
        if (pos < 1 || pos > length) {
            throw std::out_of_range("Posicion invalida en modificar");
        }

        if (pos == 1) {
            head->setInfo(element);
            return;
        }

        if (pos == length) {
            tail->setInfo(element);
            return;
        }

        Nodo<T>* current = head;
        for (int i = 1; i < pos; ++i) {
            current = current->getNext();
        }
        current->setInfo(element);
    }

    void print(std::ostream& os = std::cout) const {
        os << "[";
        Nodo<T>* current = head;
        while (current) {
            os << current->getInfo();
            current = current->getNext();
            if (current) {
                os << ", ";
            }
        }
        os << "]";
    }

    std::vector<T> toVector() const {
        std::vector<T> values;
        values.reserve(length);
        Nodo<T>* current = head;
        while (current) {
            values.push_back(current->getInfo());
            current = current->getNext();
        }
        return values;
    }

    static Lista<T> fromVector(const std::vector<T>& values) {
        Lista<T> result;
        for (const auto& value : values) {
            result.insertar(value, result.getLong() + 1);
        }
        return result;
    }

    void reorderOddAndEven() {
        if (!head || !head->getNext()) {
            return;
        }

        Nodo<T>* odd = head;
        Nodo<T>* even = head->getNext();
        Nodo<T>* firstEven = even;

        while (even && odd) {
            odd->setNext(even->getNext());
            odd = odd->getNext();

            if (odd) {
                even->setNext(odd->getNext());
                even = even->getNext();
            }
        }

        if (odd) {
            odd->setNext(firstEven);
        }

        if (even) {
            tail = even;
        } else {
            Nodo<T>* current = head;
            while (current->getNext()) {
                current = current->getNext();
            }
            tail = current;
        }
    }

    void rightShift(int shift) {
        if (length <= 1) {
            return;
        }

        int trueShift = shift % length;
        if (trueShift == 0) {
            return;
        }

        tail->setNext(head);
        int splitPos = length - trueShift;
        Nodo<T>* newTail = head;
        for (int i = 1; i < splitPos; ++i) {
            newTail = newTail->getNext();
        }

        head = newTail->getNext();
        newTail->setNext(nullptr);
        tail = newTail;
    }

    Lista<T> partialReorderOddEvenSorted() const {
        Lista<T> result;
        if (!head) {
            return result;
        }

        Nodo<T>* odd = head;
        Nodo<T>* even = head->getNext();

        while (odd && even) {
            if (odd->getInfo() <= even->getInfo()) {
                result.insertar(odd->getInfo(), result.getLong() + 1);
                odd = odd->getNext();
                if (odd) odd = odd->getNext();
            } else {
                result.insertar(even->getInfo(), result.getLong() + 1);
                even = even->getNext();
                if (even) even = even->getNext();
            }
        }

        while (odd) {
            result.insertar(odd->getInfo(), result.getLong() + 1);
            odd = odd->getNext();
            if (odd) odd = odd->getNext();
        }

        while (even) {
            result.insertar(even->getInfo(), result.getLong() + 1);
            even = even->getNext();
            if (even) even = even->getNext();
        }

        return result;
    }

    Lista<T> partialReorderHalvesSorted() const {
        Lista<T> result;
        if (!head) {
            return result;
        }

        int half = length / 2;
        Nodo<T>* p1 = head;
        Nodo<T>* p2 = head;
        for (int i = 0; i < half; ++i) {
            p2 = p2->getNext();
        }

        while (p1 != p2 && p2) {
            if (p1->getInfo() <= p2->getInfo()) {
                result.insertar(p1->getInfo(), result.getLong() + 1);
                p1 = p1->getNext();
            } else {
                result.insertar(p2->getInfo(), result.getLong() + 1);
                p2 = p2->getNext();
            }
        }

        while (p1 != p2) {
            result.insertar(p1->getInfo(), result.getLong() + 1);
            p1 = p1->getNext();
        }

        while (p2) {
            result.insertar(p2->getInfo(), result.getLong() + 1);
            p2 = p2->getNext();
        }

        return result;
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Lista<T>& list) {
    list.print(os);
    return os;
}

#endif
