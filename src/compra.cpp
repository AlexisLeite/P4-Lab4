#include "../include/producto.h"
#include <string>

using namespace std;

Compra(DTFecha fechaCompra, float montoTotal, set<Compra_Producto> com_Prods, integer id){
: fecha(fechaCompra), montoTotal(montototal), com_Prods(com_Prods), id(id){};

};


void Compra::agregarACompra(Producto prod, integer cantidad)
{
    Compra_Producto nuevoCP = new Compra_Producto(cantidad, false);
    nuevoCP.agregarACompra(prod);
    this->com_Prod;
};

bool Compra::productoEnCompra(integer id_prod)
{
    bool enCompra = false;
    for (Compra_Producto cp : this->com_Prods)
    {
        setProductos = cp.getProductos();
        enCompra = setProductos.count(id_prod) || enCompra;
    }
    return enCompra;
};


/*void Compra::setId(integer id)
{
    this->id = id;
};
*/

integer Compra::getId()
{
    return this->id;
};



DTFecha Compra::getFecha()
{
    return this->fecha;
};

float Compra::getMontoTotal()
{
    return this->montoTotal;
};

set<Compra_Producto> Compra::getCompProd()
{
    return this->com_Prods;
};

integer Compra::getId()
{
    return this->id;
};

DTCompra Compra::infoCompra()
{
    //arreglar diagrama comunicacion crear compra!
}