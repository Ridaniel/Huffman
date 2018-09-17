#include <iostream>
#include<algorithm>
#include<string>
#include<map>
#include<functional>
#include <set>
#include <vector>
#include<iterator>
using namespace  std;
using namespace System;
//Nuevo Diccionario
char diccionario[90] =
{
	'0','1','2','3','4','5','6','7','8','9'
	,'A','B','C','D','E','F',
	'G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U',
	'V','W','X','Y','Z','a','b','c','d',
	'e','f','g','h','i','j','k','l','m','n','o','p','q','r','s',
	't','u','v','w','x','y','[','\\',']','^','_','`',
	':',';','<',' = ','>',' ? ','@',' ','!','"','#','$','%','&','\'','(',')','*',' + ',',',
	' - ','.',' / '
};
//diccionario puesto en un mapa
map< char, int, std::less<int>>darreglado;
//Nodo usado para el arbol binario
struct Nodo
{
	pair<char, int> val;
	Nodo*izq;
	Nodo*derecha;
	Nodo(pair<char, int> val)
	{
		this->val = val;
		izq = NULL;
		derecha = NULL;
	}
	Nodo()
	{
		izq = NULL;
		derecha = NULL;
	}
};

bool ordenar(Nodo *a, Nodo *b)
{
	if (a->val.second < b->val.second) return 1;
	else if (a->val.second == b->val.second)
	{
		if (darreglado.lower_bound(a->val.first)->second > darreglado.lower_bound(b->val.first)->second)return 0;

		return 1;
	}
	return 0;
};
void cmp2(vector<Nodo*>&v)
{
	Nodo *temp;
	temp = v[v.size() - 1];
	int pos = -2;
	for (int i = 0;i < v.size() - 1;i++)
	{
		if (temp->val.second == v[i]->val.second)
		{
			pos = i;
			break;
		}
	}
	if (pos == -1)pos = 0;
	if (pos == -2)pos = v.size() - 1;
	else {
		std::vector<Nodo*>::iterator it = v.begin();
		v.pop_back();
		v.insert(it + pos, temp);
	}
	for (int i = 0;i < v.size();i++)
		cout << v[i]->val.first << " ";
};
void verArbol(Nodo*arbol, map<char, string>&s, string rec = "")
{
	if (arbol->izq == NULL && arbol->derecha == NULL)
	{
		s[arbol->val.first] = rec;
		cout << rec << "->";
		if (arbol->val.first == ' ')cout << "espacio";
		else
			cout << arbol->val.first;
		cout << endl;
	}
	if (arbol->izq != NULL)
		verArbol(arbol->izq, s, rec += "0");
	rec.erase(rec.begin() + rec.size() - 1);
	if (arbol->derecha != NULL)
		verArbol(arbol->derecha, s, rec += "1");
	return;
}
string comprimir(string frase, map<char, string>s)
{
	string temp = "";
	for (int i = 0;i < frase.size();i++)
		temp += s.lower_bound(frase[i])->second;
	return temp;
}
string descomprimir(string comprimido, Nodo*arbol)
{
	Nodo *temp2 = arbol;
	string temp = "";
	for (int i = 0;i < comprimido.size();i++)
	{
		if (comprimido[i] == '0')
		{
			temp2 = temp2->izq;
			if (temp2->izq == nullptr && temp2->derecha == nullptr)
			{
				if (temp2->val.first == '\n')
					temp += " ";
				else
					temp += temp2->val.first;
				temp2 = arbol;
			}
		}
		else
		{
			temp2 = temp2->derecha;
			if (temp2->izq == nullptr && temp2->derecha == nullptr)
			{
				if (temp2->val.first == '\n')
					temp += " ";
				temp += temp2->val.first;
				temp2 = arbol;
			}
		}
	}
	return temp;
}
void generadorDiccionario()
{
	for (int i = 0;i < 90;i++)
		darreglado[diccionario[i]] = i;
}
string compresor()
{
	cin.get();
	system("cls");
	vector<Nodo* >ls;
	//estructuras usadas
	map<char, string>reconstructor;
	generadorDiccionario();
	map<char, int>letras;
	string frase;
	string reconstruir;
	getline(std::cin, frase);
	cout << frase << endl;
	//Asigna las frecuencias
	for (int i = 0;i < frase.size();i++)
	{
		if (letras.find(frase[i]) != letras.end())
			letras[frase[i]]++;
		else
			letras[frase[i]] = 1;
	}
	for (std::map<char, int>::iterator it = letras.begin();it != letras.end();it++)
	{
		cout << it->first << " " << it->second << endl;
	}
	//frase comprimida
	reconstruir = frase;
	//generar el vector con todas las letras
	for (auto it = letras.begin();it != letras.end();it++)
	{
		ls.push_back(new Nodo(make_pair(it->first, it->second)));
	}
	//ordenadas de acuerdo al diccionario
	sort(ls.begin(), ls.end(), ordenar);
	//for (int i = 0;i<ls.size();i++)
	//{
	//	cout << ls[i]->val.first << " ";
	//}
	//Comprension con huffman
	while (1)
	{
		//cout << ls[0]->val.second << " ";
		//cout << ls[1]->val.second << " ";
		Nodo *temp = new Nodo(make_pair(ls[0]->val.first, ls[0]->val.second + ls[1]->val.second));
		temp->izq = ls[0];
		temp->derecha = ls[1];
		ls.push_back(temp);
		ls.erase(ls.begin(), ls.begin() + 2);
		cmp2(ls);
		//stable_sort(ls.begin(), ls.end(),cmp2);
		if (ls.size() <= 1)break;
	}
	//
	cout << endl;
	verArbol(ls[0], reconstructor);
	cout << endl;
	cout << "Tu frase comprimida es :" << endl;
	string resultado = comprimir(reconstruir, reconstructor);
	cout << resultado;
	return resultado;
	cout << endl;
	cin.ignore();
	system("pause");
}
void descompresor()
{
	system("cls");
	vector<Nodo* >ls;
	int cantidad;
	cout << "Ingrese cantidad de caracteres diferentes :";
	cin >> cantidad;
	cout << endl << cantidad;
	map<char, string>reconstructor;
	generadorDiccionario();
	map<char, int>letras;

	string reconstruir;

	//Asigna las frecuencias
	cout << "Ingrese los caracteres y las veces que se repite " << endl;
	cout << "Ejemplo C 5" << endl;


	for (int i = 0;i < cantidad;i++)
	{
		char temp;
		int repetido;
		cin.get(temp);
		cin.ignore();
		cin >> repetido;
		cin.ignore();
		letras[temp] = repetido;
	}
	//frase comprimida
	//reconstruir = frase;	//generar el vector con todas las letras
	for (auto it = letras.begin();it != letras.end();it++)
	{
		ls.push_back(new Nodo(make_pair(it->first, it->second)));
	}
	//ordenadas de acuerdo al diccionario
	sort(ls.begin(), ls.end(), ordenar);
	//for (int i = 0;i<ls.size();i++)
	//{
	//	cout << ls[i]->val.first << " ";
	//}
	//Comprension con huffman
	while (1)
	{
		//cout << ls[0]->val.second << " ";
		//cout << ls[1]->val.second << " ";
		Nodo *temp = new Nodo(make_pair(ls[0]->val.first, ls[0]->val.second + ls[1]->val.second));
		temp->izq = ls[0];
		temp->derecha = ls[1];
		ls.push_back(temp);
		ls.erase(ls.begin(), ls.begin() + 2);
		cmp2(ls);
		//stable_sort(ls.begin(), ls.end(),cmp2);
		if (ls.size() <= 1)break;
	}
	cin.ignore();
	cout << "Ingrese la frase comprimida" << endl;
	string resultado;
	cin >> resultado;
	string descomprimido = descomprimir(resultado, ls[0]);
	cout << endl;
	cout << descomprimido << endl;;
	system("pause");
}
int main()
{
	char opcion;
	while (1)
	{
		system("cls");
		cout << "\n\n";
		cout << "\tMENU" << endl;
		cout << "\t(1)Comprimir " << endl;
		cout << "\t\(2)Descomprimir " << endl;
		cout << "\t(3)Salir " << endl;
		cout << "\t";
		cin >> opcion;
		switch (opcion)
		{
		case '1':compresor();getchar();break;
		case '2':descompresor();getchar();break;
		case '3':exit(0);break;
		default:cout << "Opcion no valida";getchar();
			break;
		}

	}

	getchar();
}
//Ricardo Daniel Iglesias Espinoza
