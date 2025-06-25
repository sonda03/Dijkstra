#include <iostream>
using namespace std;

const int citiesArraySize = 50000;

class myString
{
private:
    char* str;
    int length;

public:
    myString()
    {
        str = new char[1];
        str[0] = '\0';
        length = 0;
    }
    myString(char* value)
    {
        length = 0;
        if (value == nullptr)
        {
            str = new char[1];
            str[0] = '\0';
        }
        else
        {
            length = 0;
            while (value[length] != '\0')
            {
                length++;
            }
            str = new char[length + 1];
            str[length] = '\0';
            for (int i = 0; i < length; i++)
            {
                str[i] = value[i];
            }
        }
    }
    void putToString(char* value)
    {
        delete[] str;
        length = 0;
        if (value == nullptr)
        {
            str = new char[1];
            str[0] = '\0';
        }
        else
        {
            length = 0;
            while (value[length] != '\0')
            {
                length++;
            }
            str = new char[length + 1];
            str[length] = '\0';
            for (int i = 0; i < length; i++)
            {
                str[i] = value[i];
            }
        }
    }
    void clearString()
    {
        delete[] str;
        str = new char[1];
        str[0] = '\0';
        length = 0;
    }
    bool isNumber()
    {
        bool isThisANuber = 0;
        char digits[10] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };
        for (int i = 0; i < length; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (str[i] == digits[j])
                {
                    isThisANuber = true;
                    break;
                }
            }
            if (isThisANuber == false)
            {
                return false;
            }
            isThisANuber = false;
        }
        return true;
    }
    bool isCommandLetter()
    {
        if (str[0] != 'S' && str[0] != 'A')
        {
            return false;
        }
        char letters[10] = { 'S', 'A' };
        for (int i = 0; i < length - 1; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (str[i] != letters[j])
                {
                    return false;
                }
            }
        }
        return true;
    }
    int toNumber()
    {
        int result = 0;
        int finalResult = 0;
        if (this->isNumber())
        {
            for (int i = 0; i < length; i++)
            {
                result += (int(str[i]) - 48);
                for (int j = 0; j < length - i - 1; j++)
                {
                    result *= 10;
                }
                finalResult += result;
                result = 0;
            }
        }
        return finalResult;
    }
    bool compareToALetter(char a)
    {
        if (length == 1 && str[0] == a)
        {
            return true;
        }
        return false;
    }
    bool compareToAnotherString(myString a)
    {
        if (length != a.length)
        {
            return false;
        }
        for (int i = 0; i < length; i++)
        {
            if (str[i] != a.str[i])
            {
                return false;
            }
        }
        return true;
    }
    void printMyString()
    {
        for (int i = 0; i < length; i++)
        {
            cout << str[i];
        }
    }
    myString& operator+=(const char letter)
    {
        if (length != 0 && str[0] != '\0')
        {
            char* updatedString;
            length += 1;
            updatedString = new char[length + 1];
            for (int i = 0; i < length - 1; i++)
            {
                updatedString[i] = str[i];
            }
            updatedString[length - 1] = letter;
            updatedString[length] = '\0';
            char* tmp;
            tmp = str;
            str = updatedString;
            updatedString = tmp;
            delete[] tmp;
            return *this;
        }
        else
        {
            length += 1;
            str[0] = letter;
            return *this;
        }

    }
    myString& operator=(const myString& other)
    {
        if (this != &other)
        {
            str = new char[1];
            delete[] str;
            length = other.length;
            str = new char[length + 1];
            for (int i = 0; i < length; ++i)
            {
                str[i] = other.str[i];
            }
            str[length] = '\0';
        }
        return *this;
    }
};


struct flightConnection
{
    myString source;
    myString destination;
    int flightTime;
};
struct city
{
    myString name;
    int x;
    int y;
    int adjaciencyMatrixPlacement;
};
struct myVectorNode
{
    myString city;
    myVectorNode* next;
    myVectorNode* prev;
};

struct position
{
    int x;
    int y;
    int distance;
};


