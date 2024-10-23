#include <iostream>
#include <conio.h>
#include <cmath>
#include <clocale>
#include <windows.h>
//Librerias.h
#include "Membrete.h" //comillas
#include "Bienvenida.h"

using namespace std;

// Extra
void espacio();
void limpiar();
float letra_Numero();
// Menu
void Menu();
void Op_basicas();
void Op_cientificas();
// Operaciones 1
void suma(float,float,float*);
void resta(float,float,float*);
void multiplicacion(float,float,float*);
void division(float,float,float*);
// Operaciones 2
void raiz2(float,float*);
void valorAbsoluto(float,float*);
void Potencia(float,float,float*);
void Seno(float,float*);
void Coseno(float,float*);
void Tangente(float,float*);

int main(){
	int i;
	// Configurar la consola en modo pantalla completa
    HWND hwnd = GetConsoleWindow(); // Obtiene el handle de la ventana de la consola
    ShowWindow(hwnd, SW_MAXIMIZE);  // Maximiza la ventana de la consola
	// LC_TYPE afecta los caracteres de la funci�n
	setlocale(LC_CTYPE,"Spanish"); // Libreria clocale
	system("COLOR F0"); // Independiente de la libreria Windows.h
	for(i=0;i<15;i++){
		cout<<"\n";	
	}
	Bienvenida();
	getch();
	system("cls");	
	Menu();
}

void espacio(){
	int i;
	for(i=0;i<3;i++){
		cout<<"\n";	
	}
}

void limpiar(){
	system("cls");
}

float letra_Numero(){
	float num;
	cin.ignore(100,'\n');
	while (true) {
	    cin>>num;
	
	    if (cin.fail()) {
	        cin.clear(); // Limpia el estado de error
	        cin.ignore(1000,'\n'); // Ignora los caracteres en el buffer hasta el siguiente salto de l�nea
	        cout<<"\n\t >> Entrada no v�lida. "<<endl;
	        cout<<"\t << No ingrese una letra, ingresa un n�mero: ";
	    } else {
	        break; // Salir del bucle si la entrada es v�lida
	    }
	}
	return num;
}

void Menu(){
	char op;
	do{
		system("COLOR A0");
		espacio();
		Membrete();
		espacio();
		cout<<"\t >> MEN�: "<<endl;
		cout<<"\t >> OPERACIONES B�SICAS............[1]"<<endl;
		cout<<"\t >> OPERACIONES CIENTIFICAS........[2]"<<endl;
		cout<<"\t << SALIR..........................[3]\n\n\t";
		cin>>op;
		espacio();
		switch(op){
			case '1':{
				Op_basicas();
				break;
			}
			case '2':{
				Op_cientificas();
				break;
			}
			case '3':{
				cout<<"\t << CERRANDO CALCULADORA ";
				getch();
				break;
			}
			default:{
				cout<<"\t >> FUERA DE RANGO "<<endl;
				cout<<"\t << VULVA A INGRESAR LA OPCI�N ";
				getch();
				break;
			}
		}
	limpiar();	
	}while(op!='3');	
}

void Op_basicas(){
	cin.ignore(100,'\n');
	float a,b,resultado;
	char aux;
	limpiar();
	do{
		system("COLOR 90");
		espacio();
		Membrete();
		espacio();
		cout<<"\t >> SUMA...............[1]"<<endl;
		cout<<"\t >> RESTA..............[2]"<<endl;
		cout<<"\t >> MULTIPLICACI�N.....[3]"<<endl;
		cout<<"\t >> DIVISI�N...........[4]"<<endl;
		cout<<"\t << VOLVER.............[5]\n\n\t";
		cin>>aux;
		espacio();
		switch(aux){
			case '1':{
				limpiar();
				suma(a,b,&resultado);
				espacio();
				cout<<"\t La operaci�n Suma da como resultado: " <<resultado;
				break;
			}
			case '2':{
				limpiar();
				resta(a,b,&resultado);
				espacio();
				cout<<"\t La operaci�n Resta da como diferencia: " <<resultado;
				break;
			}
			case '3':{
				limpiar();
				multiplicacion(a,b,&resultado);
				espacio();
				cout<<"\t La operaci�n Multiplicaci�n da como producto: " <<resultado;
				break;
			}
			case '4':{
				limpiar();
				division(a,b,&resultado);
				espacio();
				cout<<"\t La operaci�n Divisi�n da como cociente: " <<resultado;
				break;
			}
			case '5':{
				cout<<"\t << REGRESANDO AL MEN� ";
				break;
			}
			default:{
				cout<<"\t >> FUERA DE RANGO "<<endl;
				cout<<"\t << VULVA A INGRESAR LA OPCI�N ";
				break;
			}	
		}
		getch();
		limpiar();
	}while(aux!='5');
}

void suma(float a,float b,float *resultado){
	espacio();
	Membrete();
	cout<<"\n\t SUMA: ";
	espacio();
	cout<<"\t Ingresa el Primer n�mero: ";
    a=letra_Numero();
    espacio();
    cout<<"\t Ingresa el Segundo n�mero: ";
    b=letra_Numero();
	*resultado=a+b;
}

void resta(float a,float b,float *resultado){
	espacio();
	Membrete();
	cout<<"\n\t RESTA: ";
	espacio();
	cout<<"\t Ingrese el Minuendo: ";
	a=letra_Numero();
	espacio();
	cout<<"\t Ingrese el Sustraendo: ";
	b=letra_Numero();
	*resultado=a-b;
}

