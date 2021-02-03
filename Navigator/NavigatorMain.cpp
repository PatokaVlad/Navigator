#include <iostream>
#include <vector>
#include <queue>
#include <fstream>
#include <string>

using namespace std;

const int Count = 16;

struct Graph
{
    vector < vector<int> > g;
    int s = 0;
    int end = 0;
} ToFind;

struct City
{
    int Name = 0;
    int Population = 0;
    float Coordinate = 0;
} CityTyper;

vector<City> AllCityInOne;

void CityCollector()
{
    AllCityInOne.clear();
    ifstream File;
    File.open("City.txt");
    for (int i = 0; i < Count; i++)
    {
        File >> CityTyper.Name >> CityTyper.Population >> CityTyper.Coordinate;
        AllCityInOne.push_back(CityTyper);
    }
    File.close();
}

void GetCityName(int index)
{
    switch (index)
    {
    case 0:
        cout << "Полтава";
        break;
    case 1:
        cout << "Харкiв";
        break;
    case 2:
        cout << "Балаклея";
        break;
    case 3:
        cout << "Iзюм";
        break;
    case 4:
        cout << "Лозова";
        break;
    case 5:
        cout << "Перещепино";
        break;
    case 6:
        cout << "Новi Санжари";
        break;
    case 7:
        cout << "Кременчук";
        break;
    case 8:
        cout << "Черкаси";
        break;
    case 9:
        cout << "Гребiнка";
        break;
    case 10:
        cout << "Гадяч";
        break;
    case 11:
        cout << "Ахтирка";
        break;
    case 12:
        cout << "Шарiвка";
        break;
    case 13:
        cout << "Миргород";
        break;
    case 14:
        cout << "Лубни";
        break;
    case 15:
        cout << "Семенiвка";
        break;
    default:
        break;
    }
}

void GetCityList()
{
    int Do = 0;
    cout << "  1-Ознайомитися з номерами мiст\n  2-Ознайомлений\n Дiя: ";
    do {
        cin >> Do;
    } while (Do < 1 || Do>2);
    if (Do == 2)
        return;
    else
        for (int Number = 0; Number < Count; Number++)
            switch (Number)
            {
            case 0:
                cout << " 1-Полтава" << endl;
                break;
            case 1:
                cout << " 2-Харкiв" << endl;
                break;
            case 2:
                cout << " 3-Балаклея" << endl;
                break;
            case 3:
                cout << " 4-Iзюм" << endl;
                break;
            case 4:
                cout << " 5-Лозова" << endl;
                break;
            case 5:
                cout << " 6-Перещепино" << endl;
                break;
            case 6:
                cout << " 7-Новi Санжари" << endl;
                break;
            case 7:
                cout << " 8-Кременчук" << endl;
                break;
            case 8:
                cout << " 9-Черкаси" << endl;
                break;
            case 9:
                cout << " 10-Гребiнка" << endl;
                break;
            case 10:
                cout << " 11-Гадяч" << endl;
                break;
            case 11:
                cout << " 12-Ахтирка" << endl;
                break;
            case 12:
                cout << " 13-Шарiвка" << endl;
                break;
            case 13:
                cout << " 14-Миргород" << endl;
                break;
            case 14:
                cout << " 15-Лубни" << endl;
                break;
            case 15:
                cout << " 16-Семенiвка" << endl;
                break;
            default:
                break;
            }

}

void MatrixFileRead(bool Type)
{
    ToFind.g.clear();
    vector<int> Reading;
    int Current = 0;
    ifstream File;
    if (Type)
        File.open("GraphRoad.txt");
    else File.open("GraphType.txt");
    while (File >> Current)
    {
        Reading.push_back(Current);
        if (Reading.size() == Count)
        {
            ToFind.g.push_back(Reading);
            Reading.clear();
        }
    }
    File.close();
}

void ListFileRead()
{
    ToFind.g.clear();
    vector<int> Reading;
    int Current = 0;
    ifstream File;
    File.open("Graph.txt");
    while (File >> Current)
    {
        if (Current == 999)
        {
            ToFind.g.push_back(Reading);
            Reading.clear();
        }
        else
        {
            Reading.push_back(Current);
        }
    }
    File.close();
}

void BFS(bool type)
{
    system("cls");
    GetCityList();
    cout << "Номер початкового мiста: "; cin >> ToFind.s;
    if (type)
    {
        cout << "Номер мiста призначення: "; cin >> ToFind.end;
        ToFind.end--;
    }
    ToFind.s--;
    ListFileRead();
    queue<int> q;
    q.push(ToFind.s);
    vector<bool> used(Count);
    for (int i = 0; i < Count; i++)
        used[i] = false;
    vector<int> d(Count), p(Count);
    used[ToFind.s] = true;
    p[ToFind.s] = -1;
    int dist = 0;
    int to = 0;
    GetCityName(ToFind.s);
    cout << " -> ";
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (size_t i = 0; i < ToFind.g[v].size(); i++)
        {
            to = ToFind.g[v][i];
            if (!used[to])
            {
                used[to] = true;
                q.push(to);
                d[to] = d[v] + 1;
                p[to] = v;
                dist++;
                GetCityName(to);
                cout << " -> ";
            }
            if (type)
                if (to == ToFind.end)
                    break;
        }
        if (type)
            if (to == ToFind.end)
                break;
    }
    cout << "Найкоротша дистанцiя: " << dist << endl;
}

