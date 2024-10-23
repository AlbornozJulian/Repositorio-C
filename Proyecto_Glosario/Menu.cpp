/*Situación Problemática: Se necesita un programa donde se pueda cargar definiciones de palabras que desconozcan los alumnos de una escuela X. */

#include <iostream>
#include <conio.h>
#include <clocale>
#include <windows.h>
#include <string.h>
#include <fstream>
#include <map>
#include "Herramientas.h"
#include "Creditos.h"
#include "Menu.h"
#include "Bienvenida.h"

using namespace std;

void Menu();
void nombre_Archivo(string &nombreArchivo);
void cargarGlosario(string &nombreArchivo);
void ingresarPalabra_Archivo();
void mostrar_Archivo();
void buscarPalabra_Archivo();
void eliminarPalabra_Archivo();
void guardarGlosario_Archivo(string &);

map<string, string> texto;
string palabra="",definicion="",nombreArchivo = "";

int main(){
	Maximizar();
	desactivar_Maximizar();
	system("color F0");
	espacio15();
	Bienvenida();
	Menu();
	getch();
	return 0;
}

void Menu(){
	char op;
	nombre_Archivo(nombreArchivo);
	getch();
	limpia();
	Spanish();
	do{
		system("color B0");
		espacio3();
		Menu_principal();
		espacio3();
		cout<< "\n\t 1) Ingresar Nueva Palabra \n\t 2) Mostrar Glosario \n\t 3) Buscar Palabra \n\t 4) Eliminar Palabra \n\t 5) Salir"<<endl;
		cout<< "\n\t Opción: ";
		cin>>op;
		switch(op){
			case '1':{
				limpia();
				system("color 97");
				espacio3();
				ingresarPalabra_Archivo();
				guardarGlosario_Archivo(nombreArchivo);
				break;
			}
			case '2':{
				limpia();
				system("color 97");
				espacio3();
				mostrar_Archivo();
				break;
			}
			case '3':{
				limpia();
				system("color 97");
				espacio3();
				buscarPalabra_Archivo();
				break;
			}
			case '4':{
				limpia();
				system("color 97");
				espacio3();
				eliminarPalabra_Archivo();
				guardarGlosario_Archivo(nombreArchivo);
				break;
			}
			case '5':{
				guardarGlosario_Archivo(nombreArchivo);
				limpia();
				system("color 97");
				espacio3();
				Creditos_Alumno();
				espacio3();
				cout<<"\n\t Cerrando Programa"<<endl;
				break;
			}
			default:{
				cout<<"\n\t Se ingreso una opción incorrecta... \n\t Vuelva a ingresar la opción."<<endl;
				break;
			}
		}
	getch();
	limpia();	
	}while(op!='5');
}