class myVector
{
private:
    myVectorNode* head;
    myVectorNode* tail;
public:
    myVector()
    {
        head = nullptr;
        tail = nullptr;
    }
    void pushBack(myString city)
    {
        myVectorNode* newNode = new myVectorNode;
        newNode->city = city;
        newNode->next = nullptr;
        newNode->prev = tail;

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    myString get(int index) {
        myVectorNode* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->city;
    }

    void print()
    {
        myVectorNode* current = head;
        while (current != nullptr) {
            cout << " ";
            current->city.printMyString();
            current = current->next;
        }
    }
    void printReverse() {
        myVectorNode * current = tail;
        while (current != nullptr) {
            cout << " ";
            current->city.printMyString();
            current = current->prev;
        }
    }
};

struct query
{
    myString source;
    myString destination;
    bool type;
    myVector path;
    int time;
};

struct myQueueNode
{
    int x;
    int y;
    myQueueNode* next;
};

class myQueue
{
private:
    myQueueNode* head;
    myQueueNode* tail;
public:
    myQueue()
    {
        head = nullptr;
        tail = nullptr;
    }
    void push(int x, int y)
    {
        myQueueNode* newNode = new myQueueNode;
        newNode->x = x;
        newNode->y = y;
        newNode->next = nullptr;
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    myQueueNode* pop()
    {
        myQueueNode* tmp = head;
        head = head->next;
        return tmp;
    }
    bool is_empty()
    {
        return head == nullptr;
    }
};

class myPriorityQueue
{
private:
    struct myQueueNode {
        int city;
        int distance;
        myQueueNode* next;
    };
    myQueueNode* head;
    myQueueNode* tail;
    public:
        myPriorityQueue()
        {
        head = nullptr;
        tail = nullptr;
    }
        void push(int pos, int dist)
        {
        myQueueNode* newNode = new myQueueNode;
        newNode->city = pos;
        newNode->distance = dist;
        newNode->next = nullptr;
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            myQueueNode* current = head;
            myQueueNode* prev = nullptr;
            while (current != nullptr && current->distance < dist) {
                prev = current;
                current = current->next;
            }
            if (prev == nullptr) {
                newNode->next = head;
                head = newNode;
            }
            else {
                prev->next = newNode;
                newNode->next = current;
            }
        }
    }
        myQueueNode* pop()
        {
        myQueueNode* tmp = head;
        head = head->next;
        return tmp;
    }
        bool is_empty()
        {
        return head == nullptr;
    }
};

bool is_valid(int x, int y, bool** isPassableMap, bool** visited, int w, int h) {
    return (x >= 0 && x < w && y >= 0 && y < h && isPassableMap[y][x] == 1 && !visited[y][x]);
}

void bfs(int start_x, int start_y, int endX, int endY, bool** visited, bool** isPassableMap, int w, int h, int** distances, position** parents)
{
    myQueue q;
    q.push(start_x, start_y);
    distances[start_y][start_x] = 0;
    position parentPosition;
    visited[start_y][start_x] = true;
    while (!q.is_empty()) {
        myQueueNode* node = q.pop();
        int x = node->x;
        int y = node->y;
        if (x == endX && y == endY)
        {
            return;
        }
        if (is_valid(x - 1, y, isPassableMap, visited, w, h))
        {
            q.push(x - 1, y);
            visited[y][x - 1] = true;
            distances[y][x - 1] = distances[y][x] + 1;
            parentPosition.x = x;
            parentPosition.y = y;
            parentPosition.distance = distances[y][x - 1];
            parents[y][x - 1] = parentPosition;
        }
        if (is_valid(x + 1, y, isPassableMap, visited, w, h))
        {
            q.push(x + 1, y);
            visited[y][x + 1] = true;
            distances[y][x + 1] = distances[y][x] + 1;
            parentPosition.x = x;
            parentPosition.y = y;
            parentPosition.distance = distances[y][x + 1];
            parents[y][x + 1] = parentPosition;
        }
        if (is_valid(x, y - 1, isPassableMap, visited, w, h))
        {
            q.push(x, y - 1);
            visited[y - 1][x] = true;
            distances[y - 1][x] = distances[y][x] + 1;
            parentPosition.x = x;
            parentPosition.y = y;
            parentPosition.distance = distances[y - 1][x];
            parents[y - 1][x] = parentPosition;
        }
        if (is_valid(x, y + 1, isPassableMap, visited, w, h))
        {
            q.push(x, y + 1);
            visited[y + 1][x] = true;
            distances[y + 1][x] = distances[y][x] + 1;
            parentPosition.x = x;
            parentPosition.y = y;
            parentPosition.distance = distances[y + 1][x];
            parents[y + 1][x] = parentPosition;
        }
    }
}
int find_shortest_path(int x1, int y1, int x2, int y2, int h, int w, bool** visited, int** distance, bool** isPassableMap, position** parents)
{
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            visited[i][j] = 0;
            distance[i][j] = 0;
            parents[i][j].distance = INT_MAX;
        }
    }
    bfs(x1, y1, x2, y2, visited, isPassableMap, w, h, distance, parents);
    return distance[y2][x2];
}

