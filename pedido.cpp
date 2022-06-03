#include "pedido.hpp"
#include "articulo.hpp"
Pedido::Pedido(Usuario_Pedido&PU,Pedido_Articulo&PeA,Usuario&U,const Tarjeta&T,const Fecha&F):num_ped(todoP+1),imporT(0),cantP(0),tarj(&T),dia(F){
  if(&U!=T.titular()){
    throw Impostor(&U);
  }
  if(U.compra().empty()){
    throw Vacio(&U);
  }
  if(T.caducidad()<F){
    throw Tarjeta::Caducada(T.caducidad());
  }
  if(!T.activa()){
    throw Tarjeta::Desactivada();
  }
  double imporLP=0;
  for(auto&iter:U.compra()){
    if(ArticuloAlmacenable*aux=dynamic_cast<ArticuloAlmacenable*>(iter.first)){
      if(aux->stock()<iter.second){
        Articulo& aux(*iter.first);
        U.compra().clear();
        throw SinStock(&aux);
      }
    }
    else{
      LibroDigital*auxE = dynamic_cast <LibroDigital*>(iter.first);
      if (auxE->f_expir()<=Fecha()){
        iter.second = 0;
      }
    }
  }

  PU.asocia(*this,U);
  for(auto&iter:U.compra()){
    ++cantP;
    imporT+=(iter.first->precio()* iter.second);
    if(ArticuloAlmacenable*aux=dynamic_cast<ArticuloAlmacenable*>(iter.first)){
      aux->stock()-=iter.second;
      PeA.pedir(*iter.first,*this,iter.first->precio(),iter.second);
    }
    else if(iter.second>0){
      PeA.pedir(*iter.first,*this,iter.first->precio(),iter.second);
    }
    //PA.pedir(*this,iter.first,iter.first->precio(),iter.second);
  }
  num_ped=++todoP;
  U.compra().clear();

}
std::ostream& operator<<(std::ostream&on,const Pedido&p){
  on<<"Núm. pedido: "<<p.numero()<<std::endl;
  on<<"             "<<"Fecha: "<<p.fecha()<<std::endl;
  on<<"             "<<"Pagado con: "<<p.tarjeta()->tipo()<<" n.º:"<<p.tarjeta()->numero()<<std::endl;
  on<<"             "<<"Importe: "<<std::fixed<<std::setprecision(2)<<p.total()<<" €"<<std::endl;
  return on;

    }
