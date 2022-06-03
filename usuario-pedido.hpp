#ifndef UP 
#define UP
#include <map>
#include <set>  
class Pedido;
class Usuario;
class Usuario_Pedido{
  public:
    typedef std::set<Pedido*> Pedidos;
    Pedidos& pedidos(Usuario&U){return TP.find(&U)->second;};
    void asocia(Usuario&sus,Pedido&pedi){TP[&sus].insert(&pedi);PediUsu[&pedi]=&sus;}
    void asocia(Pedido&pedi,Usuario&sus){TP[&sus].insert(&pedi);PediUsu[&pedi]=&sus;}
    Usuario* cliente(Pedido&P){return PediUsu.find(&P)->second;};
  private:
    std::map<Usuario*,Pedidos> TP;
    std::map<Pedido*,Usuario*> PediUsu;
};
#endif
