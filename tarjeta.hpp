#ifndef __50CENTS__
#define __50CENTS__
#include"usuario.hpp"
#include<set>
#include<map>
#include<unordered_set>
#include<unordered_map>
#include<ctype.h>
#include"articulo.hpp"
#include"cadena.hpp"
#include"fecha.hpp"
class Usuario;
class Incorrecto;
static const char* enum_name[]={ "Tipo indeterminado", "VISA", "Mastercard", "Maestro", "JCB", "AmericanExpress"};
class Numero;
static std::set<Numero> TNums;

class Numero{
	public:
		Numero(const Cadena&);
		enum Razon{LONGITUD,DIGITOS,NO_VALIDO};
		operator const char*() const;
		friend bool operator<(const Numero&,const Numero&);
		class Incorrecto{
			public:
				Incorrecto(Razon r):raz(r){};
				Razon razon()const{return raz;};
			private:
				Numero::Razon raz;
		};
	private:
		Cadena troq;
};
class Tarjeta{
	public:
		enum Tipo{Otro,VISA,Mastercard,Maestro,JCB,AmericanExpress};
		Tarjeta(const Numero& ,Usuario&,const Fecha&);
		Tarjeta(const Tarjeta&) = delete;
		Tarjeta& operator=(const Tarjeta&) = delete;
		Tipo tipo()const;
		const Numero& numero()const { return num;};
		const Usuario* titular()const{ return titu;};
		const Fecha& caducidad()const{ return cadu;};
		const bool activa()const {return acti;};
		bool activa(bool t);
		friend bool operator<(const Tarjeta&,const Tarjeta&);
		~Tarjeta();
		//Clase excepcion para tarjetas caducadas
		class Caducada{
			public:
				
				Caducada(const Fecha&fech):cuand(fech){};
				const Fecha& cuando()const{return cuand;};
			private:
				const Fecha& cuand;
		};
		//Clase excepcion para tarjetas duplicadas
		class Num_duplicado{
			public:
				Num_duplicado(const Numero n):dup(n){};
				const Numero& que()const{return dup;};
			private:
				const Numero dup;
		};
		//Clase de excepcion a futuro
		class Desactivada{
			public:
				//desactivada();
		};

	private:
		friend class Usuario;
		const Numero num;
		const Usuario* titu;
		const Fecha cadu;
		bool acti;
		void anular_titular();
};

//Subclase Numero 




//Metodos externos de Numero 
bool operator<(const Numero&,const Numero&);


//Metodos externos de Tarjeta 
bool operator<(const Tarjeta&,const Tarjeta&);
std::ostream& operator<<(std::ostream&,const Tarjeta&);
std::ostream& operator<<(std::ostream&,const Tarjeta::Tipo);
#endif