int readMap(int w, int h, char** map, bool** isPassableMap, city* cities, int& n)
{
    int numberOfCities = 0;
    bool lastCityFinished = false;
    myString cityName;
    int cityX = -1;
    int cityY = -1;
    int possibleLocations[8][2] = { {0,1}, {1,0}, {0,-1}, {-1,0}, {1,1}, {-1,-1}, {-1,1}, {1,-1} };
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (map[i][j] == '*' || map[i][j] == '#')
            {
                isPassableMap[i][j] = 1;
            }
            else
            {
                isPassableMap[i][j] = 0;
            }
            if ((map[i][j] >= '0' && map[i][j] <= '9') || (map[i][j] >= 'A' && map[i][j] <= 'Z')) {
                cityName += map[i][j];
                if (cityX == -1 && cityY == -1) {
                    for (char c = 0; c < 8; c++)
                    {
                        if (i + possibleLocations[c][0] >= 0 && j + possibleLocations[c][1] >= 0 && i + possibleLocations[c][0] < h && j + possibleLocations[c][1] < w)
                        {
                            if (map[i + possibleLocations[c][0]][j + possibleLocations[c][1]] == '*')
                            {
                                cityY = i + possibleLocations[c][0];
                                cityX = j + possibleLocations[c][1];
                                break;
                            }
                        }
                    }
                }
            }
            else if (cityX != -1 && cityY != -1)
            {
                cities[numberOfCities].name = cityName;
                cities[numberOfCities].x = cityX;
                cities[numberOfCities].y = cityY;
                numberOfCities++;
                cityName.clearString();
                cityX = -1;
                cityY = -1;
            }
        }
    }
    if (cityX != -1 && cityY != -1)
    {
        cities[numberOfCities].name = cityName;
        cities[numberOfCities].x = cityX;
        cities[numberOfCities].y = cityY;
        numberOfCities++;
        cityName.clearString();
        cityX = -1;
        cityY = -1;
    }
    return numberOfCities;
}
void createPathVector(position** parents, int x2, int y2, int x1, int y1, myVector** travelPath, char** map, int numberOfCities, city* cities, int xBegin, int yBegin)
{
    if (x2 == x1 && y2 == y1)
    {
        return;
    }
    else
    {
        if (map[y2][x2] == '*')
        {
            for (int i = 0; i < numberOfCities; i++)
            {
                if (cities[i].x == x2 && cities[i].y == y2)
                {
                    for (int j = 0; j < numberOfCities; j++)
                    {
                        if (cities[j].x == xBegin && cities[j].y == yBegin)
                        {
                            for (int k = 0; k < numberOfCities; k++)
                            {
                                if (cities[k].x == x1 && cities[k].y == y1)
                                {
                                    travelPath[j][k].pushBack(cities[i].name);
                                    break;
                                }
                            }
                            break;
                        }
                    }
                    break;
                }
            }
        }
        if (parents[y2][x2].distance < INT_MAX)
            createPathVector(parents, parents[y2][x2].x, parents[y2][x2].y, x1, y1, travelPath, map, numberOfCities, cities, xBegin, yBegin);
    }
}

