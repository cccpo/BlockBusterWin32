#include "Data.h"


//"HiScore.txt"よりハイスコアを取得
int Data::HiScoreLoad() {
    std::ifstream ifs("HiScore.txt");
    std::string str;
    
    //取得できない場合は異常終了
    if (ifs.fail()) {
        return -1;
    }
    //一行取得 #ToDo ランキングを設けるのであればハイスコアテーブルを設けて実装する
    std::getline(ifs, str);

    HiScore = atoi(str.c_str());

    return (HiScore);
}

//ハイスコアを"HiScore.txt"に保存する
void Data::HiScoreSave(int inHiScore) {
    std::ofstream outputfile("HiScore.txt");
    
    outputfile << inHiScore;
    outputfile.close();
}