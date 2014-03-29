#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <time.h>
#include <string.h>
#include <cstdlib>

using namespace std;

string QuitarTildes(string cadena)
{
    string vocal_sin="aaaaaaeeeeiiiioooouuuc",vocal_con="ãàáäâèéëêìíïîòóöôùúüûç";
    int i,j;
    for (i=0;i<cadena.size();i++)
        for (j=0;j<22;j++)
            if (vocal_con[j]==cadena[i])
                cadena[i]=vocal_sin[j];
    return cadena;
}
//metodo split para separar delimitado por un caracter
vector<string> Split(string palabra, string separador)
{
    vector<string> palabras;
    vector<size_t> found;
    vector<size_t> found2;
    size_t j=0;
    size_t dato;
    size_t termino=-1;
    size_t comienzo=0;
    for(size_t i=0;i<=palabra.size();i++)
    {
    j++;
    if(palabra[i] ==separador[0])
    {
        found.push_back(j);
        j=0;
    }
    }
    found.push_back(j);
    while (!found.empty())
    {
        dato = found.back();
        found2.push_back(dato);
        found.pop_back();
    }
    while (!found2.empty())
    {
        termino = found2.back();
        found2.pop_back();
        palabras.push_back(palabra.substr(comienzo,termino-1));
        comienzo = termino+comienzo;
    }

    return palabras;
}

string Estandarizar (string palabra)
{
    int i , largo=palabra.size();
    for(i=0;i<largo;i++)
    {
        palabra[i]=tolower(palabra[i]);
    }
    return palabra;
}

string Saca_Comillas(string palabra){
    int desde = 1;
    int hasta = (palabra.size())-2;
    palabra = palabra.substr(desde,hasta);

    return palabra;
}

void Total_Ingresos(void)
{
     long TotalIngre =0,Ingreso;
     string delimitador=";";
     vector<string> datos;
     string precio, str;
     ifstream leer_fich("ventas.csv");
     if ( !leer_fich){
        cout << "No se ha podido abrir el fichero";
      }
     while(!leer_fich.eof())
     {
        /* aqui va la extraccion de ingreso y transformacion de este en int */
          getline(leer_fich,str);
          datos=Split(str,delimitador);
          precio=Saca_Comillas(datos[2]);
          Ingreso = atoi(precio.c_str());
          /* suma de todos los ingresos*/
          TotalIngre=TotalIngre+Ingreso;

     }
     cout<<flush;/* limpiar el buffer*/
     leer_fich.close(); /*cerrar el fichero*/
     cout<<TotalIngre;
}

bool Existe(string palabra)
{
    int i;
    vector<string> Tiendas;
    Tiendas.push_back("falaferia");
    Tiendas.push_back("cencosux");
    Tiendas.push_back("replay");
    Tiendas.push_back("porahi");
    for(i=0;i<4;i++)
    {
        if(palabra== Tiendas[i])
        {
           return true;
        }


    }
    return false;
}
void Ingr_Mens(string palabra)
{
    long IngrMen[12];
    long i, Ingreso, mes;
    vector<string> fecha,datos;
    string precio, str, tienda,fechaCompleta,delimitador=";",delimitador2="-";
     vector<string> NombreMes;
     NombreMes.push_back("Enero");
     NombreMes.push_back("Febrero");
     NombreMes.push_back("Marzo");
     NombreMes.push_back("Abril");
     NombreMes.push_back("Mayo");
     NombreMes.push_back("Junio");
     NombreMes.push_back("Julio");
     NombreMes.push_back("Agosto");
     NombreMes.push_back("Septiembre");
     NombreMes.push_back("Octubre");
     NombreMes.push_back("Noviembre");
     NombreMes.push_back("Diciembre");
    for(i=0;i<12;i++)
    {
        IngrMen[i]=0;
    }
    string TiendaIngresada = QuitarTildes(Estandarizar(palabra));
//cout<<TiendaIngresada;
    if(Existe(TiendaIngresada)==true)
    {
        ifstream leer_fich("ventas.csv");
        if ( !leer_fich)
        {
            cout << "No se ha podido abrir el fichero";
        }
        while(!leer_fich.eof())
        {
            /*extraer los tres datos y limpiarlos*/
            getline(leer_fich,str);
            datos=Split(str,delimitador);
            tienda=Saca_Comillas(datos[0]);
            fechaCompleta=Saca_Comillas(datos[1]);
            precio=Saca_Comillas(datos[2]);
            Ingreso = atoi(precio.c_str());
            fecha = Split(fechaCompleta,delimitador2);
            mes = atoi(fecha[1].c_str());
            string TiendaDoc = Estandarizar(tienda);
            if(TiendaIngresada==TiendaDoc)
            {
                IngrMen[mes-1]=IngrMen[mes-1]+Ingreso;
            }
        }
        for(i=0;i<12;i++)
        {
            cout<<NombreMes[i]<<" : "<<IngrMen[i]<<endl;
        }
    }else
        cout<<"Tienda Ingresada no existe"<<endl;
}

int main(int argc, char *argv[])
{
    argc=2;
    argv[1]="-v";
    if(argc > 1)
    {
       if (strcmp(argv[1], "-s") == 0)/*leo la segunda posicion de los argumentos recibidos*/
        {
            if(strcmp(argv[2], "ventas.csv")==0) /*valido el argumento con el nombre del archivo*//*quizas este de mas esto*/
            {
                if (argc == 3)/*corroboro q se haya enviado cantidad correcta de argumennto*/
                {

                    cout<<"La suma total de todas las tiendas es: "; //funcion suma total*/
                    Total_Ingresos();
                }else
                    cout<<"Falto la ruta del archivo"<<endl;
            }else
                cout<<"Mal ingresada la ruta del archivo"<<endl;
        }else
            if (strcmp(argv[1], "-a") == 0)
            {
                if (argc == 4)
                {
                    if(strcmp(argv[3], "ventas.csv")==0)
                    {
                      /*Suma mensual de la Tienda (argv[3])*/
                      string palabra = argv[2];
                      Ingr_Mens(palabra);
                    }else
                        cout<<"Mal ingresada la ruta del archivo"<<endl;
                }else
                    cout<<"Mal ingresada la cantidad de parametros"<<endl;
            }else
                if (strcmp(argv[1], "-v") == 0) /*leo segunda posicion de argumentos enviados*/
                {
                    if (argc == 2)
                    {
                        cout << "Integrantes Ing. Software" << endl;
                        cout << "Diego Hernandez Garcia" << endl;
                        cout << "Miguel Nuñez Gajardo" << endl;
                        cout << "Roberto Oñate Piedras" << endl;
                        cout << "Fecha de compilacion: " << __DATE__ << " " << __TIME__ << endl;
                    }else
                        cout<<"Mal ingresada la cantidad de parametros"<<endl;
                }else
                    cout << "Opcion invalida" << endl;

    }
    else{
        cout << "Tiene que pasarle algun parametro!" << endl;
        system("pause");
    }
    return 0;
}

