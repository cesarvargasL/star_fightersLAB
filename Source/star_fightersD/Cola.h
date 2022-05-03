// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 *
 */
template<typename T> class Cola;

template<typename T>
class Nodo {
	friend Cola<T>;
private:
	T valor;
	Nodo<T>* siguiente;

public:
	Nodo(T _valor, Nodo<T>* _siguiente = nullptr) {
		valor = _valor;
		siguiente = _siguiente;
	}
};


//class STARFIGHTER_API TCola
//{
//public:
//	TCola();
//	~TCola();
//};

template<class T>
class Cola {
private:
	Nodo<T>* primero;
	Nodo<T>* ultimo;
public:
	Cola() : primero(nullptr), ultimo(nullptr) {}
	~Cola();
	void Push(T _valor);
	T Pop();
};

template<class T>
Cola<T>::~Cola() {
	while (primero) {
		Pop();
	}
}

template<class T>
void Cola<T>::Push(T _valor) {
	Nodo<T>* nodoNuevo;
	nodoNuevo = new Nodo<T>(_valor);

	if (ultimo) {
		ultimo->siguiente = nodoNuevo;
	}

	ultimo = nodoNuevo;

	if (!primero) {
		primero = nodoNuevo;
	}
}

template<class T>
T Cola<T>::Pop() {
	Nodo<T>* nodoActual;
	T valorNodo;

	nodoActual = primero;
	if (!nodoActual) {
		return 0;
	}

	primero = nodoActual->siguiente;
	valorNodo = nodoActual->valor;
	delete nodoActual;

	if (!primero) {
		ultimo = nullptr;
	}

	return valorNodo;
}
