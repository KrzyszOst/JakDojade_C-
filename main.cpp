#include <iostream>
using namespace std;
#define size_of_String  128
class Strings
{
public:
        int number_of_letters = 0;
        char strin[size_of_String];
        Strings()
        {
                for (int i = 0; i < size_of_String; i++)
                {
                        strin[i] = 0;
                }
        }
        void AddChar(char letter)
        {
                strin[number_of_letters] = letter;
                number_of_letters++;
        }
        void Read_String()
        {
                char znak;
                do {

                        cin.get (znak);
                        if (znak == '\n')
                        {
                                continue;
                        }
                        AddChar(znak);
                } while (znak != ' ');
                strin[number_of_letters - 1] = 0;
                number_of_letters--;
        }

        void PrintujStringa()
        {
                for (int i = 0; i < size_of_String; i++)
                {
                        if (strin[i] == 0)
                        {
                                break;
                        }
                        cout << strin[i];
                }
        }
        int Zamien_stringa_na_liczbe()
        {
                int liczba = 0;
                for (int i = 0; i < size_of_String; i++)
                {
                        if (strin[i] == 0)
                        {
                                return liczba;
                        }
                        int cyfra = int(strin[i] - '0');
                        liczba = liczba * 10;
                        liczba = liczba + cyfra;
                }
                return liczba;
        }
};
struct Data
{
        Strings name_of_city;
        int x = 0;
        int y = 0;
};
struct Stack_data
{
        int x = 0;
        int y = 0;
        int distance = 0;
};
struct Diksta
{
        bool is_this_citi_was_visited = false;
        int distance_from_start = 1000000;
        int Last_city = 0;
                
};
struct Matrix_of_neigthbor
{
        int number_of_cities;
        int** m;
        Matrix_of_neigthbor(int number_of_cities)
        {
                m = new int* [number_of_cities];
                for (int i = 0; i < number_of_cities; i++)
                {
                        m[i] = new int[number_of_cities];
                        for (int j = 0; j < number_of_cities; j++)
                        {
                                m[i][j] = 0;
                        }
                }
                this->number_of_cities = number_of_cities;
        }
        ~Matrix_of_neigthbor()
        {
                for (int h = 0; h < number_of_cities; h++)
                {
                        delete[] m[h];

                }
                delete[] m;
        }
};
class Stack
{
public:
        int num_of_table_elements = 0;
        Stack_data* tab;
        Stack(int n)
        {
                tab = new Stack_data[n];

        }
        void push(int x, int y, int distance)
        {
                Stack_data s;
                s.x = x;
                s.y = y;
                s.distance = distance;
                tab[num_of_table_elements] = s;
                num_of_table_elements++;
        }
        void pop(int& x, int& y, int& distance)
        {
                x = tab[num_of_table_elements - 1].x;
                y = tab[num_of_table_elements - 1].y;
                distance = tab[num_of_table_elements - 1].distance;
                num_of_table_elements--;
        }
        bool is_empty()
        {
                if (num_of_table_elements > 0)
                {
                        return false;
                }
                else
                {
                        return true;
                }
        }
};
bool is_good_mark(char mark)
{
        return isdigit(mark) || isalpha(mark);
}

