#ifndef __ARTI__
#define __ARTI__
#include"cadena.hpp"
#include"fecha.hpp"
#include<iostream>
#include<set>
class Autor{
	public:
		Autor(const Cadena&nom,const Cadena&appe,const Cadena&dire):nombre_(nom),apellido_(appe),direccion_(dire){};
		const Cadena& nombre()const{return nombre_;}
		const Cadena& apellidos()const{return apellido_;}
		const Cadena& direccion()const{return direccion_;}
	private:
		const Cadena nombre_;
		const Cadena apellido_;
		const Cadena direccion_;
};
class Articulo{
	public:
		typedef std::set<Autor*> Autores;
		Articulo(const Autores&au,const Cadena&ref,const Cadena&titu,const Fecha&fech,double pr):Autores_(au),CodRef(ref),Titu(titu),FPubli(fech),price(pr){if(Autores_.empty()){throw Autores_vacios{}; }};
		const Cadena& referencia()const;
		const Cadena& titulo()const;
		const Fecha& f_publi()const;
		const Autores autores()const{return Autores_;}
		const double precio()const{return price;}
		double& precio(){return price;}
		virtual void impresion_especifica(std::ostream&)const=0;
		class Autores_vacios{};
		virtual ~Articulo(){};
	protected:
		const Autores Autores_;
		const Cadena CodRef;
		const Cadena Titu;
		const Fecha FPubli;
		
		double price;
		//int stock_;
};
class ArticuloAlmacenable:public Articulo{
	public:
		ArticuloAlmacenable(const Autores&au,const Cadena&ref,const Cadena&titu,const Fecha&fech,double pr,int stock = 0):Articulo(au,ref,titu,fech,pr),Stock_(stock){};
		int& stock(){return Stock_;}
		int stock()const{return Stock_;}
		virtual void impresion_especifica(std::ostream&)const=0;
		virtual ~ArticuloAlmacenable(){};
	protected:
		int Stock_;
};
class Libro:public ArticuloAlmacenable{
	public:
		Libro(const Autores&au,const Cadena&ref,const Cadena&titu,const Fecha&fech,double pr,const int pg,int stock = 0):ArticuloAlmacenable(au,ref,titu,fech,pr,stock),paginitas(pg){};
		int n_pag()const{return paginitas;}
		virtual void impresion_especifica(std::ostream&)const;
		
	protected:
		const int paginitas;
};
class Cederron:public ArticuloAlmacenable{
	public:
		Cederron(const Autores&au,const Cadena&ref,const Cadena&titu,const Fecha&fech,double pr,const double tam_,int stock = 0):ArticuloAlmacenable(au,ref,titu,fech,pr,stock),Tam_(tam_){};
		double tam()const{return Tam_;}
		virtual void impresion_especifica(std::ostream&)const;
	protected:
		double Tam_;
};
class LibroDigital:public Articulo{
	public:
		LibroDigital(const Autores&au,const Cadena&ref,const Cadena&titu,const Fecha&fech,double pr_,const Fecha& expir=Fecha()):Articulo(au,ref,titu,fech,pr_),Expir_(expir){}
		const Fecha f_expir()const{return Expir_;}
		virtual void impresion_especifica(std::ostream&)const;

	private:
		const Fecha Expir_;
};
std::ostream& operator<<(std::ostream&is,const Articulo&art);
#endif