int dijkstra(int start_city, int end_city, int numberOfCities, city* cities, int** adjacentyMatrix, bool path) {
    int* distance = new int[numberOfCities];
    bool* visited = new bool[numberOfCities];
    int* parent = new int[numberOfCities];
    for (int i = 0; i < numberOfCities; i++)
    {
        distance[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }
    distance[start_city] = 0;
    for (int i = 0; i < numberOfCities - 1; i++)
    {
        int min = INT_MAX;
        int min_index = 0;
        for (int j = 0; j < numberOfCities; j++)
        {
            if (visited[j] == false && distance[j] <= min)
            {
                min = distance[j];
                min_index = j;
            }
        }
        visited[min_index] = true;
        for (int j = 0; j < numberOfCities; j++)
        {
            if (visited[j] == false && adjacentyMatrix[min_index][j]!=INT_MAX && distance[min_index] != INT_MAX && distance[min_index] + adjacentyMatrix[min_index][j] <= distance[j])
            {
                distance[j] = distance[min_index] + adjacentyMatrix[min_index][j];
                parent[j] = min_index;
            }
        }
    }
    int result = distance[end_city];
    cout << result;
    if (!path) {
        cout << endl;
        return result;
    }
    else {
        int current = end_city;
        myVector travelPath;
        int c = 0;
        while (current != start_city)
        {
            if (current != end_city) {
                travelPath.pushBack(cities[current].name);
            }
            current = parent[current];
        }
        travelPath.printReverse();
    }
    cout << endl;
    return result;
}

int main(int argc, const char* argv[])
{
    int w, h;
    int n = citiesArraySize;
    cin >> w >> h;
    char** map = new char* [h];
    bool** isPassableMap = new bool* [h];
    bool** visited = new bool* [h];
    int** distance = new int* [h];
    position** parents = new position * [h];
    city* cities = new city[n];

    for (int i = 0; i < h; i++)
    {
        map[i] = new char[w];
        isPassableMap[i] = new bool[w];
        visited[i] = new bool[w];
        distance[i] = new int[w];
        parents[i] = new position[w];
    }
    int numberOfCities = 0;
    numberOfCities = readMap(w, h, map, isPassableMap, cities, n);
    int** adjaciencyMatrixCities = new int* [numberOfCities];
    myVector** travelPath = new myVector * [numberOfCities];
    for (int i = 0; i < numberOfCities; i++)
    {
        adjaciencyMatrixCities[i] = new int[numberOfCities];
        travelPath[i] = new myVector[numberOfCities];
    }
    for (int i = 0; i < numberOfCities; i++)
    {
        for (int j = 0; j < numberOfCities; j++)
        {
            if (i == j) {
                adjaciencyMatrixCities[i][j] = 0;
                continue;
            }
            adjaciencyMatrixCities[i][j] = find_shortest_path(cities[i].x, cities[i].y, cities[j].x, cities[j].y, h, w, visited, distance, isPassableMap, parents);
            if(adjaciencyMatrixCities[i][j]!=0)
                createPathVector(parents, cities[j].x, cities[j].y, cities[i].x, cities[i].y, travelPath, map, numberOfCities, cities, cities[j].x, cities[j].y);
            else
                adjaciencyMatrixCities[i][j] = INT_MAX;
        }
    }
    int k;
    cin >> k;
    flightConnection* flights = new flightConnection[k];
    for (int i = 0; i < k; i++)
    {
        char tmp[100];
        cin >> tmp;
        flights[i].source.putToString(tmp);
        cin >> tmp;
        flights[i].destination.putToString(tmp);
        cin >> flights[i].flightTime;
    }
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < numberOfCities; j++)
        {
            for (int k = 0; k < numberOfCities; k++)
            {
                if (cities[j].name.compareToAnotherString(flights[i].source) && cities[k].name.compareToAnotherString(flights[i].destination))
                {
                    if (adjaciencyMatrixCities[j][k] > flights[i].flightTime)
                        adjaciencyMatrixCities[j][k] = flights[i].flightTime;
                }
            }
        }
    }
    int q;
    cin >> q;
    query* travels = new query[q];
    for (int i = 0; i < q; i++)
    {
        char tmp[100];
        cin >> tmp;
        travels[i].source.putToString(tmp);
        cin >> tmp;
        travels[i].destination.putToString(tmp);
        cin >> travels[i].type;
    }
    for (int i = 0; i < q; i++)
    {
        for (int j = 0; j < numberOfCities; j++)
        {
            for (int k = 0; k < numberOfCities; k++)
            {
                if (cities[j].name.compareToAnotherString(travels[i].source) && cities[k].name.compareToAnotherString(travels[i].destination))
                {
                    dijkstra(j, k, numberOfCities, cities, adjaciencyMatrixCities, travels[i].type);
                }
            }
        }
    }
    return 0;
}
