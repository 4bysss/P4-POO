#include <ctime>
#include <iostream>
#include <cassert>
#include <string.h>
#include <string>
#include<locale>
#include"fecha.hpp"
#define annoMinimo 1902
#define annoMax 2037
time_t t=time(nullptr);
tm* dt=localtime(&t);
struct tm* conv=localtime(&t);
char Fechaletra[81];

//Operadores de entrada salida
std::ostream& operator<<(std::ostream&on,const Fecha&fech){
	setlocale(LC_ALL, "es_ES.UTF-8");
	conv->tm_year= fech.anno()- 1900;
	conv->tm_mon=fech.mes()-1;
	conv->tm_mday=fech.dia();
	mktime(conv);
	std::strftime (Fechaletra,80,"%A %d de %B de %Y" ,conv);
	on<<Fechaletra;
	return on;
}



std::istream& operator>>(std::istream&in,Fecha&fech){
	char fechizador[80];
	std:in>>fechizador;
	int di,me,an;
	di=me=an=0;
	if(strlen(fechizador)>10){
		in.setstate(std::ios::failbit);
		throw Fecha::Invalida("Formato mal");
	}
	if(std::sscanf (fechizador,"%d/%d/%d",&di,&me,&an)!=3){
		in.setstate(std::ios::failbit);
		throw Fecha::Invalida("Formato mal");
	}
	else{	
		try{
			Fecha aux(fechizador);
		}catch(Fecha::Invalida e){
			in.setstate(std::ios::failbit);
			throw Fecha::Invalida("Formato mal");
		}
		fech = fechizador;
		fech.validar();
	}
	return in;
}



const char* Fecha::Invalida::por_que()const{return razon_;}
void Fecha::validar(){
	if(anno_<1902 || anno_>2037){
		throw Fecha::Invalida("Anno invalido");
	}
	if (mes_>12||mes_<1){
		throw Fecha::Invalida("Mes invalido, maximo 12");
	}
	else if(mes_==2){
		if((anno_%4==0) &&(anno_%400==0 || anno_%100!=0)){
			if(dia_>29){
				throw Fecha::Invalida("Dia invalido, anno_ bisiesto");
			}
		}
		else if (dia_>28){
			throw Fecha::Invalida("Dia no valido de febrero");
		}
	}
	else if(mes_==2&&dia_>28){
		throw Fecha::Invalida("Dia no valido de febrero");
	}
	else if((mes_==4||mes_==6||mes_==9||mes_==11)&&dia_>30){
		throw Fecha::Invalida("Dia invalido, maximo 30");
	}
	else if (dia_>31){
		throw Fecha::Invalida("Dia inavalido, maximo 31");
	}
}


//Constructor por defecto y parametrizado
Fecha::Fecha(const int d, const int m, const int y){
	dia_=d;
	mes_=m;
	anno_=y;
	if(dia_==0){
		dia_=dt->tm_mday;
	}
	if(mes_==0){
		mes_=dt->tm_mon+1;
	}
	if(anno_==0){
		anno_=dt->tm_year+1900;
	}
	validar();
	
}



//Constructorr por copia
/*Fecha::Fecha(const Fecha&f){
	dia_=f.dia_;
	mes_=f.mes_;
	anno_=f.anno_;
	validar();
}*/

//Metodos observadores
int Fecha::dia()const{return dia_;}
int Fecha::mes()const{return mes_;}
int Fecha::anno()const{return anno_;}
//Funcion que muestra la Fecha de un objeto (a efectos de testeo);
void Fecha::mostrar(){
	std::cout<<dia_<<"-"<<mes_<<"-"<<anno_<<std::endl;
}



//Constructor parametrizado por strings
Fecha::Fecha(const char *f){
	int n=std::sscanf(f,"%d/%d/%d",&dia_,&mes_,&anno_);
	
	if(n!=3){
		throw Fecha::Invalida("Formato invalido");
	}else{
	if(dia_==0){
		dia_=dt->tm_mday;
	}
	if(mes_==0){
		mes_=dt->tm_mon+1;
	}
	if(anno_==0){
		anno_=dt->tm_year+1900;
	}

	validar();}
	
}


/*Fecha& Fecha::operator=(const Fecha&f){
	dia_=f.dia_;
	mes_=f.mes_;
	anno_=f.anno_;
	return *this;
}*/



//Operador de conversion
char* Fecha::cadena()const{
	setlocale(LC_ALL, "spanish");
	conv->tm_year= anno_ - 1900;
	conv->tm_mon=mes_-1;
	conv->tm_mday=dia_;
	mktime(conv);
	std::strftime (Fechaletra,80,"%A %d de %B de %Y" ,conv );
	return Fechaletra;
}



//Operador postncremento
Fecha Fecha::operator++(int n){
	Fecha aux;
	aux=*this;
	*this+=1;
	return aux;
}



//Operador preincremento
Fecha& Fecha::operator++(){
	int i=1;
	*this+=i;
	return *this;
}



//Operator postdecremento
Fecha Fecha::operator--(int n){
	Fecha aux;
	aux=*this;
	*this+=-1;
	return aux;
}



//Operador predecremento
Fecha& Fecha::operator--(){
	*this+=-1;
	return *this;
}



//Operador -=
Fecha& Fecha::operator-=(int n){
	*this+=-n;
	return *this;
}


//Operato +;
Fecha Fecha::operator+(int n)const{
	Fecha aux;
	aux=*this;
	aux+=n;
	return aux;
}



//Operator -
Fecha Fecha::operator-(int n)const{
	Fecha aux;
	aux=*this;
	aux+=-n;
	return aux;
}



//Operador +=
Fecha& Fecha::operator+=(int n){
	this->dia_+=n;
	conv->tm_year=anno_-1900;
	conv->tm_mon=mes_-1;
	conv->tm_mday=dia_;
	mktime(conv);
	anno_=conv->tm_year+1900;
	mes_=conv->tm_mon+1;
	dia_=conv->tm_mday;
	validar();
	return *this;
}



//Operador ==
bool operator==(const Fecha&f1,const Fecha&f){
	return(f.dia_==f1.dia_&&f.mes_==f1.mes_&&f.anno_==f1.anno_);
}



bool operator<(const Fecha&f1,const Fecha&f){
	if(f1.anno_<f.anno_){
		return true;
	}
	else if(f1.anno_==f.anno_){
		if(f1.mes_<f.mes_){
			return true;
		}
		else if(f1.mes_==f.mes_){
			if(f1.dia_<f.dia_){
				return true;
			}
		}
	}
	return false;
}



//Operador !=
bool operator!=(const Fecha&f1,const Fecha&f){
	return(!(f1==f));
}



//Operator >
bool operator >(const Fecha& f1,const Fecha&f){
	return (f<f1);
}



//Operator <=
bool operator <=(const Fecha&f1,const Fecha&f){
	return (!(f<f1));
}



//Operator >=
bool operator >=(const Fecha&f1,const Fecha&f){
	return (!(f1<f));
}

