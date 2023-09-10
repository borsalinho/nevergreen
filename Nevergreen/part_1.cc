#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Zayavka
{
    string name;
    int id;
    int leg_klass;
    double speed;
    int start_day;
    int start_hour;
    string start_point;
    string end_point;
    int end_day;
    int end_hour;
    int pass;
    string waiting_point;
    int waiting_day;
    int waiting_hour;
};


class GetMarsh {
public:

    GetMarsh(Zayavka z, std::ofstream& output_file){
        z.speed *= 1.852; // переводим в км/ч
        // cout << "Дата отправки" << endl;
        // cout << "day:" << z.start_day << " hour:" << z.start_hour << endl;

        //алгоритм подстройки маршрута

        if(z.start_point == "точка в Баренцевом море"){
            // нужно выбрать левый или правый тк они могут пребывать

            // правый это ребро 5+6
            Zayavka zay_r;
            vector<vector<double>> way_right = {rebro_5, rebro_6};
            vector<string> way_right_str = { "rebro_5", "rebro_6"};
            zay_r = CheekiBreeki(z, way_right, way_right_str);

            // левый это 1+2+3
            Zayavka zay_l;
            vector<vector<double>> way_left = {rebro_1, rebro_2, rebro_3};
            vector<string> way_left_str = { "rebro_1", "rebro_2", "rebro_3"};
            zay_l = CheekiBreeki(z, way_left, way_left_str);

            
            if (!zay_r.pass && !zay_l.pass){ // если НЕ проходит по обоим путям то смотрим уже ВЫБИРАЕМ БЛИЖАЙЩИЙ
                // cout << "НЕ ПРОШЛИ ОБЕ" << endl;
                GetPoint(zay_r, zay_l, output_file); // выбирает ближайщий
            } else if (zay_r.pass || zay_l.pass) { // если проходит ХОТЯ БЫ ОДИН то смотрим уже основной путь
                // cout << "ПРОШЕЛ КАК МИНИМУМ ОДИН" << endl;
                vector<string> main_way_str;
                vector<vector<double>> main_way;

                if (zay_r.pass && !zay_l.pass){ // если прошелся по правому маршруту
                    main_way = way_right;
                    main_way_str = { "rebro_5", "rebro_6"};
                }
                if (!zay_r.pass && zay_l.pass){ // если прошелся по правому маршруту
                    main_way = way_left;
                    main_way_str = { "rebro_1", "rebro_2", "rebro_3"};
                }

                main_way_str.push_back("rebro_7");
                main_way_str.push_back("rebro_8");
                main_way_str.push_back("rebro_9");
                main_way_str.push_back("rebro_10");

                main_way.push_back(rebro_7);
                main_way.push_back(rebro_8);
                main_way.push_back(rebro_9);
                main_way.push_back(rebro_10);

                if (z.end_point == "Саббета 1"){
                    main_way.push_back(rebro_14);
                    main_way_str.push_back("rebro_14");
                }
                if (z.end_point == "Саббета 2"){
                    main_way.push_back(rebro_13);
                    main_way_str.push_back("rebro_13");
                }
                if (z.end_point == "Саббета 3"){
                    main_way.push_back(rebro_11);
                    main_way_str.push_back("rebro_11");
                }
                z = CheekiBreeki(z, main_way, main_way_str);
                if (z.pass) {
                    output_file << z.name << ", плывет с: "<< z.start_point  << " не нуждается в сопровождении" << endl;
                } else {
                    output_file << 
                    z.name << 
                    ", " <<
                    z.id << 
                    ", плывет с: "<< z.start_point  << ", " << z.waiting_point << 
                    ", дата:" << z.waiting_day << 
                    ", время:" << z.waiting_hour <<
                    ", дата прибытия:" << z.end_day << 
                    ", время прибытия:" << z.end_hour 
                    << endl;
                }
            } 

        } else {    
            vector<string> main_way_str;
            vector<vector<double>> main_way;
            if (z.start_point == "Саббета 1"){
                main_way.push_back(rebro_14);
                main_way_str.push_back("rebro_14");
            }
            if(z.start_point == "Саббета 2"){
                main_way.push_back(rebro_13);
                main_way_str.push_back("rebro_13");
            }
            if(z.start_point == "Саббета 3"){
                main_way.push_back(rebro_11);
                main_way_str.push_back("rebro_11");
            }

            main_way.push_back(rebro_10);
            main_way.push_back(rebro_9);
            main_way.push_back(rebro_8);
            main_way.push_back(rebro_7);

            main_way_str.push_back("rebro_10");
            main_way_str.push_back("rebro_9");
            main_way_str.push_back("rebro_8");
            main_way_str.push_back("rebro_7");

            z = CheekiBreeki(z, main_way, main_way_str);
            if (z.pass) {
                output_file << z.name << ", плывет с: "<< z.start_point  << " не нуждается в сопровождении" << endl;
            } else {
               output_file << 
                z.name << 
                ", " <<
                z.id << 
                ", плывет в: "<< z.start_point  << ", " << z.waiting_point << 
                ", дата:" << z.waiting_day << 
                ", время:" << z.waiting_hour <<
                ", дата прибытия:" << z.end_day << 
                ", время прибытия:" << z.end_hour 
                << endl;}

        }
    }

