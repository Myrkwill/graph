#pragma once
#include "Graph.h"
#include <vector>
#include <iostream>
#include <string>
#include "glut.h"
#include <cmath>
using namespace std;

int maxSize = 20;
Graph <int> graph;
int WinW, WinH, R;
vertCoord vertC[20];

const int maxn = 100;
int n = 6; // Количество
int s = 0; // текущая сумма
int minsum; // мин сумма
int counter; // счетчик пройденных
int found;  // найден ли путь

int a[maxn][maxn]; // матрица расстояний
int m[maxn]; // Tекущий путь
int minm[maxn]; // Минимальный путь


Graph<int> makeGraph() {
	//======
	int verts[6] = { 1, 2, 3, 4, 5, 6 };
	int sourceVertexs[9] = { 1, 3, 2, 3, 1, 5, 5, 4, 4 };
	int targetVertexs[9] = { 3, 2, 6, 5, 5, 6, 4, 6, 1};
	char answers[] = { 'y', 'n', 'n', 'y', 'n', 'y', 'n', 'y', 'n' };
	int edgeWeights[9] = { 7, 28, 24, 12, 19, 16, 21, 14, 20 };
	
	//=====

	Graph<int>graph;
	int amountofVerts, amountofEdges, vertex, sourceVertex, targetVertex, edgeWeight;
	char answer;
	amountofVerts = 6;
	amountofEdges = 9;
	cout << "Введите количество вершин графа: " << amountofVerts << endl; // cin >> amountofVerts;
	cout << "Введите количество ребер графа: " << amountofEdges << endl; // cin >> amountofEdges;
	for (int i = 0; i < amountofVerts; ++i) {
		vertex = verts[i];
		cout << "Вершина: " << vertex << endl; // cin >> vertex;
		int* vertPtr = &vertex;
		graph.insertVertex(*vertPtr);
	}

	for (int i = 0; i < amountofEdges; ++i) {
		sourceVertex = sourceVertexs[i]; // Тест
		cout << "Исходная вершина: " << sourceVertex << endl; // cin >> sourceVertex;
		
		int* sourceVertPtr = &sourceVertex;
		targetVertex = targetVertexs[i];// Тест
		cout << "Конечная вершина: " << targetVertex << endl; // cin >> targetVertex;
		
		int* targetVertPtr = &targetVertex;
		edgeWeight = edgeWeights[i];// Тест
		cout << "Вес ребра: " << edgeWeight << endl; //cin >> edgeWeight;
		graph.insertEdge(*sourceVertPtr, *targetVertPtr, edgeWeight);

		answer = answers[i]; // 'y'; // test
		cout << "Есть ли обратная связь между ребрами? [y/n]: " << answer << endl; //cin >> answer;
		if (answer == 'y' || answer == 'Y') {
			graph.insertEdge(*targetVertPtr, *sourceVertPtr, edgeWeight);
		}
	}
	cout << endl;
	graph.print();
	sourceVertex = 1; // Тест
	cout << endl << "Стартовая вершина: "; cout << sourceVertex;
	graph.search();
	// int* sourceVertPtr = &sourceVertex;
	// graph.Dijsktra(*sourceVertPtr);

	return graph;
}

void setCoord(int i, int n) {
	int R_;
	int x0 = WinW / 2;
	int y0 = WinH / 2;
	if (WinW > WinH) {
		R = 5 * (WinH / 13) / n;
		R_ = WinH / 2 - R - 10;
	} else {
		R = 5 * (WinW / 13) / n;
		R_ = WinW / 2 - R - 10;
	}
	float theta = 2.0f * 3.1415926f * float(i) / float(n);
	float y1 = R_ * cos(theta) + y0;
	float x1 = R_ * sin(theta) + x0;

	vertC[i].x = x1;
	vertC[i].y = y1;
}

void drawCircle(int x, int y, int R) {
	glColor3f(1.0, 1.0, 1.0);
	float x1, y1;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; ++i) {
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y1 = R * cos(theta) + y;
		x1 = R * sin(theta) + x;
		glVertex2f(x1, y1);
	}
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	float x2, y2;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; ++i) {
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y2 = R * cos(theta) + y;
		x2 = R * sin(theta) + x;
		glVertex2f(x2, y2);
	}
	glEnd();
}

void drawText(int num, int x1, int y1) {
	GLvoid* font = GLUT_BITMAP_HELVETICA_18;
	string s = to_string(num);
	glRasterPos2i(x1 - 5, y1 - 5);
	for (int j = 0; j < s.length(); ++j) {
		glutBitmapCharacter(font, s[j]);
	}
}

void drawVertex(int n) {
	for (int i = 0; i < n; ++i) {
		drawCircle(vertC[i].x, vertC[i].y, R);
		drawText(i + 1, vertC[i].x, vertC[i].y);
	}
}

//ребро ориентированный взвешенный граф
void drawLine(int text, int x0, int y0, int x1, int y1) {
	glColor3i(0, 0, 0);
	glBegin(GL_LINES);
		glVertex2i(x0, y0);
		glVertex2i(x1, y1);
	glEnd();

	 drawText(text, (x0 + x1) / 2 + 10, (y0 + y1) / 2 + 10);
	 drawDirect(x0, y0, x1, y1);
}

void drawDirect(int x0, int y0, int x1, int y1) {
	float vx = x0 - x1;
	float vy = y0 - y1;
	float s = 1.0f / sqrt(vx * vx + vy * vy);
	vx *= s;
	vy *= s;
	x1 = x1 + R * vx;
	y1 = y1 + R * vy;

	glColor3i(0, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(x1, y1);
	glVertex2f(x1 + 10 * (vx + vy), y1 + 10 * (vy - vx));
	glVertex2f(x1 + 10 * (vx - vy), y1 + 10 * (vy + vx));
	glEnd();
}

void reshape(int w, int h) {
	WinW = w;
	WinH = h;
	glViewport(0, 0, (GLsizei)WinW, (GLsizei)WinH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (GLdouble)WinW, 0, (GLdouble)WinH);
	glutPostRedisplay();
}

void display() {
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WinW, 0, WinH);
	glViewport(0, 0, WinW, WinH);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	graph.drawGraph();
	glutSwapBuffers();
}

void inputPath(int matrix[20][20]) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			a[i][j] = matrix[i][j];
		}
	}
}

void outputPath() {
	if (found) {
		cout << "Длина пути: " << minsum << endl;
		cout << "Путь: ";
		int c = 1;
		for (int i = 1; i <= n; i++) {
			int j = 1;
			while ((j <= n) && (minm[j] != c)) j++;
			cout << j << " -> ";
			c++;
		}
		cout << minm[1] << endl;
	}
	else cout << "Путь не найден!";
}

void searchPath(int x) {
	if ((counter == n) && (a[x][1] != 0) && (s + a[x][1] < minsum)) {
		found = 1;
		minsum = s + a[x][1];
		for (int i = 1; i <= n; i++) minm[i] = m[i];
	}
	else {
		for (int i = 1; i <= n; i++) {
			if ((i != x) && (a[x][i] != 0) && (m[i] == 0) && (s + a[x][i] < minsum)) {
				s += a[x][i];
				counter++;
				m[i] = counter;
				searchPath(i);
				m[i] = 0;
				counter--;
				s -= a[x][i];
			}
		}
	}
}

void searchPath() {
	s = 0;
	found = 0;
	minsum = 32767;
	for (int i = 1; i <= n; i++) m[i] = 0;
	counter = 1;
	m[1] = counter;
	searchPath(1);
	outputPath();
}
