#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
#include <cctype>


class Ledokol{
public:
    Ledokol(int name, bool status) : spot_(name), status_(status) {};
    ~Ledokol(){};
    int spot_;
    bool status_;
    std::string where_go_;
    double direction;
    int day_start;
};

using namespace std;


int GetData(string str){
    string str1,str2,str3,str4,str_m;
    stringstream ss(str);
    getline(ss, str, ',');
    getline(ss, str1, ',');
    getline(ss, str2, ',');
    getline(ss, str3, ',');
    getline(ss, str4, ',');
    stringstream sss(str4);
    getline(sss, str_m, ':');
    getline(sss, str_m, ',');

    return stoi(str_m);
}


int GetName(string str){
    string str1,str2,str3,str4,str_m;
    stringstream ss(str);
    getline(ss, str, ',');

    return stoi(str);
}

int GetHour(string str){
    string str1,str2,str3,str4,str5,str_m;
    stringstream ss(str);
    getline(ss, str, ',');
    getline(ss, str1, ',');
    getline(ss, str2, ',');
    getline(ss, str3, ',');
    getline(ss, str4, ',');
    getline(ss, str5, ',');
    stringstream sss(str5);
    getline(sss, str_m, ':');
    getline(sss, str_m, ',');

    return stoi(str_m);
}

string GetRebro(string str){
    string str1,str2,str3,str4,str5,str_m;
    stringstream ss(str);
    getline(ss, str, ',');
    getline(ss, str1, ',');
    getline(ss, str2, ',');
    getline(ss, str3, ',');

    return str3;
}

void DelEmpty(vector<std::string>& orders) {
    for (auto i = orders.begin(); i != orders.end(); ) {
        if (i->find("не нуждается") != std::string::npos) {
            i = orders.erase(i);
        } else {
            ++i;
        }
    }
}

int RemoveAllExceptLast(const std::string& str) {
    string tmp;
    if (isdigit(str[str.size() - 1]) && !isdigit(str[str.size() - 2])) {
        tmp = str.substr(str.length() - 1);  // Extract the last character
    } else if (isdigit(str[str.size() - 1]) && isdigit(str[str.size() - 2])) {
         tmp = str.substr(str.length() - 2);  // Extract the last character
    }
    
    return stoi(tmp);
}

// int searchDays(int *day) {
//     size_t j = 0;
//         int pass = 0;
//         // int hour = z.start_hour;
//         double way_in_rebro = 0;
//         int speed = 9 * 1.8;
//         // cout << "начал с " << way_str[j] << endl;
//         for(; *day <= 30; day++){
//             // cout << "day " << day << endl;
//             for(;hour < 24; hour++){
//                 // cout << "hour " << hour << endl;
//                 way_in_rebro = way_in_rebro + z.speed;
//             }
//             hour = 0;
//         }
// }

