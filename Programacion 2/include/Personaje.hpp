#ifndef PERSONAJE_HPP
#define PERSONAJE_HPP

#include <string>

using namespace std;

/**
 * @brief Modelo simple para los ejercicios de arboles con dragones y princesas.
 */
class Personaje {
private:
    string nombre;
    bool dragon;
    bool princesa;

public:
    /**
     * @brief Construye un personaje.
     * @param pNombre Nombre del personaje.
     * @param esDragon true si es dragon.
     * @param esPrincesa true si es princesa.
     */
    Personaje(const string& pNombre = "", bool esDragon = false, bool esPrincesa = false)
        : nombre(pNombre), dragon(esDragon), princesa(esPrincesa) {}

    /**
     * @brief Retorna el nombre del personaje.
     * @return Nombre.
     */
    string getNombre() const { return nombre; }

    /**
     * @brief Indica si el personaje es dragon.
     * @return true si es dragon.
     */
    bool esDragon() const { return dragon; }

    /**
     * @brief Indica si el personaje es princesa.
     * @return true si es princesa.
     */
    bool esPrincesa() const { return princesa; }

    /**
     * @brief Operador de igualdad por nombre y tipo.
     * @param other Personaje a comparar.
     * @return true si son iguales.
     */
    bool operator==(const Personaje& other) const {
        return nombre == other.nombre && dragon == other.dragon && princesa == other.princesa;
    }
};

#endif
