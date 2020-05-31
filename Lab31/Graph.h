#pragma once
#include <iostream>
#include <vector>
#include "glut.h"
#include <string>
using namespace std;

extern int maxSize;
extern int WinW, WinH, R;

template <typename T>
class Graph {
public:
	Graph();
	~Graph();
	int getVertPos(const T& vertex); 
	bool isEmpty(); // ����?
	bool isFull(); // ��������?
	int getAmountOfVerts(); // ���������� ������
	int getAmountOfEdges(); // ���������� �����
	int getWeight(const T& vertex1, const T& vertex2); // ��������� ���� 
	vector<T> getNbrs(const T& vertex); // ������� ������ �������
	void insertVertex(const T& vertex); // ���������� �������
	void insertEdge(const T& vertex1, const T& vertex2,int weight); // ���������� ����� 
	void print(); // ������� ��������� 
	void drawGraph(); // ��������� �����
	void search(); // ������� ������������
private:
	T adjMatrix[20][20];
	vector<T> vertList;
};

Graph<int> makeGraph();
extern struct vertCoord;
struct vertCoord {
	int x, y;
};

extern vertCoord vertC[20];
void setCoord(int i, int n);
void drawCircle(int x, int y, int R);
void drawText(int num, int x1, int y1);
void drawVertex(int n);
void drawDirect(int x0, int y0, int x1, int y1);
void drawLine(int text, int x0, int y0, int x1, int y1);
void reshape(int w, int h);
void display();

extern Graph <int> graph;
void searchPath();
void inputPath(int[20][20]);

template <typename T>
void Graph<T>::search() {
	int matrix[20][20];
	for (int i = 1; i <= 6; i++) 
		for (int j = 1; j <= 6; j++) 
			matrix[i][j] = this->adjMatrix[i - 1][j - 1];
	inputPath(matrix);
	searchPath();
}

template <typename T>
Graph<T>::Graph() {
	for (int i = 0; i < maxSize; ++i) {
		for (int j = 0; j < maxSize; ++j) {
			this->adjMatrix[i][j] = 0;
		}
	}
}

template <typename T>
Graph<T>::~Graph() { }

template <typename T>
int Graph<T>::getVertPos(const T& vertex) {
	for (int i = 0; i < this -> vertList.size(); ++i) {
		if (this -> vertList[i] == vertex) return i;
	}
	return -1;
}

template <typename T>
bool Graph<T>::isEmpty() {
	if (this->vertList.size() != 0) return false;
	else return true;
}

template <typename T>
bool Graph<T>::isFull() {
	return (vertList.size() == maxSize);
}

template <typename T>
int Graph<T>::getAmountOfVerts() {
	return this -> vertList.size();
}

template<class T>
int Graph<T>::getAmountOfEdges() {
	int amount = 0; // �������� �������
	if (!this->isEmpty()) { // ���������, ��� ���� �� ����
		for (int i = 0, vertListSize = this->vertList.size(); i < vertListSize; ++i) {
			for (int j = 0; j < vertListSize; ++j) {
				if (this->adjMatrix[i][j] == 1) // ������� ����
					amount += 1; // ������� ���������� ����
			}
		}
		return amount; // ���������� ���������� ����
	} else return 0; // ���� ���� ����, ���������� 0
}

template <typename T>
int Graph<T>::getWeight(const T& vertex1, const T& vertex2) {
	if (!this->isEmpty()) {
		int vertPos1 = getVertPos(vertex1);
		int vertPos2 = getVertPos(vertex2);
		return adjMatrix[vertPos1][vertPos2];
	} else return 0;
}

template<class T>
std::vector<T> Graph<T>::getNbrs(const T& vertex) {
	std::vector<T> nbrsList; // �������� ������ �������
	int pos = this->getVertPos(vertex); /* ���������� ������� vertex � ������� ��������� */
	if (pos != (-1)) { /* ��������, ��� vertex ���� � ������� ��������� */
		for (int i = 0, vertListSize = this->vertList.size(); i < vertListSize; ++i) {
			if (this->adjMatrix[pos][i] != 0) /* ���������� �������*/
				nbrsList.push_back(this->vertList[i]); /* ������ ������� � ������ */
		}
	}
	return nbrsList; // ������� ������ �������
}

template <typename T>
void Graph<T>::insertVertex(const T& vertex) {
	if (!this->isFull()) {
		this->vertList.push_back(vertex);
	} else {
		cout << "���� ��������. ���������� �������� ����� �������" << endl;
		return;
	}
}

template<class T>
void Graph<T>::insertEdge(const T& vertex1, const T& vertex2, int weight) {
	if (this->getVertPos(vertex1) != (-1) && this->getVertPos(vertex2) != (-1)) {
		int vertPos1 = getVertPos(vertex1);
		int vertPos2 = getVertPos(vertex2);
		if (this -> adjMatrix[vertPos1][vertPos2] != 0) {
			cout << "����� ����� ����� ��������� ��� ����������" << endl;
			return;
		} else {
			this -> adjMatrix[vertPos1][vertPos2] = weight;
		}
	}
	else {
		cout << "����� ������ (��� ����� �� ���) ��� � ����� " << endl;
		return;
	}
}

template <typename T>
void Graph<T>::print() {
	if (!this->isEmpty()) {
		cout << "������� ��������� �����:" << endl;
		cout << " " << " ";
		for (int i = 0, vertListSize = this -> vertList.size(); i < vertListSize; ++i) {
			cout << "  " << this -> vertList[i] << "  ";
		}
		cout << endl;
		for (int i = 0, vertListSize = this->vertList.size(); i < vertListSize; ++i) {
			cout << this -> vertList[i] << "  ";
			for (int j = 0; j < vertListSize; ++j) {
				cout << "  " << this -> adjMatrix[i][j] << "  ";
			}
			cout << endl;
		}
	}
	else cout << "���� ����" << endl;
}

template <typename T>
void Graph<T>::drawGraph() {
	int n = vertList.size();
	for (int i = 0; i < n; ++i) { setCoord(i, n); }

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int a = adjMatrix[i][j];
			if (a != 0) { drawLine(a, vertC[i].x, vertC[i].y, vertC[j].x, vertC[j].y); }
		}
	}
	drawVertex(n);
}


