#ifndef _fecha_
#define _fecha_
class Fecha{
	public:
		//Fecha();
//		Fecha(const Fecha&f);
		void validar();
		explicit Fecha(const int d=0, const int m=0,const int y=0);
		Fecha(const char *f);
//		Fecha& operator=(const Fecha&f);
		Fecha& operator+=(int);
		Fecha& operator-=(int);
		Fecha& operator++();
		Fecha operator++(int);
		Fecha& operator--();
		Fecha operator--(int);
		Fecha operator+(int)const;
		Fecha operator-(int)const;
		friend bool operator<(const Fecha&,const Fecha&);
		friend bool operator==(const Fecha&,const Fecha&);
		char* cadena()const;
		void mostrar();
		//prueba
		int aux();
		int dia()const;
		int mes()const;
		int anno()const;
		//~Fecha();
		class Invalida{
			public:
				Invalida(const char*a):razon_(a){};
				const char* por_que()const;
			private:
				const char* razon_;
		};
		const static int AnnoMinimo{1902};
		const static int AnnoMaximo{2037};
	private:
		int dia_,mes_,anno_;

};
std::ostream& operator<<(std::ostream&on,const Fecha&fech);
std::istream& operator>>(std::istream&in, Fecha&fech);
bool operator<(const Fecha&,const Fecha&);
bool operator==(const Fecha&,const Fecha&);
bool operator>(const Fecha&,const Fecha&);
bool operator!=(const Fecha&,const Fecha&);
bool operator<=(const Fecha&,const Fecha&);
bool operator>=(const Fecha&,const Fecha&);
#endif