// Función para ingresar el nombre y ubicación del Archivo
void nombre_Archivo(string &nombreArchivo){
	char aux;
	getch();
	limpia();
	system("color 97");
	espacio3();
	Spanish();
	do{
		limpia();
		cout<<"\n\t <::Configuración del Archivo::> \n\n\t 1_ Nombre y Guardado por defecto. \n\t 2_ Ingresar Nombre y Dirección."<<endl;
		cout<< "\n\t Opción: ";
		cin>>aux;
		switch(aux){
			case '1':{
				nombreArchivo = "Glosario.txt";
				cout<<"\n\t El Archivo se guardara con el nombre: "<<nombreArchivo<<"."<<endl;
				break;
			}
			case '2':{
				cin.ignore();
				cout<<"\n\t Ingrese el nombre del archivo y la posición donde se guardara: \n\t Por ejemplo: 'C://Users//albor//Downloads//Diccionario.txt' (No olvidar: '.txt')"<<endl;
				cout<<"\n\t Nuevo nombre: ";
				getline(cin,nombreArchivo);
				cout<<"\n\t El Archivo se guardara con el nombre y en la posición: "<<nombreArchivo<<"."<<endl;
				break;
			}
			default:{
				cout<<"\n\t Se ingreso una opción incorrecta... \n\t Vuelva a ingresar la opción."<<endl;
				getch();
				limpia();
				break;
			}
		}
		cin.ignore(1000,'\n');
		cout<<"\n\t ¿Esta conforme con la configuración? [S/N]: ";
		cin>>aux;
	}while((aux == 'N')||(aux == 'n'));
	cargarGlosario(nombreArchivo);
	setlocale(LC_CTYPE,"C");// Establecer la configuracion por defecto
	Barra();
}
// Función para cargar el glosario desde un archivo
void cargarGlosario(string &nombreArchivo){
    ifstream archivo(nombreArchivo.c_str());// if de Imput para la lectura
    if(archivo.is_open()){// Comprobamos si el archivo se abrió correctamente
        string linea, palabra, definicion;
        while(getline(archivo, linea)){
            size_t pos = linea.find(": ");// Buscamos la posición de ": " (delimitador entre palabra y definición)
            if(pos != string::npos) {// Si encontramos el delimitador
                palabra = linea.substr(0, pos);// Extraemos la palabra (lo que está antes de ": ")
                definicion = linea.substr(pos + 2);// Extraemos la definición (lo que está después de ": ")
                texto[palabra] = definicion;// Almacenamos la palabra y definición en el map
            }
        }
        archivo.close();// Cerramos el archivo después de leer
    }else{
        cout<<"\n\t No se pudo abrir el archivo, comenzando con un glosario vacío."<<endl;
        getch();
    }
}
// Función para ingresar las palabras
void ingresarPalabra_Archivo(){
	char aux;
	do{
		limpia();
		cout<<"\n\t <::Ingresar Palabra::> "<<endl;
		cin.ignore();
		cout<<"\n\t Ingrese la palabra en el Glosario: ";
		getline(cin,palabra);
		if(texto.find(palabra) != texto.end()) {
        	cout<<"\n\t La palabra '" << palabra <<"' ya está en el glosario con la definición: "<<texto[palabra]<<endl;
    	}else{
        	cout<<"\n\t Ingrese la definición: ";// Si la palabra no está, se solicita la definición y añadirla
        	getline(cin, definicion);
        	texto[palabra] = definicion;
    	}
		cout<<"\n\t ¿Desea ingresar otra palabra? [S/N]: ";
		cin>>aux;
	}while((aux == 'S')||(aux == 's'));
	espacio3();
	cout<<"\n\t Regresando al Menú..."<<endl;
}
// Función para mostar las palabra cargadas
void mostrar_Archivo(){
	if (!texto.empty()) {
        cout<<"\n\t <::Glosario Actual::> "<<endl;
        for(map<string, string>::iterator it = texto.begin(); it != texto.end(); ++it) {
            cout<<"\n\t"<<it->first<< ": " <<it->second<<endl;
        }
    } else {
        cout<<"\n\t El glosario está vacío."<<endl;
    }
    espacio3();
    cout<<"\n\t Regresando al Menú..."<<endl;
}
// Función para buscar la definición de una palabra
void buscarPalabra_Archivo(){
	string Buscar;
	cout<<"\n\t <::Buscar Palabra::> "<<endl;
	cin.ignore();
    cout<<"\n\t Ingrese la palabra que desea Buscar: ";
    getline(cin,Buscar);
    map<string, string>::iterator it = texto.find(Buscar);
    if(it != texto.end()){
        cout<<"\n\t Definición de '"<<Buscar<<"': "<<it->second<<endl;
    }else{
        cout<<"\n\t La palabra '"<<Buscar<<"' no está en el glosario."<<endl;
    }
    espacio3();
    cout<<"\n\t Regresando al Menú..."<<endl;
}
// Función para eliminar una palabra del glosario
void eliminarPalabra_Archivo(){
	string Eliminar;
	cout<<"\n\t <::Eliminar Palabra::> "<<endl;
	cin.ignore();
    cout<<"\n\t Ingrese la palabra que desea Eliminar: ";
    getline(cin,Eliminar);
    if(texto.erase(Eliminar)){
        cout<<"\n\t La palabra '"<<Eliminar<<"' fue eliminada del glosario."<<endl;
    }else{
        cout<<"\n\t La palabra '"<<Eliminar<<"' no está en el glosario."<<endl;
    }
    espacio3();
    cout<<"\n\t Regresando al Menú..."<<endl;
}
// Función para Guardar todo lo cargado en la estructura Map dentro del Archivo
void guardarGlosario_Archivo(string &nombreArchivo){
	ofstream archivo(nombreArchivo.c_str(),ios::out);// of de ouput para escribir 
	// out: si archivo existe lo reemplaza y si no existe lo crea desde cero
    if(archivo.is_open()){
        archivo<<"\n\t <::Glosario::>"<<endl;
        for(map<string, string>::iterator it = texto.begin(); it != texto.end(); ++it) {
            archivo<<it->first<< ": " <<it->second<<endl;
        }
        archivo.close();// Cerramos el archivo
        cout<<"\n\t El glosario se ha guardado correctamente en: "<<nombreArchivo<<"."<<endl;
    } else {
        cout<<"\n\t No se pudo abrir el archivo."<<endl;
		exit(1);
    }
} 