void Deykstra()
{
    system("cls");
    GetCityList();
    cout << "\n Номер початкового мiста: "; cin >> ToFind.s; ToFind.s--;
    cout << " Номер мiста призначення: "; cin >> ToFind.end; ToFind.end--;
    cout << " \nОберiть тип пошуку:\n  1-Кiлометри\n  2-Стан дорожного поктриття\n Дiя: ";
    int Do = 0;
    do {
        cin >> Do;
    } while (Do < 1 || Do>2);
    if (Do == 1)
        MatrixFileRead(true);
    else MatrixFileRead(false);
    int current, index, i, u;
    int distance[Count];
    bool visited[Count];

    for (i = 0; i < Count; i++)
    {
        distance[i] = INT_MAX;
        visited[i] = false;
    }
    distance[ToFind.s] = 0;
    for (current = 0; current < Count - 1; current++)
    {
        int min = INT_MAX;
        for (i = 0; i <= Count; i++)
            if (!visited[i] && distance[i] <= min)
            {
                min = distance[i]; index = i;
            }
        u = index;
        visited[u] = true;
        for (i = 0; i < ToFind.g[u].size(); i++)
            if (!visited[i] && ToFind.g[u][i] && distance[u] != INT_MAX && distance[u] + ToFind.g[u][i] < distance[i])
                distance[i] = distance[u] + ToFind.g[u][i];
        if (index == ToFind.end)
            break;
    }

    cout << "Найкоротший шлях:\t\n";
    if (distance[index] != INT_MAX)
    {
        cout << "  З мiста ";
        GetCityName(ToFind.s);
        cout << " до мiста ";
        GetCityName(ToFind.end);
        cout << " = " << distance[index];
        if (Do == 1)
            cout << " км" << endl;
        else cout << " одиниць" << endl;
    }
    else cout << ToFind.s << " -> " << ToFind.end + 1 << " = " << "Error" << endl;
}

void QuickSort(bool Type, int first, int last)
{
    int MidInt = 0;
    float MidFloat = 0.0;
    City Count;
    int f = first, l = last;
    switch (Type)
    {
    case true:
        MidInt = AllCityInOne[(f + l) / 2].Population;
        do
        {
            while (AllCityInOne[f].Population < MidInt) f++;
            while (AllCityInOne[l].Population > MidInt) l--;
            if (f <= l)
            {
                Count = AllCityInOne[f];
                AllCityInOne[f] = AllCityInOne[l];
                AllCityInOne[l] = Count;
                f++;
                l--;
            }
        } while (f < l);
        if (first < l) QuickSort(true, first, l);
        if (f < last) QuickSort(true, f, last);
        break;
    case false:
        MidFloat = AllCityInOne[(f + l) / 2].Coordinate;
        do
        {
            while (AllCityInOne[f].Coordinate < MidFloat) f++;
            while (AllCityInOne[l].Coordinate > MidFloat) l--;
            if (f <= l)
            {
                Count = AllCityInOne[f];
                AllCityInOne[f] = AllCityInOne[l];
                AllCityInOne[l] = Count;
                f++;
                l--;
            }
        } while (f < l);
        if (first < l) QuickSort(true, first, l);
        if (f < last) QuickSort(true, f, last);
        break;
    default:
        break;
    }
}

void CitySort()
{
    system("cls");
    CityCollector();
    GetCityList();
    cout << "\n Оберiть тип сортування:\n  1-За населенням\n  2-За координатами(градуси широта + довгота)\n Дiя: ";
    int Do = 0;
    do {
        cin >> Do;
    } while (Do < 1 || Do>2);
    if (Do == 1)
        QuickSort(true, 0, Count - 1);
    else QuickSort(false, 0, Count - 1);
    cout << "\n Оберiть порядок сортування:\n  1-За зростанням\n  2-За спаданням\n Дiя: ";
    do {
        cin >> Do;
    } while (Do < 1 || Do>2);
    if (Do == 1)
        cout << "\n Результат сортування: \n" << endl;
    if (Do == 1)
        for (int i = 0; i < Count; i++)
        {
            cout << " Мiсто: ";
            GetCityName(AllCityInOne[i].Name);
            cout << endl;
            cout << " Населення: " << AllCityInOne[i].Population << endl << " Координати(градуси широта + довгота): " << AllCityInOne[i].Coordinate << endl << endl;
        }
    else
        for (int i = Count - 1; i > 0; i--)
        {
            cout << " Мiсто: ";
            GetCityName(AllCityInOne[i].Name);
            cout << endl;
            cout << " Населення: " << AllCityInOne[i].Population << endl << " Координати(градуси широта + довгота): " << AllCityInOne[i].Coordinate << endl << endl;
        }
}

int main()
{
    int Menu = 0;
    bool Again = true;
    setlocale(LC_ALL, "Ukrainian");
    do
    {
        cout << "\n Оберiть потрiбну фунцiю: " << endl;
        cout << "  1-Обiйти всi мiста\n  2-Шлях вiд одного мiста до iншого\n  3-Найкоротший шлях вiд одного мiста до iншого\n  4-Сортування мiст по критерiям\n  5-Завершити роботу\n Дiя: ";
        do {
            cin >> Menu;
        } while (Menu > 6 || Menu < 0);
        switch (Menu)
        {
        case 1:
            BFS(false);
            break;
        case 2:
            BFS(true);
            break;
        case 3:
            Deykstra();
            break;
        case 4:
            CitySort();
            break;
        case 5:
            Again = false;
            break;
        default:
            break;
        }
    } while (Again);
    return 0;
}