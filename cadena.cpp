#include <string.h>
#include <ctype.h>
#include <iterator>
#include <iostream>//Temporal y solo para testeo
#include <iomanip>
#include "cadena.hpp"




//Operadores de entrada/salida
std::istream& operator>>(std::istream& in, Cadena&cad){
	char fina[33];
	fina[0]='\0';
	in>>std::setw(sizeof fina)>>fina;

//	fflush(stdin);
	Cadena aux(fina);
	cad=aux;
	return in;
}



std::ostream& operator<<(std::ostream&on,const Cadena&cad){
	on<<cad.c_str();
	return on;
}



//Constructor por cadenas
Cadena::Cadena(const char*cad){
	tam_=strlen(cad);
	s_=new char[tam_+1];
	strcpy(s_,cad);

}



//Constructor predeterminado
Cadena::Cadena(unsigned int n,const char s){
	s_=new char[n+1];
	for(int i=0; i<n;i++){
		s_[i]=s;
	}
	s_[n]='\0';
	tam_=n;
};



//Constructor por copia
Cadena::Cadena(const Cadena& c){
	tam_=c.tam_;
	s_=new char[c.tam_+1];
	strcpy(s_,c.s_);
}



//Metodo length
unsigned int Cadena::length()const{
	return tam_;
}



//Sobrecarga del operador =
Cadena& Cadena::operator=(Cadena&&c){
	if(this!=&c){
		delete[] s_;
		s_=std::move(c.s_);
		tam_=std::move(c.tam_);
	}
	c.s_=nullptr;
	c.tam_=0;
	return *this;
}
//constructor por movimiento
Cadena::Cadena(Cadena && c):s_(std::move(c.s_)),tam_(std::move(c.tam_)){
	c.tam_=0;
	c.s_=nullptr;
}
Cadena& Cadena::operator=(const Cadena&c){
	if(this!=&c){
		this->tam_=c.tam_;
		this->s_=new char[c.tam_+1];
		strcpy(s_,c.s_);
		s_[tam_]='\0';
	}
	return *this;
}


//Sobrecarga del operador ==
bool operator==(const Cadena&c1,const Cadena&c){
	return(strcmp(c1.s_,c.s_)==0);
}


//Sobrecarga del operador !=
bool operator!=(const Cadena&c1,const Cadena&c){
	return(!(c1==c));
}


//Sobrecarga del operador <
bool operator <(const Cadena&c1,const Cadena&c){
	return((strcmp(c1.s_,c.s_)<0));
}



//Sobrecarga del operador >
bool operator >(const Cadena&c1,const Cadena&c){
	return(c<c1);
}



//Sobrecarga del operador <=
bool operator <=(const Cadena&c1,const Cadena&c){
	return((c1==c)||(c1<c));
}


//Sobrecarga del operador >=
bool operator >=(const Cadena&c1,const Cadena&c){
	return(!(c1<c));
}



//Conversor de clase a cons char*
const char *Cadena::c_str()const{
	return(this->s_);
}



//Sobrecarga del operador []
char& Cadena::operator[](unsigned int i){
	return(this->s_[i]);
}
char Cadena::operator[](unsigned int i)const{
	return(this->s_[i]);
}



//Metodo at()
char Cadena::at(int i)const{
	if(i<0){
		throw(std::out_of_range("Fuera de los limites de la cadena"));
	}
	if(i>this->tam_-1){
		throw(std::out_of_range("Fuera de los limites de la cadena"));
	}
	else{
		return(this->s_[i]);
	}
}
char& Cadena::at(int i){
	if(i<0){
		throw(std::out_of_range("Fuera de los limites de la cadena"));
	}
	if(i>this->tam_-1){
		throw(std::out_of_range("Fuera de los limites de la cadena"));
	}
	else{
		return(this->s_[i]);
	}
}



//Sobrecarga del operador +=
Cadena& Cadena::operator +=(const Cadena&c){
	
	char* s= new char[this->tam_+c.tam_+1];
	strcpy(s, this->s_);
	strcat(s,c.s_);
	s[this->tam_+c.tam_]='\0';
	if(this->tam_!=0){
		delete[]this->s_;
	}
	this->s_=new char[this->tam_+c.tam_+1];
	strcpy(this->s_,s);
	this->tam_+=c.tam_;
	delete []s;
	return *this;
}



//Sobrecarga del operador +;
Cadena operator +(const Cadena&c1,const Cadena&c){
	Cadena s(c1);
	s+=c;
	return s;
}



//Metodo subst
Cadena Cadena::substr(int in, int tam)const{
	if(in<0||tam<0){
		throw std::out_of_range("Sobrepasado rango de la cadena");
	}
	if(in+tam>tam_-1){
		throw std::out_of_range("Sobrepasado rango de la cadena");
	}
	char ss[tam];
	for(int i=0;i<tam;i++){
		ss[i]=s_[i+in];
	}
	ss[tam]='\0';
	Cadena aux(ss);
	return aux;
}



//Destructor
Cadena::~Cadena(){
	delete[] s_;
}
void Cadena::mostrar(){
	int i=0;
	while(i<=tam_){
		std::cout<<s_[i]<<i<<std::endl;
		i++;
	}
}