bool CompareStrings(Strings* one, Strings* two)
{

        if (one->number_of_letters == two->number_of_letters)
        {
                for (int i = 0; i < one->number_of_letters; i++)
                {
                        if (one->strin[i] != two->strin[i])
                        {
                                return false;
                        }
                }
                return true;
        }
        else
        {
                return false;
        }

}
void read_city_name_from_right(int x, int y, char** board, Strings& city_name)
{
        bool still_read = true;
        int array = x;

        while (still_read)
        {

                if (is_good_mark(board[y][array]) == true)
                {
                        city_name.AddChar(board[y][array]);
                        array++;
                }
                else
                {
                        still_read = false;
                }

        }
}
void read_city_name_from_left(int x, int y, char** board, Strings& city_name)
{
        bool still_read = true;
        int array = x;
        while (still_read)
        {


                if (is_good_mark(board[y][array]) == true)
                {
                        array--;
                }
                else
                {
                        still_read = false;
                }
        }
        read_city_name_from_right(array+1, y, board, city_name);
}
void find_city_name(char** board, int width, int height, int& number_of_cities, Data*& tab_of_cities, int index_city, int i, int j)
{
        Strings& name_of_city = tab_of_cities[index_city].name_of_city;
        if ((is_good_mark(board[i - 1][j])))
        {
                read_city_name_from_left(j, i - 1, board, name_of_city);
        }
        else if (is_good_mark(board[i + 1][j]))
        {
                read_city_name_from_left(j, i + 1, board, name_of_city);
        }
        else if (is_good_mark(board[i][j - 1]))
        {
                read_city_name_from_left(j - 1, i, board, name_of_city);
        }
        else if (is_good_mark(board[i][j + 1]))
        {
                read_city_name_from_left(j + 1, i, board, name_of_city);
        }
        else if (is_good_mark(board[i + 1][j + 1]))
        {
                read_city_name_from_left(j + 1, i + 1, board, name_of_city);
        }
        else if (is_good_mark(board[i + 1][j - 1]))
        {
                read_city_name_from_left(j - 1, i + 1, board, name_of_city);
        }
        else if (is_good_mark(board[i - 1][j - 1]))
        {
                read_city_name_from_left(j - 1, i - 1, board, name_of_city);
        }
        else if (is_good_mark(board[i - 1][j + 1]))
        {
                read_city_name_from_left(j + 1, i - 1, board, name_of_city);
        }
}
void Read_names_of_cities(char** board, int width, int height, int& number_of_cities, Data*& tab_of_cities)
{
        number_of_cities = 0;
        for (int i = 0; i < height; i++)
        {
                for (int j = 0; j < width; j++)
                {
                        if (board[i][j] == '*')
                        {
                                number_of_cities++;
                        }
                }
        }
        tab_of_cities = new Data[number_of_cities];
        int index = 0;
        for (int i = 0; i < height; i++)
        {
                for (int j = 0; j < width; j++)
                {
                        if (board[i][j] == '*')
                        {
                                tab_of_cities[index].x = j;
                                tab_of_cities[index].y = i;
                                find_city_name(board, width, height, number_of_cities, tab_of_cities, index, i, j);
                                index++;
                        }
                }
        }

}


