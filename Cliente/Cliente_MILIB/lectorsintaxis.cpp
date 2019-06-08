#include "lectorsintaxis.h"
using namespace std;

LectorSintaxis::LectorSintaxis(string inputIDE){
    this->inputIDE = inputIDE;
    this->inputSize = inputIDE.size();
    this->idError = 0;
}

string LectorSintaxis::manejarInputIDE(){
    string instruccion = obtenerInstruccion();
    if(instruccion == "INSERT"){
        instruccion = manejarInstruccionInsert();
        //qDebug()<<instruccion.c_str();
        return instruccion;
    }
}

string LectorSintaxis::obtenerInstruccion(){
    string instruccion;
    string caracterActual;
    for(int posicion = 0; posicion < inputSize; posicion++){
        caracterActual = inputIDE[posicion];
        if(caracterActual != " ")
            instruccion += caracterActual;
        else{
            inputIDE = inputIDE.substr(posicion+1, inputSize-posicion);
            inputSize = inputIDE.size();
            return instruccion;
        }
    }
    idError = 1;
    return "ERROR";
}

string LectorSintaxis::manejarInstruccionInsert(){
    string verificarSintaxis = inputIDE.substr(0, 13);
    if(verificarSintaxis != "INTO METADATA"){
        idError = 2;
        return "ERROR";
    }
    inputIDE = inputIDE.substr(13, inputIDE.size()-13);
    inputSize = inputIDE.size();
    string columnas = obtenerColumnasInsert();
    string valores = obtenerValoresInsert();
    qDebug()<<"COLUMNAS: "<<columnas.c_str();
    qDebug()<<"VALORES: "<<valores.c_str();
    return columnas + "-" + valores;
}

string LectorSintaxis::obtenerContenidoTupla(){
    string contenido;
    string caracterActual;
    for(int posicion = 0; posicion < inputSize; posicion++){
        caracterActual = inputIDE[posicion];
        if(caracterActual != " "){
            if(caracterActual != ")")
                contenido += caracterActual;
            else{
                inputIDE = inputIDE.substr(posicion+1, inputSize-posicion);
                inputSize = inputIDE.size();
                return contenido;
            }
        }
    }
    return "ERROR";
}


string LectorSintaxis::obtenerColumnasInsert(){
    string caracterActual;
    for(int posicion = 0; posicion < inputSize; posicion++){
        caracterActual = inputIDE[posicion];
        if(caracterActual != " "){
            if(caracterActual == "("){
                inputIDE = inputIDE.substr(posicion+1, inputSize-posicion);
                inputSize = inputIDE.size();
                break;
            }else{
                idError = 3;
                return "ERROR";
            }
        }
    }

    string nombreColumnas = obtenerContenidoTupla();
    if(nombreColumnas == "ERROR")
        idError = 4;
    return nombreColumnas;
}

string LectorSintaxis::obtenerValoresInsert(){
    string caracterActual;
    string verificarSintaxis;
    for(int posicion = 0; posicion < inputSize; posicion++){
        caracterActual = inputIDE[posicion];
        if(caracterActual != " " && caracterActual != "\n"){
            if(caracterActual == "("){
                inputIDE = inputIDE.substr(posicion+1, inputSize-posicion);
                inputSize = inputIDE.size();
                break;
            }else
                verificarSintaxis += caracterActual;
        }
    }
    if(verificarSintaxis != "VALUES"){
        idError = 5;
        return "ERROR";
    }

    string valores = obtenerContenidoTupla();
    if(valores == "ERROR")
        idError = 5;
    return valores;
}

//INSERT INTO METADATA (NOMBRE, ARTISTA, DURACION, ALBUM)
//VALUES ("Karma Police", "Radiohead", "4:27", "OK Computer")
