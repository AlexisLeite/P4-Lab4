#ifndef CVENTA_H
#define CVENTA_H

#include "IVenta.h"
#include <string>
#include <set>
#include <map>

#include "CUsuario.h"
#include "datatypes.h"

using namespace std;

class ControladorVenta : public IVenta
{
private:
  static ControladorVenta *instancia;
  ControladorVenta();
  map<int, Compra *> compras;
  set<Promocion> conjunto2;
  map<int, Producto *> productos;
  map<string, Promocion *> promociones;
  Usuario *memUsuario;
  Promocion *memPromocion;
  Compra *memCompra;
  int contador;
  int contadorCompra;

public:
  static ControladorVenta *getInstanciaVen();
  void setContador();
  void setContadorCompra();
  int getContadorCompra();
  int getContador();
  void avanzarContador();
  void avanzarContadorCompra();

  Usuario *getMemUsuario();
  void setMemUsuario(string nickname);
  Promocion *getMemPromocion();
  void setMemPromocion(Promocion *prom);
  Compra *getMemCompra();
  void setMemCompra(Compra *compra);
  map<int, Compra *> getCompra();

  set<DTPromocion> listadoPromociones();
  // Operaciones externas
  void crearProducto(string nicknameV, string nombreP, string descripcionP, float precioP, int cantStockP, categoria cat);
  bool existeProducto(int id);

  void crearPromocion(string nombre, string descripcion, float descuento, DTFecha fechaVencimiento);
  void seleccionarProductoAProm(int prodId, int cantMinima);

  Producto *seleccionarProductoPorId(int productosid);
  set<DTProducto> listadoProductosNoEnPromo();
  bool productoEnPromo(int id);
  DTUsuario *infoPromocionVendedor(string nombre);
  set<DTProducto> infoPromocionProductos(string nombre);
  int cantidadMinimaPromo(string nombre, int id);
  DTProducto dataDeProducto(Producto *prod);
  set<DTProducto> getDatosProductosVendedor(string nicknameV);
  set<DTPromocion> getDatosPromocionVigentesVendedor(string nicknameV);
  set<DTCompra> getDatosCompraRealizadaCliente(string nicknameC);
  string nombreVendedor(int idProducto);
  void confirmarCrearPromocion(string nicknameV);

  void crearCompra(string nickname, DTFecha fechaActual);
  set<DTProducto> listadoProductos();
  void agregarACompra(int id, int cantidad);
  bool cantidadValida(int id, int cantidad);
  bool productoEnCompra(int id);
  DTCompra detallesCompra();

  set<string> obtenerProdsPendEnvio(string nombreVendedor);
  set<DTCompra2> clientesConEnvioPend(string nombreProducto);

  void enviarProducto(int idProducto, string nombreCliente);

  //  void confirmarCompra();
  // Operaciones internas (no se si el {} va o no)
  virtual ~ControladorVenta(){};
};

#endif