    Zayavka CheekiBreeki(Zayavka z, vector<vector<double>> way, vector<string> way_str){
        size_t j = 0;
        int day;
        int pass = 0;
        int hour = z.start_hour;
        double way_in_rebro = 0;
        // cout << "начал с " << way_str[j] << endl;
        for(day = z.start_day; day <= 30; day++){
            // cout << "day " << day << endl;
            z.speed = z.speed - way[j][day] * 0.07;
            if(way[j][day] > z.leg_klass || pass) {
                break;
            }
            for(;hour < 24; hour++){
                // cout << "hour " << hour << endl;
                way_in_rebro = way_in_rebro + z.speed;
                if (way_in_rebro >= way[j][0]){
                    
                    
                    // cout << "перешел на " << way_str[j] << endl;
                    way_in_rebro = 0;
                    if(way[j][day] > z.leg_klass) {
                        break;
                    }
                    j++;
                    if (j >= way.size()){
                        pass = 1;
                        j--; 
                        break;
                    }
                }
            }
            hour = 0;
        }

        if (pass){
            // cout << "прошел" << endl;
            z.pass = 1;
        } else {
            z.pass = 0;
            // cout << "застрял в ребре номер " << way_str[j] << " дата:" << day << " время:" << hour << endl;
            hour =  hour - static_cast<int>(way_in_rebro/z.speed);
            if (hour < 0) {
                day = day - 1;
                hour = 24 + hour;
            }
            z.waiting_point = "забрать перед " + way_str[j];
            z.waiting_day = day;
            z.waiting_hour = hour;
            // cout << z.waiting_point << " дата:" << z.waiting_day << " время:" << z.waiting_hour << endl;
            
        }
        return z;
    }

    void GetPoint(Zayavka zay_r, Zayavka zay_l, std::ofstream& output_file){
        std::vector<std::pair<int, std::string>> pairs;

        pairs.push_back(make_pair(5, "rebro3"));
        pairs.push_back(make_pair(4, "rebro6"));
        pairs.push_back(make_pair(3, "rebro2"));
        pairs.push_back(make_pair(2, "rebro5"));
        pairs.push_back(make_pair(1, "rebro1"));
        int proir_r = 0, proir_l = 0;
        for (const auto& pair : pairs) {
            if (zay_r.waiting_point == pair.second) {
                proir_r = pair.first;
            }
        }
        for (const auto& pair : pairs) {
            if (zay_l.waiting_point == pair.second) {
                proir_l = pair.first;
            }
        }
        if (proir_r > proir_l){
            output_file << 
            zay_r.name << 
            ", " <<
            zay_r.id << 
            ", плывет с: "<< zay_r.start_point << ", " << 
            zay_r.waiting_point << 
            ", дата:" << zay_r.waiting_day << 
            ", время:" << zay_r.waiting_hour <<
            ", дата прибытия:" << zay_r.end_day << 
            ", время прибытия:" << zay_r.end_hour <<
             endl;
            
        } else {
            output_file << 
            zay_l.name << 
            ", " <<
            zay_l.id << 
            ", плывет с: "<< zay_l.start_point << ", " << 
            zay_l.waiting_point << 
            ", дата:" << zay_l.waiting_day << 
            ", время:" << zay_l.waiting_hour <<
            ", дата прибытия:" << zay_l.end_day << 
            ", время прибытия:" << zay_l.end_hour <<
             endl;
        }

        
    }

    // vector<int> way;
    

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

private:

};

std::vector<Zayavka> parse_csv(const std::string& filename) {
    std::vector<Zayavka> zayavki;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << filename << std::endl;
        return zayavki;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::string name, start_point, end_point, start_date_m, start_date, 
    start_hour, end_date_m, end_date, end_hour, ice_class_str, id, speed, 
    end_date_q, buff, start_date_q;
    int ice_class;
    std::stringstream ss(line);

    std::getline(ss, name, ',');

    std::getline(ss, id, ',');

    std::getline(ss, ice_class_str, ',');
    if (ice_class_str == "Arc7") ice_class = 10; // берем по верхнему пределу
    if (ice_class_str == "Arc6" ||
        ice_class_str == "Arc5" ||
        ice_class_str == "Arc4" ) ice_class = 6;
    if (ice_class_str == "No ice class" ||
        ice_class_str == "Ice1" ||
        ice_class_str == "Ice3" ||
        ice_class_str == "Ice2" ) ice_class = 3;

    std::getline(ss, speed, ',');

    std::getline(ss, start_point, ',');

    std::getline(ss, end_point, ',');

    std::getline(ss, start_date_m, ',');
    std::stringstream ss_1(start_date_m);
    std::getline(ss_1, start_date_q, ' ');
    std::stringstream ss_11(start_date_q);
    std::getline(ss_11, start_date, '.');
    std::getline(ss_1, start_hour, ':');

    std::getline(ss, end_date_m, ',');
    std::stringstream ss_2(end_date_m);
    std::getline(ss_2, end_date_q, ' ');
    std::stringstream ss_22(end_date_q);
    std::getline(ss_22, end_date, '.');
    std::getline(ss_2, end_hour, ':');

        Zayavka zayavka = { name, 
                            stoi(id),
                            ice_class, 
                            stod(speed), 
                            stoi(start_date), 
                            stoi(start_hour),
                            start_point, 
                            end_point,
                            stoi(end_date), 
                            stoi(end_hour),
                            -1,
                            "",
                            0,
                            0
                        };
        zayavki.push_back(zayavka);
    }
    file.close();
    return zayavki;
}

int main() {
    std::ofstream output_file("output.csv"); // Открываем файл для записи

    std::vector<Zayavka> zayavki = parse_csv("zayavki.csv");
    for (const auto& zayavka : zayavki) {
        GetMarsh p1(zayavka, output_file);
    }
    output_file.close(); // Закрываем файл
    return 0;
}