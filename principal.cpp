#include <ios>
#include <limits>
#include <string>
#include <set>
// #include <map>
#include <iostream>

//#include "include/CUsuario.h"
#include "include/IVenta.h"
#include "include/cliente.h"
#include "include/comentario.h"
#include "include/datatypes.h"
#include "include/fabrica.h"
#include "include/IUsuario.h"
#include "include/producto.h"
#include "include/producto_promocion.h"
#include "include/usuario.h"
#include "include/vendedor.h"
// #include "include/observer.h"
// #include "include/promocion.h"
// #include "include/compra_producto.h"
// #include "include/compra.h"

using namespace std;

void altaDeUsuario(IUsuario *controlador)
{
    string nickname, contrasena;
    int dia, mes, anio;
    cout << "Ingrese nickname:";
    cin >> nickname;
    cout << "\nIngrese contrasena: ";
    cin >> contrasena;
    while (contrasena.length() < 6 || contrasena.find(' ') != string::npos) {
        if (contrasena.find(' ') != string::npos) {
            cout << "La contraseña no puede contener espacios. Intente de nuevo.\n";
        } else {
            cout << "La contraseña debe tener al menos 6 caracteres. Intente de nuevo.\n";
        }
        
        cout << "\nIngrese contraseña: ";
        cin >> contrasena;
    }
    cout << "\nIngrese dia: ";
    cin >> dia;
    cout << "\nIngrese mes: ";
    cin >> mes;
    cout << "\nIngrese anio: ";
    cin >> anio;
    DTFecha fecha(dia, mes, anio);
    controlador->ingresarUsuario(nickname, contrasena, fecha);
    if (controlador->existeUsuarioIgualNickname(nickname))
    {
        cout << "\nNickname ya existe, intente nuevamente. ";
        controlador->terminarAlta();
        altaDeUsuario(controlador);
        return;
    }
    cout << "\nIngrese 1 si va a ingresar un cliente o 2 si va a ingresar un vendedor: ";
    int opcion;
    cin >> opcion;
    switch (opcion)
    {
    case 1:
    {
        cout << "\nIngrese ciudad: ";
        string ciudad;
        cin >> ciudad;
        cout << "\nIngrese direccion: ";
        string direccion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, direccion);
        controlador->altaCliente(direccion, ciudad);
    }
    break;

    case 2:
    {
        cout << "\nIngrese codigoRUT (debe tener exactamente 12 caracteres): ";
        string codigoRUT;
        cin >> codigoRUT;
        while (codigoRUT.length() != 12) 
        {
            cout << "El codigoRUT debe tener exactamente 12 caracteres. Intente de nuevo.\n";
            cout << "\nIngrese codigoRUT (debe tener exactamente 12 caracteres): ";
            cin >> codigoRUT;
        }
        controlador->altaVendedor(codigoRUT);
    }
    break;
    }
    controlador->confirmarAltaUsuario();
    return;
}

