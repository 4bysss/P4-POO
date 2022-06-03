#include "pedido-articulo.hpp"
#include <functional>

void Pedido_Articulo::pedir(Pedido&P,Articulo&A,double C,unsigned cant){
  PedArt[&P].insert(std::make_pair(&A,LineaPedido(C,cant)));
  ArtPed[&A].insert(std::make_pair(&P,LineaPedido(C,cant)));
}

void Pedido_Articulo::pedir(Articulo&A,Pedido&P,double C,unsigned cant){
  PedArt[&P].insert(std::make_pair(&A,LineaPedido(C,cant)));
  ArtPed[&A].insert(std::make_pair(&P,LineaPedido(C,cant)));
}

const Pedido_Articulo::Pedidos& Pedido_Articulo::ventas(Articulo&A)const{
  if(ArtPed.find(&A)!=ArtPed.end()){
    return ArtPed.find(&A)->second;
  }
  else{
    Pedido_Articulo::Pedidos vacio;
    return vacio;
  }
}

bool OrdenaPedidos::operator()(const Pedido *p1, const Pedido *p2)const{
  return (p1->numero()<p2->numero());
}

std::ostream& Pedido_Articulo::mostrarVentasArticulos(std::ostream&on)const{
  double total = 0;
  for(auto&iter:ArtPed){
    on<<"Ventas de ["<<iter.first->referencia()<<"] "<<iter.first->titulo()<<"\n";
    on<<ventas(*iter.first)<<"\n";
    on<<iter.second<<"\n";
  }
  return on;
}

std::ostream& operator<<(std::ostream&on,const std::map<Pedido*,LineaPedido,OrdenaPedidos>& P){
  double total=0;
  int totalart=0;
  on<<"[Pedidos:"<<P. size()<<"]\n";
  on<<"=============================\n";
  on<<"PVP   Cantidad           Fecha de venta\n";
  on<<"=============================\n";
  for(auto& iter:P){
    totalart+=iter.second.cantidad();
    total += iter.second.precio_venta() * iter.second.cantidad();
    on<<std::fixed<<std::setprecision(2);
    on<<iter.second.precio_venta()*iter.second.cantidad()<<" € "<<iter.second.cantidad()<<"          "<<iter.first->fecha();
  }
  on<<"=============================\n";
  on<<total<<" €        "<<totalart;
  return on;
}
std::ostream& operator<<(std::ostream&on,const std::map<Articulo*, LineaPedido, OrdenaArticulos>&P){
  double total=0;
  on<<"PVP   Cantidad           Artículo\n";
  on<<"=============================\n";
  for(auto& iter:P){
    total = iter.second.precio_venta() * iter.second.cantidad();
    on<<std::fixed<<std::setprecision(2);
    on<<iter.second.precio_venta()<<" €"<<iter.second.cantidad()<<"          "<<"["<<iter.first->referencia()<<"]"<<"\""<<iter.first->titulo()<<"\"";
  }
  on<<"=============================\n";
  on<<"Total   "<<total<<" €";
  return on;
}

std::ostream& operator<<(std::ostream&on,const LineaPedido&Ln){
  on<<std::fixed<<std::setprecision(2)<<Ln.precio_venta()<<" €\t"<<Ln.cantidad();
  return on;
}

std::ostream& Pedido_Articulo::mostrarDetallePedidos(std::ostream&on)const{
  double total = 0;
  for(auto iter:PedArt){
    total+=iter.first->total();
    on<<"Pedído Núm. "<<iter.first->numero()<<"\n";
    on<<"Cliente: "<<iter.first->tarjeta()->titular()->nombre()<<"Fecha: "<<iter.first->fecha()<<"\n";
    on<<detalle(*iter.first)<<"\n";

  }
  on<<"TOTAL VENTAS: "<<std::fixed<<std::setprecision(2)<<total<<" €";
  return on;
}

