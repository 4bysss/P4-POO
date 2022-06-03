#include "usuario.hpp"
#include <cstdlib>
#include <iomanip>
#include<string.h>
//Constructor
Usuario::Usuario(const Cadena& id,const Cadena&name,const Cadena&SName,const Cadena&dir,const Clave&key):iden_(id),nombre_(name),apellido_(SName),direccion_(dir),clave_(key){
	if(UserLooser.insert(id).second == false){
		throw Id_duplicado(id);
	}
	else{
		UserLooser.insert(id);
	}
}

//Metodos observadores
const Cadena& Usuario::id()const{return iden_;}
const Cadena& Usuario::nombre()const{return nombre_;}
const Cadena& Usuario::apellidos()const{return apellido_;}
const Cadena& Usuario::direccion()const{return direccion_;}
Articulos& Usuario::compra()const{return Artis;}
Tarjetas& Usuario::tarjetas()const{return Tarjs;}


void Usuario::es_titular_de(Tarjeta&Tr)const{
	if(Tr.titular()==this){
		Tarjeta*T=&Tr;
		Numero N = T->numero();
		Tarjs.insert(std::pair<Numero,Tarjeta*>(N,T));
	}
}

void Usuario::no_es_titular_de(Tarjeta&Tr)const{
	Tarjeta*T=&Tr;
	Numero N = T->numero();
	Tarjs.erase(N);
}
void Usuario::compra(Articulo& Ar,int cant)const{
	Articulo*A=&Ar;

	if (cant==0){
		Artis.erase(A);
	}
	else if(Artis.find(A)==Artis.end()){
		if(LibroDigital*auxE = dynamic_cast <LibroDigital*>(A)){
      		if (auxE->f_expir()>=Fecha()){
				  Artis.insert(std::pair<Articulo*,unsigned int>(A,cant));
      		}
		}
		else{
		Artis.insert(std::pair<Articulo*,unsigned int>(A,cant));
		}
	}
	else{
		Artis[A]=cant;
	}
}
std::ostream& operator<<(std::ostream&on,const Usuario&sus){
	on<<sus.iden_<<" ["<<sus.clave_.clave()<<']'<<sus.nombre_<<" "<<sus.apellido_<<'\n'<<sus.direccion_<<'\n'<<"Tarjetas:\n";
	for(auto it = sus.Tarjs.begin();it!=sus.Tarjs.end();++it){
		on<<it->first;
	}
	return on;
}
int Usuario::n_articulos()const{
	int i = 0;
	for(auto it = Artis.begin();it!=Artis.end();++it){++i;}
	return i;
}
std::ostream& mostrar_carro(std::ostream&on,Usuario&sus){
	on<<"Carrito de la compra de "<<sus.iden_<<"[Artículos: "<<sus.n_articulos()<<"]\n";
	for(auto it = sus.Artis.begin();it!=sus.Artis.end();++it){
		on<<it->second<<" ["<<it->first->referencia()<<"] "<<'"'<<it->first->titulo()<<'"'<<", "<<it->first->f_publi().anno()<<". "<<std::fixed<<std::setprecision(2)<<it->first->precio()<<" €"<<'\n';
	}
	return on;
}
Usuario::~Usuario(){
	for(auto it=Tarjs.begin();it!=Tarjs.end();++it){
		it->second->anular_titular();
		
	}
	UserLooser.erase(iden_);
}
//Construcor de clave cifrada
Clave::Clave(const char* password){
	char CBaux[2];
	if(strlen(password)<5){
		throw Incorrecta(CORTA);
	}
	for(int i=0;i<2;i++){
		CBaux[i] = CrB[rand()%strlen(CrB)];
	}
	sal = CBaux;
	claveC_=crypt(password,CBaux);}
//Metodo verifica
bool Clave::verifica(const char* aux)const{
	
	return crypt(aux,sal)==claveC_;
}
//Metodo obervador
const Cadena& Clave::clave()const{
	return claveC_;
}


