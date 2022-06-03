#ifndef __USER__
#define __USER__
#include<set>
#include<map>
#include<unordered_set>
#include<unordered_map>
#include<unistd.h>
#include<iterator>
#include"articulo.hpp"
#include"tarjeta.hpp"
#include"fecha.hpp"
#include"cadena.hpp"
class Numero;
class Tarjeta;
typedef std::unordered_map<Articulo*, unsigned int> Articulos;
typedef std::map<Numero, Tarjeta*> Tarjetas;
static std::unordered_set<Cadena>UserLooser;
static const char* CrB = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890";
class Clave{
	public:
		enum Razon{CORTA,ERROR_CRYPT};
		Clave(const char*);
		const Cadena& clave()const;
		bool verifica(const char*)const;
		
		
		class Incorrecta{
			
			public:
				Incorrecta(const Razon&r):causa(r){};
				Razon razon()const{return causa;};
			private:
				const Razon causa;
		};
	private:
		Cadena claveC_;
		char * sal;
};
class Usuario{
	public:
		typedef std::unordered_map<Articulo*, unsigned int> Articulos;
		typedef std::map<Numero, Tarjeta*> Tarjetas;
		explicit Usuario(const Cadena&,const Cadena&,const Cadena&, const Cadena&,const Clave&);
		const Cadena&id()const;
		const Cadena&nombre()const;
		const Cadena&apellidos()const;
		const Cadena&direccion()const;
		Articulos& compra()const;
		Tarjetas& tarjetas()const;
		Usuario&operator=(const Usuario&) = delete;
		Usuario(const Usuario&) = delete;
		void es_titular_de(Tarjeta&)const;
		void no_es_titular_de(Tarjeta&)const;
		void compra(Articulo&,int cant = 1)const;
		int n_articulos()const;
		friend std::ostream& operator<<(std::ostream& os, const Usuario&);
		friend std::ostream& mostrar_carro(std::ostream&,Usuario&sus);
		
		class Id_duplicado{
			public:
				Id_duplicado(const Cadena&dup):dupi(dup){};
				const Cadena& idd()const{return dupi;};
			private:
				const Cadena& dupi;
		};
		~Usuario();
	private:
		friend class Tarjeta;
		mutable Articulos Artis;
		mutable Tarjetas Tarjs;
		const Cadena iden_;
		const Cadena nombre_;
		const Cadena apellido_;
		const Cadena direccion_;
		const Clave clave_;
};

std::ostream& mostrar_carro(std::ostream&,Usuario&sus);
std::ostream& operator<<(std::ostream& os, const Usuario&);

//Subclase Clave

#endif
