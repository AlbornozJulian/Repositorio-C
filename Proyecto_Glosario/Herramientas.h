#include <iostream>
#include <conio.h>
#include <cstring> 
#include <clocale>
#include <windows.h>

using namespace std;

float letra_Numero(){
	cin.ignore(100,'\n');
	float num;
	while (true) {
	    cin>>num;
	    if (cin.fail()) {
	        cin.clear(); // Limpia el estado de error
	        cin.ignore(1000,'\n'); // Ignora los caracteres en el buffer hasta el siguiente salto de línea
	        cout<<"\n\t >> Entrada no válida. "<<endl;
	        cout<<"\t << No ingrese una letra, ingrese un número: ";
	    } else {
	        break; // Salir del bucle si la entrada es válida
	    }
	}
	return num;
}

void espacio3(){
	for(int i=0;i<3;i++){
		cout<<"\n";	
	}
}

void espacio15(){
	for(int i=0;i<15;i++){
		cout<<"\n";	
	}
}

void limpia(){
	system("cls");
}

void Maximizar(){
	// Configurar la consola en modo pantalla completa
    HWND hwnd = GetConsoleWindow(); // Obtiene el handle de la ventana de la consola
    ShowWindow(hwnd, SW_MAXIMIZE);  // Maximiza la ventana de la consola
}

void Spanish(){
	// LC_TYPE afecta los caracteres de la función
	setlocale(LC_CTYPE,"Spanish"); // Librería clocale
}

void desactivar_Maximizar(){
	HWND consoleWindow;
	consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow,GWL_STYLE,GetWindowLong(consoleWindow,GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

void gotoxy(int x,int y){
	HANDLE hcon;
	hcon=GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X=x;
	dwPos.Y=y;
	SetConsoleCursorPosition(hcon,dwPos);
}

void centrar_Texto(const char *texto,int y){
	int longitud=strlen(texto);
	gotoxy(75-(longitud/2),y);cout<<texto;
}

void Barra(){
	// Barra de carga
	int i;
	centrar_Texto("<<:: C A R G A N D O  M E N U ::>>", 30);
	for(i=3;i<=150;i++){
		gotoxy(i,32);cout<<static_cast<char>(177);
	}
	for(i=3;i<=150;i++){
		gotoxy(i,32);cout<<static_cast<char>(219);
		Sleep(35);//Milisegundos 1000==1 segundo
	}
}