void dfs(int x, int y, char** board, Matrix_of_neigthbor& m, int id_of_city, Data* tabofcities, int numberofcities, int width, int heigth)
{
        int xstart = x;
        int ystart = y;
        int** visited = new int* [heigth];
        for (int i = 0; i < heigth; i++)
        {
                visited[i] = new int[width];
                for (int j = 0; j < width; j++)
                {
                        visited[i][j] = 0;
                }
        }
        int distance = 0;
        Stack s(width * heigth / 2);
        s.push(x, y, distance);
        while (s.is_empty() == false)
        {
                s.pop(x, y, distance);
                int kierunki[4][2] = { {0,1},
                        {0,-1},
                        {1,0},
                        {-1,0} };

                if (visited[y][x] == 0 || visited[y][x] > distance)
                {
                        visited[y][x] = distance;
                }
                for (int i = 0; i < 4; i++)
                {
                        int x1 = kierunki[i][1] + x;
                        int y1 = kierunki[i][0] + y;
                        if (board[y1][x1] == '#' && (visited[y1][x1] == 0 || visited[y1][x1] - 1 > distance))
                        {

                                s.push(x1, y1, distance + 1);
                        }



                        if (board[y1][x1] == '*' &&( y1 != ystart || x1 != xstart))
                        {
                                int jd = 0;
                                for (; jd < numberofcities; jd++)
                                {
                                        if (tabofcities[jd].x == x1 && tabofcities[jd].y == y1)
                                        {
                                                break;
                                        }


                                }
                                if (distance + 1 < m.m[id_of_city][jd] || m.m[id_of_city][jd] == 0)
                                {
                                        m.m[id_of_city][jd] = distance + 1;
                                }
                        }
                }


        }
        for (int i = 0; i < heigth; i++)
        {
                delete[] visited[i];
        }
        delete[] visited;

}
bool Find_first_city(Matrix_of_neigthbor* m, Data* tabofcities,int & id,int &distance,int current_id_of_city,Diksta* cities)
{
        for (int i = id+1; i < m->number_of_cities; i++)
        {
                if (m->m[current_id_of_city][i] > 0 && cities[i].is_this_citi_was_visited==false)
                {
                        distance = m->m[current_id_of_city][i];
                        id = i;
                        return true;
                }

        }
        return false;
}
int find_id_city_which_wasnt_visited(Matrix_of_neigthbor* m, Diksta* cities)
{
        int id_minimum = 0;
        int minimum_distance = 100000;
        for (int i = 0; i < m->number_of_cities; i++)
        {
                if (cities[i].distance_from_start < minimum_distance&&cities[i].is_this_citi_was_visited==false)
                {
                        minimum_distance = cities[i].distance_from_start;
                        id_minimum = i;
                }
        }
        return id_minimum;
}
void print_path(Matrix_of_neigthbor* m, Data* tabofcities, bool print_route, Diksta* cities,int id_of_second_city,int id_of_first_city)
{
        if (print_route == true)
        {
                int paths_counter = 0;
                int id_of_city = id_of_second_city;
                while (id_of_city != id_of_first_city)
                {

                        cities[paths_counter].distance_from_start = cities[id_of_city].Last_city;
                        id_of_city = cities[id_of_city].Last_city;
                        paths_counter++;
                        
                }
                paths_counter--;
                for (int p = paths_counter -1; p >=0 ; p--)
                {
                        id_of_city = cities[p].distance_from_start;
                        cout << " ";
                        tabofcities[id_of_city].name_of_city.PrintujStringa();
                }
        }
}
void dikstra(Matrix_of_neigthbor* m, Data* tabofcities)
{
        int id_of_city = 0;
        Strings first_city;
        first_city.Read_String();
        int id_of_first_city = 0;
        Strings second_city;
        second_city.Read_String();
        int id_of_seocnd_city=0;
        bool print_route;
        cin >> print_route;
        for (int i = 0; i < m->number_of_cities; i++)
        {
                if (CompareStrings(&first_city, &tabofcities[i].name_of_city))
                {
                        id_of_first_city = i;
                }
                if (CompareStrings(&second_city, &tabofcities[i].name_of_city))
                {
                        id_of_seocnd_city = i;
                }
        }
        id_of_city = id_of_first_city;
        Diksta* cities = new Diksta[m->number_of_cities];
        cities[id_of_city].distance_from_start = 0;
        while (id_of_city != id_of_seocnd_city)
        {
                cities[id_of_city].is_this_citi_was_visited = true;
                int id=-1;
                int distance=0;
                while (Find_first_city(m, tabofcities, id, distance, id_of_city,cities))
                {
                        if (distance + cities[id_of_city].distance_from_start < cities[id].distance_from_start)
                        {
                                cities[id].distance_from_start = distance + cities[id_of_city].distance_from_start;
                                cities[id].Last_city = id_of_city;
                        }
                }
                id_of_city = find_id_city_which_wasnt_visited(m, cities);
        }
        cout << cities[id_of_city].distance_from_start;
        print_path(m, tabofcities, print_route, cities, id_of_seocnd_city, id_of_first_city);
        cout << endl;
        delete[] cities;
}
int main()
{
        int number_of_cites;
        int number_of_flight_connections;
        Data* tab_of_cities;

        int width;
        cin >> width;
        int height;
        cin >> height;
        width += 2;
        height += 2;
        char** board = new char* [height];
        for (int i = 0; i < height; i++)
        {
                board[i] = new char[width];

        }
        for (int i = 1; i < height - 1; i++)
        {
                for (int j = 1; j < width - 1; j++)
                {
                        cin >> board[i][j];
                }
        }
        cin >> number_of_flight_connections;
        
        for (int k = 0; k < height; k++)
        {
                for (int p = 0; p < width; p++)
                {
                        if (k == 0 || k == height - 1 || p == 0 || p == width - 1)
                        {
                                board[k][p] = '.';
                        }
                }
        }
        Read_names_of_cities(board, width, height, number_of_cites, tab_of_cities);
        Matrix_of_neigthbor m(number_of_cites);
        for (int i = 0; i < number_of_flight_connections; i++)
        {
                Strings flight_one;
                Strings flight_two;
                flight_one.Read_String();
                flight_two.Read_String();
                int distance;
                cin >> distance;
                int flight_one_id=0;
                int flight_two_id=0;
                for (int k = 0; k < number_of_cites; k++)
                {
                        if (CompareStrings(&flight_one, &tab_of_cities[k].name_of_city))
                        {
                                flight_one_id = k;
                                
                        }
                }
                for (int k = 0; k < number_of_cites; k++)
                {
                        if (CompareStrings(&flight_two, &tab_of_cities[k].name_of_city))
                        {
                                flight_two_id = k;

                        }
                }
                if (distance < m.m[flight_one_id][flight_two_id])
                {
                        m.m[flight_one_id][flight_two_id] = distance;
                }
                else if (m.m[flight_one_id][flight_two_id]==0)
                {
                        m.m[flight_one_id][flight_two_id] = distance;
                }
        }

        for (int k = 0; k < number_of_cites; k++)
        {
                dfs(tab_of_cities[k].x, tab_of_cities[k].y, board, m, k, tab_of_cities, number_of_cites, width, height);

        }
        /*for (int i = 0; i < number_of_cites; i++)
        {
                for (int j = 0; j < number_of_cites; j++)
                {
                        cout << m.m[i][j] << " ";
                }
                cout << endl;
        }*/
        int numbers_of_disktra;
        cin >> numbers_of_disktra;
        for (int i = 0; i < numbers_of_disktra; i++)
        {
                dikstra(&m, tab_of_cities);

        }
        for (int i = 0; i < height; i++)
        {
                delete[] board[i];
        }
        delete[] board;

}