#include"articulo.hpp"
#include"cadena.hpp"
#include"fecha.hpp"
#include <iomanip>
const Cadena& Articulo::referencia()const{return CodRef;}
const Cadena& Articulo::titulo()const{return Titu;}
const Fecha& Articulo::f_publi()const{return FPubli;}
//int Articulo::stock()const{return stock_;}
//int& Articulo::stock(){return stock_;}
std::ostream& operator<<(std::ostream&on,const Articulo&ar){
	on<<"["<<ar.referencia()<<"] "<<'"'<<ar.titulo()<<'"'<<", de ";
	auto aux = ar.autores();
	auto i = aux.begin();
	on<<(*i)->apellidos();
	for(i;i!=aux.end();++i){
		if(i!=aux.begin()){
			on<<", ";
			on<<(*i)->apellidos();
		}
	}
	
	on<<". "<<ar.f_publi().anno()<<". "<<std::fixed<<std::setprecision(2)<<ar.precio()<<" €\n\t";
	ar.impresion_especifica(on);
	return on;
}
//Pendiente Impresion especifica de las clases heredadas
void Libro::impresion_especifica(std::ostream&on)const{
	
	on<<paginitas<<" págs., "<<Stock_<<" unidades.";
	
};
void Cederron::impresion_especifica(std::ostream&on)const{
	on<<std::fixed<<std::setprecision(0)<<Tam_<<" MB, "<<Stock_<<" unidades.";	
};
void LibroDigital::impresion_especifica(std::ostream&on)const{
	on<<"A la venta hasta el "<<Expir_<<'.';	

};

