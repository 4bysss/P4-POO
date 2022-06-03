#ifndef PA
#define PA
#include<map>
#include<iostream>
#include<set>
#include<iomanip>
#include <iterator>
#include"articulo.hpp"
#include"pedido.hpp"
class LineaPedido{
  public:
    //Observadores
    explicit LineaPedido(double preci,int cantidad=1):PVP(preci),canti(cantidad){}
    double precio_venta()const{return PVP;}
    int cantidad()const {return canti;}
  private:
    double PVP;
    int canti;
};
std::ostream& operator<<(std::ostream&,const LineaPedido&);

class OrdenaPedidos:public std::binary_function<Pedido*,Pedido*,bool>{
  public:
    bool operator()(const Pedido*p1,const Pedido*p2)const;
};
class OrdenaArticulos:public std::binary_function<Articulo*,Articulo*,bool>{
  public:
    bool operator()(Articulo*A1,Articulo*A2)const{return A1->referencia()<A2->referencia();}
};
class Pedido_Articulo{
  public:
    std::ostream& mostrarVentasArticulos(std::ostream&on)const; 
    std::ostream& mostrarDetallePedidos(std::ostream&on)const;
    typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
    typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
    const ItemsPedido& detalle(Pedido&P)const{return PedArt.find(&P)->second;}
    void pedir(Pedido&P,Articulo&A,double C,unsigned cant=1);
    void pedir(Articulo&A,Pedido&P,double C,unsigned cant=1);
    const Pedidos& ventas(Articulo&A)const;


  private:
    std::map<Pedido*, ItemsPedido, OrdenaPedidos> PedArt;
    std::map<Articulo*, Pedidos, OrdenaArticulos> ArtPed;
};
std::ostream& operator<<(std::ostream&,const std::map<Pedido*, LineaPedido, OrdenaPedidos>&  );
std::ostream& operator<<(std::ostream&,const std::map<Articulo*, LineaPedido, OrdenaArticulos>&);

#endif