void SORTTTTT(vector<string>& orders){
    vector<double> rebro_1 = {440,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2};
    vector<double> rebro_2 = {450.04,0,1,1,1,1,2,2,2,2,2,2,2,2,3,3,3,3,3,3,3,4,4,4,4,4,4,4,5,5,5};
    vector<double> rebro_3 = {169.16,1,1,1,1,2,2,2,2,2,2,3,3,3,3,3,3,3,4,4,4,4,4,5,5,5,5,6,6,6,6};
    vector<double> rebro_4 = {752,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2};
    vector<double> rebro_5 = {376.68,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2};
    vector<double> rebro_6 = {414.56,0,0,0,1,1,1,1,1,1,1,1,1,2,2,2,2,2,3,3,3,3,3,4,4,4,4,4,5,5,6};
    vector<double> rebro_7 = {123.36,1,1,1,2,2,2,2,2,2,3,3,3,3,3,3,4,4,4,4,4,5,5,5,5,6,6,6,6,6,7};
    vector<double> rebro_8 = {33.15,1,1,2,2,2,2,2,2,3,3,3,3,3,3,4,4,4,4,4,5,5,5,5,6,6,6,6,6,7,7};
    vector<double> rebro_9 = {72.4,2,2,2,2,3,3,3,3,4,4,4,4,4,5,5,5,5,5,6,6,6,6,7,7,7,7,7,8,8,8};
    vector<double> rebro_10 = {85.96,2,2,2,3,3,3,3,4,4,4,4,4,5,5,5,5,5,6,6,6,6,7,7,7,7,7,7,8,8,8};
    vector<double> rebro_11 = {15.78,3,3,3,3,3,3,3,3,4,4,4,5,5,5,5,5,6,6,6,6,7,7,7,7,7,7,7,7,7,7};
    vector<double> rebro_12 = {45.52,3,3,3,3,3,3,3,3,4,4,4,5,5,5,5,5,6,6,6,6,7,7,7,7,7,7,7,7,7,7};
    vector<double> rebro_13 = {15.65,3,3,3,3,3,3,3,3,4,4,4,5,5,5,5,5,6,6,6,6,7,7,7,7,7,7,7,7,7,7};
    vector<double> rebro_14 = {256.72,3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,5,5,5,5,5,5,6,6,6,6,7,7,7,8,9};

    vector<pair<int, int>> buff;
    vector<pair<int, string>> rebra;
    vector<pair<int, int>> rebra_int;
    
    for (size_t i = 0; i < orders.size(); i++){
        buff.push_back(make_pair(i, GetData(orders[i])));
        rebra.push_back(make_pair(i, GetRebro(orders[i])));
    }

    sort(buff.begin(), buff.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;
    });

    for (const auto& pair : buff) {
        cout << orders[pair.first] << endl;
    }

    cout << endl;
   
   for (size_t i = 0; i < rebra.size(); i++) {
        rebra_int.push_back(make_pair(i, RemoveAllExceptLast(rebra[i].second)));
        // cout << rebra_int[i].second << endl;
    }

    Ledokol led_1(11, true); // саббета 3 = 11
    Ledokol led_2(6, true); // сабета 1 = 14
    Ledokol led_4(13, true); // 2 ребро
    Ledokol led_3(11, true); // саббета 2 = 13
   
    

    vector<Ledokol> mnogo_ledokolov = {led_1, led_2, led_3, led_4};
    vector<vector<double>>  all_way_str = {rebro_1, rebro_2, rebro_3, rebro_4, rebro_5, rebro_6, rebro_7, rebro_8, rebro_9, rebro_10, rebro_11, rebro_12, rebro_13, rebro_14};
    int j = 0;
    for (size_t i = 0; i < rebra_int.size(); i++) {
        if (rebra_int[i].second <= 9) {
            if (mnogo_ledokolov[j].status_ == true) {
                mnogo_ledokolov[j].status_ = false;
                mnogo_ledokolov[j].where_go_ = "Забирает с Баренцевого";
                mnogo_ledokolov[j].direction = 0;
                for (int k = mnogo_ledokolov[j].spot_ - 1; k >= rebra_int[i].second; k--) {
                    mnogo_ledokolov[j].direction += all_way_str[k][0];
                    mnogo_ledokolov[j].day_start = buff[i].second - mnogo_ledokolov[j].direction / (9 * 1.8);
                    
                }
                cout << "Откуда забирает:" << mnogo_ledokolov[j].where_go_ 
                << " Расстояние до ребра: " << mnogo_ledokolov[j].direction << " Дата отплытия за " << mnogo_ledokolov[j].day_start << " дней раньше прибытия судна" << endl;
            } else {
                if (mnogo_ledokolov[j].status_ == true) {
                mnogo_ledokolov[j].status_ = false;
                mnogo_ledokolov[j - 1].status_ = true;
                mnogo_ledokolov[j].where_go_ = "Забирает с Баренцевого";
                mnogo_ledokolov[j].direction = 0;
                for (int k = rebra_int[i].second; k < mnogo_ledokolov[j].spot_ - 1; k++) {
                    mnogo_ledokolov[j].direction += all_way_str[k][0];
                    mnogo_ledokolov[j].day_start = buff[i].second - mnogo_ledokolov[j].direction / (9 * 1.8);
                    
                }
                cout << GetName(orders[i]) << "Откуда забирает:" << mnogo_ledokolov[j].where_go_ 
                << " Расстояние до ребра: " << mnogo_ledokolov[j].direction << " Дата отплытия за " << mnogo_ledokolov[j].day_start << " дней раньше прибытия судна" << endl;
            }
                
            }
        } else {
            mnogo_ledokolov[j - 1].status_ = true;
            cout << "Забираем с портов" << endl;
            
        }
        if (j < 4) j++;
        if (j == 4) j-=2;
    }

    // int ledokol_can_1 = 1;
    // int ledokol_can_2 = 1;
    // int ledokol_can_3 = 1;
    // int ledokol_can_4 = 1;
    // int cont = 0;
    // size_t j = 0;
    // for (size_t i = 9; i <= 30; i++) {
    //     cont = 0;
    //     for (; j < rebra_int.size() && cont == 0; j++) {
            
    //         if (rebra_int[j].second == static_cast<int>(i)) {
    //             for (size_t k = 0; k < mnogo_ledokolov.size() && cont == 0; k++) {
    //                 if (i <= 9) {
    //                         cont = 1;
    //                         if (mnogo_ledokolov[k].status_ == true) {
                                
    //                             mnogo_ledokolov[k].status_ = false;
    //                             mnogo_ledokolov[k].where_go_ = "Забирает с Баренцевого";
    //                             mnogo_ledokolov[k].direction = 0;
    //                                 for (int l = mnogo_ledokolov[k].spot_ - 1; l >= rebra_int[j].second; l--) {
    //                                     mnogo_ledokolov[k].direction += all_way_str[l][0];
                                        
    //                                 }

                                    
    //                                 mnogo_ledokolov[k].day_start = buff[j].second - mnogo_ledokolov[k].direction / (9 * 1.8);
    //                             cout << "Откуда забирает:" << mnogo_ledokolov[j].where_go_ 
    //                             << " Расстояние до ребра: " << mnogo_ledokolov[j].direction << " Дата отплытия за " << mnogo_ledokolov[j].day_start << " дней раньше прибытия судна" << endl;
    //                     }

    //                 } else {
    //                     // cont = 1;
    //                     if (mnogo_ledokolov[k].status_ == true) {
    //                             // 
    //                             mnogo_ledokolov[k].status_ = false;
    //                             mnogo_ledokolov[k].where_go_ = "Забирает с порта";
    //                             mnogo_ledokolov[k].direction = 0;
    //                                 for (int l = rebra_int[j].second; l <=  mnogo_ledokolov[k].spot_ - 1; l++) {
    //                                     mnogo_ledokolov[k].direction += all_way_str[l][0];
                                        
    //                                 }

    //                             mnogo_ledokolov[k].day_start = buff[j].second - mnogo_ledokolov[k].direction / (9 * 1.8);
    //                             cout << "Откуда забирает:" << mnogo_ledokolov[j].where_go_ 
    //                             << " Расстояние до ребра: " << mnogo_ledokolov[j].direction << " Дата отплытия за " << mnogo_ledokolov[j].day_start << " дней раньше прибытия судна" << endl;
    //                     }
    //                 }
                        
    //             }
    //         }
    // }

    //         // if (static_cast<int>(i) == ledokol_can_1) {
    //         //     ledokol_can_1 = 0;
    //         //     mnogo_ledokolov[0].status_ = true;
    //         // } else if (static_cast<int>(i) == ledokol_can_2) {
    //         //     ledokol_can_2 = 0;
    //         //     mnogo_ledokolov[1].status_ = true;
    //         // } else if (static_cast<int>(i) == ledokol_can_3) {
    //         //     ledokol_can_3 = 0;
    //         //     mnogo_ledokolov[2].status_ = true;
    //         // } else if (static_cast<int>(i) == ledokol_can_4) {
    //         //     ledokol_can_4 = 0;
    //         //     mnogo_ledokolov[3].status_ = true;
    //         // }
    // }
    
    
}

int main() {
    vector<std::string> orders;
    ifstream file("output.csv");
    string line;
    while (getline(file, line)) {
        orders.push_back(line);
    }
    DelEmpty(orders);

    // Сортировка вектора orders по возрастанию даты
    // Не арбайтен
    // sort(orders.begin(), orders.end(), compareDates);

    
    
    // for (auto& order : orders){
    //         cout << order << endl;
    //         // cout << GetData(order) << endl;
    //         // cout << GetHour(order) << endl;
    // }

    // int day;
    // int hour = 0;



    // int order_day, order_hour;    
    // for(day = 0; day <= 30; day++){
    //     for(hour = 0;hour < 24; hour++){
            

    //     }
    // }

    SORTTTTT(orders);

    return 0;
}

