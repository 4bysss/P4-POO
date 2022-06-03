#ifndef AMAZON
#define AMAZON
#include "usuario-pedido.hpp"
#include "usuario.hpp"
#include "tarjeta.hpp"
#include "fecha.hpp"
#include "pedido-articulo.hpp"
class Pedido_Articulo;
static unsigned todoP = 0;
class Pedido{
  public:
    Pedido(Usuario_Pedido&PU,Pedido_Articulo&PA,Usuario&U,const Tarjeta&T,const Fecha&F=Fecha());
    Pedido(Pedido&)=delete;
    const unsigned numero()const{return num_ped;}
    const double total()const{return imporT;}
    const Fecha& fecha()const{return dia;}
    static unsigned n_total_pedidos(){return todoP;}
    const Tarjeta* tarjeta()const{return tarj;}
    //Clases excepcion
    class Vacio{
      public:
        Vacio(Usuario*Us):Us_(*Us){}
        Usuario& usuario()const{return Us_;}
      private:
        Usuario& Us_;
    };
    //Clase impostor
    class Impostor{
      public:
        Impostor(Usuario*Us):Us_(*Us){}
        Usuario& usuario() const{return Us_;}
      private:
        Usuario& Us_;
    };
    //Clase sin stock
    class SinStock{
      public:
        SinStock(Articulo*Ar):Ar_(*Ar){}
        Articulo& articulo()const{return Ar_;}
      public:
        Articulo& Ar_;
    };
  private:
    unsigned num_ped;
    double imporT;
    unsigned cantP;
    const Tarjeta* tarj;
    const Fecha dia;

};
std::ostream& operator<<(std::ostream& os, const Pedido& p);

#endif