void listadoDeUsuarios(IUsuario *controlador)
{  
    map<string, Vendedor*> vendedores;
    map<string, Cliente*> clientes;
    set<DTUsuario> dataUsuarios;
    map<string, Usuario*> usuarios = controlador->listadoUsuarios();
    for(map<string, Usuario*>::iterator it = usuarios.begin(); it != usuarios.end(); ++it)
    {
        Vendedor* vendedor = dynamic_cast<Vendedor*>(it->second);
        if (vendedor != NULL)
        {
            vendedores[vendedor->getNickname()] = vendedor;
        }
        else 
        {
        Cliente* cliente = dynamic_cast<Cliente*>(it->second);
        clientes[cliente->getNickname()] = cliente;
        }
    }
    for(map<string, Vendedor*>::iterator it = vendedores.begin(); it != vendedores.end(); ++it)
    {
        cout << "Nickname: " << it->second->getNickname() << ", Fecha nacimiento: " << it->second->getFechaNac().getDia() << "/" << it->second->getFechaNac().getMes() << "/" << it->second->getFechaNac().getAnio() << ", Codigo RUT: " << it->second->getCodigoRUT() << "\n";

    }

    for(map<string, Cliente*>::iterator iter = clientes.begin(); iter != clientes.end(); ++iter)
    {
          cout << "Nickname: "<< iter->second->getNickname() << ", Fecha nacimiento: " << iter->second->getFechaNac().getDia() << "/" << iter->second->getFechaNac().getMes() << "/" << iter->second->getFechaNac().getAnio() << ", Dirección: "<< iter->second->getDireccion() << ", Ciudad: " << iter->second->getCiudad() << "\n";
    }
    
    cout << "Ingrese enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void altaDeProducto(IUsuario *controladorU, IVenta *controladorV)
{
    set<DTUsuario> dataVendedores;
    map<string, Usuario*> usuarios = controladorU->listadoUsuarios();
    // for(map<string, Usuario*>::iterator it = usuarios.begin(); it != usuarios.end(); ++it)
    // {
    //     dataVendedores.insert(it->second->getDatosUsuario());
    // }
    for(map<string, Usuario*>::iterator it = usuarios.begin(); it != usuarios.end(); ++it)
    {
        Vendedor* vendedor = dynamic_cast<Vendedor*>(it->second);
        if (vendedor) 
        {
            dataVendedores.insert(vendedor->getDatosUsuario());
        }
    }    
    for (DTUsuario vendedor : dataVendedores)
    {
        cout << vendedor.getNickname() << "\n";
    }
    string nicknameV, nombreP, descripcionP;
    float precioP;
    int cantStockP, opcion;
    categoria cat;
    cout << "Elija un vendedor: ";
    cin >> nicknameV;
    // Agregar precondición de que el vendedor sea correcto
    while (! controladorU->existeUsuarioIgualNickname(nicknameV)) 
        {
        cout << "El vendedor ingresado no existe. Vuelva a intentar.\n";
        cin >> nicknameV;
        }

    cout << "\n"
         << "Ingrese nombre del producto: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, nombreP);
    cout << "\n"
         << "Ingrese descripcion del producto: ";
    getline(cin, descripcionP);
    cout << "\n"
         << "Ingrese precio del producto: ";
    cin >> precioP;
    cout << "\n"
         << "Ingrese cantidad en stock: ";
    cin >> cantStockP;
    cout << "\n"
         << "Ingrese 1 si es electrodomestico, 2 si es ropa, 3 si es otro: ";
    cin >> opcion;
    switch (opcion)
    {
    case 1:
        cat = electrodomesticos;
        break;
    case 2:
        cat = ropa;
        break;
    case 3:
        cat = otro;
        break;
    }
    Usuario *usuario = controladorU->obtenerUsuarioPorNickname(nicknameV);
    Vendedor *vendedor = dynamic_cast<Vendedor *>(usuario);
    if (vendedor != NULL)
    {
        controladorV->crearProducto(vendedor, nombreP, descripcionP, precioP, cantStockP, cat);
    }
}

void consultarProducto(IUsuario * controladorU, IVenta *controladorV) // agregar precondicion de no hay producto
{

    int idProducto;
    set<DTProducto> dataProductos;
    dataProductos = controladorV->listadoProductos();
    for (DTProducto producto : dataProductos)
    {
        cout << "Id: " << producto.getId() << "\n";
        
        cout << "Nombre: " << producto.getNombre() << "\n";
    }

    cout << "Seleccione un Producto con su id: ";
    cin >> idProducto;
    cout << "\n";
    Producto *productoConsultado = controladorV->seleccionarProductoPorId(idProducto);
    DTProducto dataP = productoConsultado->getDataProducto();

    cout << "Nombre : " << dataP.getNombre() << "\n";
    cout << "Id: " << dataP.getId() << "\n";
    cout << "Precio: " << dataP.getPrecio() << "\n";
    cout << "Cantidad en stock: " << dataP.getCantStock() << "\n";
    
    
    cout << "Descripcion: " << dataP.getDesc() << "\n";
    string cat;
    switch (dataP.getCat()) 
    {   case ropa: 
        {
            cat = "ropa";
            break;
        }
        case electrodomesticos:
        {
            cat = "electrodomestico";
            break;
        }
        case otro:
        {         
            cat = "otro";
            break;
        }
    }
    cout << "Categoria: " << cat << "\n";
    
    map<string, Usuario*> vendedores;
    vendedores = controladorU->listadoUsuarios("vendedor");
    string nicknameV;
    for(map<string, Usuario*>::iterator it = vendedores.begin(); it != vendedores.end(); ++it)
    {
        Vendedor *vendedor = dynamic_cast<Vendedor *>(it->second);
        if (vendedor->getProductos().find(idProducto) != vendedor->getProductos().end())
        {
            nicknameV = vendedor->getNickname();
            break;
        }
    }
    cout << "Nickname del vendedor: " << nicknameV << endl;
    cout << "Ingrese enter para continuar...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}



void crearPromocion(IUsuario * controladorU, IVenta * controladorV)
{
    string nombreProm, descripcionProm;
    float descuento;
    int dia, mes, anio;
    cout << "Ingrese nombre de la promocion: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, nombreProm);    
    cout << "\n"  << "Ingrese descripcion: ";
    getline(cin, descripcionProm);
    cout << "\n" << "Ingrese descuento: ";
    cin >> descuento;
    cout << "\nIngrese fecha de vencimiento. " ;
    cout << "\n Dia: ";
    cin >> dia;
    cout << ". Mes: ";
    cin >> mes;
    cout << ". Anio: ";
    cin >> anio;
    cout << "\n";

    DTFecha fechaVen = DTFecha(dia, mes, anio);
    string nicknameV;
    cout << "Listado de vendedores: \n";
    map<string, Usuario*> vendedores = controladorU->listadoUsuarios("vendedor");
    map<string, Usuario*>::iterator it;
    for (it = vendedores.begin(); it != vendedores.end(); it++)
    {
        cout << it->second->getNickname() << "\n";
    }
    cout << "Seleccione un vendedor: ";
    cin >> nicknameV;
    Usuario * usuario = controladorU->obtenerUsuarioPorNickname(nicknameV);
    Vendedor *vendedor = dynamic_cast<Vendedor *>(usuario);
    controladorV->setMemUsuario(usuario);


    controladorV->crearPromocion(nombreProm, descripcionProm, descuento, fechaVen);
    

    map<int, Producto*> dataProductos = vendedor->getProductos();
    cout << "Listado de productos: \n";
    for (map<int,Producto *>::iterator it = dataProductos.begin(); it != dataProductos.end(); it++)
    {   
        if (!it->second->estaEnPromo())
        {
            cout << "Id: " << it->second->getId();
            cout << ", Nombre: " << it->second->getNombre() << "\n";
        }
    }

    int id, cantMinima;
    bool flag = true;
    cout << "Ingrese los productos que van a componer la promo (ingrese -1 para dejar de agregar). ";
    string SoN;
    while (flag)
    {   
        cout << "ID: ";
        cin >> id;
        cout << "Cantidad Minima: ";
        cin >> cantMinima;
        controladorV->seleccionarProductoAProm(id , cantMinima);
        cout << "Quiere continuar?  si o no: ";
        cin >> SoN;
        if (SoN == "no")
        {
            break;
        }    
    }
}

void consultarPromocion(IVenta * controladorV)
{
    //Imprime todas las Promociones vigentes en el sistema  (HABRIA Q PREGUNTAR PRECOND PARA IMPRIMIR: FECHA VENC < FECHA SISTEMA)
    string opcion;
    cout << "este";
    map<string, Promocion *> dataPromos = controladorV->listadoPromociones();
    cout << "este otro";
    map<string, Promocion *>::iterator it;
    for (it = dataPromos.begin(); it != dataPromos.end(); it++)
    {
        cout << "Nombre: " << it->second->getNombre() << "\n";
        cout << "Descripcion: " << it->second->getDescripcion() << "\n";
        cout << "Descuento: " << it->second->getDescuento() << "\n";
        cout << "Valido hasta: " << it->second->getFechaVen().getDia() << "/" << it->second->getFechaVen().getMes() << "/" << it->second->getFechaVen().getAnio() << "\n";
    }
    cout << "Si desea ver los productos dentro de una promoción ingrese el nombre de esta. De lo contrario, escriba Salir: ";
    cin >> opcion;
    //aca faltaria ver precond q opcion sea un nombre valido
    if (opcion != "Salir")
    {
        //Imprime informacion del vendedor de la Promocion
        Promocion *prom =  dataPromos.find(opcion)->second;
        Vendedor * vendedor = prom->getVendedor();
        cout << "Vendedor: " << vendedor->getNickname() << "\n";
        cout << "Codigo RUT: " << vendedor->getCodigoRUT() << "\n";
        cout << "Fecha de nacimiento: " << vendedor->getFechaNac().getDia() << "/" << vendedor->getFechaNac().getMes() << "/" << vendedor->getFechaNac().getAnio()  << "\n";
       
        //Imprime informacion de todos los productos de la Promocion
        set<Producto_Promocion*> prodproms = prom->getProdProms();
        set<Producto_Promocion*>::iterator it;
        string cat;
        for (it = prodproms.begin(); it != prodproms.end(); it++)
        {
            Producto* prod = (*it)->getProducto();
            cout << "Id: " << prod->getId() << "\n";
            cout << "Nombre: " << prod->getNombre() << "\n";
            cout << "Categoria: " << prod->getCat() << "\n";
            switch (prod->getCat()) 
            {   case ropa: 
                {
                    cat = "ropa";
                    break;
                }
                case electrodomesticos:
                {
                    cat = "electrodomestico";
                    break;
                }
                case otro:
                {         
                    cat = "otro";
                    break;
                }
            }
            cout << "Categoria: " << cat << "\n";
            cout << "Descripcion: " << prod->getDesc() << "\n";
            cout << "Cantidad en stock: " << prod->getCantStock() << "\n";
            cout << "Cantidad minima para aplicar promoción: " << (*it)->getCantidadMinima() << "\n";
            cout << "Precio: " << prod->getPrecio() << "\n";
        }
    }
}

void dejarComentario(IUsuario *controladorU, IVenta *controladorV)
{
    // lista usuarios y selecciona uno
    string nicknameU, textoC;
    int idP;
    map<string, Usuario*> dataUsuarios = controladorU->listadoUsuarios();
    map<string, Usuario*>::iterator it;
    for (it = dataUsuarios.begin(); it != dataUsuarios.end(); it++)
    {
        cout << it->second->getNickname() << "\n";
    }
    cout << "Seleccione un Usuario: ";
    cin >> nicknameU;
    Usuario * usuario = controladorU->obtenerUsuarioPorNickname(nicknameU);
    // lista productos y selecciona uno
    set<DTProducto> dataProductos;
    dataProductos = controladorV->listadoProductos();

    for (DTProducto producto : dataProductos)
    {
        cout << "Id: " << producto.getId() << "\n";
        cout << "Nombre: " << producto.getNombre() << "\n";
        cout << "Categoria: " << producto.getCat() << "\n";
        cout << "Descripcion: " << producto.getDesc() << "\n";
        cout << "Cantidad en stock: " << producto.getCantStock() << "\n";
        cout << "Precio: " << producto.getPrecio() << "\n";
    }
    cout << "Seleccione un Producto con su id: ";
    cin >> idP;

    cout << "\nIngrese 1 si desea realizar un comentario nuevo o 2 si desea responder a un comentario existente: ";
    int opcion;
    cin >> opcion;
    switch (opcion)
    {
    case 1:
    {
        cout << "Ingrese el texto del comentario: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, textoC);
        Producto *seleccionado = controladorV->seleccionarProductoPorId(idP);
        controladorU->crearComentario(textoC, seleccionado, usuario);
    }
    break;

    case 2:
    {
        int idComen;
        Producto *seleccionado = controladorV->seleccionarProductoPorId(idP);
        map<int, Comentario *>::iterator it;
        map<int, Comentario *> mapa = seleccionado->listadoComentarios();
        //lista todos los comentarios asociados al producto seleccionado
        for (it = mapa.begin(); it != mapa.end(); ++it)
        {
            cout << "Id comentario: " << it->second->getId() << "\n";
            cout << "Comentario: " << it->second->getText() << "\n";
        }
        cout << "Seleccione un Comentario con su id: ";
        cin >> idComen;
        cout << "\n";
        cout << "Ingrese el texto de la respuesta al comentario: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, textoC);
        Comentario * comentarioOriginal = mapa.find(idComen)->second;
        controladorU->crearRespuesta(textoC, comentarioOriginal);
    }
    break;
    }
}

void eliminarComentario(IUsuario *controladorU)
{
    map<string, Usuario*> dataUsuarios = controladorU->listadoUsuarios();
    map<string, Usuario*>::iterator it;
    for (it = dataUsuarios.begin(); it != dataUsuarios.end(); it++)
    {
        cout << it->second->getNickname() << "\n";
    }
    string usuarioSeleccionado;
    cout << "Ingrese el nickname del usuario que desee borrar un comentario: \n";
    cin >> usuarioSeleccionado;

    Usuario *usuario = controladorU->obtenerUsuarioPorNickname(usuarioSeleccionado);
    controladorU->recordarUsuario(usuario);
    map<int, Comentario *> comentarios;
    comentarios = usuario->getComentarios();
    cout << "Listado de Comentarios de " << usuarioSeleccionado << "\n";
    if (comentarios.empty())
        cout << "tavacio";
    for (map<int, Comentario *>::const_iterator it = comentarios.begin(); it != comentarios.end(); ++it)
    {
        cout << "ID: " << it->second->getId() << ", ";
        cout << "Contenido: " << it->second->getText() << " \n";
        cout << "Fecha: " << it->second->getFecha().getDia() << "/" << it->second->getFecha().getMes() << "/" << it->second->getFecha().getAnio() << "\n";
    }
    cout << "Ingrese ID del comentario a eliminar: ";
    int id;
    cin >> id;
    cout << "\n";
    controladorU->eliminarComentario(id);
    cout << "Comentario " << id << "eliminado. ";
}

//void expedienteDeUsuario(IUsuario *controlador)
//{
//    string nicknameU;
//
//    cout << "Usuarios registrados:\n";
//    set<DTUsuario> dataUsuarios;
//    dataUsuarios = controlador->listadoUsuarios();
//    for (DTUsuario usuario : dataUsuarios)
//    {
//        cout << usuario.getNickname() << "\n";
//    }
//
//    cout << "Seleccione un usuario: ";
//    cin >> nicknameU;
//    cout << "\n";
//    Usuario *usuario;
//    usuario = controlador->obtenerUsuarioPorNickname(nicknameU);
//    DTUsuario dataUsuario;
//    dataUsuario = usuario->getDatosUsuario();
//    cout << "Datos del usuario seleccionado:\n"
//         << dataUsuario << endl;
//
//    Vendedor *vendedor = dynamic_cast<Vendedor *>(usuario);
//    if (vendedor != NULL)
//    {
//        // Usuario es vendedor
//        // lista todos los productos del vendedor
//        map<int, Producto *> productos = vendedor->getProductos();
//        cout << "Productos del vendedor " << vendedor->getNickname() << ": \n"
//             << endl;
//        for (map<int, Producto *>::const_iterator it = productos.begin(); it != productos.end(); ++it)
//        {
//            Producto *producto = it->second;
//            cout << producto->getDataProducto() << endl;
//        }
//
//        // Lista todos las promociones activas
//        set<Promocion> promociones = vendedor->getPromociones();
//        cout << "\nPromociones del vendedor " << vendedor->getNickname() << ": \n"
//             << endl;
//        for (set<Promocion>::const_iterator it = promociones.begin(); it != promociones.end(); ++it)
//        {
//            Promocion promocion = *it;
//            cout << promocion.getNombre() << endl; // Muestro el nombre de la promo
//        }
//    }
//    else
//    {
//        // El usuario es cliente
//        Cliente *cliente = dynamic_cast<Cliente *>(usuario);
//        set<Compra> compras = cliente->getCompras();
//        cout << "\nCompras del cliente " << cliente->getNickname() << ": \n"
//             << endl;
//        for (set<Compra>::const_iterator it = compras.begin(); it != compras.end(); ++it)
//        {
//            Compra pcompra = *it;
//            cout << "Id de la compra:" << endl;
//            cout << pcompra.getId() << endl; // Muestro el nombre de la promo
//            for (const Producto& producto : pcompra.getCompProd(). ()) {
//                cout << "Nombre del producto: " << producto.getNombre() << endl;
//            }
//        }
//
//    }
//}
//
//void altaDeUsuarioCARGARDATOSPREESTABLECIDOS(IUsuario *controlador, string nickname, string constrasena, int dia, int mes, int anio, int opcion, string ciudad, string direccion, string codigoRUT)
//{ //Pasar opcion = 1 si es cliente y 2 si es vendedor. 
//    DTFecha fecha(dia, mes, anio);
//    controlador->ingresarUsuario(nickname, contrasena, fecha);
//    if (controlador->existeUsuarioIgualNickname(nickname))
//    {
//        cout << "\nYa existe usuario con nickname:" << nickname;
//        controlador->terminarAlta();
//        return;
//    }
//    switch (opcion)
//    {
//    case 1:
//    {
//        controlador->altaCliente(direccion, ciudad);
//    }
//    break;
//    case 2:
//    {
//        if (codigoRUT.length() != 12) {
//        {
//            cout << "El codigoRUT debe tener exactamente 12 caracteres.\n";
//        }
//        controlador->altaVendedor(codigoRUT);
//    }
//    break;
//    }
//    controlador->confirmarAltaUsuario();
//    return;
//}
//void altaDeProductoCARGARDATOSPREESTABLECIDOS(IUsuario *controladorU, IVenta *controladorV, string nicknameV, string nombreP, string descripcion, float precio int cantStockP, int opcion)
//{
//   set<DTUsuario> dataVendedores;
//    map<string, Usuario*> usuarios = controladorU->listadoUsuarios();
//
//   for(map<string, Usuario*>::iterator it = usuarios.begin(); it != usuarios.end(); ++it)
//    {
//        Vendedor* vendedor = dynamic_cast<Vendedor*>(it->second);
//       if (vendedor) 
//        {
//            dataVendedores.insert(vendedor->getDatosUsuario());
//        }
//    }    
//   for (DTUsuario vendedor : dataVendedores)
//    {
//       cout << vendedor.getNickname() << "\n";
//   }
//    string nicknameV, nombreP, descripcionP;
//   float precioP;
//    int cantStockP, opcion;
//    categoria cat;
//    cout << "Elija un vendedor: ";
//   cin >> nicknameV;
//  
//  cout << "\n"
//        << "Ingrese nombre del producto: ";
//   cin.ignore(numeric_limits<streamsize>::max(), '\n');
//  getline(cin, nombreP);
//   cout << "\n"
//       << "Ingrese descripcion del producto: ";
//    getline(cin, descripcionP);
//    cout << "\n"
//         << "Ingrese precio del producto: ";
//    cin >> precioP;
//    cout << "\n"
//         << "Ingrese cantidad en stock: ";
//   cin >> cantStockP;
//    cout << "\n"
//         << "Ingrese 1 si es electrodomestico, 2 si es ropa, 3 si es otro: ";
//    cin >> opcion;
//   switch (opcion)
//   {
//  case 1:
//     cat = electrodomesticos;
//        break;
//    case 2:
//        cat = ropa;
//        break;
//    case 3:
//        cat = otro;
//       break;
//   }
//    Usuario *usuario = controladorU->obtenerUsuarioPorNickname(nicknameV);
//    Vendedor *vendedor = dynamic_cast<Vendedor *>(usuario);
//    if (vendedor != NULL)
//    {
//        controladorV->crearProducto(vendedor, nombreP, descripcionP, precioP, cantStockP, cat);
//    }
//}
//
//void cargarDatosPreestablecidos(){
//    //altaDeUsuarioCARGARDATOSPREESTABLECIDOS le paso el controlador, nombre, fecha, opcion = 1 si es cliente y 2 si es vendedor
//    // si es cliente le paso ciudad y direecion y en codigo rut le paso x, si es vendedor le paso codigoRUT y en ciudad, y direccion le pongo x.
//    altaDeUsuarioCARGARDATOSPREESTABLECIDOS(controladorU,ana23,qwer1234,15,05,1988,2,x,x,212345678001);
//    altaDeUsuarioCARGARDATOSPREESTABLECIDOS(controladorU,carlos78,asdfghj,18,06,1986,2,x,x,356789012345);
//    altaDeUsuarioCARGARDATOSPREESTABLECIDOS(controladorU,diegom,zxcvbn,28,07,1993,2,x,x,190123456789);
//    altaDeUsuarioCARGARDATOSPREESTABLECIDOS(controladorU,juan87,1qaz2wsx,20,10,1992,1,Melo,Av. 18 de Julio 456,x);
//    altaDeUsuarioCARGARDATOSPREESTABLECIDOS(controladorU,laura,3edc4rfv,22,09,1979,1,Montevideo,Rondeau 1617,x);
//    altaDeUsuarioCARGARDATOSPREESTABLECIDOS(controladorU,maria01,5tgb6yhn,2,03,1985,2,x,x,321098765432);
//    altaDeUsuarioCARGARDATOSPREESTABLECIDOS(controladorU,natalia,poiuyt,14,04,1982,1,Salto,Paysandu 2021, x);
//    altaDeUsuarioCARGARDATOSPREESTABLECIDOS(controladorU,pablo10,lkjhgv,30,11,1995,1,Mercedes,Av. Rivera 1819,x);
//    altaDeUsuarioCARGARDATOSPREESTABLECIDOS(controladorU,roberto,mnbvcx,12,08,1990,1,Montevideo,Av. Brasil 1011,x);
//    altaDeUsuarioCARGARDATOSPREESTABLECIDOS(controladorU,sofia25,1234asdf,07,12,1983,2,x,x,445678901234);
//    
//  
//
//}

int main()
{

    Fabrica *fabrica = Fabrica::getInstanceF();      // se crea instancia única de fábrica
    IUsuario *controladorU = fabrica->getIUsuario(); // se crea la instancia del controlador CUsuario de tipo IUsuario
    IVenta *controladorV = fabrica->getIVenta();
    controladorV->setContador();
    controladorU->setContadorComentario();

    int opcion;
    bool continuar = true;
    while (continuar)
    {
        cout << "---Presione un numero para elegir un caso de uso: " << endl;
        cout << "1: Alta de usuario" << endl
             << "2: Listado de usuarios" << endl
             << "3: Alta de producto" << endl
             << "4: Consultar producto" << endl
             << "5: Crear promocion" << endl
             << "6: Consultar promocion" << endl
             << "7: Realizar compra" << endl
             << "8: Dejar comentario" << endl
             << "9: Eliminar comentario" << endl
             << "10: Enviar producto" << endl
             << "11: Expediente de Usuario" << endl
             << "12: Suscribirse a notificaciones" << endl
             << "13: Consulta de notificaciones" << endl
             << "14: Eliminar suscripciones" << endl
             << "15: Cargar datos preestablecidos" << endl
             << "16: Terminar programa" << endl;
        cout << "Ingrese el numero correspondiente al caso de uso a ejecutar: ";
        cin >> opcion;
        switch (opcion)
        {
        case 1:
            cout << "Ejecutando caso de uso: Alta de usuario" << endl;
            altaDeUsuario(controladorU);
            break;

        case 2:
            cout << "Ejecutando caso de uso: Listado de usuarios" << endl;
            listadoDeUsuarios(controladorU);
            break;

        case 3:
            cout << "Ejecutando caso de uso: Alta de producto" << endl;
            altaDeProducto(controladorU,  controladorV);
            break;

        case 4:
            cout << "Ejecutando caso de uso: Consultar producto" << endl;
            consultarProducto(controladorU, controladorV);
            break;

        case 5:
            cout << "Ejecutando caso de uso: Crear promocion" << endl;
            crearPromocion(controladorU, controladorV);
            break;

        case 6:
            cout << "Ejecutando caso de uso: Consultar promocion" << endl;
            consultarPromocion(controladorV);
            break;

        case 7:
            cout << "Ejecutando caso de uso: Realizar compra" << endl;
            break;

        case 8:
            cout << "Ejecutando caso de uso: Dejar comentario" << endl;
            dejarComentario(controladorU, controladorV);
            break;

        case 9:
            cout << "Ejecutando caso de uso: Eliminar Comentario" << endl;
            eliminarComentario(controladorU);
            break;

        case 10:
            cout << "Ejecutando caso de uso: Enviar Producto" << endl;
            break;

        case 11:
            cout << "Ejecutando caso de uso: Expediente de Usuario" << endl;
            //expedienteDeUsuario(controladorU);
            break;

        case 12:
            cout << "Ejecutando caso de uso: Suscribirse a notificaciones" << endl;
            break;

        case 13:
            cout << "Ejecutando caso de uso: Consulta de notificaciones" << endl;
            break;

        case 14:
            cout << "Ejecutando caso de uso: Eliminar suscripciones" << endl;
            break;

        case 15:
            cout << "hay q hacerlo xd...\n";
            break;

        case 16:
            cout << "Terminando programa...\n";
            continuar = false;
            break;

        default:
            cout << "Opcion no valida. Intente nuevamente.\n";
        }
    };

    return 0;
}