void multiplicacion(float a,float b, float *resultado){
	espacio();
	Membrete();
	cout<<"\n\t MULTIPLICACI�N: ";
	espacio();
	cout<<"\t Ingrese el Primer n�mero: ";
	a=letra_Numero();
	espacio();
	cout<<"\t Ingrese el Segundo n�mero: ";
	b=letra_Numero();
	*resultado=a*b;
}

void division(float a, float b,float *resultado){
	espacio();
	Membrete();
	cout<<"\n\t DIVISI�N: ";
	espacio();
	cout<<"\t Ingrese el Dividendo: ";
	a=letra_Numero();
	espacio();
	do{
		cout<<"\t Ingrese el Divisor: ";
		b=letra_Numero();
		if(b==0){
		cout<<"\n\t El Divisor es Cero."<<endl;
		cout<<"\t Divisi�n inv�lida."<<endl;
		cout<<"\t Ingrese un valor distinto a cero. \n\n";
		}	
	}while(b==0);
	*resultado=a/b;
}

void Op_cientificas(){
	cin.ignore(100,'\n');
	float a,b,resultado;
	char aux;
	limpiar();
	do{
		system("COLOR D0");
		espacio();
		Membrete();
		espacio();
		cout<<"\t >> RA�Z CUADRADA........[1]"<<endl;
		cout<<"\t >> VALOR ABSOLUTO.......[2]"<<endl;
		cout<<"\t >> POTENCIA.............[3]"<<endl;
		cout<<"\t >> SENO.................[4]"<<endl;
		cout<<"\t >> COSENO...............[5]"<<endl;
		cout<<"\t >> TANGENTE.............[6]"<<endl;
		cout<<"\t << VOLVER...............[7]\n\n\t";
		cin>>aux;
		espacio();
		switch(aux){
			case '1':{
				limpiar();
				raiz2(a,&resultado);
				espacio();
				cout<<"\t La operaci�n ra�z cuadrada da como resultado: " <<resultado;
				break;
			}
			case '2':{
				limpiar();
				valorAbsoluto(a,&resultado);
				espacio();
				cout<<"\t La operaci�n Valor Absoluto da como resultado: " <<resultado;
				break;
			}
			case '3':{
				limpiar();
				Potencia(a,b,&resultado);
				espacio();
				cout<<"\t La operaci�n Potencia da como resultado: " <<resultado;
				break;
			}
			case '4':{
				limpiar();
				Seno(a,&resultado);
				espacio();
				cout<<"\t La Funci�n Seno da como resultado: " <<resultado;
				break;
			}
			case '5':{
				limpiar();
				Coseno(a,&resultado);
				espacio();
				cout<<"\t La Funci�n Coseno da como resultado: " <<resultado;
				break;
			}
			case '6':{
				limpiar();
				Tangente(a,&resultado);
				espacio();
				cout<<"\t La Funci�n Tangente da como resultado: " <<resultado;
				break;
			}
			case '7':{
				cout<<"\t << REGRESANDO AL MEN� ";
				break;
			}
			default:{
				cout<<"\t >> FUERA DE RANGO "<<endl;
				cout<<"\t << VULVA A INGRESAR LA OPCI�N ";
				break;
			}	
		}
		getch();
		limpiar();
	}while(aux!='7');
}

void raiz2(float a,float *resultado){
	espacio();
	Membrete();
	cout<<"\n\t RA�Z CUADRADA: ";
	espacio();
	cout<<"\t Ingrese un n�mero para saber su Ra�z Cuadrada: ";
	a=letra_Numero();
	*resultado=sqrt(a);
}

void valorAbsoluto(float a,float *resultado){
	espacio();
	Membrete();
	cout<<"\n\t VALOR ABSOLUTO: ";
	espacio();
	cout<<"\t Ingrese un n�mero para saber su Valor Absoluto: ";
	a=letra_Numero();
	*resultado=fabs(a);
}

void Potencia(float a,float b,float *resultado){
	espacio();
	Membrete();
	cout<<"\n\t POTENCIA: ";
	espacio();
	cout<<"\t Ingrese la Base de la Potencia: ";
	a=letra_Numero();
	espacio();
	cout<<"\t Ingrese la Exponente de la Potencia: ";
	b=letra_Numero();
	*resultado=pow(a,b);
}

void Seno(float a,float *resultado){
	float aux;
	espacio();
	Membrete();
	cout<<"\n\t FUNCI�N SENO: ";
	espacio();
	cout<<"\t Ingrese un valor en Grados para saber su Funci�n Seno: ";
	aux=letra_Numero();
	a=aux*M_PI/180; // N�mero M_PI=3.141592
	*resultado=sin(a);
}

void Coseno(float a,float *resultado){
	float aux;
	espacio();
	Membrete();
	cout<<"\n\t FUNCI�N COSENO: ";
	espacio();
	cout<<"\t Ingrese un valor en Grados para saber su Funci�n Coseno: ";
	aux=letra_Numero();
	a=aux*M_PI/180; // N�mero M_PI=3.141592
	*resultado=cos(a);
}

void Tangente(float a,float *resultado){
	float aux;
	espacio();
	Membrete();
	cout<<"\n\t FUNCI�N TANGENTE: ";
	espacio();
	cout<<"\t Ingrese un valor en Grados para saber su Funci�n Tangente: ";
	aux=letra_Numero();
	a=aux*M_PI/180; // N�mero M_PI=3.141592
	*resultado=tan(a);
}
