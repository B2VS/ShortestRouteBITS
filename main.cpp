#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define VV 51
#define pi 3.14159265359
#include <limits.h>


float d[VV][VV], sun[VV][VV], slope[VV][VV];
float f[VV][VV], s, previous[VV];

using namespace std;

void printer(int inde)
{
    int i;
    char s1[50];
    ifstream f1("names.txt", ios::in);
    for (i = 0; i <= inde; ++i) f1 >> s1[i];
    cout << s1;
    f1.close();
}

void Print_Path(float graph[VV][VV],int src,int v)
{
    if (v == src) cout << src + 1; //printer(src + 1);
    else
    {
        Print_Path(graph, src, previous[v]);
        cout << " -> " << v + 1; // printer(v + 1);
    }
}

float minDistance(float dist[], bool sptSet[])
{

    float min = INT_MAX, min_index;
    for (int v = 0; v < VV; v++)
    {
        if (sptSet[v] == false && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void load_data()
{
    ifstream f1("distance.txt", ios::in);
    for (int i = 0; i < VV; ++i) for (int j = 0; j < VV; ++j) f1 >> d[i][j];
    f1.close();
    ifstream f2("sun.txt", ios::in);
    for (int i = 0; i < VV; ++i) for (int j = 0; j < VV; ++j) f2 >> sun[i][j];
    f2.close();
    ifstream f3("slope.txt", ios::in);
    for (int i = 0; i < VV; ++i) for (int j = 0; j < VV; ++j) f3 >> slope[i][j];
    f3.close();
}

void calcsun(float k, float rise, float len, float t)
{
    s = 1 + k * sin(pi * ((t - rise) / len));
}

void calcf()
{
    for (int i = 0; i < VV; ++i)
        for (int j = 0; j < VV; ++j)
            if (sun[i][j]) f[i][j] = s * d[i][j]; //* slope[i][j];
            else f[i][j] = d[i][j]; //* slope[i][j];
}


void dijkstra(float graph[VV][VV], int src, int destination)
{
    float dist[VV];
    bool sptSet[VV];
    for (int i = 0; i < VV; i++)
    {
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }
    dist[src] = 0;
    for (int count = 0; count < VV-1; count++)
    {
        int u = minDistance(dist, sptSet);
        sptSet[u] = true;
        for (int v = 0; v < VV; v++)
        {
            float var;
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX)
                var = dist[u] + graph[u][v];
            if (var < dist[v])
            {
                dist[v] = var;
                previous[v] = u;
            }

        }
     }

     cout << endl << endl << "THE PATH IS: ";
     Print_Path(graph, src, destination);
     cout << endl << "Normalized path length: " << dist[destination];
     cout << endl << endl;

}

int calc_index(char s1[])
{
    ifstream f1("names.txt", ios::in);
    char s2[50];
    for (int i = 0; i < VV; ++i)
    {
        f1 >> s2;
        if (strcmp(s1,s2) == 0) return i;
    }
    f1.close();
}

int main()
{
    int a[50], n;
    char s1[50];
    cout << "Graphs and Networks Presentation (Program)" << endl;
    cout << "By Vedic Sharma, Ahana Ghosh, Adnan Ahzam" << endl << endl;
    cout << "Calculates the easiest way to reach from one point to another within BPHC" << endl << endl;
    cout << "Enter the starting position: ";
    cin >> a[0];//
    //cin.getline(s1);
    //a[0] = calc_index(s1);
    //cout << "a[0] = " << a[0] << endl;
    cout << "Enter the destination position: ";
    cin >> a[1];//
    //cin.getline(s1);
    //a[1] = calc_index(s1);
    //cout << "a[1] = " << a[1] << endl;
    cout << endl;
    cout << "Enter number of intermediate positions: ";
    cin >> n;
    cout << endl;
    for (int i = 1; i <= n; ++i)
    {
        cout << "Enter intermediate position #" << i << ": ";
        a[i + 1] = a[i];
        cin >> a[i];//
        //cin.getline(s1);
        //a[i] = calc_index(s1);
    }
    cout << endl;
    load_data();
    float sun_index_k = 1, sunrise = 6.25, day_len = 11.5;
    char ch;
    float t;
    cout << "How would you like to use the sun index?" << endl;
    cout << "a. Use default at given time" << endl;
    cout << "b. Use sun index at it's maximum = 2 (default)" << endl;
    cout << "c. Don't use sun index = 1 (default)" << endl;
    cout << "d. Use sun index but allow me to tell how much sun index at maximum intensity" << endl;
    cout << "e. Use sun index but allow me to put all values for the function" << endl;
    cout << "f. It's too hot. I don't want to travel in sun unless I have to..." << endl;
    cout << "Please enter your decision: ";
    cin >> ch;
    s = 1;
    if (ch == 'a')
    {
        cout << endl;
        cout << "Enter the time: "; cin >> t;
        if (t >= 6.25 && t <= 17.75) calcsun(sun_index_k, sunrise, day_len, t);
    }
    if (ch == 'b') s = 2;
    if (ch == 'd')
    {
        cout << endl << "Enter the sun index at maximum intensity: "; cin >> sun_index_k;
        cout << endl;
        cout << "Enter the time: "; cin >> t;
        if (t >= 6.25 && t <= 17.75) calcsun(--sun_index_k, sunrise, day_len, t);
    }
    if (ch == 'e')
    {
        cout << endl << "Enter the sun index constant: "; cin >> sun_index_k;
        cout << "Enter the time of sunrise: "; cin >> sunrise;
        cout << "Enter day length: "; cin >> day_len;
        cout << endl;
        cout << "Enter the time: "; cin >> t;
        if (t >= 6.25 && t <= 17.75) calcsun(sun_index_k, sunrise, day_len, t);
    }
    if (ch == 'f')
    {
        s = 100;
    }
    calcf();
    cout << endl << endl;
    for (int i = 0; i < n + 1; ++i)
    {
        cout << "Path " << i + 1 << ": " << endl;
        dijkstra(f, a[i] - 1, a[i+1] - 1);
        cout << endl << endl;
    }
}
